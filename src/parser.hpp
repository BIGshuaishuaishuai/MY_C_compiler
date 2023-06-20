/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    LP = 258,
    RP = 259,
    LC = 260,
    RC = 261,
    RB = 262,
    LB = 263,
    PLUS = 264,
    SUB = 265,
    MULT = 266,
    DIV = 267,
    MOD = 268,
    SHL = 269,
    SHR = 270,
    LT = 271,
    EQ = 272,
    GT = 273,
    GE = 274,
    LE = 275,
    NE = 276,
    EQU = 277,
    ADDEQ = 278,
    SUBEQ = 279,
    MULEQ = 280,
    DIVEQ = 281,
    MODEQ = 282,
    SHLEQ = 283,
    SHREQ = 284,
    NOT = 285,
    BNOT = 286,
    AND = 287,
    BAND = 288,
    OR = 289,
    BOR = 290,
    RETURN = 291,
    IF = 292,
    WHILE = 293,
    ELSE = 294,
    FOR = 295,
    BREAK = 296,
    SWITCH = 297,
    CASE = 298,
    DEFAULT = 299,
    CONTINUE = 300,
    DO = 301,
    PTR = 302,
    SEMI = 303,
    COMMA = 304,
    ARRAY = 305,
    COLON = 306,
    INT = 307,
    ID = 308,
    TYPE = 309,
    FLOAT = 310,
    CHAR = 311,
    ARGLIST = 312,
    NEQ = 313
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 27 "parser.y"

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

#line 139 "parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */
