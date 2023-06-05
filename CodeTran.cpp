#include "node.hpp"
#include "CodeTran.hpp"

using namespace std;
using namespace node;
using namespace llvm;
#define INFO "[INFO]: "
#define INTCAST(x) context.builder.CreateIntCast(x, context.builder.getInt32Ty(), true)
// LLVMContext Context;

extern node::Root* root;

void CodeContext::CreateContext(node::Root* root){
    std::cout << "Generating code...\n";
    // std::cout << this << ":"<< root << std::endl;
    /* Create the top level interpreter function to call as entry */

    // std::cout << "[Root start]"<<std::endl;
    CodeContext &tmp_ = *this;
    // std::cout << "[Root 1]"<<std::endl;
    std::cout << this << ":"<< root << std::endl;
    root->CodeGen(tmp_);
    std::cout << "Code is generated.\n"<<std::endl;
    module->print(outs(), nullptr);

    // PassManager pm;
    // pm.add(createPrintModulePass(&outs()));
    // pm.run(*module);
}


static Type *typeOf(const VarType& type)
{
    if (type._type == 3) {
        return Type::getInt64Ty(Context);
    }
    else if (type._type == 2) {
        return Type::getDoubleTy(Context);
    }
    else if (type._type == 1) {
        return Type::getInt8Ty(Context);
    }
    
    return Type::getVoidTy(Context);
}

Value* Root::CodeGen(CodeContext& context){
    std::cout<<INFO<<"Into CodeGen"<<std::endl; 
    Value* last = NULL;
    context.cur_vars = context.global_vars;
    // std::cout<<INFO<<"Into CodeGen"<<std::endl; 
    std::cout<<INFO<<"into for"<<std::endl;
    for (auto it = _decls->begin(); it != _decls->end();it++) {
        
        auto pt = *it;
        std::cout <<INFO<<"Generating the "<<std::endl;
        last = pt->CodeGen(context);
    }
    std::cout <<INFO<<"Generated ROOT"<<std::endl;
    return last;
}
Value* FuncDecl::CodeGen(CodeContext& context){
    vector<Type*> argtypes;
    Args::const_iterator it;
    FunctionType* ftype_ = NULL;
    std::cout << "Generating function: " << _FuncName<< std::endl;

    if (context.func_table.find(_FuncName) != context.func_table.end()){
        std::cerr << "declared function " << _FuncName << endl;
        return NULL;
    }
    for (it = _args->begin(); it != _args->end();it++) {
        argtypes.push_back(typeOf(((**it)._Type)->_type));
    }
    if (argtypes.size() == 0){
        ftype_ = FunctionType::get(typeOf(_Type->_type),false);
    }
    else {
        ftype_ = FunctionType::get(typeOf(_Type->_type),argtypes,false);
    }
    std::cout<<INFO<<"Here?"<<std::endl;
    Function * func = Function::Create(ftype_,GlobalValue::InternalLinkage,_FuncName.c_str(),context.module);
    BasicBlock *bblock = BasicBlock::Create(Context,_FuncName.c_str(), func, 0);
    CodeBlock* tmp = new CodeBlock();
    tmp->codeblock = bblock;
    std::cout<<INFO<<"Here?"<<std::endl;

    context.cur_vars = tmp->local_vars;
    std::cout<<INFO<<"Here?"<<std::endl;
    context.func_table[_FuncName.c_str()] = tmp;
    std::cout<<INFO<<"Here?"<<std::endl;
    context.InsBlock(tmp);

    std::cout<<INFO<<"Here?"<<std::endl;
    if (_args!=NULL){
        std::cout<<INFO<<"not null"<<std::endl;    
        for (it = _args->begin(); it != _args->end();it++) {
            (*it)->CodeGen(context);
        }
    }
        
    std::cout<<INFO<<"Here?"<<std::endl;

    Value* last = NULL;
    Stms::const_iterator it_;
    for (it_ = _fb->begin(); it_ != _fb->end();it_++) {
        auto pt = *it_;
        std::cout << "Generating stm "<< std::endl;
        last = pt->CodeGen(context);
    }
    std::cout << "Genetated function body"<<std::endl;

    ReturnInst::Create(Context,bblock);
    context.RmTailBlock();
    std::cout << "Generated function: " << _FuncName<< std::endl;
    return func; 
}
Value* Arg::CodeGen(CodeContext& context){
    std::cout << "Generate arg:" << tps[_Type->_type]<< " " << _Name << endl;
    AllocaInst *alloc = new AllocaInst(typeOf(_Type->_type), 0,_Name.c_str(), context.TailBlock()->codeblock);
    std::map<std::string , Value*>& vars = context.localvars();
    vars[_Name] = alloc; 
    return alloc;
}
Value* VarDecl::CodeGen(CodeContext& context){
    Type * typ = typeOf(_Type->_type);
    // std::cout<<"Type:"<<_Type->_type<<std::endl;
    VarList::const_iterator it;
    Value *alloc = NULL;
    std::map<std::string , Value*>& vars = context.localvars();

    for (it = _list->begin();it != _list->end();it++){
        std::cout << "Generate var:" << " " << (*it)->_id <<" var"<< endl;
        alloc = new AllocaInst(typ,0, (*it)->_id.c_str(), context.TailBlock()->codeblock);
        vars[(*it)->_id] = alloc;
        if ((*it)->_initvaL != NULL) {
            std::cout << "Generating assignment for " << (*it)->_id <<" var"<< endl;
            // std::cout << "vars: "<<vars[(*it)->_id]<<std::endl;
            // std::cout << "tailblock: "<<context.TailBlock()<<std::endl;
            // std::cout << "tail bblock: "<<context.TailBlock()->codeblock<<std::endl;
            auto ret = ((*it)->_initvaL)->CodeGen(context);
            // std::cout << "ret val:" << ret<<std::endl;
            // std::cout << "alloc val:" << alloc<<std::endl;
            
            new StoreInst(ret, alloc, false, context.TailBlock()->codeblock);
            // std::cout << (*it)->_id << "Generated done"<<endl;
            
        }
        std::cout<<INFO<<"cur vars"<<std::endl;
        for (auto &t : vars){
            std::cout<<INFO<<t.first<<":"<<t.second<<std::endl;
        }
    }
    return alloc;
}
Value* IfStm::CodeGen(CodeContext& context){
    Value* res = NULL;
    BasicBlock *curblock = context.TailBlock()->codeblock;
    Function *func = curblock->getParent();
    context.builder.SetInsertPoint(curblock);
    BasicBlock *entry = BasicBlock::Create(Context, "entry", func);
    BasicBlock *exit_ = BasicBlock::Create(Context, "exit", func);
    
    context.builder.SetInsertPoint(entry);
    CodeBlock* tmp_ = new CodeBlock();
    tmp_->codeblock = entry;
    tmp_->local_vars = context.TailBlock()->local_vars;

    context.InsBlock(tmp_);
    BasicBlock *ifBB = (BasicBlock*)(_ifStm->CodeGen(context));
    BasicBlock *elseBB = exit_;
    if (_ifelse){
        elseBB = (BasicBlock*)_elseifStm->CodeGen(context);
    }
    
    context.builder.CreateCondBr(_switch->CodeGen(context), ifBB, elseBB);
    context.RmTailBlock();
    CodeBlock* tool = new CodeBlock();
    tool->codeblock = exit_;
    tool ->local_vars = context.TailBlock()->local_vars;
    context.InsBlock(tool);
    context.builder.SetInsertPoint(exit_);

    return res;
}
Value* ForStm::CodeGen(CodeContext& context){
    Value* res = NULL;

    BasicBlock *entry = context.TailBlock()->codeblock;
    Function *func = entry->getParent();
    BasicBlock *loop_ = (BasicBlock*)(_block->CodeGen(context));
    BasicBlock *step_ = BasicBlock::Create(Context, "step", func);
    BasicBlock *exit_ = BasicBlock::Create(Context, "exit", func);

    // 在entry块中添加跳转指令，跳转到loop块
    context.builder.SetInsertPoint(entry);
    Value* init = NULL;
    if (_expr1) init = _expr1->CodeGen(context);
    std::cout<<INFO<<"COND 1 DONE"<<std::endl;
    context.builder.CreateBr(step_);
    std::cout<<INFO<<"COND 2 DONE"<<std::endl;

    // 在loop块中添加for循环的条件分支和跳转指令
    context.builder.SetInsertPoint(loop_);
    Value *act = NULL;
    if (_expr3) _expr3->CodeGen(context);
    std::cout<<INFO<<"STEP 1 DONE"<<std::endl;

    context.builder.CreateBr(step_);
    std::cout<<INFO<<"STEP 2 DONE"<<std::endl;
    

    // 在step块中添加i++的指令，跳转到loop块
    context.builder.SetInsertPoint(step_);
    Value* cmp = NULL;
    if(_expr2)cmp = _expr2->CodeGen(context);
    std::cout<<INFO<<"CMP 1 DONE"<<std::endl;

    context.builder.CreateCondBr(cmp, loop_, exit_);
    std::cout<<INFO<<"CMP 2 DONE"<<std::endl;


    // 在exit块中添加返回指令
    CodeBlock *tool = new CodeBlock();
    tool->codeblock = exit_;
    tool ->local_vars = context.TailBlock()->local_vars;

    context.InsBlock(tool);
    context.builder.SetInsertPoint(exit_);
    return res;
}
Value* WhileStm::CodeGen(CodeContext& context){
    Value* res = NULL;
    // 创建 While 语句的基本块
    Value*init = _expr->CodeGen(context);
    BasicBlock* curblock = context.TailBlock()->codeblock;
    Function* func = curblock->getParent();

    BasicBlock *loop_ = (BasicBlock*)(_block->CodeGen(context));
    
    BasicBlock *exit_ = BasicBlock::Create(Context, "exit", func);
    

    context.builder.SetInsertPoint(curblock);
    context.builder.CreateBr(loop_);
    context.builder.SetInsertPoint(loop_);

    Value *cmp = _expr->CodeGen(context);
    context.builder.CreateCondBr(cmp, loop_, exit_);

    // 在exit块中添加返回指令
    CodeBlock *tool = new CodeBlock();
    tool->codeblock = exit_;
    
    tool ->local_vars = context.TailBlock()->local_vars;

    context.InsBlock(tool);
    context.builder.SetInsertPoint(exit_);
    // 创建条件判断的基本块
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
    BasicBlock *exit_ = BasicBlock::Create(Context, "exit", func);
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
        last = pt->CodeGen(context);
        context.builder.CreateBr(exit_);
        context.RmTailBlock();
    }

    context.RmTailBlock();
    CodeBlock *tool = new CodeBlock();
    tool->codeblock = exit_;
    tool ->local_vars = context.TailBlock()->local_vars;

    context.InsBlock(tool);
    context.builder.SetInsertPoint(exit_);

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
    BasicBlock *bblock = BasicBlock::Create(Context,"block", func, 0);
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
    BasicBlock *bblock = BasicBlock::Create(Context,"block", func, 0);
    CodeBlock* tool = new CodeBlock();
    tool->codeblock = bblock;
    tool->local_vars = context.TailBlock()->local_vars;
    context.InsBlock(tool);
    Stms::const_iterator it;
    for (it = _statements->begin(); it != _statements->end();it++) {
        auto pt = *it;
        std::cout << "Generating stm " <<  std::endl;
        std::cout << "****[The ptr]****:"<<typeid(pt).name()<< std::endl;
        last = pt->CodeGen(context);
    }

    context.RmTailBlock();
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
    int math = 0,cmp = 0;
    auto pt = rhs;
    auto new_pt= dynamic_cast<Id*>(lhs);
    std::cout<<INFO<<"op:"<<op<<std::endl;
    switch (op)
    {
        case 1 :case 15:return context.builder.CreateAdd( lhs->CodeGen(context),rhs->CodeGen(context),(string("add_") + to_string(context.opnums++)).c_str());
        case 2 :case 16:return context.builder.CreateSub( lhs->CodeGen(context),rhs->CodeGen(context),(string("sub_") + to_string(context.opnums++)).c_str());
        case 3 :case 18:return context.builder.CreateMul( lhs->CodeGen(context),rhs->CodeGen(context),(string("mul_") + to_string(context.opnums++)).c_str());
        case 4 :case 17:return context.builder.CreateSDiv(lhs->CodeGen(context),rhs->CodeGen(context),(string("div_") + to_string(context.opnums++)).c_str());
        case 5 :case 19:return context.builder.CreateSRem(lhs->CodeGen(context),rhs->CodeGen(context),(string("mod_") + to_string(context.opnums++)).c_str());
        case 6 :case 20:return context.builder.CreateShl( lhs->CodeGen(context),rhs->CodeGen(context),(string("shl_") + to_string(context.opnums++)).c_str());
        case 7 :case 21:return context.builder.CreateAShr(lhs->CodeGen(context),rhs->CodeGen(context),(string("shr_") + to_string(context.opnums++)).c_str());
        case 8 :
            std::cout<<INFO<<"case 8"<<std::endl;
            op1 = INTCAST(lhs->CodeGen(context));
            op2 = INTCAST(rhs->CodeGen(context));
            std::cout<<INFO<<"get done!"<<std::endl;
            std::cout<<INFO<<"op1 type:"<<op1->getType()<<std::endl;
            std::cout<<INFO<<"op2 type:"<<op2->getType()<<std::endl;
            return context.builder.CreateICmpULT(op1,op2,"lt");
            // return CmpInst::Create(Instruction::ICmp, CmpInst::ICMP_ULT, op1, op2);

        case 9 :return context.builder.CreateICmpULE(INTCAST(lhs->CodeGen(context)),INTCAST(rhs->CodeGen(context)),(string("le_") + to_string(context.opnums++)).c_str());
        case 10:return context.builder.CreateICmpEQ (INTCAST(lhs->CodeGen(context)),INTCAST(rhs->CodeGen(context)),(string("eq_") + to_string(context.opnums++)).c_str());
        case 11:return context.builder.CreateICmpUGE(INTCAST(lhs->CodeGen(context)),INTCAST(rhs->CodeGen(context)),(string("ge_") + to_string(context.opnums++)).c_str());
        case 12:return context.builder.CreateICmpUGT(INTCAST(lhs->CodeGen(context)),INTCAST(rhs->CodeGen(context)),(string("gt_") + to_string(context.opnums++)).c_str());
        case 13:return context.builder.CreateICmpNE (INTCAST(lhs->CodeGen(context)),INTCAST(rhs->CodeGen(context)),(string("ne_") + to_string(context.opnums++)).c_str());
        case 14:
            
            std::cout << "Creating assignment for " << new_pt->_name<<" var"<<std::endl;
            std::cout<<INFO<<"cur vars"<<std::endl;
            for (auto &t : vars){
                std::cout<<INFO<<t.first<<":"<<t.second<<std::endl;
            }
            
            if (vars.find(new_pt->_name) == vars.end()) {
                std::cerr << "undeclared variable " << std::endl;
                return NULL;
            }
            
            std::cout<<INFO<<"No new_pt"<<std::endl;
            return new StoreInst(pt->CodeGen(context), context.localvars()[new_pt->_name], false, context.TailBlock()->codeblock);
        // case 22:inst = Instruction::ICMP;math = 1;break;

        case 22:return context.builder.CreateAnd(INTCAST(lhs->CodeGen(context)),INTCAST(rhs->CodeGen(context)),(string("and_") + to_string(context.opnums++)).c_str());
        case 23:return context.builder.CreateAnd(INTCAST(lhs->CodeGen(context)),INTCAST(rhs->CodeGen(context)),(string("and_") + to_string(context.opnums++)).c_str());
        case 24:return context.builder.CreateOr( INTCAST(lhs->CodeGen(context)),INTCAST(rhs->CodeGen(context)),(string( "or_") + to_string(context.opnums++)).c_str());
        case 25:return context.builder.CreateOr( INTCAST(lhs->CodeGen(context)),INTCAST(rhs->CodeGen(context)),(string( "or_") + to_string(context.opnums++)).c_str());
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
    std::cout <<INFO<<"The type of this int:"<<typeid(res).name()<<std::endl;
    // std::cout << INFO <<"The type of the int:"<<res->getType()<<std::endl;

    return res;

}
Value* Id::CodeGen(CodeContext& context){
    std::cout << "Generating identifier reference: " << _name << endl;
    std::map<std::string , Value*>& vars = context.localvars();
    if (vars.find(_name) == vars.end() and context.global_vars.find(_name) == context.global_vars.end()) {
        std::cerr << "undeclared variable " << _name << endl;
        return NULL;
    }

    LoadInst* load = NULL;
    if (vars.find(_name) != vars.end() )load = context.builder.CreateLoad(vars[_name]);
    else load = context.builder.CreateLoad(context.global_vars[_name]);
    auto res = load->getPointerOperand ();
    llvm::Type *Ty = res->getType();
    llvm::Constant *C = NULL;
    if (Ty->isIntegerTy()) {
        llvm::ConstantInt *CI = llvm::dyn_cast<llvm::ConstantInt>(res);
        if (CI) {
            // V是常量整数类型
            // 将其转为llvm::Constant对象
            std::cout<<INFO<<"It's CI"<<std::endl;

            C = llvm::ConstantInt::get(res->getType(), CI->getValue());

        }
    } 
    else if (Ty->isFloatingPointTy()) {
    // V是浮点数类型
        llvm::ConstantFP *CF = llvm::dyn_cast<llvm::ConstantFP>(res);
        if (CF) {
            // V是常量浮点数类型
            // 将其转为llvm::Constant对象
            std::cout<<INFO<<"It's CF"<<std::endl;
            
            C = llvm::ConstantFP::get(CF->getType(), CF->getValueAPF());
        }
    }
    else {
        std::cout <<INFO<<"The type of this load:"<<res->getType()->getTypeID()<<std::endl;
        return res;
    }
    std::cout <<INFO<<"The type of this load:"<<C->getType()->getTypeID()<<std::endl;
    // std::cout << INFO <<"The type of the int:"<<C->getType()<<std::endl;
    return C;
}
