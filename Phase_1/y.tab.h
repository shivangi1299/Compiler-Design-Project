/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ID = 258,
    num = 259,
    s = 260,
    begin = 261,
    b_open = 262,
    b_close = 263,
    br_open = 264,
    br_close = 265,
    dt = 266,
    semi = 267,
    eq = 268,
    com = 269,
    tif = 270,
    telse = 271,
    relop = 272,
    addop = 273,
    mulop = 274,
    divop = 275,
    subop = 276,
    incop = 277,
    tfor = 278,
    twhile = 279,
    tcout = 280,
    coutop = 281,
    combop = 282
  };
#endif
/* Tokens.  */
#define ID 258
#define num 259
#define s 260
#define begin 261
#define b_open 262
#define b_close 263
#define br_open 264
#define br_close 265
#define dt 266
#define semi 267
#define eq 268
#define com 269
#define tif 270
#define telse 271
#define relop 272
#define addop 273
#define mulop 274
#define divop 275
#define subop 276
#define incop 277
#define tfor 278
#define twhile 279
#define tcout 280
#define coutop 281
#define combop 282

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 29 "validatecfg.y" /* yacc.c:1909  */
 char var[10]; 

#line 111 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
