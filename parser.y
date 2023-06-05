%{
    #include <iostream>
    #include <string>
    #include "node.hpp" 
    
    int type2int(std::string type)
    {
        if(type == "void") return node::void_type;
        else if(type == "char") return node::char_type;
        else if(type == "float") return node::float_type;
        else if(type == "int") return node::int_type;
        else return -1;
    }

    void yyerror(const char *s) {
        printf("Error: %s\n", s);
        exit(1); 
    }
    int yylex();
    extern int yylineno;
    node::Root *root;
%}

%output "parser.cpp"


%union {
    int ival;
    std::string *sval;
    std::string *type;
    float fval;
    char cval;
    node::Root *root_;
    node::Decl *decl;
    node::Decls *decls; 
    node::VarType *varType;
    node::Stm *stm;
    node::Stms *stms;
    node::Block *block;
    node::Arg *arg;
    node::Args *args;
    node::VarInit *varInit;
    node::VarList *varList;
    node::Expr *expr;
	node::ExprList* exprList;
    node::Cases *cases;
    node::CaseStm *caseStm;
}

%token  LP RP LC RC RB LB
%token  PLUS SUB MULT DIV MOD SHL SHR
%token  LT EQ GT GE LE NE 
%token  EQU ADDEQ SUBEQ MULEQ DIVEQ MODEQ SHLEQ SHREQ
%token  NOT BNOT AND BAND OR BOR
%token  RETURN IF WHILE ELSE FOR BREAK SWITCH CASE DEFAULT CONTINUE DO
%token  PTR SEMI COMMA ARRAY COLON           	
%token<ival> INT
%token<sval> ID 
%token<type> TYPE
%token<fval> FLOAT
%token<cval> CHAR

%left   COMMA
%left   ARGLIST
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

%type<root_>							    Root	
%type<decl>								Decl FuncDecl VarDecl		
%type<decls>							Decls	
%type<stm>								Stm IfStm ForStm WhileStm DoStm SwitchStm BreakStm ContinueStm ReturnStm
%type<stms>							    Stms FuncBody
%type<block>                            Block
%type<arg>								Arg
%type<args>							    Args
%type<varInit>							VarInit	
%type<varList>							VarList 
%type<expr>								Expr Constant 
%type<exprList>							ExprList _ExprList
%type<cases>							Cases
%type<caseStm>							CaseStm
%type<varType>							VarType 	

%nonassoc IF
%nonassoc ELSE

%start Root

%%

Root:       Decls { $$ = new node::Root($1, yylineno); root = $$; std::cout << "[parser root]: " << $$ << std::endl; }
            ;

Decls:      Decls Decl  { $1->push_back($2);    $$ = $1; }
            |           { $$ = new node::Decls(); }
            ;

Decl:       VarDecl     { $$ = $1; }
            | FuncDecl  { $$ = $1; }
            ;

VarDecl:    VarType VarList SEMI    { $$ = new  node::VarDecl($1, $2, yylineno); }
            ;

VarList:    VarList COMMA VarInit   { $$ = $1; $$->push_back($3); }
           | VarInit                { $$ = new  node::VarList(); $$->push_back($1); }
           ;
     
VarInit:    ID              { $$ = new  node::VarInit(*$1, yylineno); }
            | ID EQU Expr   { $$ = new  node::VarInit(*$1, $3, yylineno); }
            | ID EQU LC ExprList RC { $$ = new node::VarInit(*$1, $4, yylineno); }
            ;

VarType:    TYPE                    { $$ = new  node::VarType(type2int(*$1), yylineno); }
            | TYPE PTR              { $$ = new  node::PtrType(type2int(*$1), yylineno); }
            | TYPE ARRAY LB INT RB  { $$ = new  node::ArrayType(type2int(*$1), $4, yylineno); }
            ;

FuncDecl:   VarType ID LP Args RP SEMI          { $$ = new  node::FuncDecl($1, *$2, $4, yylineno); }
            | VarType ID LP Args RP FuncBody    { $$ = new  node::FuncDecl($1, *$2, $4, yylineno, $6); }
            ;

FuncBody:	LC Stms RC              { $$ = $2;} 
            ;

Args:       Args COMMA Arg  { $$ = $1; $$->push_back($3); }
            |               { $$ = new  node::Args(); }
            ;

Arg:        VarType ID      { $$ = new  node::Arg($1, yylineno, *$2); }
            | VarType       { $$ = new  node::Arg($1, yylineno); }
            ;  

Stms:       Stms Stm        { $$ = $1; $$->push_back($2); }
            |               { $$ = new  node::Stms(); }
            ;
            
Stm:        Expr SEMI           { $$ = new  node::ExprStm($1, yylineno); }
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

Expr:         Expr PLUS Expr            { $$ = new  node::BINOP($1, node::plus_, $3, yylineno); }
            | Expr SUB Expr     { $$ = new  node::BINOP($1, node::sub_, $3, yylineno); }
            | Expr MULT Expr        { $$ = new  node::BINOP($1, node::mult_, $3, yylineno); }
            | Expr DIV Expr     { $$ = new  node::BINOP($1, node::div_, $3, yylineno); }
            | Expr MOD Expr     { $$ = new  node::BINOP($1, node::mod_, $3, yylineno); }
            | Expr SHL Expr     { $$ = new  node::BINOP($1, node::shl_, $3, yylineno); }
            | Expr SHR Expr         { $$ = new  node::BINOP($1, node::shr_, $3, yylineno); }
            | Expr LT Expr      { $$ = new  node::BINOP($1, node::lt_, $3, yylineno); }
            | Expr LE Expr      { $$ = new  node::BINOP($1, node::le_, $3, yylineno); }
            | Expr EQ Expr      { $$ = new  node::BINOP($1, node::eq_, $3, yylineno); }
            | Expr GE Expr      { $$ = new  node::BINOP($1, node::ge_, $3, yylineno); }
            | Expr GT Expr      { $$ = new  node::BINOP($1, node::gt_, $3, yylineno); }
            | Expr NE Expr      { $$ = new  node::BINOP($1, node::ne_, $3, yylineno); }
            | Expr EQU Expr      { $$ = new  node::BINOP($1, node::equ_, $3, yylineno); }
            | Expr ADDEQ Expr       { $$ = new  node::BINOP($1, node::addeq_, $3, yylineno); }
            | Expr SUBEQ Expr       { $$ = new  node::BINOP($1, node::subeq_, $3, yylineno); }
            | Expr DIVEQ Expr       { $$ = new  node::BINOP($1, node::diveq_, $3, yylineno); }
            | Expr MULEQ Expr       { $$ = new  node::BINOP($1, node::muleq_, $3, yylineno); }
            | Expr MODEQ Expr       { $$ = new  node::BINOP($1, node::modeq_, $3, yylineno); }
            | Expr SHLEQ Expr       { $$ = new  node::BINOP($1, node::shleq_, $3, yylineno); }
            | Expr SHREQ Expr       { $$ = new  node::BINOP($1, node::shreq_, $3, yylineno); }
            | Expr AND Expr     { $$ = new  node::BINOP($1, node::and_, $3, yylineno); }
            | Expr BAND Expr        { $$ = new  node::BINOP($1, node::band_, $3, yylineno); }
            | Expr OR Expr      { $$ = new  node::BINOP($1, node::or_, $3, yylineno); }
            | Expr BOR Expr     { $$ = new  node::BINOP($1, node::bor_, $3, yylineno); }
            | LP Expr RP        { $$ = $2; }
            | PLUS Expr %prec NOT   { $$ = new  node::SOP($2, node::splus_, yylineno); }
            | SUB Expr  %prec NOT   { $$ = new  node::SOP($2, node::ssub_, yylineno); }
            | NOT Expr              { $$ = new  node::SOP($2, node::not_, yylineno); }
            | MULT Expr %prec NOT   { $$ = new  node::SOP($2, node::smult_, yylineno); }
            | BNOT Expr %prec NOT   { $$ = new  node::SOP($2, node::sbnot_, yylineno); }
            | Constant             { $$ = $1; }
            | ID                { $$ = new  node::Id(*$1, yylineno); }
            | ID LB Expr RB     { $$ = new  node::ArrayCall(*$1, $3, yylineno); }
            | ID LP ExprList RP { $$ = new  node::FuncCall(*$1, $3, yylineno); }
            ;

ExprList:	_ExprList COMMA Expr		{  $$ = $1; $$->push_back($3);   }
			| Expr %prec ARGLIST	    {  $$ = new  node::ExprList(); $$->push_back($1);   }
			|							{  $$ = new  node::ExprList();   }
			;

_ExprList:	_ExprList COMMA Expr 		{  $$ = $1; $$->push_back($3);   }
			| Expr %prec ARGLIST		{  $$ = new  node::ExprList(); $$->push_back($1);   }
			;
 
Constant:   INT             { $$ = new  node::Int($1, yylineno); }
            | CHAR          { $$ = new  node::Char($1, yylineno); }
            | FLOAT         { $$ = new  node::Float($1, yylineno); }
            ; 

ReturnStm:  RETURN Expr SEMI    { $<stm>$ = new  node::ReturnStm($2, yylineno); }
            RETURN SEMI         { $$ = new  node::ReturnStm(NULL, yylineno); }
            ;

IfStm:      IF LP Expr RP Block ELSE Block  { $$ = new  node::IfStm($3, $5, $7, true, yylineno); }
            | IF LP Expr RP Block           { $$ = new  node::IfStm($3, $5, NULL, false, yylineno); }
            ;
ForStm:     FOR LP Expr SEMI Expr SEMI Expr RP Block    { $$ = new  node::ForStm($3, $5, $7, $9, yylineno); }

WhileStm:   WHILE LP Expr RP Block  { $$ = new  node::WhileStm($3, $5, yylineno); }
            ;

DoStm:      DO Block WHILE LP Expr RP SEMI  { $$ = new  node::DoStm($5, $2, yylineno); }
            ;

SwitchStm:  SWITCH LP Expr RP LC Cases RC   { $$ = new  node::SwitchStm($3, $6, yylineno); }
            ;

CaseStm:    CASE Expr COLON Stms       { $$ = new  node::CaseStm($2, $4, yylineno); }
            | DEFAULT COLON Stms       { $$ = new  node::CaseStm(NULL, $3, yylineno); }
            ;
 
ContinueStm:CONTINUE SEMI   { $$ = new  node::ContinueStm(yylineno); }
            ;

BreakStm:   BREAK SEMI      { $$ = new  node::BreakStm(yylineno); }
            ;

Cases:      Cases CaseStm   { $$ = $1; $$->push_back($2); }
            |               { $$ = new  node::Cases(); }
            ;

Block:      LC Stms RC    { $$ = new  node::Block($2, yylineno); }    
            ;

%%