%{
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
    Hash temp(name);
    temp.set_counter(id_counter);
    scope_name.push_front(name);
    scope_list.push_front(temp);
    scope_Llab.push_front(count_L);
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
            outstring+="ixor\n";
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
    std::list<int>* arg_types;
}
%token <int_types>BOOL
%token BREAK CASE
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
%type<string_types>ex_function
%type<arg_types> formal_argument formal_arguments comm_expression comm_expressions


%%
start_symbol:   programs {};
programs:       program programs |/*empty*/; 
program:        functions|declarations;
                
functions:      function functions|/*empty*/;
ex_function:    FUNC type SAVE_IDENTIFERS LEFT_PARENTHESE {
                    inser_data(1,$3.IDname->c_str(),"0",$2,FUNC_ATTRIBUTE);
                    id_counter=-1;
                    add_scope($3.IDname->c_str());
                    inser_data(1,$3.IDname->c_str(),"0",$2,FUNC_ATTRIBUTE);
                    $$=new string($3.IDname->c_str());
                    print_tab();
                    if(*$3.IDname!="main")
                        printf("method public static %s %s(",type_name[$2].c_str(),$3.IDname->c_str());
                    else
                        printf("method public static %s main(java.lang.String[]",type_name[$2].c_str());
                        
                };
ex1_function:   ex_function formal_arguments RIGHT_PARENTHESE LEFT_BRACKETS{
                func_map[$1->c_str()]=$2;
                if(*$1!="main")
                for (std::list<int>::iterator it=$2->begin(); it != $2->end(); ++it){
                    if(it!=--$2->end())
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
                };
function:       ex1_function statements RIGHT_BRACKETS{print_tab();printf("}\n");exit_scope();};

formal_arguments:/*empty*/{$$=new list<int>;}|formal_argument{$$=$1;};

formal_argument: SAVE_IDENTIFERS type{
                    list<int>* temp=new list<int>;
                    temp->push_front($2);
                    $$=temp;
                    inser_data(1,$1.IDname->c_str(),"0",$2,VAR_ATTRIBUTE);
                }|
                  formal_argument COMMA SAVE_IDENTIFERS type{
                    $1->push_front($4);
                    $$=$1;
                    inser_data(1,$3.IDname->c_str(),"0",$4,VAR_ATTRIBUTE);
                };

func_invo:      IDENTIFERS LEFT_PARENTHESE comm_expression RIGHT_PARENTHESE{
                map<string,list<int>*>::iterator temp=func_map.find($1.IDname->c_str());
                if(temp!=func_map.end())
                {
                    list<int>::iterator it1=temp->second->begin();
                    list<int>::iterator it2=$3->begin();
                    int count;
                    if(temp->second->size()==$3->size())
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
                $$=$1;
                $$.IDAttributes=VAR_ATTRIBUTE;
                };
comm_expression:/*empty*/{$$=new list<int>;}|comm_expressions{$$=$1;};
comm_expressions:
                expression{
                    list<int>* temp=new list<int>;
                    temp->push_front($1.IDtype);
                    $$=temp;
                }|
                expression COMMA comm_expression{
                    $3->push_front($1.IDtype);
                    $$=$3;
                };

ex_compound:    LEFT_BRACKETS{add_scope(current_scop+"_Compound");};
Compound:       ex_compound statements RIGHT_BRACKETS{exit_scope();};

Conditionals:    IF LEFT_PARENTHESE bool_expression{
                printf("%s",outstring.c_str());
                outstring="";
                print_tab();
                printf("ifeq L%s_%s\n",current_scop.c_str(),to_string(count_L).c_str());
                }RIGHT_PARENTHESE Compound{
                print_tab();
                printf("    goto L%s_%s\n",current_scop.c_str(),to_string(count_L+1).c_str());
                print_tab();
                printf("L%s_%s:\n",current_scop.c_str(),to_string(count_L).c_str());
                count_L++;
                outstring="";
                };
Conditional:    Conditionals ELSE Compound{
                print_tab();
                printf("L%s_%s:\n",current_scop.c_str(),to_string(count_L++).c_str());
                outstring="";
                }|Conditionals{
                print_tab();
                printf("L%s_%s:\n",current_scop.c_str(),to_string(count_L++).c_str());
                outstring="";};

ex_loop:        FOR LEFT_PARENTHESE{add_scope(current_scop+"_loop");};
LOOP:           ex_loop statements {
                print_tab();
                printf("L%s_%s:\n",current_scop.c_str(),to_string(count_L++).c_str());
                }  SEMICOLON bool_expression {
                printf("%s",outstring.c_str());
                outstring="";
                print_tab();
                printf("ifeq L%s_%s\n",current_scop.c_str(),to_string(count_L).c_str());
                print_tab();
                printf("goto L%s_%s\n",current_scop.c_str(),to_string(count_L+1).c_str());
                print_tab();
                printf("L%s_%s:\n",current_scop.c_str(),to_string(count_L+2).c_str());
                }SEMICOLON statements RIGHT_PARENTHESE{
                print_tab();
                printf("goto L%s_%s\n",current_scop.c_str(),to_string(count_L-3).c_str());
                print_tab();
                printf("L%s_%s:\n",current_scop.c_str(),to_string(count_L+1).c_str());
                } Compound{
                print_tab();
                printf("goto L%s_%s\n",current_scop.c_str(),to_string(count_L+2).c_str());
                print_tab();
                printf("L%s_%s:\n",current_scop.c_str(),to_string(count_L).c_str());
                count_L+=3;
                exit_scope();};
Procedure:      GO func_invo{};

statements:     declarations statements  |
                statement statements|
                /*empty*/ ;
                
                
                
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
                    
                    string index="istore "+current_lookout_index($1.IDname->c_str());
                    if(index=="istore -1"){
                        index="putstatic "+type_name[$1.IDtype]+" ";
                        index+=lookout_index($1.IDname->c_str())+"."+$1.IDname->c_str();
                    }
                    print_exp_tab();
                    outstring+=index+"\n";
                    printf("%s",outstring.c_str());
                    outstring="";
                    
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
                PRINT expression{
                string types_out=type_name[$2.IDtype];
                if(types_out=="string")
                    types_out="java.lang.String";
                print_tab();
                printf("getstatic java.io.PrintStream java.lang.System.out\n");
                printf("%s",outstring.c_str());
                print_tab();
                printf("invokevirtual void java.io.PrintStream.print(%s)\n",types_out.c_str());
                outstring="";}|
                
                PRINTLN expression{
                string types_out=type_name[$2.IDtype];
                if(types_out=="string")
                    types_out="java.lang.String";
                print_tab();
                printf("getstatic java.io.PrintStream java.lang.System.out\n");
                printf("%s",outstring.c_str());
                print_tab();
                printf("invokevirtual void java.io.PrintStream.println(%s)\n",types_out.c_str());
                outstring="";
                }|
                READ IDENTIFERS|
                RETURN {
                outstring="";
                print_tab();
                printf("return\n");
                }|
                RETURN expression{
                printf("%s",outstring.c_str());
                outstring="";
                print_tab();
                if($2.IDtype==REALTYPE)
                    printf("dreturn\n");
                if($2.IDtype==INTTYPE||$2.IDtype==BOOLTYPE)
                    printf("ireturn\n");
                if($2.IDtype==VOIDTYPE)
                    printf("return\n");
                $$=$2;};

                                
                
                
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
                    printf("name : %s\n",temp_id.get_IDname().c_str());
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
                        printf("IDAttributes %d\n",$1.IDAttributes);
                        yyerror("not ARRAY_type");
                        return 1;
                    }
                    if ($3<$1.IDnumber&& $3>=0){
                        $$=$1;
                        $$.IDAttributes=VAR_ATTRIBUTE;
                        $$.IDnumber=1;
                    }
                    else{ 
                        yyerror("ARRAY index error");
                        return 1;
                    }
                };

arrays_declaration:VAR SAVE_IDENTIFERS LEFT_SQUARE_BRACKETS const_index_expression RIGHT_SQUARE_BRACKETS type
                {
                //if SAVE_IccDENTIFERS not return 1 to expression error than creat the item in table
                    inser_data($4,$2.IDname->c_str(),"0",$6,ARRAY_ATTRIBUTE);
                    printf("/*array not support*/\n");
                    outstring="";
                };                
                

consts_declaration:
                CONST SAVE_IDENTIFERS ASSIGNMENT constant_exp{
                    
                    if(current_scop=="goble"){
                        print_tab();
                        printf("field static %s %s = %s\n",type_name[$4.IDtype].c_str(),$2.IDname->c_str(),$4.IDvalue->c_str());
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
                    inser_data(1,$2.IDname->c_str(),$4.IDvalue->c_str(),$4.IDtype,CONST_ATTRIBUTE);
                    //printf("Const_declaration:%s\n",$4.IDvalue->c_str());
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
                    if(current_scop=="goble"){
                        print_tab();
                        printf("field static %s %s = %s\n",type_name[$3].c_str(),$2.IDname->c_str(),$5.IDvalue->c_str());
                    }
                    else{
                        printf("%s",outstring.c_str());
                        print_tab();
                        if(get_current_counter()>0)
                            printf("istore %d\n",get_current_counter());
                        else
                            printf("istore 0\n");
                    }
                    inser_data(1,$2.IDname->c_str(),$5.IDvalue->c_str(),$3,VAR_ATTRIBUTE);
                    outstring="";
                    //printf("Variables_declaration:%s\n",$5.IDvalue->c_str());
                }|
                VAR SAVE_IDENTIFERS type{
                    if(current_scop=="goble"){
                        print_tab();
                        printf("field static %s %s\n",type_name[$3].c_str(),$2.IDname->c_str());
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
                    inser_data(1,$2.IDname->c_str(),"0",$3,VAR_ATTRIBUTE);
                    outstring="";
                    //printf("Variables_declaration:%s\n",$2);
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
                STRING_CONSTANTS{
                print_exp_tab();
                outstring+="ldc \""+string($1->c_str())+"\"\n";
                $$=create_idnode(CONST_ATTRIBUTE,STRINGTYPE,1,$1->c_str()).idnode;};
                
                

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
                number_expression ARITHMETIC_ADD number_expression{$$=slove(ARITHMETIC_ADD,$1,$3);if ($$.IDAttributes==ERROR_ATTRIBUTE) return 1;}|
                number_expression ARITHMETIC_SUB number_expression{$$=slove(ARITHMETIC_SUB,$1,$3);if ($$.IDAttributes==ERROR_ATTRIBUTE) return 1;}|
                number_expression ARITHMETIC_MUL number_expression{$$=slove(ARITHMETIC_MUL,$1,$3);if ($$.IDAttributes==ERROR_ATTRIBUTE) return 1;}|
                number_expression ARITHMETIC_DIV number_expression{$$=slove(ARITHMETIC_DIV,$1,$3);if ($$.IDAttributes==ERROR_ATTRIBUTE) return 1;}|
                number_expression EXPONENTIATION number_expression{$$=slove(EXPONENTIATION,$1,$3);if ($$.IDAttributes==ERROR_ATTRIBUTE) return 1;}|
                ARITHMETIC_SUB number_expression %prec UMINUS{$$=slove(MINUS,$2,$2);if ($$.IDAttributes==ERROR_ATTRIBUTE) return 1;}|
                ARITHMETIC_ADD number_expression %prec UADD{$$=slove(PLAUS,$2,$2);if ($$.IDAttributes==ERROR_ATTRIBUTE) return 1;}|
                commponent{
                $$=$1;
                if ($$.IDAttributes!=CONST_ATTRIBUTE&&$$.IDAttributes!=VAR_ATTRIBUTE){
                printf("must be a number\n");
                return 1;}};


bool_expression:LEFT_PARENTHESE bool_expression RIGHT_PARENTHESE{$$=$2;if ($$.IDAttributes==ERROR_ATTRIBUTE) return 1;}|
                number_expression RELATIONAL_BIG number_expression{$$=slove(RELATIONAL_BIG,$1,$3);if ($$.IDAttributes==ERROR_ATTRIBUTE) return 1;}|
                number_expression RELATIONAL_LEAST number_expression{$$=slove(RELATIONAL_LEAST,$1,$3);if ($$.IDAttributes==ERROR_ATTRIBUTE) return 1;}|
                number_expression RELATIONAL_LEAST_EQ number_expression{$$=slove(RELATIONAL_LEAST_EQ,$1,$3);if ($$.IDAttributes==ERROR_ATTRIBUTE) return 1;}|
                number_expression RELATIONAL_BIG_EQ number_expression{$$=slove(RELATIONAL_BIG_EQ,$1,$3);if ($$.IDAttributes==ERROR_ATTRIBUTE) return 1;}|
                number_expression RELATIONAL_EQ number_expression{$$=slove(RELATIONAL_EQ,$1,$3);if ($$.IDAttributes==ERROR_ATTRIBUTE) return 1;}|
                number_expression RELATIONAL_NEQ number_expression{$$=slove(RELATIONAL_NEQ,$1,$3);if ($$.IDAttributes==ERROR_ATTRIBUTE) return 1;}|
                bool_expression AND bool_expression{$$=slove(AND,$1,$3);if ($$.IDAttributes==ERROR_ATTRIBUTE) return 1;}|
                bool_expression OR bool_expression{$$=slove(OR,$1,$3);if ($$.IDAttributes==ERROR_ATTRIBUTE) return 1;}|
                NOT bool_expression{$$=slove(NOT,$2,$2);if ($$.IDAttributes==ERROR_ATTRIBUTE) return 1;}|
                BOOLEAN_CONSTANTS_FALSE{
                print_exp_tab();
                outstring+="iconst_"+std::to_string($1)+"\n";
                $$=create_idnode(CONST_ATTRIBUTE,BOOLTYPE,1,std::to_string($1)).idnode;}|
                BOOLEAN_CONSTANTS_TRUE{
                print_exp_tab();
                outstring+="iconst_"+std::to_string($1)+"\n";
                $$=create_idnode(CONST_ATTRIBUTE,BOOLTYPE,1,std::to_string($1)).idnode;};
                            
                
commponent:     
                INTEGER_CONSTANTS{
                print_exp_tab();
                outstring+="sipush "+std::to_string($1)+"\n";
                $$=create_idnode(CONST_ATTRIBUTE,INTTYPE,1,std::to_string($1)).idnode;
                }|
                REAL_CONSTANTS{
                print_exp_tab();
                outstring+="sipush "+std::to_string($1)+"\n";
                $$=create_idnode(CONST_ATTRIBUTE,REALTYPE,1,std::to_string($1)).idnode;
                }|
                func_invo{
                print_exp_tab();
                outstring+="invokestatic "+type_name[$1.IDtype]+" "+app_name+".";
                outstring+=string($1.IDname->c_str())+get_format($1.IDname->c_str())+"\n";
                $$=$1;}|
                IDENTIFERS{
                string index="iload "+current_lookout_index($1.IDname->c_str());
                if(index=="iload -1"){
                    index="getstatic "+type_name[$1.IDtype]+" ";
                    index+=lookout_index($1.IDname->c_str())+"."+$1.IDname->c_str();
                }
                print_exp_tab();
                outstring+=index+"\n";
                $$=$1;}|
                arrays_variable{
                print_exp_tab();
                outstring+="not support array\n";
                $$=$1;};
                
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

