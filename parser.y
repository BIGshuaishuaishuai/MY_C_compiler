%{
#include "node.hpp" 
#include <string>
#include <iostream>


void yyerror(const char *s) {
    std::printf("Error: %s\n", s);
    std::exit(1); 
}

int yylex();

node::Program *Root;
%}

%output "Parser.cpp"

%union {
    int ival;
    std::string *sval;
    std::string *type;
    float fval;
    char cval;
    std::string *strVal;

    node::Program *program;
    node::Declaration *decl;
    node::Decls *decls; 
    node::FuncDecl *funcDecl;
    node::FuncBody *funcBody;
    node::VarDecl *varDecl;
    node::VarType *varType;
    node::Stmt *stmt;
    node::IfStmt *ifStmt;
    node::ForStmt *forStmt;
    node::WhileStmt *whileStmt;
    node::DoStmt *doStmt;
    node::SwitchStmt *switchStmt;
    node::CaseList *caseList;
    node::CaseStmt *caseStmt;
    node::BreakStmt* breakStmt;
	node::ContinueStmt* continueStmt;
    node::ReturnStmt *returnStmt;
    node::Stmts *stmts;
    node::Block *block;
    node::Arg *arg;
    node::ArgList *argList;
    node::VarInit *varInit;
    node::VarList *varList;
    node::Expr *expr;
    node::Constant* constant;
	node::ExprList* exprList;

}

%token  LP RP LC RC RB LB
        PLUS SUB MULT DIV MOD SHL SHR
        LT EQ GT GE LE NE 
        EQU ADDEQ SUBEQ MULEQ DIVEQ MODEQ SHLEQ SHREQ
        NOT BNOT AND BAND OR BOR
        RETURN IF WHILE ELSE FOR BREAK SWITCH CASE DEFAULT CONTINUE
        PTR SEMI COMMA TYPE ARRAY COLON
           	
%token<ival> INT
%token<sval> ID 
%token<type> TYPE
%token<dval> FLOAT
%token<cval> CHAR

%type<root>							    Root	
%type<decl>								Decl	
%type<decls>							Decls	
%type<funcDecl>							FuncDecl
%type<funcBody>							FuncBody
%type<varDecl>							VarDecl	
%type<varType>							VarType 	
%type<stmt>								Stm
%type<ifStmt>							IfStm
%type<forStmt>							ForStm
%type<whileStmt>						WhileStm
%type<doStmt>							DoStm
%type<switchStmt>						SwitchStm
%type<cases>							Cases
%type<caseStmt>							CaseStm
%type<breakStmt>						BreakStm
%type<continueStmt>						ContinueStm
%type<returnStmt>						ReturnStm
%type<stmts>							Stms
%type<block>							Block
%type<arg>								Arg
%type<argList>							Args
%type<varInit>							VarInit	
%type<varList>							VarList 
%type<expr>								Expr	
%type<constant>							Const
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

%start Root
%%

Root:       Decls 
            ;

Decls:      Decls Decl
            |
            ;

Decl:       VarDecl
            | FuncDecl
            ;

VarDecl:    VarType VarList SEMI
            ;

FuncDecl:   VarType ID LP Args RP SEMI
            | VarType ID LP Args RP FuncBody
            ;

FuncBody:	LC Stms RC
            ;

VarList:    VarList COMMA VarInit
           | VarInit
           ;
     
VarInit:    ID
            | ID EQU Expr
            ;

VarType:    TYPE
            | TYPE PTR
            | TYPE ARRAY LB INT RB
            ;


Stms:       Stms Stm
            | 
            ;

Stm:        Expr SEMI
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

Block:      Stm
            | LC Stms RC
            ;

Expr:         Expr PLUS Expr
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
            | PLUS Expr %prec NOT
            | SUB Expr  %prec NOT
            | NOT Expr
            | MULT Expr %prec NOT
            | BNOT Expr %prec NOT
            | Const
            | ID
            | ID LB Expr RB 
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

IfStm:      IF LP Expr RP Block ELSE Block
            | IF LP Expr RP Block
            ;
ForStm:     FOR LP Expr RP Block

WhileStm:   WHILE LP Expr RP Block
            ;

DoStm:      DO Block WHILE LP Expr RP SEMI
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