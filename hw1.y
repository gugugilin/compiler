%{
#include<list>
#include<stdio.h>
#include<string>
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

%}

/* tokens */
%union{
    bool bool_types;
    int int_types;
    double real_types;
    char* string_types;
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
%type<real_types> number_expression rel_expression expression
%type<int_types> Int_expression index_expression type
%type<bool_types> bool_expression
%type<string_types> commponent constant_exp


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
                
                
statement:      IDENTIFIER ASSIGNMENT expression|
                IDENTIFIER LEFT_SQUARE_BRACKETS Int_expression RIGHT_SQUARE_BRACKETS ASSIGNMENT expression|
                PRINT expression|
                PRINTLN expression|
                READ IDENTIFIER|
                RETURN |
                RETURN expression
                {
                    Trace("Reducing to statement\n");
                };

                                
                
                
//declaration
type:           BOOL|
                INT|
                REAL|
                STRING
                {
                    Trace("Reducing to type\n");
                };
                        
declarations:   declaration declarations|
                /*empty*/
                {
                    Trace("Reducing to declarations\n");
                };
declaration:    Variables_declaration|
                consts_declaration
                {
                    Trace("Reducing to declaration\n");
                };

arrays_variable:IDENTIFIER LEFT_SQUARE_BRACKETS index_expression RIGHT_SQUARE_BRACKETS
                {
                    Trace("Reducing to arrays_variable\n");
                };
arrays_declaration:VAR IDENTIFIER LEFT_SQUARE_BRACKETS Int_expression RIGHT_SQUARE_BRACKETS type
                {
                        
                        Trace("Reducing to arrays_declaration\n");
                };
                

consts_declaration:
                CONST IDENTIFIER ASSIGNMENT constant_exp
                {
                    Trace("Reducing to consts\n");
                };
Variables_declaration:
                VAR IDENTIFIER type ASSIGNMENT constant_exp|
                VAR IDENTIFIER type|
                arrays_declaration
                {
                    Trace("Reducing to Variables\n");
                };


constant_exp:   rel_expression|
                bool_expression|
                STRING_CONSTANTS
                {
                    
                    Trace("Reducing to constant_exp\n");
                };
                
// expression                
expression:     bool_expression|
                number_expression|
                Int_expression|
                rel_expression|
                STRING_CONSTANTS
                {
                    Trace("Reducing to expression\n");
                };  
                

            
index_expression:
                Int_expression|
                IDENTIFIER
                {
                //only int;
                };
                
            
number_expression: 
                LEFT_PARENTHESE number_expression RIGHT_PARENTHESE|
                number_expression ARITHMETIC_ADD number_expression|
                number_expression ARITHMETIC_SUB number_expression|
                number_expression ARITHMETIC_MUL number_expression|
                number_expression ARITHMETIC_DIV number_expression|
                number_expression EXPONENTIATION number_expression|
                ARITHMETIC_SUB number_expression %prec UMINUS|
                ARITHMETIC_ADD number_expression %prec UADD|
                commponent
                {
                    //if  not number +-*/    ex:3+"lala"
                    Trace("Reducing to number_expression\n");
                };
rel_expression: LEFT_PARENTHESE rel_expression RIGHT_PARENTHESE|
                rel_expression ARITHMETIC_ADD rel_expression|
                rel_expression ARITHMETIC_SUB rel_expression|
                rel_expression ARITHMETIC_MUL rel_expression|
                rel_expression ARITHMETIC_DIV rel_expression|
                rel_expression EXPONENTIATION rel_expression|
                ARITHMETIC_SUB rel_expression %prec UMINUS|
                ARITHMETIC_ADD rel_expression %prec UADD|
                REAL_CONSTANTS|INTEGER_CONSTANTS
                {
                    Trace("Reducing to rel_expression\n");
                };
                
Int_expression: LEFT_PARENTHESE Int_expression RIGHT_PARENTHESE|
                Int_expression ARITHMETIC_ADD Int_expression|
                Int_expression ARITHMETIC_SUB Int_expression|
                Int_expression ARITHMETIC_MUL Int_expression|
                Int_expression ARITHMETIC_DIV Int_expression|
                Int_expression EXPONENTIATION Int_expression|
                ARITHMETIC_SUB Int_expression %prec UMINUS|
                ARITHMETIC_ADD Int_expression %prec UADD|
                INTEGER_CONSTANTS
                {
                    Trace("Reducing to Int_expression\n");
                };
                
bool_expression:number_expression RELATIONAL_BIG number_expression|
                number_expression RELATIONAL_LEAST number_expression|
                number_expression RELATIONAL_LEAST_EQ number_expression|
                number_expression RELATIONAL_BIG_EQ number_expression|
                number_expression RELATIONAL_EQ number_expression|
                number_expression RELATIONAL_NEQ number_expression|
                LEFT_PARENTHESE bool_expression RIGHT_PARENTHESE|
                bool_expression AND bool_expression|
                bool_expression OR bool_expression|
                NOT bool_expression|
                BOOLEAN_CONSTANTS_FALSE|
                BOOLEAN_CONSTANTS_TRUE
                {
                    Trace("Reducing to bool_expression\n");
                };
commponent:     INTEGER_CONSTANTS|
                REAL_CONSTANTS|
                IDENTIFIER|
                arrays_variable
                {
                    
                    Trace("Reducing to commponent\n");
                };
                
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

