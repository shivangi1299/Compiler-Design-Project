
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "newast.y"

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <limits.h>

	void yyerror(const char*);
	int yylex();
	extern FILE * yyin, *yyout;

	int x=0;	

	extern int line;
	
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



/* Line 189 of yacc.c  */
#line 147 "newast.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     HASH = 258,
     INCLUDE = 259,
     STDIO = 260,
     STDLIB = 261,
     MATH = 262,
     STRING = 263,
     TIME = 264,
     STRING_LITERAL = 265,
     HEADER_LITERAL = 266,
     PRINT = 267,
     RETURN = 268,
     INTEGER_LITERAL = 269,
     CHARACTER_LITERAL = 270,
     FLOAT_LITERAL = 271,
     IDENTIFIER = 272,
     INC_OP = 273,
     DEC_OP = 274,
     LE_OP = 275,
     GE_OP = 276,
     EQ_OP = 277,
     NE_OP = 278,
     MUL_ASSIGN = 279,
     DIV_ASSIGN = 280,
     ADD_ASSIGN = 281,
     SUB_ASSIGN = 282,
     CHAR = 283,
     INT = 284,
     FLOAT = 285,
     VOID = 286,
     FOR = 287,
     WHILE = 288,
     IF = 289,
     ELSE = 290
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 80 "newast.y"

	int ival;
	float fval;
	char cval;
	char string[128];
	struct node *ptr;



/* Line 214 of yacc.c  */
#line 228 "newast.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 240 "newast.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  14
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   183

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  84
/* YYNRULES -- Number of states.  */
#define YYNSTATES  140

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   294

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    18,     2,     2,
      49,    50,    17,    14,    51,    15,     2,    16,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    48,
      44,    19,    45,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    46,     2,    47,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    52,    53
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,    12,    17,    19,    21,    24,    26,
      28,    30,    32,    34,    36,    38,    41,    45,    47,    50,
      52,    54,    57,    60,    65,    72,    76,    78,    80,    82,
      84,    92,    98,   104,   108,   110,   112,   114,   116,   120,
     122,   126,   128,   132,   133,   138,   140,   142,   143,   148,
     150,   152,   154,   156,   158,   160,   162,   165,   167,   171,
     173,   175,   177,   179,   183,   185,   188,   191,   193,   196,
     198,   200,   202,   206,   210,   212,   216,   220,   224,   228,
     230,   234,   238,   240,   244
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      55,     0,    -1,    56,    -1,     3,     4,    44,    59,    45,
      56,    -1,     3,     4,    11,    56,    -1,    57,    -1,    58,
      -1,    57,    58,    -1,    64,    -1,    69,    -1,     5,    -1,
       6,    -1,     7,    -1,     8,    -1,     9,    -1,    46,    47,
      -1,    46,    61,    47,    -1,    62,    -1,    61,    62,    -1,
      64,    -1,    65,    -1,    13,    78,    -1,    63,    48,    -1,
      12,    49,    10,    50,    -1,    12,    49,    10,    51,    79,
      50,    -1,    68,    71,    48,    -1,    60,    -1,    78,    -1,
      66,    -1,    67,    -1,    38,    49,    78,    78,    79,    50,
      65,    -1,    39,    49,    79,    50,    65,    -1,    40,    49,
      79,    50,    65,    -1,    67,    41,    65,    -1,    37,    -1,
      34,    -1,    35,    -1,    36,    -1,    68,    70,    60,    -1,
      23,    -1,    70,    49,    50,    -1,    72,    -1,    71,    51,
      72,    -1,    -1,    23,    73,    19,    74,    -1,    23,    -1,
      77,    -1,    -1,    82,    75,    76,    74,    -1,    19,    -1,
      32,    -1,    33,    -1,    30,    -1,    31,    -1,    84,    -1,
      48,    -1,    79,    48,    -1,    74,    -1,    79,    51,    74,
      -1,    23,    -1,    20,    -1,    22,    -1,    21,    -1,    49,
      79,    50,    -1,    80,    -1,    81,    24,    -1,    81,    25,
      -1,    81,    -1,    83,    82,    -1,    52,    -1,    53,    -1,
      85,    -1,    84,    28,    85,    -1,    84,    29,    85,    -1,
      86,    -1,    85,    44,    86,    -1,    85,    45,    86,    -1,
      85,    26,    86,    -1,    85,    27,    86,    -1,    87,    -1,
      86,    14,    87,    -1,    86,    15,    87,    -1,    82,    -1,
      87,    17,    82,    -1,    87,    16,    82,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   118,   118,   120,   120,   120,   122,   122,   124,   124,
     126,   126,   126,   126,   126,   128,   128,   130,   130,   132,
     132,   132,   132,   134,   134,   136,   139,   147,   147,   147,
     149,   150,   152,   152,   154,   154,   154,   154,   156,   169,
     174,   176,   176,   179,   179,   210,   243,   244,   244,   293,
     293,   293,   294,   294,   296,   298,   298,   300,   300,   303,
     315,   320,   329,   339,   341,   342,   343,   345,   346,   354,
     354,   356,   357,   362,   369,   370,   375,   380,   385,   391,
     392,   393,   395,   396,   397
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "HASH", "INCLUDE", "STDIO", "STDLIB",
  "MATH", "STRING", "TIME", "STRING_LITERAL", "HEADER_LITERAL", "PRINT",
  "RETURN", "'+'", "'-'", "'/'", "'*'", "'%'", "'='", "INTEGER_LITERAL",
  "CHARACTER_LITERAL", "FLOAT_LITERAL", "IDENTIFIER", "INC_OP", "DEC_OP",
  "LE_OP", "GE_OP", "EQ_OP", "NE_OP", "MUL_ASSIGN", "DIV_ASSIGN",
  "ADD_ASSIGN", "SUB_ASSIGN", "CHAR", "INT", "FLOAT", "VOID", "FOR",
  "WHILE", "IF", "ELSE", "\"low\"", "\"high\"", "'<'", "'>'", "'{'", "'}'",
  "';'", "'('", "')'", "','", "\"INC_OP\"", "\"DEC_OP\"", "$accept", "S",
  "program", "translation_unit", "ext_dec", "libraries",
  "compound_statement", "block_item_list", "block_item", "printstat",
  "declaration", "statement", "iteration_statement", "condition_statement",
  "type_specifier", "function_definition", "declarator",
  "init_declarator_list", "init_declarator", "$@1",
  "assignment_expression", "$@2", "assignment_operator",
  "conditional_expression", "expression_statement", "expression",
  "primary_expression", "postfix_expression", "unary_expression",
  "unary_operator", "equality_expression", "relational_expression",
  "additive_expression", "multiplicative_expression", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,    43,    45,    47,    42,    37,    61,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,    60,    62,   123,   125,    59,    40,
      41,    44,   293,   294
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    54,    55,    56,    56,    56,    57,    57,    58,    58,
      59,    59,    59,    59,    59,    60,    60,    61,    61,    62,
      62,    62,    62,    63,    63,    64,    65,    65,    65,    65,
      66,    66,    67,    67,    68,    68,    68,    68,    69,    70,
      70,    71,    71,    73,    72,    72,    74,    75,    74,    76,
      76,    76,    76,    76,    77,    78,    78,    79,    79,    80,
      80,    80,    80,    80,    81,    81,    81,    82,    82,    83,
      83,    84,    84,    84,    85,    85,    85,    85,    85,    86,
      86,    86,    87,    87,    87
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     6,     4,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     2,     3,     1,     2,     1,
       1,     2,     2,     4,     6,     3,     1,     1,     1,     1,
       7,     5,     5,     3,     1,     1,     1,     1,     3,     1,
       3,     1,     3,     0,     4,     1,     1,     0,     4,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     3,     1,
       1,     1,     1,     3,     1,     2,     2,     1,     2,     1,
       1,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    35,    36,    37,    34,     0,     2,     5,     6,
       8,     0,     9,     0,     1,     7,    39,     0,     0,    41,
       0,     0,     0,     0,     0,    38,    25,     0,     4,    10,
      11,    12,    13,    14,     0,     0,     0,     0,    60,    62,
      61,    59,     0,     0,     0,    15,    55,     0,    69,    70,
      26,     0,    17,     0,    19,    20,    28,    29,     0,    57,
      46,    27,     0,    64,    67,    82,     0,    54,    71,    74,
      79,    40,    45,    42,     0,    44,     0,    21,     0,     0,
       0,     0,    16,    18,    22,     0,    56,     0,    65,    66,
       0,    68,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     3,     0,     0,     0,     0,    63,    33,    58,
      49,    52,    53,    50,    51,     0,    82,    72,    73,    77,
      78,    75,    76,    80,    81,    84,    83,    23,     0,     0,
       0,     0,    48,     0,     0,    31,    32,    24,     0,    30
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     6,     7,     8,     9,    34,    50,    51,    52,    53,
      10,    55,    56,    57,    11,    12,    17,    18,    19,    22,
      59,    90,   115,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -82
static const yytype_int16 yypact[] =
{
       4,     9,   -82,   -82,   -82,   -82,    18,   -82,    56,   -82,
     -82,     8,   -82,    23,   -82,   -82,    47,    50,   -34,   -82,
       4,     3,     7,    24,   -15,   -82,   -82,    31,   -82,   -82,
     -82,   -82,   -82,   -82,    20,    -1,    62,    87,   -82,   -82,
     -82,   -82,    89,   108,   131,   -82,   -82,    -1,   -82,   -82,
     -82,    66,   -82,    21,   -82,   -82,   -82,    39,    31,   -82,
     -82,   -82,    86,   -82,    60,    -3,    -1,    46,   -21,   102,
     130,   -82,    78,   -82,     4,   -82,   141,   -82,    87,    -1,
      -1,   114,   -82,   -82,   -82,   110,   -82,    -1,   -82,   -82,
     122,   -82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   -82,   116,    87,   118,   120,   -82,   -82,   -82,
     -82,   -82,   -82,   -82,   -82,    -1,   -82,   -21,   -21,   102,
     102,   102,   102,   130,   130,   -82,   -82,   -82,    -1,    -1,
     110,   110,   -82,   123,   125,   -82,   -82,   -82,   110,   -82
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -82,   -82,   -18,   -82,   164,   -82,   162,   -82,   132,   -82,
      -8,   -81,   -82,   -82,     2,   -82,   -82,   -82,   154,   -82,
     -32,   -82,   -82,   -82,   -36,   -47,   -82,   -82,    28,   -82,
     -82,    68,    48,    79
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -48
static const yytype_int16 yytable[] =
{
      81,    77,    28,    75,   108,    94,    95,     1,    29,    30,
      31,    32,    33,    13,    26,    54,   -47,    27,    14,    38,
      39,    40,    41,    96,    97,    58,    35,   -47,   -47,   -47,
     -47,    16,   105,   106,    20,    71,    36,    37,     2,     3,
       4,     5,   104,    54,    38,    39,    40,    41,    47,   135,
     136,    48,    49,    58,    72,   109,   102,   139,     2,     3,
       4,     5,    42,    43,    44,    74,   -43,    21,   129,    84,
      23,    45,    46,    47,    92,    93,    48,    49,    36,    37,
      85,   133,   134,   132,    88,    89,    38,    39,    40,    41,
       2,     3,     4,     5,    91,   -45,    23,   -43,   -45,    24,
       2,     3,     4,     5,    42,    43,    44,    38,    39,    40,
      41,    76,    23,    82,    46,    47,    98,    99,    48,    49,
     116,   116,   116,   116,   116,   116,   116,   116,   125,   126,
      38,    39,    40,    41,    86,    46,    47,    87,    78,    48,
      49,   110,   119,   120,   121,   122,   100,   101,    42,    43,
      44,   103,   111,   112,   113,   114,    23,    79,    46,    47,
     117,   118,    48,    49,   107,    87,   127,   128,   130,    87,
     131,    87,    15,   137,    87,   138,    87,   123,   124,    25,
      80,    73,     0,    83
};

static const yytype_int16 yycheck[] =
{
      47,    37,    20,    35,    85,    26,    27,     3,     5,     6,
       7,     8,     9,     4,    48,    23,    19,    51,     0,    20,
      21,    22,    23,    44,    45,    23,    19,    30,    31,    32,
      33,    23,    79,    80,    11,    50,    12,    13,    34,    35,
      36,    37,    78,    51,    20,    21,    22,    23,    49,   130,
     131,    52,    53,    51,    23,    87,    74,   138,    34,    35,
      36,    37,    38,    39,    40,    45,    19,    44,   104,    48,
      46,    47,    48,    49,    28,    29,    52,    53,    12,    13,
      41,   128,   129,   115,    24,    25,    20,    21,    22,    23,
      34,    35,    36,    37,    66,    48,    46,    19,    51,    49,
      34,    35,    36,    37,    38,    39,    40,    20,    21,    22,
      23,    49,    46,    47,    48,    49,    14,    15,    52,    53,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
      20,    21,    22,    23,    48,    48,    49,    51,    49,    52,
      53,    19,    94,    95,    96,    97,    16,    17,    38,    39,
      40,    10,    30,    31,    32,    33,    46,    49,    48,    49,
      92,    93,    52,    53,    50,    51,    50,    51,    50,    51,
      50,    51,     8,    50,    51,    50,    51,    98,    99,    17,
      49,    27,    -1,    51
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    34,    35,    36,    37,    55,    56,    57,    58,
      64,    68,    69,     4,     0,    58,    23,    70,    71,    72,
      11,    44,    73,    46,    49,    60,    48,    51,    56,     5,
       6,     7,     8,     9,    59,    19,    12,    13,    20,    21,
      22,    23,    38,    39,    40,    47,    48,    49,    52,    53,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    74,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    50,    23,    72,    45,    74,    49,    78,    49,    49,
      49,    79,    47,    62,    48,    41,    48,    51,    24,    25,
      75,    82,    28,    29,    26,    27,    44,    45,    14,    15,
      16,    17,    56,    10,    78,    79,    79,    50,    65,    74,
      19,    30,    31,    32,    33,    76,    82,    85,    85,    86,
      86,    86,    86,    87,    87,    82,    82,    50,    51,    78,
      50,    50,    74,    79,    79,    65,    65,    50,    50,    65
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 18:

/* Line 1455 of yacc.c  */
#line 130 "newast.y"
    {	create_node("stmt", 0);	;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 132 "newast.y"
    { create_node("return", 1);	;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 139 "newast.y"
    {
						struct node *ftp;
						ftp = first;
						while(ftp!=NULL){
							if(ftp->scope == scope && ftp->valid == 1){
								ftp->valid = 0;}
							ftp=ftp->link; }
						scope--;;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 149 "newast.y"
    { 	create_node("for", 0); ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 150 "newast.y"
    { create_node("while", 0); ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 152 "newast.y"
    {create_node("if",0);;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 152 "newast.y"
    {create_node("else",0);;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 154 "newast.y"
    {	datatype = (yyvsp[(1) - (1)].ival); ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 154 "newast.y"
    { datatype = (yyvsp[(1) - (1)].ival); ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 154 "newast.y"
    {	datatype = (yyvsp[(1) - (1)].ival); ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 154 "newast.y"
    {datatype = (yyvsp[(1) - (1)].ival); ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 157 "newast.y"
    {
					create_node((yyvsp[(2) - (3)].string), 3);
					struct node *ftp;
					ftp = first;
					while(ftp!=NULL){
						if(ftp->scope == scope && ftp->valid == 1){
							ftp->valid = 0;		}
						else if(strcmp(ftp->token, "param") == 0 && ftp->valid == 1){
							ftp->valid = 0;		}
						ftp=ftp->link;		}
					scope--;					;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 169 "newast.y"
    {		if((yyvsp[(1) - (1)].ptr)->dtype == -1) {
       								(yyvsp[(1) - (1)].ptr)->dtype = datatype;
        							(yyvsp[(1) - (1)].ptr)->val.i = 0;
        							strcpy((yyvsp[(1) - (1)].ptr)->token, "function");	}
								strcpy((yyval.string), (yyvsp[(1) - (1)].ptr)->name); 									;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 174 "newast.y"
    { ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 179 "newast.y"
    { create_node((yyvsp[(1) - (1)].ptr)->name, 1); ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 179 "newast.y"
    {	
						if((yyvsp[(1) - (4)].ptr)->dtype !=- 1 && (yyvsp[(1) - (4)].ptr)->scope < scope && (yyvsp[(1) - (4)].ptr)->valid == 1){
							struct node *ftp, *nnode;
							nnode = (struct node *)malloc(sizeof(struct node));
							ftp = first;
							while(ftp->link!=NULL){
								ftp = ftp->link;}
							addsymbol(nnode,(yyvsp[(1) - (4)].ptr)->name);	
							ftp->link = nnode;
							nnode->link = NULL;
							(yyvsp[(1) - (4)].ptr) = nnode;

							float tempf; 

							switch(datatype){
								case 0: addInt((yyvsp[(1) - (4)].ptr), 0, (yyvsp[(4) - (4)].fval)); break;
								case 1: addFloat((yyvsp[(1) - (4)].ptr), 1, (yyvsp[(4) - (4)].fval)); break;
								case 2: tempf = (float)(yyvsp[(4) - (4)].fval);
										addChar((yyvsp[(1) - (4)].ptr), 2, (int)tempf); break; }
							create_node("=", 0); }
						
						else{
							float tempf;

							create_node("=", 0);
							switch(datatype){
								case 0: addInt((yyvsp[(1) - (4)].ptr), 0, (yyvsp[(4) - (4)].fval)); break;
								case 1: addFloat((yyvsp[(1) - (4)].ptr), 1, (yyvsp[(4) - (4)].fval)); break;
								case 2: tempf = (float)(yyvsp[(4) - (4)].fval);
										addChar((yyvsp[(1) - (4)].ptr), 2, (int)tempf); break; }
						}		;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 210 "newast.y"
    {	if((yyvsp[(1) - (1)].ptr)->dtype !=- 1 && (yyvsp[(1) - (1)].ptr)->scope < scope && (yyvsp[(1) - (1)].ptr)->valid == 1){
																							
							struct node *ftp, *nnode;
							nnode = (struct node *)malloc(sizeof(struct node));
							ftp = first;
							while(ftp->link!=NULL){
								ftp = ftp->link; }
							addsymbol(nnode,(yyvsp[(1) - (1)].ptr)->name);	
							ftp->link = nnode;
							nnode->link = NULL;							
							(yyvsp[(1) - (1)].ptr) = nnode;
							
							switch(datatype){
								case 0: addInt((yyvsp[(1) - (1)].ptr), 0, INT_MIN); break;
								case 1: addFloat((yyvsp[(1) - (1)].ptr), 1, INT_MIN); break;
								case 2: addChar((yyvsp[(1) - (1)].ptr), 2, '-'); }

							char buff[20];
							strcpy(buff, "Dc ");
							strcat(buff, (yyvsp[(1) - (1)].ptr)->name);
							create_node(buff, 1); 	}
						
						else{
							switch(datatype){
								case 0: addInt((yyvsp[(1) - (1)].ptr), 0, INT_MIN); break;
								case 1: addFloat((yyvsp[(1) - (1)].ptr), 1, INT_MIN); break;
								case 2: addChar((yyvsp[(1) - (1)].ptr), 2, '-'); }
							char buff[20];
							strcpy(buff, "Dc ");
							strcat(buff, (yyvsp[(1) - (1)].ptr)->name);
							create_node(buff, 1); }				;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 243 "newast.y"
    {	(yyval.fval) = (yyvsp[(1) - (1)].fval); ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 244 "newast.y"
    { crt = lhs; ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 245 "newast.y"
    {	switch(assignop){
					case 0: if(idcheck == 1){
								create_node("=", 0);
								switch(crt->dtype){
									case 0: crt->val.i = (int)(yyvsp[(4) - (4)].fval); break;
									case 1: crt->val.f = (yyvsp[(4) - (4)].fval); break;
									case 2: crt->val.c = (char)((int)(yyvsp[(4) - (4)].fval)); }
								}
							crt = NULL; break;

					case 1: if(idcheck == 1){
								create_node("+=", 0);
								switch(crt->dtype){
									case 0: crt->val.i = (int)(yyvsp[(1) - (4)].fval) + (int)(yyvsp[(4) - (4)].fval); break;
									case 1: crt->val.f = (yyvsp[(1) - (4)].fval) + (yyvsp[(4) - (4)].fval); break;
									case 2: crt->val.c = (char)((int)(yyvsp[(1) - (4)].fval) + (int)(yyvsp[(4) - (4)].fval)); }
								}
							crt = NULL; break;

					case 2:	if(idcheck == 1){
								create_node("-=", 0);
								switch(crt->dtype){
									case 0: crt->val.i = (int)(yyvsp[(1) - (4)].fval) - (int)(yyvsp[(4) - (4)].fval); break;
									case 1: crt->val.f = (yyvsp[(1) - (4)].fval) - (yyvsp[(4) - (4)].fval); break;
									case 2: crt->val.c = (char)((int)(yyvsp[(1) - (4)].fval) - (int)(yyvsp[(4) - (4)].fval)); }
								}
							crt = NULL; break;

					case 3:	if(idcheck == 1){
								create_node("*=", 0);
								switch(crt->dtype){
									case 0: crt->val.i = (int)(yyvsp[(1) - (4)].fval) * (int)(yyvsp[(4) - (4)].fval); break;
									case 1: crt->val.f = (yyvsp[(1) - (4)].fval) * (yyvsp[(4) - (4)].fval); break;
									case 2: crt->val.c = (char)((int)(yyvsp[(1) - (4)].fval) * (int)(yyvsp[(4) - (4)].fval)); }
								}
							crt = NULL; break;

					case 4:	if(idcheck == 1){
								create_node("/=", 0);
								switch(crt->dtype){
									case 0: crt->val.i = (int)(yyvsp[(1) - (4)].fval) / (int)(yyvsp[(4) - (4)].fval); break;
									case 1: crt->val.f = (yyvsp[(1) - (4)].fval) / (yyvsp[(4) - (4)].fval); break;
									case 2: crt->val.c = (char)((int)(yyvsp[(1) - (4)].fval) / (int)(yyvsp[(4) - (4)].fval)); }
								}
							crt = NULL; break;		}
				assignop = -1;
				assigntype = -1;		;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 293 "newast.y"
    {	assignop = 0; ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 293 "newast.y"
    {	assignop = 1; ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 293 "newast.y"
    {	assignop = 2; ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 294 "newast.y"
    { assignop = 3; ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 294 "newast.y"
    {	assignop = 4; ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 296 "newast.y"
    {(yyval.fval) = (yyvsp[(1) - (1)].fval);;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 303 "newast.y"
    {					
					idcheck = 1;
					lhs = (yyvsp[(1) - (1)].ptr);
					switch((yyvsp[(1) - (1)].ptr)->dtype){
						case 0: (yyval.fval) = (yyvsp[(1) - (1)].ptr)->val.i;
								assigntype = 0; break;
						case 1: (yyval.fval) = (yyvsp[(1) - (1)].ptr)->val.f;
								assigntype = 1; break;
						case 2: (yyval.fval) = (yyvsp[(1) - (1)].ptr)->val.c;
								assigntype = 2;		}
					
					create_node((yyvsp[(1) - (1)].ptr)->name, 1);			;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 315 "newast.y"
    {
					(yyval.fval) = (yyvsp[(1) - (1)].ival);
					assigntype = 0;
					sprintf(tempStr, "%d", (int)(yyvsp[(1) - (1)].ival));
					create_node(tempStr, 1);	;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 320 "newast.y"
    {	
					assigntype = 1;
					switch(datatype){
						case 1: (yyval.fval) = (yyvsp[(1) - (1)].fval); break;
						case 0: 
						case 2: (yyval.fval) = (int)(yyvsp[(1) - (1)].fval); }

					sprintf(tempStr, "%f", (yyvsp[(1) - (1)].fval));
					create_node(tempStr, 1);  ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 329 "newast.y"
    {	
					assigntype = 2;
					int temp;
					switch(datatype){
						case 2: temp = (int)(yyvsp[(1) - (1)].cval);
								(yyval.fval) =  (float)temp; break;
						case 0:
						case 1: (yyval.fval) = (int)(yyvsp[(1) - (1)].cval); }
					sprintf(tempStr, "%c", (yyvsp[(1) - (1)].cval));
					create_node(tempStr, 1);		;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 339 "newast.y"
    { (yyval.fval) = (yyvsp[(2) - (3)].fval);;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 341 "newast.y"
    {	(yyval.fval) = (yyvsp[(1) - (1)].fval);	;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 342 "newast.y"
    {	(yyvsp[(1) - (2)].fval)++; (yyval.fval) = (yyvsp[(1) - (2)].fval);	create_node("++", 0); ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 343 "newast.y"
    {	(yyvsp[(1) - (2)].fval)--; (yyval.fval) = (yyvsp[(1) - (2)].fval);	create_node("--", 0); ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 345 "newast.y"
    {	(yyval.fval) = (yyvsp[(1) - (1)].fval);	;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 346 "newast.y"
    {
					switch(unaryop){	
						case 1:	(yyval.fval) = ++(yyvsp[(2) - (2)].fval);
								create_node("++", 0);	break;
						case 2:	(yyval.fval) = --(yyvsp[(2) - (2)].fval);
								create_node("--", 0);	break;		}
					unaryop = -1; ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 354 "newast.y"
    { unaryop = 1; ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 354 "newast.y"
    {unaryop = 2;;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 356 "newast.y"
    {	(yyval.fval) = (yyvsp[(1) - (1)].fval);	;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 358 "newast.y"
    { 	create_node("==", 0);
					if((yyvsp[(1) - (3)].fval) == (yyvsp[(3) - (3)].fval))
						(yyval.fval) = 1;
					else	(yyval.fval) = 0;	;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 363 "newast.y"
    {   create_node("!=", 0);
					if((yyvsp[(1) - (3)].fval) != (yyvsp[(3) - (3)].fval))
						(yyval.fval) = 1;
					else	(yyval.fval) = 0; ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 369 "newast.y"
    {	(yyval.fval) = (yyvsp[(1) - (1)].fval);	;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 371 "newast.y"
    {	create_node("<", 0);
					if((yyvsp[(1) - (3)].fval) < (yyvsp[(3) - (3)].fval))
						(yyval.fval) = 1;
					else	(yyval.fval) = 0;	;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 376 "newast.y"
    { 	create_node(">", 0);
					if((yyvsp[(1) - (3)].fval) > (yyvsp[(3) - (3)].fval))
						(yyval.fval) = 1;
					else	(yyval.fval) = 0;	;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 381 "newast.y"
    { 	create_node("<=", 0);
					if((yyvsp[(1) - (3)].fval) <= (yyvsp[(3) - (3)].fval))
						(yyval.fval) = 1;
					else	(yyval.fval) = 0;	;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 386 "newast.y"
    { 	create_node(">=", 0);
					if((yyvsp[(1) - (3)].fval) >= (yyvsp[(3) - (3)].fval))
						(yyval.fval) = 1;
					else	(yyval.fval) = 0;	;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 391 "newast.y"
    {	(yyval.fval) = (yyvsp[(1) - (1)].fval);	;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 392 "newast.y"
    {	create_node("+", 0);	(yyval.fval) = (yyvsp[(1) - (3)].fval) + (yyvsp[(3) - (3)].fval);	;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 393 "newast.y"
    {	create_node("-", 0);	(yyval.fval) = (yyvsp[(1) - (3)].fval) - (yyvsp[(3) - (3)].fval);	;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 395 "newast.y"
    {	(yyval.fval) = (yyvsp[(1) - (1)].fval);	;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 396 "newast.y"
    {	create_node("*", 0);	(yyval.fval) = (yyvsp[(1) - (3)].fval) * (yyvsp[(3) - (3)].fval);	;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 397 "newast.y"
    {	(yyval.fval) = (yyvsp[(1) - (3)].fval) / (yyvsp[(3) - (3)].fval);	create_node("/", 0); ;}
    break;



/* Line 1455 of yacc.c  */
#line 2126 "newast.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 399 "newast.y"


void yyerror(const char *str){
	fflush(stdout);
	printf("Line:%d: %s", line,str); }

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
    tp->lineno = line;		}

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
	printf("%d", h);
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


