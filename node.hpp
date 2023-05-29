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

    class Node {
    public:
        Node() {}
        virtual ~Node() {}
        virtual llvm::Value* CodeGen(CodeContext& context) {};
    };
    class Stm : public Node {
    public:
        Stm() {}
        ~Stm() {}
        virtual llvm::Value* CodeGen(CodeContext& context) {};
    };
    class VarType: public Node {
    public:
        int _type;

        VarType(int __type): _type(__type) {}
        ~VarType() {}
        virtual llvm::Value* CodeGen(CodeContext& context){};
    };
    class Expr : public Node {
    public:
        Expr() {}
        ~Expr() {}
        virtual llvm::Value* CodeGen(CodeContext& context){};
    };
    class Root : public Node {
    public:
        Decls* _decls;
        Root(Decls* __d): _decls(__d) {}
        ~Root() {}
        llvm::Value* CodeGen(CodeContext& context);
    };

    class Decl: public Stm {
    public:
        Decl() {}
        ~Decl() {}
        virtual llvm::Value* CodeGen(CodeContext& context) {};

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
        std::string des(){ return "Decl Func:" + tps[_Type->_type]+ _FuncName;}
    };

    class Arg: public Node {
    public:
        VarType* _Type;
        std::string _Name;
        Arg(VarType* __Type, const std::string& __Name = "") :
            _Type(__Type), _Name(__Name) {}
        ~Arg() {}
        llvm::Value* CodeGen(CodeContext& context);
    };

    class VarDecl: public Decl {
    public:
        VarType* _Type;
        VarList* _list;
        VarDecl(VarType* __Type, VarList* __list) :
            _Type(__Type), _list(__list) {}
        ~VarDecl() {}
        llvm::Value* CodeGen(CodeContext& context);
        std::string des(){ return "Decl Vars type:" + tps[_Type->_type];}
    };

    class VarInit: public Node {
    public:
        std::string _id;
        Expr* _initvaL;

        VarInit(const std::string& __id) :
            _id(__id), _initvaL(NULL) {}
        VarInit(const std::string& __id, Expr* __initvaL) :
            _id(__id), _initvaL(__initvaL) {}
        ~VarInit() {}
        llvm::Value* CodeGen(CodeContext& context){}
    };

    class PtrType: public VarType {
    public:
        bool _ptr;
        PtrType(int __type) :
            VarType(__type), _ptr(true) {}
        ~PtrType() {}
        llvm::Value* CodeGen(CodeContext& context){}
    };

    class ArrayType: public VarType {
    public:
        int _num;
        bool _array;
        ArrayType(int __type, int __num) :
            VarType(__type), _num(__num), _array(true) {}
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
        IfStm(Expr* __switch, Block* __ifStm, Block* __elseifStm, bool __ifelse) : 
            _switch(__switch), _ifStm(__ifStm), _elseifStm(__elseifStm), _ifelse(__ifelse) {}
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
        ForStm(Expr* __expr1, Expr* __expr2, Expr* __expr3, Block* __block) :
            _expr1(__expr1), _expr2(__expr2), _expr3(__expr3), _block(__block) {}
        ForStm() {}
        std::string des(){return "ForStm";}
        llvm::Value* CodeGen(CodeContext& context);
    };

    class WhileStm : public Stm{
    public:
        Expr* _expr;
        Block* _block;
        WhileStm(Expr* __expr, Block* __block) : _expr(__expr), _block(__block) {}
        ~WhileStm() {}
        std::string des(){return "WhileStm";}
        llvm::Value* CodeGen(CodeContext& context);
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
        std::string des(){return "DoStm";}
        llvm::Value* CodeGen(CodeContext& context);
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
        std::string des(){return "SwitchStm";}
        llvm::Value* CodeGen(CodeContext& context);
    };

    class CaseStm : public Stm{
    public:
        Expr* _expr;
        Stms* _stms;
        CaseStm(Expr* __expr, Stms* __stms) : _expr(__expr), _stms(__stms) {}
        const Stms* getStms(){ return _stms;}
        void changeStmList(Stms* __stms){ _stms = __stms; }
        std::string des(){return "CaseStm";}
        llvm::Value* CodeGen(CodeContext& context);
    };

    class BreakStm : public Stm{
    public:
        BreakStm(){}
        ~BreakStm(){}
        llvm::Value* CodeGen(CodeContext& context);
    };

    class ContinueStm : public Stm{
    public:
        ContinueStm(){}
        ~ContinueStm(){}
        llvm::Value* CodeGen(CodeContext& context);
    };

    class ReturnStm : public Stm{
    public:
        Expr* _return;
        ReturnStm(Expr* __return): _return(__return) {}
        ~ReturnStm(){}
        llvm::Value* CodeGen(CodeContext& context);
    };

    class ExprStm : public Stm{
    public:
        Expr* _expr;
        ExprStm(Expr* __expr): _expr(__expr) {}
        ~ExprStm(){}
        llvm::Value* CodeGen(CodeContext& context){}
    };

    class Block : public Stm {
    public:
        Stms* _statements;
        Block(Stms* __s): _statements(__s) { }
        ~Block() {}
        llvm::Value* CodeGen(CodeContext& context);
    };

    class SOP : public Expr {
    public:
        int op;
        Expr* lhs;
        SOP(Expr* lhs, int op) :
            lhs(lhs), op(op) { }
        ~SOP() {}
        llvm::Value* CodeGen(CodeContext& context);
    };

    class BINOP : public Expr {
    public:
        int op;
        Expr* lhs;
        Expr* rhs;
        BINOP(Expr* lhs, int op, Expr* rhs) :
            lhs(lhs), rhs(rhs), op(op) { }
        ~BINOP() {}
        llvm::Value* CodeGen(CodeContext& context);
    };

    class Id : public Expr {
    public:
        std::string _name;
        Id(const std::string& __name) : _name(__name) { }
        ~Id() {}
        llvm::Value* CodeGen(CodeContext& context);
    };

    class Constant : public Expr {
    public:
        int _type;
        Constant(int __type) : _type(__type) { }
        ~Constant() {}
        virtual llvm::Value* CodeGen(CodeContext& context){}
    };

    class Int : public Constant {
    public:
        long long _value;
        Int(long long __value, int __type = 3) : Constant(__type), _value(__value) { }
        ~Int() {}
        llvm::Value* CodeGen(CodeContext& context);
    };

    class Float : public Constant {
    public:
        double _value;
        Float(double __value, int __type = 2) : Constant(__type), _value(__value) { }
        ~Float() {}
        llvm::Value* CodeGen(CodeContext& context);
    };

    class Char : public Constant {
    public:
        char _value;
        Char(char __value, int __type = 1) : Constant(__type), _value(__value) { }
        ~Char() {}
        llvm::Value* CodeGen(CodeContext& context);
    };

    // 这里记得要检验一下参数数量对不对
    class FuncCall : public Expr {
    public:
        std::string _FuncName;
        ExprList* _arguments;
        FuncCall(std::string __FuncName, ExprList* __arguments) :
            _FuncName(__FuncName), _arguments(__arguments) { }
        ~FuncCall() {}
        llvm::Value* CodeGen(CodeContext& context);
    };

    class ArrayCall : public Expr {
    public:
        std::string _id;
        Expr* _num;
        ArrayCall(const std::string& __id, Expr* __num) : 
            _id(__id), _num(__num) {}
        ~ArrayCall() {}
        llvm::Value* CodeGen(CodeContext& context);
    };
}

#endif