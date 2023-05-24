#include <iostream>
#include <vector>
#include <llvm/Value.h>
#include "debug.h"

class CodeGenContext;
class NStatement;
class NExpression;
class NVariableDeclaration;

typedef std::vector<Declaration*> Decls;
typedef std::vector<VarInit*> VarList;
typedef std::vector<Case*> CaseList;
typedef std::vector<Stmt*>StmtList; 
typedef std::vector<Arg*> ArgList;
typedef std::vector<Expr*> ExprList;

enum Type {
    IND,CAHR,FLOAT,VOID 
};

enum Op{
    PLUS,SUB ,MULT,DIV ,MOD ,SHL ,SHR ,LT  ,LE  ,EQ  ,
    GE  ,GT  ,NE  ,EQ  ,ADDE,SUBE,DIVE,MULE,MODE,SHLE,
    SHRE,AND ,BAND,OR  ,BOR ,pr  ,DOT ,ARROW
};

enum ValT{
    int_,char_,float_
}

class Node {
private:
    void* l_child;
    void* r_child;
public:
    Node() {}
    virtual ~Node() {}
    virtual llvm::Value* codeGen(CodeGenContext& context) { }
};

class Program : public Node {
private:
    Decls decls;
public:
    Program(Decls& decls) : decls(decls){}
    const Decls& getDecls(){ return self.decls;}
    void changeDecls(Decls& decls){ self.decls = decl;}
    virtual llvm::Value* codeGen(CodeGenContext& context){ }
};

class Declaration : public Node {
private:
    VarType vartype;
public:
    Declaration(VarType& vartype) : vartype(vartype){}
    const VarType& getVarType(){ return self.vartype;}
    void changeType(VarType& vartype){ self.vartype = vartype;}
    virtual llvm::Value* codeGen(CodeGenContext& context){ }
};
class Block : public Node {
private:
    StmtList stmtlist;
public:
    Block(StmtList& stmtlist) : stmtlist(stmtlist){}
    const StmtList& getStmtList(){ return stmtlist;}
    void changeStmtList(StmtList& stmtlist){self.stmtlist = stmtlist;}
    virtual llvm::Value* codeGen(CodeGenContext& context){ }
};

class VarDecl : public Declaration {
private:
    VarList varlist;
public:
    VarDecl(VarList& varlist) : varlist(varlist) {}
    const VarList& getVarList(){ return varlist;}
    void changeVarList(VarList& varlist){ self.varlist = varlist;}
    virtual llvm::Value* codeGen(CodeGenContext& context){ }
};

class FuncDecl : public Declaration {
private:
    ArgList arglist;
    FuncBody func;
public;
    FuncDecl(ArgList& arglist, FuncBody& func): func(func),arglist(arglist) {}
    const ArgList& getArgList() { return arglist;}
    const FuncBody& getFuncBody() { return func; }
    void changeArgList(ArgList& arglist){ self.arglist = arglist;}
    void changeFuncBody(FuncBody& func){ self.func = func; }
    virtual llvm::Value* codeGen(CodeGenContext& context){ }
};

class FuncBody:public Block {

};

class VarDecl : public Declaration {
private:
    VarList varlist;
public:
    VarDecl(VarList& varlist) : varlist(varlist) {}
    const VarList& getVarList(){ return varlist;}
    void changeVarList(VarList& vatlist) {self.varlist = vatlist;}
    virtual llvm::Value* codeGen(CodeGenContext& context){ }
};

class VarType : public Node{
private:
    Type type;
public:
    VarType(Type type) : type(type) {}
    const Type& getType(){ return type;}
    void changeType(Type type){ type = type; }
    virtual llvm::Value* codeGen(CodeGenContext& context){ }
};

class Stmt : public Node {
private:
    Expr expr;
public:
    Stmt(Expr expr) : expr(expr) {}
    const Expr& getExpr(){ return expr;}
    void changeExpr(Expr expr){ expr = expr; }
    virtual llvm::Value* codeGen(CodeGenContext& context){ }
};

class IfStmt : public Stmt{
private:
    Stmt ifstmt;
    Stmt elseifstmt;
    int ifelse;
public:
    IfStmt(Stmt ifstmt,Stmt elseifstmt, int ifelse) : ifstmt(ifstmt), elseifstmt(elseifstmt), ifelse(ifelse) {}
    const Stmt& getifStmt() {return ifstmt;}
    const Stmt& getelseStmt() {return elseifstmt;}
    void changeIfStmt(Stmt& ifstmt){ifstmt = ifstmt;}
    void changeElseStmt(Stmt& elseifstmt){ elseifstmt = elseifstmt;}
    virtual llvm::Value* codeGen(CodeGenContext& context){ }

};

class ForStmt : public Stmt{
private:
    Expr expr;
    Block block;
public:
    ForStmt(Expr expr, Block block) : expr(expr), block(block) {}
    const Expr& getExpr(){ return expr; }
    const Block& getBlock(){ return block; }
    void changeExpr(Expr& expr){ expr = expr;}
    void changeBlock(Block& block){ block = block;}
    virtual llvm::Value* codeGen(CodeGenContext& context){ }
};

class WhileStmt : public Stmt{
private:
    Expr expr;
    Block block;
public:
    WhileStmt(Expr& expr, Block& block) : expr(expr), block(block) {}
    const Expr& getExpr(){ return expr; }
    const Block& getBlock(){ return block; }
    void changeExpr(Expr& expr){ expr = expr;}
    void changeBlock(Block& block){ block = block;}
    virtual llvm::Value* codeGen(CodeGenContext& context){ }
};

class DoStmt : public Stmt{
private:
    Expr expr;
    Block block;
public:
    DoStmt(Expr& expr, Block& block) : expr(expr), block(block) {}
    const Expr& getExpr(){ return expr; }
    const Block& getBlock(){ return block; }
    void changeExpr(Expr& expr){ expr = expr;}
    void changeBlock(Block& block){ block = block;}
    virtual llvm::Value* codeGen(CodeGenContext& context){ }
};
class SwitchStmt : public Stmt{
private:
    Expr expr;
    CaseList cases;
public:
    SwitchStmt(Expr& expr, CaseList& cases): expr(expr), cases(cases) {}
    const Expr& getExpr(){ return expr; }
    const CaseList& getCaseList(){ return cases; }
    void changeExpr(Expr& expr){ expr = expr;}
    void changeCaseList(CaseList& cases){ cases = cases;}
    virtual llvm::Value* codeGen(CodeGenContext& context){ }
};

class CaseStmt : public Stmt{
private:
    StmtList stmts;
public:
    CaseStmt(StmtList stmts) : stmts(stmts) {}
    const StmtList& getStmts(){ return stmts;}
    void changeStmtList(StmtList& stmts){ stmts = stmts; }
    virtual llvm::Value* codeGen(CodeGenContext& context){ }
};

class BreakStmt : public Stmt{
private:
    
};

class ContinueStmt : public Stmt{

};

class ReturnStmt : public Stmt{

};


class Expr : public Node{
private:
    Expr& l_child;
    Expr& r_child;
    Op op;
public:
    Expr(Expr& l_child, Expr& r_child, Op op): l_child(l_child), r_child(r_child), op(op) {}
    const Expr& getLChild(){ return l_child;}
    const Expr& getRChild(){ return r_child;}
    void changeLChild(Expr& l_child){l_child = l_child;}
    void changeRChild(Expr& r_child){r_child = r_child;}
    virtual llvm::Value* codeGen(CodeGenContext& context){ }

};

union Val{
        char cval;
        int ival;
        double dval;
    };

class Constant : public Node{
private:
    Val val;
    ValT valt;
public:
    Constant (Val val,ValT valt) : val(val), valt(valt) {}
    const Val& getVal() {return val}
    const ValT& getValT() {return valt;}
    void changeVal(const Val& val) { val = val; }
    void changeValT(const ValT& valt) { valt = valt;}
    virtual llvm::Value* codeGen(CodeGenContext& context){ }

};