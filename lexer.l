// /**
//  * @file    lexer.cpp
//  * @brief   complete the lexer part of the C compiler.
//  *          你的程序在输出错误提示信息时，需要输出具体的错误类型、出错的位置（源程序行号）
// 以及相关的说明文字        
// */

// 这里还要include一些东西

%%

0|[1-9][0-9]*               { return INT; } 
[A-Za-z_][0-9A-Za-z_]*      { return ID; }
(0|[1-9][0-9]*)"."[0-9]+     { return FLOAT; }
\'.\'                       { return CHAR; }
"("     { return LP; }
")"     { return RP; }
"{"     { return LC; }
"}"     { return RC; }
"["     { return LB; }
"]"     { return RB; }
"+"     { return PLUS; }
"-"     { return MINUS; }
"*"     { return MULT; }
"/"     { return DIV; }
"%"     { return MOD; }
"<"     { return LT; }
"=="    { return EQ; }
">"     { return GT; }
">="    { return GE; }
"<="    { return LE; }
"!="    { return NE; }
","     { return COMMA; }
"="     { return EQU; }
"!"     { return NOT; }
"&&"    { return AND; }
"||"    { return OR; }
"return"    { return RETURN; }
"if"        { return IF; }
"while"     { return WHILE; }
"else"      { return ELSE; }
"for"       { return FOR; }
";"     { return SEMI; }
"."     { return DOT; }
"*"     { return STAR; }
"int"|"char"|"float"    { return TYPE; }
\t | \n { ; }
.       { printf("Error type A at Line %d: Illegal lex %s.\n", yylineno, yytext); }
%%