#include "node.hpp"
#include "CodeTran.hpp"

using namespace std;

#define INFO "[INFO]: "

auto DynStm(Stm* p){
    IfStm* p_0 = dynamic_cast<IfStm*>(p);
    ForStm* p_1 = dynamic_cast<ForStm*>(p);
    WhileStm* p_2 = dynamic_cast<WhileStm*>(p);
    DoStm* p_3 = dynamic_cast<DoStm*>(p);
    CaseStm* p_4 = dynamic_cast<CaseStm*>(p);
    SwitchStm* p_5 = dynamic_cast<SwitchStm*>(p);
    
    BreakStm* p_6 = dynamic_cast<BreakStm*>(p);
    ContinueStm* p_7 = dynamic_cast<ContinueStm*>(p);
    ReturnStm* p_8 = dynamic_cast<ReturnStm*>(p);
    Block*p_9 = dynamic_cast<Block*>(p);
    ExprStm*p_10 = dynamic_cast<ExprStm*>(p);

    if (p_0) return p_0;
    else if(p_1) return p_1;
    else if(p_2) return p_2;
    else if(p_3) return p_3;
    else if(p_4) return p_4;
    else if(p_5) return p_5;
    else if(p_6) return p_6;
    else if(p_7) return p_7;
    else if(p_8) return p_8;
    else if(p_9) return p_9;
    else if(p_10) return p_10;
    else return p;
    
}
auto DynDecl(Decl* p){
    FuncDecl* p_0 = dynamic_cast<FuncDecl*>(p); 
    VarDecl* p_1 = dynamic_cast<VarDecl*>(p);

    if (p_0) return p_0;
    else if (p_1) return p_1;
    else return p;
}
auto DynExpr(Expr* p){
    SOP* p_0 = dynamic_cast<SOP*>(p);
    BINOP* p_1 = dynamic_cast<BINOP*>(p);
    ID* p_2 = dynamic_cast<ID*>(p);
    Int* p_3 = dynamic_cast<Int*>(p);
    Float* p_4 = dynamic_cast<Float*>(p);
    Char* p_5 = dynamic_cast<Char*>(p);
    Constant* p_6 = dynamic_cast<Constant*>(p);
    FuncCall* p_7 = dynamic_cast<FuncCall*>(p);
    ArrayCall*p_8 = dynamic_cast<ArrayCall*>(p);
    if (p_0) return p_0;
    else if(p_1) return p_1;
    else if(p_2) return p_2;
    else if(p_3) return p_3;
    else if(p_4) return p_4;
    else if(p_5) return p_5;
    else if(p_6) return p_6;
    else if(p_7) return p_7;
    else if(p_8) return p_8;
    else return p;

}
// auto DynCase(Stm* p){

// }
// auto DynVarInit(Stm* p){

// }
void CodeContext::CreateContext(Root* root){
    std::cout << "Generating code...\n";
  
    /* Create the top level interpreter function to call as entry */
    vector<const Type*> argTypes;
    FunctionType *ftype = FunctionType::get(Type::VoidTy, argTypes, false);
    mainFunction = Function::Create(ftype, GlobalValue::InternalLinkage, "main", module);
    BasicBlock *bblock = BasicBlock::Create("entry", mainFunction, 0);
    
    CodeBlock* tmp = new CodeBlock();
    tmp->codeblock = bblock;
    InsBlock(tmp);
    root.codeGen(*this);
    RmTailBlock();

    std::cout << "Code is generated.\n";
    PassManager pm;
    pm.add(createPrintModulePass(&outs()));
    pm.run(*module);
}

GenericValue CodeContext::runCode() {
    std::cout << "Running code...\n";
    ExistingModuleProvider *mp = new ExistingModuleProvider(module);
    ExecutionEngine *ee = ExecutionEngine::create(mp, false);
    vector<genericvalue> noargs;
    GenericValue v = ee->runFunction(mainFunction, noargs);
    std::cout << "Code was run.\n";
    return v;
}

static const Type *typeOf(const VarType& type)
{
    if (type._type == 3) {
        return Type::Int64Ty;
    }
    else if (type._type == 2) {
        return Type::FloatTy;
    }
    else if (type._type == 1) {
        return Type::Int8Ty;
    }
    
    return Type::VoidTy;
}

Value* Root::CodeGen(CodeContext& context){
    Value* final = NULL;
    for (auto it = _decls.begin(); it != _decls.end();it++) {
        auto pt = DynDecl(*it);
        std::cout <<INFO<<"Generating the "<<pt->dec();
        last = pt->CodeGen(context);
    }
    std::cout <<INFO<<"Generated ROOT"<<std::endl;
    return last;
}
Value* FuncDecl::CodeGen(CodeContext& context){
    vector<const Type*> argtypes;
    Args::const_iterator it;

    for (it = _args.begin(); it != _args.end();it++) {
        argtypes.push_back(typeOf(((**it)._Type->)_type));
    }
    FuncType* ftype = FuncType::get(typeOf(_Type->_type),argtypes,false);
    Function * func = Function::Create(ftype,GlobalValue::InternalLinkage,_FuncName.c_str(),context.module);
    BasicBlock *bblock = BasicBlock::Create("entry", func, 0);

    CodeBlock* tmp = new CodeBlock()
    tmp->block = bblock;
    context.InsBlock(tmp);

    for (it = _args.begin(); it != _args.end();it++) {
        (*it)->CodeGen(context);
    }

    Value* last = NULL;
    Stms::const_iterator it;
    for (it = Stms::begin(); it != Stms::end();it++) {
        auto pt = DynStm(*it);
        std::cout << "Generating stm " << it->Des()<< std::endl;
        last = pt->CodeGen(context);
    }
    std::cout << "Genetated function body"<<std::endl;

    ReturnInst::Create(bblock);
    context.RmTailBlock();
    std::cout << "Generated function: " << _FuncName<< std::endl;
    return func; 
}
Value* Arg::CodeGen(CodeContext& context){
    std::cout << "Generate arg:" << tps[_Type->_type]<< " " << _Name << endl;
    AllocaInst *alloc = new AllocaInst(typeOf(_Type->_type), _Name.c_str(), context.TailBlock()->codeblock);
    std::map<std::string , Value*>& vars = context.localvars();
    vars[id.name] = alloc;
    return alloc;
}
Value* VarDecl::CodeGen(CodeContext& context){
    auto typ = typeOf(_Type->_type);
    VarList::const_iterator it;
    AllocaInst *alloc = NULL;
    std::map<std::string , Value*>& vars = context.localvars();

    for (it = _list.begin();it != _list.end();it++){
        std::cout << "Generate var:" << " " << (*it)->_id << endl;
        alloc = new AllocaInst(typ, (*it)->_id, context.TailBlock()->codeblock);
        vars[id.name] = alloc;
        if ((*it)->_initvaL != NULL) {
            std::cout << "Generating assignment for " << (*it)->_id << endl;
            StoreInst(((*it)->_initvaL)->codeGen(context), vars[pt->_name], false, context.TailBlock()->codeblock);
        }
    }
    return alloc;
}


Value* IfStm::CodeGen(CodeContext& context){

}
Value* ForStm::CodeGen(CodeContext& context){

}

Value* WhileStm::CodeGen(CodeContext& context){
    // 创建 While 语句的基本块
    BasicBlock* loopBB = BasicBlock::Create(Context, "loop", function);

    // 创建条件判断的基本块
    BasicBlock* condBB = BasicBlock::Create(Context, "cond", function);

    // 创建循环体的基本块
    BasicBlock* bodyBB = BasicBlock::Create(Context, "body", function);

    // 在当前基本块中插入跳转到条件判断基本块的指令
    BranchInst::Create(condBB, currentBlock);

    // 在条件判断基本块中插入条件判断指令
    IRBuilder<> builder(condBB);
    Value* condition = // 条件表达式的值
    builder.CreateCondBr(condition, bodyBB, loopBB);

    // 在循环体基本块中插入循环体指令
    IRBuilder<> builder(bodyBB);
    // 循环体指令

    // 在循环体基本块中插入跳转到条件判断基本块的指令
    BranchInst::Create(condBB, bodyBB);

    // 在当前基本块中插入跳转到循环基本块的指令
    BranchInst::Create(loopBB, currentBlock);

}

Value* DoStm::CodeGen(CodeContext& context){

}

Value* SwitchStm::CodeGen(CodeContext& context){

}

Value* CaseStm::CodeGen(CodeContext& context){

}

Value* BreakStm::CodeGen(CodeContext& context){

}
Value* ContinueStm::CodeGen(CodeContext& context){

}

Value* ReturnStm::CodeGen(CodeContext& context){

}

Value* Block::CodeGen(CodeContext& context){
    Value* last = NULL;
    Stms::const_iterator it;
    for (it = Stms::begin(); it != Stms::end();it++) {
        auto pt = DynStm(*it);
        std::cout << "Generating stm " << it->Des()<< std::endl;
        last = pt->CodeGen(context);
    }
    std::cout << "Genetated Block"<<std::endl;
    return last; 
}
Value* SOP::CodeGen(CodeContext& context){
    std::cout << "Creating single operation " << bops[op] << endl;
    auto inst;
    int mode = 0;
    switch(op){
        case 1:return lhs->CodeGen(context);
        case 2:inst = Instruction::Sub ;mode = 1;break;
        case 3:inst = Instruction::
        // case 4:return 
        case 5:return BinaryOperator::CreateNot(lhs->CodeGen(context), "");
        default:
            std::errc<<INFO<<"wrong"<<std::endl;
            break;
    }
    if (mode == 1){
        return  BinaryOperator::Create(inst,ConstantInt::get(Type::Int64Ty, 0, true);, lhs.codeGen(context), "", context.TailBlock()->codeblock);
    }
    

}
Value* BINOP::CodeGen(CodeContext& context){
    std::cout << "Creating binary operation " << bops[op] << endl;
    auto inst;
    int math = 0,cmp = 0;

    switch (op)
    {
        case 1 :case 15:inst = Instruction::Add ;math = 1;break;
        case 2 :case 16:inst = Instruction::Sub ;math = 1;break;
        case 3 :case 18:inst = Instruction::Mul ;math = 1;break;
        case 4 :case 17:inst = Instruction::SDiv;math = 1;break;
        case 5 :case 19:inst = Instruction::SRem;math = 1;break;
        case 6 :case 20:inst = Instruction::Shl ;math = 1;break;
        case 7 :case 21:inst = Instruction::Shr ;math = 1;break;
        case 8 :inst = CmpInst::ICMP_ULT;cmp = 1;break;
        case 9 :inst = CmpInst::ICMP_ULE;cmp = 1;break;
        case 10:inst = CmpInst::ICMP_EQ; cmp = 1;break;
        case 11:inst = CmpInst::ICMP_UGE;cmp = 1;break;
        case 12:inst = CmpInst::ICMP_UGT;cmp = 1;break;
        case 13:inst = CmpInst::ICMP_NE; cmp = 1;break;
        case 14:
            std::cout << "Creating assignment for " << lhs->_name << std::endl;
            auto pt = DynExpr(lhs) 
            if (context.localvars().find(pt->_name) == context.locals().end()) {
                std::cerr << "undeclared variable " << pt->_name << std::endl;
                return NULL;
            }
            return new StoreInst(pt->codeGen(context), context.localvars()[pt->_name], false, context.TailBlock()->codeblock);
        // case 22:inst = Instruction::ICMP;math = 1;break;

        case 22:inst = Instruction::And; math = 1;break;
        case 23:inst = Instruction::AndSaturate;math = 1;break;
        case 24:inst = Instruction::Or;  math = 1;break;
        case 25:inst = Instruction::OrSaturate ;math = 1;break;
    }
    if (math || cmp){
        return  BinaryOperator::Create(inst, lhs.codeGen(context),rhs.codeGen(context), "", context.TailBlock()->codeblock);
    }
}
Value* FuncCall::CodeGen(CodeContext& context){
    Function *func = context.module->getFunction(_FuncName.c_str());
    if (function == NULL) {
        std::cerr << "no such function " << _FuncName << std::endl;
    }
    std::vector<Value *> args;
    ExprList::const_iterator it;
    for (it = arguments.begin(); it != arguments.end(); it++) {
        auto tp = DynExpr(*it);
        std::cout <<"Generate arg "<<std::endl;
        args.push_back(tp->CodeGen(context));
    }
    CallInst *call = CallInst::Create(func, args.begin(), args.end(), "", context.currentBlock());
    std::cout << "Generated function call: " << id.name << endl;
    return call;
}
Value* ArrayCall::CodeGen(CodeContext& context){

}
Value* Char::CodeGen(CodeContext& context){
    std::cout << "Creating char: " << _value << endl;
    return ConstantInt::get(Type::Int8Ty, value);
}
Value* Float::CodeGen(CodeContext& context){
    std::cout << "Creating Float: " << _value << endl;
    return ConstantFP::get(Type::FP64Ty, _value);
}
Value* Int::CodeGen(CodeContext& context){
    std::cout << "Generating integer: " << _value << endl;
    return ConstantInt::get(Type::Int64Ty, _value, true);
}
Value* ID::CodeGen(CodeContext& context){
    std::cout << "Generating identifier reference: " << _name << endl;
    std::map<std::string , Value*>& vars = context.localvars();
    if (vars.find(_name) == vars.end()) {
        std::cerr << "undeclared variable " << _name << endl;
        return NULL;
    }
    return new LoadInst(vars[_name], "", false, context.TailBlock()->codeblock);
}
