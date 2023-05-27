/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include "node.hpp" 
#include <string>
#include <iostream>

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

node::Root *root;

#line 94 "Parser.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


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
    FUNC_CALL_ARG_LIST = 312,
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

    node::Root *root;
    node::Decl *decl;
    node::Decls *decls; 
    node::FuncDecl *funcDecl;
    node::VarDecl *varDecl;
    node::VarType *varType;
    node::Stm *stmt;
    node::IfStm *ifStm;
    node::ForStm *forStm;
    node::WhileStm *whileStm;
    node::DoStm *doStm;
    node::SwitchStm *switchStm;
    node::Cases *cases;
    node::CaseStm *caseStm;
    node::BreakStm* breakStm;
	node::ContinueStm* continueStm;
    node::ReturnStm *returnStm;
    node::Stms *stmts;
    node::Block *block;
    node::Arg *arg;
    node::Args *args;
    node::VarInit *varInit;
    node::VarList *varList;
    node::Expr *expr;
    node::Constant* constant;
	node::ExprList* exprList;

#line 237 "Parser.cpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);





#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   813

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  59
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  93
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  184

#define YYUNDEFTOK  2
#define YYMAXUTOK   313


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   115,   115,   118,   119,   122,   123,   126,   129,   130,
     133,   136,   137,   140,   141,   144,   145,   146,   150,   151,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   168,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   208,   209,
     210,   213,   214,   217,   218,   219,   222,   222,   226,   227,
     229,   231,   234,   237,   240,   241,   244,   247,   250,   251,
     254,   255,   258,   259
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "LP", "RP", "LC", "RC", "RB", "LB",
  "PLUS", "SUB", "MULT", "DIV", "MOD", "SHL", "SHR", "LT", "EQ", "GT",
  "GE", "LE", "NE", "EQU", "ADDEQ", "SUBEQ", "MULEQ", "DIVEQ", "MODEQ",
  "SHLEQ", "SHREQ", "NOT", "BNOT", "AND", "BAND", "OR", "BOR", "RETURN",
  "IF", "WHILE", "ELSE", "FOR", "BREAK", "SWITCH", "CASE", "DEFAULT",
  "CONTINUE", "DO", "PTR", "SEMI", "COMMA", "ARRAY", "COLON", "INT", "ID",
  "TYPE", "FLOAT", "CHAR", "FUNC_CALL_ARG_LIST", "NEQ", "$accept", "Root",
  "Decls", "Decl", "VarDecl", "FuncDecl", "FuncBody", "VarList", "VarInit",
  "VarType", "Stms", "Stm", "Block", "Expr", "ExprList", "_ExprList",
  "Constant", "ReturnStm", "@1", "IfStm", "ForStm", "WhileStm", "DoStm",
  "SwitchStm", "CaseStm", "ContinueStm", "BreakStm", "Cases", "Args",
  "Arg", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313
};
# endif

#define YYPACT_NINF (-111)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-73)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -111,     2,   -50,  -111,   -24,  -111,  -111,  -111,   -36,  -111,
      11,     0,   -37,  -111,    16,  -111,   175,  -111,    19,    63,
       9,   175,   175,   175,   175,   175,   175,  -111,    17,  -111,
    -111,   699,  -111,    51,  -111,  -111,    13,   -50,   508,    53,
      53,    53,    53,    53,   175,   175,   175,   175,   175,   175,
     175,   175,   175,   175,   175,   175,   175,   175,   175,   175,
     175,   175,   175,   175,   175,   175,   175,   175,   175,   175,
     175,  -111,  -111,  -111,    22,  -111,  -111,   266,    72,    28,
     672,     3,     3,    53,    53,    53,   170,   170,   120,   293,
     120,   120,   120,   699,   699,   699,   699,   699,   699,   699,
     699,   699,   753,   250,   726,   780,    54,  -111,  -111,   175,
    -111,  -111,  -111,   175,    76,    77,    78,    34,    80,    38,
      82,  -111,  -111,    19,  -111,  -111,   348,  -111,  -111,  -111,
    -111,  -111,  -111,  -111,  -111,   307,   108,   388,   175,   175,
     175,  -111,   175,  -111,    50,  -111,  -111,  -111,   535,   562,
     428,   589,    86,    62,    82,    82,   175,    96,   175,    57,
      73,  -111,   468,  -111,   616,  -111,    82,   175,    60,    67,
    -111,   643,  -111,   175,    65,  -111,  -111,    82,   223,  -111,
    -111,  -111,   162,   162
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     2,     1,    15,     3,     5,     6,     0,    16,
       0,    13,     0,    12,     0,    91,     0,     7,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    73,    65,    75,
      74,    14,    64,    13,    11,    17,     0,     0,     0,    59,
      60,    62,    61,    63,    70,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    19,     8,     9,    93,    90,    58,    69,     0,     0,
       0,    33,    34,    35,    36,    37,    38,    39,    40,    42,
      44,    43,    41,    45,    46,    47,    48,    50,    49,    51,
      52,    53,    54,    55,    56,    57,     0,    92,    67,     0,
      66,    19,    10,     0,     0,     0,     0,     0,     0,     0,
       0,    29,    30,     0,    18,    31,     0,    21,    22,    24,
      23,    25,    26,    27,    28,    68,     0,     0,     0,     0,
       0,    87,     0,    86,     0,    20,    32,    76,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      79,    81,     0,    89,     0,    77,     0,     0,     0,     0,
      78,     0,    83,     0,     0,    88,    82,     0,     0,    19,
      80,    19,    85,    84
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -111,  -111,  -111,  -111,   118,  -111,  -111,  -111,   103,    25,
    -110,  -111,   -99,   -16,  -111,  -111,  -111,  -111,  -111,  -111,
    -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     5,   122,     7,    73,    12,    13,   123,
     106,   124,   125,   126,    78,    79,    32,   127,   153,   128,
     129,   130,   131,   132,   175,   133,   134,   168,    20,    75
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      31,   136,     3,    15,     4,    38,    39,    40,    41,    42,
      43,    17,    18,    36,    48,    49,    50,    11,    71,    14,
      44,   144,    16,     9,    58,    45,    10,     8,    77,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   160,   161,    21,    37,   111,
     112,    72,    74,    22,    23,    24,   172,   170,    19,   182,
      35,   183,    33,    16,    58,   107,   108,   109,   180,   138,
     139,   140,   141,   142,    25,    26,   143,   111,   152,   158,
     113,   114,   115,   135,   116,   117,   118,   137,   159,   119,
     120,   163,   121,   173,   174,   165,    27,    28,     4,    29,
      30,    21,   166,   111,   146,   176,   179,    22,    23,    24,
       6,    34,   148,   149,   150,     0,   151,     0,     0,    46,
      47,    48,    49,    50,    51,    52,     0,     0,    25,    26,
     162,    58,   164,     0,   113,   114,   115,     0,   116,   117,
     118,   171,     0,   119,   120,     0,   121,   178,     0,     0,
      27,    28,     4,    29,    30,    21,     0,   111,     0,     0,
       0,    22,    23,    24,     0,     0,     0,     0,    21,    46,
      47,    48,    49,    50,    22,    23,    24,     0,     0,     0,
       0,    58,    25,    26,     0,     0,     0,     0,   113,   114,
     115,     0,   116,   117,   118,    25,    26,   119,   120,     0,
     121,     0,     0,     0,    27,    28,     4,    29,    30,     0,
       0,     0,     0,     0,     0,     0,     0,    27,    28,     0,
      29,    30,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,     0,     0,    67,    68,    69,    70,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,     0,     0,   181,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,     0,     0,    67,    68,
      69,    70,    46,    47,    48,    49,    50,    51,    52,    53,
       0,    55,    56,    57,    58,   -72,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,     0,     0,    67,
      68,    69,    70,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -71,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,     0,     0,
      67,    68,    69,    70,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   145,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,     0,     0,
      67,    68,    69,    70,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   147,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,     0,     0,
      67,    68,    69,    70,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   156,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,     0,     0,
      67,    68,    69,    70,     0,     0,     0,     0,     0,     0,
       0,     0,    76,     0,     0,     0,   167,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,     0,   154,
      67,    68,    69,    70,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,     0,   155,    67,    68,    69,
      70,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,     0,   157,    67,    68,    69,    70,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,     0,
     169,    67,    68,    69,    70,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,     0,   177,    67,    68,
      69,    70,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,     0,     0,    67,    68,    69,    70,   110,
       0,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,     0,     0,    67,    68,    69,    70,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,     0,
       0,    67,    68,    69,    70,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    67,    68,
       0,    70,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    68,     0,    70,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    68
};

static const yytype_int16 yycheck[] =
{
      16,   111,     0,     3,    54,    21,    22,    23,    24,    25,
      26,    48,    49,     4,    11,    12,    13,    53,     5,     8,
       3,   120,    22,    47,    21,     8,    50,     2,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,   154,   155,     3,    49,     5,
       6,    48,    37,     9,    10,    11,     6,   166,    52,   179,
       7,   181,    53,    22,    21,    53,     4,    49,   177,     3,
       3,     3,    48,     3,    30,    31,    48,     5,    38,     3,
      36,    37,    38,   109,    40,    41,    42,   113,    36,    45,
      46,     5,    48,    43,    44,    48,    52,    53,    54,    55,
      56,     3,    39,     5,     6,    48,    51,     9,    10,    11,
       2,    18,   138,   139,   140,    -1,   142,    -1,    -1,     9,
      10,    11,    12,    13,    14,    15,    -1,    -1,    30,    31,
     156,    21,   158,    -1,    36,    37,    38,    -1,    40,    41,
      42,   167,    -1,    45,    46,    -1,    48,   173,    -1,    -1,
      52,    53,    54,    55,    56,     3,    -1,     5,    -1,    -1,
      -1,     9,    10,    11,    -1,    -1,    -1,    -1,     3,     9,
      10,    11,    12,    13,     9,    10,    11,    -1,    -1,    -1,
      -1,    21,    30,    31,    -1,    -1,    -1,    -1,    36,    37,
      38,    -1,    40,    41,    42,    30,    31,    45,    46,    -1,
      48,    -1,    -1,    -1,    52,    53,    54,    55,    56,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,    53,    -1,
      55,    56,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    -1,    -1,    32,    33,    34,    35,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    -1,    -1,    51,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    -1,    -1,    32,    33,
      34,    35,     9,    10,    11,    12,    13,    14,    15,    16,
      -1,    18,    19,    20,    21,    49,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    -1,    -1,    32,
      33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    49,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    -1,    -1,
      32,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    48,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    -1,    -1,
      32,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    48,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    -1,    -1,
      32,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    48,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    -1,    -1,
      32,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     4,    -1,    -1,    -1,    48,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    -1,     4,
      32,    33,    34,    35,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    -1,     4,    32,    33,    34,
      35,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    -1,     4,    32,    33,    34,    35,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    -1,
       4,    32,    33,    34,    35,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    -1,     4,    32,    33,
      34,    35,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    -1,    -1,    32,    33,    34,    35,     7,
      -1,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    -1,    -1,    32,    33,    34,    35,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    -1,
      -1,    32,    33,    34,    35,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,
      -1,    35,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    33,    -1,    35,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    33
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    60,    61,     0,    54,    62,    63,    64,    68,    47,
      50,    53,    66,    67,     8,     3,    22,    48,    49,    52,
      87,     3,     9,    10,    11,    30,    31,    52,    53,    55,
      56,    72,    75,    53,    67,     7,     4,    49,    72,    72,
      72,    72,    72,    72,     3,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    32,    33,    34,
      35,     5,    48,    65,    68,    88,     4,    72,    73,    74,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    69,    53,     4,    49,
       7,     5,     6,    36,    37,    38,    40,    41,    42,    45,
      46,    48,    63,    68,    70,    71,    72,    76,    78,    79,
      80,    81,    82,    84,    85,    72,    69,    72,     3,     3,
       3,    48,     3,    48,    71,    48,     6,    48,    72,    72,
      72,    72,    38,    77,     4,     4,    48,     4,     3,    36,
      71,    71,    72,     5,    72,    48,    39,    48,    86,     4,
      71,    72,     6,    43,    44,    83,    48,     4,    72,    51,
      71,    51,    69,    69
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    59,    60,    61,    61,    62,    62,    63,    64,    64,
      65,    66,    66,    67,    67,    68,    68,    68,    69,    69,
      70,    70,    70,    70,    70,    70,    70,    70,    70,    70,
      70,    70,    71,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    73,    73,
      73,    74,    74,    75,    75,    75,    77,    76,    78,    78,
      79,    80,    81,    82,    83,    83,    84,    85,    86,    86,
      87,    87,    88,    88
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     1,     1,     3,     6,     6,
       3,     3,     1,     1,     3,     1,     2,     5,     2,     0,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     2,     2,     2,     1,     1,     4,     4,     3,     1,
       0,     3,     1,     1,     1,     1,     0,     6,     7,     5,
       9,     5,     7,     7,     4,     3,     2,     2,     2,     0,
       3,     0,     2,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 115 "parser.y"
                  { (yyval.root) = new node::Root(*(yyvsp[0].decls)); }
#line 1667 "Parser.cpp"
    break;

  case 3:
#line 118 "parser.y"
                        { (yyvsp[-1].decls)->push_back((yyvsp[0].decl));    (yyval.decls) = (yyvsp[-1].decls); }
#line 1673 "Parser.cpp"
    break;

  case 4:
#line 119 "parser.y"
                        { (yyval.decls) = new node::Decls(); }
#line 1679 "Parser.cpp"
    break;

  case 5:
#line 122 "parser.y"
                        { (yyval.decl) = (yyvsp[0].varDecl); }
#line 1685 "Parser.cpp"
    break;

  case 6:
#line 123 "parser.y"
                        { (yyval.decl) = (yyvsp[0].funcDecl); }
#line 1691 "Parser.cpp"
    break;

  case 7:
#line 126 "parser.y"
                                    { (yyval.varDecl) = new node::VarDecl((yyvsp[-2].varType), (yyvsp[-1].varList)); }
#line 1697 "Parser.cpp"
    break;

  case 8:
#line 129 "parser.y"
                                                { (yyval.funcDecl) = new node::FuncDecl((yyvsp[-5].varType), *(yyvsp[-4].sval), (yyvsp[-2].args)); }
#line 1703 "Parser.cpp"
    break;

  case 9:
#line 130 "parser.y"
                                                { (yyval.funcDecl) = new node::FuncDecl((yyvsp[-5].varType), *(yyvsp[-4].sval), (yyvsp[-2].args), (yyvsp[0].funcBody)); }
#line 1709 "Parser.cpp"
    break;

  case 10:
#line 133 "parser.y"
                                        { (yyval.funcBody) = (yyvsp[-1].stms);}
#line 1715 "Parser.cpp"
    break;

  case 11:
#line 136 "parser.y"
                                    { (yyval.varList) = (yyvsp[-2].varList); (yyval.varList)->push_back((yyvsp[0].varInit)); }
#line 1721 "Parser.cpp"
    break;

  case 12:
#line 137 "parser.y"
                                    { (yyval.varList) = new node::VarList(); (yyval.varList)->push_back((yyvsp[0].varInit)); }
#line 1727 "Parser.cpp"
    break;

  case 13:
#line 140 "parser.y"
                            { (yyval.varInit) = new node::VarInit(*(yyvsp[0].sval)); }
#line 1733 "Parser.cpp"
    break;

  case 14:
#line 141 "parser.y"
                            { (yyval.varInit) = new node::VarInit(*(yyvsp[-2].sval), (yyvsp[0].expr)); }
#line 1739 "Parser.cpp"
    break;

  case 15:
#line 144 "parser.y"
                                    { (yyval.varType) = new node::VarType(type2int(*(yyvsp[0].type))); }
#line 1745 "Parser.cpp"
    break;

  case 16:
#line 145 "parser.y"
                                    { (yyval.varType) = new node::PtrType(type2int(*(yyvsp[-1].type))); }
#line 1751 "Parser.cpp"
    break;

  case 17:
#line 146 "parser.y"
                                    { (yyval.varType) = new node::ArrayType(type2int(*(yyvsp[-4].type)), (yyvsp[-1].ival)); }
#line 1757 "Parser.cpp"
    break;

  case 18:
#line 150 "parser.y"
                            { (yyval.stms) = (yyvsp[-1].stms); (yyval.stms)->push_back((yyvsp[0].stm)); }
#line 1763 "Parser.cpp"
    break;

  case 19:
#line 151 "parser.y"
                            { (yyval.stms) = new node::Stms(); }
#line 1769 "Parser.cpp"
    break;

  case 20:
#line 154 "parser.y"
                                { (yyval.stm) = new node::ExprStm((yyvsp[-1].expr)); }
#line 1775 "Parser.cpp"
    break;

  case 21:
#line 155 "parser.y"
                                { (yyval.stm) = (yyvsp[0].stm); }
#line 1781 "Parser.cpp"
    break;

  case 22:
#line 156 "parser.y"
                                { (yyval.stm) = (yyvsp[0].stm); }
#line 1787 "Parser.cpp"
    break;

  case 23:
#line 157 "parser.y"
                                { (yyval.stm) = (yyvsp[0].stm); }
#line 1793 "Parser.cpp"
    break;

  case 24:
#line 158 "parser.y"
                                { (yyval.stm) = (yyvsp[0].stm); }
#line 1799 "Parser.cpp"
    break;

  case 25:
#line 159 "parser.y"
                                { (yyval.stm) = (yyvsp[0].stm); }
#line 1805 "Parser.cpp"
    break;

  case 26:
#line 160 "parser.y"
                                { (yyval.stm) = (yyvsp[0].stm); }
#line 1811 "Parser.cpp"
    break;

  case 27:
#line 161 "parser.y"
                                { (yyval.stm) = (yyvsp[0].stm); }
#line 1817 "Parser.cpp"
    break;

  case 28:
#line 162 "parser.y"
                                { (yyval.stm) = (yyvsp[0].stm); }
#line 1823 "Parser.cpp"
    break;

  case 29:
#line 163 "parser.y"
                                { (yyval.stm) = NULL; }
#line 1829 "Parser.cpp"
    break;

  case 30:
#line 164 "parser.y"
                                { (yyval.stm) = (yyvsp[0].varDecl); }
#line 1835 "Parser.cpp"
    break;

  case 31:
#line 165 "parser.y"
                                { (yyval.stm) = (yyvsp[0].block); }
#line 1841 "Parser.cpp"
    break;

  case 32:
#line 168 "parser.y"
                          { (yyval.block) new node::Block((yyvsp[-1].stms)); }
#line 1847 "Parser.cpp"
    break;

  case 33:
#line 171 "parser.y"
                                        { (yyval.expr) = new node::BINOP((yyvsp[-2].expr), plus, (yyvsp[0].expr)); }
#line 1853 "Parser.cpp"
    break;

  case 34:
#line 172 "parser.y"
                                { (yyval.expr) = new node::BINOP((yyvsp[-2].expr), sub, (yyvsp[0].expr)); }
#line 1859 "Parser.cpp"
    break;

  case 35:
#line 173 "parser.y"
                                    { (yyval.expr) = new node::BINOP((yyvsp[-2].expr), mult, (yyvsp[0].expr)); }
#line 1865 "Parser.cpp"
    break;

  case 36:
#line 174 "parser.y"
                                { (yyval.expr) = new node::BINOP((yyvsp[-2].expr), div, (yyvsp[0].expr)); }
#line 1871 "Parser.cpp"
    break;

  case 37:
#line 175 "parser.y"
                                { (yyval.expr) = new node::BINOP((yyvsp[-2].expr), mod, (yyvsp[0].expr)); }
#line 1877 "Parser.cpp"
    break;

  case 38:
#line 176 "parser.y"
                                { (yyval.expr) = new node::BINOP((yyvsp[-2].expr), shl, (yyvsp[0].expr)); }
#line 1883 "Parser.cpp"
    break;

  case 39:
#line 177 "parser.y"
                                    { (yyval.expr) = new node::BINOP((yyvsp[-2].expr), shr, (yyvsp[0].expr)); }
#line 1889 "Parser.cpp"
    break;

  case 40:
#line 178 "parser.y"
                                { (yyval.expr) = new node::BINOP((yyvsp[-2].expr), lt, (yyvsp[0].expr)); }
#line 1895 "Parser.cpp"
    break;

  case 41:
#line 179 "parser.y"
                                { (yyval.expr) = new node::BINOP((yyvsp[-2].expr), le, (yyvsp[0].expr)); }
#line 1901 "Parser.cpp"
    break;

  case 42:
#line 180 "parser.y"
                                { (yyval.expr) = new node::BINOP((yyvsp[-2].expr), eq, (yyvsp[0].expr)); }
#line 1907 "Parser.cpp"
    break;

  case 43:
#line 181 "parser.y"
                                { (yyval.expr) = new node::BINOP((yyvsp[-2].expr), ge, (yyvsp[0].expr)); }
#line 1913 "Parser.cpp"
    break;

  case 44:
#line 182 "parser.y"
                                { (yyval.expr) = new node::BINOP((yyvsp[-2].expr), gt, (yyvsp[0].expr)); }
#line 1919 "Parser.cpp"
    break;

  case 45:
#line 183 "parser.y"
                                { (yyval.expr) = new node::BINOP((yyvsp[-2].expr), ne, (yyvsp[0].expr)); }
#line 1925 "Parser.cpp"
    break;

  case 46:
#line 184 "parser.y"
                                 { (yyval.expr) = new node::BINOP((yyvsp[-2].expr), equ, (yyvsp[0].expr)); }
#line 1931 "Parser.cpp"
    break;

  case 47:
#line 185 "parser.y"
                                    { (yyval.expr) = new node::BINOP((yyvsp[-2].expr), addeq, (yyvsp[0].expr)); }
#line 1937 "Parser.cpp"
    break;

  case 48:
#line 186 "parser.y"
                                    { (yyval.expr) = new node::BINOP((yyvsp[-2].expr), subeq, (yyvsp[0].expr)); }
#line 1943 "Parser.cpp"
    break;

  case 49:
#line 187 "parser.y"
                                    { (yyval.expr) = new node::BINOP((yyvsp[-2].expr), diveq, (yyvsp[0].expr)); }
#line 1949 "Parser.cpp"
    break;

  case 50:
#line 188 "parser.y"
                                    { (yyval.expr) = new node::BINOP((yyvsp[-2].expr), muleq, (yyvsp[0].expr)); }
#line 1955 "Parser.cpp"
    break;

  case 51:
#line 189 "parser.y"
                                    { (yyval.expr) = new node::BINOP((yyvsp[-2].expr), modeq, (yyvsp[0].expr)); }
#line 1961 "Parser.cpp"
    break;

  case 52:
#line 190 "parser.y"
                                    { (yyval.expr) = new node::BINOP((yyvsp[-2].expr), shleq, (yyvsp[0].expr)); }
#line 1967 "Parser.cpp"
    break;

  case 53:
#line 191 "parser.y"
                                    { (yyval.expr) = new node::BINOP((yyvsp[-2].expr), shreq, (yyvsp[0].expr)); }
#line 1973 "Parser.cpp"
    break;

  case 54:
#line 192 "parser.y"
                                { (yyval.expr) = new node::BINOP((yyvsp[-2].expr), and, (yyvsp[0].expr)); }
#line 1979 "Parser.cpp"
    break;

  case 55:
#line 193 "parser.y"
                                    { (yyval.expr) = new node::BINOP((yyvsp[-2].expr), band, (yyvsp[0].expr)); }
#line 1985 "Parser.cpp"
    break;

  case 56:
#line 194 "parser.y"
                                { (yyval.expr) = new node::BINOP((yyvsp[-2].expr), or, (yyvsp[0].expr)); }
#line 1991 "Parser.cpp"
    break;

  case 57:
#line 195 "parser.y"
                                { (yyval.expr) = new node::BINOP((yyvsp[-2].expr), bor, (yyvsp[0].expr)); }
#line 1997 "Parser.cpp"
    break;

  case 58:
#line 196 "parser.y"
                                { (yyval.expr) = (yyvsp[-1].expr); }
#line 2003 "Parser.cpp"
    break;

  case 59:
#line 197 "parser.y"
                                    { (yyval.expr) = new node::SOP((yyvsp[0].expr), splus); }
#line 2009 "Parser.cpp"
    break;

  case 60:
#line 198 "parser.y"
                                    { (yyval.expr) = new node::SOP((yyvsp[0].expr), ssub); }
#line 2015 "Parser.cpp"
    break;

  case 61:
#line 199 "parser.y"
                                    { (yyval.expr) = new node::SOP((yyvsp[0].expr), not); }
#line 2021 "Parser.cpp"
    break;

  case 62:
#line 200 "parser.y"
                                    { (yyval.expr) = new node::SOP((yyvsp[0].expr), smult); }
#line 2027 "Parser.cpp"
    break;

  case 63:
#line 201 "parser.y"
                                    { (yyval.expr) = new node::SOP((yyvsp[0].expr), sbnot); }
#line 2033 "Parser.cpp"
    break;

  case 64:
#line 202 "parser.y"
                                   { (yyval.expr) = (yyvsp[0].constant); }
#line 2039 "Parser.cpp"
    break;

  case 65:
#line 203 "parser.y"
                                { (yyval.expr) = new node::ID(*(yyvsp[0].sval)); }
#line 2045 "Parser.cpp"
    break;

  case 66:
#line 204 "parser.y"
                                { (yyval.expr) = new node::ArrayCall(*(yyvsp[-3].sval), (yyvsp[-1].expr)); }
#line 2051 "Parser.cpp"
    break;

  case 67:
#line 205 "parser.y"
                                { (yyval.expr) = new node::FuncCall(*(yyvsp[-3].sval), (yyvsp[-1].exprList)); }
#line 2057 "Parser.cpp"
    break;

  case 68:
#line 208 "parser.y"
                                                                                                        {  (yyval.exprList) = (yyvsp[-2].exprList); (yyval.exprList)->push_back((yyvsp[0].expr));   }
#line 2063 "Parser.cpp"
    break;

  case 69:
#line 209 "parser.y"
                                                                                                        {  (yyval.exprList) = new node::ExprList(); (yyval.exprList)->push_back((yyvsp[0].expr));   }
#line 2069 "Parser.cpp"
    break;

  case 70:
#line 210 "parser.y"
                                                                                                                                        {  (yyval.exprList) = new node::ExprList();   }
#line 2075 "Parser.cpp"
    break;

  case 71:
#line 213 "parser.y"
                                                                                                        {  (yyval.exprList) = (yyvsp[-2].exprList); (yyval.exprList)->push_back((yyvsp[0].expr));   }
#line 2081 "Parser.cpp"
    break;

  case 72:
#line 214 "parser.y"
                                                                                                        {  (yyval.exprList) = new node::ExprList(); (yyval.exprList)->push_back((yyvsp[0].expr));   }
#line 2087 "Parser.cpp"
    break;

  case 73:
#line 217 "parser.y"
                            { (yyval.constant) = new node::Int((yyvsp[0].ival)); }
#line 2093 "Parser.cpp"
    break;

  case 74:
#line 218 "parser.y"
                            { (yyval.constant) = new node::Char((yyvsp[0].cval)); }
#line 2099 "Parser.cpp"
    break;

  case 75:
#line 219 "parser.y"
                            { (yyval.constant) = new node::Float((yyvsp[0].dval)); }
#line 2105 "Parser.cpp"
    break;

  case 76:
#line 222 "parser.y"
                                { (yyval.Stm) = new node::ReturnStm((yyvsp[-1].expr)); }
#line 2111 "Parser.cpp"
    break;

  case 77:
#line 223 "parser.y"
                                { (yyval.stm) = new node::ReturnStm(NULL); }
#line 2117 "Parser.cpp"
    break;

  case 78:
#line 226 "parser.y"
                                            { (yyval.stm) = new node::IfStm((yyvsp[-4].expr), (yyvsp[-2].block), (yyvsp[0].block), true); }
#line 2123 "Parser.cpp"
    break;

  case 79:
#line 227 "parser.y"
                                            { (yyval.stm) = new node::IfStm((yyvsp[-2].expr), (yyvsp[0].block), NULL, false); }
#line 2129 "Parser.cpp"
    break;

  case 80:
#line 229 "parser.y"
                                                        { (yyval.stm) = new node::ForStm((yyvsp[-6].expr), (yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].block)); }
#line 2135 "Parser.cpp"
    break;

  case 81:
#line 231 "parser.y"
                                    { (yyval.stm) = new node::WhileStm((yyvsp[-2].expr), (yyvsp[0].block)); }
#line 2141 "Parser.cpp"
    break;

  case 82:
#line 234 "parser.y"
                                            { (yyval.stm) = new node::DoStm((yyvsp[-2].expr), (yyvsp[-5].block)); }
#line 2147 "Parser.cpp"
    break;

  case 83:
#line 237 "parser.y"
                                            { (yyval.stm) = new node::SwitchStm((yyvsp[-4].expr), (yyvsp[-1].cases)); }
#line 2153 "Parser.cpp"
    break;

  case 84:
#line 240 "parser.y"
                                            { (yyval.stm) = new node::CaseStm((yyvsp[-2].expr), (yyvsp[0].stms)); }
#line 2159 "Parser.cpp"
    break;

  case 85:
#line 241 "parser.y"
                                       { (yyval.stm) = new node::CaseStm(NULL, (yyvsp[0].stms)); }
#line 2165 "Parser.cpp"
    break;

  case 86:
#line 244 "parser.y"
                            { (yyval.stm) = new node::ContinueStm(); }
#line 2171 "Parser.cpp"
    break;

  case 87:
#line 247 "parser.y"
                            { (yyval.stm) = new node::BreakStm(); }
#line 2177 "Parser.cpp"
    break;

  case 88:
#line 250 "parser.y"
                            { (yyval.cases) = (yyvsp[-1].cases); (yyval.cases)->push_back((yyvsp[0].stm)); }
#line 2183 "Parser.cpp"
    break;

  case 89:
#line 251 "parser.y"
                            { (yyval.cases) = new node::Cases(); }
#line 2189 "Parser.cpp"
    break;

  case 90:
#line 254 "parser.y"
                            { (yyval.args) = (yyvsp[-2].args); (yyval.args)->push_back((yyvsp[0].arg)); }
#line 2195 "Parser.cpp"
    break;

  case 91:
#line 255 "parser.y"
                            { (yyval.args) = new node::Args(); }
#line 2201 "Parser.cpp"
    break;

  case 92:
#line 258 "parser.y"
                            { (yyval.arg) = new node::Args((yyvsp[-1].varType), *(yyvsp[0].sval)); }
#line 2207 "Parser.cpp"
    break;

  case 93:
#line 259 "parser.y"
                            { (yyval.arg) = new node::Args((yyvsp[0].varType)); }
#line 2213 "Parser.cpp"
    break;


#line 2217 "Parser.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 262 "parser.y"
