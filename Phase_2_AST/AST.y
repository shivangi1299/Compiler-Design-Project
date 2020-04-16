%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <limits.h>

	void yyerror(const char*);
	int yylex();
	extern FILE * yyin, *yyout;

	int x=0;	

	extern int yylineno;
	
	int scope = 0;

	int unaryop = -1;		//unary operator type
	int assignop = -1;		//assignment operator == += -=
	int datatype = -1;		//type specifier
	int assigntype = -1;	//RHS type 
	int idcheck = -1;		//check if ID 

	char tempStr[100];		//sprintf

	struct node{
		char token[20];
		char name[20];
		int dtype;
		int scope;
		int lineno;
		int valid;
		union value{
			float f;
			int i;
			char c;
		}val;
		
		struct node *link;

	}*first = NULL, *tmp, *crt, *lhs;

	typedef struct Node{
		struct Node *left;
		struct Node *right;
		char token[100];
		struct Node *val;
		int level;
	}Node;

	typedef struct tree_stack{
		Node *node;
		struct tree_stack *next;
	}tree_stack;

	tree_stack *tree_top = NULL;
	char preBuf[1000000];

	struct node * checksym(char *);
	void addsymbol(struct node *,char *);	
	void addInt(struct node *, int, int);
	void addFloat(struct node *, int, float);
	void addChar(struct node *, int, char);

	//AST 
	void create_node(char *token, int leaf);
	Node *pop_tree();
	void preorder(Node* root);
	void printtree(Node* root);
	int getmaxlevel(Node *root);
	void printGivenLevel(Node* root, int level, int h);

%}

%token  INCLUDE
%token  STRING_LITERAL COUT RETURN 
%left 	'+' '-'
%left 	'/' '*' 
%right 	'='
%expect 1

%union{
	int ival;
	float fval;
	char cval;
	char string[128];
	struct node *ptr;
}

%token <ival> 	INTEGER_LITERAL 
%token <cval> 	CHARACTER_LITERAL
%token <fval> 	FLOAT_LITERAL 
%token <ptr> 	IDENTIFIER  

%token	INC_OP DEC_OP LE_OP GE_OP EQ_OP NE_OP OUT_OP
%token	MUL_ASSIGN 	DIV_ASSIGN 	ADD_ASSIGN 	SUB_ASSIGN
%token	<ival> 	CHAR INT FLOAT	VOID
%token 	FOR WHILE
%token  IF ELSE

%type <fval>	assignment_expression 	assignment_operator 
%type <fval>	primary_expression 
%type <fval>	equality_expression 
%type <fval>	relational_expression 
%type <fval>	additive_expression 
%type <fval>	multiplicative_expression 
%type <fval>	unary_expression 	unary_operator
%type <fval>	conditional_expression
%type <fval>	expression 	
%type <fval>	postfix_expression 	

%type <string> 	declarator

%start S

%%
S : program 
  
program	: INCLUDE program | translation_unit	;

translation_unit : ext_dec | translation_unit ext_dec ;

ext_dec	: declaration | function_definition;

compound_statement : '{' '}' | '{' block_item_list '}' ;

block_item_list	: block_item | block_item_list block_item {	create_node("stmt", 0);	};

block_item : declaration | statement | RETURN expression_statement	{ create_node("return", 1);	} | printstat ';' ;

printstat : COUT OUT_OP STRING_LITERAL | COUT OUT_OP STRING_LITERAL OUT_OP expression;

declaration : type_specifier init_declarator_list ';' ;

statement
	: compound_statement {
						struct node *ftp;
						ftp = first;
						while(ftp!=NULL){
							if(ftp->scope == scope && ftp->valid == 1){
								ftp->valid = 0;}
							ftp=ftp->link; }
						scope--;}
	| expression_statement | iteration_statement | condition_statement ;

iteration_statement : FOR '(' expression_statement  expression_statement expression  ')' statement 	{ 	create_node("for", 0); }			
	| WHILE '('expression ')' statement { create_node("while", 0); } ;

condition_statement : IF '(' expression ')' statement {create_node("if",0);} | condition_statement ELSE statement {create_node("else",0);} ;

type_specifier : VOID 	{datatype = $1; } | CHAR { datatype = $1; }	| INT {	datatype = $1; } | FLOAT {datatype = $1; };

function_definition: type_specifier declarator compound_statement 	
				{
					create_node($2, 3);
					struct node *ftp;
					ftp = first;
					while(ftp!=NULL){
						if(ftp->scope == scope && ftp->valid == 1){
							ftp->valid = 0;		}
						else if(strcmp(ftp->token, "param") == 0 && ftp->valid == 1){
							ftp->valid = 0;		}
						ftp=ftp->link;		}
					scope--;					}

declarator: IDENTIFIER   {		if($1->dtype == -1) {
       								$1->dtype = datatype;
        							$1->val.i = 0;
        							strcpy($1->token, "function");	}
								strcpy($$, $1->name); 									}  			
	| declarator '(' ')'					{ } ;

init_declarator_list : init_declarator | init_declarator_list ',' init_declarator;

init_declarator
	: IDENTIFIER { create_node($1->name, 1); } '=' assignment_expression {	
						if($1->dtype !=- 1 && $1->scope < scope && $1->valid == 1){
							struct node *ftp, *nnode;
							nnode = (struct node *)malloc(sizeof(struct node));
							ftp = first;
							while(ftp->link!=NULL){
								ftp = ftp->link;}
							addsymbol(nnode,$1->name);	
							ftp->link = nnode;
							nnode->link = NULL;
							$1 = nnode;

							float tempf; 

							switch(datatype){
								case 0: addInt($1, 0, $4); break;
								case 1: addFloat($1, 1, $4); break;
								case 2: tempf = (float)$4;
										addChar($1, 2, (int)tempf); break; }
							create_node("=", 0); }
						
						else{
							float tempf;

							create_node("=", 0);
							switch(datatype){
								case 0: addInt($1, 0, $4); break;
								case 1: addFloat($1, 1, $4); break;
								case 2: tempf = (float)$4;
										addChar($1, 2, (int)tempf); break; }
						}		}	
	| IDENTIFIER	{	if($1->dtype !=- 1 && $1->scope < scope && $1->valid == 1){
																							
							struct node *ftp, *nnode;
							nnode = (struct node *)malloc(sizeof(struct node));
							ftp = first;
							while(ftp->link!=NULL){
								ftp = ftp->link; }
							addsymbol(nnode,$1->name);	
							ftp->link = nnode;
							nnode->link = NULL;							
							$1 = nnode;
							
							switch(datatype){
								case 0: addInt($1, 0, INT_MIN); break;
								case 1: addFloat($1, 1, INT_MIN); break;
								case 2: addChar($1, 2, '-'); }

							char buff[20];
							strcpy(buff, "Dc ");
							strcat(buff, $1->name);
							create_node(buff, 1); 	}
						
						else{
							switch(datatype){
								case 0: addInt($1, 0, INT_MIN); break;
								case 1: addFloat($1, 1, INT_MIN); break;
								case 2: addChar($1, 2, '-'); }
							char buff[20];
							strcpy(buff, "Dc ");
							strcat(buff, $1->name);
							create_node(buff, 1); }				};

assignment_expression
	: conditional_expression	{	$$ = $1; }
	| unary_expression	{ crt = lhs; } assignment_operator assignment_expression 
			{	switch(assignop){
					case 0: if(idcheck == 1){
								create_node("=", 0);
								switch(crt->dtype){
									case 0: crt->val.i = (int)$4; break;
									case 1: crt->val.f = $4; break;
									case 2: crt->val.c = (char)((int)$4); }
								}
							crt = NULL; break;

					case 1: if(idcheck == 1){
								create_node("+=", 0);
								switch(crt->dtype){
									case 0: crt->val.i = (int)$1 + (int)$4; break;
									case 1: crt->val.f = $1 + $4; break;
									case 2: crt->val.c = (char)((int)$1 + (int)$4); }
								}
							crt = NULL; break;

					case 2:	if(idcheck == 1){
								create_node("-=", 0);
								switch(crt->dtype){
									case 0: crt->val.i = (int)$1 - (int)$4; break;
									case 1: crt->val.f = $1 - $4; break;
									case 2: crt->val.c = (char)((int)$1 - (int)$4); }
								}
							crt = NULL; break;

					case 3:	if(idcheck == 1){
								create_node("*=", 0);
								switch(crt->dtype){
									case 0: crt->val.i = (int)$1 * (int)$4; break;
									case 1: crt->val.f = $1 * $4; break;
									case 2: crt->val.c = (char)((int)$1 * (int)$4); }
								}
							crt = NULL; break;

					case 4:	if(idcheck == 1){
								create_node("/=", 0);
								switch(crt->dtype){
									case 0: crt->val.i = (int)$1 / (int)$4; break;
									case 1: crt->val.f = $1 / $4; break;
									case 2: crt->val.c = (char)((int)$1 / (int)$4); }
								}
							crt = NULL; break;		}
				assignop = -1;
				assigntype = -1;		} ;

assignment_operator : '=' {	assignop = 0; } | ADD_ASSIGN {	assignop = 1; } | SUB_ASSIGN {	assignop = 2; }
	| MUL_ASSIGN { assignop = 3; } | DIV_ASSIGN	{	assignop = 4; } ;

conditional_expression : equality_expression {$$ = $1;} ;

expression_statement : ';'	| expression ';' ;

expression : assignment_expression	| expression ',' assignment_expression ;

primary_expression //fval
	: IDENTIFIER {					
					idcheck = 1;
					lhs = $1;
					switch($1->dtype){
						case 0: $$ = $1->val.i;
								assigntype = 0; break;
						case 1: $$ = $1->val.f;
								assigntype = 1; break;
						case 2: $$ = $1->val.c;
								assigntype = 2;		}
					
					create_node($1->name, 1);			}
	| INTEGER_LITERAL	{
					$$ = $1;
					assigntype = 0;
					sprintf(tempStr, "%d", (int)$1);
					create_node(tempStr, 1);	}
	| FLOAT_LITERAL		{	
					assigntype = 1;
					switch(datatype){
						case 1: $$ = $1; break;
						case 0: 
						case 2: $$ = (int)$1; }

					sprintf(tempStr, "%f", $1);
					create_node(tempStr, 1);  }
	| CHARACTER_LITERAL	 {	
					assigntype = 2;
					int temp;
					switch(datatype){
						case 2: temp = (int)$1;
								$$ =  (float)temp; break;
						case 0:
						case 1: $$ = (int)$1; }
					sprintf(tempStr, "%c", $1);
					create_node(tempStr, 1);		}
	| '(' expression ')' { $$ = $2;}	;

postfix_expression	: primary_expression	{	$$ = $1;	}
	| postfix_expression INC_OP	{	$1++; $$ = $1;	create_node("++", 0); }	
	| postfix_expression DEC_OP {	$1--; $$ = $1;	create_node("--", 0); } ;

unary_expression : postfix_expression	{	$$ = $1;	}
	| unary_operator unary_expression {
					switch(unaryop){	
						case 1:	$$ = ++$2;
								create_node("++", 0);	break;
						case 2:	$$ = --$2;
								create_node("--", 0);	break;		}
					unaryop = -1; } ;

unary_operator: "INC_OP" { unaryop = 1; } | "DEC_OP" {unaryop = 2;} ;

equality_expression : relational_expression {	$$ = $1;	}
	| equality_expression EQ_OP relational_expression
				{ 	create_node("==", 0);
					if($1 == $3)
						$$ = 1;
					else	$$ = 0;	}
	| equality_expression NE_OP relational_expression
				{   create_node("!=", 0);
					if($1 != $3)
						$$ = 1;
					else	$$ = 0; } ;

relational_expression
	: additive_expression	{	$$ = $1;	}
	| relational_expression '<' additive_expression
				{	create_node("<", 0);
					if($1 < $3)
						$$ = 1;
					else	$$ = 0;	}
	| relational_expression '>' additive_expression
				{ 	create_node(">", 0);
					if($1 > $3)
						$$ = 1;
					else	$$ = 0;	}
	| relational_expression LE_OP additive_expression
				{ 	create_node("<=", 0);
					if($1 <= $3)
						$$ = 1;
					else	$$ = 0;	}
	| relational_expression GE_OP additive_expression
				{ 	create_node(">=", 0);
					if($1 >= $3)
						$$ = 1;
					else	$$ = 0;	} ;

additive_expression	: multiplicative_expression	{	$$ = $1;	}
	| additive_expression '+' multiplicative_expression 	{	create_node("+", 0);	$$ = $1 + $3;	}
	| additive_expression '-' multiplicative_expression		{	create_node("-", 0);	$$ = $1 - $3;	}	;

multiplicative_expression : unary_expression			{	$$ = $1;	}
	| multiplicative_expression '*' unary_expression 	{	create_node("*", 0);	$$ = $1 * $3;	}
	| multiplicative_expression '/' unary_expression	{	$$ = $1 / $3;	create_node("/", 0); }	;

%%

void yyerror(const char *str){
	fflush(stdout);
	printf("Line:%d: %s", yylineno,str); }

int main(){
	yyout = fopen("output.c", "w");

	tree_top = (tree_stack*)malloc(sizeof(tree_stack));
	tree_top->node = NULL;
	tree_top->next = NULL;
	struct Node *root;

	printf("\n");
	yyparse();

	root = pop_tree();
	printtree(root);
	preorder(root);
	
	printf("\n\nPreorder Traversal\n\n");
	printf("%s\n", preBuf);

	fclose(yyout);
	return 0;			}

void addInt(struct node *t,int type,int val) {
    if(t->dtype == -1) {
        t->dtype = type;
        t->val.i = val;
        strcpy(t->token, "identifier");	 }	}

void addFloat(struct node *t,int type,float val) {
    if(t->dtype == -1) {
        t->dtype = type;
        t->val.f = (float)val;
        strcpy(t->token, "identifier"); }	}

void addChar(struct node *t,int type, char val) {
   	if(t->dtype == -1) {
   	    t->dtype = type;
   	    t->val.c = (char)val;
   	    strcpy(t->token, "identifier");	}	}

struct node * checksym(char *vname) {
	struct node *ftp;
	struct node *rp;
	struct node *nnode;
	struct node *same;

	if(first == NULL) {
		nnode = (struct node *)malloc(sizeof(struct node));
		addsymbol(nnode,vname);
	    first = nnode;	}
	else {
	    ftp = first;
	    while(ftp!=NULL) {
	        if(strcmp(vname,ftp->name) == 0){
	            if(ftp->scope > scope && ftp->valid == 1) {	          	
					same = ftp; 
	            	return same;  }	
	            else if(ftp->scope == scope && ftp->valid == 1){
	            	same = ftp;
	            	return same;  }          	
	            else if(ftp->scope < scope && ftp->valid == 1){	
	         		same = ftp;
	            	return same;     }    }            
	        rp = ftp;
	        ftp = ftp->link;	 }
	    nnode = (struct node *)malloc(sizeof(struct node));
		addsymbol(nnode,vname);

	    rp->link = nnode;	}
	return nnode;		}


void addsymbol(struct node *tp, char *vname) {
    strcpy(tp->name,vname);
    tp->dtype = -1;
    tp->link = NULL;
    tp->scope = scope;
    tp->valid = 1;
    tp->lineno = yylineno;		}

void create_node(char *token, int leaf) {
	Node *l;
	Node *r;
	if(leaf==0) {
		r = pop_tree();
		l = pop_tree();	}
	else if(leaf ==1) {
		l = NULL;
		r = NULL;	}
	else {
		l = pop_tree();
		r = NULL;	}

	Node *newnode = (Node*)malloc(sizeof(Node));
	strcpy(newnode->token, token);
	newnode->left = l;
	newnode->right = r;

	tree_stack *temp= (tree_stack*)malloc(sizeof(tree_stack));
	temp->node = newnode;
	temp->next = tree_top;
	tree_top = temp;			}

Node* pop_tree(){
	tree_stack *temp = tree_top;
	tree_top = tree_top->next;
	Node *retnode = temp->node;
	if(temp != NULL)
		free(temp);
	return retnode;		}

void printtree(Node* root){
    int h = getmaxlevel(root)-1;
    int i;
	printf("\n\nAbstract Syntax Tree\n\n");

    for (i=1; i<=h; i++){
		printf("\t");
		for(int j=0;j<=h+1-i;j++){
			printf("      ");	}
        printGivenLevel(root, i,h);
        printf("\n\n\n");	  }
}

int getmaxlevel(Node *root){
	int count=0;
	Node *temp= root;
	int flag;
	while(temp->left!=NULL || temp->right!=NULL){
		Node *temp1 = temp->left;
		flag = 0;
		if(temp1->left == NULL && temp1->right == NULL)
			flag = 1;
		count++;
		if(temp->left!=NULL && flag==0)
			temp=temp->left;
		else	temp=temp->right;		}
	return count*2;		}

void printGivenLevel(Node* root, int level, int h){
    if (root == NULL)  return;
    if (level == 1){
		for(int j=0; j<=h-1-level; j++){
			printf(" ");	}
	    printf("%s ", root->token);		}
    else if (level > 1){
        printGivenLevel(root->left, level-1,h);
		for(int j=0; j<=h-1-level; j++){
			printf(" ");	}
        printGivenLevel(root->right, level-1,h);    }
}

void preorder(Node * node){
	if (node == NULL)	return;	
	if(node->left!=NULL && node->right!=NULL)
		strcat(preBuf, "   ( ");
	strcat(preBuf, node->token);
	strcat(preBuf, "   ");
	preorder(node-> left);
	if(node->right){
		preorder(node-> right);	}
	if(node->left!=NULL && node->right!=NULL)
		strcat(preBuf, ")   ");
}

