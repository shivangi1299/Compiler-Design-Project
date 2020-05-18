%{

#include<string.h>
#include<stdio.h>

struct quad{

char op[5];
char arg1[10];
//int arg1;
char arg2[10];
char result[10];
}QUAD[30];

struct stack{

int items[100];
int top;
}stk;

struct vars{

char var[5];
int val;
}VARS[30];

int Index=0,tIndex=0,StNo,Ind,tInd;
int vIndex=0;
extern int LineNo;
void cp();

%}

%union { char var[10]; }
%token <var> NUM VAR RELOP
%token MAIN IF ELSE WHILE TYPE FOR COUT S
%type <var> EXPR ASSIGNMENT CONDITION IFST ELSEST WHILELOOP FORLOOP 
%left '-' '+'
%left '*' '/'

%%

PROGRAM : MAIN BLOCK ;

BLOCK: '{' CODE '}';

CODE: BLOCK | STATEMENT CODE | STATEMENT ;

STATEMENT: DECST ';' | ASSIGNMENT ';' | CONDST | WHILEST | FORST | PRINTST ;

DECST: TYPE VARLIST ;

VARLIST: VAR ',' VARLIST | VAR ;

ASSIGNMENT: VAR '=' EXPR{

strcpy(QUAD[Index].op,"=");

strcpy(QUAD[Index].arg1,$3);

strcpy(QUAD[Index].arg2,"");

strcpy(QUAD[Index].result,$1);

strcpy($$,QUAD[Index++].result);

}

| EXPR{

strcpy(QUAD[Index].op,"=");

strcpy(QUAD[Index].arg1,QUAD[Index-1].result);

strcpy(QUAD[Index].arg2,"");

strcpy(QUAD[Index].result,QUAD[Index-1].arg1);

strcpy($$,QUAD[Index++].result);

}

;

EXPR: EXPR '+' EXPR {AddQuadruple("+",$1,$3,$$);}

| EXPR '-' EXPR {AddQuadruple("-",$1,$3,$$);}

| EXPR '*' EXPR {AddQuadruple("*",$1,$3,$$);}

| EXPR '/' EXPR {AddQuadruple("/",$1,$3,$$);}

| '-''-' EXPR {AddQuadruple("-",$3,"1",$$);}

| '+''+' EXPR {AddQuadruple("+",$3,"1",$$);}

| EXPR '-''-' {AddQuadruple("-",$1,"1",$$);}

| EXPR '+''+' {AddQuadruple("+",$1,"1",$$);}

| '(' EXPR ')' {strcpy($$,$2);}

| VAR

| NUM

;

CONDST: IFST{

Ind=pop();

sprintf(QUAD[Ind].result,"%d",Index);

Ind=pop();

sprintf(QUAD[Ind].result,"%d",Index);

}

| IFST ELSEST ;

IFST: IF '(' CONDITION ')' {

strcpy(QUAD[Index].op,"==");

strcpy(QUAD[Index].arg1,$3);

strcpy(QUAD[Index].arg2,"FALSE");

strcpy(QUAD[Index].result,"-1");

push(Index);

Index++;

}

BLOCK { 

strcpy(QUAD[Index].op,"GOTO"); 

strcpy(QUAD[Index].arg1,""); 

strcpy(QUAD[Index].arg2,"");

strcpy(QUAD[Index].result,"-1");

push(Index);

Index++;

};

ELSEST: ELSE{

tInd=pop();

Ind=pop();

push(tInd);

sprintf(QUAD[Ind].result,"%d",Index);

}

BLOCK{

Ind=pop();
 
sprintf(QUAD[Ind].result,"%d",Index);

};

CONDITION: VAR RELOP CONDITION {AddQuadruple($2,$1,$3,$$);

StNo=Index-1;

}

| VAR

| NUM

;

WHILEST: WHILELOOP{

Ind=pop();

sprintf(QUAD[Ind].result,"%d",StNo);

Ind=pop();

sprintf(QUAD[Ind].result,"%d",Index);

};

WHILELOOP: WHILE'('CONDITION ')' {

strcpy(QUAD[Index].op,"==");

strcpy(QUAD[Index].arg1,$3);

strcpy(QUAD[Index].arg2,"FALSE");

strcpy(QUAD[Index].result,"-1");

push(Index);

Index++;

}

BLOCK {

strcpy(QUAD[Index].op,"GOTO");

strcpy(QUAD[Index].arg1,"");

strcpy(QUAD[Index].arg2,"");

strcpy(QUAD[Index].result,"-1");

push(Index);

Index++;

};


FORST: FORLOOP{

Ind=pop();

sprintf(QUAD[Ind].result,"%d",StNo);

Ind=pop();

sprintf(QUAD[Ind].result,"%d",Index);

};

FORLOOP: FOR'('ASSIGNMENT';'CONDITION';'ASSIGNMENT')' {

strcpy(QUAD[Index].op,"==");

strcpy(QUAD[Index].arg1,QUAD[Index-3].result);

strcpy(QUAD[Index].arg2,"FALSE");

strcpy(QUAD[Index].result,"-1");

push(Index);

Index++;

}

BLOCK {

strcpy(QUAD[Index].op,"GOTO");

strcpy(QUAD[Index].arg1,"");

strcpy(QUAD[Index].arg2,"");

strcpy(QUAD[Index].result,"-1");

push(Index);

Index++;

};

PRINTST: COUT OUTPUT ';' ;

OUTPUT: S | EXPR ;

%%

extern FILE *yyin;
int main(int argc,char *argv[])

{

FILE *fp;
int i;

if(argc>1){

	fp=fopen(argv[1],"r");

	if(!fp){
		printf("\n File not found");
		exit(0);

	}

	yyin=fp;
}

yyparse();


printf("\n\n\t\t ----------------------------""\n\t\t Pos Operator \tArg1 \tArg2 \tResult" "\n\t\t--------------------");
for(i=0;i<Index;i++){
//	printf("%d", i);
	printf("\n\t\t %d\t %s\t %s\t %s\t%s",i,QUAD[i].op,QUAD[i].arg1,QUAD[i].arg2,QUAD[i].result);

}

printf("\n\t\t -----------------------");

//printf("hello");
cp();
//printf("\nbye");
//}

printf("\n\n"); return 0; }

void push(int data){ 
	stk.top++;

	if(stk.top==100){
		printf("\n Stack overflow\n");
		exit(0);
	}

	stk.items[stk.top]=data;
}

void push_var(char var[5],int val){
		strcpy(VARS[vIndex].var,var);
		VARS[vIndex++].val=val;
}

int pop(){
	int data;

	if(stk.top==-1){
		printf("\n Stack underflow\n");
		exit(0);

	}

	data=stk.items[stk.top--];
	return data;
}

void cp(){
	printf("\n\n\t\tOptimized Code");
	int flag=0;
	for(int i=0; i<Index; i++){
		//printf("%d",Index);
		//printf("%s", QUAD[i].op);
		if((strcmp(QUAD[i].op,"=")!=0) && (strcmp(QUAD[i].op,"==")!=0) && (strcmp(QUAD[i].op,"GOTO")!=0)){
			//printf("\tentered if");
			int temp;
			while(strcmp(QUAD[i].op,"=")!=0){
				//int temp;
				int flag=0; int done1=0; int done2=0; int oper; 
				int o1, o2;
				if(strcmp(QUAD[i].op, "/")==0)
					oper = 1;
				if(strcmp(QUAD[i].op, "-")==0)
					oper = 2;
				if(strcmp(QUAD[i].op, "*")==0)
					oper = 3;
				if(strcmp(QUAD[i].op, "+")==0)
					oper = 4;
				//printf("%d",oper);
				switch(oper){

					case 1 : 
							for(int j=vIndex-1; j>-1; j--){
								if(strcmp(VARS[j].var,QUAD[i].arg1)==0 && done1==0){
									o1 = VARS[j].val;
									flag+=1;
									done1=1;
								}
								if(strcmp(VARS[j].var,QUAD[i].arg2)==0 && done2==0){
									o2 = VARS[j].val;
									flag+=2;
									done2=1;	
								}
								if(flag==3)
									break;
							}
							if(flag==3){
								push_var(QUAD[i].result,o1/o2);	
								printf("\n\t\t %d\t %s\t %d\t %d\t%d",i,QUAD[i].op,o1,o2,o1/o2);									
							}
							else if(flag==1){
								o2 = atoi(QUAD[i].arg2);
								push_var(QUAD[i].result,o1/o2);
								printf("\n\t\t %d\t %s\t %d\t %d\t%d",i,QUAD[i].op,o1,o2,o1/o2);
							}
							else{
								o1 = atoi(QUAD[i].arg1);
								push_var(QUAD[i].result,o1/o2);
								printf("\n\t\t %d\t %s\t %d\t %d\t%d",i,QUAD[i].op,o1,o2,o1/o2);									
							}
							temp=o1/o2;
							break;
							
					case 2: 	for(int j=vIndex-1; j>-1; j--){
								if(strcmp(VARS[j].var,QUAD[i].arg1)==0 && done1==0){
									o1 = VARS[j].val;
									flag+=1;
									done1=1;
								}
								if(strcmp(VARS[j].var,QUAD[i].arg2)==0 && done2==0){
									o2 = VARS[j].val;
									flag+=2;
									done2=1;	
								}
								if(flag==3)
									break;
							}
							if(flag==3){
								push_var(QUAD[i].result,o1-o2);	
								printf("\n\t\t %d\t %s\t %d\t %d\t%d",i,QUAD[i].op,o1,o2,o1-o2);									
							}
							else if(flag==1){
								o2 = atoi(QUAD[i].arg2);
								push_var(QUAD[i].result,o1-o2);
								printf("\n\t\t %d\t %s\t %d\t %d\t%d",i,QUAD[i].op,o1,o2,o1-o2);
							}
							else{
								o1 = atoi(QUAD[i].arg1);
								push_var(QUAD[i].result,o1-o2);
								printf("\n\t\t %d\t %s\t %d\t %d\t%d",i,QUAD[i].op,o1,o2,o1-o2);									
							}
							temp=o1-o2;
							break;
					
					case 3: 	for(int j=vIndex-1; j>-1; j--){
								if(strcmp(VARS[j].var,QUAD[i].arg1)==0 && done1==0){
									o1 = VARS[j].val;
									flag+=1;
									done1=1;
								}
								if(strcmp(VARS[j].var,QUAD[i].arg2)==0 && done2==0){
									o2 = VARS[j].val;
									flag+=2;
									done2=1;	
								}
								if(flag==3)
									break;
							}
							if(flag==3){
								push_var(QUAD[i].result,o1*o2);	
								printf("\n\t\t %d\t %s\t %d\t %d\t%d",i,QUAD[i].op,o1,o2,o1*o2);									
							}
							else if(flag==1){
								o2 = atoi(QUAD[i].arg2);
								push_var(QUAD[i].result,o1*o2);
								printf("\n\t\t %d\t %s\t %d\t %d\t%d",i,QUAD[i].op,o1,o2,o1*o2);
							}
							else{
								o1 = atoi(QUAD[i].arg1);
								push_var(QUAD[i].result,o1*o2);
								printf("\n\t\t %d\t %s\t %d\t %d\t%d",i,QUAD[i].op,o1,o2,o1*o2);									
							}
							temp=o1*o2;
							break;
						   
					case 4: 	for(int j=vIndex-1; j>-1; j--){
								if(strcmp(VARS[j].var,QUAD[i].arg1)==0 && done1==0){
									o1 = VARS[j].val;
									flag+=1;
									done1=1;
								}
								if(strcmp(VARS[j].var,QUAD[i].arg2)==0 && done2==0){
									o2 = VARS[j].val;
									flag+=2;
									done2=1;	
								}
								if(flag==3)
									break;
							}
							if(flag==3){
								push_var(QUAD[i].result,o1+o2);	
								printf("\n\t\t %d\t %s\t %d\t %d\t%d",i,QUAD[i].op,o1,o2,o1+o2);									
							}
							else if(flag==1){
								o2 = atoi(QUAD[i].arg2);
								push_var(QUAD[i].result,o1+o2);
								printf("\n\t\t %d\t %s\t %d\t %d\t%d",i,QUAD[i].op,o1,o2,o1+o2);
							}
							else{
								o1 = atoi(QUAD[i].arg1);
								push_var(QUAD[i].result,o1+o2);
								printf("\n\t\t %d\t %s\t %d\t %d\t%d",i,QUAD[i].op,o1,o2,o1+o2);									
							}
							temp=o1+o2;
							break;
					//default: printf("default");		
				}
			i++;
			}
			//for(
			//if(strcmp(QUAD[i].arg1[0],"t")==0){
				push_var(QUAD[i].result,temp);
				printf("\n\t\t %d\t %s\t %d\t %s\t%s",i,QUAD[i].op,temp,QUAD[i].arg2,QUAD[i].result);
			//}
			
		}
		else if((strcmp(QUAD[i].op,"=")==0) && strlen(QUAD[i].result)==1){
			push_var(QUAD[i].result,atoi(QUAD[i].arg1));
			printf("\n\t\t %d\t %s\t %s\t %s\t%s",i,QUAD[i].op,QUAD[i].arg1,QUAD[i].arg2,QUAD[i].result);
		}	
	}
	printf("\n\n\t\tSymbol table variable values\n");
	for(int l=0; l<vIndex; l++){
		printf("\n\t\t%s\t%d", VARS[l].var, VARS[l].val);
	}
}

void AddQuadruple(char op[5],char arg1[10],char arg2[10],char result[10]){
	strcpy(QUAD[Index].op,op);
	strcpy(QUAD[Index].arg1,arg1);
	//sprintf(QUAD[Index].arg1,arg1);
	strcpy(QUAD[Index].arg2,arg2);
	sprintf(QUAD[Index].result,"t%d",tIndex++);
	strcpy(result,QUAD[Index++].result);
}

yyerror(){
	printf("\n Error in line no:%d",LineNo);
}





