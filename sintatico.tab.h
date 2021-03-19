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

#ifndef YY_YY_SINTATICO_TAB_H_INCLUDED
# define YY_YY_SINTATICO_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    ID = 258,                      /* ID  */
    TYPE = 259,                    /* TYPE  */
    IF = 260,                      /* IF  */
    WHILE = 261,                   /* WHILE  */
    FORALL = 262,                  /* FORALL  */
    FOR = 263,                     /* FOR  */
    ELSE = 264,                    /* ELSE  */
    RETURN = 265,                  /* RETURN  */
    OPPOS = 266,                   /* OPPOS  */
    OPUNI = 267,                   /* OPUNI  */
    OPTER = 268,                   /* OPTER  */
    OPBIN3 = 269,                  /* OPBIN3  */
    OPBIN4 = 270,                  /* OPBIN4  */
    OPBIN5 = 271,                  /* OPBIN5  */
    OPBIN6 = 272,                  /* OPBIN6  */
    OPBIN7 = 273,                  /* OPBIN7  */
    OPBIN8 = 274,                  /* OPBIN8  */
    OPBIN9 = 275,                  /* OPBIN9  */
    OPBIN10 = 276,                 /* OPBIN10  */
    OPASSIGN = 277,                /* OPASSIGN  */
    STRING = 278,                  /* STRING  */
    CHAR = 279,                    /* CHAR  */
    INT = 280,                     /* INT  */
    FLOAT = 281,                   /* FLOAT  */
    EMPTY = 282                    /* EMPTY  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 23 "sintatico.y"

	char name[32768];
	int dval;
	float fval;
	char empty;

#line 98 "sintatico.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SINTATICO_TAB_H_INCLUDED  */
