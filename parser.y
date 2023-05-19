%{
#include "AST.hpp" 
#include <string>
#include <iostream>


void yyerror(const char *s) {
    std::printf("Error: %s\n", s);
    std::exit(1); 
}

int yylex(void);

AST::Program *Root;
%}

%output "Parser.cpp"

%union {
    int iVal;
    std::string *sVal;
    double dVal;
    char cVal;
	std::string *strVal;
    AST::Program *program;
    AST::Decl *decl;
    AST::Decls *decls; 
    AST::FuncDecl *funcDecl;
    AST::FuncBody *funcBody;
    AST::VarDecl *varDecl;
    AST::TypeDecl *typeDecl;
    AST::VarType *varType;
    AST::BuiltInType* builtInType;
    AST::FieldDecls* fieldDecls;
	AST::FieldDecl* fieldDecl;
	AST::MemList* memList;
    AST::Stmt *stmt;
    AST::IfStmt *ifStmt;
    AST::ForStmt *forStmt;
    AST::WhileStmt *whileStmt;
    AST::DoStmt *doStmt;
    AST::SwitchStmt *switchStmt;
    AST::CaseList *caseList;
    AST::CaseStmt *caseStmt;
    AST::BreakStmt* breakStmt;
	AST::ContinueStmt* continueStmt;
    AST::ReturnStmt *returnStmt;
    AST::Stmts *stmts;
    AST::Block *block;
    AST::Arg *arg;
    AST::ArgList *argList;
    AST::VarInit *varInit;
    AST::VarList *varList;
    AST::Expr *expr;
    AST::Constant* constant;
	AST::ExprList* exprList;
    AST::Enm *enm;
    AST::EnmList *enmList;
}

%token  LP RP LC RC RB LB
        PLUS SUB MULT DIV MOD SHL SHR
        LT EQ GT GE LE NE 
        EQU ADDEQ SUBEQ MULEQ DIVEQ MODEQ 
        NOT AND BAND OR BOR
        RETURN IF WHILE ELSE FOR SWITCH CASE DEFAULT CONTINUE
        PTR SEMI COMMA DOT TYPE
           	
%token<iVal> INT
%token<sVal> ID 
%token<dVal> FLOAT
%token<cVal> CHAR

%type<program>							Program	
%type<decl>								Decl	
%type<decls>							Decls	
%type<funcDecl>							FuncDecl
%type<funcBody>							FuncBody	
%type<varDecl>							VarDecl	
%type<typeDecl>							TypeDecl	
%type<varType>							VarType _VarType
%type<builtInType>						BuiltInType
%type<fieldDecls>						FieldDecls
%type<fieldDecl>						FieldDecl
%type<memList>							MemList _MemList	
%type<stmt>								Stmt
%type<ifStmt>							IfStmt
%type<forStmt>							ForStmt
%type<whileStmt>						WhileStmt
%type<doStmt>							DoStmt
%type<switchStmt>						SwitchStmt
%type<caseList>							CaseList
%type<caseStmt>							CaseStmt
%type<breakStmt>						BreakStmt
%type<continueStmt>						ContinueStmt
%type<returnStmt>						ReturnStmt
%type<stmts>							Stmts
%type<block>							Block
%type<arg>								Arg
%type<argList>							ArgList _ArgList
%type<varInit>							VarInit	
%type<varList>							VarList _VarList
%type<expr>								Expr	
%type<constant>							Constant
%type<exprList>							ExprList _ExprList
%type<enm>								Enm
%type<enmList>							EnmList	_EnmList

%nonassoc IF
%nonassoc ELSE

%left	COMMA //15
%left	FUNC_CALL_ARG_LIST
%right	ASSIGN ADDEQ SUBEQ MULEQ DIVEQ MODEQ SHLEQ SHREQ BANDEQ BOREQ BXOREQ //14
%right	QUES COLON //13
%left	OR//12
%left	AND//11
%left	BOR//10
%left	BXOR//9
%left	BAND//8
%left	EQ NEQ//7
%left	GE GT LE LT//6
%left	SHL SHR//5
%left	ADD SUB//4
%left	MUL DIV MOD//3
%right	DADD DSUB NOT BNOT SIZEOF//2
%left	DOT ARW//1

%start Program
%%

Root:       Decls
            ;

Decls:      Decls decl
            |
            ;

decl:       VarDecl
            | FuncDecl
            ;

VarDecl:    VarType VarList SEMI
            ;

FuncDecl:   VarType ID LP args RP SEMI
            | VarType ID LP args RP FuncBody
            ;

FuncBody:	LC Stmts RC
            ;

VarList:    VarList COMMA VarInit
           | VarInit
           ;
     
VarInit:    ID
            | ID EQU Expr
            ;

VarType:    TYPE
            | PTR TYPE 
            | TYPE ARRAY LB INT RB
            ;

args:       VarType ID
            | VarType
            ;

Stms:       Stms stm
            | 
            ;

stm:        Expr SEMI
            | ReturnStm
            | IfStm
            | WhileStm
            | DoStm
            | SwitchStm
            | ContinueStm
            | BreakStm
            | CaseStm
            | SEMI
            | VarDecl
            | Block
            ;

Block:      LC Stms RC

// 没太看懂yjj这里右递归是怎么避免的
Expr:       Expr PLUS expr

ReturnStm:  RETURN Expr SEMI
            RETURN SEMI
            ;

IfStm:      IF LP Expr RP Stm ELSE Stm
            | IF LP Expr RP Stm
            ;

WhileStm:   WHILE LP Expr RP Stm
            ;

DoStm:      DO Stmt WHILE LP Expr RP SEMI
            ;

SwitchStm:  SWITCH LP Expr RP LC Cases RC
            ;

CaseStm:      CASE Expr COLON Stms
            | DEFAULT Expr COLON Stms
            ;

ContinueStm:CONTINUE SEMI
            ;

BreakStm:   BREAK SEMI
            ;

Cases:      Cases CaseStm
            ;

args:           
%%