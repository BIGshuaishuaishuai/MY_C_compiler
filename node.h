#include <iostream>
#include <vector>
#include <llvm/Value.h>

class CodeGenContext;

class NVariableDeclaration;

class Node;
    class Root;
    class Decl;
    class FuncDecl;
        class FuncBody;
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

    class Expr;
        class SOP;
        class BINOP;
        class Constant;
            class Int;
            class Float;
            class Char;
        

typedef std::vector<Stm*> Stms;
typedef std::vector<Expr*> ExpressionList;
typedef std::vector<CaseStm*> Cases;
typedef std::vector<VarInit*> VarList;
typedef std::vector<Arg*> Args;

// yjj那份expr那些nodes代码重复率太高了，这里用一个OP做参数来替代了
enum BOP {  // bi-op
    plus = 1, sub, mult, div, mod, shl, shr, lt, le, eq, ge, gt,
    ne, eq, addeq, subeq, diveq, muleq, modeq, shleq, shreq,
    and, band, or, bor
};

enum SOP {  // single operation
    splus = 1, ssub,  not, smult, sbnot
};

enum type {
    void_type = 0, char_type, float_type, int_type 
};

class Node {
public:
    Node() {}
    virtual ~Node() {}
    virtual llvm::Value* codeGen(CodeGenContext& context) {}
};

typedef vector<Decl*> Decls;

class Root : public Node {
public:
    Decls* _decls;
    Root(Decls* __d): _decls(__d) {}
    ~Root() {}
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class Decl: public Stm {
public:
    Decl() {}
    ~Decl() {}
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class FuncDecl: poublic

class Stm : public Node {
public:
    Stm() {}
    ~Stm() {}
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class Expr : public Node {
public:
    Expr() {}
    ~Expr() {}
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class Constant : public Expr {
public:
    int _type;
    Constant* _val;
    Constant(int __type) : type(__type) { }
    ~Constant() {}
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class Int : public Constant {
public:
    long long _value;
    Int(long long __value, int __type = int_type) : Constant(__type), _value(__value) { }
    ~Int() {}
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class Float : public Constant {
public:
    double _value;
    Float(double __value, int __type = float_type) : Constant(__type), _value(__value) { }
    ~Float() {}
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class Char : public Constant {
public:
    char _value;
    Char(char __value, int __type = float_type) : Constant(__type), _value(__value) { }
    ~Char() {}
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class ID : public Expr {
public:
    std::string _name;
    ID(const std::string& __name) : _name(__name) { }
    ~ID() {}
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NMethodCall : public Expr {
public:
    ID* _FuncName;
    Args _arguments;
    NMethodCall(const ID& id, Args& arguments) :
        ID(id), Args(arguments) { }
    NMethodCall(const ID& id) : id(id) { }
    ~NMethodCall() {}
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class BINOP : public Expr {
public:
    int op;
    Expr* lhs;
    Expr* rhs;
    BINOP(Expr* lhs, int op, Expr* rhs) :
        lhs(lhs), rhs(rhs), op(op) { }
    ~BINOP() {}
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class SOP : public Expr {
public:
    int op;
    Expr* lhs;
    SOP(Expr* lhs, int op) :
        lhs(lhs), op(op) { }
    ~SOP() {}
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class Block : public Expr {
public:
    Stms statements;
    Block(Stm* s):  { }
    ~Block() {}
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class ExprStatement : public Stm {
public:
    Expr& expression;
    ExprStatement(Expr& expression) : 
        expression(expression) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NVariableDeclaration : public Stm {
public:
    const NIdentifier& type;
    NIdentifier& id;
    Expr *assignmentExpr;
    NVariableDeclaration(const NIdentifier& type, NIdentifier& id) :
        type(type), id(id) { }
    NVariableDeclaration(const NIdentifier& type, NIdentifier& id, Expr *assignmentExpr) :
        type(type), id(id), assignmentExpr(assignmentExpr) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NFunctionDeclaration : public Stm {
public:
    const NIdentifier& type;
    const NIdentifier& id;
    VariableList arguments;
    NBlock& block;
    NFunctionDeclaration(const NIdentifier& type, const NIdentifier& id, 
            const VariableList& arguments, NBlock& block) :
        type(type), id(id), arguments(arguments), block(block) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};