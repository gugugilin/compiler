/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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
#line 46 "hw1.y" /* yacc.c:1909  */

    bool bool_types;
    int int_types;
    double real_types;
    const char* string_types;
    struct node{
        int IDAttributes;
        const char* IDvalue;
    }idnode;

#line 205 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
