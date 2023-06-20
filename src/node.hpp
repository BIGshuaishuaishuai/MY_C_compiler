#ifndef __NODE_HPP__
#define __NODE_HPP__
#include <iostream>
#include <vector>
#include <string>
#include "llvm/IR/Value.h"

class CodeContext;
namespace node{
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
                class Id;
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
        plus_ = 1, sub_, mult_, div_, mod_, shl_, shr_, lt_, le_, eq_, ge_, gt_,
        ne_, equ_, addeq_, subeq_, diveq_, muleq_, modeq_, shleq_, shreq_,
        and_, band_, or_, bor_
    };

    enum SOP_ {  // single operation
        splus_ = 1, ssub_,  not_, smult_, sbnot_
    };

    enum type {
        void_type = 0, char_type, float_type, int_type 
    };

    static std::string tps[4] = {"void ", "char ", "float ", "int "};
    static std::string bops[30] = {
        " ","plus ","sub ","mult ","div ","mod ","shl ","shr ",
        "lt ","le ","eq ","ge ","ge ","gt ","ne ","equ ","addeq ",
        "subeq ","diveq ","muleq ","modeq ","shleq ","shreq ",
        "and ","band ","or ","bor "
    };

    static std::string sops[6] = {
        " ","splus ", "ssub ", "not ","smult ", "sbnot "
    };
#define LOG "[PARSE LOG]: "
    class Node {
    public:
        Node(int line): line(line) {std::cout<<LOG<<"Line "<<line<<std::endl;}
        virtual ~Node() {}
        virtual llvm::Value* CodeGen(CodeContext& context) {};
        int line;
    };
    class Stm : public Node {
    public:
        Stm(int line): Node(line) {std::cout <<LOG<<"Stm "<<std::endl;}
        ~Stm() {}
        virtual llvm::Value* CodeGen(CodeContext& context) {};
    };
    class VarType: public Node {
    public:
        int _type;
        bool _array;
        bool _ptr;
        VarType(int __type, int line,bool __array,bool __ptr): _type(__type), Node(line),_array(__array), _ptr(__ptr) {}
        ~VarType() {}
        virtual llvm::Value* CodeGen(CodeContext& context){};
        // int line;
    };
    class Expr : public Node {
    public:
        Expr(int line): Node(line) {}
        ~Expr() {}
        virtual llvm::Value* CodeGen(CodeContext& context){};
    };
    class Root : public Node {
    public:
        Decls* _decls;
        Root(Decls* __d, int line): _decls(__d), Node(line) {}
        ~Root() {}
        llvm::Value* CodeGen(CodeContext& context);
    };

    class Decl: public Stm {
    public:
        Decl(int line): Stm(line) {}
        ~Decl() {}
        virtual llvm::Value* CodeGen(CodeContext& context) {};

    };

    class FuncDecl: public Decl {
    public:
        VarType* _Type;
        std::string _FuncName;
        Args* _args;
        Stms* _fb; 
        FuncDecl(VarType* __Type, const std::string& __FuncName, Args* __args, int line, Stms* __fb = NULL) :
                _Type(__Type), _FuncName(__FuncName), _args(__args), _fb(__fb), Decl(line) {std::cout <<LOG<<"Func Decl "<<__FuncName<<std::endl; }
        ~FuncDecl() {}
        llvm::Value* CodeGen(CodeContext& context);
        std::string des(){ return "Decl Func:" + tps[_Type->_type]+ _FuncName;}
    };

    class Arg: public Node {
    public:
        VarType* _Type;
        std::string _Name;
        Arg(VarType* __Type, int line,const std::string& __Name = "") :
            _Type(__Type), _Name(__Name), Node(line) {std::cout <<LOG<<"Arg Decl "<<__Name<<std::endl;}
        ~Arg() {}
        llvm::Value* CodeGen(CodeContext& context);
    };

    class VarDecl: public Decl {
    public:
        VarType* _Type;
        VarList* _list;
        VarDecl(VarType* __Type, VarList* __list, int line) :
            _Type(__Type), _list(__list), Decl(line) {std::cout <<LOG<<"Var Decl "<<std::endl;}
        ~VarDecl() {}
        llvm::Value* CodeGen(CodeContext& context);
        std::string des(){ return "Decl Vars type:" + tps[_Type->_type];}
    };

    class VarInit: public Node {
    public:
        std::string _id;
        Expr* _initvaL;
        ExprList* _arrayinit;

        VarInit(const std::string& __id, int line) :
            _id(__id), _initvaL(NULL), Node(line), _arrayinit(NULL) {}
        VarInit(const std::string& __id, Expr* __initvaL, int line) :
            _id(__id), _initvaL(__initvaL), Node(line),  _arrayinit(NULL) {}
        VarInit(const std::string& __id, ExprList* __arrayinit, int line) :
            _id(__id), _arrayinit(__arrayinit), Node(line), _initvaL(NULL) {}    
        ~VarInit() {}
        llvm::Value* CodeGen(CodeContext& context){}
    };

    class PtrType: public VarType {
    public:
        PtrType(int __type, int line) :
            VarType(__type, line, false, true) {}
        ~PtrType() {}
        llvm::Value* CodeGen(CodeContext& context){}
    };

    class ArrayType: public VarType {
    public:
        int _num;

        ArrayType(int __type, int __num, int line) :
            VarType(__type, line, true, false), _num(__num) {}
        ~ArrayType() {}
        llvm::Value* CodeGen(CodeContext& context){}
    };
    // if-else 这里只支持一个else好了

    class IfStm : public Stm{
    public:
        Expr* _switch;
        Block* _ifStm;
        Block* _elseifStm;
        bool _ifelse;   // true: has else; false: no else
        IfStm(Expr* __switch, Block* __ifStm, Block* __elseifStm, bool __ifelse, int line) : 
            _switch(__switch), _ifStm(__ifStm), _elseifStm(__elseifStm), _ifelse(__ifelse), Stm(line) {}
        ~IfStm() {}
        const Block* _getifStm() {return _ifStm;}
        const Block* _getelseStm() {return _elseifStm;}
        void changeIfStm(Block* __ifStm){_ifStm = __ifStm;}
        void changeElseStm(Block* __elseifStm){ _elseifStm = __elseifStm;}
        std::string des(){return "IfStm";}
        llvm::Value* CodeGen(CodeContext& context);

    };

    class ForStm : public Stm{
    public:
        Expr* _expr1, *_expr2, *_expr3;
        Block* _block;
        ForStm(Expr* __expr1, Expr* __expr2, Expr* __expr3, Block* __block, int line) :
            _expr1(__expr1), _expr2(__expr2), _expr3(__expr3), _block(__block), Stm(line) {}
        std::string des(){return "ForStm";}
        llvm::Value* CodeGen(CodeContext& context);
    };

    class WhileStm : public Stm{
    public:
        Expr* _expr;
        Block* _block;
        WhileStm(Expr* __expr, Block* __block, int line) : _expr(__expr), _block(__block), Stm(line) {}
        ~WhileStm() {}
        std::string des(){return "WhileStm";}
        llvm::Value* CodeGen(CodeContext& context);
    };

    class DoStm : public Stm{
    public:
        Expr* _expr;
        Block* _block;
        DoStm(Expr* __expr, Block* __block, int line) : _expr(__expr), _block(__block), Stm(line) {}
        // DoStm() {}
        const Expr* getExpr(){ return _expr; }
        const Block* getBlock(){ return _block; }
        void changeExpr(Expr* __expr){ _expr = __expr;}
        void changeBlock(Block* __block){ _block = __block;}
        std::string des(){return "DoStm";}
        llvm::Value* CodeGen(CodeContext& context);
    };

    class SwitchStm : public Stm{
    public:
        Expr* _expr;
        Cases* _cases;
        SwitchStm(Expr* __expr, Cases* __cases, int line): _expr(__expr), _cases(__cases), Stm(line) {}
        // SwitchStm() {}
        const Expr* getExpr(){ return _expr; }
        const Cases* getCaseList(){ return _cases; }
        void changeExpr(Expr* __expr){ _expr = __expr;}
        void changeCaseList(Cases* __cases){ _cases = __cases;}
        std::string des(){return "SwitchStm";}
        llvm::Value* CodeGen(CodeContext& context);
    };

    class CaseStm : public Stm {
    public:
        Expr* _expr;
        Stms* _stms;
        CaseStm(Expr* __expr, Stms* __stms, int line) : _expr(__expr), _stms(__stms), Stm(line) {}
        const Stms* getStms(){ return _stms;}
        void changeStmList(Stms* __stms){ _stms = __stms; }
        std::string des(){return "CaseStm";}
        llvm::Value* CodeGen(CodeContext& context);
    };

    class BreakStm : public Stm{
    public:
        BreakStm(int line): Stm(line) {}
        ~BreakStm(){}
        llvm::Value* CodeGen(CodeContext& context);
    };

    class ContinueStm : public Stm{
    public:
        ContinueStm(int line): Stm(line) {}
        ~ContinueStm(){}
        llvm::Value* CodeGen(CodeContext& context);
    };

    class ReturnStm : public Stm{
    public:
        Expr* _return;
        ReturnStm(Expr* __return, int line): _return(__return), Stm(line) {}
        ~ReturnStm(){}
        llvm::Value* CodeGen(CodeContext& context);
    };

    class ExprStm : public Stm{
    public:
        Expr* _expr;
        ExprStm(Expr* __expr, int line): _expr(__expr), Stm(line) {}
        ~ExprStm(){}
        llvm::Value* CodeGen(CodeContext& context);
    };

    class Block : public Stm{
    public:
        Stms* _statements;
        Block(Stms* __s, int line): _statements(__s), Stm(line) { }
        ~Block() {}
        llvm::Value* CodeGen(CodeContext& context);
    };

    class SOP : public Expr {
    public:
        int op;
        Expr* lhs;
        SOP(Expr* lhs, int op, int line) :
            lhs(lhs), op(op), Expr(line) { }
        ~SOP() {}
        llvm::Value* CodeGen(CodeContext& context);
    };

    class BINOP : public Expr {
    public:
        int op;
        Expr* lhs;
        Expr* rhs;
        BINOP(Expr* lhs, int op, Expr* rhs, int line) :
            lhs(lhs), rhs(rhs), op(op), Expr(line) { }
        ~BINOP() {}
        llvm::Value* CodeGen(CodeContext& context);
    };

    class Id : public Expr {
    public:
        std::string _name;
        Id(const std::string& __name, int line) : _name(__name), Expr(line) { }
        ~Id() {}
        llvm::Value* CodeGen(CodeContext& context);
    };

    class Constant : public Expr {
    public:
        int _type;
        Constant(int __type, int line) : _type(__type), Expr(line) { }
        ~Constant() {}
        virtual llvm::Value* CodeGen(CodeContext& context){}
    };

    class Int : public Constant {
    public:
        long long _value;
        Int(long long __value, int line, int __type = 3) : Constant(__type, line), _value(__value) { }
        ~Int() {}
        llvm::Value* CodeGen(CodeContext& context);
    };

    class Float : public Constant {
    public:
        double _value;
        Float(double __value, int line, int __type = 2) : Constant(__type, line), _value(__value) { }
        ~Float() {}
        llvm::Value* CodeGen(CodeContext& context);
    };

    class Char : public Constant {
    public:
        char _value;
        Char(char __value, int line, int __type = 1) : Constant(__type, line), _value(__value) { }
        ~Char() {}
        llvm::Value* CodeGen(CodeContext& context);
    };

    // 这里记得要检验一下参数数量对不对
    class FuncCall : public Expr {
    public:
        std::string _FuncName;
        ExprList* _arguments;
        FuncCall(std::string __FuncName, ExprList* __arguments, int line) :
            _FuncName(__FuncName), _arguments(__arguments), Expr(line) { }
        ~FuncCall() {}
        llvm::Value* CodeGen(CodeContext& context);
    };

    class ArrayCall : public Expr {
    public:
        std::string _id;
        Expr* _num;
        ArrayCall(const std::string& __id, Expr* __num, int line) : 
            _id(__id), _num(__num), Expr(line) {}
        ~ArrayCall() {}
        llvm::Value* CodeGen(CodeContext& context);
    };
}

#endif