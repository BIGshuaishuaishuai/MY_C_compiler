%{
/**
 * @file    lexer.cpp
 * @brief   complete the lexer part of the C compiler.
 *          你的程序在输出错误提示信息时，需要输出具体的错误类型、出错的位置（源程序行号）
以及相关的说明文字        
*/

/*  yylineno    行号
 *  yytext      当前的lex
 *  yyleng      当前lex的长度
 *  yylex       即这部分的函数
*/
    #include "node.hpp"
    #include "parser.hpp"
    #include <string>
    #include <iostream>
    #include <cstdlib>
    extern "C" int yywrap() {return 1;}
    // extern yyleng;
    // int lineno = 0
    using namespace std;
%}
%option yylineno
%option outfile="lexer.cpp"
%option never-interactive
%%

"("     { std::cout <<"( HERE "<< yylineno <<std::endl;return LP; }
")"     { std::cout <<") HERE"<<std::endl;return RP; }
"{"     { std::cout <<"{ HERE"<<std::endl;return LC; }
"}"     { std::cout <<"} HERE"<<std::endl;return RC; }
"["     { std::cout <<"[ HERE"<<std::endl;return LB; }
"]"     { std::cout <<"] HERE"<<std::endl;return RB; }
"+"     { return PLUS; }
"-"     { return SUB; }
"*"     { return MULT; }
"/"     { return DIV; }
"%"     { return MOD; }
"<<"    { return SHL; }
">>"    { return SHR; }
"<"     { return LT; }
"=="    { return EQ; }
">"     { return GT; }
">="    { return GE; }
"<="    { return LE; }
"!="    { return NE; }
"="     { return EQU; }
"+="	{ return ADDEQ; }
"-="	{ return SUBEQ; }
"*="	{ return MULEQ; }
"/="	{ return DIVEQ; }
"%="	{ return MODEQ; }
"<<="   { return SHLEQ; }
">>="   { return SHREQ; }
"!"     { return NOT; }
"~"     { return BNOT; }
"&&"    { return AND; }
"&"     { return BAND; }
"||"    { return OR; }
"|"     { return BOR; }
"return"    { return RETURN; }
"if"        { std::cout <<"IF HERE"<<std::endl;return IF; }
"else"      { return ELSE; }
"do"        { return DO; }
"while"     { return WHILE; }
"for"       { return FOR; }
"break"     { return BREAK; }
"continue"  { return CONTINUE; }
"switch"	{ return SWITCH; }
"case"		{ return CASE; }
"default"	{ return DEFAULT; }
"ptr"       { std::cout <<"PTR HERE "<< yylineno <<std::endl;return PTR; }
"array"     { return ARRAY; }
","     { std::cout <<"COMMA HERE " <<std::endl;return COMMA; }
";"     { return SEMI; }
":"     { return COLON; }
" " | "\t"   { ; }
"\n"      { ; }
"//".*  { ; }
"int"|"char"|"float"|"void" { yylval.type = new std::string(yytext, yyleng); std::cout <<"type " << *yylval.type << " HERE "<< yylineno <<std::endl; return TYPE; }
[0-9]+                      { yylval.ival = atoi(yytext); return INT; } 
[A-Za-z_][0-9A-Za-z_]*      { std::cout <<"ID HERE "<< yylineno <<std::endl;yylval.sval = new std::string(yytext, yyleng); return ID; }
[0-9]+\.[0-9]+              { yylval.fval = atof(yytext); return FLOAT; }
"\'"."\'"                   { yylval.cval = yytext[1]; return CHAR; }
.       { printf("Lex Error at Line %d: Illegal lex %s.\n", yylineno, yytext);exit(1); }
%%