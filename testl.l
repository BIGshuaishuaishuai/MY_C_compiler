%{
    // this file is used to test lexer.l
    //#include "node.h"
    //#include "parser.hpp"
    #include <stdio.h>
    #include <string>
    #include <iostream>
    extern "C" int yywrap() {return 1;}
    using namespace std;
%}

%option outfile="lex_test.cpp"

%%

"("     { cout << "lp " << endl;}
")"     { cout << "rp " << endl;}
"{"     { cout << "lc " << endl;}
"}"     { cout << "rc " << endl;}
"["     { cout << "lb " << endl;}
"]"     { cout << "rb " << endl;}
"+"     { cout << "+  " << endl; }
"-"     { cout << "-  " << endl; }
"*"     { cout << "*  " << endl; }
"/"     { cout << "/  " << endl; }
"%"     { cout << "%  " << endl; }
"<<"    { cout << "<< " << endl; }
">>"    { cout << ">> " << endl; }
"<"     { cout << "<  " << endl;}
"=="    { cout << "== " << endl;}
">"     { cout << ">  " << endl;}
">="    { cout << ">= " << endl;}
"<="    { cout << "<= " << endl;}
"!="    { cout << "!= " << endl;}
"="     { cout << "=  " << endl; }
"+="	{ cout << "=  " << endl; }
"-="	{ cout << "-= " << endl; }
"*="	{ cout << "*= " << endl; }
"/="	{ cout << "/= " << endl; }
"%="	{ cout << "%= " << endl; }
"<<="   { cout << "<<=" << endl; }
">>="   { cout << ">>=" << endl; }
"!"     { cout << "!  " << endl; }
"~"     { cout << "~  " << endl; }
"&&"    { cout << "&& " << endl; }
"&"     { cout << "&  " << endl; }
"||"    { cout << "|| " << endl; }
"|"     { cout << "|  " << endl; }
"return"    { cout << "return " << endl; }
"if"        { cout << "if " << endl;}
"do"        { cout << "do " << endl; }
"while"     { cout << "while " << endl;}
"else"      { cout << "else " << endl;}
"for"       { cout << "for " << endl;}
"break"     { cout << "break" << endl;  }
"continue"  { cout << "continue " << endl; }
"switch"	{ cout << "switch " << endl; }
"case"		{ cout << "case " << endl; }
"default"	{ cout << "default " << endl; }
"ptr"       { cout << "ptr " << endl; }
"array"     { cout << "array " << endl; }
","     { cout << ",  " << endl; }    
";"     { cout << ";  " << endl; }
"."     { cout << ".  " << endl; }
" " | \t | \n { ; }
"//".*  { ; }
"int"|"char"|"float"|"void" {string a = std::string(yytext, yyleng); cout << "type: " << a << endl; }
[0-9]+                      {  cout << "INT: " << atoi(yytext) << endl;  } 
[A-Za-z_][0-9A-Za-z_]*      { string a = std::string(yytext, yyleng); cout << "ID: " << a << endl;  }
[0-9]+\.[0-9]+              { cout << "FLOAT: " << atof(yytext) << endl; }
"\'"."\'"                       { cout << "CHAR: " << yytext[1] << endl; }
.       { printf("Error type A at Line %d: Illegal lex %s.\n", yylineno, yytext); }
%%

int main()
{
    FILE *fp;
	fp = fopen("test.txt", "r");
    if (!fp)
    {
        printf("can not open the file.\n");
        return 0;
    }
    yyin = fp;
    yylex();
    return 0;
}
