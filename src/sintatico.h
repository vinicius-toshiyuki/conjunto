/* A Bison parser, made by GNU Bison 3.7.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_SINTATICO_H_INCLUDED
# define YY_YY_SINTATICO_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 125 "sintatico.y"

#include "tree.h"

#line 53 "sintatico.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    STRING = 258,                  /* STRING  */
    CHAR = 259,                    /* CHAR  */
    INT = 260,                     /* INT  */
    FLOAT = 261,                   /* FLOAT  */
    ID = 262,                      /* ID  */
    TYPE = 263,                    /* TYPE  */
    IN = 264,                      /* IN  */
    OPPOS = 265,                   /* OPPOS  */
    OPUNI = 266,                   /* OPUNI  */
    OPBIN1 = 267,                  /* OPBIN1  */
    OPBIN2 = 268,                  /* OPBIN2  */
    OPBIN3 = 269,                  /* OPBIN3  */
    OPBIN4 = 270,                  /* OPBIN4  */
    OPBIN5 = 271,                  /* OPBIN5  */
    OPBIN6 = 272,                  /* OPBIN6  */
    OPBIN7 = 273,                  /* OPBIN7  */
    OPBIN8 = 274,                  /* OPBIN8  */
    OPASSIGN = 275,                /* OPASSIGN  */
    IF = 276,                      /* IF  */
    WHILE = 277,                   /* WHILE  */
    FORALL = 278,                  /* FORALL  */
    FOR = 279,                     /* FOR  */
    ELSE = 280,                    /* ELSE  */
    RETURN = 281,                  /* RETURN  */
    EMPTY = 282                    /* EMPTY  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define STRING 258
#define CHAR 259
#define INT 260
#define FLOAT 261
#define ID 262
#define TYPE 263
#define IN 264
#define OPPOS 265
#define OPUNI 266
#define OPBIN1 267
#define OPBIN2 268
#define OPBIN3 269
#define OPBIN4 270
#define OPBIN5 271
#define OPBIN6 272
#define OPBIN7 273
#define OPBIN8 274
#define OPASSIGN 275
#define IF 276
#define WHILE 277
#define FORALL 278
#define FOR 279
#define ELSE 280
#define RETURN 281
#define EMPTY 282

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 129 "sintatico.y"

	char name[32768];
	node_t node;

#line 131 "sintatico.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (int *max, int *childrenCount);

#endif /* !YY_YY_SINTATICO_H_INCLUDED  */
