#include "node.hpp"
#include "CodeTran.hpp"

using namespace std;
using namespace node;
using namespace llvm;
#define INFO "[INFO]: "
// LLVMContext Context;

extern node::Root* root;

void CodeContext::CreateContext(node::Root* root){
    std::cout << "Generating code...\n";
    // std::cout << this << ":"<< root << std::endl;

    /* Create the top level interpreter function to call as entry */
    vector<Type*> argTypes;
    FunctionType *ftype = FunctionType::get(Type::getVoidTy(Context), argTypes, false);
    Function* mainFunction = Function::Create(ftype, GlobalValue::InternalLinkage, "main", module);
    BasicBlock *bblock = BasicBlock::Create(Context,"entry", mainFunction, 0);
    // std::cout << "[Create BBlock]"<<std::endl;
    CodeBlock* tmp = new CodeBlock();
    tmp->codeblock = bblock;
    // std::cout << "[Ins starts]"<<std::endl;
    
    InsBlock(tmp);
    // std::cout << "[Root start]"<<std::endl;
    CodeContext &tmp_ = *this;
    // std::cout << "[Root 1]"<<std::endl;
    root->CodeGen(tmp_);
    RmTailBlock();
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
    // std::cout<<INFO<<"Into CodeGen"<<std::endl; 
    for (auto it = _decls->begin(); it != _decls->end();it++) {
        std::cout<<INFO<<"into for"<<std::endl;
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
    for (it = _args->begin(); it != _args->end();it++) {
        argtypes.push_back(typeOf(((**it)._Type)->_type));
    }
    if (argtypes.size() == 0){
        ftype_ = FunctionType::get(typeOf(_Type->_type),false);
    }
    else {
        ftype_ = FunctionType::get(typeOf(_Type->_type),argtypes,false);
    }
    Function * func = Function::Create(ftype_,GlobalValue::InternalLinkage,_FuncName.c_str(),context.module);
    BasicBlock *bblock = BasicBlock::Create(Context,"entry", func, 0);

    CodeBlock* tmp = new CodeBlock();
    tmp->codeblock = bblock;
    context.InsBlock(tmp);

    for (it = _args->begin(); it != _args->end();it++) {
        (*it)->CodeGen(context);
    }

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
        // std::cout << "Generate var:" << " " << (*it)->_id << endl;
        alloc = new AllocaInst(typ,0, (*it)->_id.c_str(), context.TailBlock()->codeblock);
        vars[(*it)->_id] = alloc;
        if ((*it)->_initvaL != NULL) {
            // std::cout << "Generating assignment for " << (*it)->_id << endl;
            // std::cout << "vars: "<<vars[(*it)->_id]<<std::endl;
            // std::cout << "tailblock: "<<context.TailBlock()<<std::endl;
            // std::cout << "tail bblock: "<<context.TailBlock()->codeblock<<std::endl;
            auto ret = ((*it)->_initvaL)->CodeGen(context);
            // std::cout << "ret val:" << ret<<std::endl;
            // std::cout << "alloc val:" << alloc<<std::endl;
            
            new StoreInst(ret, alloc, false, context.TailBlock()->codeblock);
            // std::cout << (*it)->_id << "Generated done"<<endl;
            
        }
    }
    return alloc;
}
Value* IfStm::CodeGen(CodeContext& context){
    Value* res = NULL;

    return res;
}
Value* ForStm::CodeGen(CodeContext& context){
    Value* res = NULL;

    return res;
}
Value* WhileStm::CodeGen(CodeContext& context){
    Value* res = NULL;

    return res;
    // 创建 While 语句的基本块
    // BasicBlock* loopBB = BasicBlock::Create(Context, "loop", function);

    // // 创建条件判断的基本块
    // BasicBlock* condBB = BasicBlock::Create(Context, "cond", function);

    // // 创建循环体的基本块
    // BasicBlock* bodyBB = BasicBlock::Create(Context, "body", function);

    // // 在当前基本块中插入跳转到条件判断基本块的指令
    // BranchInst::Create(condBB, currentBlock);

    // // 在条件判断基本块中插入条件判断指令
    // IRBuilder<> builder(condBB);
    // Value* condition = // 条件表达式的值
    // builder.CreateCondBr(condition, bodyBB, loopBB);

    // // 在循环体基本块中插入循环体指令
    // IRBuilder<> builder(bodyBB);
    // // 循环体指令

    // // 在循环体基本块中插入跳转到条件判断基本块的指令
    // BranchInst::Create(condBB, bodyBB);

    // // 在当前基本块中插入跳转到循环基本块的指令
    // BranchInst::Create(loopBB, currentBlock);

}
Value* DoStm::CodeGen(CodeContext& context){
    Value* res = NULL;

    return res;
}
Value* SwitchStm::CodeGen(CodeContext& context){
    Value* res = NULL;

    return res;
}
Value* CaseStm::CodeGen(CodeContext& context){
    Value* res = NULL;

    return res;
}
Value* BreakStm::CodeGen(CodeContext& context){
    Value* res = NULL;

    return res;
}
Value* ContinueStm::CodeGen(CodeContext& context){
    Value* res = NULL;

    return res;
}
Value* ReturnStm::CodeGen(CodeContext& context){
    Value* res = NULL;

    return res;
}
Value* Block::CodeGen(CodeContext& context){
    Value* last = NULL;
    Stms::const_iterator it;
    for (it = _statements->begin(); it != _statements->end();it++) {
        auto pt = *it;
        std::cout << "Generating stm " <<  std::endl;
        last = pt->CodeGen(context);
    }
    std::cout << "Genetated Block"<<std::endl;
    return last; 
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
    
    int math = 0,cmp = 0;
    auto pt = lhs;
    auto new_pt= dynamic_cast<Id*>(pt);
    switch (op)
    {
        case 1 :case 15:inst_1 = Instruction::Add ;math = 1;break;
        case 2 :case 16:inst_1 = Instruction::Sub ;math = 1;break;
        case 3 :case 18:inst_1 = Instruction::Mul ;math = 1;break;
        case 4 :case 17:inst_1 = Instruction::SDiv;math = 1;break;
        case 5 :case 19:inst_1 = Instruction::SRem;math = 1;break;
        case 6 :case 20:inst_1 = Instruction::Shl ;math = 1;break;
        case 7 :case 21:inst_1 = Instruction::AShr ;math = 1;break;
        case 8 :inst_2 = CmpInst::ICMP_ULT;cmp = 1;break;
        case 9 :inst_2 = CmpInst::ICMP_ULE;cmp = 1;break;
        case 10:inst_2 = CmpInst::ICMP_EQ; cmp = 1;break;
        case 11:inst_2 = CmpInst::ICMP_UGE;cmp = 1;break;
        case 12:inst_2 = CmpInst::ICMP_UGT;cmp = 1;break;
        case 13:inst_2 = CmpInst::ICMP_NE; cmp = 1;break;
        case 14:
            std::cout << "Creating assignment for " << std::endl;
            if (new_pt){
                
                if (context.localvars().find(new_pt->_name) == context.localvars().end()) {
                    std::cerr << "undeclared variable " << std::endl;
                    return NULL;
                }
            }
            std::cout<<INFO<<"No new_pt"<<std::endl;
            return new StoreInst(pt->CodeGen(context), context.localvars()[new_pt->_name], false, context.TailBlock()->codeblock);
        // case 22:inst = Instruction::ICMP;math = 1;break;

        case 22:inst_1 = Instruction::And; math = 1;break;
        case 23:inst_1 = Instruction::And;math = 1;break;
        case 24:inst_1 = Instruction::Or;  math = 1;break;
        case 25:inst_1 = Instruction::Or ;math = 1;break;
    }
    if (math || cmp){
        if (math){
            return  BinaryOperator::Create(inst_1, lhs->CodeGen(context),rhs->CodeGen(context), "", context.TailBlock()->codeblock);
        }
        else if (cmp){
            // return   ICmpInst(*(context.TailBlock()->codeblock),inst_2, lhs->CodeGen(context),rhs->CodeGen(context), "");
            return NULL;
        }
        
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
    return ConstantInt::get(Type::getInt8Ty(Context), _value);
}
Value* Float::CodeGen(CodeContext& context){
    std::cout << "Creating Float: " << _value << endl;
    return ConstantFP::get(Type::getDoubleTy(Context), _value);
}
Value* Int::CodeGen(CodeContext& context){
    std::cout << "Generating integer: " << _value << endl;
    return ConstantInt::get(Type::getInt64Ty(Context), _value, true);
}
Value* Id::CodeGen(CodeContext& context){
    std::cout << "Generating identifier reference: " << _name << endl;
    std::map<std::string , Value*>& vars = context.localvars();
    if (vars.find(_name) == vars.end()) {
        std::cerr << "undeclared variable " << _name << endl;
        return NULL;
    }
    return new LoadInst(vars[_name]->getType(),vars[_name], "", false, context.TailBlock()->codeblock);
}
