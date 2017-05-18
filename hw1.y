%{
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>  
#include <math.h>
#include "lex.yy.c"
#define Trace(t) {printf("[%d]:%s",linenum,t);}
using namespace std;
list<string> scope_name;
void yyerror(char * msg);
void scope_init(){
    string name="goble";
    scope_name.push_front(name);
}
string get_scope(){
    return scope_name.front();
}

void insert_scope(string name){
    scope_name.push_front(name);
}

bool isNum(string str)  
{  
    stringstream sin(str);  
    double d;  
    char c;  
    if(!(sin >> d))  
    {
        return false;
    }
    if (sin >> c) 
    {
        return false;
    }  
    return true;  
} 


%}

/* tokens */

%union{
    bool bool_types;
    int int_types;
    double real_types;
    const char* string_types;
    struct node{
        int IDAttributes;
        const char* IDvalue;
    }idnode;
}
%token <int_types>BOOL
%token BREAK
%token CASE
%token CONST
%token CONTINUE
%token DEFAULT
%token ELSE
%token FOR
%token FUNC
%token GO
%token IF
%token IMPORT
%token <int_types>INT
%token NIL
%token PRINT
%token PRINTLN
%token <int_types>REAL
%token RETURN
%token <int_types>STRING
%token STRUCT
%token SWITCH
%token TYPE
%token VAR
%token VOID
%token WHILE
%token READ
%token ARITHMETIC_ADD
%token ARITHMETIC_SUB
%token ARITHMETIC_MUL
%token ARITHMETIC_DIV
%token RELATIONAL_LEAST
%token RELATIONAL_LEAST_EQ
%token RELATIONAL_BIG_EQ
%token RELATIONAL_BIG
%token RELATIONAL_EQ
%token RELATIONAL_NEQ
%token COMPOUND_OPERATORS_ADD
%token COMPOUND_OPERATORS_SUB
%token COMPOUND_OPERATORS_MUL
%token COMPOUND_OPERATORS_DIV
%token <bool_types> BOOLEAN_CONSTANTS_FALSE
%token <bool_types> BOOLEAN_CONSTANTS_TRUE
%token AND
%token NOT
%token OR

%token COMMENTS_ONE
%token COMMENTS_START_MUL
%token COMMENTS_END_MUL
%token COMMA
%token COLON
%token SEMICOLON
%token LEFT_PARENTHESE
%token RIGHT_PARENTHESE
%token LEFT_SQUARE_BRACKETS
%token RIGHT_SQUARE_BRACKETS
%token LEFT_BRACKETS
%token RIGHT_BRACKETS
%token EXPONENTIATION
%token REMAINDER
%token LOGICAL
%token ASSIGNMENT



%token <int_types> INTEGER_CONSTANTS
%token <string_types>IDENTIFIER
%token <real_types> REAL_CONSTANTS
%token <string_types> STRING_CONSTANTS
%token ERROR_SIMPLE


%left OR
%left AND
%left NOT

%left RELATIONAL_LEAST RELATIONAL_LEAST_EQ  RELATIONAL_EQ RELATIONAL_BIG RELATIONAL_BIG_EQ RELATIONAL_NEQ
%left ARITHMETIC_ADD ARITHMETIC_SUB
%left ARITHMETIC_MUL ARITHMETIC_DIV
%left EXPONENTIATION
%nonassoc UMINUS
%nonassoc UADD
%type<real_types> number_expression const_number_expression
%type<int_types> index_expression type const_index_expression
%type<bool_types> bool_expression const_bool_expression
%type<string_types> constant_exp expression 
%type<idnode> IDENTIFERS commponent arrays_variable


%%
start_symbol:   program 
                {
                    Trace("Reducing to start_symbol\n");
                };
program:        body
                {
                    Trace("Reducing to program\n");
                };
body:           statements|
                declarations
                {
                    Trace("Reducing to body\n");
                };



statements:     declarations statements  |
                statement statements|
                /*empty*/ 
                {
                    Trace("Reducing to statements\n");
                };
                
                
statement:      IDENTIFERS ASSIGNMENT expression{
                //if IDAttributes of IDENTIFERS is 1 than return 1 to expression error
                }|
                IDENTIFERS LEFT_SQUARE_BRACKETS index_expression RIGHT_SQUARE_BRACKETS ASSIGNMENT expression{
                //if IDAttributes of IDENTIFERS is 1 than return 1 to expression error
                }|
                PRINT expression|
                PRINTLN expression|
                READ IDENTIFERS|
                RETURN |
                RETURN expression
                {
                    Trace("Reducing to statement\n");
                };

                                
                
                
//declaration
type:           BOOL{$$=$1;}|
                INT{$$=$1;}|
                REAL{$$=$1;}|
                STRING{$$=$1;};
       
SAVE_IDENTIFERS:IDENTIFIER{
                //if find the Id in table than return 1 to expression error
                //else not do anything
                };
       
IDENTIFERS:    IDENTIFIER{
                // must find the value and the attrubutes to ASSIGNMENT in table
                // if not find return 1 to expression error
                union YYSTYPE temp;
                temp.idnode.IDAttributes=2;
                temp.idnode.IDvalue=$1;
                $$=temp.idnode;
                };
                                
                        
declarations:   declaration declarations|/*empty*/;
                
declaration:    Variables_declaration|
                consts_declaration;
                

arrays_variable:IDENTIFERS LEFT_SQUARE_BRACKETS index_expression RIGHT_SQUARE_BRACKETS
                {
                union YYSTYPE temp;
                temp.idnode.IDAttributes=2;
                temp.idnode.IDvalue=$1.IDvalue;
                $$=temp.idnode;
                };

arrays_declaration:VAR SAVE_IDENTIFERS LEFT_SQUARE_BRACKETS const_index_expression RIGHT_SQUARE_BRACKETS type
                {
                //if SAVE_IDENTIFERS not return 1 to expression error than creat the item in table
                };                
                

consts_declaration:
                CONST SAVE_IDENTIFERS ASSIGNMENT constant_exp{
                //if SAVE_IDENTIFERS not return 1 to expression error constant_exp is pass
                //than creat the item in table
                printf("Variables_declaration:%s\n",$4);
                };
                
Variables_declaration:
                VAR SAVE_IDENTIFERS type ASSIGNMENT constant_exp{
                //if SAVE_IDENTIFERS not return 1 to expression error constant_exp is pass
                //than creat the item in table
                printf("Variables_declaration:%s\n",$5);
                }|
                VAR SAVE_IDENTIFERS type|
                arrays_declaration;
                


constant_exp:   const_number_expression{$$=std::to_string($1).c_str();}
                |const_bool_expression{$$=std::to_string($1).c_str();}|
                STRING_CONSTANTS{$$=$1;};

                
// expression                
expression:     bool_expression{$$=std::to_string($1).c_str();}|
                number_expression{$$=std::to_string($1).c_str();}|
                STRING_CONSTANTS{$$=$1;};
                
                

const_index_expression:
                const_number_expression{$$=int($1);};
                
index_expression:
                number_expression{$$=int($1);};
                
const_number_expression:
                LEFT_PARENTHESE number_expression RIGHT_PARENTHESE{$$=$2;}|
                number_expression ARITHMETIC_ADD number_expression{$$=$1+$3;}|
                number_expression ARITHMETIC_SUB number_expression{$$=$1-$3;}|
                number_expression ARITHMETIC_MUL number_expression{$$=$1*$3;}|
                number_expression ARITHMETIC_DIV number_expression{$$=$1/$3;}|
                number_expression EXPONENTIATION number_expression{$$=pow($1,$3);}|
                ARITHMETIC_SUB number_expression %prec UMINUS{$$=-$2;}|
                ARITHMETIC_ADD number_expression %prec UADD{$$=$2;}|
                commponent
                {
                    if($1.IDAttributes!=1)
                    {
                        Trace("must be a const\n");
                        //return 1;
                    }
                    if(isNum($1.IDvalue))
                         $$ = atof($1.IDvalue);
                    else
                    {
                        Trace("must be a number\n");
                        //return 1;
                    }
                };
            
number_expression: 
                LEFT_PARENTHESE number_expression RIGHT_PARENTHESE{$$=$2;}|
                number_expression ARITHMETIC_ADD number_expression{$$=$1+$3;}|
                number_expression ARITHMETIC_SUB number_expression{$$=$1-$3;}|
                number_expression ARITHMETIC_MUL number_expression{$$=$1*$3;}|
                number_expression ARITHMETIC_DIV number_expression{$$=$1/$3;}|
                number_expression EXPONENTIATION number_expression{$$=pow($1,$3);}|
                ARITHMETIC_SUB number_expression %prec UMINUS{$$=-$2;}|
                ARITHMETIC_ADD number_expression %prec UADD{$$=$2;}|
                commponent
                {
                    if(isNum($1.IDvalue))
                         $$ = atof($1.IDvalue);
                    else
                    {
                        Trace("must be a number\n");
                        //return 1;
                    }
                };

const_bool_expression:
                const_number_expression RELATIONAL_BIG const_number_expression{$$=($1>$3);}|
                const_number_expression RELATIONAL_LEAST const_number_expression{$$=($1<$3);}|
                const_number_expression RELATIONAL_LEAST_EQ const_number_expression{$$=($1<=$3);}|
                const_number_expression RELATIONAL_BIG_EQ const_number_expression{$$=($1>=$3);}|
                const_number_expression RELATIONAL_EQ const_number_expression{$$=($1==$3);}|
                const_number_expression RELATIONAL_NEQ const_number_expression{$$=($1!=$3);}|
                LEFT_PARENTHESE const_bool_expression RIGHT_PARENTHESE{$$=$2;}|
                const_bool_expression AND const_bool_expression{$$=($1&$3);}|
                const_bool_expression OR const_bool_expression{$$=($1|$3);}|
                NOT const_bool_expression{$$=!$2;}|
                BOOLEAN_CONSTANTS_FALSE{$$=$1;}|
                BOOLEAN_CONSTANTS_TRUE{$$=$1;};

bool_expression:number_expression RELATIONAL_BIG number_expression{$$=($1>$3);}|
                number_expression RELATIONAL_LEAST number_expression{$$=($1<$3);}|
                number_expression RELATIONAL_LEAST_EQ number_expression{$$=($1<=$3);}|
                number_expression RELATIONAL_BIG_EQ number_expression{$$=($1>=$3);}|
                number_expression RELATIONAL_EQ number_expression{$$=($1==$3);}|
                number_expression RELATIONAL_NEQ number_expression{$$=($1!=$3);}|
                LEFT_PARENTHESE bool_expression RIGHT_PARENTHESE{$$=$2;}|
                bool_expression AND bool_expression{$$=($1&$3);}|
                bool_expression OR bool_expression{$$=($1|$3);}|
                NOT bool_expression{$$=!$2;}|
                BOOLEAN_CONSTANTS_FALSE{$$=$1;}|
                BOOLEAN_CONSTANTS_TRUE{$$=$1;};
                
commponent:     INTEGER_CONSTANTS{
                union YYSTYPE temp;
                temp.idnode.IDAttributes=1;
                temp.idnode.IDvalue=std::to_string($1).c_str();
                $$=temp.idnode;
                }|
                REAL_CONSTANTS{
                union YYSTYPE temp;
                temp.idnode.IDAttributes=1;
                temp.idnode.IDvalue=std::to_string($1).c_str();
                $$=temp.idnode;
                }|
                IDENTIFERS{$$=$1;}|
                arrays_variable{$$=$1;};
                
                
/*
//other
semi:           SEMICOLON
                {
                Trace("Reducing to semi\n");
                }
                ;
                */
%%


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

