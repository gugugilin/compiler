%{
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>  
#include <math.h>
#include <map>
#include "lex.yy.c"
#define Trace(t) {printf("[%d]:%s",linenum,t);}
const int MINUS=500;
const int PLAUS=501;
using namespace std;
Hash out_scope_table;
list<string> scope_name;
list<Hash> scope_list;
string current_scop;
int idcount;
void yyerror(char * msg);
void scope_init(){
    string name="goble";
    Hash temp;
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
    Hash temp;
    scope_name.push_front(name);
    scope_list.push_front(temp);
    current_scop=name;
}
void exit_scope(){
    scope_name.pop_front();
    scope_list.pop_front();
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
    out_scope_table.insert(new_data);
    scope_list.push_front(temp);
    return 1;
}
void update_data(string name,string value){
    list<Hash>::iterator it=scope_list.end();
    for(--it;it!=scope_list.begin();--it){
        if(it->lookout(name)){
            it->update(name,value);
            break;
        }
    }
    if(it->lookout(name)){
        it->update(name,value);
    }
}

id_node current_lookout_data(string name){
    Hash temp=scope_list.front();
    id_node new_data(1,name,-1,-1,"0",current_scop);
    if (temp.lookout(name)==-1)
    {
        return new_data;
    }
    return temp.get_data(name);
}
id_node lookout_data(string name){
    list<Hash>::iterator it=scope_list.end();
    for(--it;it!=scope_list.begin();--it){
        if(it->lookout(name)){
            return it->get_data(name);
        }
    }
    if(it->lookout(name)){
        return it->get_data(name);
    }
    id_node new_data(1,name,-1,-1,"0",current_scop);
    new_data.print_node();
    return new_data;
}
void insert_scope(string name){
    Hash temp;
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
id_union::node slove(int op,id_union::node& t1,id_union::node& t2){
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
            break;
        case ARITHMETIC_SUB:
            if(isnum(t1,t2)){
            double answer=atof(t1.IDvalue->c_str())-atof(t2.IDvalue->c_str());
            t1.IDvalue=new string(to_string(answer).c_str());
            if(t1.IDtype!=t2.IDtype) t1.IDtype=REALTYPE;
            temp=t1;
            }
            else temp=create_idnode(ERROR_ATTRIBUTE,-1,1,"0").idnode;
            break;
        case ARITHMETIC_MUL:
            if(isnum(t1,t2)){
            double answer=atof(t1.IDvalue->c_str())*atof(t2.IDvalue->c_str());
            t1.IDvalue=new string(to_string(answer).c_str());
            if(t1.IDtype!=t2.IDtype) t1.IDtype=REALTYPE;
            temp=t1;
            }
            else temp=create_idnode(ERROR_ATTRIBUTE,-1,1,"0").idnode;
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
            break;
        case PLAUS:
            if(isnum(t1,t1)){temp=t1;}
            else temp=create_idnode(ERROR_ATTRIBUTE,-1,1,"0").idnode;
            break;
        case RELATIONAL_BIG:
            if(isnum(t1,t2)){
            bool answer=atof(t1.IDvalue->c_str())>atof(t2.IDvalue->c_str());
            t1.IDvalue=new string(to_string(answer).c_str());
            if(t1.IDtype!=t2.IDtype) t1.IDtype=BOOLTYPE;
            temp=t1;
            }
            else temp=create_idnode(ERROR_ATTRIBUTE,-1,1,"0").idnode;
            break;
        case RELATIONAL_BIG_EQ:
            if(isnum(t1,t2)){
            bool answer=atof(t1.IDvalue->c_str())>=atof(t2.IDvalue->c_str());
            t1.IDvalue=new string(to_string(answer).c_str());
            if(t1.IDtype!=t2.IDtype) t1.IDtype=BOOLTYPE;
            temp=t1;
            }
            else temp=create_idnode(ERROR_ATTRIBUTE,-1,1,"0").idnode;
            break;
        case RELATIONAL_LEAST:
            if(isnum(t1,t2)){
            bool answer=atof(t1.IDvalue->c_str())<atof(t2.IDvalue->c_str());
            t1.IDvalue=new string(to_string(answer).c_str());
            if(t1.IDtype!=t2.IDtype) t1.IDtype=BOOLTYPE;
            temp=t1;
            }
            else temp=create_idnode(ERROR_ATTRIBUTE,-1,1,"0").idnode;
            break;
        case RELATIONAL_LEAST_EQ:
            if(isnum(t1,t2)){
            bool answer=atof(t1.IDvalue->c_str())<=atof(t2.IDvalue->c_str());
            t1.IDvalue=new string(to_string(answer).c_str());
            if(t1.IDtype!=t2.IDtype) t1.IDtype=BOOLTYPE;
            temp=t1;
            }
            else temp=create_idnode(ERROR_ATTRIBUTE,-1,1,"0").idnode;
            break;
        case RELATIONAL_EQ:
            if(isnum(t1,t2)){
            bool answer=atof(t1.IDvalue->c_str())==atof(t2.IDvalue->c_str());
            t1.IDvalue=new string(to_string(answer).c_str());
            if(t1.IDtype!=t2.IDtype) t1.IDtype=BOOLTYPE;
            temp=t1;
            }
            else temp=create_idnode(ERROR_ATTRIBUTE,-1,1,"0").idnode;
            break;
        case RELATIONAL_NEQ:
            if(isnum(t1,t2)){
            bool answer=atof(t1.IDvalue->c_str())!=atof(t2.IDvalue->c_str());
            t1.IDvalue=new string(to_string(answer).c_str());
            if(t1.IDtype!=t2.IDtype) t1.IDtype=BOOLTYPE;
            temp=t1;
            }
            else temp=create_idnode(ERROR_ATTRIBUTE,-1,1,"0").idnode;
            break;
        case AND:
            if(t1.IDtype==BOOLTYPE&&t2.IDtype==BOOLTYPE){
            bool answer=(atof(t1.IDvalue->c_str())==1)&(atof(t2.IDvalue->c_str())==1);
            t1.IDvalue=new string(to_string(answer).c_str());
            temp=t1;
            }
            else temp=create_idnode(ERROR_ATTRIBUTE,-1,1,"0").idnode;
            break;
        case OR:
            if(t1.IDtype==BOOLTYPE&&t2.IDtype==BOOLTYPE){
            bool answer=(atof(t1.IDvalue->c_str())==1)&(atof(t2.IDvalue->c_str())==1);
            t1.IDvalue=new string(to_string(answer).c_str());
            temp=t1;
            }
            else temp=create_idnode(ERROR_ATTRIBUTE,-1,1,"0").idnode;
            break;
        case NOT:
            if(t1.IDtype==BOOLTYPE&&t1.IDtype==BOOLTYPE){
            bool answer=!(atof(t1.IDvalue->c_str())==1);
            t1.IDvalue=new string(to_string(answer).c_str());
            temp=t1;
            }
            else temp=create_idnode(ERROR_ATTRIBUTE,-1,1,"0").idnode;
            break;
    }
    return temp;
}

%}

/* tokens */

%union{
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
%token <int_types>VOID
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
%type<int_types> index_expression type const_index_expression
%type<idnode> IDENTIFERS commponent arrays_variable constant_exp expression SAVE_IDENTIFERS statement bool_expression number_expression func_invo


%%
start_symbol:   program 
                {
                    Trace("Reducing to start_symbol\n");
                };
program:        statements|declarations
                {
                    Trace("Reducing to program\n");
                };
ex_function:    FUNC type SAVE_IDENTIFERS LEFT_PARENTHESE {
                    inser_data(1,$3.IDname->c_str(),"0",$2,FUNC_ATTRIBUTE);
                    add_scope($3.IDname->c_str());
                    inser_data(1,$3.IDname->c_str(),"0",$2,FUNC_ATTRIBUTE);
                };
function:       ex_function  formal_arguments RIGHT_PARENTHESE LEFT_BRACKETS statements RIGHT_BRACKETS{exit_scope();};

formal_arguments:/*empty*/|formal_argument{};

formal_argument: SAVE_IDENTIFERS type{
                    inser_data(1,$1.IDname->c_str(),"0",$2,VAR_ATTRIBUTE);
                }|
                SAVE_IDENTIFERS type COMMA formal_argument{
                    inser_data(1,$1.IDname->c_str(),"0",$2,VAR_ATTRIBUTE);
                };

func_invo:      IDENTIFERS LEFT_PARENTHESE comm_expression RIGHT_PARENTHESE{$$=$1;};

comm_expression:/*empty*/|expression|comm_expression COMMA comm_expression{};

Compound:       LEFT_BRACKETS statements RIGHT_BRACKETS{};

Conditional:    IF LEFT_PARENTHESE bool_expression RIGHT_PARENTHESE Compound ELSE Compound|
                IF LEFT_PARENTHESE bool_expression RIGHT_PARENTHESE Compound{};

LOOP:           FOR LEFT_PARENTHESE statements SEMICOLON bool_expression SEMICOLON statements RIGHT_PARENTHESE Compound{};

ex_Procedure:   GO IDENTIFERS LEFT_PARENTHESE{add_scope("Procedure");};
Procedure:      ex_Procedure comm_expression RIGHT_PARENTHESE{
                    exit_scope();
                };

statements:     declarations statements  |
                statement statements|
                /*empty*/ 
                {
                    Trace("Reducing to statements\n");
                };
                
                
statement:      Compound|LOOP|function|Conditional|Procedure|
                IDENTIFERS ASSIGNMENT expression{
                    //if IDAttributes of IDENTIFERS is 1 than return 1 to expression error
                    if($1.IDAttributes==CONST_ATTRIBUTE)
                    {
                        yyerror("const variables can't change\n");
                        return 1;
                    }
                    if($1.IDAttributes==ARRAY_ATTRIBUTE)
                    {
                        yyerror("It's array variables\n");
                        return 1;
                    }
                    if($1.IDtype!=$3.IDtype){
                        if(!(($1.IDtype==INTTYPE&&$3.IDtype==REALTYPE)||($3.IDtype==INTTYPE&&$1.IDtype==REALTYPE)))
                        {
                            yyerror("can't convert the type\n");
                            return 1;
                        }
                    }
                    update_data($1.IDname->c_str(),$3.IDvalue->c_str());
                    
                }|
                arrays_variable ASSIGNMENT expression{
                    //if IDAttributes of IDENTIFERS is 1 than return 1 to expression error
                    if($1.IDAttributes==CONST_ATTRIBUTE)
                    {
                        yyerror("const variables can't change\n");
                        return 1;
                    }
                    if($1.IDtype!=$3.IDtype){
                        if(!(($1.IDtype==INTTYPE&&$3.IDtype==REALTYPE)||($3.IDtype==INTTYPE&&$1.IDtype==REALTYPE)))
                        {
                            yyerror("can't convert the type\n");
                            return 1;
                        }
                    }
                    update_data($1.IDname->c_str(),$3.IDvalue->c_str());
                }|
                PRINT expression{printf("%s ",$2.IDvalue->c_str());}|
                PRINTLN expression{printf(" %s \n",$2.IDvalue->c_str());}|
                READ IDENTIFERS|
                RETURN |
                RETURN expression
                {
                    $$=$2;
                    Trace("Reducing to statement\n");
                };

                                
                
                
//declaration
type:           VOID{$$=$1;}|
                BOOL{$$=$1;}|
                INT{$$=$1;}|
                REAL{$$=$1;}|
                STRING{$$=$1;};
       
SAVE_IDENTIFERS:IDENTIFIER{
                //if find the Id in table than return 1 to expression error
                //else not do anything
                union YYSTYPE temp;
                id_node temp_id = current_lookout_data($1->c_str());
                if (temp_id.get_IDAttributes()==ERROR_ATTRIBUTE)
                {
                    temp.idnode.IDAttributes=CONST_ATTRIBUTE;
                    temp.idnode.IDtype=0;
                    temp.idnode.IDnumber=1;
                    temp.idnode.IDvalue=new string("0");
                    temp.idnode.IDname=new string(temp_id.get_IDname().c_str());
                    $$=temp.idnode;
                }
                else{
                    yyerror("redeclaration error");
                    return 1;
                }
                };
       
IDENTIFERS:    IDENTIFIER{
                // must find the value and the attrubutes to ASSIGNMENT in table
                // if not find return 1 to expression error
                union YYSTYPE temp;
                id_node temp_id = lookout_data($1->c_str());
                if (temp_id.get_IDAttributes()==ERROR_ATTRIBUTE)
                {
                    yyerror("not define declaration");
                    return 1;
                }
                temp.idnode.IDAttributes=temp_id.get_IDAttributes();
                temp.idnode.IDtype=temp_id.get_IDtype();
                temp.idnode.IDnumber=temp_id.get_IDnumber();
                temp.idnode.IDvalue=new string(temp_id.get_IDvalue().c_str());
                temp.idnode.IDname=new string(temp_id.get_IDname().c_str());
                $$=temp.idnode;
                };
                                
                        
declarations:   declaration declarations|/*empty*/;
                
declaration:    Variables_declaration|
                consts_declaration;
                

arrays_variable:IDENTIFERS LEFT_SQUARE_BRACKETS index_expression RIGHT_SQUARE_BRACKETS
                {
                    if ($1.IDAttributes!=ARRAY_ATTRIBUTE){
                        yyerror("not ARRAY_type");
                        return 1;
                    }
                    if ($3<=$1.IDnumber&& $3>=0){
                        $$=$1;
                    }
                    else{ 
                        printf("xd:%d %d\n",$1.IDnumber,$3);
                        yyerror("ARRAY index error");
                        return 1;
                    }
                };

arrays_declaration:VAR SAVE_IDENTIFERS LEFT_SQUARE_BRACKETS const_index_expression RIGHT_SQUARE_BRACKETS type
                {
                //if SAVE_IDENTIFERS not return 1 to expression error than creat the item in table
                    inser_data($4,$2.IDname->c_str(),"0",$6,ARRAY_ATTRIBUTE);
                };                
                

consts_declaration:
                CONST SAVE_IDENTIFERS ASSIGNMENT constant_exp{
                    inser_data(1,$2.IDname->c_str(),$4.IDvalue->c_str(),$4.IDtype,CONST_ATTRIBUTE);
                    printf("Const_declaration:%s\n",$4.IDvalue->c_str());
                };
                
Variables_declaration:
                VAR SAVE_IDENTIFERS type ASSIGNMENT constant_exp{
                    //if SAVE_IDENTIFERS not return 1 to expression error constant_exp is pass
                    //than creat the item in table
                    if ($3!=$5.IDtype)
                    {
                        yyerror("type not match");
                        return 1;
                    }
                    inser_data(1,$2.IDname->c_str(),$5.IDvalue->c_str(),$3,VAR_ATTRIBUTE);
                    printf("Variables_declaration:%s\n",$5.IDvalue->c_str());
                }|
                VAR SAVE_IDENTIFERS type{
                    inser_data(1,$2.IDname->c_str(),"0",$3,VAR_ATTRIBUTE);
                    printf("Variables_declaration:%s\n",$2);
                }|
                arrays_declaration;
                


constant_exp:  expression{
                if ($1.IDAttributes!=CONST_ATTRIBUTE){
                    yyerror("must be const");
                    return 1;
                }
                $$=$1;
                };

                
// expression                
expression:     
                number_expression{$$=$1;}|bool_expression{$$=$1;}|
                STRING_CONSTANTS{$$=create_idnode(CONST_ATTRIBUTE,STRINGTYPE,1,$1->c_str()).idnode;};
                
                

const_index_expression:
                number_expression{
                if ($1.IDAttributes!=CONST_ATTRIBUTE){
                    yyerror("must be const");
                    return 1;
                }
                $$=atoi($1.IDvalue->c_str());
                };
                
index_expression:
                number_expression{$$=atoi($1.IDvalue->c_str());};
                            
number_expression: 
                LEFT_PARENTHESE number_expression RIGHT_PARENTHESE{$$=$2;if ($$.IDAttributes==ERROR_ATTRIBUTE) return 1;}|
                
                number_expression ARITHMETIC_ADD number_expression{
                $$=slove(ARITHMETIC_ADD,$1,$3);
                if ($$.IDAttributes==ERROR_ATTRIBUTE) 
                return 1;
                }|
                number_expression ARITHMETIC_SUB number_expression{$$=slove(ARITHMETIC_SUB,$1,$3);if ($$.IDAttributes==ERROR_ATTRIBUTE) return 1;}|
                number_expression ARITHMETIC_MUL number_expression{$$=slove(ARITHMETIC_MUL,$1,$3);if ($$.IDAttributes==ERROR_ATTRIBUTE) return 1;}|
                number_expression ARITHMETIC_DIV number_expression{$$=slove(ARITHMETIC_DIV,$1,$3);if ($$.IDAttributes==ERROR_ATTRIBUTE) return 1;}|
                number_expression EXPONENTIATION number_expression{$$=slove(EXPONENTIATION,$1,$3);if ($$.IDAttributes==ERROR_ATTRIBUTE) return 1;}|
                ARITHMETIC_SUB number_expression %prec UMINUS{$$=slove(MINUS,$2,$2);if ($$.IDAttributes==ERROR_ATTRIBUTE) return 1;}|
                ARITHMETIC_ADD number_expression %prec UADD{$$=slove(PLAUS,$2,$2);if ($$.IDAttributes==ERROR_ATTRIBUTE) return 1;}|
                commponent{$$=$1;if ($$.IDAttributes==ERROR_ATTRIBUTE) return 1;};


bool_expression:number_expression RELATIONAL_BIG number_expression{$$=slove(RELATIONAL_BIG,$1,$3);if ($$.IDAttributes==ERROR_ATTRIBUTE) return 1;}|
                number_expression RELATIONAL_LEAST number_expression{$$=slove(RELATIONAL_LEAST,$1,$3);if ($$.IDAttributes==ERROR_ATTRIBUTE) return 1;}|
                number_expression RELATIONAL_LEAST_EQ number_expression{$$=slove(RELATIONAL_LEAST_EQ,$1,$3);if ($$.IDAttributes==ERROR_ATTRIBUTE) return 1;}|
                number_expression RELATIONAL_BIG_EQ number_expression{$$=slove(RELATIONAL_BIG_EQ,$1,$3);if ($$.IDAttributes==ERROR_ATTRIBUTE) return 1;}|
                number_expression RELATIONAL_EQ number_expression{$$=slove(RELATIONAL_EQ,$1,$3);if ($$.IDAttributes==ERROR_ATTRIBUTE) return 1;}|
                number_expression RELATIONAL_NEQ number_expression{$$=slove(RELATIONAL_NEQ,$1,$3);if ($$.IDAttributes==ERROR_ATTRIBUTE) return 1;}|
                LEFT_PARENTHESE bool_expression RIGHT_PARENTHESE{$$=$2;if ($$.IDAttributes==ERROR_ATTRIBUTE) return 1;}|
                bool_expression AND bool_expression{$$=slove(AND,$1,$3);if ($$.IDAttributes==ERROR_ATTRIBUTE) return 1;}|
                bool_expression OR bool_expression{$$=slove(OR,$1,$3);if ($$.IDAttributes==ERROR_ATTRIBUTE) return 1;}|
                NOT bool_expression{$$=slove(NOT,$2,$2);if ($$.IDAttributes==ERROR_ATTRIBUTE) return 1;}|
                BOOLEAN_CONSTANTS_FALSE{$$=create_idnode(CONST_ATTRIBUTE,BOOLTYPE,1,std::to_string($1)).idnode;}|
                BOOLEAN_CONSTANTS_TRUE{$$=create_idnode(CONST_ATTRIBUTE,BOOLTYPE,1,std::to_string($1)).idnode;};
                            
                
commponent:     
                INTEGER_CONSTANTS{
                $$=create_idnode(CONST_ATTRIBUTE,INTTYPE,1,std::to_string($1)).idnode;
                }|
                REAL_CONSTANTS{
                $$=create_idnode(CONST_ATTRIBUTE,REALTYPE,1,std::to_string($1)).idnode;
                }|
                func_invo{$$=$1;}|
                IDENTIFERS{$$=$1;}|
                arrays_variable{$$=$1;};
                
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
    dump_table();
}

