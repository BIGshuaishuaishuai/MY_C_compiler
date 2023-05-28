%{
    #include <iostream>
    #include "node.hpp" 

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
    Root *root;
%}

%output "Parser.cpp"

%union {
    int ival;
    std::string *sval;
    std::string *type;
    float fval;
    char cval;
    Root *root;
    Decl *decl;
    Decls *decls; 
    VarType *varType;
    Stm *stm;
    Stms *stms;
    Arg *arg;
    Args *args;
    VarInit *varInit;
    VarList *varList;
    Expr *expr;
	ExprList* exprList;
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
%token<dval> FLOAT
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

%type<root>							    Root	
%type<decl>								Decl FuncDecl VarDecl		
%type<decls>							Decls	
%type<stm>								Stm IfStm ForStm WhileStm DoStm SwitchStm CaseStm BreakStm ContinueStm ReturnStm
%type<stms>							    Stms FuncBody
%type<arg>								Arg
%type<args>							    Args
%type<varInit>							VarInit	
%type<varList>							VarList 
%type<expr>								Expr Constant Block
%type<exprList>							ExprList _ExprList
%type<cases>							Cases
%type<varType>							VarType 	

%nonassoc IF
%nonassoc ELSE

%start Root

%%

Root:       Decls { $$ = new Root($1); }
            ;

Decls:      Decls Decl  { $1->push_back($2);    $$ = $1; }
            |           { $$ = new Decls(); }
            ;

Decl:       VarDecl     { $$ = $1; }
            | FuncDecl  { $$ = $1; }
            ;

VarDecl:    VarType VarList SEMI    { $$ = new VarDecl($1, $2); }
            ;

VarList:    VarList COMMA VarInit   { $$ = $1; $$->push_back($3); }
           | VarInit                { $$ = new VarList(); $$->push_back($1); }
           ;
     
VarInit:    ID              { $$ = new VarInit(*$1); }
            | ID EQU Expr   { $$ = new VarInit(*$1, $3); }
            ;

VarType:    TYPE                    { $$ = new VarType(type2int(*$1)); }
            | TYPE PTR              { $$ = new PtrType(type2int(*$1)); }
            | TYPE ARRAY LB INT RB  { $$ = new ArrayType(type2int(*$1), $4); }
            ;

FuncDecl:   VarType ID LP Args RP SEMI          { $$ = new FuncDecl($1, *$2, $4); }
            | VarType ID LP Args RP FuncBody    { $$ = new FuncDecl($1, *$2, $4, $6); }
            ;

FuncBody:	LC Stms RC              { $$ = $2;} 
            ;

Args:       Args COMMA Arg  { $$ = $1; $$->push_back($3); }
            |               { $$ = new Args(); }
            ;

Arg:        VarType ID      { $$ = new Args($1, *$2); }
            | VarType       { $$ = new Args($1); }
            ;  

Stms:       Stms Stm        { $$ = $1; $$->push_back($2); }
            |               { $$ = new Stms(); }
            ;
            
Stm:        Expr SEMI           { $$ = new ExprStm($1); }
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

Expr:         Expr PLUS Expr            { $$ = new BINOP($1, plus_, $3); }
            | Expr SUB Expr     { $$ = new BINOP($1, sub_, $3); }
            | Expr MULT Expr        { $$ = new BINOP($1, mult_, $3); }
            | Expr DIV Expr     { $$ = new BINOP($1, div_, $3); }
            | Expr MOD Expr     { $$ = new BINOP($1, mod_, $3); }
            | Expr SHL Expr     { $$ = new BINOP($1, shl_, $3); }
            | Expr SHR Expr         { $$ = new BINOP($1, shr_, $3); }
            | Expr LT Expr      { $$ = new BINOP($1, lt_, $3); }
            | Expr LE Expr      { $$ = new BINOP($1, le_, $3); }
            | Expr EQ Expr      { $$ = new BINOP($1, eq_, $3); }
            | Expr GE Expr      { $$ = new BINOP($1, ge_, $3); }
            | Expr GT Expr      { $$ = new BINOP($1, gt_, $3); }
            | Expr NE Expr      { $$ = new BINOP($1, ne_, $3); }
            | Expr EQU Expr      { $$ = new BINOP($1, equ_, $3); }
            | Expr ADDEQ Expr       { $$ = new BINOP($1, addeq_, $3); }
            | Expr SUBEQ Expr       { $$ = new BINOP($1, subeq_, $3); }
            | Expr DIVEQ Expr       { $$ = new BINOP($1, diveq_, $3); }
            | Expr MULEQ Expr       { $$ = new BINOP($1, muleq_, $3); }
            | Expr MODEQ Expr       { $$ = new BINOP($1, modeq_, $3); }
            | Expr SHLEQ Expr       { $$ = new BINOP($1, shleq_, $3); }
            | Expr SHREQ Expr       { $$ = new BINOP($1, shreq_, $3); }
            | Expr AND Expr     { $$ = new BINOP($1, and_, $3); }
            | Expr BAND Expr        { $$ = new BINOP($1, band_, $3); }
            | Expr OR Expr      { $$ = new BINOP($1, or_, $3); }
            | Expr BOR Expr     { $$ = new BINOP($1, bor_, $3); }
            | LP Expr RP        { $$ = $2; }
            | PLUS Expr %prec NOT   { $$ = new SOP($2, splus_); }
            | SUB Expr  %prec NOT   { $$ = new SOP($2, ssub_); }
            | NOT Expr              { $$ = new SOP($2, not_); }
            | MULT Expr %prec NOT   { $$ = new SOP($2, smult_); }
            | BNOT Expr %prec NOT   { $$ = new SOP($2, sbnot_); }
            | Constant             { $$ = $1; }
            | ID                { $$ = new ID(*$1); }
            | ID LB Expr RB     { $$ = new ArrayCall(*$1, $3); }
            | ID LP ExprList RP { $$ = new FuncCall(*$1, $3); }
            ;

ExprList:	_ExprList COMMA Expr		{  $$ = $1; $$->push_back($3);   }
			| Expr %prec ARGLIST	    {  $$ = new ExprList(); $$->push_back($1);   }
			|							{  $$ = new ExprList();   }
			;

_ExprList:	_ExprList COMMA Expr 		{  $$ = $1; $$->push_back($3);   }
			| Expr %prec ARGLIST		{  $$ = new ExprList(); $$->push_back($1);   }
			;
 
Constant:   INT             { $$ = new Int($1); }
            | CHAR          { $$ = new Char($1); }
            | FLOAT         { $$ = new Float($1); }
            ; 

ReturnStm:  RETURN Expr SEMI    { $<Stm>$ = new ReturnStm($2); }
            RETURN SEMI         { $$ = new ReturnStm(NULL); }
            ;

IfStm:      IF LP Expr RP Block ELSE Block  { $$ = new IfStm($3, $5, $7, true); }
            | IF LP Expr RP Block           { $$ = new IfStm($3, $5, NULL, false); }
            ;
ForStm:     FOR LP Expr SEMI Expr SEMI Expr RP Block    { $$ = new ForStm($3, $5, $7, $9); }

WhileStm:   WHILE LP Expr RP Block  { $$ = new WhileStm($3, $5); }
            ;

DoStm:      DO Block WHILE LP Expr RP SEMI  { $$ = new DoStm($5, $2); }
            ;

SwitchStm:  SWITCH LP Expr RP LC Cases RC   { $$ = new SwitchStm($3, $6); }
            ;

CaseStm:    CASE Expr COLON Stms            { $$ = new CaseStm($2, $4); }
            | DEFAULT COLON Stms       { $$ = new CaseStm(NULL, $3); }
            ;
 
ContinueStm:CONTINUE SEMI   { $$ = new ContinueStm(); }
            ;

BreakStm:   BREAK SEMI      { $$ = new BreakStm(); }
            ;

Cases:      Cases CaseStm   { $$ = $1; $$->push_back($2); }
            |               { $$ = new Cases(); }
            ;

Block:      LC Stms RC    { $$ = new Block($2); }    
            ;

%%