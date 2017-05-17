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
#define LIST     {strcat(buf,yytext);strcat(temp,yytext);}
#define tokenInteger(t,i) {LIST; printf("<%s:%d>\n","t",i);}
#define tokenid(t,s) {LIST; printf("<%s:%s>\n","t",s);}
using namespace std;
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

class Hash { 
public: 
    Hash(){
        counter=0;
    } 
    int lookout(string s){
        map<string,int>::iterator temp=hash_table_string.find(s);
        if (temp==hash_table_string.end())
            return -1;
        return temp->second;
    }
    int insert(string s){
        if(lookout(s)==-1){
            hash_table_string[s]=counter;
            hash_table_int[counter]=s;
            counter++;
            return counter-1;
        }
        return counter;
    }
    string lookout(int index){
        map<int,string>::iterator temp=hash_table_int.find(index);
        if (temp==hash_table_int.end())
            return "Not found";
        return temp->second;
    }
    void dump(){
        for (map<int,string>::iterator it=hash_table_int.begin(); it!=hash_table_int.end(); ++it)
            printf("%d => %s \n",it->first,it->second.c_str());
    }
private:
    int counter;
    map<int,string> hash_table_int;
    map<string,int> hash_table_string;
};

Hash Symbol_Tables;
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
    printf("<%s:'%s'>\n",name.c_str(),temp);
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
        case 0:
            yylval.int_types=BOOLTYPE;
            break;
        case 12:
            yylval.int_types=INTTYPE;
            break;
        case 16:
            yylval.int_types=REALTYPE;
            break;
        case 18:
            yylval.int_types=STRINGTYPE;
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
comma [']
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
<comment>\n {linenum++;printf("%d: %s\n",linenum,buf);clear_linebuf(buf);}
<comment>. {LIST}


{keywords} %{return token("keyword", slove_sparce());%}
{comma} %{return token("COMMA", COMMA);%}
{colon} %{return token("COLON", COLON);%}
{semicolon} %{return token("SEMICOLON", SEMICOLON);%}
{line_feed} %{
            linenum++;
            temp_buf.assign(buf);
            if(temp_buf.compare("")!=0)
                printf("%d: %s\n",linenum,buf);
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
{Real_Constants} %{sscanf(yytext, "%f", &yylval.real_types); return token("REAL_CONSTANTS",REAL_CONSTANTS);%}
{Boolean_Constants} %{yylval.bool_types=strcmp(yytext,"true"); return token("Boolean_Constants",slove_sparce());%}

{identifier} %{
            //Symbol_Tables.insert(yytext);
            sscanf(yytext, "%s", &yylval.string_types);
            return token("identifier",IDENTIFIER);
            %}

            
\" {
    BEGIN String_Constants;
    str_temp="";
    LIST;
    }
    
<String_Constants>\"\" {str_temp+="\"";LIST;}
<String_Constants>\n {exit(-1);}
<String_Constants>\" {printf("<string:\"%s\">\n",str_temp.c_str());BEGIN 0;
sscanf(str_temp.c_str(), "%s", &yylval.string_types);
return STRING_CONSTANTS;LIST;
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
