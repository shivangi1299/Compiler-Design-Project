%{

#include"y.tab.h"

#include<stdio.h>

#include<string.h>

int LineNo=1;

%}

identifier [a-zA-Z][_a-zA-Z0-9]*

number [0-9]+|([0-9]*\.[0-9]+)

%%
(\/\/.*)[\n] {}
(\/\*.*\*\/)[\n] {}
(\/\*(.*\n)*.*\*\/)[\n] {}

"int main"\(\) return MAIN;
cout<< return COUT;
if return IF;
else return ELSE;
while return WHILE;
int |
char |
float return TYPE;
for return FOR;
{identifier} {strcpy(yylval.var,yytext); return VAR;}
{number} {strcpy(yylval.var,yytext); return NUM;}
\< | 
\> |
\>= |
\<= |
== {strcpy(yylval.var,yytext); return RELOP;}
\"(.)*\" {return S;}
[ \t] ;
\n LineNo++;
. return yytext[0];

%% 

int yywrap (void)  
{return 1;
}
