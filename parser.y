%{
#include "node.hpp" 
#include <string>
#include <iostream>

int type2int(std::string type)
{
    if(type == "void") return void_type;
    else if(type == "char") return char_type;
    else if(type == "float") return float_type;
    else if(type == "int") return int_type;
    else return -1;
}

void yyerror(const char *s) {
    std::printf("Error: %s\n", s);
    std::exit(1); 
}

int yylex();

node::Root *root;
%}

%output "Parser.cpp"

%union {
    int ival;
    std::string *sval;
    std::string *type;
    float fval;
    char cval;

    node::Root *root;
    node::Decl *decl;
    node::Decls *decls; 
    node::FuncDecl *funcDecl;
    node::VarDecl *varDecl;
    node::VarType *varType;
    node::Stm *stmt;
    node::IfStm *ifStm;
    node::ForStm *forStm;
    node::WhileStm *whileStm;
    node::DoStm *doStm;
    node::SwitchStm *switchStm;
    node::Cases *cases;
    node::CaseStm *caseStm;
    node::BreakStm* breakStm;
	node::ContinueStm* continueStm;
    node::ReturnStm *returnStm;
    node::Stms *stmts;
    node::Block *block;
    node::Arg *arg;
    node::Args *args;
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
%type<stm>								Stm
%type<ifStm>							IfStm
%type<forStm>							ForStm
%type<whileStm>						    WhileStm
%type<doStm>							DoStm
%type<switchStm>						SwitchStm
%type<cases>							Cases
%type<caseStm>							CaseStm
%type<breakStm>						    BreakStm
%type<continueStm>						ContinueStm
%type<returnStm>						ReturnStm
%type<stms>							    Stms
%type<block>							Block
%type<arg>								Arg
%type<args>							    Args
%type<varInit>							VarInit	
%type<varList>							VarList 
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

%start Root
%%

Root:       Decls { $$ = new node::Root(*$1); }
            ;

Decls:      Decls Decl  { $1->push_back($2);    $$ = $1; }
            |           { $$ = new node::Decls(); }
            ;

Decl:       VarDecl     { $$ = $1; }
            | FuncDecl  { $$ = $1; }
            ;

VarDecl:    VarType VarList SEMI    { $$ = new node::VarDecl($1, $2); }
            ;

FuncDecl:   VarType ID LP Args RP SEMI          { $$ = new node::FuncDecl($1, *$2, $4); }
            | VarType ID LP Args RP FuncBody    { $$ = new node::FuncDecl($1, *$2, $4, $6); }
            ;

FuncBody:	LC Stms RC              { $$ = $2;} 
            ;

VarList:    VarList COMMA VarInit   { $$ = $1; $$->push_back($3); }
           | VarInit                { $$ = new node::VarList(); $$->push_back($1); }
           ;
     
VarInit:    ID              { $$ = new node::VarInit(*$1); }
            | ID EQU Expr   { $$ = new node::VarInit(*$1, $3); }
            ;

VarType:    TYPE                    { $$ = new node::VarType(type2int(*$1)); }
            | TYPE PTR              { $$ = new node::PtrType(type2int(*$1)); }
            | TYPE ARRAY LB INT RB  { $$ = new node::ArrayType(type2int(*$1), $4); }
            ;


Stms:       Stms Stm        { $$ = $1; $$->push_back($2); }
            |               { $$ = new node::Stms(); }
            ;
            
Stm:        Expr SEMI           { $$ = new node::ExprStm($1); }
            | ReturnStm         { $$ = $1; }
            | IfStm             { $$ = $1; }
            | WhileStm          { $$ = $1; }
            | ForStm            { $$ = $1; }
            | DoStm             { $$ = $1; }
            | SwitchStm         { $$ = $1; }
            | ContinueStm       { $$ = $1; }
            | BreakStm          { $$ = $1; }
            | SEMI              { $$ = NULL; }
            | VarDecl           { $$ = $1; }
            | Block             { $$ = $1; }
            ;           

Block:      LC Stms RC    { $$ new node::Block($2); }    
            ;

Expr:         Expr PLUS Expr            { $$ = new node::BINOP($1, plus, $2); }
            | Expr SUB Expr     { $$ = new node::BINOP($1, sub, $2); }
            | Expr MULT Expr        { $$ = new node::BINOP($1, mult, $2); }
            | Expr DIV Expr     { $$ = new node::BINOP($1, div, $2); }
            | Expr MOD Expr     { $$ = new node::BINOP($1, mod, $2); }
            | Expr SHL Expr     { $$ = new node::BINOP($1, shl, $2); }
            | Expr SHR Expr         { $$ = new node::BINOP($1, shr, $2); }
            | Expr LT Expr      { $$ = new node::BINOP($1, lt, $2); }
            | Expr LE Expr      { $$ = new node::BINOP($1, le, $2); }
            | Expr EQ Expr      { $$ = new node::BINOP($1, eq, $2); }
            | Expr GE Expr      { $$ = new node::BINOP($1, ge, $2); }
            | Expr GT Expr      { $$ = new node::BINOP($1, gt, $2); }
            | Expr NE Expr      { $$ = new node::BINOP($1, ne, $2); }
            | Expr EQ Expr      { $$ = new node::BINOP($1, eq, $2); }
            | Expr ADDEQ Expr       { $$ = new node::BINOP($1, addeq, $2); }
            | Expr SUBEQ Expr       { $$ = new node::BINOP($1, subeq, $2); }
            | Expr DIVEQ Expr       { $$ = new node::BINOP($1, diveq, $2); }
            | Expr MULEQ Expr       { $$ = new node::BINOP($1, muleq, $2); }
            | Expr MODEQ Expr       { $$ = new node::BINOP($1, modeq, $2); }
            | Expr SHLEQ Expr       { $$ = new node::BINOP($1, shleq, $2); }
            | Expr SHREQ Expr       { $$ = new node::BINOP($1, shreq, $2); }
            | Expr AND Expr     { $$ = new node::BINOP($1, and, $2); }
            | Expr BAND Expr        { $$ = new node::BINOP($1, band, $2); }
            | Expr OR Expr      { $$ = new node::BINOP($1, or, $2); }
            | Expr BOR Expr     { $$ = new node::BINOP($1, bor, $2); }
            | LP Expr RP        { $$ = $2; }
            | PLUS Expr %prec NOT   { $$ = new node::SOP($2, splus); }
            | SUB Expr  %prec NOT   { $$ = new node::SOP($2, ssub); }
            | NOT Expr              { $$ = new node::SOP($2, not); }
            | MULT Expr %prec NOT   { $$ = new node::SOP($2, smult); }
            | BNOT Expr %prec NOT   { $$ = new node::SOP($2, sbnot); }
            | Constant             { $$ = $1; }
            | ID                { $$ = new node::ID(*$1); }
            | ID LB Expr RB     { $$ = new node::ArrayCall(*$1, $3); }
            | ID LP ExprList RP { $$ = new node::FuncCall(*$1, $3); }
            ;

ExprList:	_ExprList COMMA Expr									{  $$ = $1; $$->push_back($3);   }
			| Expr %prec FUNC_CALL_ARG_LIST							{  $$ = new node::ExprList(); $$->push_back($1);   }
			|														{  $$ = new node::ExprList();   }
			;

_ExprList:	_ExprList COMMA Expr 									{  $$ = $1; $$->push_back($3);   }
			| Expr %prec FUNC_CALL_ARG_LIST							{  $$ = new node::ExprList(); $$->push_back($1);   }
			;
 
Constant:   INT             { $$ = new node::Int($1); }
            | CHAR          { $$ = new node::Char($1); }
            | FLOAT         { $$ = new node::Float($1); }
            ; 

ReturnStm:  RETURN Expr SEMI    { $$ = new node::ReturnStm($2); }
            RETURN SEMI         { $$ = new node::ReturnStm(NULL); }
            ;

IfStm:      IF LP Expr RP Block ELSE Block  { $$ = new node::IfStm($3, $5, $7, true); }
            | IF LP Expr RP Block           { $$ = new node::IfStm($3, $5, NULL, false); }
            ;
ForStm:     FOR LP Expr SEMI Expr SEMI Expr RP Block    { $$ = new node::ForStm($3, $5, $7, $9); }

WhileStm:   WHILE LP Expr RP Block  { $$ = new node::WhileStm($3, $5); }
            ;

DoStm:      DO Block WHILE LP Expr RP SEMI  { $$ = new node::DoStm($5, $2); }
            ;

SwitchStm:  SWITCH LP Expr RP LC Cases RC   { $$ = new node::SwitchStm($3, $6); }
            ;

CaseStm:    CASE Expr COLON Stms            { $$ = new node::CaseStm($2, $4); }
            | DEFAULT COLON Stms       { $$ = new node::CaseStm(NULL, $3); }
            ;
 
ContinueStm:CONTINUE SEMI   { $$ = new node::ContinueStm(); }
            ;

BreakStm:   BREAK SEMI      { $$ = new node::BreakStm(); }
            ;

Cases:      Cases CaseStm   { $$ = $1; $$->push_back($2); }
            |               { $$ = new node::Cases(); }
            ;

Args:       Args COMMA Arg  { $$ = $1; $$->push_back($3); }
            |               { $$ = new node::Args(); }
            ;

Arg:        VarType ID      { $$ = new node::Args($1, *$2); }
            | VarType       { $$ = new node::Args($1); }
            ;  

%%