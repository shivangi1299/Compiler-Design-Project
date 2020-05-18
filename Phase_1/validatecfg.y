%{

    #include<stdio.h>

    int valid=1;

extern void yyerror(char* s);  /* prints grammar violation message */
extern int yylex(void);
extern FILE *yyin;
extern FILE *yyout;
extern int yylineno;
extern char* yytext;
extern void remove_duplicates();
extern struct sym_table {
	char name[20];
	char value[50];
	int line_number;
	int scope;
	char datatype[20];
	int id_value;
}table[100];
//extern struct table[100];
extern int sym_table_length;
extern void print_symtable();
extern void addvalue(int y, int yylineno);
int flag=0;

%}
%union { char var[10]; }
%token ID num s begin b_open b_close br_open br_close dt semi eq com tif telse relop addop mulop divop subop incop tfor twhile tcout coutop combop
%type <var> assignexp OP exp num
/*
%nonassoc "null"
%nonassoc "rule"


%right eq
%left tif
%left twhile
%left tfor
%left br_close
%right br_open
%left b_close
%right ID
%right num
%right incop
%left semi
%left tcout
%left dt
%right error
%expect 1

%nonassoc "null"
%nonassoc "rule"


%prec tif
%prec twhile
%prec tfor
%prec br_close
%prec br_open

%prec ID
%prec num
%prec incop
%prec semi
%prec tcout
%prec dt
%right error
*/
%nonassoc "null"
%nonassoc "rule"

%left tif
%left twhile
%left tfor
%left br_close
%right br_open

%right ID
%right num
%right incop
%left semi
%left tcout
%left dt
%right error
%expect 1


%%

start : begin bopen bclose bropen stmt brclose;

bopen : error {yyerror(": Missing paranthesis (\n");} | b_open;

bclose : error {yyerror(": Missing paranthesis )\n");} | b_close;

bropen : error {yyerror(": Missing braces {\n");} | br_open;

stmt : stmt statement %prec "rule" | stmt vardec %prec "rule" | %prec "null";

vardec : dt ID dec ;

dec: without_init | with_init;

without_init : eos | var without_init;

var : com ID;

with_init : eq num more;

more: eos | com ID with_init;

statement : statement ctrl_stmt %prec "rule" | statement cond %prec "rule" | statement print_stmt %prec "rule" | %prec "null" ;

ctrl_stmt : if | iter_stmt;

if  : matched  | unmatched;

matched : tif b_open cond b_close matched telse matched | n_statement;

n_statement: br_open statement br_close;

unmatched : tif b_open cond b_close br_open statement br_close | tif b_open cond b_close matched telse unmatched;

iter_stmt : for | while;

while : twhile bopen cond bclose bropen statement br_close;

for : tfor bopen prfx with_init cond loop_opn bclose bropen statement br_close;

prfx: dt ID | ID;

cond : exp | loop_opn cond | eos ;

exp : val operator cond | val %prec "null"| val eos %prec "rule" | ID eq assignexp  ;

assignexp: num OP num 
{switch(flag)
{case 1: /*printf("%d", atoi($1)+atoi($3));*/ addvalue(atoi($1)+atoi($3), yylineno); break; 
case 2: /*printf("%d", atoi($1)+atoi($3));*/ addvalue(atoi($1)*atoi($3), yylineno); break;
case 3: /*printf("%d", atoi($1)+atoi($3));*/ addvalue(atoi($1)/atoi($3), yylineno); break;
case 4: /*printf("%d", atoi($1)+atoi($3));*/ addvalue(atoi($1)-atoi($3), yylineno); break;
};
};

val: ID | num;

operator : relop | OP | eq ;

OP: addop {flag=1;} | mulop{flag=2;} | divop {flag=3;} | subop {flag=4;};

loop_opn : incop ID | ID incop | ID combop val;

print_stmt : tcout coutop S;

S : cond | s eos;

eos : error {yyerror(": Missing semi colon\n");} | semi;

brclose : error {yyerror(": Missing braces }\n");} | br_close;

 
%%

extern void yyerror(char* si)
{

    //printf("Syntax Error\n");
    printf("%s", si);
    valid=0;
}


int main(int argc, char * argv[])

{

    yyin=fopen(argv[1],"r");
    printf("\n----------------\nTOKEN GENERATOR\n----------------\n\n");
    printf("LINE\tLEXEME\t\t\t\tTOKEN\t\t\tSCOPE\n");
    yyparse();
    
    fclose(yyin);
    if(valid)

    {

        printf("Congrats! It's valid.\n");
	//printf("Valid: %d\n", valid);

    }
    printf("\n----------------\nSYMBOL TABLE\n----------------\n\n");
    printf("SNo.\tName\t\tIdentifier\tLine number\tScope\tDatatype\tValue");
    printf("\n");
    print_symtable();	

    return 0;

}

