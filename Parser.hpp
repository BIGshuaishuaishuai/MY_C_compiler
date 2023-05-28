/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    LP = 258,                      /* LP  */
    RP = 259,                      /* RP  */
    LC = 260,                      /* LC  */
    RC = 261,                      /* RC  */
    RB = 262,                      /* RB  */
    LB = 263,                      /* LB  */
    PLUS = 264,                    /* PLUS  */
    SUB = 265,                     /* SUB  */
    MULT = 266,                    /* MULT  */
    DIV = 267,                     /* DIV  */
    MOD = 268,                     /* MOD  */
    SHL = 269,                     /* SHL  */
    SHR = 270,                     /* SHR  */
    LT = 271,                      /* LT  */
    EQ = 272,                      /* EQ  */
    GT = 273,                      /* GT  */
    GE = 274,                      /* GE  */
    LE = 275,                      /* LE  */
    NE = 276,                      /* NE  */
    EQU = 277,                     /* EQU  */
    ADDEQ = 278,                   /* ADDEQ  */
    SUBEQ = 279,                   /* SUBEQ  */
    MULEQ = 280,                   /* MULEQ  */
    DIVEQ = 281,                   /* DIVEQ  */
    MODEQ = 282,                   /* MODEQ  */
    SHLEQ = 283,                   /* SHLEQ  */
    SHREQ = 284,                   /* SHREQ  */
    NOT = 285,                     /* NOT  */
    BNOT = 286,                    /* BNOT  */
    AND = 287,                     /* AND  */
    BAND = 288,                    /* BAND  */
    OR = 289,                      /* OR  */
    BOR = 290,                     /* BOR  */
    RETURN = 291,                  /* RETURN  */
    IF = 292,                      /* IF  */
    WHILE = 293,                   /* WHILE  */
    ELSE = 294,                    /* ELSE  */
    FOR = 295,                     /* FOR  */
    BREAK = 296,                   /* BREAK  */
    SWITCH = 297,                  /* SWITCH  */
    CASE = 298,                    /* CASE  */
    DEFAULT = 299,                 /* DEFAULT  */
    CONTINUE = 300,                /* CONTINUE  */
    DO = 301,                      /* DO  */
    PTR = 302,                     /* PTR  */
    SEMI = 303,                    /* SEMI  */
    COMMA = 304,                   /* COMMA  */
    ARRAY = 305,                   /* ARRAY  */
    COLON = 306,                   /* COLON  */
    INT = 307,                     /* INT  */
    ID = 308,                      /* ID  */
    TYPE = 309,                    /* TYPE  */
    FLOAT = 310,                   /* FLOAT  */
    CHAR = 311,                    /* CHAR  */
    ARGLIST = 312,                 /* ARGLIST  */
    NEQ = 313                      /* NEQ  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 24 "parser.y"

    int ival;
    std::string *sval;
    std::string *type;
    float fval;
    char cval;
    Node::Root *root;
    Node::Decl *decl;
    Node::Decls *decls; 
    Node::VarType *varType;
    Node::Stm *stm;
    Node::Stms *stms;
    Node::Arg *arg;
    Node::Args *args;
    Node::VarInit *varInit;
    Node::VarList *varList;
    Node::Expr *expr;
	Node::ExprList* exprList;

#line 142 "Parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_HPP_INCLUDED  */
