%{
// /**
//  * @file    lexer.cpp
//  * @brief   complete the lexer part of the C compiler.
//  *          你的程序在输出错误提示信息时，需要输出具体的错误类型、出错的位置（源程序行号）
// 以及相关的说明文字        
// */

// /*  yylineno    行号
//  *  yytext      当前的lex
//  *  yyleng      当前lex的长度
//  *  yylex       即这部分的函数
// */
    //#include "node.h"
    //#include "parser.hpp"
    #include <stdio.h>
    #include <string>
    #include <iostream>
    extern "C" int yywrap() {return 1;}
    using namespace std;
%}

%%

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
" " | \t | \n { ; }
"//".*  { ; }
"int"|"char"|"float"        { yylval.sval = new std::string(yytext, yyleng); return TYPE; }
[0-9]+                      { yylval.ival = atoi(yytext); return INT; } 
[A-Za-z_][0-9A-Za-z_]*      { yylval.sval = new std::string(yytext, yyleng); return ID; }
[0-9]+\.[0-9]+              { yylval.fval = atof(yytext); return FLOAT; }
\'.\'                       { yylval.cval = yytext[1]; return CHAR; }
.       { printf("Error type A at Line %d: Illegal lex %s.\n", yylineno, yytext); }
%%