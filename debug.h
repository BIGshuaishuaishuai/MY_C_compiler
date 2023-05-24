# ifndef __DEBUG_H__
# define __DEBUG_H__

#include<iostream>
#include<string>

// using namespace std;

enum token{LP, RP, LC, RC, LB, RB, PLUS, SUB, MULT, DIV, MOD, 
           SHL, SHR, LT, EQ, GT, GE, LE, NE, EQU, ADDEQ, SUBEQ, 
           MULEQ, DIVEQ, MODEQ, SHLEQ, SHREQ, NOT, BNOT, AND, 
           BAND, OR, BOR, RET, IF, ELSE, WHILE, FOR, BREAK, CONTINUE, 
           SWITCH, CASE, DEFAULT, PTR, ARRAY, COMMA, SEMI, COLON, DOT, ARROW, 
};

enum token tok;

std::string tokens_str[] = {
    "LP", "RP", "LC", "RC", "LB", "RB", "PLUS", "SUB", "MULT", "DIV", "MOD", 
    "SHL", "SHR", "LT", "EQ", "GT", "GE", "LE", "NE", "EQU", "ADDEQ", "SUBEQ", 
    "MULEQ", "DIVEQ", "MODEQ", "SHLEQ", "SHREQ", "NOT", "BNOT", "AND", 
    "BAND", "OR", "BOR", "RET", "IF", "ELSE", "WHILE", "FOR", "BREAK", "CONTINUE", 
    "SWITCH", "CASE", "DEFAULT", "PTR", "ARRAY", "COMMA", "SEMI", "COLON", "DOT", "ARROW"
};

# define TOKEN(token) (tokens_str[tok = token]);

# endif
