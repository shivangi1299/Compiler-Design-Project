%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>

	#include "y.tab.h"

	int yylineno = 1;
	extern int scope;

	extern void yyerror(const char *);  
	extern struct node * checksym(char *);

%}

digit   		[0-9]
letter   		[a-zA-Z]

%%

[\n]		{ fprintf(yyout, "%s", yytext); yylineno++;	}
(\/\/.*)[\n] {}
(\/\*.*\*\/)[\n] {}
(\/\*(.*\n)*.*\*\/)[\n] {}

"#include"[ ]\<{letter}+(\.{letter}*)?\>		{ fprintf(yyout, "%s", yytext);  return INCLUDE; }

int			{ fprintf(yyout, "%s", yytext);  yylval.ival=0; return INT; 	}
float		{ fprintf(yyout, "%s", yytext);  yylval.ival=1; return FLOAT; }
char		{ fprintf(yyout, "%s", yytext);  yylval.ival=2; return CHAR; }
void		{ fprintf(yyout, "%s", yytext);  yylval.ival=3; return VOID; }

for			{ fprintf(yyout, "%s", yytext);  return FOR; }
if          { fprintf(yyout, "%s", yytext); return IF;} 
else		{ fprintf(yyout, "%s", yytext); return ELSE;}
while       { fprintf(yyout, "%s", yytext); return WHILE;}      
cout 		{ fprintf(yyout, "%s", yytext);	 return COUT; }
return 		{ fprintf(yyout, "%s", yytext);	 return RETURN; }


{letter}({letter}|{digit}|_)*	{	fprintf(yyout, "%s", yytext);  
									yylval.ptr = checksym(yytext); 
									return IDENTIFIER;	}
{digit}+\.{digit}+              {	fprintf(yyout, "%s", yytext);   
									yylval.fval=atof(yytext);
									return FLOAT_LITERAL;	}  		
{digit}+						{	fprintf(yyout, "%s", yytext);  
									yylval.ival=atoi(yytext);
									return INTEGER_LITERAL;		}	
"'"."'"							{	fprintf(yyout, "%s", yytext);
									yylval.cval= yytext[1];
									return CHARACTER_LITERAL;  }

\".*\"							{fprintf(yyout, "%s", yytext);  return STRING_LITERAL; }

"+="		{fprintf(yyout, "%s", yytext);  return(ADD_ASSIGN); }
"-="		{fprintf(yyout, "%s", yytext);  return(SUB_ASSIGN); }
"*="		{fprintf(yyout, "%s", yytext);  return(MUL_ASSIGN); }
"/="		{fprintf(yyout, "%s", yytext);  return(DIV_ASSIGN); }
"++"		{fprintf(yyout, "%s", yytext);  return(INC_OP); }
"--"		{fprintf(yyout, "%s", yytext);  return(DEC_OP); }
"<="		{fprintf(yyout, "%s", yytext);  return(LE_OP); }
">="		{fprintf(yyout, "%s", yytext);  return(GE_OP); }
"=="		{fprintf(yyout, "%s", yytext);  return(EQ_OP); }
"!="		{fprintf(yyout, "%s", yytext);  return(NE_OP); }
";"			{fprintf(yyout, "%s", yytext);  return(';'); }
"{"			{fprintf(yyout, "%s", yytext);  scope++; return('{'); }
"}"			{fprintf(yyout, "%s", yytext);  return('}'); }
","			{fprintf(yyout, "%s", yytext);  return(','); }
":"			{fprintf(yyout, "%s", yytext);  return(':'); }
"="			{fprintf(yyout, "%s", yytext);  return('='); }
"("			{fprintf(yyout, "%s", yytext);  return('('); }
")"			{fprintf(yyout, "%s", yytext);  return(')'); }

[ ] ;

"."			{fprintf(yyout, "%s", yytext);  return('.'); }
"&"			{fprintf(yyout, "%s", yytext);  return('&'); }

"-"			{fprintf(yyout, "%s", yytext);  return('-'); }
"+"			{fprintf(yyout, "%s", yytext);  return('+'); }
"*"			{fprintf(yyout, "%s", yytext);  return('*'); }
"/"			{fprintf(yyout, "%s", yytext);  return('/'); }

"<"			{fprintf(yyout, "%s", yytext);  return('<'); }
">"			{fprintf(yyout, "%s", yytext);  return('>'); }
"<<"		{fprintf(yyout, "%s", yytext);  return(OUT_OP);}

\t		{fprintf(yyout, "%s", yytext); /* whitespace separates tokens */}

.			{ printf("No Match, Invalid Expression %s\n", yytext); return yytext[0];}

%%

int yywrap(void)
{
	return 1;
}

