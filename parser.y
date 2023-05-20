%{
#include "node.hpp" 
#include <string>
#include <iostream>


void yyerror(const char *s) {
    std::printf("Error: %s\n", s);
    std::exit(1); 
}

int yylex();

AST::Program *Root;
%}

%output "Parser.cpp"

%union {
    int ival;
    std::string *sval;
    std::string *type;
    float fval;
    char cval;

	// std::string *strVal;
    // AST::Program *program;
    // AST::Decl *decl;
    // AST::Decls *decls; 
    // AST::FuncDecl *funcDecl;
    // AST::FuncBody *funcBody;
    // AST::VarDecl *varDecl;
    // AST::TypeDecl *typeDecl;
    // AST::VarType *varType;
    // AST::BuiltInType* builtInType;
    // AST::FieldDecls* fieldDecls;
	// AST::FieldDecl* fieldDecl;
	// AST::MemList* memList;
    // AST::Stmt *stmt;
    // AST::IfStmt *ifStmt;
    // AST::ForStmt *forStmt;
    // AST::WhileStmt *whileStmt;
    // AST::DoStmt *doStmt;
    // AST::SwitchStmt *switchStmt;
    // AST::CaseList *caseList;
    // AST::CaseStmt *caseStmt;
    // AST::BreakStmt* breakStmt;
	// AST::ContinueStmt* continueStmt;
    // AST::ReturnStmt *returnStmt;
    // AST::Stmts *stmts;
    // AST::Block *block;
    // AST::Arg *arg;
    // AST::ArgList *argList;
    // AST::VarInit *varInit;
    // AST::VarList *varList;
    // AST::Expr *expr;
    // AST::Constant* constant;
	// AST::ExprList* exprList;
    // AST::Enm *enm;
    // AST::EnmList *enmList;
}

%token  LP RP LC RC RB LB
        PLUS SUB MULT DIV MOD SHL SHR
        LT EQ GT GE LE NE 
        EQU ADDEQ SUBEQ MULEQ DIVEQ MODEQ SHLEQ SHREQ
        NOT BNOT AND BAND OR BOR
        RETURN IF WHILE ELSE FOR BREAK SWITCH CASE DEFAULT CONTINUE
        PTR SEMI COMMA DOT TYPE ARRAY COLON ARROW
           	
%token<ival> INT
%token<sval> ID 
%token<type> TYPE
%token<dval> FLOAT
%token<cval> CHAR

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
%type<stmt>								Stm
%type<ifStmt>							IfStm
%type<forStmt>							ForStm
%type<whileStmt>						WhileStm
%type<doStmt>							DoStm
%type<switchStmt>						SwitchStm
%type<caseList>							CaseList
%type<caseStmt>							CaseStm
%type<breakStmt>						BreakStm
%type<continueStmt>						ContinueStm
%type<returnStmt>						ReturnStm
%type<stmts>							Stms
%type<block>							Block
%type<arg>								Arg
%type<argList>							ArgList _ArgList
%type<varInit>							VarInit	
%type<varList>							VarList _VarList
%type<expr>								Expr	
%type<constant>							Constant
%type<exprList>							ExprList _ExprList

%nonassoc IF
%nonassoc ELSE


%left   COMMA
%left   FUNC_CALL_ARG_LIST
%right  EQU ADDEQ SUBEQ MULEQ DIVEQ MODEQ SHLEQ SHREQ
%left	OR
%left	AND
%left	BOR
%left	BAND
%left	EQ NEQ
%left	GE GT LE LT
%left   SHL SHR
%left   PLUS SUB 
%left   MULT DIV MOD
%right  BNOT NOT
%left   ARROW DOT

%start Root
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


Stms:       Stms stm
            | 
            ;

stm:        Expr SEMI
            | ReturnStm
            | IfStm
            | WhileStm
            | ForStm
            | DoStm
            | SwitchStm
            | ContinueStm
            | BreakStm
            | SEMI
            | VarDecl
            | Block
            ;

Block:      LC Stms RC
            ;

Expr:       Expr PLUS Expr
            | Expr SUB Expr
            | Expr MULT Expr
            | Expr DIV Expr
            | Expr MOD Expr
            | Expr SHL Expr
            | Expr SHR Expr
            | Expr LT Expr
            | Expr LE Expr
            | Expr EQ Expr
            | Expr GE Expr
            | Expr GT Expr
            | Expr NE Expr
            | Expr EQ Expr
            | Expr ADDEQ Expr
            | Expr SUBEQ Expr
            | Expr DIVEQ Expr
            | Expr MULEQ Expr
            | Expr MODEQ Expr
            | Expr SHLEQ Expr
            | Expr SHREQ Expr
            | Expr AND Expr
            | Expr BAND Expr
            | Expr OR Expr
            | Expr BOR Expr
            | LP Expr RP
            | Expr DOT ID
            | Expr ARROW ID
            | PLUS Expr %prec NOT
            | SUB Expr  %prec NOT
            | NOT Expr
            | MULT Expr %prec NOT
            | BNOT Expr %prec NOT
            | Const
            | ID
            | ID LB Expr RB %prec ARROW
            | ID LP ExprList RP
            ;

ExprList:	_ExprList COMMA Expr									{  $$ = $1; $$->push_back($3);   }
			| Expr %prec FUNC_CALL_ARG_LIST							{  $$ = new AST::ExprList(); $$->push_back($1);   }
			|														{  $$ = new AST::ExprList();   }
			;

_ExprList:	_ExprList COMMA Expr 									{  $$ = $1; $$->push_back($3);   }
			| Expr %prec FUNC_CALL_ARG_LIST							{  $$ = new AST::ExprList(); $$->push_back($1);   }
			;
 
Const:      INT
            | CHAR
            | FLOAT
            ; 

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

CaseStm:    CASE Expr COLON Stms
            | DEFAULT Expr COLON Stms
            ;

ContinueStm:CONTINUE SEMI
            ;

BreakStm:   BREAK SEMI
            ;

Cases:      Cases CaseStm
            ;

Args:       Args COMMA Arg 
            | Arg
            ;

Arg:        VarType ID
            | VarType
            ;  

%%