#include <iostream>
#include <vector>
#include <string>
#include <llvm/Value.h>

class CodeGenContext;

class Node;
    class Root;
    class Decl;
        class FuncDecl;
            //FuncBody 直接用Stms
            class Arg;
        class VarDecl;
            class VarInit;
            
    class VarType;
        class PtrType;
        class ArrayType;

    class Stm;
		class IfStm;
		class ForStm;
		class WhileStm;
		class DoStm;
		class SwitchStm;
			class CaseStm;
		class BreakStm;
		class ContinueStm;
		class ReturnStm;
		class Block;
        class ExprStm;

    class Expr;
        class SOP;
        class BINOP;
        class ID;
        class Constant;
            class Int;
            class Float;
            class Char;
        class FuncCall;
        class ArrayCall;

typedef std::vector<Stm*> Stms;
typedef std::vector<Decl*> Decls;
typedef std::vector<Expr*> ExprList;
typedef std::vector<CaseStm*> Cases;
typedef std::vector<VarInit*> VarList;
typedef std::vector<Arg*> Args;

enum BOP {  // bi-op
    plus = 1, sub, mult, div, mod, shl, shr, lt, le, eq, ge, gt,
    ne, equ, addeq, subeq, diveq, muleq, modeq, shleq, shreq,
    and, band, or, bor
};

enum SOP {  // single operation
    splus = 1, ssub,  not, smult, sbnot
};

enum type {
    void_type = 0, char_type, float_type, int_type 
};

std::string tps[4] = {"void ", "char ", "float ", "int "}
std::string bops[26] = {
    " ","plus ","sub ","mult ","div ","mod ","shl ","shr ",
    "lt ","le ","eq ","ge ","ge ","gt ","ne ","equ ","addeq ",
    "subeq ","diveq ","muleq ","modeq ","shleq ","shreq ",
    "and ","band ","or ","bor "
}

std::string sops[6] = {
    " ","splus ", "ssub ", "not ","smult ", "sbnot "
}

class Node {
public:
    Node() {}
    virtual ~Node() {}
    virtual llvm::Value* codeGen(CodeContext& context) {}
};

class Root : public Node {
public:
    Decls* _decls;
    Root(Decls* __d): _decls(__d) {}
    ~Root() {}
    virtual llvm::Value* codeGen(CodeContext& context);
};

class Decl: public Stm {
public:
    Decl() {}
    ~Decl() {}
    virtual llvm::Value* codeGen(CodeContext& context);
    virtual std::string dec(){} 

};

class FuncDecl: public Decl {
public:
    VarType* _Type;
    std::string _FuncName;
    Args* _args;
    Stms* _fb; 
    FuncDecl(VarType* __Type, const std::string& __FuncName, Args* __args, Stms* __fb = NULL) :
			_Type(__Type), _FuncName(__FuncName), _args(__args), _fb(__fb) {}
	~FuncDecl() {}
    llvm::Value* CodeGen(CodeContext& context);
    std::string dec(){ return "Decl Func:" + tps[_Type->_type]+ _FuncName;}
};

class Arg: public Node {
public:
    VarType* _Type;
    std::string _Name;
	Arg(VarType* __Type, const std::string& __Name = "") :
		_VarType(__Type), _Name(__Name) {}
	~Arg() {}
    llvm::Value* CodeGen(CodeContext& context);
};

class VarDecl: public Decl {
public:
    VarType* _Type;
    VarList* _list;
	VarDecl(VarType* __Type, VarList* __list) :
		_Type(__Type), _VarList(__list) {}
	~VarDecl() {}
    llvm::Value* CodeGen(CodeContext& context);
    std::string dec(){ return "Decl Vars type:" + tps[_Type->_type];}
};

class VarInit: public Node {
public:
    std::string _id;
    Expr* _initvaL;

	VarInit(const std::string& __id) :
		_id(__id), _initvaL(NULL) {}
	VarInit(const std::string& __id, Expr* __initvaL) :
		_id(__id), _initvaL(__initvaL) {}
	~VarDecl() {}
    llvm::Value* CodeGen(CodeContext& context);
};

class VarType: public Node {
public:
    int _type;

	VarType(int __type): _type(__type) {}
	~VarType() {}
    llvm::Value* CodeGen(CodeContext& context);
};


class PtrType: public VarType {
public:
    bool _ptr;
	PtrType(int __type) :
		VarType(__Type), _ptr(true) {}
	~PtrType() {}
    llvm::Value* CodeGen(CodeContext& context);
};

class ArrayType: public VarType {
public:
    int _num;
    bool _array;
	ArrayType(int __type, int __num) :
		VarType(__Type), _num(__num), _array(true) {}
	~ArrayType() {}
    llvm::Value* CodeGen(CodeContext& context);
};

class Stm : public Node {
public:
    Stm() {}
    ~Stm() {}
    virtual std::string Des(){}
    virtual llvm::Value* codeGen(CodeContext& context);
};

// if-else 这里只支持一个else好了

class IfStm : public Stm{
public:
    Expr* _switch;
    Block* _ifStm;
    Block* _elseifStm;
    bool _ifelse;   // true: has else; false: no else
    IfStm(Expr* __switch, Block* __ifStm, Block* __elseifStm, bool __ifelse) : 
        _switch(__switch), _ifStm(__ifStm), _elseifStm(__elseifStm), _ifelse(__ifelse) {}
    ~IfStm() {}
    const Block* _getifStm() {return _ifStm;}
    const Block* _getelseStm() {return _elseifStm;}
    void changeIfStm(Block* __ifStm){_ifStm = __ifStm;}
    void changeElseStm(Block* _elseifStm){ _elseifStm = __elseifStm;}
    std::string Des(){return "IfStm"}

    virtual llvm::Value* codeGen(CodeContext& context);

};

class ForStm : public Stm{
public:
    Expr* _expr1, _expr2, _expr3;
    Block* _block;
    ForStm(Expr* __expr1, Expr* __expr2, Expr* __expr3, Block* __block) :
        _expr1(__expr1), _expr2(__expr2), _expr3(__expr3), _block(__block) {}
    ForStm() {}
    std::string Des(){return "ForStm"}
    virtual llvm::Value* codeGen(CodeContext& context);
};

class WhileStm : public Stm{
public:
    Expr* _expr;
    Block* _block;
    WhileStm(Expr* __expr, Block* __block) : _expr(__expr), _block(__block) {}
    ~WhileStm() {}
    std::string Des(){return "WhileStm"}
    virtual llvm::Value* codeGen(CodeContext& context);
};

class DoStm : public Stm{
public:
    Expr* _expr;
    Block* _block;
    DoStm(Expr* __expr, Block* __block) : _expr(__expr), _block(__block) {}
    DoStm() {}
    const Expr* getExpr(){ return _expr; }
    const Block* getBlock(){ return _block; }
    void changeExpr(Expr* __expr){ _expr = __expr;}
    void changeBlock(Block* __block){ _block = __block;}
    std::string Des(){return "DoStm"}
    virtual llvm::Value* codeGen(CodeContext& context);
};

class SwitchStm : public Stm{
public:
    Expr* _expr;
    Cases* _cases;
    SwitchStm(Expr* __expr, Cases* __cases): _expr(__expr), _cases(__cases) {}
    SwitchStm() {}
    const Expr* getExpr(){ return _expr; }
    const Cases* getCaseList(){ return _cases; }
    void changeExpr(Expr* __expr){ _expr = __expr;}
    void changeCaseList(Cases* __cases){ _cases = __cases;}
    std::string Des(){return "SwitchStm"}
    virtual llvm::Value* codeGen(CodeContext& context);
};

class CaseStm : public Stm{
public:
    Expr* _expr;
    Stms* _stms;
    CaseStm(Stm* __stms) : _stms(__stms) {}
    const Stms* getStms(){ return _stms;}
    void changeStmList(Stms* __stms){ _stms = __stms; }
    std::string Des(){return "CaseStm"}
    virtual llvm::Value* codeGen(CodeContext& context);
};

class BreakStm : public Stm{
public:
    BreakStm(){}
    ~BreakStm(){}
    virtual llvm::Value* codeGen(CodeContext& context);
};

class ContinueStm : public Stm{
public:
    ContinueStm(){}
    ~ContinueStm(){}
    virtual llvm::Value* codeGen(CodeContext& context);
};

class ReturnStm : public Stm{
public:
    Expr* _return;
    ReturnStm(Expr* __return): _return(__return) {}
    ~ReturnStm(){}
    virtual llvm::Value* codeGen(CodeContext& context);
};

class ExprStm : public Stm{
public:
    Expr* _expr;
    ExprStm(Expr* __expr): _expr(__expr) {}
    ~ExprStm(){}
    virtual llvm::Value* codeGen(CodeContext& context);
};

class Block : public Expr {
public:
    Stms _statements;
    Block(Stm* __s): _statements(__s) { }
    ~Block() {}
    virtual llvm::Value* codeGen(CodeContext& context);
};

class Expr : public Node {
public:
    Expr() {}
    ~Expr() {}
    virtual llvm::Value* codeGen(CodeContext& context);
};

class SOP : public Expr {
public:
    int op;
    Expr* lhs;
    SOP(Expr* lhs, int op) :
        lhs(lhs), op(op) { }
    ~SOP() {}
    virtual llvm::Value* codeGen(CodeContext& context);
};

class BINOP : public Expr {
public:
    int op;
    Expr* lhs;
    Expr* rhs;
    BINOP(Expr* lhs, int op, Expr* rhs) :
        lhs(lhs), rhs(rhs), op(op) { }
    ~BINOP() {}
    virtual llvm::Value* codeGen(CodeContext& context);
};

class ID : public Expr {
public:
    std::string _name;
    ID(const std::string& __name) : _name(__name) { }
    ~ID() {}
    virtual llvm::Value* codeGen(CodeContext& context);
}

class Constant : public Expr {
public:
    int _type;
    Constant(int __type) : type(__type) { }
    ~Constant() {}
    virtual llvm::Value* codeGen(CodeContext& context);
};

class Int : public Constant {
public:
    long long _value;
    Int(long long __value, int __type = int_type) : Constant(__type), _value(__value) { }
    ~Int() {}
    virtual llvm::Value* codeGen(CodeContext& context);
};

class Float : public Constant {
public:
    double _value;
    Float(double __value, int __type = float_type) : Constant(__type), _value(__value) { }
    ~Float() {}
    virtual llvm::Value* codeGen(CodeContext& context);
};

class Char : public Constant {
public:
    char _value;
    Char(char __value, int __type = char_type) : Constant(__type), _value(__value) { }
    ~Char() {}
    virtual llvm::Value* codeGen(CodeContext& context);
};

// 这里记得要检验一下参数数量对不对
class FuncCall : public Expr {
public:
    std::string _FuncName;
    ExprList* _arguments;
    FuncCall(std::string __FuncName, ExprList* __arguments) :
        _FuncName(__FuncName), _arguments(__arguments) { }
    ~FuncCall() {}
    virtual llvm::Value* codeGen(CodeContext& context);
};

class ArrayCall : public Expr {
public:
    std::string _id;
    Expr* _num;
    ArrayCall(const std::string& __id, Expr* __num) : 
        _id(__id), _num(__num) {}
    ~ArrayCall() {}
    virtual llvm::Value* codeGen(CodeContext& context);
};