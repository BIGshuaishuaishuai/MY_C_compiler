#include "node.hpp"
#include "CodeTran.hpp"
#include <array>
#include <vector>

using namespace std;
using namespace node;
using namespace llvm;
#define INFO "[INFO]: "
#define INTCAST(x) context.builder.CreateIntCast(x, context.builder.getInt32Ty(), true)
// LLVMContext Context;

extern node::Root* root;

void CodeContext::CreateContext(node::Root* root){
    std::cout << "Generating code...\n";
    CodeContext &tmp_ = *this;
    // std::cout << "[Root 1]"<<std::endl;
    std::cout << this << ":"<< root << std::endl;
    root->CodeGen(tmp_);
    std::cout << "Code is generated.\n"<<std::endl;
    module->print(outs(), nullptr);
    std::error_code error;
    raw_fd_ostream file("example.bc", error, sys::fs::F_None);
    WriteBitcodeToFile(*module, file);
}


static Type *typeOf(const VarType* type)
{
    if (type->_type == 3) {
        return Type::getInt64Ty(Context);
    }
    else if (type->_type == 2) {
        return Type::getDoubleTy(Context);
    }
    else if (type->_type == 1) {
        return Type::getInt8Ty(Context);
    }
    
    return Type::getVoidTy(Context);
}

Value* Root::CodeGen(CodeContext& context){
    // std::cout<<INFO<<"Into CodeGen"<<std::endl; 
    Value* last = NULL;
    context.cur_vars = context.global_vars;
    // std::cout<<INFO<<"Into CodeGen"<<std::endl; 
    // std::cout<<INFO<<"into for"<<std::endl;
    for (auto it = _decls->begin(); it != _decls->end();it++) {
        
        auto pt = *it;
        // std::cout <<INFO<<"Generating the "<<std::endl;
        last = pt->CodeGen(context);
    }
    // std::cout <<INFO<<"Generated ROOT"<<std::endl;
    return last;
}
Value* FuncDecl::CodeGen(CodeContext& context){
    vector<Type*> argtypes;
    Args::const_iterator it;
    // std::map<std::string, Value*> vars;
    FunctionType* ftype_ = NULL;
    std::cout << "Generating function: " << _FuncName<< std::endl;

    if (context.func_table.find(_FuncName) != context.func_table.end()){
        std::cerr << "declared function " << _FuncName << endl;
        return NULL;
    }
    for (it = _args->begin(); it != _args->end();it++) {
        argtypes.push_back(typeOf(((**it)._Type)));
    }
    if (argtypes.size() == 0){
        ftype_ = FunctionType::get(typeOf(_Type),false);
    }
    else {
        ftype_ = FunctionType::get(typeOf(_Type),argtypes,false);
    }
    std::cout<<INFO<<"Here?"<<std::endl;

    Function * func = NULL;
    if (_FuncName == "main"){
        func = Function::Create(ftype_,GlobalValue::ExternalLinkage, _FuncName.c_str(),context.module);
    }
    else{
        func = Function::Create(ftype_,GlobalValue::InternalLinkage, _FuncName.c_str(),context.module);
    }

    BasicBlock *bblock = BasicBlock::Create(Context,_FuncName.c_str(), func, 0);
    CodeBlock* tmp = new CodeBlock();
    tmp->codeblock = bblock;
    // tmp->local_vars = vars;
    context.cur_vars = tmp->local_vars;
    context.func_table[_FuncName.c_str()] = tmp;
    context.InsBlock(tmp);
    context.builder.SetInsertPoint(bblock);

    for (int i = 0; i < _args->size();i++) {
        func->getArg(i)->setName(((*_args)[i]->_Name).c_str());
    }
    if (_args!=NULL){
        // std::cout<<INFO<<"not null"<<std::endl;    
        for (it = _args->begin(); it != _args->end();it++) {
            (*it)->CodeGen(context);
        }
    }
    if (_fb != NULL){
        Value* last = NULL;
        Stms::const_iterator it_;
        for (it_ = _fb->begin(); it_ != _fb->end();it_++) {
            auto pt = *it_;
            std::cout << "Generating stm "<< std::endl;
            last = pt->CodeGen(context);
        }
        std::cout << "Genetated function body"<<std::endl;
        bblock = context.TailBlock()->codeblock;
        context.builder.CreateRet(last);
    }
    
    context.RmTailBlock();
    std::cout << "Generated function: " << _FuncName<< std::endl;
    return func; 
}
Value* Arg::CodeGen(CodeContext& context){
    std::cout << "Generate arg:" << tps[_Type->_type]<< " " << _Name << endl;
    auto alloc = new AllocaInst(typeOf(_Type), 0,_Name.c_str(), context.TailBlock()->codeblock);
    std::map<std::string , Value*>& vars = context.localvars();
    vars[_Name] = alloc; 
    return alloc;
}
Value* VarDecl::CodeGen(CodeContext& context){
    Type * typ = typeOf(_Type);
    VarList::const_iterator it;
    Value *alloc = NULL;
    std::map<std::string , Value*>& vars = context.localvars();
    
    for (it = _list->begin();it != _list->end();it++){
        if (vars.find((*it)->_id) != vars.end()){
            std::cout <<"varible exits! line: "<<(*it)->line<<std::endl;
            exit(1);
        }
        std::cout << "Generate var:" << " " << (*it)->_id <<" var"<< endl;
        if (_Type->_array == true) {
            auto new_pt = static_cast<ArrayType*>(_Type); //正确，通过使用static_cast向下转型
            int arrnum = new_pt->_num;

            std::vector<llvm::Constant*> tmp;
            llvm::ArrayType* arrType = llvm::ArrayType::get(typ, arrnum);
            alloc = context.builder.CreateAlloca(arrType);

            if ((*it)->_arrayinit != NULL){
                for (int i = 0;i < (*it)->_arrayinit->size();i++){
                    Value* index = ConstantInt::get(Type::getInt32Ty(Context), i);
                    Value* val = (*((*it)->_arrayinit))[i] -> CodeGen(context);
                    Value* ptr = context.builder.CreateGEP(alloc, {ConstantInt::get(Type::getInt32Ty(Context), 0), index});
                    context.builder.CreateStore(val, ptr);
                }
            }
        }
        else if (_Type->_ptr == true){
            alloc = context.builder.CreateAlloca(context.builder.getInt64Ty());
            if ((*it)->_initvaL != NULL) {
                std::cout << "Generating assignment for " << (*it)->_id <<" var"<< endl;
                auto ret = ((*it)->_initvaL)->CodeGen(context);
                
                new StoreInst(ret, alloc, false, context.TailBlock()->codeblock);
            }
        }
        else {
            alloc = new AllocaInst(typ,0, (*it)->_id.c_str(), context.TailBlock()->codeblock);
           
            if ((*it)->_initvaL != NULL) {
                std::cout << "Generating assignment for " << (*it)->_id <<" var"<< endl;
                auto ret = ((*it)->_initvaL)->CodeGen(context);
                new StoreInst(ret, alloc, false, context.TailBlock()->codeblock);
                
            }

            // std::cout<<INFO<<"cur vars"<<std::endl;
            for (auto &t : vars){
                // std::cout<<INFO<<t.first<<":"<<t.second<<std::endl;
            }
        }
        vars[(*it)->_id] = alloc;
        
    }
    return alloc;
}
Value* IfStm::CodeGen(CodeContext& context){
    Value* res = NULL;
    BasicBlock *curblock = context.TailBlock()->codeblock;
    Function *func = curblock->getParent();
    context.builder.SetInsertPoint(curblock);
    
    BasicBlock *entry = BasicBlock::Create(Context, (string("entry_") + to_string((context.fors++))).c_str(), func);
    context.builder.CreateBr(entry);
    BasicBlock *exit_ = BasicBlock::Create(Context, (string("exit_") + to_string((context.fors++))).c_str(), func);
    
    
    CodeBlock* tmp_ = new CodeBlock();
    BasicBlock *ifBB = (BasicBlock*)(_ifStm->CodeGen(context));
    auto ifBB_e = context.TailBlock()->codeblock;
    context.builder.SetInsertPoint(ifBB_e);
    context.builder.CreateBr(exit_);
    context.RmTailBlock();

    BasicBlock *elseBB = exit_;
    if (_ifelse){
        elseBB = (BasicBlock*)_elseifStm->CodeGen(context);
        auto elseBB_e = context.TailBlock()->codeblock;
        context.RmTailBlock();
        context.builder.SetInsertPoint(elseBB_e);
        context.builder.CreateBr(exit_);
    }
    

    context.builder.SetInsertPoint(entry);
    context.builder.CreateCondBr(_switch->CodeGen(context), ifBB, elseBB);

    CodeBlock *tool = new CodeBlock();
    tool->codeblock = exit_;
    tool ->local_vars = context.TailBlock()->local_vars;
    context.RmTailBlock();
    context.InsBlock(tool);
    context.builder.SetInsertPoint(exit_);

    return res;
}
Value* ForStm::CodeGen(CodeContext& context){

    Value* res = NULL;
    BasicBlock *cur = context.TailBlock()->codeblock;
    Function *func = cur->getParent();
    auto entry = BasicBlock::Create(Context, (string("entry_") + to_string((context.fors++))).c_str(), func);
    BasicBlock *step_ = BasicBlock::Create(Context, (string("step_") + to_string((context.fors++))).c_str(), func);
    BasicBlock *exit_ = BasicBlock::Create(Context, (string("exit_") + to_string((context.fors++))).c_str(), func);
    context.builder.SetInsertPoint(cur);
    context.builder.CreateBr(entry);
    Value* init = NULL;
    context.builder.SetInsertPoint(entry);

    CodeBlock *tool_ = new CodeBlock();
    tool_->codeblock = entry;
    // tool ->cur_vars = context.TailBlock()->localvars();
    tool_ ->local_vars = context.TailBlock()->local_vars;
    context.InsBlock(tool_);
    if (_expr1) {
        init = _expr1->CodeGen(context);
        // std::cout<<INFO<<"COND 1 DONE"<<std::endl;
    }
    context.builder.SetInsertPoint(entry);
    context.builder.CreateBr(step_);

    // std::cout<<INFO<<"COND 2 DONE"<<std::endl;
    context.RmTailBlock();
    BasicBlock *loop_ = (BasicBlock*)(_block->CodeGen(context));
    
    auto loop_e = context.TailBlock()->codeblock;
    context.builder.SetInsertPoint(loop_e);
    Value *act = NULL;
    if (_expr3) _expr3->CodeGen(context);
    // std::cout<<INFO<<"STEP 1 DONE"<<std::endl;
    context.RmTailBlock();
    context.builder.SetInsertPoint(loop_e);
    context.builder.CreateBr(step_);
    // std::cout<<INFO<<"STEP 2 DONE"<<std::endl;
    

    CodeBlock *tool_step = new CodeBlock();
    tool_step->codeblock = step_;
    tool_step ->local_vars = context.TailBlock()->local_vars;
    context.InsBlock(tool_step);
    context.builder.SetInsertPoint(step_);
    Value* cmp = NULL;
    if(_expr2)cmp = _expr2->CodeGen(context);
    // std::cout<<INFO<<"CMP 1 DONE"<<std::endl;

    context.builder.SetInsertPoint(step_);
    context.builder.CreateCondBr(cmp, loop_, exit_);
    // std::cout<<INFO<<"CMP 2 DONE"<<std::endl;
    context.RmTailBlock();
    
    // 在exit块中添加返回指令
    CodeBlock *tool = new CodeBlock();
    tool->codeblock = exit_;
    // tool ->cur_vars = context.TailBlock()->localvars();
    tool ->local_vars = context.TailBlock()->local_vars;
    // tool ->global_vars = context.TailBlock()->global_vars;
    context.RmTailBlock();
    context.InsBlock(tool);
    context.builder.SetInsertPoint(exit_);
    return res;
}
Value* WhileStm::CodeGen(CodeContext& context){
    Value* res = NULL;
    // 创建 While 语句的基本块
    
    BasicBlock* curblock = context.TailBlock()->codeblock;
    Function* func = curblock->getParent();
    // BasicBlock *entry = context.builder.CreateBasicBlock
    BasicBlock *entry_ = BasicBlock::Create(Context, (string("entry_") + to_string(context.fors++)).c_str(), func);
    BasicBlock *exit_ = BasicBlock::Create(Context, (string("exit_") + to_string((context.fors++))).c_str(), func);
    context.builder.SetInsertPoint(curblock);
    context.builder.CreateBr(entry_);
    context.builder.SetInsertPoint(entry_);
    BasicBlock *loop_ = (BasicBlock*)(_block->CodeGen(context));
    auto loop_e = context.TailBlock()->codeblock;
    context.RmTailBlock();

    context.builder.SetInsertPoint(entry_);
    Value *cmp = _expr->CodeGen(context);
    context.builder.SetInsertPoint(entry_);
    context.builder.CreateCondBr(cmp, loop_, exit_);
    context.builder.SetInsertPoint(loop_e);
    context.builder.CreateBr(entry_);


    CodeBlock *tool = new CodeBlock();
    tool->codeblock = exit_;
    // tool ->cur_vars = context.TailBlock()->localvars();
    tool ->local_vars = context.TailBlock()->local_vars;
    // tool ->global_vars = context.TailBlock()->global_vars;
    context.RmTailBlock();
    context.InsBlock(tool);
    context.builder.SetInsertPoint(exit_);

    return res;
}
Value* DoStm::CodeGen(CodeContext& context){
    Value* res = NULL;

    return res;
}
Value* SwitchStm::CodeGen(CodeContext& context){
    Value* res = NULL;

    BasicBlock *curblock = context.TailBlock()->codeblock;
    Function *func = curblock->getParent();

    BasicBlock *entry = BasicBlock::Create(Context, "entry", func);
    CodeBlock* tmp_ = new CodeBlock();
    tmp_->codeblock = entry;
    context.InsBlock(tmp_);

    int len = _cases->size();
    context.builder.SetInsertPoint(entry);
    Value* val = _expr->CodeGen(context); 
    BasicBlock *exit_ = curblock;
    SwitchInst *switchInst = context.builder.CreateSwitch(val, exit_, len);
    Value* last = NULL;
    for (int i = 0;i < len;i++){
        CaseStm* pt = (*_cases)[i];
        BasicBlock* case_ = BasicBlock::Create(Context,(string("case_") + to_string(i)).c_str(),func);
        CodeBlock* tmp = new CodeBlock();
        tmp->codeblock = case_;
        switchInst->addCase(dyn_cast<llvm::ConstantInt>((pt->_expr->CodeGen(context))), case_);
        context.InsBlock(tmp);
        context.builder.SetInsertPoint(case_);
        // tmp ->cur_vars = context.TailBlock()->localvars();
        tmp ->local_vars = context.TailBlock()->local_vars;
        // tmp ->global_vars = context.TailBlock()->global_vars;
        last = pt->CodeGen(context);
        context.builder.CreateBr(exit_);
        context.RmTailBlock();
    }

    context.RmTailBlock();
    CodeBlock *tool = new CodeBlock();
    tool->codeblock = exit_;
    // tool ->cur_vars = context.TailBlock()->localvars();
    tool ->local_vars = context.TailBlock()->local_vars;
    // tool ->global_vars = context.TailBlock()->global_vars;
    context.RmTailBlock();
    context.InsBlock(tool);
    context.builder.SetInsertPoint(exit_);
    // CodeBlock *tool = new CodeBlock();
    // tool->codeblock = exit_;
    // tool ->local_vars = context.TailBlock()->local_vars;

    // context.InsBlock(tool);
    // context.builder.SetInsertPoint(exit_);

    return last;
}
Value* CaseStm::CodeGen(CodeContext& context){
    BasicBlock *curblock = context.TailBlock()->codeblock;
    Function * func = curblock->getParent();
    Value* last = NULL;
    if (func == NULL){
        std::cout<<"no func"<<std::endl;
        exit(1);
    }
    BasicBlock *bblock = BasicBlock::Create(Context,(string("block_") + to_string((context.blocks++))).c_str(), func, 0);
    CodeBlock* tool = new CodeBlock();
    tool->codeblock = bblock;
    tool ->local_vars = context.TailBlock()->local_vars;

    context.InsBlock(tool);
    Stms::const_iterator it;
    for (it = _stms->begin(); it != _stms->end();it++) {
        auto pt = *it;
        std::cout << "Generating stm " <<  std::endl;
        last = pt->CodeGen(context);
    }

    context.RmTailBlock();
    std::cout << "Genetated case"<<std::endl;
    return bblock; 
}
Value* BreakStm::CodeGen(CodeContext& context){
    Value* res = NULL;

    return res;
}
Value* ExprStm::CodeGen(CodeContext& context){
    cout <<"The ExprStm"<<std::endl;
    Value* res = _expr->CodeGen(context);
    
    return res;
}
Value* ContinueStm::CodeGen(CodeContext& context){
    Value* res = NULL;

    return res;
}
Value* ReturnStm::CodeGen(CodeContext& context){
    Value* res = NULL;
    CodeBlock* cur = context.TailBlock();
    Function* func = cur->codeblock->getParent();
    context.builder.SetInsertPoint(cur->codeblock);
    context.builder.CreateRet(_return->CodeGen(context));
    return res;
}
Value* Block::CodeGen(CodeContext& context){
    Value* last = NULL;
    BasicBlock *curblock = context.TailBlock()->codeblock;
    
    Function * func = curblock->getParent();
    if (func == NULL){
        std::cout<<"no func"<<std::endl;
        exit(1);
    }
    BasicBlock *bblock = BasicBlock::Create(Context,(string("block_") + to_string((context.blocks++))), func, 0);
    CodeBlock* tool = new CodeBlock();
    tool->codeblock = bblock;
    tool->local_vars = context.TailBlock()->local_vars;
    context.builder.SetInsertPoint(bblock);
    context.InsBlock(tool);

    Stms::const_iterator it;
    for (it = _statements->begin(); it != _statements->end();it++) {
        auto pt = *it;
        std::cout << "Generating stm " <<  std::endl;
        std::cout << "****[The ptr]****:"<<typeid(pt).name()<< std::endl;
        last = pt->CodeGen(context);
    }

    std::cout << "Genetated Block"<<std::endl;
    return bblock; 
}
Value* SOP::CodeGen(CodeContext& context){
    std::cout << "Creating single operation " << bops[op] << endl;
    int mode = 0;
    auto inst = Instruction::Sub ;
    switch(op){
        case 1:return lhs->CodeGen(context);
        case 2:;mode = 1;return  BinaryOperator::Create(inst,ConstantInt::get(Type::getInt64Ty(Context), 0, true), lhs->CodeGen(context), "", context.TailBlock()->codeblock);
        // case 3:auto inst = Instruction::
        // case 4:return 
        case 5:return BinaryOperator::CreateNot(lhs->CodeGen(context), "");
    }
    

}
Value* BINOP::CodeGen(CodeContext& context){
    std::cout << "Creating binary operation " << bops[op] << endl;
    auto inst_1 = Instruction::Add ;
    auto inst_2 = CmpInst::ICMP_ULT;
    auto vars = context.localvars();
    Value* op1, *op2;
    Value* res = NULL;
    int math = 0,cmp = 0;
    auto pt = rhs;
    Id* new_pt= NULL;
    // if (lhs == NULL)std::cout<<INFO<<"LHS NULL"<<op<<std::endl;
    // if (rhs == NULL)std::cout<<INFO<<"RHS NULL"<<op<<std::endl;
    
    // std::cout<<INFO<<"op:"<<op<<std::endl;
    switch (op)
    {
        case 1 :
            // std::cout<<INFO<<"case 1"<<std::endl;
            op1 = lhs->CodeGen(context);
            op2 = rhs->CodeGen(context);
            // std::cout<<INFO<<"get done!"<<std::endl;
            // std::cout<<INFO<<"op1 type:"<<op1->getType()<<std::endl;
            // std::cout<<INFO<<"op2 type:"<<op2->getType()<<std::endl;
            res = context.builder.CreateAdd( op1,op2,(string("add_") + to_string(context.opnums++)).c_str());
            // llvm::Type::force_to_use(res);
            return res;
        case 2 :
            // std::cout<<INFO<<"case 2"<<std::endl;
            op1 = lhs->CodeGen(context);
            op2 = rhs->CodeGen(context);
            // std::cout<<INFO<<"get done!"<<std::endl;
            // std::cout<<INFO<<"op1 type:"<<op1->getType()<<std::endl;
            // std::cout<<INFO<<"op2 type:"<<op2->getType()<<std::endl;
            return context.builder.CreateSub( op1,op2,(string("sub_") + to_string(context.opnums++)).c_str());
        case 3 :
            // std::cout<<INFO<<"case 3"<<std::endl;
            op1 = lhs->CodeGen(context);
            op2 = rhs->CodeGen(context);
            // std::cout<<INFO<<"get done!"<<std::endl;
            // std::cout<<INFO<<"op1 type:"<<op1->getType()<<std::endl;
            // std::cout<<INFO<<"op2 type:"<<op2->getType()<<std::endl;
            return context.builder.CreateMul( op1,op2,(string("mul_") + to_string(context.opnums++)).c_str());
        case 4 :
            // std::cout<<INFO<<"case 4"<<std::endl;
            op1 = lhs->CodeGen(context);
            op2 = rhs->CodeGen(context);
            // std::cout<<INFO<<"get done!"<<std::endl;
            // std::cout<<INFO<<"op1 type:"<<op1->getType()<<std::endl;
            // std::cout<<INFO<<"op2 type:"<<op2->getType()<<std::endl;
            return context.builder.CreateSDiv(op1,op2,(string("div_") + to_string(context.opnums++)).c_str());
        case 5 :
            // std::cout<<INFO<<"case 5"<<std::endl;
            op1 = lhs->CodeGen(context);
            op2 = rhs->CodeGen(context);
            // std::cout<<INFO<<"get done!"<<std::endl;
            // std::cout<<INFO<<"op1 type:"<<op1->getType()<<std::endl;
            // std::cout<<INFO<<"op2 type:"<<op2->getType()<<std::endl;
            return context.builder.CreateSRem(op1,op2,(string("mod_") + to_string(context.opnums++)).c_str());
        case 6 :
            // std::cout<<INFO<<"case 6"<<std::endl;
            op1 = lhs->CodeGen(context);
            op2 = rhs->CodeGen(context);
            // std::cout<<INFO<<"get done!"<<std::endl;
            // std::cout<<INFO<<"op1 type:"<<op1->getType()<<std::endl;
            // std::cout<<INFO<<"op2 type:"<<op2->getType()<<std::endl;
            return context.builder.CreateShl( op1,op2,(string("shl_") + to_string(context.opnums++)).c_str());
        case 7 :return context.builder.CreateAShr(lhs->CodeGen(context),rhs->CodeGen(context),(string("shr_") + to_string(context.opnums++)).c_str());
        case 8 :
            // std::cout<<INFO<<"case 8"<<std::endl;
            op1 = INTCAST(lhs->CodeGen(context));
            op2 = INTCAST(rhs->CodeGen(context));
            // std::cout<<INFO<<"get done!"<<std::endl;
            // std::cout<<INFO<<"op1 type:"<<op1->getType()<<std::endl;
            // std::cout<<INFO<<"op2 type:"<<op2->getType()<<std::endl;
            return context.builder.CreateICmpULT((Value*)op1,(Value*)op2,(string("lt_") + to_string(context.opnums++)).c_str());
            // return CmpInst::Create(Instruction::ICmp, CmpInst::ICMP_ULT, op1, op2);

        case 9 :return context.builder.CreateICmpULE(lhs->CodeGen(context),rhs->CodeGen(context),(string("le_") + to_string(context.opnums++)).c_str());
        case 10:return context.builder.CreateICmpEQ (lhs->CodeGen(context),rhs->CodeGen(context),(string("eq_") + to_string(context.opnums++)).c_str());
        case 11:return context.builder.CreateICmpUGE(lhs->CodeGen(context),rhs->CodeGen(context),(string("ge_") + to_string(context.opnums++)).c_str());
        case 12:return context.builder.CreateICmpUGT(lhs->CodeGen(context),rhs->CodeGen(context),(string("gt_") + to_string(context.opnums++)).c_str());
        case 13:return context.builder.CreateICmpNE (lhs->CodeGen(context),rhs->CodeGen(context),(string("ne_") + to_string(context.opnums++)).c_str());
        case 14:
            new_pt = (Id*)lhs;
            // std::cout<<INFO<<"cur vars"<<std::endl;
            for (auto &t : vars){
                // std::cout<<INFO<<t.first<<":"<<t.second<<std::endl;
            }
            // if (new_pt == NULL) std::cout<<INFO<<"NULL"<<std::endl;
            std::cout<< "Creating assignment for " << new_pt->_name<<" var"<<std::endl;
            
            
            if (vars.find(new_pt->_name) == vars.end()) {
                std::cerr << "undeclared variable " << std::endl;
                return NULL;
            }
            
            // std::cout<<INFO<<"No new_pt"<<std::endl;
            op1 = pt->CodeGen(context);
            return new StoreInst(op1, context.localvars()[new_pt->_name], false, context.TailBlock()->codeblock);
        // case 22:inst = Instruction::ICMP;math = 1;break;
        case 15:return context.builder.CreateAdd( lhs->CodeGen(context),rhs->CodeGen(context),(string("add_") + to_string(context.opnums++)).c_str());
        case 16:return context.builder.CreateSub( lhs->CodeGen(context),rhs->CodeGen(context),(string("sub_") + to_string(context.opnums++)).c_str());
        case 18:return context.builder.CreateMul( lhs->CodeGen(context),rhs->CodeGen(context),(string("mul_") + to_string(context.opnums++)).c_str());
        case 17:return context.builder.CreateSDiv(lhs->CodeGen(context),rhs->CodeGen(context),(string("div_") + to_string(context.opnums++)).c_str());
        case 19:return context.builder.CreateSRem(lhs->CodeGen(context),rhs->CodeGen(context),(string("mod_") + to_string(context.opnums++)).c_str());
        case 20:return context.builder.CreateShl( lhs->CodeGen(context),rhs->CodeGen(context),(string("shl_") + to_string(context.opnums++)).c_str());
        case 21:return context.builder.CreateAShr(lhs->CodeGen(context),rhs->CodeGen(context),(string("shr_") + to_string(context.opnums++)).c_str());
        case 22:return context.builder.CreateAnd(lhs->CodeGen(context),rhs->CodeGen(context),(string("and_") + to_string(context.opnums++)).c_str());
        case 23:return context.builder.CreateAnd(lhs->CodeGen(context),rhs->CodeGen(context),(string("and_") + to_string(context.opnums++)).c_str());
        case 24:return context.builder.CreateOr( lhs->CodeGen(context),rhs->CodeGen(context),(string( "or_") + to_string(context.opnums++)).c_str());
        case 25:return context.builder.CreateOr( lhs->CodeGen(context),rhs->CodeGen(context),(string( "or_") + to_string(context.opnums++)).c_str());
    }
}
Value* FuncCall::CodeGen(CodeContext& context){
    Function *func = context.module->getFunction(_FuncName.c_str());
    if (func == NULL) {
        std::cerr << "no such function " << _FuncName << std::endl;
    }
    std::vector<Value *> args;
    ExprList::const_iterator it;
    for (it = _arguments->begin(); it != _arguments->end(); it++) {
        auto tp = *it;
        std::cout <<"Generate arg "<<std::endl;
        args.push_back(tp->CodeGen(context));
    }
    CallInst *call = CallInst::Create(func, args, "", context.TailBlock()->codeblock);
    std::cout << "Generated function call: " << _FuncName << endl;
    return call;
}
Value* ArrayCall::CodeGen(CodeContext& context){
    std::cout<<"Creating the array call: "<<_id<<std::endl;
    auto cur_vars = context.localvars();
    Value* alloc = NULL;
    if (cur_vars.find(_id) == cur_vars.end() and context.global_vars.find(_id) == context.global_vars.end()){
        std::cerr << "undeclared variable " << std::endl;
        return NULL;
    }
    if (cur_vars.find(_id) != cur_vars.end()) alloc = cur_vars[_id];
    else alloc = context.global_vars[_id];
    // auto alloc = cur_vars
    Value *idx = _num->CodeGen(context);
    Value* ptr = context.builder.CreateGEP(alloc,  idx);
    LoadInst *load = context.builder.CreateLoad(ptr);
    return load;
}
Value* Char::CodeGen(CodeContext& context){
    std::cout << "Creating char: " << _value << endl;
    return context.builder.getInt8(_value);
}
Value* Float::CodeGen(CodeContext& context){
    std::cout << "Creating Float: " << _value << endl;
    return ConstantFP::get(Type::getDoubleTy(Context), _value);

}
Value* Int::CodeGen(CodeContext& context){
    std::cout << "Generating integer: " << _value << endl;
    Value* res = context.builder.getInt64(_value);
    // std::cout <<INFO<<"The type of this int:"<<typeid(res).name()<<std::endl;
    std::cout << INFO <<"The type of the int:"<<res->getType()<<std::endl;

    return res;

}
Value* Id::CodeGen(CodeContext& context){
    std::cout << "Generating identifier reference: " << _name << endl;
    std::map<std::string , Value*>& vars = context.localvars();
    auto func = context.TailBlock()->codeblock->getParent();
    for (auto& arg : func->args()) {
        if(_name == string(arg.getName())){
            std::cout<<"Found arg:"<<_name<<std::endl;
            return &arg;
         }
    } 
    if (vars.find(_name) == vars.end() and context.global_vars.find(_name) == context.global_vars.end()) {
        std::cerr << "undeclared variable " << _name << endl;
        return NULL;
    }

    
    Value *load = NULL;
    if (vars.find(_name) != vars.end() )load = vars[_name];
    else load = context.global_vars[_name];
    auto res = context.builder.CreateLoad(load, _name.c_str());
    
    return res;
}
