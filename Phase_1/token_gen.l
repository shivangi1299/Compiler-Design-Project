%{
#include <stdio.h>
#include <string.h>
#include "y.tab.h"
int yyscope=0;
int line=0;
int sym_table_length = 0;
char dtype[10];
int terminators[100];
int terminator_index=0;
struct sym_table {
	char name[20];
	char value[50];
	int line_number;
	int scope;
	char datatype[20];
	int id_value;
}table[100];
int installID(int type, char* tmp_yytext, int yylineno, int yyscope, char* dtype);
void remove_duplicates();
void addValue(char* yytext, int yylineno);
void addvalue(int y, int yylineno);
int ispresent(char* yytext);
void print_symtable();
%}


letter [a-zA-z]
digit [0-9]


%%
(\/\/.*)[\n] {}
(\/\*.*\*\/)[\n] {}
(\/\*(.*\n)*.*\*\/)[\n] {}
\n {yylineno++; }
"int main" {return begin;}
\{ { printf("%d\t%s\t\t\t\tBRACE OPEN\n",yylineno,yytext);yyscope++; return br_open;}
\} {printf("%d\t%s\t\t\t\tBRACE CLOSE\n",yylineno,yytext);yyscope--; return br_close;}
#include[ ]<{letter}+(\.{letter}*)?> printf("%d\t%s\t\t\t\tPREPROCESSOR\n",yylineno,yytext);
&|: {printf("%d\t%s\t\t\t\tPUNCTUATION\n",yylineno,yytext); }
, {return com;}
cin printf("%d\t%s\t\t\t\tINBUILT FUNCTION\n",yylineno,yytext);
cout {printf("%d\t%s\t\t\t\tINBUILT FUNCTION\n",yylineno,yytext); return tcout;}
return|main|case|endl|switch|auto|break|case|const|continue|default|do|extern|goto|long|register|short|signed|sizeof|static|unsigned|volatile|using|namespace printf("%d\t%s\t\t\t\tKEYWORD\n",yylineno,yytext);
if {printf("%d\t%s\t\t\t\tKEYWORD\n",yylineno,yytext);return tif;}
else {printf("%d\t%s\t\t\t\tKEYWORD\n",yylineno,yytext);return telse;}
for {printf("%d\t%s\t\t\t\tKEYWORD\n",yylineno,yytext);return tfor;}
while {printf("%d\t%s\t\t\t\tKEYWORD\n",yylineno,yytext);return twhile;}
int|float|char|struct|bool|double|void|wchar_t|class|union|enum|typedef {printf("%d\t%s\t\t\t\tDATATYPE\n",yylineno,yytext); strcpy(dtype,yytext); line=yylineno; return dt;}
\"(.)*\" {printf("%d\t%s\t\t\t\tSTRING CONSTANT\n",yylineno,yytext); return s;}
>|<|>=|<=|==|!= {printf("%d\t%s\t\t\t\tOPERATOR\n",yylineno,yytext); return relop;}
\+ {printf("%d\t%s\t\t\t\tOPERATOR\n",yylineno,yytext);return addop;}
\* {printf("%d\t%s\t\t\t\tOPERATOR\n",yylineno,yytext);return mulop;}
\/ {printf("%d\t%s\t\t\t\tOPERATOR\n",yylineno,yytext);return divop;}
\- {printf("%d\t%s\t\t\t\tOPERATOR\n",yylineno,yytext);return subop;}
\+\+|\-\- {printf("%d\t%s\t\t\t\tOPERATOR\n",yylineno,yytext);return incop;}
\+=|\-=|\*=|\/=	{printf("%d\t%s\t\t\t\tOPERATOR\n",yylineno,yytext);return combop;}
\<< {printf("%d\t%s\t\t\t\tOPERATOR\n",yylineno,yytext);return coutop;}
\( {printf("%d\t%s\t\t\t\tBRACKET OPEN\n",yylineno,yytext); return b_open;}
\) {printf("%d\t%s\t\t\t\tBRACKET CLOSE\n",yylineno,yytext); return b_close;}


{letter}({letter}|{digit}|_)* {printf("%d\t%s\t\t\t\tIDENTIFIER\t\t%d\n",yylineno,yytext,yyscope); if(line==yylineno || ispresent(yytext)){installID(1,yytext,yylineno,yyscope,dtype);}; strcpy(yylval.var,yytext);return ID;}

{digit}+ {printf("%d\t%s\t\t\t\tINTEGER\n",yylineno,yytext); addValue(yytext, yylineno); strcpy(yylval.var,yytext); return num;}
{digit}+"E"(\+|\-)?{digit}+ printf("%d\t%s\t\t\t\tREAL NUMBER\n",yylineno,yytext);
{digit}+\.{digit}+(E(\+|\-)?{digit}+)? printf("%d\t%s\t\t\t\tFLOATING NUMBER\n",yylineno,yytext);
= {printf("%d\t%s\t\t\t\tASSIGNMENT\n",yylineno,yytext); return eq;}
; {printf("%d\t%s\t\t\t\tTERMINATOR\n",yylineno,yytext); terminators[terminator_index]=yylineno; terminator_index+=1; return semi;}
\t ;
[ ] ;
.  {return yytext[0];} 




%%

int installID (int type, char* tmp_yytext, int yylineno, int yyscope, char* dtype){
	switch (type) {
		case 1:
			strcpy (table[sym_table_length].name, "IDENTIFIER");		
			strcpy (table[sym_table_length].value, tmp_yytext);
			strcpy (table[sym_table_length].datatype, dtype);
			table[sym_table_length].line_number = yylineno;	
			table[sym_table_length].scope = yyscope;
			table[sym_table_length].id_value = rand();								 
			break;	}
				sym_table_length++;
}

void remove_duplicates()
{
for(int i=0; i<sym_table_length; i++)
    {
        for(int j=i+1; j<sym_table_length; j++)
        {
            if( (strcmp(table[i].value, table[j].value) == 0) ) 
            {
		strcpy(table[j].datatype,table[i].datatype);
		
		if(table[i].id_value<100000000 && table[j].id_value>100000000 && table[j].scope>table[i].scope)
			table[j].id_value=table[i].id_value;
                
            }
        }

	for(int j=i+1; j<sym_table_length; j++)
	{
	if( (strcmp(table[i].value, table[j].value) == 0) &&  (table[i].scope == table[j].scope) ){
		for(int k=i; k<sym_table_length; k++)
                {
                    table[k] = table[k + 1];
                }
		sym_table_length--;
                j--;
		}
	}
    }
}

int ispresent(char* yytext){
for(int i=0; i<sym_table_length; i++){
	if((strcmp(table[i].value, yytext) == 0))
		return 1;
	}
return 0;
}

void addValue(char* tmp_text, int yylineno){
for(int i=0; i<sym_table_length; i++)
	if(table[i].line_number==yylineno){
		table[i].id_value=atoi(tmp_text);
	}
}

void addvalue(int y, int yylineno){
for(int i=0; i<sym_table_length; i++)
	if(table[i].line_number==yylineno){
		table[i].id_value=y;
	}
}


void print_symtable(){
 remove_duplicates();
 for (int i = 0; i < sym_table_length; ++i) {
	printf("%d\t%s\t%s\t\t%d\t\t%d\t%s\t\t%d", (i+1), table[i].name, table[i].value, table[i].line_number, table[i].scope, table[i].datatype, table[i].id_value);
		printf("\n");
	}
}

int yywrap(){
    return 1;
}



/*
int main(int argc, char * argv[]){
    yyin=fopen(argv[1],"r");
    
    printf("\n----------------\nTOKEN GENERATOR\n----------------\n\n");
    printf("LINE\tLEXEME\t\t\t\tTOKEN\t\t\tSCOPE\n");
    yylex();
    fclose(yyin);
    printf("\n----------------\nSYMBOL TABLE\n----------------\n\n");
    printf("SNo.\tName\t\tValue\tLine number\tScope\tDatatype\tValue");
	printf("\n");
	print_symtable();
    return 0;
} */

