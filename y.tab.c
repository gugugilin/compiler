/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "hw1.y" /* yacc.c:339  */

#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>  
#include <math.h>
#include <map>
#include "lex.yy.c"
#define Trace(t) {printf("[%d]:%s",linenum,t);}
using namespace std;
list<string> scope_name;
map<string,Hash> scope_list;
string current_scop;
int idcount;
void yyerror(char * msg);
void scope_init(){
    string name="goble";
    Hash temp;
    scope_name.push_front(name);
    scope_list[name]=temp;
    current_scop="goble";
    idcount=0;
}
string get_scope(){
    return scope_name.front();
}

int inser_data(int idcount,string idname,string idvalue,int idtype, int idattrubutes){
    map<string,Hash>::iterator temp=scope_list.find(current_scop);
    Hash temp1=temp->second;
    if (temp1.lookout(idname)!=-1)
    {
        return -1;
    }
    scope_list.erase(temp);
    id_node new_data(idcount,idname,idtype,idattrubutes,idvalue);
    temp1.insert(new_data);
    scope_list[current_scop]=temp1;
    return 1;
}
void update_data(string name,string value){
    map<string,Hash>::iterator temp=scope_list.find(current_scop);
    Hash temp1=temp->second;
    temp1.update(name,value);
}
id_node lookout_data(string name){
    map<string,Hash>::iterator temp=scope_list.find(current_scop);
    id_node new_data(1,name,-1,-1,"None");
    Hash temp1=temp->second;
    if (temp1.lookout(name)==-1)
    {
        return new_data;
    }
    return temp1.get_data(name);
}
void insert_scope(string name){
    Hash temp;
    scope_name.push_front(name);
    scope_list[name]=temp;
    current_scop=name;
}
typedef union YYSTYPE id_union;
id_union create_idnode(int Attrubutes,int IDtype,int IDnumber,const char * IDvalue)
{
    
    id_union temp;
    temp.idnode.IDAttributes=Attrubutes;
    temp.idnode.IDtype=IDtype;
    temp.idnode.IDnumber=IDnumber;
    temp.idnode.IDvalue=IDvalue;
    return temp;
}



#line 143 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    BOOL = 258,
    BREAK = 259,
    CASE = 260,
    CONST = 261,
    CONTINUE = 262,
    DEFAULT = 263,
    ELSE = 264,
    FOR = 265,
    FUNC = 266,
    GO = 267,
    IF = 268,
    IMPORT = 269,
    INT = 270,
    NIL = 271,
    PRINT = 272,
    PRINTLN = 273,
    REAL = 274,
    RETURN = 275,
    STRING = 276,
    STRUCT = 277,
    SWITCH = 278,
    TYPE = 279,
    VAR = 280,
    VOID = 281,
    WHILE = 282,
    READ = 283,
    ARITHMETIC_ADD = 284,
    ARITHMETIC_SUB = 285,
    ARITHMETIC_MUL = 286,
    ARITHMETIC_DIV = 287,
    RELATIONAL_LEAST = 288,
    RELATIONAL_LEAST_EQ = 289,
    RELATIONAL_BIG_EQ = 290,
    RELATIONAL_BIG = 291,
    RELATIONAL_EQ = 292,
    RELATIONAL_NEQ = 293,
    COMPOUND_OPERATORS_ADD = 294,
    COMPOUND_OPERATORS_SUB = 295,
    COMPOUND_OPERATORS_MUL = 296,
    COMPOUND_OPERATORS_DIV = 297,
    BOOLEAN_CONSTANTS_FALSE = 298,
    BOOLEAN_CONSTANTS_TRUE = 299,
    AND = 300,
    NOT = 301,
    OR = 302,
    COMMENTS_ONE = 303,
    COMMENTS_START_MUL = 304,
    COMMENTS_END_MUL = 305,
    COMMA = 306,
    COLON = 307,
    SEMICOLON = 308,
    LEFT_PARENTHESE = 309,
    RIGHT_PARENTHESE = 310,
    LEFT_SQUARE_BRACKETS = 311,
    RIGHT_SQUARE_BRACKETS = 312,
    LEFT_BRACKETS = 313,
    RIGHT_BRACKETS = 314,
    EXPONENTIATION = 315,
    REMAINDER = 316,
    LOGICAL = 317,
    ASSIGNMENT = 318,
    INTEGER_CONSTANTS = 319,
    IDENTIFIER = 320,
    REAL_CONSTANTS = 321,
    STRING_CONSTANTS = 322,
    ERROR_SIMPLE = 323,
    UMINUS = 324,
    UADD = 325
  };
#endif
/* Tokens.  */
#define BOOL 258
#define BREAK 259
#define CASE 260
#define CONST 261
#define CONTINUE 262
#define DEFAULT 263
#define ELSE 264
#define FOR 265
#define FUNC 266
#define GO 267
#define IF 268
#define IMPORT 269
#define INT 270
#define NIL 271
#define PRINT 272
#define PRINTLN 273
#define REAL 274
#define RETURN 275
#define STRING 276
#define STRUCT 277
#define SWITCH 278
#define TYPE 279
#define VAR 280
#define VOID 281
#define WHILE 282
#define READ 283
#define ARITHMETIC_ADD 284
#define ARITHMETIC_SUB 285
#define ARITHMETIC_MUL 286
#define ARITHMETIC_DIV 287
#define RELATIONAL_LEAST 288
#define RELATIONAL_LEAST_EQ 289
#define RELATIONAL_BIG_EQ 290
#define RELATIONAL_BIG 291
#define RELATIONAL_EQ 292
#define RELATIONAL_NEQ 293
#define COMPOUND_OPERATORS_ADD 294
#define COMPOUND_OPERATORS_SUB 295
#define COMPOUND_OPERATORS_MUL 296
#define COMPOUND_OPERATORS_DIV 297
#define BOOLEAN_CONSTANTS_FALSE 298
#define BOOLEAN_CONSTANTS_TRUE 299
#define AND 300
#define NOT 301
#define OR 302
#define COMMENTS_ONE 303
#define COMMENTS_START_MUL 304
#define COMMENTS_END_MUL 305
#define COMMA 306
#define COLON 307
#define SEMICOLON 308
#define LEFT_PARENTHESE 309
#define RIGHT_PARENTHESE 310
#define LEFT_SQUARE_BRACKETS 311
#define RIGHT_SQUARE_BRACKETS 312
#define LEFT_BRACKETS 313
#define RIGHT_BRACKETS 314
#define EXPONENTIATION 315
#define REMAINDER 316
#define LOGICAL 317
#define ASSIGNMENT 318
#define INTEGER_CONSTANTS 319
#define IDENTIFIER 320
#define REAL_CONSTANTS 321
#define STRING_CONSTANTS 322
#define ERROR_SIMPLE 323
#define UMINUS 324
#define UADD 325

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 80 "hw1.y" /* yacc.c:355  */

    bool bool_types;
    int int_types;
    double real_types;
    const char* string_types;
    struct node{
        int IDAttributes;
        int IDtype;
        int IDnumber;
        const char* IDvalue;
        const char* IDname;
    }idnode;

#line 337 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 354 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  41
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   337

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  71
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  85
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  151

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   325

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   182,   182,   186,   190,   191,   198,   199,   201,   206,
     228,   244,   245,   246,   247,   248,   258,   259,   260,   261,
     263,   283,   302,   302,   304,   305,   308,   324,   332,   338,
     349,   353,   357,   358,   359,   363,   364,   365,   370,   373,
     376,   377,   378,   379,   380,   381,   382,   383,   384,   402,
     403,   404,   405,   406,   407,   408,   409,   410,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     436,   437,   438,   439,   440,   441,   442,   443,   444,   445,
     446,   447,   449,   452,   455,   456
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "BOOL", "BREAK", "CASE", "CONST",
  "CONTINUE", "DEFAULT", "ELSE", "FOR", "FUNC", "GO", "IF", "IMPORT",
  "INT", "NIL", "PRINT", "PRINTLN", "REAL", "RETURN", "STRING", "STRUCT",
  "SWITCH", "TYPE", "VAR", "VOID", "WHILE", "READ", "ARITHMETIC_ADD",
  "ARITHMETIC_SUB", "ARITHMETIC_MUL", "ARITHMETIC_DIV", "RELATIONAL_LEAST",
  "RELATIONAL_LEAST_EQ", "RELATIONAL_BIG_EQ", "RELATIONAL_BIG",
  "RELATIONAL_EQ", "RELATIONAL_NEQ", "COMPOUND_OPERATORS_ADD",
  "COMPOUND_OPERATORS_SUB", "COMPOUND_OPERATORS_MUL",
  "COMPOUND_OPERATORS_DIV", "BOOLEAN_CONSTANTS_FALSE",
  "BOOLEAN_CONSTANTS_TRUE", "AND", "NOT", "OR", "COMMENTS_ONE",
  "COMMENTS_START_MUL", "COMMENTS_END_MUL", "COMMA", "COLON", "SEMICOLON",
  "LEFT_PARENTHESE", "RIGHT_PARENTHESE", "LEFT_SQUARE_BRACKETS",
  "RIGHT_SQUARE_BRACKETS", "LEFT_BRACKETS", "RIGHT_BRACKETS",
  "EXPONENTIATION", "REMAINDER", "LOGICAL", "ASSIGNMENT",
  "INTEGER_CONSTANTS", "IDENTIFIER", "REAL_CONSTANTS", "STRING_CONSTANTS",
  "ERROR_SIMPLE", "UMINUS", "UADD", "$accept", "start_symbol", "program",
  "body", "statements", "statement", "type", "SAVE_IDENTIFERS",
  "IDENTIFERS", "declarations", "declaration", "arrays_variable",
  "arrays_declaration", "consts_declaration", "Variables_declaration",
  "constant_exp", "expression", "const_index_expression",
  "index_expression", "const_number_expression", "number_expression",
  "const_bool_expression", "bool_expression", "commponent", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325
};
# endif

#define YYPACT_NINF -80

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-80)))

#define YYTABLE_NINF -58

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       9,   -56,    85,    85,    85,   -56,   -52,   -80,    41,   -80,
     -80,   -80,     9,   -44,     9,    -3,   -19,   -80,   -80,   -80,
     -80,   -18,   111,   111,   -80,   -80,   117,   117,   -80,   -80,
     -80,    13,   -80,   -80,   191,   -12,   -80,   -80,   -80,    89,
     -80,   -80,   -80,     9,   111,    85,   -80,   -80,    85,    90,
     111,   -80,   -80,   191,   -80,   181,    62,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   117,   117,
     -80,   -80,   -80,   -80,   137,    -9,    16,   218,   -80,   -80,
     111,   111,   -80,   -80,   143,   143,   -80,   -80,   288,   223,
      -7,   228,   201,   -80,   -80,   -24,   -24,    21,    21,   218,
     218,   218,   218,   218,   218,   -80,   -80,    32,   111,    34,
     -80,    90,   -80,   235,   241,   288,   -80,   208,   145,   137,
     137,   137,   137,   137,   137,   111,   111,   111,   111,   111,
     143,   143,   214,   159,   -80,   250,   -80,   -80,   -80,   -80,
     -80,   -80,   -80,   255,   260,   267,   273,   277,   -80,    48,
     -80
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       8,     0,     0,     0,    14,     0,     0,    21,     0,     2,
       3,     4,     8,     0,     5,    23,     0,    31,    25,    24,
      20,     0,     0,     0,    80,    81,     0,     0,    82,    83,
      37,    84,    85,    11,    35,    36,    57,    12,    15,     0,
      13,     1,     7,     8,     0,     0,     6,    22,     0,     0,
       0,    56,    55,     0,    79,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      16,    17,    18,    19,     0,    30,     0,    39,     9,    10,
       0,     0,    68,    69,     0,     0,    34,    28,    32,     0,
      33,    48,     0,    49,    76,    50,    51,    52,    53,    71,
      72,    73,    70,    74,    75,    54,    77,    78,     0,     0,
      38,     0,    26,    47,    46,     0,    67,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    29,    40,    64,    59,    60,    61,
      58,    62,    63,    41,    42,    43,    44,    45,    65,    66,
      27
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -80,   -80,   -80,   -80,    11,   -80,   -39,    92,     4,    17,
     -80,    68,   -80,   -80,   -80,    -6,    27,   -80,   -80,   -21,
      -2,   -79,    44,   -35
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     8,     9,    10,    46,    12,    75,    21,    31,    43,
      15,    32,    17,    18,    19,    87,    33,   109,    76,   115,
      89,    90,    35,    36
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      34,    34,    34,     1,    13,   116,   118,    59,    60,    20,
      40,    11,    44,     7,    91,     1,    13,    14,    13,    45,
      51,    52,     5,    42,    53,    55,     2,     3,    88,     4,
      37,    38,    47,    68,     5,    69,    67,     6,   130,    91,
     131,    41,    77,    34,    48,    49,    34,    13,    92,    91,
      91,   148,   149,   110,   111,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,    53,    53,    16,    44,
      54,    56,    78,   112,     7,    79,    91,    68,   113,   114,
      16,    67,    16,   117,    91,    91,    91,    91,    91,    91,
      88,   133,    70,   130,   150,    91,    91,    39,   137,   138,
     139,   140,   141,   142,    71,   134,   132,    68,    72,    69,
      73,    16,   106,   107,    22,    23,     0,    94,     0,    80,
      81,     0,     0,   143,   144,   145,   146,   147,    24,    25,
       0,    26,     0,    82,    83,     0,    84,     0,     0,    27,
      22,    23,     0,     0,    85,    74,    22,    23,     0,    28,
       7,    29,    30,     0,    28,     7,    29,    86,     0,     0,
      24,    25,    70,    26,     0,    50,    80,    81,     0,     0,
       0,    27,    80,    81,    71,    28,     7,    29,    72,     0,
      73,    28,     7,    29,     0,     0,    82,    83,     0,    84,
     130,   108,   131,     0,     0,     0,     0,    85,     0,     0,
     136,    28,     7,    29,     0,     0,     0,    28,     7,    29,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      57,    58,    59,    60,     0,     0,    93,   125,   126,   127,
     128,    67,     0,    57,    58,    59,    60,    57,    58,    59,
      60,    67,   125,   126,   127,   128,    93,   -57,   -57,   -57,
     -57,    67,     0,   135,   -56,   -56,   -56,   -56,   129,   135,
     -55,   -55,   -55,   -55,    67,     0,     0,     0,    67,   -49,
     -49,   -49,   -49,   129,   -50,   -50,    59,    60,   -57,   -51,
     -51,    59,    60,     0,     0,   -56,   -52,   -52,   -52,   -52,
       0,   -55,   -53,   -53,   -53,   -53,   -54,   -54,   -54,   -54,
     -49,     0,     0,     0,     0,    67,     0,     0,     0,     0,
      67,   119,   120,   121,   122,   123,   124,    67,     0,     0,
       0,     0,     0,    67,     0,     0,     0,   -54
};

static const yytype_int16 yycheck[] =
{
       2,     3,     4,     6,     0,    84,    85,    31,    32,    65,
       6,     0,    56,    65,    49,     6,    12,     0,    14,    63,
      22,    23,    25,    12,    26,    27,    17,    18,    49,    20,
       3,     4,    15,    45,    25,    47,    60,    28,    45,    74,
      47,     0,    44,    45,    63,    63,    48,    43,    50,    84,
      85,   130,   131,    74,    63,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,     0,    56,
      26,    27,    45,    57,    65,    48,   111,    45,    80,    81,
      12,    60,    14,    85,   119,   120,   121,   122,   123,   124,
     111,    57,     3,    45,   133,   130,   131,     5,   119,   120,
     121,   122,   123,   124,    15,   111,   108,    45,    19,    47,
      21,    43,    68,    69,    29,    30,    -1,    55,    -1,    29,
      30,    -1,    -1,   125,   126,   127,   128,   129,    43,    44,
      -1,    46,    -1,    43,    44,    -1,    46,    -1,    -1,    54,
      29,    30,    -1,    -1,    54,    56,    29,    30,    -1,    64,
      65,    66,    67,    -1,    64,    65,    66,    67,    -1,    -1,
      43,    44,     3,    46,    -1,    54,    29,    30,    -1,    -1,
      -1,    54,    29,    30,    15,    64,    65,    66,    19,    -1,
      21,    64,    65,    66,    -1,    -1,    43,    44,    -1,    46,
      45,    54,    47,    -1,    -1,    -1,    -1,    54,    -1,    -1,
      55,    64,    65,    66,    -1,    -1,    -1,    64,    65,    66,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      29,    30,    31,    32,    -1,    -1,    55,    29,    30,    31,
      32,    60,    -1,    29,    30,    31,    32,    29,    30,    31,
      32,    60,    29,    30,    31,    32,    55,    29,    30,    31,
      32,    60,    -1,    55,    29,    30,    31,    32,    60,    55,
      29,    30,    31,    32,    60,    -1,    -1,    -1,    60,    29,
      30,    31,    32,    60,    29,    30,    31,    32,    60,    29,
      30,    31,    32,    -1,    -1,    60,    29,    30,    31,    32,
      -1,    60,    29,    30,    31,    32,    29,    30,    31,    32,
      60,    -1,    -1,    -1,    -1,    60,    -1,    -1,    -1,    -1,
      60,    33,    34,    35,    36,    37,    38,    60,    -1,    -1,
      -1,    -1,    -1,    60,    -1,    -1,    -1,    60
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,    17,    18,    20,    25,    28,    65,    72,    73,
      74,    75,    76,    79,    80,    81,    82,    83,    84,    85,
      65,    78,    29,    30,    43,    44,    46,    54,    64,    66,
      67,    79,    82,    87,    91,    93,    94,    87,    87,    78,
      79,     0,    75,    80,    56,    63,    75,    80,    63,    63,
      54,    91,    91,    91,    93,    91,    93,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    60,    45,    47,
       3,    15,    19,    21,    56,    77,    89,    91,    87,    87,
      29,    30,    43,    44,    46,    54,    67,    86,    90,    91,
      92,    94,    91,    55,    55,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    93,    93,    54,    88,
      90,    63,    57,    91,    91,    90,    92,    91,    92,    33,
      34,    35,    36,    37,    38,    29,    30,    31,    32,    60,
      45,    47,    91,    57,    86,    55,    55,    90,    90,    90,
      90,    90,    90,    91,    91,    91,    91,    91,    92,    92,
      77
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    71,    72,    73,    74,    74,    75,    75,    75,    76,
      76,    76,    76,    76,    76,    76,    77,    77,    77,    77,
      78,    79,    80,    80,    81,    81,    82,    83,    84,    85,
      85,    85,    86,    86,    86,    87,    87,    87,    88,    89,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    94,    94,    94,    94
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     2,     2,     0,     3,
       3,     2,     2,     2,     1,     2,     1,     1,     1,     1,
       1,     1,     2,     0,     1,     1,     4,     6,     4,     5,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     3,     2,     2,     1,     3,
       3,     3,     3,     3,     3,     2,     2,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     1,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       1,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
            /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
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
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

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
      int yyn = yypact[*yyssp];
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
          yyp++;
          yyformat++;
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

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
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
#line 183 "hw1.y" /* yacc.c:1646  */
    {
                    Trace("Reducing to start_symbol\n");
                }
#line 1594 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 187 "hw1.y" /* yacc.c:1646  */
    {
                    Trace("Reducing to program\n");
                }
#line 1602 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 192 "hw1.y" /* yacc.c:1646  */
    {
                    Trace("Reducing to body\n");
                }
#line 1610 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 201 "hw1.y" /* yacc.c:1646  */
    {
                    Trace("Reducing to statements\n");
                }
#line 1618 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 206 "hw1.y" /* yacc.c:1646  */
    {
                    //if IDAttributes of IDENTIFERS is 1 than return 1 to expression error
                    if((yyvsp[-2].idnode).IDAttributes==CONST_ATTRIBUTE)
                    {
                        yyerror("const variables can't change\n");
                        return 1;
                    }
                    if((yyvsp[-2].idnode).IDAttributes==ARRAY_ATTRIBUTE)
                    {
                        yyerror("It's array variables\n");
                        return 1;
                    }
                    if((yyvsp[-2].idnode).IDtype!=(yyvsp[0].idnode).IDtype){
                        if(!(((yyvsp[-2].idnode).IDtype==INTTYPE&&(yyvsp[0].idnode).IDtype==REALTYPE)||((yyvsp[0].idnode).IDtype==INTTYPE&&(yyvsp[-2].idnode).IDtype==REALTYPE)))
                        {
                            yyerror("can't convert the type\n");
                            return 1;
                        }
                    }
                    update_data((yyvsp[-2].idnode).IDname,(yyvsp[0].idnode).IDvalue);
                    
                }
#line 1645 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 228 "hw1.y" /* yacc.c:1646  */
    {
                    //if IDAttributes of IDENTIFERS is 1 than return 1 to expression error
                    if((yyvsp[-2].idnode).IDAttributes==CONST_ATTRIBUTE)
                    {
                        yyerror("const variables can't change\n");
                        return 1;
                    }
                    if((yyvsp[-2].idnode).IDtype!=(yyvsp[0].idnode).IDtype){
                        if(!(((yyvsp[-2].idnode).IDtype==INTTYPE&&(yyvsp[0].idnode).IDtype==REALTYPE)||((yyvsp[0].idnode).IDtype==INTTYPE&&(yyvsp[-2].idnode).IDtype==REALTYPE)))
                        {
                            yyerror("can't convert the type\n");
                            return 1;
                        }
                    }
                    update_data((yyvsp[-2].idnode).IDname,(yyvsp[0].idnode).IDvalue);
                }
#line 1666 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 244 "hw1.y" /* yacc.c:1646  */
    {printf("%s ",(yyvsp[0].idnode).IDvalue);}
#line 1672 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 245 "hw1.y" /* yacc.c:1646  */
    {printf(" %s \n",(yyvsp[0].idnode).IDvalue);}
#line 1678 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 249 "hw1.y" /* yacc.c:1646  */
    {
                    (yyval.idnode)=(yyvsp[0].idnode);
                    Trace("Reducing to statement\n");
                }
#line 1687 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 258 "hw1.y" /* yacc.c:1646  */
    {(yyval.int_types)=(yyvsp[0].int_types);}
#line 1693 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 259 "hw1.y" /* yacc.c:1646  */
    {(yyval.int_types)=(yyvsp[0].int_types);}
#line 1699 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 260 "hw1.y" /* yacc.c:1646  */
    {(yyval.int_types)=(yyvsp[0].int_types);}
#line 1705 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 261 "hw1.y" /* yacc.c:1646  */
    {(yyval.int_types)=(yyvsp[0].int_types);}
#line 1711 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 263 "hw1.y" /* yacc.c:1646  */
    {
                //if find the Id in table than return 1 to expression error
                //else not do anything
                union YYSTYPE temp;
                id_node temp_id = lookout_data((yyvsp[0].string_types));
                if (temp_id.get_IDAttributes()==ERROR_ATTRIBUTE)
                {
                    temp.idnode.IDAttributes=CONST_ATTRIBUTE;
                    temp.idnode.IDtype=0;
                    temp.idnode.IDnumber=1;
                    temp.idnode.IDvalue="None";
                    temp.idnode.IDname=temp_id.get_IDname().c_str();
                    (yyval.idnode)=temp.idnode;
                }
                else{
                    yyerror("redeclaration error");
                    return 1;
                }
                }
#line 1735 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 283 "hw1.y" /* yacc.c:1646  */
    {
                // must find the value and the attrubutes to ASSIGNMENT in table
                // if not find return 1 to expression error
                union YYSTYPE temp;
                id_node temp_id = lookout_data((yyvsp[0].string_types));
                if (temp_id.get_IDAttributes()==ERROR_ATTRIBUTE)
                {
                    yyerror("not define declaration");
                    return 1;
                }
                temp.idnode.IDAttributes=temp_id.get_IDAttributes();
                temp.idnode.IDtype=temp_id.get_IDtype();
                temp.idnode.IDnumber=temp_id.get_IDnumber();
                temp.idnode.IDvalue=temp_id.get_IDvalue().c_str();
                temp.idnode.IDname=temp_id.get_IDname().c_str();
                (yyval.idnode)=temp.idnode;
                }
#line 1757 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 309 "hw1.y" /* yacc.c:1646  */
    {
                    if ((yyvsp[-3].idnode).IDAttributes!=ARRAY_ATTRIBUTE){
                        yyerror("not ARRAY_type");
                        return 1;
                    }
                    if ((yyvsp[-1].int_types)<=(yyvsp[-3].idnode).IDnumber&& (yyvsp[-1].int_types)>=0){
                        (yyval.idnode)=(yyvsp[-3].idnode);
                    }
                    else{ 
                        printf("xd:%d %d\n",(yyvsp[-3].idnode).IDnumber,(yyvsp[-1].int_types));
                        yyerror("ARRAY index error");
                        return 1;
                    }
                }
#line 1776 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 325 "hw1.y" /* yacc.c:1646  */
    {
                //if SAVE_IDENTIFERS not return 1 to expression error than creat the item in table
                    inser_data((yyvsp[-2].int_types),(yyvsp[-4].idnode).IDname,"None",(yyvsp[0].int_types),ARRAY_ATTRIBUTE);
                }
#line 1785 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 332 "hw1.y" /* yacc.c:1646  */
    {
                    inser_data(1,(yyvsp[-2].idnode).IDname,(yyvsp[0].idnode).IDvalue,(yyvsp[0].idnode).IDtype,CONST_ATTRIBUTE);
                    printf("Const_declaration:%s\n",(yyvsp[0].idnode).IDvalue);
                }
#line 1794 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 338 "hw1.y" /* yacc.c:1646  */
    {
                    //if SAVE_IDENTIFERS not return 1 to expression error constant_exp is pass
                    //than creat the item in table
                    if ((yyvsp[-2].int_types)!=(yyvsp[0].idnode).IDtype)
                    {
                        yyerror("type not match");
                        return 1;
                    }
                    inser_data(1,(yyvsp[-3].idnode).IDname,(yyvsp[0].idnode).IDvalue,(yyvsp[-2].int_types),VAR_ATTRIBUTE);
                    printf("Variables_declaration:%s\n",(yyvsp[0].idnode).IDvalue);
                }
#line 1810 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 349 "hw1.y" /* yacc.c:1646  */
    {
                    inser_data(1,(yyvsp[-1].idnode).IDname,"None",(yyvsp[0].int_types),VAR_ATTRIBUTE);
                    printf("Const_declaration:%s\n",(yyvsp[-1].idnode));
                }
#line 1819 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 357 "hw1.y" /* yacc.c:1646  */
    {(yyval.idnode)=create_idnode(CONST_ATTRIBUTE,REALTYPE,1,std::to_string((yyvsp[0].real_types)).c_str()).idnode;}
#line 1825 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 358 "hw1.y" /* yacc.c:1646  */
    {(yyval.idnode)=create_idnode(CONST_ATTRIBUTE,BOOLTYPE,1,std::to_string((yyvsp[0].bool_types)).c_str()).idnode;}
#line 1831 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 359 "hw1.y" /* yacc.c:1646  */
    {(yyval.idnode)=create_idnode(CONST_ATTRIBUTE,STRINGTYPE,1,(yyvsp[0].string_types)).idnode;}
#line 1837 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 363 "hw1.y" /* yacc.c:1646  */
    {(yyval.idnode)=create_idnode(CONST_ATTRIBUTE,REALTYPE,1,std::to_string((yyvsp[0].real_types)).c_str()).idnode;}
#line 1843 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 364 "hw1.y" /* yacc.c:1646  */
    {(yyval.idnode)=create_idnode(CONST_ATTRIBUTE,BOOLTYPE,1,std::to_string((yyvsp[0].bool_types)).c_str()).idnode;}
#line 1849 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 365 "hw1.y" /* yacc.c:1646  */
    {(yyval.idnode)=create_idnode(CONST_ATTRIBUTE,STRINGTYPE,1,(yyvsp[0].string_types)).idnode;}
#line 1855 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 370 "hw1.y" /* yacc.c:1646  */
    {(yyval.int_types)=int((yyvsp[0].real_types));}
#line 1861 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 373 "hw1.y" /* yacc.c:1646  */
    {(yyval.int_types)=int((yyvsp[0].real_types));}
#line 1867 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 376 "hw1.y" /* yacc.c:1646  */
    {(yyval.real_types)=(yyvsp[-1].real_types);}
#line 1873 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 377 "hw1.y" /* yacc.c:1646  */
    {(yyval.real_types)=(yyvsp[-2].real_types)+(yyvsp[0].real_types);}
#line 1879 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 378 "hw1.y" /* yacc.c:1646  */
    {(yyval.real_types)=(yyvsp[-2].real_types)-(yyvsp[0].real_types);}
#line 1885 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 379 "hw1.y" /* yacc.c:1646  */
    {(yyval.real_types)=(yyvsp[-2].real_types)*(yyvsp[0].real_types);}
#line 1891 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 380 "hw1.y" /* yacc.c:1646  */
    {(yyval.real_types)=(yyvsp[-2].real_types)/(yyvsp[0].real_types);}
#line 1897 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 381 "hw1.y" /* yacc.c:1646  */
    {(yyval.real_types)=pow((yyvsp[-2].real_types),(yyvsp[0].real_types));}
#line 1903 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 382 "hw1.y" /* yacc.c:1646  */
    {(yyval.real_types)=-(yyvsp[0].real_types);}
#line 1909 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 383 "hw1.y" /* yacc.c:1646  */
    {(yyval.real_types)=(yyvsp[0].real_types);}
#line 1915 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 385 "hw1.y" /* yacc.c:1646  */
    {
                    if((yyvsp[0].idnode).IDAttributes!=CONST_ATTRIBUTE)
                    {
                        yyerror("must be a const\n");
                        return 1;
                    }
                    if((yyvsp[0].idnode).IDtype==INTTYPE||(yyvsp[0].idnode).IDtype==REALTYPE){
                         (yyval.real_types) = atof((yyvsp[0].idnode).IDvalue);
                    }
                    else
                    {
                        yyerror("must be a number\n");
                        return 1;
                    }
                }
#line 1935 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 402 "hw1.y" /* yacc.c:1646  */
    {(yyval.real_types)=(yyvsp[-1].real_types);}
#line 1941 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 403 "hw1.y" /* yacc.c:1646  */
    {(yyval.real_types)=(yyvsp[-2].real_types)+(yyvsp[0].real_types);}
#line 1947 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 404 "hw1.y" /* yacc.c:1646  */
    {(yyval.real_types)=(yyvsp[-2].real_types)-(yyvsp[0].real_types);}
#line 1953 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 405 "hw1.y" /* yacc.c:1646  */
    {(yyval.real_types)=(yyvsp[-2].real_types)*(yyvsp[0].real_types);}
#line 1959 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 406 "hw1.y" /* yacc.c:1646  */
    {(yyval.real_types)=(yyvsp[-2].real_types)/(yyvsp[0].real_types);}
#line 1965 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 407 "hw1.y" /* yacc.c:1646  */
    {(yyval.real_types)=pow((yyvsp[-2].real_types),(yyvsp[0].real_types));}
#line 1971 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 408 "hw1.y" /* yacc.c:1646  */
    {(yyval.real_types)=-(yyvsp[0].real_types);}
#line 1977 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 409 "hw1.y" /* yacc.c:1646  */
    {(yyval.real_types)=(yyvsp[0].real_types);}
#line 1983 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 411 "hw1.y" /* yacc.c:1646  */
    {
                    if((yyvsp[0].idnode).IDtype==INTTYPE||(yyvsp[0].idnode).IDtype==REALTYPE){
                         (yyval.real_types) = atof((yyvsp[0].idnode).IDvalue);
                    }
                    else
                    {
                        yyerror("must be a number\n");
                        return 1;
                    }
                }
#line 1998 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 423 "hw1.y" /* yacc.c:1646  */
    {(yyval.bool_types)=((yyvsp[-2].real_types)>(yyvsp[0].real_types));}
#line 2004 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 424 "hw1.y" /* yacc.c:1646  */
    {(yyval.bool_types)=((yyvsp[-2].real_types)<(yyvsp[0].real_types));}
#line 2010 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 425 "hw1.y" /* yacc.c:1646  */
    {(yyval.bool_types)=((yyvsp[-2].real_types)<=(yyvsp[0].real_types));}
#line 2016 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 426 "hw1.y" /* yacc.c:1646  */
    {(yyval.bool_types)=((yyvsp[-2].real_types)>=(yyvsp[0].real_types));}
#line 2022 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 427 "hw1.y" /* yacc.c:1646  */
    {(yyval.bool_types)=((yyvsp[-2].real_types)==(yyvsp[0].real_types));}
#line 2028 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 428 "hw1.y" /* yacc.c:1646  */
    {(yyval.bool_types)=((yyvsp[-2].real_types)!=(yyvsp[0].real_types));}
#line 2034 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 429 "hw1.y" /* yacc.c:1646  */
    {(yyval.bool_types)=(yyvsp[-1].bool_types);}
#line 2040 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 430 "hw1.y" /* yacc.c:1646  */
    {(yyval.bool_types)=((yyvsp[-2].bool_types)&(yyvsp[0].bool_types));}
#line 2046 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 431 "hw1.y" /* yacc.c:1646  */
    {(yyval.bool_types)=((yyvsp[-2].bool_types)|(yyvsp[0].bool_types));}
#line 2052 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 432 "hw1.y" /* yacc.c:1646  */
    {(yyval.bool_types)=!(yyvsp[0].bool_types);}
#line 2058 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 433 "hw1.y" /* yacc.c:1646  */
    {(yyval.bool_types)=(yyvsp[0].bool_types);}
#line 2064 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 434 "hw1.y" /* yacc.c:1646  */
    {(yyval.bool_types)=(yyvsp[0].bool_types);}
#line 2070 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 436 "hw1.y" /* yacc.c:1646  */
    {(yyval.bool_types)=((yyvsp[-2].real_types)>(yyvsp[0].real_types));}
#line 2076 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 437 "hw1.y" /* yacc.c:1646  */
    {(yyval.bool_types)=((yyvsp[-2].real_types)<(yyvsp[0].real_types));}
#line 2082 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 438 "hw1.y" /* yacc.c:1646  */
    {(yyval.bool_types)=((yyvsp[-2].real_types)<=(yyvsp[0].real_types));}
#line 2088 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 439 "hw1.y" /* yacc.c:1646  */
    {(yyval.bool_types)=((yyvsp[-2].real_types)>=(yyvsp[0].real_types));}
#line 2094 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 440 "hw1.y" /* yacc.c:1646  */
    {(yyval.bool_types)=((yyvsp[-2].real_types)==(yyvsp[0].real_types));}
#line 2100 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 441 "hw1.y" /* yacc.c:1646  */
    {(yyval.bool_types)=((yyvsp[-2].real_types)!=(yyvsp[0].real_types));}
#line 2106 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 442 "hw1.y" /* yacc.c:1646  */
    {(yyval.bool_types)=(yyvsp[-1].bool_types);}
#line 2112 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 443 "hw1.y" /* yacc.c:1646  */
    {(yyval.bool_types)=((yyvsp[-2].bool_types)&(yyvsp[0].bool_types));}
#line 2118 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 444 "hw1.y" /* yacc.c:1646  */
    {(yyval.bool_types)=((yyvsp[-2].bool_types)|(yyvsp[0].bool_types));}
#line 2124 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 445 "hw1.y" /* yacc.c:1646  */
    {(yyval.bool_types)=!(yyvsp[0].bool_types);}
#line 2130 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 446 "hw1.y" /* yacc.c:1646  */
    {(yyval.bool_types)=(yyvsp[0].bool_types);}
#line 2136 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 447 "hw1.y" /* yacc.c:1646  */
    {(yyval.bool_types)=(yyvsp[0].bool_types);}
#line 2142 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 449 "hw1.y" /* yacc.c:1646  */
    {
                (yyval.idnode)=create_idnode(CONST_ATTRIBUTE,INTTYPE,1,std::to_string((yyvsp[0].int_types)).c_str()).idnode;
                }
#line 2150 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 452 "hw1.y" /* yacc.c:1646  */
    {
                (yyval.idnode)=create_idnode(CONST_ATTRIBUTE,REALTYPE,1,std::to_string((yyvsp[0].real_types)).c_str()).idnode;
                }
#line 2158 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 455 "hw1.y" /* yacc.c:1646  */
    {(yyval.idnode)=(yyvsp[0].idnode);}
#line 2164 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 456 "hw1.y" /* yacc.c:1646  */
    {(yyval.idnode)=(yyvsp[0].idnode);}
#line 2170 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2174 "y.tab.c" /* yacc.c:1646  */
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

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

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
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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
                  yystos[*yyssp], yyvsp);
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
#line 467 "hw1.y" /* yacc.c:1906  */



void yyerror(char * msg)
{
    fprintf(stderr, "%s\n", msg);
}

int main(int argc,char** argv)
{
    /* open the source program file */
    if (argc != 2) {
        printf ("Usage: sc filename\n");
        exit(1);
    }
    yyin = fopen(argv[1], "r");         /* open input file */
    scope_init();
    int count=0;
    /* perform parsing */
    while(1)
    {
        if (yyparse() == 1)                 /* parsing */
        {
            count++;
            yyerror("Parsing error !");    /* syntax error */
            break;
        }
        else
            break;
    }
    if(count==0)
        yyerror("\nsave pass!!\n");
    else
        fprintf(stderr,"\nParsing error:%d \n",count);
}

