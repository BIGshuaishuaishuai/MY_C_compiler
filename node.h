#include <iostream>
#include <vector>
#include <llvm/Value.h>

class CodeGenContext;
class Stm;
class Expr;
class NVariableDeclaration;

typedef std::vector<Stm*> StatementList;
typedef std::vector<Expr*> ExpressionList;
typedef std::vector<NVariableDeclaration*> VariableList;

// yjj那份expr那些nodes代码重复率太高了，这里用一个OP做参数来替代了
enum BOP {  // bi-op
    plus = 1, sub, mult, div, mod, shl, shr, lt, le, eq, ge, gt,
    ne, eq, addeq, subeq, diveq, muleq, modeq, shleq, shreq,
    and, band, or, bor
};

enum SOP {  // single operation
    splus = 1, ssub, not, smult, sbnot
};

enum type {
    void_type = 0, char_type, float_type, int_type 
};

class Node {
public:
    Node() {}
    virtual ~Node() {}
    virtual llvm::Value* codeGen(CodeGenContext& context) { }
};

typedef vector<Decl*> Decls;

class Root : public Node {
public:
    Decls _decls;
    Root() {}
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class Decl: public Stm {
    
};

class Expr : public Node {
};

class Stm : public Node {
};

class Constant : public Expr {
public:
    int _type;
    Constant* _val;
    Constant(int __type) : type(__type) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class Int : public Constant {
public:
    long long _value;
    Int(long long __value, int __type = int_type) : Constant(__type), _value(__value) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class Float : public Constant {
public:
    double _value;
    Float(double __value, int __type = float_type) : Constant(__type), _value(__value) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class Char : public Constant {
public:
    char _value;
    Char(char __value, int __type = float_type) : Constant(__type), _value(__value) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class ID : public Expr {
public:
    std::string name;
    NIdentifier(const std::string& name) : name(name) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NMethodCall : public Expr {
public:
    const NIdentifier& id;
    ExpressionList arguments;
    NMethodCall(const NIdentifier& id, ExpressionList& arguments) :
        id(id), arguments(arguments) { }
    NMethodCall(const NIdentifier& id) : id(id) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class BINOP : public Expr {
public:
    int op;
    Expr& lhs;
    Expr& rhs;
    BINOP(Expr& lhs, int op, Expr& rhs) :
        lhs(lhs), rhs(rhs), op(op) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class SOP : public Expr {
public:
    int op;
    Expr& lhs;
    SOP(Expr& lhs, int op) :
        lhs(lhs), op(op) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NAssignment : public Expr {
public:
    NIdentifier& lhs;
    Expr& rhs;
    NAssignment(NIdentifier& lhs, Expr& rhs) : 
        lhs(lhs), rhs(rhs) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NBlock : public Expr {
public:
    StatementList statements;
    NBlock() { }
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