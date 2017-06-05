%{
#include <iostream>
#include <string>
#include<map>
#include<list>
#include "y.tab.h"
#define MAX_LINE_LENG 1024
#define BOOLTYPE 1
#define INTTYPE 2
#define REALTYPE 3
#define STRINGTYPE 4
#define VOIDTYPE 5
#define ERROR_ATTRIBUTE -1
#define FUNC_ATTRIBUTE 0
#define CONST_ATTRIBUTE 1
#define VAR_ATTRIBUTE 2
#define ARRAY_ATTRIBUTE 3
#define LIST     {strcat(buf,yytext);strcat(temp,yytext);}
#define tokenInteger(t,i) {LIST; printf("<%s:%d>\n","t",i);}
#define tokenid(t,s) {LIST; printf("<%s:%s>\n","t",s);}
using namespace std;
string type_name[6]={"none","int","int","int","string","void"};
string attr_name[5]={"ERROR","FUNC","CONST","VAR","ARRAY"};
int linenum = 0;
char buf[MAX_LINE_LENG];
char temp[MAX_LINE_LENG];
string temp_buf;
string str_temp="";
extern "C"{
    int yywrap(void)
    {
        return 1;
    }
}
class id_node{
public:
    id_node(){
        IDtable_count=0;
        IDnumber=1;
        IDname="none";
        IDtype=-1;
        IDAttributes=-1;
        IDvalue="none";
        Scope="gobal";
    }
    id_node(int number,string name,int types,int attributes,string value,string scope){
        IDtable_count=0;
        IDnumber=number;
        IDname=name;
        IDtype=types;
        IDAttributes=attributes;
        IDvalue=value;
        Scope=scope;
    }
    string get_IDname(){return IDname;}
    int get_IDnumber(){return IDnumber;}
    int get_IDtype(){return IDtype;}
    int get_IDAttributes(){return IDAttributes;}
    int get_count(){return IDtable_count;}
    string get_IDvalue(){return IDvalue;}
    void set_count(int index){IDtable_count=index;}
    string set_IDvalue(string new_value){
    IDvalue=new_value;
    return IDvalue;}
    string set_name(string name){IDname=name;return name;}
    string set_scope(string name){Scope=name;return Scope;}
    void print_node(){
        printf("IDScope:%s\nIDname:%s\nIDtype:%s\nIDAttributes:%s\nIDvalue:%s\nIDnumber:%d\n",Scope.c_str(),IDname.c_str(),type_name[IDtype].c_str(),attr_name[1+ IDAttributes].c_str(),IDvalue.c_str(),IDnumber);
    }
private:
    int IDtable_count;
    int IDnumber;
    string IDname;
    int IDtype;
    int IDAttributes;//function(0) or const(1) or var(2)
    string IDvalue;
    string Scope;
};

class Hash { 
public: 
    Hash(string name){
        counter=0;
        scope_name=name;
    } 
    int lookout(string s){
        map<string,id_node>::iterator temp=hash_table_string.find(s);
        if (temp==hash_table_string.end())
            return -1;
        return temp->second.get_IDnumber();
    }
    id_node get_data(string s){
        map<string,id_node>::iterator temp=hash_table_string.find(s);
        return temp->second;
    }
    void update(string name,string value){
        map<string,id_node>::iterator temp1=hash_table_string.find(name);
        int index=temp1->second.get_count();
        map<int,id_node>::iterator temp2=hash_table_int.find(index);
        hash_table_string.erase(temp1);
        hash_table_int.erase(temp2);
        id_node temp=temp1->second;
        temp.set_IDvalue(value);
        hash_table_string[name]=temp;
        hash_table_int[index]=temp;
    }
    int insert(id_node node){
        if(lookout(node.get_IDname())==-1){
            node.set_count(counter);
            hash_table_string[node.get_IDname()]=node;
            hash_table_int[counter]=node;
            counter++;
            return counter-1;
        }
        return counter;
    }
    void dump(){
        for (map<int,id_node>::iterator it=hash_table_int.begin(); it!=hash_table_int.end(); ++it)
        {
            printf("------ID print: %d ------ \n ",it->first);
            it->second.print_node();
            printf("------------------------- \n ",it->first);
        }
    }
    int get_counter(){return counter;}
    int set_counter(int index){counter=index;}
    string get_name(){return scope_name;}
private:
    int counter;
    string scope_name;
    map<int,id_node> hash_table_int;
    map<string,id_node> hash_table_string;
};

Hash create_table(){
    Hash temp("table");
    return temp;
}
void clear_linebuf(char* s){
        memset(s,0,sizeof(buf));
}
void touper(char* s){
    for(int i=0;i<sizeof(temp);++i)
    {    
        if(s[i]<='z'&& s[i]>='a')
            s[i]-=32;
    }
}
int token(string name,int TokenIndex){
    clear_linebuf(temp);
    LIST;
    if(name.compare("keyword")==0)
        touper(temp);
    //printf("<%s:'%s'>\n",name.c_str(),temp);
    clear_linebuf(temp);
    return TokenIndex;
}
string temp_s[45]={"bool","break","case","const","continue","default","else","for","func","go","if","import","int","nil","print","println","real","return","string","struct","switch","type","var","void","while","read","+","-","*","/","<","<=",">=",">","==","!=","+=","-=","*=","/=","false","true","&","!","|"};
int slove_sparce(){
    int init=258,i=0;
    for(i=0;i<45;i++,init++){
        string temp1=yytext;
        if(temp_s[i]==temp1)
            break;
    }
    //printf("xd<%s> %d\n",yytext,init);
    switch(init)
    {
        case 0+258:
            yylval.int_types=BOOLTYPE;
            break;
        case 12+258:
            yylval.int_types=INTTYPE;
            break;
        case 16+258:
            yylval.int_types=REALTYPE;
            break;
        case 18+258:
            yylval.int_types=STRINGTYPE;
            break;
        case 23+258:
            yylval.int_types=VOIDTYPE;
            break;
            
    }
    return init;
}
%}
%x String_Constants
%x comment
Comments_one \/\/[^\n]*
Comments_start_mul \/\*
Comments_end_mul \*\/
keywords bool|break|case|const|continue|default|else|for|func|go|if|import|int|nil|print|println|real|return|string|struct|switch|type|var|void|while|read
comma [,]
colon [:]
semicolon [;]
line_feed [\n]
space_feed [\ ]+
tab_feed [\t]+


left_parenthese [(]
right_parenthese [)]
left_square_brackets [[]
right_square_brackets []]
left_brackets [{]
right_brackets [}]
arithmetic "+"|"-"|"*"|"/"
exponentiation [\^]
remainder [\%]
relational <|<=|>=|>|==|!=
logical [&|!]
assignment [=]
compound_operators \+=|\-=|\*=|\/=

Integer_Constants [0-9]+
Boolean_Constants "false"|"true"
identifier [a-zA-Z][a-zA-Z0-9]*
Real_Constants ([0-9]+"."?[0-9]*([Ee][+|-]?[0-9]*)?)|([0-9]*"."?[0-9]+([Ee][+|-]?[0-9]*)?)
error_simple .

%%
{Comments_one} LIST
{Comments_start_mul} {BEGIN comment;LIST}
<comment>{Comments_end_mul} {BEGIN 0;LIST}
<comment>\n {linenum++;clear_linebuf(buf);}
<comment>. {LIST}


{keywords} %{return token("keyword", slove_sparce());%}
{comma} %{return token("COMMA", COMMA);%}
{colon} %{return token("COLON", COLON);%}
{semicolon} %{return token("SEMICOLON", SEMICOLON);%}
{line_feed} %{
            linenum++;
            temp_buf.assign(buf);
            if(temp_buf.compare("")!=0)
                //printf("/* %d: %s*/\n ",linenum,buf);
            clear_linebuf(buf);
            clear_linebuf(temp);
            %}
{tab_feed} LIST
{space_feed} LIST
{left_parenthese} %{return token("LEFT_PARENTHESE", LEFT_PARENTHESE);%}
{right_parenthese} %{return token("RIGHT_PARENTHESE", RIGHT_PARENTHESE);%}
{left_square_brackets} %{return token("LEFT_SQUARE_BRACKETS", LEFT_SQUARE_BRACKETS);%}
{right_square_brackets} %{return token("RIGHT_SQUARE_BRACKETS", RIGHT_SQUARE_BRACKETS);%}
{left_brackets} %{return token("LEFT_BRACKETS", LEFT_BRACKETS);%}
{right_brackets} %{return token("RIGHT_BRACKETS", RIGHT_BRACKETS);%}

{arithmetic} %{return token("arithmetic", slove_sparce());%}
{exponentiation} %{return token("EXPONENTIATION", EXPONENTIATION);%}
{remainder} %{return token("REMAINDER", REMAINDER);%}
{relational} %{return token("relational", slove_sparce());%}
{logical} %{return token("LOGICAL", slove_sparce());%}
{assignment} %{return token("ASSIGNMENT", ASSIGNMENT);%}
{compound_operators} %{return token("compound_operators", slove_sparce());%}


{Integer_Constants} %{sscanf(yytext, "%d", &yylval.int_types);return token("Integer_Constants",INTEGER_CONSTANTS);%}     
{Real_Constants} %{yylval.real_types=atof(yytext); return token("REAL_CONSTANTS",REAL_CONSTANTS);%}
{Boolean_Constants} %{yylval.bool_types=strcmp(yytext,"false"); return token("Boolean_Constants",slove_sparce());%}

{identifier} %{
            //Symbol_Tables.insert(yytext);
            yylval.string_types=new string(yytext);
            return token("identifier",IDENTIFIER);
            %}

            
\" {
    BEGIN String_Constants;
    str_temp="";
    LIST;
    }
    
<String_Constants>\"\" {str_temp+="\"";LIST;}
<String_Constants>\n {exit(-1);}
<String_Constants>\" {BEGIN 0;
yylval.string_types=new string(str_temp.c_str());
LIST;
return STRING_CONSTANTS;
}
<String_Constants>. {str_temp+=yytext;LIST;}


{error_simple} %{
            printf("error[%d]: %s\n",linenum,yytext);
            return ERROR_SIMPLE;
            %}
%% 

/*
int main()
{
    yylex();
}
*/
