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
#line 1 "hw3.y" /* yacc.c:339  */

#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>  
#include <math.h>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

#include "lex.yy.c"
#define Trace(t) {printf("[%d]:%s",linenum,t);}
const int MINUS=500;
const int PLAUS=501;
using namespace std;
int count_L=0;
int count_L_old=0;
int scope_number=0;
Hash out_scope_table("out_table");
list<string> scope_name;
list<Hash> scope_list;
string current_scop;
string outstring="";
string app_name="";
int id_counter=0;
map<string,list<int>*> func_map;
list<int> scope_Llab;


template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

string get_format(string name){
    string out ="(";
    map<string,list<int>*>::iterator temp=func_map.find(name);
    if(temp!=func_map.end())
    {
        list<int>::iterator it1=temp->second->begin();
        int count;
        for(it1,count=0;it1!=temp->second->end();++it1,++count)
        {
            if(it1!=--temp->second->end())
                out+=type_name[*it1]+",";
            else
                out+=type_name[*it1];
        }
    }
    return out+=")";
}

void print_exp_tab(){
    int i=0,m=scope_list.size();
    for(;i<m;++i)
        outstring+="    ";
}
void print_tab(){
    int i=0,m=scope_list.size();
    for(;i<m;++i)
        printf("    ");
}
int idcount;
void yyerror(char * msg);
void scope_init(string name){
    Hash temp(name);
    scope_name.push_front(name);
    scope_list.push_front(temp);
    current_scop="goble";
    idcount=0;
}


string get_scope(){             
    return scope_name.front();
}
void dump_table(){
    out_scope_table.dump();
}
void add_scope(string name){
    name=name+to_string(scope_number++);
    Hash temp(name);
    temp.set_counter(id_counter);
    scope_name.push_front(name);
    scope_list.push_front(temp);
    scope_Llab.push_front(count_L);
    count_L_old=count_L;
    current_scop=name;
}
int get_current_counter(){
    return scope_list.front().get_counter();
}
void exit_scope(){
    scope_name.pop_front();
    scope_list.pop_front();
    count_L=scope_Llab.front();
    scope_Llab.pop_front();
    current_scop=scope_name.front();
}
int inser_data(int idcount,string idname,string idvalue,int idtype, int idattrubutes){
    Hash temp=scope_list.front();
    if (temp.lookout(idname)!=-1)
    {
        return -1;
    }
    scope_list.pop_front();
    id_node new_data(idcount,idname,idtype,idattrubutes,idvalue,current_scop);
    temp.insert(new_data);
    new_data.set_name(current_scop+"_"+idname); //avoid the redefine the variables name
    out_scope_table.insert(new_data); //insert the data to dump table
    scope_list.push_front(temp);
    id_counter++;
    return 1;
}
void update_data(string name,string value){//For ASSIGNMENT to update the value
    list<Hash>::iterator it=scope_list.begin();
    for(it;it!=scope_list.end();++it){
        if(it->lookout(name)!=-1){
            it->update(name,value);
            break;
        }
    }
}

id_node current_lookout_data(string name){//for create the variables to check 
    Hash temp=scope_list.front();
    id_node new_data(1,name,-1,-1,"0",current_scop);
    if (temp.lookout(name)==-1)
    {
        return new_data;
    }
    return temp.get_data(name);
}

id_node lookout_data(string name){//for check the use variables
    list<Hash>::iterator it=scope_list.begin();
    for(;it!=scope_list.end();++it){
        if(it->lookout(name)!=-1){
            return it->get_data(name);
        }
    }
    id_node new_data(1,name,-1,-1,"0",current_scop);
    return new_data;
}

string current_lookout_index(string name){//for check the use variables
    list<Hash>::iterator it=scope_list.begin();
    for(;it!=(--scope_list.end());++it)
        if (it->lookout(name)!=-1)
            return to_string(it->get_data(name).get_count());
    return "-1";
}
string lookout_index(string name){//for check the use variables
    list<Hash>::iterator it=(--scope_list.end());
    if(it->lookout(name)!=-1){
        return it->get_name();
    }
    return current_scop;
}
void insert_scope(string name){
    Hash temp(name);
    scope_name.push_front(name);
    scope_list.push_front(temp);
    current_scop=name;
}
typedef union YYSTYPE id_union;
id_union create_idnode(int Attrubutes,int IDtype,int IDnumber,string IDvalue)
{
    
    id_union temp;
    temp.idnode.IDAttributes=Attrubutes;
    temp.idnode.IDtype=IDtype;
    temp.idnode.IDnumber=IDnumber;
    temp.idnode.IDvalue=new string(IDvalue.c_str());
    return temp;
}
bool isnum(id_union::node t1,id_union::node t2){
    if(!(t1.IDtype==INTTYPE||t1.IDtype==REALTYPE)){yyerror("must be a number");return false;}
    if(!(t2.IDtype!=INTTYPE||t2.IDtype!=REALTYPE)){yyerror("must be a number");return false;}
    return true;
}
id_union::node slove(int op,id_union::node& t1,id_union::node& t2){//slove the exp
    id_union::node temp;
    switch(op){
        case ARITHMETIC_ADD:
            if(isnum(t1,t2)){
            double answer=atof(t1.IDvalue->c_str())+atof(t2.IDvalue->c_str());
            t1.IDvalue=new string(to_string(answer).c_str());
            if(t1.IDtype!=t2.IDtype) t1.IDtype=REALTYPE;
            temp=t1;
            }
            else temp=create_idnode(ERROR_ATTRIBUTE,-1,1,"0").idnode;
            print_exp_tab();
            outstring+="iadd\n";
            break;
        case ARITHMETIC_SUB:
            if(isnum(t1,t2)){
            double answer=atof(t1.IDvalue->c_str())-atof(t2.IDvalue->c_str());
            t1.IDvalue=new string(to_string(answer).c_str());
            if(t1.IDtype!=t2.IDtype) t1.IDtype=REALTYPE;
            temp=t1;
            }
            else temp=create_idnode(ERROR_ATTRIBUTE,-1,1,"0").idnode;
            print_exp_tab();
            outstring+="isub\n";
            break;
        case ARITHMETIC_MUL:
            if(isnum(t1,t2)){
            double answer=atof(t1.IDvalue->c_str())*atof(t2.IDvalue->c_str());
            t1.IDvalue=new string(to_string(answer).c_str());
            if(t1.IDtype!=t2.IDtype) t1.IDtype=REALTYPE;
            temp=t1;
            }
            else temp=create_idnode(ERROR_ATTRIBUTE,-1,1,"0").idnode;
            print_exp_tab();
            outstring+="imul\n";
            break;
        case ARITHMETIC_DIV:
            if(isnum(t1,t2)){
            if(atof(t2.IDvalue->c_str())==0){
                yyerror("can't be zero");
                temp=create_idnode(ERROR_ATTRIBUTE,-1,1,"0").idnode;
            }
            double answer=atof(t1.IDvalue->c_str())/atof(t2.IDvalue->c_str());
            t1.IDvalue=new string(to_string(answer).c_str());
            if(t1.IDtype!=t2.IDtype) t1.IDtype=REALTYPE;
            temp=t1;
            }
            else temp=create_idnode(ERROR_ATTRIBUTE,-1,1,"0").idnode;
            print_exp_tab();
            outstring+="idiv\n";
            break;
        case EXPONENTIATION:
            if(isnum(t1,t2)){
            double answer=pow(atof(t1.IDvalue->c_str()),atof(t2.IDvalue->c_str()));
            t1.IDvalue=new string(to_string(answer).c_str());
            if(t1.IDtype!=t2.IDtype) t1.IDtype=REALTYPE;
            temp=t1;
            }
            else temp=create_idnode(ERROR_ATTRIBUTE,-1,1,"0").idnode;
            break;
        case MINUS:
            if(isnum(t1,t1)){
            double answer=-atof(t1.IDvalue->c_str());
            t1.IDvalue=new string(to_string(answer).c_str());
            temp=t1;
            }
            else temp=create_idnode(ERROR_ATTRIBUTE,-1,1,"0").idnode;
            print_exp_tab();
            outstring+="ineg\n";
            break;
        case PLAUS:
            if(isnum(t1,t1)){temp=t1;}
            else temp=create_idnode(ERROR_ATTRIBUTE,-1,1,"0").idnode;
            break;
        case RELATIONAL_BIG:
            if(isnum(t1,t2)){
            bool answer=atof(t1.IDvalue->c_str())>atof(t2.IDvalue->c_str());
            t1.IDvalue=new string(to_string(answer).c_str());
            t1.IDtype=BOOLTYPE;
            temp=t1;
            }
            else temp=create_idnode(ERROR_ATTRIBUTE,-1,1,"0").idnode;
            print_exp_tab();
            outstring+="    isub\n";
            print_exp_tab();
            outstring+="    ifgt L"+current_scop+"_"+to_string(count_L)+"\n";
            print_exp_tab();
            outstring+="    iconst_0\n";
            print_exp_tab();
            outstring+="    goto L"+current_scop+"_"+to_string(count_L+1)+"\n";
            print_exp_tab();
            outstring+="L"+current_scop+"_"+to_string(count_L)+": iconst_1\n";
            print_exp_tab();
            outstring+="L"+current_scop+"_"+to_string(++count_L)+":\n";
            count_L++;
            break;
        case RELATIONAL_BIG_EQ:
            if(isnum(t1,t2)){
            bool answer=atof(t1.IDvalue->c_str())>=atof(t2.IDvalue->c_str());
            t1.IDvalue=new string(to_string(answer).c_str());
            t1.IDtype=BOOLTYPE;
            temp=t1;
            }
            else temp=create_idnode(ERROR_ATTRIBUTE,-1,1,"0").idnode;
            print_exp_tab();
            outstring+="    isub\n";
            print_exp_tab();
            outstring+="    ifge L"+current_scop+"_"+to_string(count_L)+"\n";
            print_exp_tab();
            outstring+="    iconst_0\n";
            print_exp_tab();
            outstring+="    goto L"+current_scop+"_"+to_string(count_L+1)+"\n";
            print_exp_tab();
            outstring+="L"+current_scop+"_"+to_string(count_L)+": iconst_1\n";
            print_exp_tab();
            outstring+="L"+current_scop+"_"+to_string(++count_L)+":\n";
            count_L++;
            break;
        case RELATIONAL_LEAST:
            if(isnum(t1,t2)){
            bool answer=atof(t1.IDvalue->c_str())<atof(t2.IDvalue->c_str());
            t1.IDvalue=new string(to_string(answer).c_str());
            t1.IDtype=BOOLTYPE;
            temp=t1;
            }
            else temp=create_idnode(ERROR_ATTRIBUTE,-1,1,"0").idnode;
            print_exp_tab();
            outstring+="    isub\n";
            print_exp_tab();
            outstring+="    iflt L"+current_scop+"_"+to_string(count_L)+"\n";
            print_exp_tab();
            outstring+="    iconst_0\n";
            print_exp_tab();
            outstring+="    goto L"+current_scop+"_"+to_string(count_L+1)+"\n";
            print_exp_tab();
            outstring+="L"+current_scop+"_"+to_string(count_L)+": iconst_1\n";
            print_exp_tab();
            outstring+="L"+current_scop+"_"+to_string(++count_L)+":\n";
            count_L++;
            break;
        case RELATIONAL_LEAST_EQ:
            if(isnum(t1,t2)){
            bool answer=atof(t1.IDvalue->c_str())<=atof(t2.IDvalue->c_str());
            t1.IDvalue=new string(to_string(answer).c_str());
            t1.IDtype=BOOLTYPE;
            temp=t1;
            }
            else temp=create_idnode(ERROR_ATTRIBUTE,-1,1,"0").idnode;
            print_exp_tab();
            outstring+="    isub\n";
            print_exp_tab();
            outstring+="    ifle L"+current_scop+"_"+to_string(count_L)+"\n";
            print_exp_tab();
            outstring+="    iconst_0\n";
            print_exp_tab();
            outstring+="    goto L"+current_scop+"_"+to_string(count_L+1)+"\n";
            print_exp_tab();
            outstring+="L"+current_scop+"_"+to_string(count_L)+": iconst_1\n";
            print_exp_tab();
            outstring+="L"+current_scop+"_"+to_string(++count_L)+":\n";
            count_L++;
            break;
        case RELATIONAL_EQ:
            if(isnum(t1,t2)){
            bool answer=atof(t1.IDvalue->c_str())==atof(t2.IDvalue->c_str());
            t1.IDvalue=new string(to_string(answer).c_str());
            t1.IDtype=BOOLTYPE;
            temp=t1;
            }
            else 
                temp=create_idnode(ERROR_ATTRIBUTE,-1,1,"0").idnode;
            print_exp_tab();
            outstring+="    isub\n";
            print_exp_tab();
            outstring+="    ifeq L"+current_scop+"_"+to_string(count_L)+"\n";
            print_exp_tab();
            outstring+="    iconst_0\n";
            print_exp_tab();
            outstring+="    goto L"+current_scop+"_"+to_string(count_L+1)+"\n";
            print_exp_tab();
            outstring+="L"+current_scop+"_"+to_string(count_L)+": iconst_1\n";
            print_exp_tab();
            outstring+="L"+current_scop+"_"+to_string(++count_L)+":\n";
            count_L++;
            break;
        case RELATIONAL_NEQ:
            if(isnum(t1,t2)){
            bool answer=atof(t1.IDvalue->c_str())!=atof(t2.IDvalue->c_str());
            t1.IDvalue=new string(to_string(answer).c_str());
            t1.IDtype=BOOLTYPE;
            temp=t1;
            }
            else temp=create_idnode(ERROR_ATTRIBUTE,-1,1,"0").idnode;
            print_exp_tab();
            outstring+="    isub\n";
            print_exp_tab();
            outstring+="    ifne L"+current_scop+"_"+to_string(count_L)+"\n";
            print_exp_tab();
            outstring+="    iconst_0\n";
            print_exp_tab();
            outstring+="    goto L"+current_scop+"_"+to_string(count_L+1)+"\n";
            print_exp_tab();
            outstring+="L"+current_scop+"_"+to_string(count_L)+": iconst_1\n";
            print_exp_tab();
            outstring+="L"+current_scop+"_"+to_string(++count_L)+":\n";
            count_L++;
            break;
        case AND:
            if(t1.IDtype==BOOLTYPE&&t2.IDtype==BOOLTYPE){
            bool answer=(atof(t1.IDvalue->c_str())==1)&(atof(t2.IDvalue->c_str())==1);
            t1.IDvalue=new string(to_string(answer).c_str());
            temp=t1;
            }
            else temp=create_idnode(ERROR_ATTRIBUTE,-1,1,"0").idnode;
            print_exp_tab();
            outstring+="iand\n";
            break;
        case OR:
            if(t1.IDtype==BOOLTYPE&&t2.IDtype==BOOLTYPE){
            bool answer=(atof(t1.IDvalue->c_str())==1)&(atof(t2.IDvalue->c_str())==1);
            t1.IDvalue=new string(to_string(answer).c_str());
            temp=t1;
            }
            else temp=create_idnode(ERROR_ATTRIBUTE,-1,1,"0").idnode;
            print_exp_tab();
            outstring+="ior\n";
            break;
        case NOT:
            if(t1.IDtype==BOOLTYPE&&t1.IDtype==BOOLTYPE){
            bool answer=!(atof(t1.IDvalue->c_str())==1);
            t1.IDvalue=new string(to_string(answer).c_str());
            temp=t1;
            }
            else temp=create_idnode(ERROR_ATTRIBUTE,-1,1,"0").idnode;
            print_exp_tab();
            outstring+="iconst_1\n";
            print_exp_tab();
            outstring+="ixor\n";
            break;
    }
    return temp;
}


#line 506 "y.tab.c" /* yacc.c:339  */

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
    OR = 301,
    NOT = 302,
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
#define OR 301
#define NOT 302
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
#line 443 "hw3.y" /* yacc.c:355  */

    bool bool_types;
    int int_types;
    double real_types;
    std::string* string_types;
    struct node{
        int IDAttributes;
        int IDtype;
        int IDnumber;
        std::string* IDvalue;
        std::string* IDname;
    }idnode;
    std::list<int>* arg_types;

#line 701 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 718 "y.tab.c" /* yacc.c:358  */

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
#define YYFINAL  25
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   283

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  71
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  99
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  170

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
       0,   545,   545,   546,   546,   547,   547,   549,   549,   550,
     563,   580,   582,   582,   584,   590,   596,   628,   628,   630,
     635,   640,   641,   643,   643,   649,   657,   664,   669,   671,
     672,   675,   684,   672,   696,   707,   708,   708,   713,   713,
     713,   713,   713,   714,   747,   763,   774,   785,   786,   791,
     807,   808,   809,   810,   811,   813,   833,   853,   853,   855,
     856,   859,   877,   887,   911,   935,   953,   957,   968,   968,
     969,   977,   986,   989,   990,   991,   992,   993,   994,   995,
     996,   997,  1004,  1005,  1006,  1007,  1008,  1009,  1010,  1011,
    1012,  1013,  1015,  1019,  1023,  1036,  1041,  1046,  1051,  1060
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
  "BOOLEAN_CONSTANTS_TRUE", "AND", "OR", "NOT", "COMMENTS_ONE",
  "COMMENTS_START_MUL", "COMMENTS_END_MUL", "COMMA", "COLON", "SEMICOLON",
  "LEFT_PARENTHESE", "RIGHT_PARENTHESE", "LEFT_SQUARE_BRACKETS",
  "RIGHT_SQUARE_BRACKETS", "LEFT_BRACKETS", "RIGHT_BRACKETS",
  "EXPONENTIATION", "REMAINDER", "LOGICAL", "ASSIGNMENT",
  "INTEGER_CONSTANTS", "IDENTIFIER", "REAL_CONSTANTS", "STRING_CONSTANTS",
  "ERROR_SIMPLE", "UMINUS", "UADD", "$accept", "start_symbol", "programs",
  "program", "functions", "ex_function", "ex1_function", "function",
  "formal_arguments", "formal_argument", "func_invo", "comm_expression",
  "comm_expressions", "ex_compound", "Compound", "ex_IF", "$@1",
  "Conditionals", "Conditional", "ex_loop", "LOOP", "$@2", "$@3", "$@4",
  "Procedure", "statements", "statement", "type", "SAVE_IDENTIFERS",
  "IDENTIFERS", "declarations", "declaration", "arrays_variable",
  "arrays_declaration", "consts_declaration", "Variables_declaration",
  "constant_exp", "expression", "const_index_expression",
  "index_expression", "number_expression", "bool_expression", "commponent", YY_NULLPTR
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

#define YYPACT_NINF -63

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-63)))

#define YYTABLE_NINF -99

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      66,   -62,    45,   -62,    12,   -63,    66,   -63,   -62,   111,
       6,   -63,    10,   -63,   -63,   -63,   -63,   -40,   -63,   -63,
     -63,   -63,   -63,   -62,   123,   -63,   -63,    -2,     5,    45,
      16,   -18,   -63,   117,   117,   117,   -18,   -63,   -63,   -63,
     111,   -63,    18,    20,   -63,   111,   -63,   -63,    22,   111,
      19,   111,    21,   -63,   -63,   117,    36,   137,    29,    37,
     -62,   -63,   -63,   -63,    44,    46,   137,   137,   -63,   -63,
     143,   143,   -63,   -63,   -63,   -63,   181,   -63,   -63,   223,
      -7,   -63,   -63,   -63,   -63,    40,    20,   -63,   -63,   -63,
     -63,   137,   117,   -63,   117,   -63,   -63,   -63,   137,    -4,
      57,   202,   117,   -63,    45,   117,   143,   -63,   -63,   223,
     -63,   191,    95,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   143,   143,   -63,   109,    72,    73,
     202,   -63,   -63,   -11,    45,   -63,   -63,    79,   -63,    84,
      -7,   -63,   -63,    -3,    -3,    77,    77,   202,   202,   202,
     202,   202,   202,   -63,   -63,   -63,   -63,   143,   -63,   -63,
     -63,   117,    -7,   -63,    90,   111,    96,   -63,    20,   -63
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     0,     0,     0,     2,     4,     5,    12,    37,
       8,     6,    58,    66,    60,    59,    55,     0,    51,    52,
      53,    54,    50,     0,     0,     1,     3,     0,    13,     0,
       0,     0,    23,     0,     0,    48,     0,    21,    56,    40,
      37,    38,     0,    28,    41,    37,    39,    42,     0,    37,
       0,    37,     0,     7,    57,     0,     0,     0,    65,     0,
       0,    14,    29,    34,     0,     0,     0,     0,    92,    93,
       0,     0,    95,    96,    70,    97,    94,    99,    45,    68,
      69,    81,    46,    49,    47,     0,     0,    27,    30,    11,
      36,     0,     0,    35,     0,    63,    67,     9,     0,    98,
       0,    71,     0,    10,     0,    17,     0,    80,    79,     0,
      91,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    22,    26,     0,     0,
      72,    43,    44,     0,     0,    64,    15,     0,    18,    19,
      24,    73,    82,    74,    75,    76,    77,    84,    85,    86,
      83,    87,    88,    78,    89,    90,    25,     0,    61,    62,
      16,    17,    31,    20,     0,    37,     0,    32,     0,    33
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -63,   -63,   148,   -63,   145,   -63,   -63,   153,   -63,   -63,
     127,     1,   -63,   -63,   -35,   -63,   -63,   -63,   -63,   -63,
     -63,   -63,   -63,   -63,   -63,   -38,   -63,   -15,     7,    -9,
      68,   -63,    -8,   -63,   -63,   -63,    63,   -29,   -63,   -63,
     -12,   -37,   -63
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,     6,     7,     8,     9,    39,    27,    28,
      75,   137,   138,    40,    41,    42,    65,    43,    44,    45,
      46,   128,   164,   168,    47,    48,    49,    23,    17,    99,
      51,    12,    77,    13,    14,    15,    95,    96,   100,   129,
      79,    80,    81
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      50,    52,    85,    16,    78,    82,    83,    88,    87,    58,
      24,    90,    25,    93,    61,    29,     1,     2,   113,   114,
     115,   116,    64,    55,    76,    76,    76,    84,   115,   116,
      56,    50,    52,   110,   112,     3,    50,    52,   124,   125,
      50,    52,    50,    52,   141,   101,    76,    38,    18,   123,
     105,   127,    91,    59,   107,   108,    60,   123,   109,   111,
      19,    76,    76,   131,    20,   132,    21,   104,    11,   140,
      62,    22,     1,    86,    11,    91,   139,     2,    37,   130,
      54,    89,    92,    76,    94,    76,   133,   154,   155,   136,
      97,     3,   102,    76,   109,   103,    76,    76,   105,   126,
     106,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   109,   109,   134,    76,    76,     1,   156,   159,
     162,    30,     2,    31,    32,   157,    18,   166,    33,    34,
     158,    35,   139,   169,   160,   161,     3,   123,    19,    36,
     124,   125,    20,   165,    21,   109,    66,    67,    76,    22,
     142,   167,    76,    10,    26,    53,    50,    52,    63,    10,
      68,    69,   163,    10,    70,   135,    66,    67,     0,    37,
       0,    71,    66,    67,     0,     0,    38,     0,     0,    57,
       0,    72,    38,    73,    74,     0,    68,    69,     0,     0,
      70,    98,     0,     0,     0,     0,     0,    71,     0,     0,
       0,    72,    38,    73,     0,     0,     0,    72,    38,    73,
     -98,   -98,   -98,   -98,   -98,   -98,   -98,   -98,   -98,   -98,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
       0,   113,   114,   115,   116,   105,     0,    91,     0,     0,
       0,   -98,     0,     0,     0,     0,   141,     0,     0,     0,
       0,   123,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   123
};

static const yytype_int16 yycheck[] =
{
       9,     9,    40,    65,    33,    34,    35,    45,    43,    24,
       3,    49,     0,    51,    29,     8,     6,    11,    29,    30,
      31,    32,    31,    63,    33,    34,    35,    36,    31,    32,
      23,    40,    40,    70,    71,    25,    45,    45,    45,    46,
      49,    49,    51,    51,    55,    57,    55,    65,     3,    60,
      54,    86,    56,    55,    66,    67,    51,    60,    70,    71,
      15,    70,    71,    92,    19,    94,    21,    60,     0,   106,
      54,    26,     6,    55,     6,    56,   105,    11,    58,    91,
      12,    59,    63,    92,    63,    94,    98,   124,   125,   104,
      54,    25,    63,   102,   106,    58,   105,   106,    54,    59,
      54,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,    57,   124,   125,     6,     9,   134,
     157,    10,    11,    12,    13,    53,     3,   165,    17,    18,
      57,    20,   161,   168,    55,    51,    25,    60,    15,    28,
      45,    46,    19,    53,    21,   157,    29,    30,   157,    26,
      55,    55,   161,     0,     6,    10,   165,   165,    31,     6,
      43,    44,   161,    10,    47,   102,    29,    30,    -1,    58,
      -1,    54,    29,    30,    -1,    -1,    65,    -1,    -1,    56,
      -1,    64,    65,    66,    67,    -1,    43,    44,    -1,    -1,
      47,    54,    -1,    -1,    -1,    -1,    -1,    54,    -1,    -1,
      -1,    64,    65,    66,    -1,    -1,    -1,    64,    65,    66,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      -1,    29,    30,    31,    32,    54,    -1,    56,    -1,    -1,
      -1,    60,    -1,    -1,    -1,    -1,    55,    -1,    -1,    -1,
      -1,    60,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    60
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,    11,    25,    72,    73,    74,    75,    76,    77,
      78,   101,   102,   104,   105,   106,    65,    99,     3,    15,
      19,    21,    26,    98,    99,     0,    73,    79,    80,    99,
      10,    12,    13,    17,    18,    20,    28,    58,    65,    78,
      84,    85,    86,    88,    89,    90,    91,    95,    96,    97,
     100,   101,   103,    75,   101,    63,    99,    56,    98,    55,
      51,    98,    54,    81,   100,    87,    29,    30,    43,    44,
      47,    54,    64,    66,    67,    81,   100,   103,   108,   111,
     112,   113,   108,   108,   100,    96,    55,    85,    96,    59,
      96,    56,    63,    96,    63,   107,   108,    54,    54,   100,
     109,   111,    63,    58,    99,    54,    54,   111,   111,   111,
     112,   111,   112,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    60,    45,    46,    59,    85,    92,   110,
     111,   108,   108,   111,    57,   107,    98,    82,    83,   108,
     112,    55,    55,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   112,   112,     9,    53,    57,    98,
      55,    51,   112,    82,    93,    53,    96,    55,    94,    85
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    71,    72,    73,    73,    74,    74,    75,    75,    76,
      77,    78,    79,    79,    80,    80,    81,    82,    82,    83,
      83,    84,    85,    87,    86,    88,    88,    89,    89,    90,
      92,    93,    94,    91,    95,    96,    96,    96,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      98,    98,    98,    98,    98,    99,   100,   101,   101,   102,
     102,   103,   104,   105,   106,   106,   106,   107,   108,   108,
     108,   109,   110,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   112,   112,   112,   112,   112,   112,   112,   112,
     112,   112,   112,   112,   112,   113,   113,   113,   113,   113
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     1,     1,     2,     0,     4,
       4,     3,     0,     1,     2,     4,     4,     0,     1,     1,
       3,     1,     3,     0,     4,     4,     3,     2,     1,     2,
       0,     0,     0,    11,     2,     2,     2,     0,     1,     1,
       1,     1,     1,     3,     3,     2,     2,     2,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     2,     0,     1,
       1,     4,     6,     4,     5,     3,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     2,
       2,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1
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
#line 545 "hw3.y" /* yacc.c:1646  */
    {}
#line 1959 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 550 "hw3.y" /* yacc.c:1646  */
    {
                    inser_data(1,(yyvsp[-1].idnode).IDname->c_str(),"0",(yyvsp[-2].int_types),FUNC_ATTRIBUTE);
                    id_counter=-1;
                    add_scope((yyvsp[-1].idnode).IDname->c_str());
                    inser_data(1,(yyvsp[-1].idnode).IDname->c_str(),"0",(yyvsp[-2].int_types),FUNC_ATTRIBUTE);
                    (yyval.string_types)=new string((yyvsp[-1].idnode).IDname->c_str());
                    print_tab();
                    if(*(yyvsp[-1].idnode).IDname!="main")
                        printf("method public static %s %s(",type_name[(yyvsp[-2].int_types)].c_str(),(yyvsp[-1].idnode).IDname->c_str());
                    else
                        printf("method public static %s main(java.lang.String[]",type_name[(yyvsp[-2].int_types)].c_str());
                        
                }
#line 1977 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 563 "hw3.y" /* yacc.c:1646  */
    {
                func_map[(yyvsp[-3].string_types)->c_str()]=(yyvsp[-2].arg_types);
                if(*(yyvsp[-3].string_types)!="main")
                for (std::list<int>::iterator it=(yyvsp[-2].arg_types)->begin(); it != (yyvsp[-2].arg_types)->end(); ++it){
                    if(it!=--(yyvsp[-2].arg_types)->end())
                        printf("%s,",type_name[*it].c_str());
                    else
                        printf("%s",type_name[*it].c_str());
                }
                printf(")\n");
                print_tab();
                printf("max_stack 15\n");
                print_tab();
                printf("max_locals 15\n");
                print_tab();
                printf("{\n");
                }
#line 1999 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 580 "hw3.y" /* yacc.c:1646  */
    {print_tab();printf("}\n");exit_scope();}
#line 2005 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 582 "hw3.y" /* yacc.c:1646  */
    {(yyval.arg_types)=new list<int>;}
#line 2011 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 582 "hw3.y" /* yacc.c:1646  */
    {(yyval.arg_types)=(yyvsp[0].arg_types);}
#line 2017 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 584 "hw3.y" /* yacc.c:1646  */
    {
                    list<int>* temp=new list<int>;
                    temp->push_front((yyvsp[0].int_types));
                    (yyval.arg_types)=temp;
                    inser_data(1,(yyvsp[-1].idnode).IDname->c_str(),"0",(yyvsp[0].int_types),VAR_ATTRIBUTE);
                }
#line 2028 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 590 "hw3.y" /* yacc.c:1646  */
    {
                    (yyvsp[-3].arg_types)->push_front((yyvsp[0].int_types));
                    (yyval.arg_types)=(yyvsp[-3].arg_types);
                    inser_data(1,(yyvsp[-1].idnode).IDname->c_str(),"0",(yyvsp[0].int_types),VAR_ATTRIBUTE);
                }
#line 2038 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 596 "hw3.y" /* yacc.c:1646  */
    {
                map<string,list<int>*>::iterator temp=func_map.find((yyvsp[-3].idnode).IDname->c_str());
                if(temp!=func_map.end())
                {
                    list<int>::iterator it1=temp->second->begin();
                    list<int>::iterator it2=(yyvsp[-1].arg_types)->begin();
                    int count;
                    if(temp->second->size()==(yyvsp[-1].arg_types)->size())
                    {
                    
                        for(it1,count=0;it1!=temp->second->end();++it1,++it2,++count){
                            if(*it1!=*it2){
                                printf("argument type not mathc in %d\n",count);
                                return 1;
                            }
                        }
                    }
                    else{
                        printf("%d\n",temp->second->size());
                        printf("argument number not match\n");
                        return 1;
                    }
                    
                }
                else
                {
                    printf("not func\n");
                    return 1;
                }
                (yyval.idnode)=(yyvsp[-3].idnode);
                (yyval.idnode).IDAttributes=VAR_ATTRIBUTE;
                }
#line 2075 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 628 "hw3.y" /* yacc.c:1646  */
    {(yyval.arg_types)=new list<int>;}
#line 2081 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 628 "hw3.y" /* yacc.c:1646  */
    {(yyval.arg_types)=(yyvsp[0].arg_types);}
#line 2087 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 630 "hw3.y" /* yacc.c:1646  */
    {
                    list<int>* temp=new list<int>;
                    temp->push_front((yyvsp[0].idnode).IDtype);
                    (yyval.arg_types)=temp;
                }
#line 2097 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 635 "hw3.y" /* yacc.c:1646  */
    {
                    (yyvsp[0].arg_types)->push_front((yyvsp[-2].idnode).IDtype);
                    (yyval.arg_types)=(yyvsp[0].arg_types);
                }
#line 2106 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 640 "hw3.y" /* yacc.c:1646  */
    {add_scope(current_scop+"_Compound");}
#line 2112 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 641 "hw3.y" /* yacc.c:1646  */
    {exit_scope();}
#line 2118 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 643 "hw3.y" /* yacc.c:1646  */
    {add_scope(current_scop+"_IF");}
#line 2124 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 643 "hw3.y" /* yacc.c:1646  */
    {
                printf("%s",outstring.c_str());
                outstring="";
                print_tab();
                printf("ifeq L%s_%s\n",current_scop.c_str(),to_string(count_L).c_str());
                }
#line 2135 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 649 "hw3.y" /* yacc.c:1646  */
    {
                print_tab();
                printf("    goto L%s_%s\n",current_scop.c_str(),to_string(count_L+1).c_str());
                print_tab();
                printf("L%s_%s:\n",current_scop.c_str(),to_string(count_L).c_str());
                count_L++;
                outstring="";
                }
#line 2148 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 657 "hw3.y" /* yacc.c:1646  */
    {
                print_tab();
                printf("L%s_%s:\n",current_scop.c_str(),to_string(count_L).c_str());
                count_L++;
                outstring="";
                exit_scope();
                }
#line 2160 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 664 "hw3.y" /* yacc.c:1646  */
    {
                print_tab();
                printf("L%s_%s:\n",current_scop.c_str(),to_string(count_L++).c_str());
                outstring="";
                exit_scope();
                }
#line 2171 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 671 "hw3.y" /* yacc.c:1646  */
    {add_scope(current_scop+"_loop");}
#line 2177 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 672 "hw3.y" /* yacc.c:1646  */
    {
                print_tab();
                printf("L%s_%s:\n",current_scop.c_str(),to_string(count_L++).c_str());
                }
#line 2186 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 675 "hw3.y" /* yacc.c:1646  */
    {
                printf("%s",outstring.c_str());
                outstring="";
                print_tab();
                printf("ifeq L%s_%s\n",current_scop.c_str(),to_string(count_L).c_str());
                print_tab();
                printf("goto L%s_%s\n",current_scop.c_str(),to_string(count_L+1).c_str());
                print_tab();
                printf("L%s_%s:\n",current_scop.c_str(),to_string(count_L+2).c_str());
                }
#line 2201 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 684 "hw3.y" /* yacc.c:1646  */
    {
                print_tab();
                printf("goto L%s_%s\n",current_scop.c_str(),to_string(count_L-3).c_str());
                print_tab();
                printf("L%s_%s:\n",current_scop.c_str(),to_string(count_L+1).c_str());
                }
#line 2212 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 689 "hw3.y" /* yacc.c:1646  */
    {
                print_tab();
                printf("goto L%s_%s\n",current_scop.c_str(),to_string(count_L+2).c_str());
                print_tab();
                printf("L%s_%s:\n",current_scop.c_str(),to_string(count_L).c_str());
                count_L+=3;
                exit_scope();}
#line 2224 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 696 "hw3.y" /* yacc.c:1646  */
    {
                    if((yyvsp[0].idnode).IDtype==VOIDTYPE){
                        print_exp_tab();
                        outstring+="invokestatic "+type_name[(yyvsp[0].idnode).IDtype]+" "+app_name+".";
                        outstring+=string((yyvsp[0].idnode).IDname->c_str())+get_format((yyvsp[0].idnode).IDname->c_str())+"\n";
                    }else{
                        yyerror("must be void func\n");
                        return 1;
                    }
                }
#line 2239 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 714 "hw3.y" /* yacc.c:1646  */
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
                    
                    string index="istore "+current_lookout_index((yyvsp[-2].idnode).IDname->c_str());
                    if(index=="istore -1"){
                        index="putstatic "+type_name[(yyvsp[-2].idnode).IDtype]+" ";
                        index+=lookout_index((yyvsp[-2].idnode).IDname->c_str())+"."+(yyvsp[-2].idnode).IDname->c_str();
                    }
                    print_exp_tab();
                    outstring+=index+"\n";
                    printf("%s",outstring.c_str());
                    outstring="";
                    
                    update_data((yyvsp[-2].idnode).IDname->c_str(),(yyvsp[0].idnode).IDvalue->c_str());
                    
                }
#line 2277 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 747 "hw3.y" /* yacc.c:1646  */
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
                    update_data((yyvsp[-2].idnode).IDname->c_str(),(yyvsp[0].idnode).IDvalue->c_str());
                }
#line 2298 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 763 "hw3.y" /* yacc.c:1646  */
    {
                string types_out=type_name[(yyvsp[0].idnode).IDtype];
                if(types_out=="string")
                    types_out="java.lang.String";
                print_tab();
                printf("getstatic java.io.PrintStream java.lang.System.out\n");
                printf("%s",outstring.c_str());
                print_tab();
                printf("invokevirtual void java.io.PrintStream.print(%s)\n",types_out.c_str());
                outstring="";}
#line 2313 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 774 "hw3.y" /* yacc.c:1646  */
    {
                string types_out=type_name[(yyvsp[0].idnode).IDtype];
                if(types_out=="string")
                    types_out="java.lang.String";
                print_tab();
                printf("getstatic java.io.PrintStream java.lang.System.out\n");
                printf("%s",outstring.c_str());
                print_tab();
                printf("invokevirtual void java.io.PrintStream.println(%s)\n",types_out.c_str());
                outstring="";
                }
#line 2329 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 786 "hw3.y" /* yacc.c:1646  */
    {
                outstring="";
                print_tab();
                printf("return\n");
                }
#line 2339 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 791 "hw3.y" /* yacc.c:1646  */
    {
                printf("%s",outstring.c_str());
                outstring="";
                print_tab();
                if((yyvsp[0].idnode).IDtype==REALTYPE)
                    printf("dreturn\n");
                if((yyvsp[0].idnode).IDtype==INTTYPE||(yyvsp[0].idnode).IDtype==BOOLTYPE)
                    printf("ireturn\n");
                if((yyvsp[0].idnode).IDtype==VOIDTYPE)
                    printf("return\n");
                (yyval.idnode)=(yyvsp[0].idnode);}
#line 2355 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 807 "hw3.y" /* yacc.c:1646  */
    {(yyval.int_types)=(yyvsp[0].int_types);}
#line 2361 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 808 "hw3.y" /* yacc.c:1646  */
    {(yyval.int_types)=(yyvsp[0].int_types);}
#line 2367 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 809 "hw3.y" /* yacc.c:1646  */
    {(yyval.int_types)=(yyvsp[0].int_types);}
#line 2373 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 810 "hw3.y" /* yacc.c:1646  */
    {(yyval.int_types)=(yyvsp[0].int_types);}
#line 2379 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 811 "hw3.y" /* yacc.c:1646  */
    {(yyval.int_types)=(yyvsp[0].int_types);}
#line 2385 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 813 "hw3.y" /* yacc.c:1646  */
    {
                //if find the Id in table than return 1 to expression error
                //else not do anything
                union YYSTYPE temp;
                id_node temp_id = current_lookout_data((yyvsp[0].string_types)->c_str());
                if (temp_id.get_IDAttributes()==ERROR_ATTRIBUTE)
                {
                    temp.idnode.IDAttributes=CONST_ATTRIBUTE;
                    temp.idnode.IDtype=0;
                    temp.idnode.IDnumber=1;
                    temp.idnode.IDvalue=new string("0");
                    temp.idnode.IDname=new string(temp_id.get_IDname().c_str());
                    (yyval.idnode)=temp.idnode;
                }
                else{
                    yyerror("redeclaration error");
                    return 1;
                }
                }
#line 2409 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 833 "hw3.y" /* yacc.c:1646  */
    {
                // must find the value and the attrubutes to ASSIGNMENT in table
                // if not find return 1 to expression error
                union YYSTYPE temp;
                id_node temp_id = lookout_data((yyvsp[0].string_types)->c_str());
                if (temp_id.get_IDAttributes()==ERROR_ATTRIBUTE)
                {
                    printf("name : %s\n",temp_id.get_IDname().c_str());
                    yyerror("not define declaration");
                    return 1;
                }
                temp.idnode.IDAttributes=temp_id.get_IDAttributes();
                temp.idnode.IDtype=temp_id.get_IDtype();
                temp.idnode.IDnumber=temp_id.get_IDnumber();
                temp.idnode.IDvalue=new string(temp_id.get_IDvalue().c_str());
                temp.idnode.IDname=new string(temp_id.get_IDname().c_str());
                (yyval.idnode)=temp.idnode;
                }
#line 2432 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 860 "hw3.y" /* yacc.c:1646  */
    {
                    if ((yyvsp[-3].idnode).IDAttributes!=ARRAY_ATTRIBUTE){
                        printf("IDAttributes %d\n",(yyvsp[-3].idnode).IDAttributes);
                        yyerror("not ARRAY_type");
                        return 1;
                    }
                    if ((yyvsp[-1].int_types)<(yyvsp[-3].idnode).IDnumber&& (yyvsp[-1].int_types)>=0){
                        (yyval.idnode)=(yyvsp[-3].idnode);
                        (yyval.idnode).IDAttributes=VAR_ATTRIBUTE;
                        (yyval.idnode).IDnumber=1;
                    }
                    else{ 
                        yyerror("ARRAY index error");
                        return 1;
                    }
                }
#line 2453 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 878 "hw3.y" /* yacc.c:1646  */
    {
                //if SAVE_IccDENTIFERS not return 1 to expression error than creat the item in table
                    inser_data((yyvsp[-2].int_types),(yyvsp[-4].idnode).IDname->c_str(),"0",(yyvsp[0].int_types),ARRAY_ATTRIBUTE);
                    printf("/*array not support*/\n");
                    outstring="";
                }
#line 2464 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 887 "hw3.y" /* yacc.c:1646  */
    {
                    
                    if(current_scop=="goble"){
                        print_tab();
                        printf("field static %s %s = %s\n",type_name[(yyvsp[0].idnode).IDtype].c_str(),(yyvsp[-2].idnode).IDname->c_str(),(yyvsp[0].idnode).IDvalue->c_str());
                    }
                    else{
                        printf("%s",outstring.c_str());                        
                        print_tab();
                        if(get_current_counter()>0)
                        {
                            printf("istore %d\n",get_current_counter());
                        }
                        else
                        {
                            printf("istore 0\n");
                        }
                    }
                    outstring="";
                    inser_data(1,(yyvsp[-2].idnode).IDname->c_str(),(yyvsp[0].idnode).IDvalue->c_str(),(yyvsp[0].idnode).IDtype,CONST_ATTRIBUTE);
                    //printf("Const_declaration:%s\n",$4.IDvalue->c_str());
                }
#line 2491 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 911 "hw3.y" /* yacc.c:1646  */
    {
                    //if SAVE_IDENTIFERS not return 1 to expression error constant_exp is pass
                    //than creat the item in table
                    if ((yyvsp[-2].int_types)!=(yyvsp[0].idnode).IDtype)
                    {
                        yyerror("type not match");
                        return 1;
                    }
                    if(current_scop=="goble"){
                        print_tab();
                        printf("field static %s %s = %s\n",type_name[(yyvsp[-2].int_types)].c_str(),(yyvsp[-3].idnode).IDname->c_str(),(yyvsp[0].idnode).IDvalue->c_str());
                    }
                    else{
                        printf("%s",outstring.c_str());
                        print_tab();
                        if(get_current_counter()>0)
                            printf("istore %d\n",get_current_counter());
                        else
                            printf("istore 0\n");
                    }
                    inser_data(1,(yyvsp[-3].idnode).IDname->c_str(),(yyvsp[0].idnode).IDvalue->c_str(),(yyvsp[-2].int_types),VAR_ATTRIBUTE);
                    outstring="";
                    //printf("Variables_declaration:%s\n",$5.IDvalue->c_str());
                }
#line 2520 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 935 "hw3.y" /* yacc.c:1646  */
    {
                    if(current_scop=="goble"){
                        print_tab();
                        printf("field static %s %s\n",type_name[(yyvsp[0].int_types)].c_str(),(yyvsp[-1].idnode).IDname->c_str());
                    }
                    else{
                        print_tab();
                        printf("sipush 0\n");
                        print_tab();
                        if(get_current_counter()>0)
                            printf("istore %d\n",get_current_counter());
                        else
                            printf("istore 0\n");
                    }
                    inser_data(1,(yyvsp[-1].idnode).IDname->c_str(),"0",(yyvsp[0].int_types),VAR_ATTRIBUTE);
                    outstring="";
                    //printf("Variables_declaration:%s\n",$2);
                }
#line 2543 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 957 "hw3.y" /* yacc.c:1646  */
    {
                if ((yyvsp[0].idnode).IDAttributes!=CONST_ATTRIBUTE){
                    yyerror("must be const");
                    return 1;
                }
                (yyval.idnode)=(yyvsp[0].idnode);
                }
#line 2555 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 968 "hw3.y" /* yacc.c:1646  */
    {(yyval.idnode)=(yyvsp[0].idnode);}
#line 2561 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 968 "hw3.y" /* yacc.c:1646  */
    {(yyval.idnode)=(yyvsp[0].idnode);}
#line 2567 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 969 "hw3.y" /* yacc.c:1646  */
    {
                print_exp_tab();
                outstring+="ldc \""+string((yyvsp[0].string_types)->c_str())+"\"\n";
                (yyval.idnode)=create_idnode(CONST_ATTRIBUTE,STRINGTYPE,1,(yyvsp[0].string_types)->c_str()).idnode;}
#line 2576 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 977 "hw3.y" /* yacc.c:1646  */
    {
                if ((yyvsp[0].idnode).IDAttributes!=CONST_ATTRIBUTE){
                    yyerror("must be const");
                    return 1;
                }
                (yyval.int_types)=atoi((yyvsp[0].idnode).IDvalue->c_str());
                }
#line 2588 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 986 "hw3.y" /* yacc.c:1646  */
    {(yyval.int_types)=atoi((yyvsp[0].idnode).IDvalue->c_str());}
#line 2594 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 989 "hw3.y" /* yacc.c:1646  */
    {(yyval.idnode)=(yyvsp[-1].idnode);if ((yyval.idnode).IDAttributes==ERROR_ATTRIBUTE) return 1;}
#line 2600 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 990 "hw3.y" /* yacc.c:1646  */
    {(yyval.idnode)=slove(ARITHMETIC_ADD,(yyvsp[-2].idnode),(yyvsp[0].idnode));if ((yyval.idnode).IDAttributes==ERROR_ATTRIBUTE) return 1;}
#line 2606 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 991 "hw3.y" /* yacc.c:1646  */
    {(yyval.idnode)=slove(ARITHMETIC_SUB,(yyvsp[-2].idnode),(yyvsp[0].idnode));if ((yyval.idnode).IDAttributes==ERROR_ATTRIBUTE) return 1;}
#line 2612 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 992 "hw3.y" /* yacc.c:1646  */
    {(yyval.idnode)=slove(ARITHMETIC_MUL,(yyvsp[-2].idnode),(yyvsp[0].idnode));if ((yyval.idnode).IDAttributes==ERROR_ATTRIBUTE) return 1;}
#line 2618 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 993 "hw3.y" /* yacc.c:1646  */
    {(yyval.idnode)=slove(ARITHMETIC_DIV,(yyvsp[-2].idnode),(yyvsp[0].idnode));if ((yyval.idnode).IDAttributes==ERROR_ATTRIBUTE) return 1;}
#line 2624 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 994 "hw3.y" /* yacc.c:1646  */
    {(yyval.idnode)=slove(EXPONENTIATION,(yyvsp[-2].idnode),(yyvsp[0].idnode));if ((yyval.idnode).IDAttributes==ERROR_ATTRIBUTE) return 1;}
#line 2630 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 995 "hw3.y" /* yacc.c:1646  */
    {(yyval.idnode)=slove(MINUS,(yyvsp[0].idnode),(yyvsp[0].idnode));if ((yyval.idnode).IDAttributes==ERROR_ATTRIBUTE) return 1;}
#line 2636 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 996 "hw3.y" /* yacc.c:1646  */
    {(yyval.idnode)=slove(PLAUS,(yyvsp[0].idnode),(yyvsp[0].idnode));if ((yyval.idnode).IDAttributes==ERROR_ATTRIBUTE) return 1;}
#line 2642 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 997 "hw3.y" /* yacc.c:1646  */
    {
                (yyval.idnode)=(yyvsp[0].idnode);
                if ((yyval.idnode).IDAttributes!=CONST_ATTRIBUTE&&(yyval.idnode).IDAttributes!=VAR_ATTRIBUTE){
                printf("must be a number\n");
                return 1;}}
#line 2652 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 1004 "hw3.y" /* yacc.c:1646  */
    {(yyval.idnode)=(yyvsp[-1].idnode);if ((yyval.idnode).IDAttributes==ERROR_ATTRIBUTE) return 1;}
#line 2658 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 1005 "hw3.y" /* yacc.c:1646  */
    {(yyval.idnode)=slove(RELATIONAL_BIG,(yyvsp[-2].idnode),(yyvsp[0].idnode));if ((yyval.idnode).IDAttributes==ERROR_ATTRIBUTE) return 1;}
#line 2664 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 1006 "hw3.y" /* yacc.c:1646  */
    {(yyval.idnode)=slove(RELATIONAL_LEAST,(yyvsp[-2].idnode),(yyvsp[0].idnode));if ((yyval.idnode).IDAttributes==ERROR_ATTRIBUTE) return 1;}
#line 2670 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 1007 "hw3.y" /* yacc.c:1646  */
    {(yyval.idnode)=slove(RELATIONAL_LEAST_EQ,(yyvsp[-2].idnode),(yyvsp[0].idnode));if ((yyval.idnode).IDAttributes==ERROR_ATTRIBUTE) return 1;}
#line 2676 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 1008 "hw3.y" /* yacc.c:1646  */
    {(yyval.idnode)=slove(RELATIONAL_BIG_EQ,(yyvsp[-2].idnode),(yyvsp[0].idnode));if ((yyval.idnode).IDAttributes==ERROR_ATTRIBUTE) return 1;}
#line 2682 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 1009 "hw3.y" /* yacc.c:1646  */
    {(yyval.idnode)=slove(RELATIONAL_EQ,(yyvsp[-2].idnode),(yyvsp[0].idnode));if ((yyval.idnode).IDAttributes==ERROR_ATTRIBUTE) return 1;}
#line 2688 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 1010 "hw3.y" /* yacc.c:1646  */
    {(yyval.idnode)=slove(RELATIONAL_NEQ,(yyvsp[-2].idnode),(yyvsp[0].idnode));if ((yyval.idnode).IDAttributes==ERROR_ATTRIBUTE) return 1;}
#line 2694 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 1011 "hw3.y" /* yacc.c:1646  */
    {(yyval.idnode)=slove(AND,(yyvsp[-2].idnode),(yyvsp[0].idnode));if ((yyval.idnode).IDAttributes==ERROR_ATTRIBUTE) return 1;}
#line 2700 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 1012 "hw3.y" /* yacc.c:1646  */
    {(yyval.idnode)=slove(OR,(yyvsp[-2].idnode),(yyvsp[0].idnode));if ((yyval.idnode).IDAttributes==ERROR_ATTRIBUTE) return 1;}
#line 2706 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 1013 "hw3.y" /* yacc.c:1646  */
    {
                (yyval.idnode)=slove(NOT,(yyvsp[0].idnode),(yyvsp[0].idnode));if ((yyval.idnode).IDAttributes==ERROR_ATTRIBUTE) return 1;}
#line 2713 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 1015 "hw3.y" /* yacc.c:1646  */
    {
                print_exp_tab();
                outstring+="iconst_"+std::to_string((yyvsp[0].bool_types))+"\n";
                (yyval.idnode)=create_idnode(CONST_ATTRIBUTE,BOOLTYPE,1,std::to_string((yyvsp[0].bool_types))).idnode;}
#line 2722 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 1019 "hw3.y" /* yacc.c:1646  */
    {
                print_exp_tab();
                outstring+="iconst_"+std::to_string((yyvsp[0].bool_types))+"\n";
                (yyval.idnode)=create_idnode(CONST_ATTRIBUTE,BOOLTYPE,1,std::to_string((yyvsp[0].bool_types))).idnode;}
#line 2731 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 1023 "hw3.y" /* yacc.c:1646  */
    {
                string index="iload "+current_lookout_index((yyvsp[0].idnode).IDname->c_str());
                if(index=="iload -1"){
                    index="getstatic "+type_name[(yyvsp[0].idnode).IDtype]+" ";
                    index+=lookout_index((yyvsp[0].idnode).IDname->c_str())+"."+(yyvsp[0].idnode).IDname->c_str();
                }
                print_exp_tab();
                outstring+=index+"\n";
                (yyval.idnode)=(yyvsp[0].idnode);}
#line 2745 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 1036 "hw3.y" /* yacc.c:1646  */
    {
                print_exp_tab();
                outstring+="sipush "+std::to_string((yyvsp[0].int_types))+"\n";
                (yyval.idnode)=create_idnode(CONST_ATTRIBUTE,INTTYPE,1,std::to_string((yyvsp[0].int_types))).idnode;
                }
#line 2755 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 1041 "hw3.y" /* yacc.c:1646  */
    {
                print_exp_tab();
                outstring+="sipush "+std::to_string((yyvsp[0].real_types))+"\n";
                (yyval.idnode)=create_idnode(CONST_ATTRIBUTE,REALTYPE,1,std::to_string((yyvsp[0].real_types))).idnode;
                }
#line 2765 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 1046 "hw3.y" /* yacc.c:1646  */
    {
                print_exp_tab();
                outstring+="invokestatic "+type_name[(yyvsp[0].idnode).IDtype]+" "+app_name+".";
                outstring+=string((yyvsp[0].idnode).IDname->c_str())+get_format((yyvsp[0].idnode).IDname->c_str())+"\n";
                (yyval.idnode)=(yyvsp[0].idnode);}
#line 2775 "y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 1051 "hw3.y" /* yacc.c:1646  */
    {
                string index="iload "+current_lookout_index((yyvsp[0].idnode).IDname->c_str());
                if(index=="iload -1"){
                    index="getstatic "+type_name[(yyvsp[0].idnode).IDtype]+" ";
                    index+=lookout_index((yyvsp[0].idnode).IDname->c_str())+"."+(yyvsp[0].idnode).IDname->c_str();
                }
                print_exp_tab();
                outstring+=index+"\n";
                (yyval.idnode)=(yyvsp[0].idnode);}
#line 2789 "y.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 1060 "hw3.y" /* yacc.c:1646  */
    {
                print_exp_tab();
                outstring+="not support array\n";
                (yyval.idnode)=(yyvsp[0].idnode);}
#line 2798 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2802 "y.tab.c" /* yacc.c:1646  */
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
#line 1065 "hw3.y" /* yacc.c:1906  */



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
    
    int count=0;
    std::vector<std::string> name_class_temp = split(argv[1], '/');
    std::vector<std::string> name_class = split(name_class_temp.back().c_str(), '.');
    app_name=name_class.front();
    scope_init(app_name);
    printf("class %s\n{\n",app_name.c_str());
    if (yyparse() == 1)                 /* parsing */
    {
        count++;
        yyerror("Parsing error !");    /* syntax error */
    }
    if(count==0){
        //dump_table();
        printf("}\n");
        yyerror("\nsave pass!!\n");
    }
    else
        fprintf(stderr,"\nParsing error:%d \n",count);
}

