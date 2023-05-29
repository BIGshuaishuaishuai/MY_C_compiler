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

Root:       Decls { $$ = new  node::Root($1); root = $$; std::cout << "[parser root]: " << $$ << std::endl; }
            ;

Decls:      Decls Decl  { $1->push_back($2);    $$ = $1; }
            |           { $$ = new  node::Decls(); }
            ;

Decl:       VarDecl     { $$ = $1; }
            | FuncDecl  { $$ = $1; }
            ;

VarDecl:    VarType VarList SEMI    { $$ = new  node::VarDecl($1, $2); }
            ;

VarList:    VarList COMMA VarInit   { $$ = $1; $$->push_back($3); }
           | VarInit                { $$ = new  node::VarList(); $$->push_back($1); }
           ;
     
VarInit:    ID              { $$ = new  node::VarInit(*$1); }
            | ID EQU Expr   { $$ = new  node::VarInit(*$1, $3); }
            ;

VarType:    TYPE                    { $$ = new  node::VarType(type2int(*$1)); }
            | TYPE PTR              { $$ = new  node::PtrType(type2int(*$1)); }
            | TYPE ARRAY LB INT RB  { $$ = new  node::ArrayType(type2int(*$1), $4); }
            ;

FuncDecl:   VarType ID LP Args RP SEMI          { $$ = new  node::FuncDecl($1, *$2, $4); }
            | VarType ID LP Args RP FuncBody    { $$ = new  node::FuncDecl($1, *$2, $4, $6); }
            ;

FuncBody:	LC Stms RC              { $$ = $2;} 
            ;

Args:       Args COMMA Arg  { $$ = $1; $$->push_back($3); }
            |               { $$ = new  node::Args(); }
            ;

Arg:        VarType ID      { $$ = new  node::Arg($1, *$2); }
            | VarType       { $$ = new  node::Arg($1); }
            ;  

Stms:       Stms Stm        { $$ = $1; $$->push_back($2); }
            |               { $$ = new  node::Stms(); }
            ;
            
Stm:        Expr SEMI           { $$ = new  node::ExprStm($1); }
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

Expr:         Expr PLUS Expr            { $$ = new  node::BINOP($1, node::plus_, $3); }
            | Expr SUB Expr     { $$ = new  node::BINOP($1, node::sub_, $3); }
            | Expr MULT Expr        { $$ = new  node::BINOP($1, node::mult_, $3); }
            | Expr DIV Expr     { $$ = new  node::BINOP($1, node::div_, $3); }
            | Expr MOD Expr     { $$ = new  node::BINOP($1, node::mod_, $3); }
            | Expr SHL Expr     { $$ = new  node::BINOP($1, node::shl_, $3); }
            | Expr SHR Expr         { $$ = new  node::BINOP($1, node::shr_, $3); }
            | Expr LT Expr      { $$ = new  node::BINOP($1, node::lt_, $3); }
            | Expr LE Expr      { $$ = new  node::BINOP($1, node::le_, $3); }
            | Expr EQ Expr      { $$ = new  node::BINOP($1, node::eq_, $3); }
            | Expr GE Expr      { $$ = new  node::BINOP($1, node::ge_, $3); }
            | Expr GT Expr      { $$ = new  node::BINOP($1, node::gt_, $3); }
            | Expr NE Expr      { $$ = new  node::BINOP($1, node::ne_, $3); }
            | Expr EQU Expr      { $$ = new  node::BINOP($1, node::equ_, $3); }
            | Expr ADDEQ Expr       { $$ = new  node::BINOP($1, node::addeq_, $3); }
            | Expr SUBEQ Expr       { $$ = new  node::BINOP($1, node::subeq_, $3); }
            | Expr DIVEQ Expr       { $$ = new  node::BINOP($1, node::diveq_, $3); }
            | Expr MULEQ Expr       { $$ = new  node::BINOP($1, node::muleq_, $3); }
            | Expr MODEQ Expr       { $$ = new  node::BINOP($1, node::modeq_, $3); }
            | Expr SHLEQ Expr       { $$ = new  node::BINOP($1, node::shleq_, $3); }
            | Expr SHREQ Expr       { $$ = new  node::BINOP($1, node::shreq_, $3); }
            | Expr AND Expr     { $$ = new  node::BINOP($1, node::and_, $3); }
            | Expr BAND Expr        { $$ = new  node::BINOP($1, node::band_, $3); }
            | Expr OR Expr      { $$ = new  node::BINOP($1, node::or_, $3); }
            | Expr BOR Expr     { $$ = new  node::BINOP($1, node::bor_, $3); }
            | LP Expr RP        { $$ = $2; }
            | PLUS Expr %prec NOT   { $$ = new  node::SOP($2, node::splus_); }
            | SUB Expr  %prec NOT   { $$ = new  node::SOP($2, node::ssub_); }
            | NOT Expr              { $$ = new  node::SOP($2, node::not_); }
            | MULT Expr %prec NOT   { $$ = new  node::SOP($2, node::smult_); }
            | BNOT Expr %prec NOT   { $$ = new  node::SOP($2, node::sbnot_); }
            | Constant             { $$ = $1; }
            | ID                { $$ = new  node::Id(*$1); }
            | ID LB Expr RB     { $$ = new  node::ArrayCall(*$1, $3); }
            | ID LP ExprList RP { $$ = new  node::FuncCall(*$1, $3); }
            ;

ExprList:	_ExprList COMMA Expr		{  $$ = $1; $$->push_back($3);   }
			| Expr %prec ARGLIST	    {  $$ = new  node::ExprList(); $$->push_back($1);   }
			|							{  $$ = new  node::ExprList();   }
			;

_ExprList:	_ExprList COMMA Expr 		{  $$ = $1; $$->push_back($3);   }
			| Expr %prec ARGLIST		{  $$ = new  node::ExprList(); $$->push_back($1);   }
			;
 
Constant:   INT             { $$ = new  node::Int($1); }
            | CHAR          { $$ = new  node::Char($1); }
            | FLOAT         { $$ = new  node::Float($1); }
            ; 

ReturnStm:  RETURN Expr SEMI    { $<stm>$ = new  node::ReturnStm($2); }
            RETURN SEMI         { $$ = new  node::ReturnStm(NULL); }
            ;

IfStm:      IF LP Expr RP Block ELSE Block  { $$ = new  node::IfStm($3, $5, $7, true); }
            | IF LP Expr RP Block           { $$ = new  node::IfStm($3, $5, NULL, false); }
            ;
ForStm:     FOR LP Expr SEMI Expr SEMI Expr RP Block    { $$ = new  node::ForStm($3, $5, $7, $9); }

WhileStm:   WHILE LP Expr RP Block  { $$ = new  node::WhileStm($3, $5); }
            ;

DoStm:      DO Block WHILE LP Expr RP SEMI  { $$ = new  node::DoStm($5, $2); }
            ;

SwitchStm:  SWITCH LP Expr RP LC Cases RC   { $$ = new  node::SwitchStm($3, $6); }
            ;

CaseStm:    CASE Expr COLON Stms       { $$ = new  node::CaseStm($2, $4); }
            | DEFAULT COLON Stms       { $$ = new  node::CaseStm(NULL, $3); }
            ;
 
ContinueStm:CONTINUE SEMI   { $$ = new  node::ContinueStm(); }
            ;

BreakStm:   BREAK SEMI      { $$ = new  node::BreakStm(); }
            ;

Cases:      Cases CaseStm   { $$ = $1; $$->push_back($2); }
            |               { $$ = new  node::Cases(); }
            ;

Block:      LC Stms RC    { $$ = new  node::Block($2); }    
            ;

%%