/* A Bison parser, made by GNU Bison 3.7.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 6 "sintatico.y"
 /* ================== INÍCIO DO PREFÁCIO ===================== */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include "lex.yy.h"
#include "tree.h"

#define NAMESIZE 32768
#define FILENAMESIZE 512

/* ======== Definição de carcteres para impressão da árvore ===== */
#define __UNICODE_CHARS_SUPPPORT__
#ifdef __UNICODE_CHARS_SUPPPORT__

#define TREECHILDFIRST "┬"
#define TREECHILDMID "├"
#define TREECHILDLAST "└"
#define TREECHILD "│"
#define TREELEAF "○"
#define TREEBRANCH "─"

#define ERR_SEPARATOR "══════════"

#else

#define TREECHILDFIRST "."
#define TREECHILDMID "+"
#define TREECHILDLAST "+"
#define TREECHILD "|"
#define TREELEAF ">"
#define TREEBRANCH "-"

#define ERR_SEPARATOR "=========="
#endif
/* ============================================================== */

/* ================== Definição de cores ======================== */
#define CLEARCOLOR "\033[0m"
#define __TRUE_COLOR_SUPPORT__
#ifdef __TRUE_COLOR_SUPPORT__

#define TREEROOTCOLOR "\033[38;2;170;170;170m"
#define TREELEAFCOLOR "\033[1m"

#define ERR_COLOR "\033[48;2;145;40;40m"
#define ERR_TOKEN ERR_COLOR "<error>" CLEARCOLOR
#define ERR_TEMPLATE \
	ERR_COLOR "  > %s" CLEARCOLOR "\n" ERR_COLOR ERR_SEPARATOR CLEARCOLOR "\n"
#define ERR_LOCATION ERR_COLOR "%s:%d:%d" CLEARCOLOR "\n"

#else

#define TREEROOTCOLOR "\033[90m"
#define TREELEAFCOLOR "\033[1m"

#define ERR_COLOR "\033[31;7m"
#define ERR_TOKEN ERR_COLOR "<error>" CLEARCOLOR
#define ERR_TEMPLATE \
	ERR_COLOR "  > %s" CLEARCOLOR "\n" ERR_COLOR ERR_SEPARATOR CLEARCOLOR "\n"
#define ERR_LOCATION ERR_COLOR "%s:%d:%d" CLEARCOLOR "\n"
#endif
/* ============================================================== */

/* ========================= Macros ============================= */
#define ADD_BIN_EXP(RES, EXP1, OP, EXP2) {      \
	node_t exp = create_node(strdup("<exp>"));  \
	node_t op = create_node(strdup("<opbin>")); \
	add_child(OP, op);                          \
	add_child(EXP1, exp);                       \
	add_child(op, exp);                         \
	add_child(EXP2, exp);                       \
	RES = exp;                                  \
}

#define ADD_BIN_EXP_ERR(RES, EXP1, OP) {             \
	node_t exp = create_node(strdup("<exp>"));       \
	node_t op = create_node(strdup("<opbin>"));      \
	add_child(OP, op);                               \
	add_child(EXP1, exp);                            \
	add_child(op, exp);                              \
	node_t err = create_node(ERR_TOKEN);             \
	add_child(err, exp);                             \
	RES = exp;                                       \
	ssprintf(                                        \
		syn_errormsg,                                \
		"Expected expression while processing '%s'", \
		OP->value                                    \
		);                                           \
}

#define ADD_UNI_EXP(RES, OP, EXP1) {            \
	node_t exp = create_node(strdup("<exp>"));  \
	node_t op = create_node(strdup("<opuni>")); \
	add_child(OP, op);                          \
	add_child(op, exp);                         \
	add_child(EXP1, exp);                       \
	RES = exp;                                  \
}

#define FIRSTCHILD_VALUE(NODE) \
	((char *) ((node_t) NODE->children->first->value)->value)

#define PUSH_CONTEXT { \
	node_t OLD_CONTEXT = current_context; \
	current_context = create_node(create_list()); \
	add_child(current_context, OLD_CONTEXT); \
}

#define POP_CONTEXT \
	current_context = current_context->parent;

enum {
	FUN,
	VAR
};
#define ADD_CONTEXT(ENTRY_CONTEXT, ID_CONTEXT, TYPE_CONTEXT) {  \
	char TEMPLATE[] = "<%s '%s' (%s)>";                         \
	char *ENTRY, *TYPE;                                          \
	char FUNCTION[] = "function", VARIABLE[] = "variable";      \
	switch (ENTRY_CONTEXT) {                                    \
		case FUN: TYPE = FUNCTION; break;                       \
		case VAR: TYPE = VARIABLE; break;                       \
		default:                                                \
			fprintf(stderr, "Invalid entry type in context\n"); \
			exit(EXIT_FAILURE);                                 \
	}                                                           \
	ENTRY = (char *) malloc(                                    \
		strlen(TEMPLATE) +                                      \
		strlen(TYPE) +                                          \
		strlen(ID_CONTEXT) +                                    \
		strlen(TYPE_CONTEXT) + 1                                \
		);                                                      \
	sprintf(ENTRY, TEMPLATE, TYPE, ID_CONTEXT, TYPE_CONTEXT);   \
	insert(0, ENTRY, current_context->value);                   \
}

/* ============================================================== */

/* Estrutura para passar argumentos para impressão */
typedef struct {
	int *childrenCount;
	void (*val_print)(node_t value);
} printData_t;

/* Assinatura dependente do %parse-param */
int yyerror(int *max, int *childrenCount, char *s);
int yylex();

void ssprintf(char *target, char *template, ...); /* É a mesma coisa do sprintf() */
void print(node_t node, void *data);              /* Imprime um nó de uma árvore */
void print_syntatic(node_t value);                /* Imprime o valor de um nó da árvore sintática */
void print_context(node_t value);                 /* Imprime o valor de um nó do contexto */
void max_level(node_t node, void *data);          /* Obtém a profundidade de uma árvore */
void free_values(node_t node, void *data);        /* Libera a memória do valor de um nó */
void free_context(node_t node, void *data);       /* Libera a memória de um context */

extern int lnum, lcol; /* Vêm do lexico.l */

char filename[FILENAMESIZE + 1]; /* Armazena o nome do arquivo de entrada */
char syn_errormsg[NAMESIZE + 1]; /* Armazena a próxima mensagem de erro */

node_t root;    /* Raiz da árvore sintática */
list_t parents; /* Auxilia na inserção na árvore */

node_t current_context;
node_t context; /* Árvore de contextos */

#line 241 "sintatico.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "sintatico.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_STRING = 3,                     /* STRING  */
  YYSYMBOL_CHAR = 4,                       /* CHAR  */
  YYSYMBOL_INT = 5,                        /* INT  */
  YYSYMBOL_FLOAT = 6,                      /* FLOAT  */
  YYSYMBOL_ID = 7,                         /* ID  */
  YYSYMBOL_TYPE = 8,                       /* TYPE  */
  YYSYMBOL_IN = 9,                         /* IN  */
  YYSYMBOL_OPPOS = 10,                     /* OPPOS  */
  YYSYMBOL_OPUNI = 11,                     /* OPUNI  */
  YYSYMBOL_OPBIN1 = 12,                    /* OPBIN1  */
  YYSYMBOL_OPBIN2 = 13,                    /* OPBIN2  */
  YYSYMBOL_OPBIN3 = 14,                    /* OPBIN3  */
  YYSYMBOL_OPBIN4 = 15,                    /* OPBIN4  */
  YYSYMBOL_OPBIN5 = 16,                    /* OPBIN5  */
  YYSYMBOL_OPBIN6 = 17,                    /* OPBIN6  */
  YYSYMBOL_OPBIN7 = 18,                    /* OPBIN7  */
  YYSYMBOL_OPBIN8 = 19,                    /* OPBIN8  */
  YYSYMBOL_OPASSIGN = 20,                  /* OPASSIGN  */
  YYSYMBOL_21_ = 21,                       /* '*'  */
  YYSYMBOL_22_ = 22,                       /* '/'  */
  YYSYMBOL_23_ = 23,                       /* '+'  */
  YYSYMBOL_24_ = 24,                       /* '-'  */
  YYSYMBOL_25_ = 25,                       /* '%'  */
  YYSYMBOL_26_ = 26,                       /* '!'  */
  YYSYMBOL_27_ = 27,                       /* '~'  */
  YYSYMBOL_28_ = 28,                       /* '&'  */
  YYSYMBOL_IF = 29,                        /* IF  */
  YYSYMBOL_WHILE = 30,                     /* WHILE  */
  YYSYMBOL_FORALL = 31,                    /* FORALL  */
  YYSYMBOL_FOR = 32,                       /* FOR  */
  YYSYMBOL_ELSE = 33,                      /* ELSE  */
  YYSYMBOL_RETURN = 34,                    /* RETURN  */
  YYSYMBOL_EMPTY = 35,                     /* EMPTY  */
  YYSYMBOL_36_ = 36,                       /* '?'  */
  YYSYMBOL_37_ = 37,                       /* ':'  */
  YYSYMBOL_38_ = 38,                       /* '('  */
  YYSYMBOL_39_ = 39,                       /* ')'  */
  YYSYMBOL_40_ = 40,                       /* ';'  */
  YYSYMBOL_41_ = 41,                       /* '{'  */
  YYSYMBOL_42_ = 42,                       /* '}'  */
  YYSYMBOL_43_ = 43,                       /* ','  */
  YYSYMBOL_44_ = 44,                       /* '='  */
  YYSYMBOL_YYACCEPT = 45,                  /* $accept  */
  YYSYMBOL_prog = 46,                      /* prog  */
  YYSYMBOL_declarations = 47,              /* declarations  */
  YYSYMBOL_48_1 = 48,                      /* $@1  */
  YYSYMBOL_declarationstail = 49,          /* declarationstail  */
  YYSYMBOL_50_2 = 50,                      /* $@2  */
  YYSYMBOL_cmd = 51,                       /* cmd  */
  YYSYMBOL_52_3 = 52,                      /* @3  */
  YYSYMBOL_53_4 = 53,                      /* $@4  */
  YYSYMBOL_54_5 = 54,                      /* $@5  */
  YYSYMBOL_cmds = 55,                      /* cmds  */
  YYSYMBOL_56_6 = 56,                      /* $@6  */
  YYSYMBOL_cmdstail = 57,                  /* cmdstail  */
  YYSYMBOL_58_7 = 58,                      /* $@7  */
  YYSYMBOL_declaration = 59,               /* declaration  */
  YYSYMBOL_60_8 = 60,                      /* @8  */
  YYSYMBOL_61_9 = 61,                      /* @9  */
  YYSYMBOL_62_10 = 62,                     /* @10  */
  YYSYMBOL_63_11 = 63,                     /* $@11  */
  YYSYMBOL_64_12 = 64,                     /* @12  */
  YYSYMBOL_65_13 = 65,                     /* @13  */
  YYSYMBOL_66_14 = 66,                     /* $@14  */
  YYSYMBOL_declr_fntail = 67,              /* declr_fntail  */
  YYSYMBOL_68_15 = 68,                     /* $@15  */
  YYSYMBOL_69_16 = 69,                     /* $@16  */
  YYSYMBOL_70_17 = 70,                     /* $@17  */
  YYSYMBOL_parlist = 71,                   /* parlist  */
  YYSYMBOL_72_18 = 72,                     /* @18  */
  YYSYMBOL_73_19 = 73,                     /* $@19  */
  YYSYMBOL_74_20 = 74,                     /* $@20  */
  YYSYMBOL_partail = 75,                   /* partail  */
  YYSYMBOL_forargs = 76,                   /* forargs  */
  YYSYMBOL_77_21 = 77,                     /* $@21  */
  YYSYMBOL_78_22 = 78,                     /* $@22  */
  YYSYMBOL_79_23 = 79,                     /* $@23  */
  YYSYMBOL_80_24 = 80,                     /* $@24  */
  YYSYMBOL_81_25 = 81,                     /* $@25  */
  YYSYMBOL_fordeclrlist = 82,              /* fordeclrlist  */
  YYSYMBOL_fortail = 83,                   /* fortail  */
  YYSYMBOL_idlist = 84,                    /* idlist  */
  YYSYMBOL_85_26 = 85,                     /* $@26  */
  YYSYMBOL_86_27 = 86,                     /* $@27  */
  YYSYMBOL_exp = 87,                       /* exp  */
  YYSYMBOL_88_28 = 88,                     /* @28  */
  YYSYMBOL_fntail = 89,                    /* fntail  */
  YYSYMBOL_arglist = 90,                   /* arglist  */
  YYSYMBOL_argtail = 91                    /* argtail  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   13156

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  47
/* YYNRULES -- Number of rules.  */
#define YYNRULES  129
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  680

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   282


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    26,     2,     2,     2,    25,    28,     2,
      38,    39,    21,    23,    43,    24,     2,    22,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    37,    40,
       2,    44,     2,    36,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    41,     2,    42,    27,     2,     2,     2,
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
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    29,    30,    31,    32,
      33,    34,    35
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   229,   229,   231,   232,   232,   237,   238,   238,   243,
     248,   254,   259,   264,   267,   264,   273,   274,   277,   277,
     285,   288,   290,   296,   303,   309,   315,   322,   323,   323,
     328,   329,   329,   334,   334,   344,   344,   359,   364,   359,
     375,   384,   390,   375,   400,   400,   409,   409,   421,   421,
     435,   436,   436,   444,   444,   451,   451,   460,   461,   469,
     479,   487,   479,   490,   497,   490,   500,   500,   503,   510,
     511,   517,   520,   525,   526,   526,   529,   529,   535,   536,
     537,   538,   539,   540,   541,   549,   550,   551,   552,   553,
     554,   555,   556,   557,   558,   559,   560,   561,   562,   563,
     564,   565,   566,   567,   568,   569,   582,   591,   591,   599,
     601,   602,   603,   604,   605,   606,   607,   608,   609,   610,
     611,   612,   613,   614,   632,   633,   636,   637,   640,   641
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "STRING", "CHAR",
  "INT", "FLOAT", "ID", "TYPE", "IN", "OPPOS", "OPUNI", "OPBIN1", "OPBIN2",
  "OPBIN3", "OPBIN4", "OPBIN5", "OPBIN6", "OPBIN7", "OPBIN8", "OPASSIGN",
  "'*'", "'/'", "'+'", "'-'", "'%'", "'!'", "'~'", "'&'", "IF", "WHILE",
  "FORALL", "FOR", "ELSE", "RETURN", "EMPTY", "'?'", "':'", "'('", "')'",
  "';'", "'{'", "'}'", "','", "'='", "$accept", "prog", "declarations",
  "$@1", "declarationstail", "$@2", "cmd", "@3", "$@4", "$@5", "cmds",
  "$@6", "cmdstail", "$@7", "declaration", "@8", "@9", "@10", "$@11",
  "@12", "@13", "$@14", "declr_fntail", "$@15", "$@16", "$@17", "parlist",
  "@18", "$@19", "$@20", "partail", "forargs", "$@21", "$@22", "$@23",
  "$@24", "$@25", "fordeclrlist", "fortail", "idlist", "$@26", "$@27",
  "exp", "@28", "fntail", "arglist", "argtail", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,    42,    47,    43,    45,    37,    33,   126,    38,   276,
     277,   278,   279,   280,   281,   282,    63,    58,    40,    41,
      59,   123,   125,    44,    61
};
#endif

#define YYPACT_NINF (-649)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-130)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     167,   128,   101,   113,   202,   299,    40,    48,    91,  -649,
     213,    86,    28,    52,   106,   144,   107,   122,   260,    90,
     136,    28,    28,    71,    23,   172,   179,   213,   183,   267,
     186,   271,   195,   229,    80,   130,    80,   185,   279,   290,
    2993,    24,   302,   303,   313,   184,   314,   275,   300,  3033,
     277,  3073,    80,   333,   310,   318,   319,  3033,  8629,  8658,
    8687,  8716,  8599,  6900,  6900,  6900,  6900,  6900,  6900,  6900,
     315,   322,   323,   326,  4228,  8745,  6926,  3113,  3153,   324,
     332,  3193,  8774,  3233,  3033,   340,    80,   339,  8803,  4264,
     345,  8832,  8861,  8890,  8919,  8948,  8977,  9006,  4300,  4336,
    4372,   346,   347,  9035, 10165,  3273,  3033,   312,  6900,  4408,
    4444,  4480,  4516,  4552,  4588,  4624,   385,  4660,  4696,  4732,
    4768,  4804,  6952,  3313,  3033,   349,   387,   388,  9064,  9093,
     551,  9122,   353, 10193,   355, 10221,   357, 10249,  4190,  3353,
    3393,  9151,  3433,   358,   359,  9180,  9209,  9238,  9267,  9296,
    9325,  9354,  9383,  9412,  9441,  9470,  9499,  9528,  9557,  9586,
    9615,  9644,  9673,  9702,  9731,  9760,  9789,  9818,  9847,  9876,
    9905, 11819,   360,   335,   398,   354,    36,  4073,  4073,  4112,
    4112,  4112,  4112,   396,  4830,   365,   367,  9934,  3273,  3473,
    6900,   336,   338,  6978,    45,  9963,  9992,  2033,  2073,  3513,
    3553,  3593,  3633,   230, 10021,  4151,   366,   368,   375, 10050,
     354,  4112,  4112,  7004,    28,  4112,   367,    72,  3673,  3713,
    7063,   383,  3753,   386,   169,   368,   417,   392,   367,   382,
     368,   389,  7004,   367,  7095,   399,   395,   420,   429,   141,
   10277, 10305, 10333, 10361, 10137,  6926,  6926,  6926,  6926,  6926,
    6926,  6926, 10389,  6926,  6926,  4868,  4904,  4940,  4976,  5012,
    5048,  5084,   440,  5120,  5156,  5192,  5228,  5264,  6952, 11845,
   11871, 11897, 11923, 11789,  6952,  6952,  6952,  6952,  6952,  6952,
    6952, 11949,  6926,   397,   433,   634,   666,   309,  6978,  6978,
    6978,  6978,  6978,  6978,  6978,   698,  6926,  6952,  5300,  5336,
    5372,  5408,  5444,  5480,  5516,   442,  5552,  5588,  5624,  5660,
    5696,  6952,  6978,  5732,  5768,  5804,  5840,  5876,  5912,  5948,
     443,  5984,  6020,  6056,  6092,  6128,  6952,   238,   421,   422,
     430,   326,  6164,  2113,   426,  2153, 10079,  6874,  7127,  7159,
    7191,  7223,  7031,  7004,  7004,  7004,  7004,  7004,  7004,  7004,
    7255,  6926,  7004,  6200,  6236,  6272,  6308,  6344,  6380,  6416,
     469,  6452,  6488,  6524,  6560,  6596,  6952,   184,   464,   316,
     435,    91, 10417,  6632,   436, 10445, 10473, 10501, 10529, 10557,
   10585, 10613, 10641, 10669, 10697, 10725, 10753, 10781, 10809, 10837,
   10865, 10893, 10921, 10949, 10977, 11005, 11033, 11061, 11089, 11117,
   11145, 11173, 11201, 11229, 11257, 11285, 11313, 11341, 11369, 11975,
   12001,  6668,   437, 12027, 12053, 12079, 12105, 12131, 12157, 12183,
   11397,   730,  6704,   439,   762,   794,   826,   858,   890,   922,
     954, 11425, 12209, 12235, 12261, 12287, 12313, 12339, 12365, 12391,
   12417, 12443, 12469, 12495, 12521, 12547, 12573, 12599, 12625, 12651,
   12677, 12703, 12729, 12755, 12781, 12807, 12833, 12859, 12885,   986,
    1018,  1050,  1082,  1114,  1146,  1178,  1210,  1242,  1274,  1306,
    1338,  1370,  1402,  1434,  1466,  1498,  1530,  1562,  1594,  1626,
    1658,  1690,  1722,  1754,  1786, 12911,   342,   441,    91,  6740,
    6776,  6812,   444,   438, 10108,  3033,  2193, 11453,  7287,  6848,
     445,  7319,  7351,  7383,  7415,  7447,  7479,  7511, 11481,  7543,
    7575,  7607,  7639,  7671,  7703,  7735,  7767,  7799,  7831,  7863,
    7895,  7927,  7959,  7991,  8023,  8055,  8087,  8119,  8151,  8183,
    8215,  8247,  8279,  8311,  8343, 12937,   446,   184,    86,    28,
     144,   448, 11509, 11537,   551, 11565, 11593,  6926, 12963, 12989,
     551, 13015, 13041,  1818,  1850,   551,  1882,  1914,  6952,  6978,
      86,    28,   144,   449,   447, 11621,   452, 11649,   453, 11677,
    4190,  2233,  2273,   451,  8375,  8407,   551,  8439,  8471,  7004,
     455,    95,   456,   458,   179,    73, 11705,    82,    98, 13067,
    1946,   119,   460,   462,   179,  4073,  4073,  4073,  4073,  4073,
    4073,   463,  2313,   103,  8503,   468,  3793,   465,  3833,   185,
     479, 11733, 11761, 13093, 13119,  1978,  2010,   470,  2353,   466,
    2393,   185,   480,  2433,  2473,  2513,  2553,  2593,  2633,  4151,
    8535,  8567,  2993,    35,   471,  3873,  2993,    44,   472,  2673,
    4073,  4073,  4073,  3033,   474,  3073,  3033,  3033,   475,  3073,
    3033,  2713,  2753,  2793,   461,  3233,  3033,   476,   487,  3233,
    3033,   488,  3913,  3033,   489,   388,  2833,  3033,   490,   388,
     491,  3953,   516,   492,  2873,   520,  3993,  4033,  2913,  2953
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     1,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -649,  -649,  -649,  -649,   514,  -649,   -72,   211,   -86,  -134,
     -42,  -649,   361,  -649,     0,  -367,  -397,  -360,  -571,  -227,
    -589,  -648,  -426,  -623,  -472,  -485,   -18,  -649,  -649,  -649,
     -17,   -25,  -649,  -649,  -649,  -649,  -649,   317,   -71,    68,
    -649,  -649,   -60,  -210,  -356,  -394,   337
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    10,    17,    27,    78,   101,   215,    79,
      80,   105,   143,   188,    81,    12,    19,    16,    38,     7,
      47,   174,    29,    84,    49,   124,    25,    45,    34,    36,
      44,   185,   224,   230,   214,   225,   207,   227,   186,     8,
      22,    21,    82,    90,   131,   176,   194
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
       4,    30,   539,    91,    92,    93,    94,    95,    96,    97,
      18,   541,   370,   610,   103,    87,   104,   672,   545,    46,
     634,   675,   656,   622,   -55,    50,   660,    18,    55,   129,
      35,   -55,   638,   142,   374,    85,   644,   195,   133,   135,
     137,    13,   125,   334,   334,   648,  -127,    14,   145,   147,
     149,   151,   153,   155,   157,   159,   551,   162,   164,   166,
     168,   170,   171,   412,   144,    51,   -55,   556,   -73,   126,
     175,     6,   -53,  -129,   611,   196,   645,   423,   187,   -53,
      20,   -57,   172,   613,  -127,   649,    15,   -35,    42,    32,
      33,    28,   -76,   -35,   -35,   -76,   605,    23,    24,   615,
     487,     9,    23,    24,   630,   197,   198,   199,   200,   201,
     202,  -129,   612,    -2,   -53,   206,   142,   336,   336,   561,
     617,   614,    -5,    43,   204,   -35,    23,    24,   563,   -50,
     209,   -37,   500,   210,   -50,     5,   216,   616,   -51,   218,
     219,   581,   631,   222,   577,   223,   -74,    26,   369,   -74,
     585,    23,    24,   220,   228,   606,   587,   231,   -50,   233,
     643,   588,   235,   591,   647,   618,   -40,    -3,   -73,   -51,
     663,     6,   234,   -51,   667,     1,    31,   335,   335,   -40,
     -38,   -73,   603,   -50,     6,   375,   376,   377,   378,   379,
     380,   381,   237,   382,   383,   385,   387,   389,   391,   393,
     395,   397,    -4,   400,   402,   404,   406,   408,   409,   -69,
      -4,    37,   226,    -6,   413,   414,   415,   416,   417,   418,
     419,     1,   420,   -57,    40,    41,   -41,   238,   424,   425,
     426,   427,   428,   429,   430,   -77,   431,   432,   434,   436,
     438,   440,   442,   444,   446,   486,   449,   451,   453,   455,
     457,   458,   459,   461,   463,   465,   467,   469,   471,   473,
      -7,   476,   478,   480,   482,   484,   485,   -36,    -7,   -75,
     -63,   -34,   494,   -63,   213,   -36,   -40,   497,   -73,   -34,
      48,     6,   221,   501,   502,   503,   504,   505,   506,   507,
      -8,   508,   509,   511,   513,   515,   517,   519,   521,   523,
     -39,   526,   528,   530,   532,   534,   535,   371,   -39,    52,
     -83,    53,   -47,   543,    54,    56,    57,    83,   -83,   421,
     -47,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   422,
     -83,   -83,   -83,   -83,   -83,   -45,   -49,    11,   -43,   -33,
      86,   -59,   -33,   -45,   -49,   -83,   -43,  -107,   -83,   -54,
     536,   549,   -83,    98,   538,  -128,   -33,   -52,   -56,   -33,
      99,   100,   554,   312,   -13,   106,   313,   314,   315,   316,
     317,   318,   319,   320,   107,   321,   322,   323,   324,   325,
     560,   127,   -33,   130,   138,   -33,   160,   139,   -58,   -42,
     326,   173,   177,  -128,   179,   488,   181,   193,   -81,   192,
     -29,   189,   191,   203,   205,   -68,   -81,   337,   184,   -81,
     -81,   -81,   -81,   -81,   -81,   -81,   -81,   -32,   -81,   -81,
     -81,   -81,   -81,   -64,   229,   -67,   232,   367,   -65,   565,
     567,   569,   -61,   -81,   -82,   -70,   -81,   368,   -62,   575,
     -81,   398,   -82,   447,   474,   -82,   -82,   -82,   -82,   -82,
     -82,   -82,   -82,   573,   -82,   -82,   -82,   -82,   -82,   489,
     490,   334,   334,   334,   334,   334,   334,   495,   491,   -82,
     524,   537,   -82,   540,   544,   550,   -82,   555,   571,   562,
     635,   639,   570,   576,   175,   -59,   595,   586,   584,   594,
     175,   597,   599,   602,   -58,   175,   608,   609,   589,   590,
     620,   621,   629,   662,   633,   637,   334,   334,   334,   632,
     187,   636,   646,   650,   655,   659,   175,   677,   665,   604,
     580,   679,   583,   623,   624,   625,   626,   627,   628,   666,
     669,   671,   674,   676,   678,   336,   336,   336,   336,   336,
     336,    39,   492,   642,   593,   601,     0,   217,     0,   208,
       0,   236,  -126,     0,   283,   284,   285,   286,   287,     0,
       0,     0,   288,   607,     0,     0,     0,     0,   651,   652,
     653,     0,   289,   619,   290,   291,     0,   292,   293,   294,
     336,   336,   336,     0,     0,     0,   295,     0,     0,   296,
    -126,     0,     0,     0,     0,   335,   335,   335,   335,   335,
     335,   654,     0,     0,   657,   658,     0,   582,   661,     0,
       0,     0,     0,     0,   664,     0,     0,     0,   668,     0,
       0,   670,     0,     0,     0,   673,     0,     0,     0,   592,
       0,     0,     0,     0,     0,   -78,     0,     0,     0,     0,
     335,   335,   335,   -78,     0,     0,   -78,   -78,   -78,   -78,
     -78,   -78,   -78,   -78,     0,   -78,   -78,   -78,   -78,   -78,
       0,     0,     0,     0,     0,     0,     0,   -79,     0,     0,
     -78,     0,     0,   -78,     0,   -79,     0,   -78,   -79,   -79,
     -79,   -79,   -79,   -79,   -79,   -79,     0,   -79,   -79,   -79,
     -79,   -79,     0,     0,     0,     0,     0,     0,     0,   -80,
       0,     0,   -79,     0,     0,   -79,     0,   -80,     0,   -79,
     -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,     0,   -80,
     -80,   -80,   -80,   -80,     0,     0,     0,     0,     0,     0,
       0,   -84,     0,     0,   -80,     0,     0,   -80,     0,   -84,
       0,   -80,   -84,   -84,   -84,   -84,   -84,   -84,   -84,   -84,
       0,   -84,   -84,   -84,   -84,   -84,     0,     0,     0,     0,
       0,     0,     0,   -91,     0,     0,   -84,     0,     0,   -84,
       0,   -91,     0,   -84,   -91,   -91,   -91,   -91,   -91,   -91,
     -91,   -91,     0,   -91,   -91,   -91,   -91,   -91,     0,     0,
       0,     0,     0,     0,     0,   -85,     0,     0,   -91,     0,
       0,   -91,     0,   -85,     0,   -91,   -85,   -85,   -85,   -85,
     -85,   -85,   -85,   -85,     0,   -85,   -85,   -85,   -85,   -85,
       0,     0,     0,     0,     0,     0,     0,   -86,     0,     0,
     -85,     0,     0,   -85,     0,   -86,     0,   -85,   -86,   -86,
     -86,   -86,   -86,   -86,   -86,   -86,     0,   -86,   -86,   -86,
     -86,   -86,     0,     0,     0,     0,     0,     0,     0,   -87,
       0,     0,   -86,     0,     0,   -86,     0,   -87,     0,   -86,
     -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,     0,   -87,
     -87,   -87,   -87,   -87,     0,     0,     0,     0,     0,     0,
       0,   -88,     0,     0,   -87,     0,     0,   -87,     0,   -88,
       0,   -87,   -88,   -88,   -88,   -88,   -88,   -88,   -88,   -88,
       0,   -88,   -88,   -88,   -88,   -88,     0,     0,     0,     0,
       0,     0,     0,   -89,     0,     0,   -88,     0,     0,   -88,
       0,   -89,     0,   -88,   -89,   -89,   -89,   -89,   -89,   -89,
     -89,   -89,     0,   -89,   -89,   -89,   -89,   -89,     0,     0,
       0,     0,     0,     0,     0,   -90,     0,     0,   -89,     0,
       0,   -89,     0,   -90,     0,   -89,   -90,   -90,   -90,   -90,
     -90,   -90,   -90,   -90,     0,   -90,   -90,   -90,   -90,   -90,
       0,     0,     0,     0,     0,     0,     0,   -97,     0,     0,
     -90,     0,     0,   -90,     0,   -97,     0,   -90,   -97,   -97,
     -97,   -97,   -97,   -97,   -97,   -97,     0,   -97,   -97,   -97,
     -97,   -97,     0,     0,     0,     0,     0,     0,     0,  -115,
       0,     0,   -97,     0,     0,   -97,     0,  -115,     0,   -97,
    -115,  -115,  -115,  -115,  -115,  -115,  -115,  -115,     0,  -115,
    -115,  -115,  -115,  -115,     0,     0,     0,     0,     0,     0,
       0,   -98,     0,     0,  -115,     0,     0,  -115,     0,   312,
       0,  -115,   -98,   -98,   -98,   -98,   -98,   -98,   -98,   -98,
       0,   321,   322,   323,   324,   325,     0,     0,     0,     0,
       0,     0,     0,  -116,     0,     0,   -98,     0,     0,   -98,
       0,  -116,     0,   -98,  -116,  -116,  -116,  -116,  -116,  -116,
    -116,  -116,     0,  -116,  -116,  -116,  -116,  -116,     0,     0,
       0,     0,     0,     0,     0,   -99,     0,     0,  -116,     0,
       0,  -116,     0,   312,     0,  -116,   313,   -99,   -99,   -99,
     -99,   -99,   -99,   -99,     0,   321,   322,   323,   324,   325,
       0,     0,     0,     0,     0,     0,     0,  -117,     0,     0,
     -99,     0,     0,   -99,     0,  -117,     0,   -99,  -117,  -117,
    -117,  -117,  -117,  -117,  -117,  -117,     0,  -117,  -117,  -117,
    -117,  -117,     0,     0,     0,     0,     0,     0,     0,  -100,
       0,     0,  -117,     0,     0,  -117,     0,   312,     0,  -117,
     313,   314,  -100,  -100,  -100,  -100,  -100,  -100,     0,   321,
     322,   323,   324,   325,     0,     0,     0,     0,     0,     0,
       0,  -118,     0,     0,  -100,     0,     0,  -100,     0,  -118,
       0,  -100,  -118,  -118,  -118,  -118,  -118,  -118,  -118,  -118,
       0,  -118,  -118,  -118,  -118,  -118,     0,     0,     0,     0,
       0,     0,     0,  -101,     0,     0,  -118,     0,     0,  -118,
       0,   312,     0,  -118,   313,   314,   315,  -101,  -101,  -101,
    -101,  -101,     0,   321,   322,   323,   324,   325,     0,     0,
       0,     0,     0,     0,     0,  -119,     0,     0,  -101,     0,
       0,  -101,     0,  -119,     0,  -101,  -119,  -119,  -119,  -119,
    -119,  -119,  -119,  -119,     0,  -119,  -119,  -119,  -119,  -119,
       0,     0,     0,     0,     0,     0,     0,  -102,     0,     0,
    -119,     0,     0,  -119,     0,   312,     0,  -119,   313,   314,
     315,   316,  -102,  -102,  -102,  -102,     0,   321,   322,   323,
     324,   325,     0,     0,     0,     0,     0,     0,     0,  -120,
       0,     0,  -102,     0,     0,  -102,     0,  -120,     0,  -102,
    -120,  -120,  -120,  -120,  -120,  -120,  -120,  -120,     0,  -120,
    -120,  -120,  -120,  -120,     0,     0,     0,     0,     0,     0,
       0,  -103,     0,     0,  -120,     0,     0,  -120,     0,   312,
       0,  -120,   313,   314,   315,   316,   317,  -103,  -103,  -103,
       0,   321,   322,   323,   324,   325,     0,     0,     0,     0,
       0,     0,     0,  -121,     0,     0,  -103,     0,     0,  -103,
       0,  -121,     0,  -103,  -121,  -121,  -121,  -121,  -121,  -121,
    -121,  -121,     0,  -121,  -121,  -121,  -121,  -121,     0,     0,
       0,     0,     0,     0,     0,  -104,     0,     0,  -121,     0,
       0,  -121,     0,   312,     0,  -121,   313,   314,   315,   316,
     317,   318,  -104,  -104,     0,   321,   322,   323,   324,   325,
       0,     0,     0,     0,     0,     0,     0,  -122,     0,     0,
    -104,     0,     0,  -104,     0,  -122,     0,  -104,  -122,  -122,
    -122,  -122,  -122,  -122,  -122,  -122,     0,  -122,  -122,  -122,
    -122,  -122,     0,     0,     0,     0,     0,     0,     0,  -110,
       0,     0,  -122,     0,     0,  -122,     0,  -110,     0,  -122,
    -110,  -110,  -110,  -110,  -110,  -110,  -110,  -110,     0,  -110,
    -110,  -110,  -110,  -110,     0,     0,     0,     0,     0,     0,
       0,   -92,     0,     0,  -110,     0,     0,  -110,     0,   312,
       0,  -110,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,
       0,   -92,   -92,   -92,   -92,   -92,     0,     0,     0,     0,
       0,     0,     0,  -111,     0,     0,   -92,     0,     0,   -92,
       0,  -111,     0,   -92,  -111,  -111,  -111,  -111,  -111,  -111,
    -111,  -111,     0,  -111,  -111,  -111,  -111,  -111,     0,     0,
       0,     0,     0,     0,     0,   -93,     0,     0,  -111,     0,
       0,  -111,     0,   312,     0,  -111,   -93,   -93,   -93,   -93,
     -93,   -93,   -93,   -93,     0,   -93,   -93,   -93,   -93,   -93,
       0,     0,     0,     0,     0,     0,     0,  -113,     0,     0,
     -93,     0,     0,   -93,     0,  -113,     0,   -93,  -113,  -113,
    -113,  -113,  -113,  -113,  -113,  -113,     0,  -113,  -113,  -113,
    -113,  -113,     0,     0,     0,     0,     0,     0,     0,   -95,
       0,     0,  -113,     0,     0,  -113,     0,   312,     0,  -113,
     -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,     0,   321,
     322,   -95,   -95,   325,     0,     0,     0,     0,     0,     0,
       0,  -114,     0,     0,   -95,     0,     0,   -95,     0,  -114,
       0,   -95,  -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,
       0,  -114,  -114,  -114,  -114,  -114,     0,     0,     0,     0,
       0,     0,     0,   -96,     0,     0,  -114,     0,     0,  -114,
       0,   312,     0,  -114,   -96,   -96,   -96,   -96,   -96,   -96,
     -96,   -96,     0,   321,   322,   -96,   -96,   325,     0,     0,
       0,     0,     0,     0,     0,  -112,     0,     0,   -96,     0,
       0,   -96,     0,  -112,     0,   -96,  -112,  -112,  -112,  -112,
    -112,  -112,  -112,  -112,     0,  -112,  -112,  -112,  -112,  -112,
       0,     0,     0,     0,     0,     0,     0,   -94,     0,     0,
    -112,     0,     0,  -112,     0,   312,     0,  -112,   -94,   -94,
     -94,   -94,   -94,   -94,   -94,   -94,     0,   -94,   -94,   -94,
     -94,   -94,     0,     0,     0,     0,     0,     0,     0,  -123,
       0,     0,   -94,     0,     0,   -94,     0,  -123,     0,   -94,
    -123,  -123,  -123,  -123,  -123,  -123,  -123,  -123,     0,  -123,
    -123,  -123,  -123,  -123,     0,     0,     0,     0,     0,     0,
       0,  -106,     0,     0,  -123,     0,     0,  -123,     0,   312,
       0,  -123,   313,   314,   315,   316,   317,   318,   319,   320,
       0,   321,   322,   323,   324,   325,     0,     0,     0,     0,
       0,     0,     0,  -108,     0,     0,   326,     0,     0,  -106,
       0,  -108,     0,  -106,  -108,  -108,  -108,  -108,  -108,  -108,
    -108,  -108,     0,  -108,  -108,  -108,  -108,  -108,     0,     0,
       0,     0,     0,     0,     0,  -109,     0,     0,  -108,     0,
       0,  -108,     0,  -109,     0,  -108,  -109,  -109,  -109,  -109,
    -109,  -109,  -109,  -109,     0,  -109,  -109,  -109,  -109,  -109,
       0,     0,     0,     0,     0,     0,     0,  -105,     0,     0,
    -109,     0,     0,  -109,     0,   312,     0,  -109,   313,   314,
     315,   316,   317,   318,   319,   320,     0,   321,   322,   323,
     324,   325,     0,     0,     0,     0,     0,     0,     0,  -125,
       0,     0,   326,     0,     0,  -105,     0,  -125,     0,  -105,
    -125,  -125,  -125,  -125,  -125,  -125,  -125,  -125,     0,  -125,
    -125,  -125,  -125,  -125,     0,     0,     0,     0,     0,     0,
       0,  -124,     0,     0,  -125,     0,     0,  -125,     0,  -124,
       0,  -125,  -124,  -124,  -124,  -124,  -124,  -124,  -124,  -124,
       0,  -124,  -124,  -124,  -124,  -124,   -22,   -22,   -22,   -22,
     -22,   -22,     0,     0,   -22,     0,  -124,     0,     0,  -124,
       0,     0,     0,  -124,   -22,     0,   -22,   -22,     0,   -22,
     -22,   -22,   -22,   -22,   -22,   -22,   211,   -22,   -22,     0,
       0,   -22,     0,   -22,   -22,   -22,    -9,    -9,    -9,    -9,
      -9,    -9,     0,     0,    -9,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    -9,     0,    -9,    -9,     0,    -9,
      -9,    -9,    -9,    -9,    -9,    -9,   212,    -9,    -9,     0,
       0,    -9,     0,    -9,    -9,    -9,   -20,   -20,   -20,   -20,
     -20,   -20,     0,     0,   -20,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -20,     0,   -20,   -20,     0,   -20,
     -20,   -20,   -20,   -20,   -20,   -20,   -20,   -20,   -20,     0,
       0,   -20,     0,   -20,   -20,   -20,   -21,   -21,   -21,   -21,
     -21,   -21,     0,     0,   -21,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -21,     0,   -21,   -21,     0,   -21,
     -21,   -21,   -21,   -21,   -21,   -21,   -21,   -21,   -21,     0,
       0,   -21,     0,   -21,   -21,   -21,   -16,   -16,   -16,   -16,
     -16,   -16,     0,     0,   -16,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -16,     0,   -16,   -16,     0,   -16,
     -16,   -16,   -16,   -16,   -16,   -16,   -16,   -16,   -16,     0,
       0,   -16,     0,   -16,   -16,   -16,   -26,   -26,   -26,   -26,
     -26,   -26,     0,     0,   -26,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -26,     0,   -26,   -26,     0,   -26,
     -26,   -26,   -26,   -26,   -26,   -26,   -26,   -26,   -26,     0,
       0,   -26,     0,   -26,   -26,   -26,   -17,   -17,   -17,   -17,
     -17,   -17,     0,     0,   -17,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -17,     0,   -17,   -17,     0,   -17,
     -17,   -17,   -17,   -17,   -17,   -17,   -17,   -17,   -17,     0,
       0,   -17,     0,   -17,   -17,   -17,   -19,   -19,   -19,   -19,
     -19,   -19,     0,     0,   -19,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -19,     0,   -19,   -19,     0,   -19,
     -19,   -19,   -19,   -19,   -19,   -19,   -19,   -19,   -19,     0,
       0,   -19,     0,   -19,   -19,   -19,   -36,   -36,   -36,   -36,
     -36,   -36,     0,     0,   -36,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -36,     0,   -36,   -36,     0,   -36,
     -36,   -36,   -36,   -36,   -36,   -36,   -36,   -36,   -36,     0,
       0,   -36,     0,   -36,   -36,   -36,   -34,   -34,   -34,   -34,
     -34,   -34,     0,     0,   -34,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -34,     0,   -34,   -34,     0,   -34,
     -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,     0,
       0,   -34,     0,   -34,   -34,   -34,   -22,   -22,   -22,   -22,
     -22,   -22,     0,     0,   -22,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -22,     0,   -22,   -22,     0,   -22,
     -22,   -22,   -22,   -22,   -22,   -22,   640,   -22,   -22,     0,
       0,   -22,     0,   -22,   -22,   -22,    -9,    -9,    -9,    -9,
      -9,    -9,     0,     0,    -9,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    -9,     0,    -9,    -9,     0,    -9,
      -9,    -9,    -9,    -9,    -9,    -9,   641,    -9,    -9,     0,
       0,    -9,     0,    -9,    -9,    -9,   -24,   -24,   -24,   -24,
     -24,   -24,     0,     0,   -24,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -24,     0,   -24,   -24,     0,   -24,
     -24,   -24,   -24,   -24,   -24,   -24,   -24,   -24,   -24,     0,
       0,   -24,     0,   -24,   -24,   -24,   -11,   -11,   -11,   -11,
     -11,   -11,     0,     0,   -11,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -11,     0,   -11,   -11,     0,   -11,
     -11,   -11,   -11,   -11,   -11,   -11,   -11,   -11,   -11,     0,
       0,   -11,     0,   -11,   -11,   -11,   -25,   -25,   -25,   -25,
     -25,   -25,     0,     0,   -25,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -25,     0,   -25,   -25,     0,   -25,
     -25,   -25,   -25,   -25,   -25,   -25,   -25,   -25,   -25,     0,
       0,   -25,     0,   -25,   -25,   -25,   -12,   -12,   -12,   -12,
     -12,   -12,     0,     0,   -12,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -12,     0,   -12,   -12,     0,   -12,
     -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,     0,
       0,   -12,     0,   -12,   -12,   -12,   -39,   -39,   -39,   -39,
     -39,   -39,     0,     0,   -39,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -39,     0,   -39,   -39,     0,   -39,
     -39,   -39,   -39,   -39,   -39,   -39,   -39,   -39,   -39,     0,
       0,   -39,     0,   -39,   -39,   -39,   -23,   -23,   -23,   -23,
     -23,   -23,     0,     0,   -23,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -23,     0,   -23,   -23,     0,   -23,
     -23,   -23,   -23,   -23,   -23,   -23,   -23,   -23,   -23,     0,
       0,   -23,     0,   -23,   -23,   -23,   -10,   -10,   -10,   -10,
     -10,   -10,     0,     0,   -10,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -10,     0,   -10,   -10,     0,   -10,
     -10,   -10,   -10,   -10,   -10,   -10,   -10,   -10,   -10,     0,
       0,   -10,     0,   -10,   -10,   -10,   -15,   -15,   -15,   -15,
     -15,   -15,     0,     0,   -15,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -15,     0,   -15,   -15,     0,   -15,
     -15,   -15,   -15,   -15,   -15,   -15,   -15,   -15,   -15,     0,
       0,   -15,     0,   -15,   -15,   -15,   -47,   -47,   -47,   -47,
     -47,   -47,     0,     0,   -47,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -47,     0,   -47,   -47,     0,   -47,
     -47,   -47,   -47,   -47,   -47,   -47,   -47,   -47,   -47,     0,
       0,   -47,     0,   -47,   -47,   -47,   -45,   -45,   -45,   -45,
     -45,   -45,     0,     0,   -45,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -45,     0,   -45,   -45,     0,   -45,
     -45,   -45,   -45,   -45,   -45,   -45,   -45,   -45,   -45,     0,
       0,   -45,     0,   -45,   -45,   -45,   -49,   -49,   -49,   -49,
     -49,   -49,     0,     0,   -49,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -49,     0,   -49,   -49,     0,   -49,
     -49,   -49,   -49,   -49,   -49,   -49,   -49,   -49,   -49,     0,
       0,   -49,     0,   -49,   -49,   -49,   -43,   -43,   -43,   -43,
     -43,   -43,     0,     0,   -43,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -43,     0,   -43,   -43,     0,   -43,
     -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,     0,
       0,   -43,     0,   -43,   -43,   -43,   -46,   -46,   -46,   -46,
     -46,   -46,     0,     0,   -46,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -46,     0,   -46,   -46,     0,   -46,
     -46,   -46,   -46,   -46,   -46,   -46,     0,   -46,   -46,     0,
       0,   -46,     0,   -46,   -46,   -46,    58,    59,    60,    61,
      62,   239,     0,     0,    63,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    64,     0,    65,    66,     0,    67,
      68,    69,    70,    71,    72,    73,     0,    74,    75,     0,
       0,    76,     0,    77,   -18,   -27,   -44,   -44,   -44,   -44,
     -44,   -44,     0,     0,   -44,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -44,     0,   -44,   -44,     0,   -44,
     -44,   -44,   -44,   -44,   -44,   -44,     0,   -44,   -44,     0,
       0,   -44,     0,   -44,   -44,   -44,   -20,   -20,   -20,   -20,
     -20,   -20,     0,     0,   -20,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -20,     0,   -20,   -20,     0,   -20,
     -20,   -20,   -20,   -20,   -20,   -20,     0,   -20,   -20,     0,
       0,   -20,     0,   -20,   -20,   -20,   -28,   -28,   -28,   -28,
     -28,   -28,     0,     0,   -28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -28,     0,   -28,   -28,     0,   -28,
     -28,   -28,   -28,   -28,   -28,   -28,     0,   -28,   -28,     0,
       0,   -28,     0,   -28,   -28,   -28,   -21,   -21,   -21,   -21,
     -21,   -21,     0,     0,   -21,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -21,     0,   -21,   -21,     0,   -21,
     -21,   -21,   -21,   -21,   -21,   -21,     0,   -21,   -21,     0,
       0,   -21,     0,   -21,   -21,   -21,   -48,   -48,   -48,   -48,
     -48,   -48,     0,     0,   -48,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -48,     0,   -48,   -48,     0,   -48,
     -48,   -48,   -48,   -48,   -48,   -48,     0,   -48,   -48,     0,
       0,   -48,     0,   -48,   -48,   -48,    58,    59,    60,    61,
      62,   239,     0,     0,    63,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    64,     0,    65,    66,     0,    67,
      68,    69,    70,    71,    72,    73,     0,    74,    75,     0,
       0,    76,     0,    77,   -18,   -30,   -16,   -16,   -16,   -16,
     -16,   -16,     0,     0,   -16,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -16,     0,   -16,   -16,     0,   -16,
     -16,   -16,   -16,   -16,   -16,   -16,     0,   -16,   -16,     0,
       0,   -16,     0,   -16,   -16,   -16,   -26,   -26,   -26,   -26,
     -26,   -26,     0,     0,   -26,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -26,     0,   -26,   -26,     0,   -26,
     -26,   -26,   -26,   -26,   -26,   -26,     0,   -26,   -26,     0,
       0,   -26,     0,   -26,   -26,   -26,   -17,   -17,   -17,   -17,
     -17,   -17,     0,     0,   -17,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -17,     0,   -17,   -17,     0,   -17,
     -17,   -17,   -17,   -17,   -17,   -17,     0,   -17,   -17,     0,
       0,   -17,     0,   -17,   -17,   -17,   -31,   -31,   -31,   -31,
     -31,   -31,     0,     0,   -31,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -31,     0,   -31,   -31,     0,   -31,
     -31,   -31,   -31,   -31,   -31,   -31,     0,   -31,   -31,     0,
       0,   -31,     0,   -31,   -31,   -31,   -19,   -19,   -19,   -19,
     -19,   -19,     0,     0,   -19,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -19,     0,   -19,   -19,     0,   -19,
     -19,   -19,   -19,   -19,   -19,   -19,     0,   -19,   -19,     0,
       0,   -19,     0,   -19,   -19,   -19,   -24,   -24,   -24,   -24,
     -24,   -24,     0,     0,   -24,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -24,     0,   -24,   -24,     0,   -24,
     -24,   -24,   -24,   -24,   -24,   -24,     0,   -24,   -24,     0,
       0,   -24,     0,   -24,   -24,   -24,   -11,   -11,   -11,   -11,
     -11,   -11,     0,     0,   -11,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -11,     0,   -11,   -11,     0,   -11,
     -11,   -11,   -11,   -11,   -11,   -11,     0,   -11,   -11,     0,
       0,   -11,     0,   -11,   -11,   -11,   -25,   -25,   -25,   -25,
     -25,   -25,     0,     0,   -25,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -25,     0,   -25,   -25,     0,   -25,
     -25,   -25,   -25,   -25,   -25,   -25,     0,   -25,   -25,     0,
       0,   -25,     0,   -25,   -25,   -25,   -12,   -12,   -12,   -12,
     -12,   -12,     0,     0,   -12,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -12,     0,   -12,   -12,     0,   -12,
     -12,   -12,   -12,   -12,   -12,   -12,     0,   -12,   -12,     0,
       0,   -12,     0,   -12,   -12,   -12,   -23,   -23,   -23,   -23,
     -23,   -23,     0,     0,   -23,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -23,     0,   -23,   -23,     0,   -23,
     -23,   -23,   -23,   -23,   -23,   -23,     0,   -23,   -23,     0,
       0,   -23,     0,   -23,   -23,   -23,   -10,   -10,   -10,   -10,
     -10,   -10,     0,     0,   -10,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -10,     0,   -10,   -10,     0,   -10,
     -10,   -10,   -10,   -10,   -10,   -10,     0,   -10,   -10,     0,
       0,   -10,     0,   -10,   -10,   -10,   -15,   -15,   -15,   -15,
     -15,   -15,     0,     0,   -15,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -15,     0,   -15,   -15,     0,   -15,
     -15,   -15,   -15,   -15,   -15,   -15,     0,   -15,   -15,     0,
       0,   -15,     0,   -15,   -15,   -15,   -36,   -36,   -36,   -36,
     -36,   -36,     0,     0,   -36,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -36,     0,   -36,   -36,     0,   -36,
     -36,   -36,   -36,   -36,   -36,   -36,     0,   -36,   -36,     0,
       0,   -36,     0,   -36,   -36,   -36,   -34,   -34,   -34,   -34,
     -34,   -34,     0,     0,   -34,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -34,     0,   -34,   -34,     0,   -34,
     -34,   -34,   -34,   -34,   -34,   -34,     0,   -34,   -34,     0,
       0,   -34,     0,   -34,   -34,   -34,   -39,   -39,   -39,   -39,
     -39,   -39,     0,     0,   -39,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -39,     0,   -39,   -39,     0,   -39,
     -39,   -39,   -39,   -39,   -39,   -39,     0,   -39,   -39,     0,
       0,   -39,     0,   -39,   -39,   -39,   -47,   -47,   -47,   -47,
     -47,   -47,     0,     0,   -47,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -47,     0,   -47,   -47,     0,   -47,
     -47,   -47,   -47,   -47,   -47,   -47,     0,   -47,   -47,     0,
       0,   -47,     0,   -47,   -47,   -47,   -45,   -45,   -45,   -45,
     -45,   -45,     0,     0,   -45,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -45,     0,   -45,   -45,     0,   -45,
     -45,   -45,   -45,   -45,   -45,   -45,     0,   -45,   -45,     0,
       0,   -45,     0,   -45,   -45,   -45,   -49,   -49,   -49,   -49,
     -49,   -49,     0,     0,   -49,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -49,     0,   -49,   -49,     0,   -49,
     -49,   -49,   -49,   -49,   -49,   -49,     0,   -49,   -49,     0,
       0,   -49,     0,   -49,   -49,   -49,   -43,   -43,   -43,   -43,
     -43,   -43,     0,     0,   -43,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -43,     0,   -43,   -43,     0,   -43,
     -43,   -43,   -43,   -43,   -43,   -43,     0,   -43,   -43,     0,
       0,   -43,     0,   -43,   -43,   -43,    58,    59,    60,    61,
      62,   327,     0,     0,    63,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    64,     0,    65,    66,     0,    67,
      68,    69,   328,   329,   330,   331,     0,   332,    75,     0,
       0,    76,     0,   333,   -18,    58,    59,    60,    61,    62,
     239,     0,     0,    63,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    64,     0,    65,    66,     0,    67,    68,
      69,    70,    71,    72,    73,     0,    74,    75,     0,     0,
      76,     0,    77,   -18,   -14,   -14,   -14,   -14,   -14,   -14,
       0,     0,   -14,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -14,     0,   -14,   -14,     0,   -14,   -14,   -14,
     -14,   -14,   -14,   -14,     0,   -14,   -14,     0,     0,   -14,
       0,   -14,   -14,    58,    59,    60,    61,    62,   183,     0,
       0,    63,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    64,     0,    65,    66,     0,    67,    68,    69,     0,
       0,     0,     0,     0,     0,    75,     0,     0,    76,   102,
     184,    58,    59,    60,    61,    62,     0,     0,     0,    63,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    64,
       0,    65,    66,     0,    67,    68,    69,     0,     0,     0,
       0,     0,     0,    75,     0,   128,    76,    58,    59,    60,
      61,    62,     0,     0,     0,    63,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    64,     0,    65,    66,     0,
      67,    68,    69,     0,     0,     0,     0,     0,     0,    75,
       0,   132,    76,   240,   241,   242,   243,   244,     0,     0,
       0,   245,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   246,     0,   247,   248,     0,   249,   250,   251,     0,
       0,     0,     0,     0,     0,   252,     0,   134,   253,   240,
     241,   242,   243,   244,     0,     0,     0,   245,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   246,     0,   247,
     248,     0,   249,   250,   251,     0,     0,     0,     0,     0,
       0,   252,     0,   136,   253,   240,   241,   242,   243,   244,
       0,     0,     0,   245,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   246,     0,   247,   248,     0,   249,   250,
     251,     0,     0,     0,     0,     0,     0,   252,     0,   146,
     253,    58,    59,    60,    61,    62,     0,     0,     0,    63,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    64,
       0,    65,    66,     0,    67,    68,    69,     0,     0,     0,
       0,     0,     0,    75,     0,   148,    76,    58,    59,    60,
      61,    62,     0,     0,     0,    63,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    64,     0,    65,    66,     0,
      67,    68,    69,     0,     0,     0,     0,     0,     0,    75,
       0,   150,    76,    58,    59,    60,    61,    62,     0,     0,
       0,    63,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    64,     0,    65,    66,     0,    67,    68,    69,     0,
       0,     0,     0,     0,     0,    75,     0,   152,    76,    58,
      59,    60,    61,    62,     0,     0,     0,    63,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    64,     0,    65,
      66,     0,    67,    68,    69,     0,     0,     0,     0,     0,
       0,    75,     0,   154,    76,    58,    59,    60,    61,    62,
       0,     0,     0,    63,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    64,     0,    65,    66,     0,    67,    68,
      69,     0,     0,     0,     0,     0,     0,    75,     0,   156,
      76,    58,    59,    60,    61,    62,     0,     0,     0,    63,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    64,
       0,    65,    66,     0,    67,    68,    69,     0,     0,     0,
       0,     0,     0,    75,     0,   158,    76,    58,    59,    60,
      61,    62,     0,     0,     0,    63,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    64,     0,    65,    66,     0,
      67,    68,    69,     0,     0,     0,     0,     0,     0,    75,
       0,   161,    76,    58,    59,    60,    61,    62,     0,     0,
       0,    63,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    64,     0,    65,    66,     0,    67,    68,    69,     0,
       0,     0,     0,     0,     0,    75,     0,   163,    76,    58,
      59,    60,    61,    62,     0,     0,     0,    63,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    64,     0,    65,
      66,     0,    67,    68,    69,     0,     0,     0,     0,     0,
       0,    75,     0,   165,    76,    58,    59,    60,    61,    62,
       0,     0,     0,    63,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    64,     0,    65,    66,     0,    67,    68,
      69,     0,     0,     0,     0,     0,     0,    75,     0,   167,
      76,    58,    59,    60,    61,    62,     0,     0,     0,    63,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    64,
       0,    65,    66,     0,    67,    68,    69,     0,     0,     0,
       0,     0,     0,    75,     0,   169,    76,    58,    59,    60,
      61,    62,     0,     0,     0,    63,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    64,     0,    65,    66,     0,
      67,    68,    69,    58,    59,    60,    61,    62,     0,    75,
       0,    63,    76,     0,     0,     0,     0,     0,     0,     0,
       0,    64,     0,    65,    66,     0,    67,    68,    69,     0,
       0,     0,     0,     0,     0,    75,     0,     0,    76,   384,
     -72,   240,   241,   242,   243,   244,     0,     0,     0,   245,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   246,
       0,   247,   248,     0,   249,   250,   251,     0,     0,     0,
       0,     0,     0,   252,     0,   386,   253,   240,   241,   242,
     243,   244,     0,     0,     0,   245,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   246,     0,   247,   248,     0,
     249,   250,   251,     0,     0,     0,     0,     0,     0,   252,
       0,   388,   253,   240,   241,   242,   243,   244,     0,     0,
       0,   245,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   246,     0,   247,   248,     0,   249,   250,   251,     0,
       0,     0,     0,     0,     0,   252,     0,   390,   253,   240,
     241,   242,   243,   244,     0,     0,     0,   245,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   246,     0,   247,
     248,     0,   249,   250,   251,     0,     0,     0,     0,     0,
       0,   252,     0,   392,   253,   240,   241,   242,   243,   244,
       0,     0,     0,   245,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   246,     0,   247,   248,     0,   249,   250,
     251,     0,     0,     0,     0,     0,     0,   252,     0,   394,
     253,   240,   241,   242,   243,   244,     0,     0,     0,   245,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   246,
       0,   247,   248,     0,   249,   250,   251,     0,     0,     0,
       0,     0,     0,   252,     0,   396,   253,   240,   241,   242,
     243,   244,     0,     0,     0,   245,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   246,     0,   247,   248,     0,
     249,   250,   251,     0,     0,     0,     0,     0,     0,   252,
       0,   399,   253,   240,   241,   242,   243,   244,     0,     0,
       0,   245,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   246,     0,   247,   248,     0,   249,   250,   251,     0,
       0,     0,     0,     0,     0,   252,     0,   401,   253,   240,
     241,   242,   243,   244,     0,     0,     0,   245,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   246,     0,   247,
     248,     0,   249,   250,   251,     0,     0,     0,     0,     0,
       0,   252,     0,   403,   253,   240,   241,   242,   243,   244,
       0,     0,     0,   245,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   246,     0,   247,   248,     0,   249,   250,
     251,     0,     0,     0,     0,     0,     0,   252,     0,   405,
     253,   240,   241,   242,   243,   244,     0,     0,     0,   245,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   246,
       0,   247,   248,     0,   249,   250,   251,     0,     0,     0,
       0,     0,     0,   252,     0,   407,   253,   240,   241,   242,
     243,   244,     0,     0,     0,   245,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   246,     0,   247,   248,     0,
     249,   250,   251,     0,     0,     0,     0,     0,     0,   252,
       0,   433,   253,   269,   270,   271,   272,   273,     0,     0,
       0,   274,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   275,     0,   276,   277,     0,   278,   279,   280,     0,
       0,     0,     0,     0,     0,   281,     0,   435,   282,   269,
     270,   271,   272,   273,     0,     0,     0,   274,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   275,     0,   276,
     277,     0,   278,   279,   280,     0,     0,     0,     0,     0,
       0,   281,     0,   437,   282,   269,   270,   271,   272,   273,
       0,     0,     0,   274,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   275,     0,   276,   277,     0,   278,   279,
     280,     0,     0,     0,     0,     0,     0,   281,     0,   439,
     282,   269,   270,   271,   272,   273,     0,     0,     0,   274,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   275,
       0,   276,   277,     0,   278,   279,   280,     0,     0,     0,
       0,     0,     0,   281,     0,   441,   282,   269,   270,   271,
     272,   273,     0,     0,     0,   274,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   275,     0,   276,   277,     0,
     278,   279,   280,     0,     0,     0,     0,     0,     0,   281,
       0,   443,   282,   269,   270,   271,   272,   273,     0,     0,
       0,   274,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   275,     0,   276,   277,     0,   278,   279,   280,     0,
       0,     0,     0,     0,     0,   281,     0,   445,   282,   269,
     270,   271,   272,   273,     0,     0,     0,   274,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   275,     0,   276,
     277,     0,   278,   279,   280,     0,     0,     0,     0,     0,
       0,   281,     0,   448,   282,   269,   270,   271,   272,   273,
       0,     0,     0,   274,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   275,     0,   276,   277,     0,   278,   279,
     280,     0,     0,     0,     0,     0,     0,   281,     0,   450,
     282,   269,   270,   271,   272,   273,     0,     0,     0,   274,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   275,
       0,   276,   277,     0,   278,   279,   280,     0,     0,     0,
       0,     0,     0,   281,     0,   452,   282,   269,   270,   271,
     272,   273,     0,     0,     0,   274,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   275,     0,   276,   277,     0,
     278,   279,   280,     0,     0,     0,     0,     0,     0,   281,
       0,   454,   282,   269,   270,   271,   272,   273,     0,     0,
       0,   274,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   275,     0,   276,   277,     0,   278,   279,   280,     0,
       0,     0,     0,     0,     0,   281,     0,   456,   282,   269,
     270,   271,   272,   273,     0,     0,     0,   274,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   275,     0,   276,
     277,     0,   278,   279,   280,     0,     0,     0,     0,     0,
       0,   281,     0,   460,   282,   283,   284,   285,   286,   287,
       0,     0,     0,   288,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   289,     0,   290,   291,     0,   292,   293,
     294,     0,     0,     0,     0,     0,     0,   295,     0,   462,
     296,   283,   284,   285,   286,   287,     0,     0,     0,   288,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   289,
       0,   290,   291,     0,   292,   293,   294,     0,     0,     0,
       0,     0,     0,   295,     0,   464,   296,   283,   284,   285,
     286,   287,     0,     0,     0,   288,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   289,     0,   290,   291,     0,
     292,   293,   294,     0,     0,     0,     0,     0,     0,   295,
       0,   466,   296,   283,   284,   285,   286,   287,     0,     0,
       0,   288,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   289,     0,   290,   291,     0,   292,   293,   294,     0,
       0,     0,     0,     0,     0,   295,     0,   468,   296,   283,
     284,   285,   286,   287,     0,     0,     0,   288,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   289,     0,   290,
     291,     0,   292,   293,   294,     0,     0,     0,     0,     0,
       0,   295,     0,   470,   296,   283,   284,   285,   286,   287,
       0,     0,     0,   288,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   289,     0,   290,   291,     0,   292,   293,
     294,     0,     0,     0,     0,     0,     0,   295,     0,   472,
     296,   283,   284,   285,   286,   287,     0,     0,     0,   288,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   289,
       0,   290,   291,     0,   292,   293,   294,     0,     0,     0,
       0,     0,     0,   295,     0,   475,   296,   283,   284,   285,
     286,   287,     0,     0,     0,   288,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   289,     0,   290,   291,     0,
     292,   293,   294,     0,     0,     0,     0,     0,     0,   295,
       0,   477,   296,   283,   284,   285,   286,   287,     0,     0,
       0,   288,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   289,     0,   290,   291,     0,   292,   293,   294,     0,
       0,     0,     0,     0,     0,   295,     0,   479,   296,   283,
     284,   285,   286,   287,     0,     0,     0,   288,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   289,     0,   290,
     291,     0,   292,   293,   294,     0,     0,     0,     0,     0,
       0,   295,     0,   481,   296,   283,   284,   285,   286,   287,
       0,     0,     0,   288,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   289,     0,   290,   291,     0,   292,   293,
     294,     0,     0,     0,     0,     0,     0,   295,     0,   483,
     296,   283,   284,   285,   286,   287,     0,     0,     0,   288,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   289,
       0,   290,   291,     0,   292,   293,   294,     0,     0,     0,
       0,     0,     0,   295,     0,   493,   296,    58,    59,    60,
      61,    62,     0,     0,     0,    63,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    64,     0,    65,    66,     0,
      67,    68,    69,     0,     0,     0,     0,     0,     0,    75,
       0,   510,    76,   338,   339,   340,   341,   342,     0,     0,
       0,   343,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   344,     0,   345,   346,     0,   347,   348,   349,     0,
       0,     0,     0,     0,     0,   350,     0,   512,   351,   338,
     339,   340,   341,   342,     0,     0,     0,   343,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   344,     0,   345,
     346,     0,   347,   348,   349,     0,     0,     0,     0,     0,
       0,   350,     0,   514,   351,   338,   339,   340,   341,   342,
       0,     0,     0,   343,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   344,     0,   345,   346,     0,   347,   348,
     349,     0,     0,     0,     0,     0,     0,   350,     0,   516,
     351,   338,   339,   340,   341,   342,     0,     0,     0,   343,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   344,
       0,   345,   346,     0,   347,   348,   349,     0,     0,     0,
       0,     0,     0,   350,     0,   518,   351,   338,   339,   340,
     341,   342,     0,     0,     0,   343,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   344,     0,   345,   346,     0,
     347,   348,   349,     0,     0,     0,     0,     0,     0,   350,
       0,   520,   351,   338,   339,   340,   341,   342,     0,     0,
       0,   343,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   344,     0,   345,   346,     0,   347,   348,   349,     0,
       0,     0,     0,     0,     0,   350,     0,   522,   351,   338,
     339,   340,   341,   342,     0,     0,     0,   343,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   344,     0,   345,
     346,     0,   347,   348,   349,     0,     0,     0,     0,     0,
       0,   350,     0,   525,   351,   338,   339,   340,   341,   342,
       0,     0,     0,   343,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   344,     0,   345,   346,     0,   347,   348,
     349,     0,     0,     0,     0,     0,     0,   350,     0,   527,
     351,   338,   339,   340,   341,   342,     0,     0,     0,   343,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   344,
       0,   345,   346,     0,   347,   348,   349,     0,     0,     0,
       0,     0,     0,   350,     0,   529,   351,   338,   339,   340,
     341,   342,     0,     0,     0,   343,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   344,     0,   345,   346,     0,
     347,   348,   349,     0,     0,     0,     0,     0,     0,   350,
       0,   531,   351,   338,   339,   340,   341,   342,     0,     0,
       0,   343,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   344,     0,   345,   346,     0,   347,   348,   349,     0,
       0,     0,     0,     0,     0,   350,     0,   533,   351,   338,
     339,   340,   341,   342,     0,     0,     0,   343,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   344,     0,   345,
     346,     0,   347,   348,   349,     0,     0,     0,     0,     0,
       0,   350,     0,   542,   351,   240,   241,   242,   243,   244,
       0,     0,     0,   245,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   246,     0,   247,   248,     0,   249,   250,
     251,     0,     0,     0,     0,     0,     0,   252,     0,   548,
     253,   269,   270,   271,   272,   273,     0,     0,     0,   274,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   275,
       0,   276,   277,     0,   278,   279,   280,     0,     0,     0,
       0,     0,     0,   281,     0,   553,   282,   283,   284,   285,
     286,   287,     0,     0,     0,   288,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   289,     0,   290,   291,     0,
     292,   293,   294,     0,     0,     0,     0,     0,     0,   295,
       0,   564,   296,   240,   241,   242,   243,   244,     0,     0,
       0,   245,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   246,     0,   247,   248,     0,   249,   250,   251,     0,
       0,     0,     0,     0,     0,   252,     0,   566,   253,   240,
     241,   242,   243,   244,     0,     0,     0,   245,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   246,     0,   247,
     248,     0,   249,   250,   251,     0,     0,     0,     0,     0,
       0,   252,     0,   568,   253,   240,   241,   242,   243,   244,
       0,     0,     0,   245,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   246,     0,   247,   248,     0,   249,   250,
     251,     0,     0,     0,     0,     0,     0,   252,     0,   574,
     253,   338,   339,   340,   341,   342,     0,     0,     0,   343,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   344,
       0,   345,   346,     0,   347,   348,   349,   240,   241,   242,
     243,   244,     0,   350,     0,   245,   351,     0,     0,     0,
       0,     0,     0,     0,     0,   246,     0,   247,   248,     0,
     249,   250,   251,    58,    59,    60,    61,    62,     0,   252,
       0,    63,   253,   -72,     0,     0,     0,     0,     0,     0,
       0,    64,     0,    65,    66,     0,    67,    68,    69,   240,
     241,   242,   243,   244,     0,    75,     0,   245,    76,     0,
       0,     0,     0,     0,     0,     0,     0,   246,     0,   247,
     248,     0,   249,   250,   251,   269,   270,   271,   272,   273,
       0,   252,     0,   274,   253,     0,     0,     0,     0,     0,
       0,     0,     0,   275,     0,   276,   277,     0,   278,   279,
     280,   283,   284,   285,   286,   287,     0,   281,     0,   288,
     282,     0,     0,     0,     0,     0,     0,     0,     0,   289,
       0,   290,   291,     0,   292,   293,   294,   338,   339,   340,
     341,   342,     0,   295,     0,   343,   296,     0,     0,     0,
       0,     0,     0,     0,     0,   344,     0,   345,   346,     0,
     347,   348,   349,     0,     0,     0,     0,     0,     0,   350,
     -83,   498,   351,   -83,   -83,   -83,   -83,   -83,   -83,   -83,
     -83,   499,   -83,   -83,   -83,   -83,   -83,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -83,     0,  -107,
       0,   -83,   352,     0,   -83,   353,   354,   355,   356,   357,
     358,   359,   360,     0,   361,   362,   363,   364,   365,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   366,
       0,     0,     0,   -60,   352,     0,   -60,   353,   354,   355,
     356,   357,   358,   359,   360,     0,   361,   362,   363,   364,
     365,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   366,     0,     0,     0,   -69,   -81,     0,   226,   -81,
     -81,   -81,   -81,   -81,   -81,   -81,   -81,     0,   -81,   -81,
     -81,   -81,   -81,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -81,     0,     0,     0,   -81,   -82,     0,
     -81,   -82,   -82,   -82,   -82,   -82,   -82,   -82,   -82,     0,
     -82,   -82,   -82,   -82,   -82,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -82,     0,     0,     0,   -82,
     -78,     0,   -82,   -78,   -78,   -78,   -78,   -78,   -78,   -78,
     -78,     0,   -78,   -78,   -78,   -78,   -78,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -78,     0,     0,
       0,   -78,   -79,     0,   -78,   -79,   -79,   -79,   -79,   -79,
     -79,   -79,   -79,     0,   -79,   -79,   -79,   -79,   -79,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -79,
       0,     0,     0,   -79,   -80,     0,   -79,   -80,   -80,   -80,
     -80,   -80,   -80,   -80,   -80,     0,   -80,   -80,   -80,   -80,
     -80,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -80,     0,     0,     0,   -80,   -84,     0,   -80,   -84,
     -84,   -84,   -84,   -84,   -84,   -84,   -84,     0,   -84,   -84,
     -84,   -84,   -84,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -84,     0,     0,     0,   -84,   -91,     0,
     -84,   -91,   -91,   -91,   -91,   -91,   -91,   -91,   -91,     0,
     -91,   -91,   -91,   -91,   -91,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -91,     0,     0,     0,   -91,
     -85,     0,   -91,   -85,   -85,   -85,   -85,   -85,   -85,   -85,
     -85,     0,   -85,   -85,   -85,   -85,   -85,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -85,     0,     0,
       0,   -85,   -86,     0,   -85,   -86,   -86,   -86,   -86,   -86,
     -86,   -86,   -86,     0,   -86,   -86,   -86,   -86,   -86,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -86,
       0,     0,     0,   -86,   -87,     0,   -86,   -87,   -87,   -87,
     -87,   -87,   -87,   -87,   -87,     0,   -87,   -87,   -87,   -87,
     -87,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -87,     0,     0,     0,   -87,   -88,     0,   -87,   -88,
     -88,   -88,   -88,   -88,   -88,   -88,   -88,     0,   -88,   -88,
     -88,   -88,   -88,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -88,     0,     0,     0,   -88,   -89,     0,
     -88,   -89,   -89,   -89,   -89,   -89,   -89,   -89,   -89,     0,
     -89,   -89,   -89,   -89,   -89,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -89,     0,     0,     0,   -89,
     -90,     0,   -89,   -90,   -90,   -90,   -90,   -90,   -90,   -90,
     -90,     0,   -90,   -90,   -90,   -90,   -90,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -90,     0,     0,
       0,   -90,   -97,     0,   -90,   -97,   -97,   -97,   -97,   -97,
     -97,   -97,   -97,     0,   -97,   -97,   -97,   -97,   -97,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -97,
       0,     0,     0,   -97,  -115,     0,   -97,  -115,  -115,  -115,
    -115,  -115,  -115,  -115,  -115,     0,  -115,  -115,  -115,  -115,
    -115,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -115,     0,     0,     0,  -115,   352,     0,  -115,   -98,
     -98,   -98,   -98,   -98,   -98,   -98,   -98,     0,   361,   362,
     363,   364,   365,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -98,     0,     0,     0,   -98,  -116,     0,
     -98,  -116,  -116,  -116,  -116,  -116,  -116,  -116,  -116,     0,
    -116,  -116,  -116,  -116,  -116,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -116,     0,     0,     0,  -116,
     352,     0,  -116,   353,   -99,   -99,   -99,   -99,   -99,   -99,
     -99,     0,   361,   362,   363,   364,   365,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -99,     0,     0,
       0,   -99,  -117,     0,   -99,  -117,  -117,  -117,  -117,  -117,
    -117,  -117,  -117,     0,  -117,  -117,  -117,  -117,  -117,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -117,
       0,     0,     0,  -117,   352,     0,  -117,   353,   354,  -100,
    -100,  -100,  -100,  -100,  -100,     0,   361,   362,   363,   364,
     365,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -100,     0,     0,     0,  -100,  -118,     0,  -100,  -118,
    -118,  -118,  -118,  -118,  -118,  -118,  -118,     0,  -118,  -118,
    -118,  -118,  -118,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -118,     0,     0,     0,  -118,   352,     0,
    -118,   353,   354,   355,  -101,  -101,  -101,  -101,  -101,     0,
     361,   362,   363,   364,   365,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -101,     0,     0,     0,  -101,
    -119,     0,  -101,  -119,  -119,  -119,  -119,  -119,  -119,  -119,
    -119,     0,  -119,  -119,  -119,  -119,  -119,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -119,     0,     0,
       0,  -119,   352,     0,  -119,   353,   354,   355,   356,  -102,
    -102,  -102,  -102,     0,   361,   362,   363,   364,   365,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -102,
       0,     0,     0,  -102,  -120,     0,  -102,  -120,  -120,  -120,
    -120,  -120,  -120,  -120,  -120,     0,  -120,  -120,  -120,  -120,
    -120,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -120,     0,     0,     0,  -120,   352,     0,  -120,   353,
     354,   355,   356,   357,  -103,  -103,  -103,     0,   361,   362,
     363,   364,   365,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -103,     0,     0,     0,  -103,  -121,     0,
    -103,  -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,     0,
    -121,  -121,  -121,  -121,  -121,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -121,     0,     0,     0,  -121,
     352,     0,  -121,   353,   354,   355,   356,   357,   358,  -104,
    -104,     0,   361,   362,   363,   364,   365,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -104,     0,     0,
       0,  -104,  -122,     0,  -104,  -122,  -122,  -122,  -122,  -122,
    -122,  -122,  -122,     0,  -122,  -122,  -122,  -122,  -122,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -122,
       0,     0,     0,  -122,  -110,     0,  -122,  -110,  -110,  -110,
    -110,  -110,  -110,  -110,  -110,     0,  -110,  -110,  -110,  -110,
    -110,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -110,     0,     0,     0,  -110,   352,     0,  -110,   -92,
     -92,   -92,   -92,   -92,   -92,   -92,   -92,     0,   -92,   -92,
     -92,   -92,   -92,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -92,     0,     0,     0,   -92,  -111,     0,
     -92,  -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,     0,
    -111,  -111,  -111,  -111,  -111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -111,     0,     0,     0,  -111,
     352,     0,  -111,   -93,   -93,   -93,   -93,   -93,   -93,   -93,
     -93,     0,   -93,   -93,   -93,   -93,   -93,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -93,     0,     0,
       0,   -93,  -113,     0,   -93,  -113,  -113,  -113,  -113,  -113,
    -113,  -113,  -113,     0,  -113,  -113,  -113,  -113,  -113,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -113,
       0,     0,     0,  -113,   352,     0,  -113,   -95,   -95,   -95,
     -95,   -95,   -95,   -95,   -95,     0,   361,   362,   -95,   -95,
     365,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -95,     0,     0,     0,   -95,  -114,     0,   -95,  -114,
    -114,  -114,  -114,  -114,  -114,  -114,  -114,     0,  -114,  -114,
    -114,  -114,  -114,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -114,     0,     0,     0,  -114,   352,     0,
    -114,   -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,     0,
     361,   362,   -96,   -96,   365,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -96,     0,     0,     0,   -96,
    -112,     0,   -96,  -112,  -112,  -112,  -112,  -112,  -112,  -112,
    -112,     0,  -112,  -112,  -112,  -112,  -112,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -112,     0,     0,
       0,  -112,   352,     0,  -112,   -94,   -94,   -94,   -94,   -94,
     -94,   -94,   -94,     0,   -94,   -94,   -94,   -94,   -94,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -94,
       0,     0,     0,   -94,  -123,     0,   -94,  -123,  -123,  -123,
    -123,  -123,  -123,  -123,  -123,     0,  -123,  -123,  -123,  -123,
    -123,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -123,     0,     0,     0,  -123,   352,     0,  -123,   353,
     354,   355,   356,   357,   358,   359,   360,     0,   361,   362,
     363,   364,   365,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   366,     0,     0,     0,  -106,  -108,     0,
    -106,  -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,     0,
    -108,  -108,  -108,  -108,  -108,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -108,     0,     0,     0,  -108,
    -109,     0,  -108,  -109,  -109,  -109,  -109,  -109,  -109,  -109,
    -109,     0,  -109,  -109,  -109,  -109,  -109,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -109,     0,     0,
       0,  -109,   352,     0,  -109,   353,   354,   355,   356,   357,
     358,   359,   360,     0,   361,   362,   363,   364,   365,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   366,
       0,     0,     0,  -105,  -125,     0,  -105,  -125,  -125,  -125,
    -125,  -125,  -125,  -125,  -125,     0,  -125,  -125,  -125,  -125,
    -125,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -125,     0,     0,     0,  -125,  -124,     0,  -125,  -124,
    -124,  -124,  -124,  -124,  -124,  -124,  -124,     0,  -124,  -124,
    -124,  -124,  -124,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -124,     0,     0,     0,  -124,   -83,    88,
    -124,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,    89,
     -83,   -83,   -83,   -83,   -83,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -83,     0,  -107,   -81,   -83,
       0,   -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,     0,
     -81,   -81,   -81,   -81,   -81,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -81,     0,   -82,     0,   -81,
     -82,   -82,   -82,   -82,   -82,   -82,   -82,   -82,     0,   -82,
     -82,   -82,   -82,   -82,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -82,     0,   -78,     0,   -82,   -78,
     -78,   -78,   -78,   -78,   -78,   -78,   -78,     0,   -78,   -78,
     -78,   -78,   -78,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -78,     0,   -79,     0,   -78,   -79,   -79,
     -79,   -79,   -79,   -79,   -79,   -79,     0,   -79,   -79,   -79,
     -79,   -79,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -79,     0,   -80,     0,   -79,   -80,   -80,   -80,
     -80,   -80,   -80,   -80,   -80,     0,   -80,   -80,   -80,   -80,
     -80,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -80,     0,   108,     0,   -80,   109,   110,   111,   112,
     113,   114,   115,   116,     0,   117,   118,   119,   120,   121,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     122,     0,   -84,     0,   123,   -84,   -84,   -84,   -84,   -84,
     -84,   -84,   -84,     0,   -84,   -84,   -84,   -84,   -84,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -84,
       0,   -91,     0,   -84,   -91,   -91,   -91,   -91,   -91,   -91,
     -91,   -91,     0,   -91,   -91,   -91,   -91,   -91,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -91,     0,
     -85,     0,   -91,   -85,   -85,   -85,   -85,   -85,   -85,   -85,
     -85,     0,   -85,   -85,   -85,   -85,   -85,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -85,     0,   -86,
       0,   -85,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,
       0,   -86,   -86,   -86,   -86,   -86,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -86,     0,   -87,     0,
     -86,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,     0,
     -87,   -87,   -87,   -87,   -87,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -87,     0,   -88,     0,   -87,
     -88,   -88,   -88,   -88,   -88,   -88,   -88,   -88,     0,   -88,
     -88,   -88,   -88,   -88,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -88,     0,   -89,     0,   -88,   -89,
     -89,   -89,   -89,   -89,   -89,   -89,   -89,     0,   -89,   -89,
     -89,   -89,   -89,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -89,     0,   -90,     0,   -89,   -90,   -90,
     -90,   -90,   -90,   -90,   -90,   -90,     0,   -90,   -90,   -90,
     -90,   -90,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -90,     0,   108,     0,   -90,   109,   110,   111,
     112,   113,   114,   115,   116,     0,   117,   118,   119,   120,
     121,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   122,     0,  -123,     0,   140,  -123,  -123,  -123,  -123,
    -123,  -123,  -123,  -123,     0,  -123,  -123,  -123,  -123,  -123,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -123,     0,   108,     0,  -123,   109,   110,   111,   112,   113,
     114,   115,   116,     0,   117,   118,   119,   120,   121,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   122,
       0,  -108,     0,  -106,  -108,  -108,  -108,  -108,  -108,  -108,
    -108,  -108,     0,  -108,  -108,  -108,  -108,  -108,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -108,     0,
    -109,     0,  -108,  -109,  -109,  -109,  -109,  -109,  -109,  -109,
    -109,     0,  -109,  -109,  -109,  -109,  -109,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -109,     0,   -97,
       0,  -109,   -97,   -97,   -97,   -97,   -97,   -97,   -97,   -97,
       0,   -97,   -97,   -97,   -97,   -97,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -97,     0,  -115,     0,
     -97,  -115,  -115,  -115,  -115,  -115,  -115,  -115,  -115,     0,
    -115,  -115,  -115,  -115,  -115,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -115,     0,   108,     0,  -115,
     -98,   -98,   -98,   -98,   -98,   -98,   -98,   -98,     0,   117,
     118,   119,   120,   121,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -98,     0,  -116,     0,   -98,  -116,
    -116,  -116,  -116,  -116,  -116,  -116,  -116,     0,  -116,  -116,
    -116,  -116,  -116,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -116,     0,   108,     0,  -116,   109,   -99,
     -99,   -99,   -99,   -99,   -99,   -99,     0,   117,   118,   119,
     120,   121,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -99,     0,  -117,     0,   -99,  -117,  -117,  -117,
    -117,  -117,  -117,  -117,  -117,     0,  -117,  -117,  -117,  -117,
    -117,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -117,     0,   108,     0,  -117,   109,   110,  -100,  -100,
    -100,  -100,  -100,  -100,     0,   117,   118,   119,   120,   121,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -100,     0,  -118,     0,  -100,  -118,  -118,  -118,  -118,  -118,
    -118,  -118,  -118,     0,  -118,  -118,  -118,  -118,  -118,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -118,
       0,   108,     0,  -118,   109,   110,   111,  -101,  -101,  -101,
    -101,  -101,     0,   117,   118,   119,   120,   121,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -101,     0,
    -119,     0,  -101,  -119,  -119,  -119,  -119,  -119,  -119,  -119,
    -119,     0,  -119,  -119,  -119,  -119,  -119,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -119,     0,   108,
       0,  -119,   109,   110,   111,   112,  -102,  -102,  -102,  -102,
       0,   117,   118,   119,   120,   121,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -102,     0,  -120,     0,
    -102,  -120,  -120,  -120,  -120,  -120,  -120,  -120,  -120,     0,
    -120,  -120,  -120,  -120,  -120,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -120,     0,   108,     0,  -120,
     109,   110,   111,   112,   113,  -103,  -103,  -103,     0,   117,
     118,   119,   120,   121,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -103,     0,  -121,     0,  -103,  -121,
    -121,  -121,  -121,  -121,  -121,  -121,  -121,     0,  -121,  -121,
    -121,  -121,  -121,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -121,     0,   108,     0,  -121,   109,   110,
     111,   112,   113,   114,  -104,  -104,     0,   117,   118,   119,
     120,   121,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -104,     0,  -122,     0,  -104,  -122,  -122,  -122,
    -122,  -122,  -122,  -122,  -122,     0,  -122,  -122,  -122,  -122,
    -122,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -122,     0,  -110,     0,  -122,  -110,  -110,  -110,  -110,
    -110,  -110,  -110,  -110,     0,  -110,  -110,  -110,  -110,  -110,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -110,     0,   108,     0,  -110,   -92,   -92,   -92,   -92,   -92,
     -92,   -92,   -92,     0,   -92,   -92,   -92,   -92,   -92,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -92,
       0,  -111,     0,   -92,  -111,  -111,  -111,  -111,  -111,  -111,
    -111,  -111,     0,  -111,  -111,  -111,  -111,  -111,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -111,     0,
     108,     0,  -111,   -93,   -93,   -93,   -93,   -93,   -93,   -93,
     -93,     0,   -93,   -93,   -93,   -93,   -93,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -93,     0,  -113,
       0,   -93,  -113,  -113,  -113,  -113,  -113,  -113,  -113,  -113,
       0,  -113,  -113,  -113,  -113,  -113,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -113,     0,   108,     0,
    -113,   -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,     0,
     117,   118,   -95,   -95,   121,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -95,     0,  -114,     0,   -95,
    -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,     0,  -114,
    -114,  -114,  -114,  -114,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -114,     0,   108,     0,  -114,   -96,
     -96,   -96,   -96,   -96,   -96,   -96,   -96,     0,   117,   118,
     -96,   -96,   121,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -96,     0,  -112,     0,   -96,  -112,  -112,
    -112,  -112,  -112,  -112,  -112,  -112,     0,  -112,  -112,  -112,
    -112,  -112,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -112,     0,   108,     0,  -112,   -94,   -94,   -94,
     -94,   -94,   -94,   -94,   -94,     0,   -94,   -94,   -94,   -94,
     -94,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -94,     0,   108,     0,   -94,   109,   110,   111,   112,
     113,   114,   115,   116,     0,   117,   118,   119,   120,   121,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     122,     0,  -125,     0,   -66,  -125,  -125,  -125,  -125,  -125,
    -125,  -125,  -125,     0,  -125,  -125,  -125,  -125,  -125,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -125,
       0,  -124,     0,  -125,  -124,  -124,  -124,  -124,  -124,  -124,
    -124,  -124,     0,  -124,  -124,  -124,  -124,  -124,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -124,     0,
     108,     0,  -124,   109,   110,   111,   112,   113,   114,   115,
     116,     0,   117,   118,   119,   120,   121,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   122,     0,   108,
       0,   -71,   109,   110,   111,   112,   113,   114,   115,   116,
       0,   117,   118,   119,   120,   121,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   122,     0,   108,     0,
    -105,   109,   110,   111,   112,   113,   114,   115,   116,     0,
     117,   118,   119,   120,   121,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   122,     0,   108,     0,   496,
     109,   110,   111,   112,   113,   114,   115,   116,     0,   117,
     118,   119,   120,   121,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   122,     0,   -83,   372,   572,   -83,
     -83,   -83,   -83,   -83,   -83,   -83,   -83,   373,   -83,   -83,
     -83,   -83,   -83,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -83,   254,  -107,   -83,   255,   256,   257,
     258,   259,   260,   261,   262,     0,   263,   264,   265,   266,
     267,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   268,   254,     0,   141,   255,   256,   257,   258,   259,
     260,   261,   262,     0,   263,   264,   265,   266,   267,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   268,
     254,     0,   178,   255,   256,   257,   258,   259,   260,   261,
     262,     0,   263,   264,   265,   266,   267,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   268,   254,     0,
     180,   255,   256,   257,   258,   259,   260,   261,   262,     0,
     263,   264,   265,   266,   267,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   268,   -81,     0,   182,   -81,
     -81,   -81,   -81,   -81,   -81,   -81,   -81,     0,   -81,   -81,
     -81,   -81,   -81,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -81,   -82,     0,   -81,   -82,   -82,   -82,
     -82,   -82,   -82,   -82,   -82,     0,   -82,   -82,   -82,   -82,
     -82,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -82,   -78,     0,   -82,   -78,   -78,   -78,   -78,   -78,
     -78,   -78,   -78,     0,   -78,   -78,   -78,   -78,   -78,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -78,
     -79,     0,   -78,   -79,   -79,   -79,   -79,   -79,   -79,   -79,
     -79,     0,   -79,   -79,   -79,   -79,   -79,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -79,   -80,     0,
     -79,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,     0,
     -80,   -80,   -80,   -80,   -80,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -80,   -84,     0,   -80,   -84,
     -84,   -84,   -84,   -84,   -84,   -84,   -84,     0,   -84,   -84,
     -84,   -84,   -84,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -84,   -91,     0,   -84,   -91,   -91,   -91,
     -91,   -91,   -91,   -91,   -91,     0,   -91,   -91,   -91,   -91,
     -91,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -91,   -85,     0,   -91,   -85,   -85,   -85,   -85,   -85,
     -85,   -85,   -85,     0,   -85,   -85,   -85,   -85,   -85,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -85,
     -86,     0,   -85,   -86,   -86,   -86,   -86,   -86,   -86,   -86,
     -86,     0,   -86,   -86,   -86,   -86,   -86,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -86,   -87,     0,
     -86,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,     0,
     -87,   -87,   -87,   -87,   -87,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -87,   -88,     0,   -87,   -88,
     -88,   -88,   -88,   -88,   -88,   -88,   -88,     0,   -88,   -88,
     -88,   -88,   -88,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -88,   -89,     0,   -88,   -89,   -89,   -89,
     -89,   -89,   -89,   -89,   -89,     0,   -89,   -89,   -89,   -89,
     -89,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -89,   -90,     0,   -89,   -90,   -90,   -90,   -90,   -90,
     -90,   -90,   -90,     0,   -90,   -90,   -90,   -90,   -90,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -90,
     254,     0,   -90,   255,   256,   257,   258,   259,   260,   261,
     262,     0,   263,   264,   265,   266,   267,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   268,   -97,     0,
     546,   -97,   -97,   -97,   -97,   -97,   -97,   -97,   -97,     0,
     -97,   -97,   -97,   -97,   -97,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -97,  -115,     0,   -97,  -115,
    -115,  -115,  -115,  -115,  -115,  -115,  -115,     0,  -115,  -115,
    -115,  -115,  -115,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -115,   254,     0,  -115,   -98,   -98,   -98,
     -98,   -98,   -98,   -98,   -98,     0,   263,   264,   265,   266,
     267,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -98,  -116,     0,   -98,  -116,  -116,  -116,  -116,  -116,
    -116,  -116,  -116,     0,  -116,  -116,  -116,  -116,  -116,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -116,
     254,     0,  -116,   255,   -99,   -99,   -99,   -99,   -99,   -99,
     -99,     0,   263,   264,   265,   266,   267,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -99,  -117,     0,
     -99,  -117,  -117,  -117,  -117,  -117,  -117,  -117,  -117,     0,
    -117,  -117,  -117,  -117,  -117,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -117,   254,     0,  -117,   255,
     256,  -100,  -100,  -100,  -100,  -100,  -100,     0,   263,   264,
     265,   266,   267,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -100,  -118,     0,  -100,  -118,  -118,  -118,
    -118,  -118,  -118,  -118,  -118,     0,  -118,  -118,  -118,  -118,
    -118,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -118,   254,     0,  -118,   255,   256,   257,  -101,  -101,
    -101,  -101,  -101,     0,   263,   264,   265,   266,   267,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -101,
    -119,     0,  -101,  -119,  -119,  -119,  -119,  -119,  -119,  -119,
    -119,     0,  -119,  -119,  -119,  -119,  -119,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -119,   254,     0,
    -119,   255,   256,   257,   258,  -102,  -102,  -102,  -102,     0,
     263,   264,   265,   266,   267,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -102,  -120,     0,  -102,  -120,
    -120,  -120,  -120,  -120,  -120,  -120,  -120,     0,  -120,  -120,
    -120,  -120,  -120,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -120,   254,     0,  -120,   255,   256,   257,
     258,   259,  -103,  -103,  -103,     0,   263,   264,   265,   266,
     267,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -103,  -121,     0,  -103,  -121,  -121,  -121,  -121,  -121,
    -121,  -121,  -121,     0,  -121,  -121,  -121,  -121,  -121,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -121,
     254,     0,  -121,   255,   256,   257,   258,   259,   260,  -104,
    -104,     0,   263,   264,   265,   266,   267,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -104,  -122,     0,
    -104,  -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,     0,
    -122,  -122,  -122,  -122,  -122,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -122,  -110,     0,  -122,  -110,
    -110,  -110,  -110,  -110,  -110,  -110,  -110,     0,  -110,  -110,
    -110,  -110,  -110,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -110,   254,     0,  -110,   -92,   -92,   -92,
     -92,   -92,   -92,   -92,   -92,     0,   -92,   -92,   -92,   -92,
     -92,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -92,  -111,     0,   -92,  -111,  -111,  -111,  -111,  -111,
    -111,  -111,  -111,     0,  -111,  -111,  -111,  -111,  -111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -111,
     254,     0,  -111,   -93,   -93,   -93,   -93,   -93,   -93,   -93,
     -93,     0,   -93,   -93,   -93,   -93,   -93,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -93,  -113,     0,
     -93,  -113,  -113,  -113,  -113,  -113,  -113,  -113,  -113,     0,
    -113,  -113,  -113,  -113,  -113,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -113,   254,     0,  -113,   -95,
     -95,   -95,   -95,   -95,   -95,   -95,   -95,     0,   263,   264,
     -95,   -95,   267,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -95,  -114,     0,   -95,  -114,  -114,  -114,
    -114,  -114,  -114,  -114,  -114,     0,  -114,  -114,  -114,  -114,
    -114,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -114,   254,     0,  -114,   -96,   -96,   -96,   -96,   -96,
     -96,   -96,   -96,     0,   263,   264,   -96,   -96,   267,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -96,
    -112,     0,   -96,  -112,  -112,  -112,  -112,  -112,  -112,  -112,
    -112,     0,  -112,  -112,  -112,  -112,  -112,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -112,   254,     0,
    -112,   -94,   -94,   -94,   -94,   -94,   -94,   -94,   -94,     0,
     -94,   -94,   -94,   -94,   -94,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -94,   254,     0,   -94,   255,
     256,   257,   258,   259,   260,   261,   262,     0,   263,   264,
     265,   266,   267,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   268,   254,     0,   552,   255,   256,   257,
     258,   259,   260,   261,   262,     0,   263,   264,   265,   266,
     267,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   268,   254,     0,   557,   255,   256,   257,   258,   259,
     260,   261,   262,     0,   263,   264,   265,   266,   267,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   268,
     254,     0,   -71,   255,   256,   257,   258,   259,   260,   261,
     262,     0,   263,   264,   265,   266,   267,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   268,  -123,     0,
     578,  -123,  -123,  -123,  -123,  -123,  -123,  -123,  -123,     0,
    -123,  -123,  -123,  -123,  -123,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -123,   254,     0,  -123,   255,
     256,   257,   258,   259,   260,   261,   262,     0,   263,   264,
     265,   266,   267,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   268,  -108,     0,  -106,  -108,  -108,  -108,
    -108,  -108,  -108,  -108,  -108,     0,  -108,  -108,  -108,  -108,
    -108,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -108,  -109,     0,  -108,  -109,  -109,  -109,  -109,  -109,
    -109,  -109,  -109,     0,  -109,  -109,  -109,  -109,  -109,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -109,
     254,     0,  -109,   255,   256,   257,   258,   259,   260,   261,
     262,     0,   263,   264,   265,   266,   267,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   268,   254,     0,
     596,   255,   256,   257,   258,   259,   260,   261,   262,     0,
     263,   264,   265,   266,   267,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   268,   254,     0,   598,   255,
     256,   257,   258,   259,   260,   261,   262,     0,   263,   264,
     265,   266,   267,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   268,   254,     0,   600,   255,   256,   257,
     258,   259,   260,   261,   262,     0,   263,   264,   265,   266,
     267,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   268,  -125,     0,  -105,  -125,  -125,  -125,  -125,  -125,
    -125,  -125,  -125,     0,  -125,  -125,  -125,  -125,  -125,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -125,
    -124,     0,  -125,  -124,  -124,  -124,  -124,  -124,  -124,  -124,
    -124,     0,  -124,  -124,  -124,  -124,  -124,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -124,   -83,   410,
    -124,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   411,
     -83,   -83,   -83,   -83,   -83,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -83,   -83,  -107,   297,     0,
       0,   298,   299,   300,   301,   302,   303,   304,   305,     0,
     306,   307,   308,   309,   310,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -81,   311,   190,   -81,   -81,   -81,
     -81,   -81,   -81,   -81,   -81,     0,   -81,   -81,   -81,   -81,
     -81,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -82,   -81,   -81,   -82,   -82,   -82,   -82,   -82,   -82,   -82,
     -82,     0,   -82,   -82,   -82,   -82,   -82,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -78,   -82,   -82,   -78,
     -78,   -78,   -78,   -78,   -78,   -78,   -78,     0,   -78,   -78,
     -78,   -78,   -78,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -79,   -78,   -78,   -79,   -79,   -79,   -79,   -79,
     -79,   -79,   -79,     0,   -79,   -79,   -79,   -79,   -79,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -80,   -79,
     -79,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,     0,
     -80,   -80,   -80,   -80,   -80,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   297,   -80,   -80,   298,   299,   300,
     301,   302,   303,   304,   305,     0,   306,   307,   308,   309,
     310,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -84,   311,   547,   -84,   -84,   -84,   -84,   -84,   -84,   -84,
     -84,     0,   -84,   -84,   -84,   -84,   -84,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -91,   -84,   -84,   -91,
     -91,   -91,   -91,   -91,   -91,   -91,   -91,     0,   -91,   -91,
     -91,   -91,   -91,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -85,   -91,   -91,   -85,   -85,   -85,   -85,   -85,
     -85,   -85,   -85,     0,   -85,   -85,   -85,   -85,   -85,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -86,   -85,
     -85,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,     0,
     -86,   -86,   -86,   -86,   -86,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -87,   -86,   -86,   -87,   -87,   -87,
     -87,   -87,   -87,   -87,   -87,     0,   -87,   -87,   -87,   -87,
     -87,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -88,   -87,   -87,   -88,   -88,   -88,   -88,   -88,   -88,   -88,
     -88,     0,   -88,   -88,   -88,   -88,   -88,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -89,   -88,   -88,   -89,
     -89,   -89,   -89,   -89,   -89,   -89,   -89,     0,   -89,   -89,
     -89,   -89,   -89,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -90,   -89,   -89,   -90,   -90,   -90,   -90,   -90,
     -90,   -90,   -90,     0,   -90,   -90,   -90,   -90,   -90,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -97,   -90,
     -90,   -97,   -97,   -97,   -97,   -97,   -97,   -97,   -97,     0,
     -97,   -97,   -97,   -97,   -97,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -115,   -97,   -97,  -115,  -115,  -115,
    -115,  -115,  -115,  -115,  -115,     0,  -115,  -115,  -115,  -115,
    -115,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     297,  -115,  -115,   -98,   -98,   -98,   -98,   -98,   -98,   -98,
     -98,     0,   306,   307,   308,   309,   310,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -116,   -98,   -98,  -116,
    -116,  -116,  -116,  -116,  -116,  -116,  -116,     0,  -116,  -116,
    -116,  -116,  -116,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   297,  -116,  -116,   298,   -99,   -99,   -99,   -99,
     -99,   -99,   -99,     0,   306,   307,   308,   309,   310,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -117,   -99,
     -99,  -117,  -117,  -117,  -117,  -117,  -117,  -117,  -117,     0,
    -117,  -117,  -117,  -117,  -117,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   297,  -117,  -117,   298,   299,  -100,
    -100,  -100,  -100,  -100,  -100,     0,   306,   307,   308,   309,
     310,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -118,  -100,  -100,  -118,  -118,  -118,  -118,  -118,  -118,  -118,
    -118,     0,  -118,  -118,  -118,  -118,  -118,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   297,  -118,  -118,   298,
     299,   300,  -101,  -101,  -101,  -101,  -101,     0,   306,   307,
     308,   309,   310,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -119,  -101,  -101,  -119,  -119,  -119,  -119,  -119,
    -119,  -119,  -119,     0,  -119,  -119,  -119,  -119,  -119,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   297,  -119,
    -119,   298,   299,   300,   301,  -102,  -102,  -102,  -102,     0,
     306,   307,   308,   309,   310,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -120,  -102,  -102,  -120,  -120,  -120,
    -120,  -120,  -120,  -120,  -120,     0,  -120,  -120,  -120,  -120,
    -120,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     297,  -120,  -120,   298,   299,   300,   301,   302,  -103,  -103,
    -103,     0,   306,   307,   308,   309,   310,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -121,  -103,  -103,  -121,
    -121,  -121,  -121,  -121,  -121,  -121,  -121,     0,  -121,  -121,
    -121,  -121,  -121,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   297,  -121,  -121,   298,   299,   300,   301,   302,
     303,  -104,  -104,     0,   306,   307,   308,   309,   310,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -122,  -104,
    -104,  -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,     0,
    -122,  -122,  -122,  -122,  -122,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -110,  -122,  -122,  -110,  -110,  -110,
    -110,  -110,  -110,  -110,  -110,     0,  -110,  -110,  -110,  -110,
    -110,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     297,  -110,  -110,   -92,   -92,   -92,   -92,   -92,   -92,   -92,
     -92,     0,   -92,   -92,   -92,   -92,   -92,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -111,   -92,   -92,  -111,
    -111,  -111,  -111,  -111,  -111,  -111,  -111,     0,  -111,  -111,
    -111,  -111,  -111,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   297,  -111,  -111,   -93,   -93,   -93,   -93,   -93,
     -93,   -93,   -93,     0,   -93,   -93,   -93,   -93,   -93,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -113,   -93,
     -93,  -113,  -113,  -113,  -113,  -113,  -113,  -113,  -113,     0,
    -113,  -113,  -113,  -113,  -113,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   297,  -113,  -113,   -95,   -95,   -95,
     -95,   -95,   -95,   -95,   -95,     0,   306,   307,   -95,   -95,
     310,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -114,   -95,   -95,  -114,  -114,  -114,  -114,  -114,  -114,  -114,
    -114,     0,  -114,  -114,  -114,  -114,  -114,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   297,  -114,  -114,   -96,
     -96,   -96,   -96,   -96,   -96,   -96,   -96,     0,   306,   307,
     -96,   -96,   310,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -112,   -96,   -96,  -112,  -112,  -112,  -112,  -112,
    -112,  -112,  -112,     0,  -112,  -112,  -112,  -112,  -112,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   297,  -112,
    -112,   -94,   -94,   -94,   -94,   -94,   -94,   -94,   -94,     0,
     -94,   -94,   -94,   -94,   -94,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   297,   -94,   -94,   298,   299,   300,
     301,   302,   303,   304,   305,     0,   306,   307,   308,   309,
     310,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     297,   311,   558,   298,   299,   300,   301,   302,   303,   304,
     305,     0,   306,   307,   308,   309,   310,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   297,   311,   559,   298,
     299,   300,   301,   302,   303,   304,   305,     0,   306,   307,
     308,   309,   310,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -123,   311,   579,  -123,  -123,  -123,  -123,  -123,
    -123,  -123,  -123,     0,  -123,  -123,  -123,  -123,  -123,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   297,  -123,
    -123,   298,   299,   300,   301,   302,   303,   304,   305,     0,
     306,   307,   308,   309,   310,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -108,   311,  -106,  -108,  -108,  -108,
    -108,  -108,  -108,  -108,  -108,     0,  -108,  -108,  -108,  -108,
    -108,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -109,  -108,  -108,  -109,  -109,  -109,  -109,  -109,  -109,  -109,
    -109,     0,  -109,  -109,  -109,  -109,  -109,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   297,  -109,  -109,   298,
     299,   300,   301,   302,   303,   304,   305,     0,   306,   307,
     308,   309,   310,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -125,   311,  -105,  -125,  -125,  -125,  -125,  -125,
    -125,  -125,  -125,     0,  -125,  -125,  -125,  -125,  -125,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -124,  -125,
    -125,  -124,  -124,  -124,  -124,  -124,  -124,  -124,  -124,     0,
    -124,  -124,  -124,  -124,  -124,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -124,  -124
};

static const yytype_int16 yycheck[] =
{
       0,    19,   369,    63,    64,    65,    66,    67,    68,    69,
      10,   371,   239,   584,    74,    57,    76,   665,   374,    36,
     609,   669,   645,   594,     1,     1,   649,    27,    45,    89,
       7,     8,   621,   105,   244,    52,     1,     1,    98,    99,
     100,     1,    84,   177,   178,     1,     1,     7,   108,   109,
     110,   111,   112,   113,   114,   115,   412,   117,   118,   119,
     120,   121,   122,   273,   106,    41,    43,   423,    40,    86,
     130,    43,     1,     1,     1,    39,    41,   287,   138,     8,
      12,     1,   124,     1,    39,    41,    38,     1,     8,    21,
      22,     1,    40,     7,     8,    43,     1,     7,     8,     1,
     327,     0,     7,     8,     1,   177,   178,   179,   180,   181,
     182,    39,    39,     0,    43,   186,   188,   177,   178,   486,
       1,    39,     0,    43,   184,    39,     7,     8,   488,    39,
     190,    40,   342,   193,    39,     7,   207,    39,     8,   211,
     212,   538,    39,   215,   500,   216,    40,    40,     7,    43,
     544,     7,     8,   213,   225,   581,   550,   228,    39,   230,
     632,   555,   233,   560,   636,   591,    38,     0,    40,    39,
     655,    43,   232,    43,   659,     8,    40,   177,   178,    38,
       1,    40,   576,    39,    43,   245,   246,   247,   248,   249,
     250,   251,     8,   253,   254,   255,   256,   257,   258,   259,
     260,   261,     0,   263,   264,   265,   266,   267,   268,    40,
       8,    39,    43,     0,   274,   275,   276,   277,   278,   279,
     280,     8,   282,    39,    41,    39,    41,    43,   288,   289,
     290,   291,   292,   293,   294,    40,   296,   297,   298,   299,
     300,   301,   302,   303,   304,     7,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
       0,   321,   322,   323,   324,   325,   326,     0,     8,    40,
      40,     0,   332,    43,    44,     8,    38,   337,    40,     8,
       1,    43,   214,   343,   344,   345,   346,   347,   348,   349,
       0,   351,   352,   353,   354,   355,   356,   357,   358,   359,
       0,   361,   362,   363,   364,   365,   366,   239,     8,     7,
       1,     8,     0,   373,     1,     1,    41,    40,     9,    10,
       8,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,     0,     0,    38,     0,    40,
       7,     1,    43,     8,     8,    36,     8,    38,    39,    39,
     367,   411,    43,    38,    38,     1,    40,    39,    39,    43,
      38,    38,   422,     9,    38,    41,    12,    13,    14,    15,
      16,    17,    18,    19,    42,    21,    22,    23,    24,    25,
      38,    42,    40,    38,    38,    43,     1,    40,     1,     1,
      36,    42,    39,    39,    39,   327,    39,    43,     1,     1,
      42,    42,    42,     7,    39,    39,     9,    40,    40,    12,
      13,    14,    15,    16,    17,    18,    19,    42,    21,    22,
      23,    24,    25,    40,     7,    39,    44,     7,    39,   489,
     490,   491,    40,    36,     1,    40,    39,     8,    39,   499,
      43,     1,     9,     1,     1,    12,    13,    14,    15,    16,
      17,    18,    19,   495,    21,    22,    23,    24,    25,    38,
      38,   595,   596,   597,   598,   599,   600,    41,    38,    36,
       1,     7,    39,    38,    38,    38,    43,    38,    40,    38,
       1,     1,    38,    38,   544,    39,    39,   547,    40,    40,
     550,    39,    39,    42,    39,   555,    40,    39,   558,   559,
      40,    39,    39,    42,    39,    39,   640,   641,   642,    41,
     570,    41,    41,    41,    40,    40,   576,     1,    42,   579,
     537,     1,   540,   595,   596,   597,   598,   599,   600,    42,
      42,    42,    42,    42,    42,   595,   596,   597,   598,   599,
     600,    27,   331,   629,   562,   570,    -1,   210,    -1,   188,
      -1,   234,     1,    -1,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    11,   581,    -1,    -1,    -1,    -1,   640,   641,
     642,    -1,    21,   591,    23,    24,    -1,    26,    27,    28,
     640,   641,   642,    -1,    -1,    -1,    35,    -1,    -1,    38,
      39,    -1,    -1,    -1,    -1,   595,   596,   597,   598,   599,
     600,   643,    -1,    -1,   646,   647,    -1,   539,   650,    -1,
      -1,    -1,    -1,    -1,   656,    -1,    -1,    -1,   660,    -1,
      -1,   663,    -1,    -1,    -1,   667,    -1,    -1,    -1,   561,
      -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,
     640,   641,   642,     9,    -1,    -1,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,
      36,    -1,    -1,    39,    -1,     9,    -1,    43,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,
      -1,    -1,    36,    -1,    -1,    39,    -1,     9,    -1,    43,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    -1,    -1,    36,    -1,    -1,    39,    -1,     9,
      -1,    43,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    -1,    -1,    36,    -1,    -1,    39,
      -1,     9,    -1,    43,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,    36,    -1,
      -1,    39,    -1,     9,    -1,    43,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,
      36,    -1,    -1,    39,    -1,     9,    -1,    43,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,
      -1,    -1,    36,    -1,    -1,    39,    -1,     9,    -1,    43,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    -1,    -1,    36,    -1,    -1,    39,    -1,     9,
      -1,    43,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    -1,    -1,    36,    -1,    -1,    39,
      -1,     9,    -1,    43,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,    36,    -1,
      -1,    39,    -1,     9,    -1,    43,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,
      36,    -1,    -1,    39,    -1,     9,    -1,    43,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,
      -1,    -1,    36,    -1,    -1,    39,    -1,     9,    -1,    43,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    -1,    -1,    36,    -1,    -1,    39,    -1,     9,
      -1,    43,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    -1,    -1,    36,    -1,    -1,    39,
      -1,     9,    -1,    43,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,    36,    -1,
      -1,    39,    -1,     9,    -1,    43,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,
      36,    -1,    -1,    39,    -1,     9,    -1,    43,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,
      -1,    -1,    36,    -1,    -1,    39,    -1,     9,    -1,    43,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    -1,    -1,    36,    -1,    -1,    39,    -1,     9,
      -1,    43,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    -1,    -1,    36,    -1,    -1,    39,
      -1,     9,    -1,    43,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,    36,    -1,
      -1,    39,    -1,     9,    -1,    43,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,
      36,    -1,    -1,    39,    -1,     9,    -1,    43,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,
      -1,    -1,    36,    -1,    -1,    39,    -1,     9,    -1,    43,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    -1,    -1,    36,    -1,    -1,    39,    -1,     9,
      -1,    43,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    -1,    -1,    36,    -1,    -1,    39,
      -1,     9,    -1,    43,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,    36,    -1,
      -1,    39,    -1,     9,    -1,    43,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,
      36,    -1,    -1,    39,    -1,     9,    -1,    43,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,
      -1,    -1,    36,    -1,    -1,    39,    -1,     9,    -1,    43,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    -1,    -1,    36,    -1,    -1,    39,    -1,     9,
      -1,    43,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    -1,    -1,    36,    -1,    -1,    39,
      -1,     9,    -1,    43,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,    36,    -1,
      -1,    39,    -1,     9,    -1,    43,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,
      36,    -1,    -1,    39,    -1,     9,    -1,    43,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,
      -1,    -1,    36,    -1,    -1,    39,    -1,     9,    -1,    43,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    -1,    -1,    36,    -1,    -1,    39,    -1,     9,
      -1,    43,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    -1,    -1,    36,    -1,    -1,    39,
      -1,     9,    -1,    43,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,    36,    -1,
      -1,    39,    -1,     9,    -1,    43,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,
      36,    -1,    -1,    39,    -1,     9,    -1,    43,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,
      -1,    -1,    36,    -1,    -1,    39,    -1,     9,    -1,    43,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    -1,    -1,    36,    -1,    -1,    39,    -1,     9,
      -1,    43,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    -1,    -1,    36,    -1,    -1,    39,
      -1,     9,    -1,    43,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,    36,    -1,
      -1,    39,    -1,     9,    -1,    43,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,
      36,    -1,    -1,    39,    -1,     9,    -1,    43,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,
      -1,    -1,    36,    -1,    -1,    39,    -1,     9,    -1,    43,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    -1,    -1,    36,    -1,    -1,    39,    -1,     9,
      -1,    43,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    36,    -1,    -1,    39,
      -1,    -1,    -1,    43,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    -1,
      -1,    38,    -1,    40,    41,    42,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    -1,
      -1,    38,    -1,    40,    41,     3,     4,     5,     6,     7,
       8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,    27,
      28,    29,    30,    31,    32,    -1,    34,    35,    -1,    -1,
      38,    -1,    40,    41,     3,     4,     5,     6,     7,     8,
      -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    21,    -1,    23,    24,    -1,    26,    27,    28,
      29,    30,    31,    32,    -1,    34,    35,    -1,    -1,    38,
      -1,    40,    41,     3,     4,     5,     6,     7,     8,    -1,
      -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    21,    -1,    23,    24,    -1,    26,    27,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    -1,    -1,    38,     1,
      40,     3,     4,     5,     6,     7,    -1,    -1,    -1,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,
      -1,    23,    24,    -1,    26,    27,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    -1,     1,    38,     3,     4,     5,
       6,     7,    -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      -1,     1,    38,     3,     4,     5,     6,     7,    -1,    -1,
      -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    21,    -1,    23,    24,    -1,    26,    27,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    -1,     1,    38,     3,
       4,     5,     6,     7,    -1,    -1,    -1,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,
      24,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    -1,     1,    38,     3,     4,     5,     6,     7,
      -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,    27,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,     1,
      38,     3,     4,     5,     6,     7,    -1,    -1,    -1,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,
      -1,    23,    24,    -1,    26,    27,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    -1,     1,    38,     3,     4,     5,
       6,     7,    -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      -1,     1,    38,     3,     4,     5,     6,     7,    -1,    -1,
      -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    21,    -1,    23,    24,    -1,    26,    27,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    -1,     1,    38,     3,
       4,     5,     6,     7,    -1,    -1,    -1,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,
      24,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    -1,     1,    38,     3,     4,     5,     6,     7,
      -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,    27,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,     1,
      38,     3,     4,     5,     6,     7,    -1,    -1,    -1,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,
      -1,    23,    24,    -1,    26,    27,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    -1,     1,    38,     3,     4,     5,
       6,     7,    -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      -1,     1,    38,     3,     4,     5,     6,     7,    -1,    -1,
      -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    21,    -1,    23,    24,    -1,    26,    27,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    -1,     1,    38,     3,
       4,     5,     6,     7,    -1,    -1,    -1,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,
      24,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    -1,     1,    38,     3,     4,     5,     6,     7,
      -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,    27,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,     1,
      38,     3,     4,     5,     6,     7,    -1,    -1,    -1,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,
      -1,    23,    24,    -1,    26,    27,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    -1,     1,    38,     3,     4,     5,
       6,     7,    -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,     3,     4,     5,     6,     7,    -1,    35,
      -1,    11,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    21,    -1,    23,    24,    -1,    26,    27,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    -1,    -1,    38,     1,
      40,     3,     4,     5,     6,     7,    -1,    -1,    -1,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,
      -1,    23,    24,    -1,    26,    27,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    -1,     1,    38,     3,     4,     5,
       6,     7,    -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      -1,     1,    38,     3,     4,     5,     6,     7,    -1,    -1,
      -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    21,    -1,    23,    24,    -1,    26,    27,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    -1,     1,    38,     3,
       4,     5,     6,     7,    -1,    -1,    -1,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,
      24,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    -1,     1,    38,     3,     4,     5,     6,     7,
      -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,    27,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,     1,
      38,     3,     4,     5,     6,     7,    -1,    -1,    -1,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,
      -1,    23,    24,    -1,    26,    27,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    -1,     1,    38,     3,     4,     5,
       6,     7,    -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      -1,     1,    38,     3,     4,     5,     6,     7,    -1,    -1,
      -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    21,    -1,    23,    24,    -1,    26,    27,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    -1,     1,    38,     3,
       4,     5,     6,     7,    -1,    -1,    -1,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,
      24,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    -1,     1,    38,     3,     4,     5,     6,     7,
      -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,    27,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,     1,
      38,     3,     4,     5,     6,     7,    -1,    -1,    -1,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,
      -1,    23,    24,    -1,    26,    27,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    -1,     1,    38,     3,     4,     5,
       6,     7,    -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      -1,     1,    38,     3,     4,     5,     6,     7,    -1,    -1,
      -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    21,    -1,    23,    24,    -1,    26,    27,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    -1,     1,    38,     3,
       4,     5,     6,     7,    -1,    -1,    -1,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,
      24,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    -1,     1,    38,     3,     4,     5,     6,     7,
      -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,    27,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,     1,
      38,     3,     4,     5,     6,     7,    -1,    -1,    -1,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,
      -1,    23,    24,    -1,    26,    27,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    -1,     1,    38,     3,     4,     5,
       6,     7,    -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      -1,     1,    38,     3,     4,     5,     6,     7,    -1,    -1,
      -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    21,    -1,    23,    24,    -1,    26,    27,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    -1,     1,    38,     3,
       4,     5,     6,     7,    -1,    -1,    -1,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,
      24,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    -1,     1,    38,     3,     4,     5,     6,     7,
      -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,    27,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,     1,
      38,     3,     4,     5,     6,     7,    -1,    -1,    -1,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,
      -1,    23,    24,    -1,    26,    27,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    -1,     1,    38,     3,     4,     5,
       6,     7,    -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      -1,     1,    38,     3,     4,     5,     6,     7,    -1,    -1,
      -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    21,    -1,    23,    24,    -1,    26,    27,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    -1,     1,    38,     3,
       4,     5,     6,     7,    -1,    -1,    -1,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,
      24,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    -1,     1,    38,     3,     4,     5,     6,     7,
      -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,    27,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,     1,
      38,     3,     4,     5,     6,     7,    -1,    -1,    -1,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,
      -1,    23,    24,    -1,    26,    27,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    -1,     1,    38,     3,     4,     5,
       6,     7,    -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      -1,     1,    38,     3,     4,     5,     6,     7,    -1,    -1,
      -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    21,    -1,    23,    24,    -1,    26,    27,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    -1,     1,    38,     3,
       4,     5,     6,     7,    -1,    -1,    -1,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,
      24,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    -1,     1,    38,     3,     4,     5,     6,     7,
      -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,    27,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,     1,
      38,     3,     4,     5,     6,     7,    -1,    -1,    -1,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,
      -1,    23,    24,    -1,    26,    27,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    -1,     1,    38,     3,     4,     5,
       6,     7,    -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      -1,     1,    38,     3,     4,     5,     6,     7,    -1,    -1,
      -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    21,    -1,    23,    24,    -1,    26,    27,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    -1,     1,    38,     3,
       4,     5,     6,     7,    -1,    -1,    -1,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,
      24,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    -1,     1,    38,     3,     4,     5,     6,     7,
      -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,    27,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,     1,
      38,     3,     4,     5,     6,     7,    -1,    -1,    -1,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,
      -1,    23,    24,    -1,    26,    27,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    -1,     1,    38,     3,     4,     5,
       6,     7,    -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      -1,     1,    38,     3,     4,     5,     6,     7,    -1,    -1,
      -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    21,    -1,    23,    24,    -1,    26,    27,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    -1,     1,    38,     3,
       4,     5,     6,     7,    -1,    -1,    -1,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,
      24,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    -1,     1,    38,     3,     4,     5,     6,     7,
      -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,    27,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,     1,
      38,     3,     4,     5,     6,     7,    -1,    -1,    -1,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,
      -1,    23,    24,    -1,    26,    27,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    -1,     1,    38,     3,     4,     5,
       6,     7,    -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      -1,     1,    38,     3,     4,     5,     6,     7,    -1,    -1,
      -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    21,    -1,    23,    24,    -1,    26,    27,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    -1,     1,    38,     3,
       4,     5,     6,     7,    -1,    -1,    -1,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,
      24,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    -1,     1,    38,     3,     4,     5,     6,     7,
      -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,    27,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,     1,
      38,     3,     4,     5,     6,     7,    -1,    -1,    -1,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,
      -1,    23,    24,    -1,    26,    27,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    -1,     1,    38,     3,     4,     5,
       6,     7,    -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      -1,     1,    38,     3,     4,     5,     6,     7,    -1,    -1,
      -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    21,    -1,    23,    24,    -1,    26,    27,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    -1,     1,    38,     3,
       4,     5,     6,     7,    -1,    -1,    -1,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,
      24,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    -1,     1,    38,     3,     4,     5,     6,     7,
      -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,    27,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,     1,
      38,     3,     4,     5,     6,     7,    -1,    -1,    -1,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,
      -1,    23,    24,    -1,    26,    27,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    -1,     1,    38,     3,     4,     5,
       6,     7,    -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      -1,     1,    38,     3,     4,     5,     6,     7,    -1,    -1,
      -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    21,    -1,    23,    24,    -1,    26,    27,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    -1,     1,    38,     3,
       4,     5,     6,     7,    -1,    -1,    -1,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,
      24,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    -1,     1,    38,     3,     4,     5,     6,     7,
      -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,    27,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,     1,
      38,     3,     4,     5,     6,     7,    -1,    -1,    -1,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,
      -1,    23,    24,    -1,    26,    27,    28,     3,     4,     5,
       6,     7,    -1,    35,    -1,    11,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,     3,     4,     5,     6,     7,    -1,    35,
      -1,    11,    38,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    21,    -1,    23,    24,    -1,    26,    27,    28,     3,
       4,     5,     6,     7,    -1,    35,    -1,    11,    38,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,
      24,    -1,    26,    27,    28,     3,     4,     5,     6,     7,
      -1,    35,    -1,    11,    38,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,    27,
      28,     3,     4,     5,     6,     7,    -1,    35,    -1,    11,
      38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,
      -1,    23,    24,    -1,    26,    27,    28,     3,     4,     5,
       6,     7,    -1,    35,    -1,    11,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,
       9,    10,    38,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,    38,
      -1,    40,     9,    -1,    43,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,
      -1,    -1,    -1,    40,     9,    -1,    43,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,    -1,    -1,    -1,    40,     9,    -1,    43,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    36,    -1,    -1,    -1,    40,     9,    -1,
      43,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,    40,
       9,    -1,    43,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,
      -1,    40,     9,    -1,    43,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,
      -1,    -1,    -1,    40,     9,    -1,    43,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,    -1,    -1,    -1,    40,     9,    -1,    43,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    36,    -1,    -1,    -1,    40,     9,    -1,
      43,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,    40,
       9,    -1,    43,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,
      -1,    40,     9,    -1,    43,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,
      -1,    -1,    -1,    40,     9,    -1,    43,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,    -1,    -1,    -1,    40,     9,    -1,    43,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    36,    -1,    -1,    -1,    40,     9,    -1,
      43,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,    40,
       9,    -1,    43,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,
      -1,    40,     9,    -1,    43,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,
      -1,    -1,    -1,    40,     9,    -1,    43,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,    -1,    -1,    -1,    40,     9,    -1,    43,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    36,    -1,    -1,    -1,    40,     9,    -1,
      43,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,    40,
       9,    -1,    43,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,
      -1,    40,     9,    -1,    43,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,
      -1,    -1,    -1,    40,     9,    -1,    43,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,    -1,    -1,    -1,    40,     9,    -1,    43,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    36,    -1,    -1,    -1,    40,     9,    -1,
      43,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,    40,
       9,    -1,    43,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,
      -1,    40,     9,    -1,    43,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,
      -1,    -1,    -1,    40,     9,    -1,    43,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,    -1,    -1,    -1,    40,     9,    -1,    43,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    36,    -1,    -1,    -1,    40,     9,    -1,
      43,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,    40,
       9,    -1,    43,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,
      -1,    40,     9,    -1,    43,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,
      -1,    -1,    -1,    40,     9,    -1,    43,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,    -1,    -1,    -1,    40,     9,    -1,    43,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    36,    -1,    -1,    -1,    40,     9,    -1,
      43,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,    40,
       9,    -1,    43,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,
      -1,    40,     9,    -1,    43,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,
      -1,    -1,    -1,    40,     9,    -1,    43,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,    -1,    -1,    -1,    40,     9,    -1,    43,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    36,    -1,    -1,    -1,    40,     9,    -1,
      43,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,    40,
       9,    -1,    43,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,
      -1,    40,     9,    -1,    43,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,
      -1,    -1,    -1,    40,     9,    -1,    43,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,    -1,    -1,    -1,    40,     9,    -1,    43,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    36,    -1,    -1,    -1,    40,     9,    -1,
      43,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,    40,
       9,    -1,    43,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,
      -1,    40,     9,    -1,    43,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,
      -1,    -1,    -1,    40,     9,    -1,    43,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,    -1,    -1,    -1,    40,     9,    -1,    43,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    36,    -1,    -1,    -1,    40,     9,    10,
      43,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,    -1,    38,     9,    40,
      -1,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,    -1,     9,    -1,    40,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,    -1,     9,    -1,    40,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    36,    -1,     9,    -1,    40,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36,    -1,     9,    -1,    40,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,    -1,     9,    -1,    40,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    -1,     9,    -1,    40,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,
      -1,     9,    -1,    40,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,
       9,    -1,    40,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,     9,
      -1,    40,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,     9,    -1,
      40,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,    -1,     9,    -1,    40,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,    -1,     9,    -1,    40,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    36,    -1,     9,    -1,    40,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36,    -1,     9,    -1,    40,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,    -1,     9,    -1,    40,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    -1,     9,    -1,    40,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,
      -1,     9,    -1,    40,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,
       9,    -1,    40,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,     9,
      -1,    40,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,     9,    -1,
      40,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,    -1,     9,    -1,    40,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,    -1,     9,    -1,    40,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    36,    -1,     9,    -1,    40,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36,    -1,     9,    -1,    40,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,    -1,     9,    -1,    40,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    -1,     9,    -1,    40,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,
      -1,     9,    -1,    40,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,
       9,    -1,    40,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,     9,
      -1,    40,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,     9,    -1,
      40,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,    -1,     9,    -1,    40,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,    -1,     9,    -1,    40,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    36,    -1,     9,    -1,    40,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36,    -1,     9,    -1,    40,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,    -1,     9,    -1,    40,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    -1,     9,    -1,    40,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,
      -1,     9,    -1,    40,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,
       9,    -1,    40,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,     9,
      -1,    40,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,     9,    -1,
      40,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,    -1,     9,    -1,    40,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,    -1,     9,    -1,    40,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    36,    -1,     9,    -1,    40,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36,    -1,     9,    -1,    40,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,    -1,     9,    -1,    40,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    -1,     9,    -1,    40,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,
      -1,     9,    -1,    40,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,
       9,    -1,    40,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,     9,
      -1,    40,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,     9,    -1,
      40,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,    -1,     9,    -1,    40,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,    -1,     9,    10,    40,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    36,     9,    38,    39,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,     9,    -1,    39,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,
       9,    -1,    39,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,     9,    -1,
      39,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,     9,    -1,    39,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    36,     9,    -1,    39,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,     9,    -1,    39,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,
       9,    -1,    39,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,     9,    -1,
      39,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,     9,    -1,    39,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    36,     9,    -1,    39,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,     9,    -1,    39,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,
       9,    -1,    39,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,     9,    -1,
      39,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,     9,    -1,    39,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    36,     9,    -1,    39,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,     9,    -1,    39,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,
       9,    -1,    39,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,     9,    -1,
      39,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,     9,    -1,    39,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    36,     9,    -1,    39,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,     9,    -1,    39,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,
       9,    -1,    39,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,     9,    -1,
      39,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,     9,    -1,    39,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    36,     9,    -1,    39,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,     9,    -1,    39,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,
       9,    -1,    39,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,     9,    -1,
      39,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,     9,    -1,    39,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    36,     9,    -1,    39,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,     9,    -1,    39,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,
       9,    -1,    39,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,     9,    -1,
      39,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,     9,    -1,    39,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    36,     9,    -1,    39,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,     9,    -1,    39,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,
       9,    -1,    39,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,     9,    -1,
      39,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,     9,    -1,    39,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    36,     9,    -1,    39,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,     9,    -1,    39,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,
       9,    -1,    39,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,     9,    -1,
      39,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,     9,    -1,    39,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    36,     9,    -1,    39,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,     9,    -1,    39,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,
       9,    -1,    39,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,     9,    -1,
      39,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,     9,    -1,    39,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    36,     9,    -1,    39,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,     9,    -1,    39,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,
       9,    -1,    39,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,     9,    -1,
      39,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,     9,    -1,    39,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    36,     9,    -1,    39,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,     9,    -1,    39,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,
       9,    -1,    39,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,     9,    10,
      39,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,    37,    38,     9,    -1,
      -1,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     9,    36,    37,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       9,    36,    37,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     9,    36,    37,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     9,    36,    37,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,    36,
      37,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     9,    36,    37,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       9,    36,    37,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     9,    36,    37,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     9,    36,    37,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,    36,
      37,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     9,    36,    37,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       9,    36,    37,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     9,    36,    37,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     9,    36,    37,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,    36,
      37,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     9,    36,    37,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       9,    36,    37,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     9,    36,    37,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     9,    36,    37,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,    36,
      37,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     9,    36,    37,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       9,    36,    37,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     9,    36,    37,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     9,    36,    37,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,    36,
      37,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     9,    36,    37,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       9,    36,    37,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     9,    36,    37,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     9,    36,    37,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,    36,
      37,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     9,    36,    37,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       9,    36,    37,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     9,    36,    37,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     9,    36,    37,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,    36,
      37,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     9,    36,    37,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       9,    36,    37,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     9,    36,    37,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     9,    36,    37,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,    36,
      37,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     9,    36,    37,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       9,    36,    37,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     9,    36,    37,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     9,    36,    37,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,    36,
      37,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     9,    36,    37,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       9,    36,    37,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     9,    36,    37,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     9,    36,    37,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,    36,
      37,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,    37
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     8,    46,    47,    59,     7,    43,    64,    84,     0,
      48,    38,    60,     1,     7,    38,    62,    49,    59,    61,
      84,    86,    85,     7,     8,    71,    40,    50,     1,    67,
      71,    40,    84,    84,    73,     7,    74,    39,    63,    49,
      41,    39,     8,    43,    75,    72,    75,    65,     1,    69,
       1,    41,     7,     8,     1,    75,     1,    41,     3,     4,
       5,     6,     7,    11,    21,    23,    24,    26,    27,    28,
      29,    30,    31,    32,    34,    35,    38,    40,    51,    54,
      55,    59,    87,    40,    68,    75,     7,    55,    10,    20,
      88,    87,    87,    87,    87,    87,    87,    87,    38,    38,
      38,    52,     1,    87,    87,    56,    41,    42,     9,    12,
      13,    14,    15,    16,    17,    18,    19,    21,    22,    23,
      24,    25,    36,    40,    70,    55,    75,    42,     1,    87,
      38,    89,     1,    87,     1,    87,     1,    87,    38,    40,
      40,    39,    51,    57,    55,    87,     1,    87,     1,    87,
       1,    87,     1,    87,     1,    87,     1,    87,     1,    87,
       1,     1,    87,     1,    87,     1,    87,     1,    87,     1,
      87,    87,    55,    42,    66,    87,    90,    39,    39,    39,
      39,    39,    39,     8,    40,    76,    83,    87,    58,    42,
      37,    42,     1,    43,    91,     1,    39,    51,    51,    51,
      51,    51,    51,     7,    87,    39,    83,    81,    57,    87,
      87,    33,    33,    44,    79,    53,    83,    91,    51,    51,
      87,    84,    51,    83,    77,    80,    43,    82,    83,     7,
      78,    83,    44,    83,    87,    83,    82,     8,    43,     8,
       3,     4,     5,     6,     7,    11,    21,    23,    24,    26,
      27,    28,    35,    38,     9,    12,    13,    14,    15,    16,
      17,    18,    19,    21,    22,    23,    24,    25,    36,     3,
       4,     5,     6,     7,    11,    21,    23,    24,    26,    27,
      28,    35,    38,     3,     4,     5,     6,     7,    11,    21,
      23,    24,    26,    27,    28,    35,    38,     9,    12,    13,
      14,    15,    16,    17,    18,    19,    21,    22,    23,    24,
      25,    36,     9,    12,    13,    14,    15,    16,    17,    18,
      19,    21,    22,    23,    24,    25,    36,     8,    29,    30,
      31,    32,    34,    40,    54,    59,    87,    40,     3,     4,
       5,     6,     7,    11,    21,    23,    24,    26,    27,    28,
      35,    38,     9,    12,    13,    14,    15,    16,    17,    18,
      19,    21,    22,    23,    24,    25,    36,     7,     8,     7,
      64,    84,    10,    20,    88,    87,    87,    87,    87,    87,
      87,    87,    87,    87,     1,    87,     1,    87,     1,    87,
       1,    87,     1,    87,     1,    87,     1,    87,     1,     1,
      87,     1,    87,     1,    87,     1,    87,     1,    87,    87,
      10,    20,    88,    87,    87,    87,    87,    87,    87,    87,
      87,    10,    20,    88,    87,    87,    87,    87,    87,    87,
      87,    87,    87,     1,    87,     1,    87,     1,    87,     1,
      87,     1,    87,     1,    87,     1,    87,     1,     1,    87,
       1,    87,     1,    87,     1,    87,     1,    87,    87,    87,
       1,    87,     1,    87,     1,    87,     1,    87,     1,    87,
       1,    87,     1,    87,     1,     1,    87,     1,    87,     1,
      87,     1,    87,     1,    87,    87,     7,    64,    84,    38,
      38,    38,    52,     1,    87,    41,    40,    87,    10,    20,
      88,    87,    87,    87,    87,    87,    87,    87,    87,    87,
       1,    87,     1,    87,     1,    87,     1,    87,     1,    87,
       1,    87,     1,    87,     1,     1,    87,     1,    87,     1,
      87,     1,    87,     1,    87,    87,    75,     7,    38,    60,
      38,    62,     1,    87,    38,    89,    39,    37,     1,    87,
      38,    89,    39,     1,    87,    38,    89,    39,    37,    37,
      38,    60,    38,    62,     1,    87,     1,    87,     1,    87,
      38,    40,    40,    55,     1,    87,    38,    89,    39,    37,
      75,    61,    84,    71,    40,    90,    87,    90,    90,    87,
      87,    61,    84,    71,    40,    39,    39,    39,    39,    39,
      39,    76,    42,    90,    87,     1,    67,    71,    40,    39,
      63,     1,    39,     1,    39,     1,    39,     1,    67,    71,
      40,    39,    63,    51,    51,    51,    51,    51,    51,    39,
       1,    39,    41,    39,    65,     1,    41,    39,    65,     1,
      33,    33,    53,    69,     1,    41,    41,    69,     1,    41,
      41,    51,    51,    51,    55,    40,    68,    55,    55,    40,
      68,    55,    42,    70,    55,    42,    42,    70,    55,    42,
      55,    42,    66,    55,    42,    66,    42,     1,    42,     1
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    45,    46,    47,    48,    47,    49,    50,    49,    51,
      51,    51,    51,    52,    53,    51,    51,    51,    54,    51,
      51,    51,    51,    51,    51,    51,    51,    55,    56,    55,
      57,    58,    57,    60,    59,    61,    59,    62,    63,    59,
      64,    65,    66,    59,    68,    67,    69,    67,    70,    67,
      71,    72,    71,    73,    71,    74,    71,    75,    75,    75,
      77,    78,    76,    79,    80,    76,    81,    76,    76,    82,
      82,    83,    83,    84,    85,    84,    86,    84,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    88,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    89,    89,    90,    90,    91,    91
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     0,     3,     0,     0,     3,     5,
       7,     5,     5,     0,     0,     7,     2,     3,     0,     4,
       1,     1,     5,     7,     5,     5,     3,     0,     0,     3,
       0,     0,     3,     0,     5,     0,     5,     0,     0,     6,
       0,     0,     0,    11,     0,     6,     0,     5,     0,     7,
       0,     0,     4,     0,     4,     0,     4,     0,     4,     3,
       0,     0,     9,     0,     0,     7,     0,     4,     2,     0,
       5,     2,     1,     0,     0,     4,     0,     4,     1,     1,
       1,     1,     1,     1,     2,     2,     2,     2,     2,     2,
       2,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     5,     3,     0,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     0,     2,     0,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (max, childrenCount, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, max, childrenCount); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, int *max, int *childrenCount)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (max);
  YYUSE (childrenCount);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, int *max, int *childrenCount)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, max, childrenCount);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule, int *max, int *childrenCount)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)], max, childrenCount);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, max, childrenCount); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, int *max, int *childrenCount)
{
  YYUSE (yyvaluep);
  YYUSE (max);
  YYUSE (childrenCount);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yykind)
    {
    case YYSYMBOL_STRING: /* STRING  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 3941 "sintatico.tab.c"
        break;

    case YYSYMBOL_CHAR: /* CHAR  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 3950 "sintatico.tab.c"
        break;

    case YYSYMBOL_INT: /* INT  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 3959 "sintatico.tab.c"
        break;

    case YYSYMBOL_FLOAT: /* FLOAT  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 3968 "sintatico.tab.c"
        break;

    case YYSYMBOL_ID: /* ID  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 3977 "sintatico.tab.c"
        break;

    case YYSYMBOL_TYPE: /* TYPE  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 3986 "sintatico.tab.c"
        break;

    case YYSYMBOL_IN: /* IN  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 3995 "sintatico.tab.c"
        break;

    case YYSYMBOL_OPPOS: /* OPPOS  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4004 "sintatico.tab.c"
        break;

    case YYSYMBOL_OPUNI: /* OPUNI  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4013 "sintatico.tab.c"
        break;

    case YYSYMBOL_OPBIN1: /* OPBIN1  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4022 "sintatico.tab.c"
        break;

    case YYSYMBOL_OPBIN2: /* OPBIN2  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4031 "sintatico.tab.c"
        break;

    case YYSYMBOL_OPBIN3: /* OPBIN3  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4040 "sintatico.tab.c"
        break;

    case YYSYMBOL_OPBIN4: /* OPBIN4  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4049 "sintatico.tab.c"
        break;

    case YYSYMBOL_OPBIN5: /* OPBIN5  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4058 "sintatico.tab.c"
        break;

    case YYSYMBOL_OPBIN6: /* OPBIN6  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4067 "sintatico.tab.c"
        break;

    case YYSYMBOL_OPBIN7: /* OPBIN7  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4076 "sintatico.tab.c"
        break;

    case YYSYMBOL_OPBIN8: /* OPBIN8  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4085 "sintatico.tab.c"
        break;

    case YYSYMBOL_OPASSIGN: /* OPASSIGN  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4094 "sintatico.tab.c"
        break;

    case YYSYMBOL_21_: /* '*'  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4103 "sintatico.tab.c"
        break;

    case YYSYMBOL_22_: /* '/'  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4112 "sintatico.tab.c"
        break;

    case YYSYMBOL_23_: /* '+'  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4121 "sintatico.tab.c"
        break;

    case YYSYMBOL_24_: /* '-'  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4130 "sintatico.tab.c"
        break;

    case YYSYMBOL_25_: /* '%'  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4139 "sintatico.tab.c"
        break;

    case YYSYMBOL_26_: /* '!'  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4148 "sintatico.tab.c"
        break;

    case YYSYMBOL_27_: /* '~'  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4157 "sintatico.tab.c"
        break;

    case YYSYMBOL_28_: /* '&'  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4166 "sintatico.tab.c"
        break;

    case YYSYMBOL_cmd: /* cmd  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4175 "sintatico.tab.c"
        break;

    case YYSYMBOL_declaration: /* declaration  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4184 "sintatico.tab.c"
        break;

    case YYSYMBOL_exp: /* exp  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4193 "sintatico.tab.c"
        break;

      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (int *max, int *childrenCount)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
      if (yytable_value_is_error (yyn))
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 4: /* $@1: %empty  */
#line 232 "sintatico.y"
                      {
		add_child((yyvsp[0].node), parents->first->value);
	}
#line 4463 "sintatico.tab.c"
    break;

  case 7: /* $@2: %empty  */
#line 238 "sintatico.y"
                      {
		add_child((yyvsp[0].node), parents->first->value);
	}
#line 4471 "sintatico.tab.c"
    break;

  case 9: /* cmd: IF '(' exp ')' cmd  */
#line 243 "sintatico.y"
                                 {
		(yyval.node) = create_node(strdup("<if>"));
		add_child((yyvsp[-2].node), (yyval.node));
		add_child((yyvsp[0].node), (yyval.node));
	}
#line 4481 "sintatico.tab.c"
    break;

  case 10: /* cmd: IF '(' exp ')' cmd ELSE cmd  */
#line 248 "sintatico.y"
                                                 {
		(yyval.node) = create_node(strdup("<if-else>"));
		add_child((yyvsp[-4].node), (yyval.node));
		add_child((yyvsp[-2].node), (yyval.node));
		add_child((yyvsp[0].node), (yyval.node));
	}
#line 4492 "sintatico.tab.c"
    break;

  case 11: /* cmd: WHILE '(' exp ')' cmd  */
#line 254 "sintatico.y"
                                {
		(yyval.node) = create_node(strdup("<while>"));
		add_child((yyvsp[-2].node), (yyval.node));
		add_child((yyvsp[0].node), (yyval.node));
	}
#line 4502 "sintatico.tab.c"
    break;

  case 12: /* cmd: FORALL '(' exp ')' cmd  */
#line 259 "sintatico.y"
                                 {
		(yyval.node) = create_node(strdup("<forall>"));
		add_child((yyvsp[-2].node), (yyval.node));
		add_child((yyvsp[0].node), (yyval.node));
	}
#line 4512 "sintatico.tab.c"
    break;

  case 13: /* @3: %empty  */
#line 264 "sintatico.y"
              {
		(yyval.node) = create_node(strdup("<for>"));
		insert(0, (yyval.node), parents);
	}
#line 4521 "sintatico.tab.c"
    break;

  case 14: /* $@4: %empty  */
#line 267 "sintatico.y"
                          {
		removeAt(0, parents);
	}
#line 4529 "sintatico.tab.c"
    break;

  case 15: /* cmd: FOR @3 '(' forargs ')' $@4 cmd  */
#line 269 "sintatico.y"
              {
		(yyval.node) = (yyvsp[-5].node);
		add_child((yyvsp[0].node), (yyval.node));
	}
#line 4538 "sintatico.tab.c"
    break;

  case 16: /* cmd: exp ';'  */
#line 273 "sintatico.y"
                  { (yyval.node) = (yyvsp[-1].node); }
#line 4544 "sintatico.tab.c"
    break;

  case 17: /* cmd: RETURN exp ';'  */
#line 274 "sintatico.y"
                         {
		add_child((yyvsp[-1].node), ((yyval.node) = create_node(strdup("<return>"))));
	}
#line 4552 "sintatico.tab.c"
    break;

  case 18: /* $@5: %empty  */
#line 277 "sintatico.y"
          {
		insert(0, create_node(strdup("<block>")), parents);
		PUSH_CONTEXT;
	}
#line 4561 "sintatico.tab.c"
    break;

  case 19: /* cmd: $@5 '{' cmds '}'  */
#line 280 "sintatico.y"
                       {
		POP_CONTEXT;
		(yyval.node) = parents->first->value;
		removeAt(0, parents);
	}
#line 4571 "sintatico.tab.c"
    break;

  case 20: /* cmd: ';'  */
#line 285 "sintatico.y"
              {
		(yyval.node) = create_node(strdup("<emptycmd>"));
	}
#line 4579 "sintatico.tab.c"
    break;

  case 22: /* cmd: IF '(' error ')' cmd  */
#line 290 "sintatico.y"
                                        {
		(yyval.node) = create_node(strdup("<if>"));
		add_child(create_node(ERR_TOKEN), (yyval.node));
		add_child((yyvsp[0].node), (yyval.node));
		ssprintf(syn_errormsg, "Expected condition in '%s' statment", (yyvsp[-4].name));
	}
#line 4590 "sintatico.tab.c"
    break;

  case 23: /* cmd: IF '(' error ')' cmd ELSE cmd  */
#line 296 "sintatico.y"
                                                   {
		(yyval.node) = create_node(strdup("<if-else>"));
		add_child(create_node(ERR_TOKEN), (yyval.node));
		add_child((yyvsp[-2].node), (yyval.node));
		add_child((yyvsp[0].node), (yyval.node));
		ssprintf(syn_errormsg, "Expected condition in '%s' statment", (yyvsp[-6].name));
	}
#line 4602 "sintatico.tab.c"
    break;

  case 24: /* cmd: WHILE '(' error ')' cmd  */
#line 303 "sintatico.y"
                                  {
		(yyval.node) = create_node(strdup("<while>"));
		add_child(create_node(ERR_TOKEN), (yyval.node));
		add_child((yyvsp[0].node), (yyval.node));
		ssprintf(syn_errormsg, "Expected condition in '%s' statment", (yyvsp[-4].name));
	}
#line 4613 "sintatico.tab.c"
    break;

  case 25: /* cmd: FORALL '(' error ')' cmd  */
#line 309 "sintatico.y"
                                   {
		(yyval.node) = create_node(strdup("<forall>"));
		add_child(create_node(ERR_TOKEN), (yyval.node));
		add_child((yyvsp[0].node), (yyval.node));
		ssprintf(syn_errormsg, "Expected in-expression in '%s' statment", (yyvsp[-4].name));
	}
#line 4624 "sintatico.tab.c"
    break;

  case 26: /* cmd: RETURN error ';'  */
#line 315 "sintatico.y"
                           {
		(yyval.node) = create_node(strdup("<return>"));
		add_child(create_node(ERR_TOKEN), (yyval.node));
		ssprintf(syn_errormsg, "Expected return expression");
	}
#line 4634 "sintatico.tab.c"
    break;

  case 28: /* $@6: %empty  */
#line 323 "sintatico.y"
              {
		add_child((yyvsp[0].node), parents->first->value);
	}
#line 4642 "sintatico.tab.c"
    break;

  case 31: /* $@7: %empty  */
#line 329 "sintatico.y"
              {
		add_child((yyvsp[0].node), parents->first->value);
	}
#line 4650 "sintatico.tab.c"
    break;

  case 33: /* @8: %empty  */
#line 334 "sintatico.y"
                     {
		(yyval.node) = create_node(strdup("<declr>"));
		add_child((yyvsp[-1].node), (yyval.node));
		add_child((yyvsp[0].node), (yyval.node));
		ADD_CONTEXT(VAR, FIRSTCHILD_VALUE((yyvsp[0].node)), FIRSTCHILD_VALUE((yyvsp[-1].node)));
		insert(0, (yyval.node), parents);
	}
#line 4662 "sintatico.tab.c"
    break;

  case 34: /* declaration: TYPE ID @8 idlist ';'  */
#line 340 "sintatico.y"
                     {
		(yyval.node) = (yyvsp[-2].node);
		removeAt(0, parents);
	}
#line 4671 "sintatico.tab.c"
    break;

  case 35: /* @9: %empty  */
#line 344 "sintatico.y"
                      {
		(yyval.node) = create_node(strdup("<declr_fn>"));
		add_child((yyvsp[-2].node), (yyval.node));
		add_child((yyvsp[-1].node), (yyval.node));
		ADD_CONTEXT(FUN, FIRSTCHILD_VALUE((yyvsp[-1].node)), FIRSTCHILD_VALUE((yyvsp[-2].node)));
		PUSH_CONTEXT;

		node_t pars = create_node(strdup("<parlist>"));
		add_child(pars, (yyval.node));
		insert(0, pars, parents); /* É removido dentro de declr_fntail */
	}
#line 4687 "sintatico.tab.c"
    break;

  case 36: /* declaration: TYPE ID '(' @9 declr_fntail  */
#line 354 "sintatico.y"
                       {
		POP_CONTEXT;
		(yyval.node) = (yyvsp[-1].node);
	}
#line 4696 "sintatico.tab.c"
    break;

  case 37: /* @10: %empty  */
#line 359 "sintatico.y"
                      {
		(yyval.node) = create_node(strdup("<declr>"));
		add_child((yyvsp[-1].node), (yyval.node));
		add_child(create_node(ERR_TOKEN), (yyval.node));
		insert(0, (yyval.node), parents);
	}
#line 4707 "sintatico.tab.c"
    break;

  case 38: /* $@11: %empty  */
#line 364 "sintatico.y"
              {
		removeAt(0, parents);
		YYERROR;
	}
#line 4716 "sintatico.tab.c"
    break;

  case 39: /* declaration: TYPE idlist @10 ';' $@11 error  */
#line 367 "sintatico.y"
                {
		(yyval.node) = (yyvsp[-3].node);
		ssprintf(
			syn_errormsg,
			"Expected identifier of type '%s'",
			FIRSTCHILD_VALUE((yyvsp[-5].node))
		);
	}
#line 4729 "sintatico.tab.c"
    break;

  case 40: /* @12: %empty  */
#line 375 "sintatico.y"
               {
		(yyval.node) = create_node(strdup("<declr_fn>"));
		add_child((yyvsp[0].node), (yyval.node));
		add_child(create_node(ERR_TOKEN), (yyval.node));

		node_t pars = create_node(strdup("<parlist>"));
		add_child(pars, (yyval.node));
		insert(0, pars, parents);
		PUSH_CONTEXT;
	}
#line 4744 "sintatico.tab.c"
    break;

  case 41: /* @13: %empty  */
#line 384 "sintatico.y"
                          {
		removeAt(0, parents);
		(yyval.node) = (yyvsp[-3].node);
		node_t block = create_node(strdup("<block>"));
		add_child(block, (yyval.node));
		insert(0, block, parents);
	}
#line 4756 "sintatico.tab.c"
    break;

  case 42: /* $@14: %empty  */
#line 390 "sintatico.y"
                       {
		POP_CONTEXT;
		removeAt(0, parents);
		YYERROR;
	}
#line 4766 "sintatico.tab.c"
    break;

  case 43: /* declaration: TYPE @12 '(' parlist ')' @13 '{' cmds '}' $@14 error  */
#line 394 "sintatico.y"
                {
		(yyval.node) = (yyvsp[-5].node);
		ssprintf(syn_errormsg, "Expected identifier of type '%s' in function declaration", (yyvsp[-10].node)->value);
	}
#line 4775 "sintatico.tab.c"
    break;

  case 44: /* $@15: %empty  */
#line 400 "sintatico.y"
                              {
		node_t block = create_node(strdup("<block>"));
		add_child(block, ((node_t) parents->first->value)->parent);
		removeAt(0, parents); /* Inserido no que vem antes */
		insert(0, block, parents);
	}
#line 4786 "sintatico.tab.c"
    break;

  case 45: /* declr_fntail: parlist ')' '{' $@15 cmds '}'  */
#line 405 "sintatico.y"
                   {
		removeAt(0, parents);
	}
#line 4794 "sintatico.tab.c"
    break;

  case 46: /* $@16: %empty  */
#line 409 "sintatico.y"
                    {
		node_t block = create_node(strdup("<block>"));
		add_child(block, ((node_t) parents->first->value)->parent);

		add_child(create_node(ERR_TOKEN), parents->first->value);

		removeAt(0, parents); /* Inserido no que vem antes */
		insert(0, block, parents);
		ssprintf(syn_errormsg, "Expected a ')'");
	}
#line 4809 "sintatico.tab.c"
    break;

  case 47: /* declr_fntail: error '{' $@16 cmds '}'  */
#line 418 "sintatico.y"
                   {
		removeAt(0, parents);
	}
#line 4817 "sintatico.tab.c"
    break;

  case 48: /* $@17: %empty  */
#line 421 "sintatico.y"
                                {
		node_t err = create_node(ERR_TOKEN);
		node_t block = create_node(strdup("<block>"));
		add_child(err, block);
		add_child(block, ((node_t) parents->first->value)->parent);

		removeAt(0, parents); /* Inserido no que vem antes */
		insert(0, err, parents);
		ssprintf(syn_errormsg, "Expected a '{'");
	}
#line 4832 "sintatico.tab.c"
    break;

  case 49: /* declr_fntail: parlist ')' error ';' $@17 cmds '}'  */
#line 430 "sintatico.y"
                   {
		removeAt(0, parents);
	}
#line 4840 "sintatico.tab.c"
    break;

  case 51: /* @18: %empty  */
#line 436 "sintatico.y"
                  {
		(yyval.node) = create_node(strdup("<declr>"));
		add_child((yyvsp[-1].node), (yyval.node));
		add_child((yyvsp[0].node), (yyval.node));
		ADD_CONTEXT(VAR, FIRSTCHILD_VALUE((yyvsp[0].node)), FIRSTCHILD_VALUE((yyvsp[-1].node)));
		add_child((yyval.node), parents->first->value);
	}
#line 4852 "sintatico.tab.c"
    break;

  case 53: /* $@19: %empty  */
#line 444 "sintatico.y"
             { /* Missing type */
		add_child(create_node(ERR_TOKEN), parents->first->value);
		add_child((yyvsp[0].node), parents->first->value);
		YYERROR;
	}
#line 4862 "sintatico.tab.c"
    break;

  case 54: /* parlist: ID $@19 partail error  */
#line 448 "sintatico.y"
                        {
		ssprintf(syn_errormsg, "Expected a type for '%s'", FIRSTCHILD_VALUE((yyvsp[-3].node)));
	}
#line 4870 "sintatico.tab.c"
    break;

  case 55: /* $@20: %empty  */
#line 451 "sintatico.y"
               { /* Missing id */
		add_child((yyvsp[0].node), parents->first->value);
		add_child(create_node(ERR_TOKEN), parents->first->value);
		YYERROR;
	}
#line 4880 "sintatico.tab.c"
    break;

  case 56: /* parlist: TYPE $@20 partail error  */
#line 455 "sintatico.y"
                        {
		ssprintf(syn_errormsg, "Expected an identifier of type '%s'", FIRSTCHILD_VALUE((yyvsp[-3].node)));
	}
#line 4888 "sintatico.tab.c"
    break;

  case 58: /* partail: ',' TYPE ID partail  */
#line 461 "sintatico.y"
                              {
		(yyval.node) = create_node(strdup("<declr>"));
		add_child((yyvsp[-2].node), (yyval.node));
		add_child((yyvsp[-1].node), (yyval.node));
		ADD_CONTEXT(VAR, FIRSTCHILD_VALUE((yyvsp[-1].node)), FIRSTCHILD_VALUE((yyvsp[-2].node)));
		add_child((yyval.node), parents->first->value);
	}
#line 4900 "sintatico.tab.c"
    break;

  case 59: /* partail: TYPE ID partail  */
#line 469 "sintatico.y"
                          {
		(yyval.node) = create_node(strdup("<declr>"));
		add_child((yyvsp[-2].node), (yyval.node));
		add_child((yyvsp[-1].node), (yyval.node));
		ADD_CONTEXT(VAR, FIRSTCHILD_VALUE((yyvsp[-1].node)), FIRSTCHILD_VALUE((yyvsp[-2].node)));
		add_child((yyval.node), parents->first->value);
		ssprintf(syn_errormsg, "Expected a ','");
	}
#line 4913 "sintatico.tab.c"
    break;

  case 60: /* $@21: %empty  */
#line 479 "sintatico.y"
                         {
		node_t arg = create_node(strdup("<declr_init>"));
		add_child((yyvsp[-3].node), arg);
		add_child((yyvsp[-2].node), arg);
		add_child((yyvsp[0].node), arg);

		add_child(arg, parents->first->value);
		insert(0, arg, parents);
	}
#line 4927 "sintatico.tab.c"
    break;

  case 61: /* $@22: %empty  */
#line 487 "sintatico.y"
                       { /* TODO: Tem que poder fazer várias declarações sem iniciar */
		removeAt(0, parents);
	}
#line 4935 "sintatico.tab.c"
    break;

  case 63: /* $@23: %empty  */
#line 490 "sintatico.y"
                  {
		node_t arg = create_node(strdup("<declr>"));
		add_child((yyvsp[-1].node), arg);
		add_child((yyvsp[0].node), arg);

		add_child(arg, parents->first->value);
		insert(0, arg, parents);
	}
#line 4948 "sintatico.tab.c"
    break;

  case 64: /* $@24: %empty  */
#line 497 "sintatico.y"
                 {
		removeAt(0, parents);
	}
#line 4956 "sintatico.tab.c"
    break;

  case 66: /* $@25: %empty  */
#line 500 "sintatico.y"
              {
		add_child((yyvsp[0].node), parents->first->value);
	}
#line 4964 "sintatico.tab.c"
    break;

  case 68: /* forargs: fortail fortail  */
#line 503 "sintatico.y"
                          {
		node_t exp = create_node(strdup("<emptyexp>"));
		exp->parent = parents->first->value;
		insert(0, exp, parents->first->value);
	}
#line 4974 "sintatico.tab.c"
    break;

  case 70: /* fordeclrlist: ',' ID '=' exp fordeclrlist  */
#line 511 "sintatico.y"
                                      {
		add_child((yyvsp[-3].node), parents->first->value);
		add_child((yyvsp[-1].node), parents->first->value);
	}
#line 4983 "sintatico.tab.c"
    break;

  case 71: /* fortail: ';' exp  */
#line 517 "sintatico.y"
                 {
		add_child((yyvsp[0].node), parents->first->value);
	}
#line 4991 "sintatico.tab.c"
    break;

  case 72: /* fortail: ';'  */
#line 520 "sintatico.y"
              {
		add_child(create_node(strdup("<emptyexp>")), parents->first->value);
	}
#line 4999 "sintatico.tab.c"
    break;

  case 74: /* $@26: %empty  */
#line 526 "sintatico.y"
                 {
		add_child((yyvsp[0].node), parents->first->value);
	}
#line 5007 "sintatico.tab.c"
    break;

  case 76: /* $@27: %empty  */
#line 529 "sintatico.y"
                    {
		add_child(create_node(ERR_TOKEN), parents->first->value);
		ssprintf(syn_errormsg, "Expected an indentifier");
	}
#line 5016 "sintatico.tab.c"
    break;

  case 78: /* exp: INT  */
#line 535 "sintatico.y"
             { add_child((yyvsp[0].node), ((yyval.node) = create_node(strdup("<int>"))));    }
#line 5022 "sintatico.tab.c"
    break;

  case 79: /* exp: FLOAT  */
#line 536 "sintatico.y"
                 { add_child((yyvsp[0].node), ((yyval.node) = create_node(strdup("<float>"))));  }
#line 5028 "sintatico.tab.c"
    break;

  case 80: /* exp: EMPTY  */
#line 537 "sintatico.y"
                 { (yyval.node) = create_node(strdup("<empty>"));                   }
#line 5034 "sintatico.tab.c"
    break;

  case 81: /* exp: STRING  */
#line 538 "sintatico.y"
                 { add_child((yyvsp[0].node), ((yyval.node) = create_node(strdup("<string>")))); }
#line 5040 "sintatico.tab.c"
    break;

  case 82: /* exp: CHAR  */
#line 539 "sintatico.y"
                 { add_child((yyvsp[0].node), ((yyval.node) = create_node(strdup("<char>"))));   }
#line 5046 "sintatico.tab.c"
    break;

  case 83: /* exp: ID  */
#line 540 "sintatico.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 5052 "sintatico.tab.c"
    break;

  case 84: /* exp: ID OPPOS  */
#line 541 "sintatico.y"
                   {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<oppos>"));
		add_child((yyvsp[0].node), op);
		add_child((yyvsp[-1].node), exp);
		add_child(op, exp);
		(yyval.node) = exp;
	}
#line 5065 "sintatico.tab.c"
    break;

  case 85: /* exp: '*' exp  */
#line 549 "sintatico.y"
                              { ADD_UNI_EXP((yyval.node), (yyvsp[-1].node), (yyvsp[0].node));     }
#line 5071 "sintatico.tab.c"
    break;

  case 86: /* exp: '+' exp  */
#line 550 "sintatico.y"
                              { ADD_UNI_EXP((yyval.node), (yyvsp[-1].node), (yyvsp[0].node));     }
#line 5077 "sintatico.tab.c"
    break;

  case 87: /* exp: '-' exp  */
#line 551 "sintatico.y"
                              { ADD_UNI_EXP((yyval.node), (yyvsp[-1].node), (yyvsp[0].node));     }
#line 5083 "sintatico.tab.c"
    break;

  case 88: /* exp: '!' exp  */
#line 552 "sintatico.y"
                              { ADD_UNI_EXP((yyval.node), (yyvsp[-1].node), (yyvsp[0].node));     }
#line 5089 "sintatico.tab.c"
    break;

  case 89: /* exp: '~' exp  */
#line 553 "sintatico.y"
                              { ADD_UNI_EXP((yyval.node), (yyvsp[-1].node), (yyvsp[0].node));     }
#line 5095 "sintatico.tab.c"
    break;

  case 90: /* exp: '&' exp  */
#line 554 "sintatico.y"
                              { ADD_UNI_EXP((yyval.node), (yyvsp[-1].node), (yyvsp[0].node));     }
#line 5101 "sintatico.tab.c"
    break;

  case 91: /* exp: OPUNI exp  */
#line 555 "sintatico.y"
                              { ADD_UNI_EXP((yyval.node), (yyvsp[-1].node), (yyvsp[0].node));     }
#line 5107 "sintatico.tab.c"
    break;

  case 92: /* exp: exp '*' exp  */
#line 556 "sintatico.y"
                              { ADD_BIN_EXP((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 5113 "sintatico.tab.c"
    break;

  case 93: /* exp: exp '/' exp  */
#line 557 "sintatico.y"
                              { ADD_BIN_EXP((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 5119 "sintatico.tab.c"
    break;

  case 94: /* exp: exp '%' exp  */
#line 558 "sintatico.y"
                              { ADD_BIN_EXP((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 5125 "sintatico.tab.c"
    break;

  case 95: /* exp: exp '+' exp  */
#line 559 "sintatico.y"
                              { ADD_BIN_EXP((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 5131 "sintatico.tab.c"
    break;

  case 96: /* exp: exp '-' exp  */
#line 560 "sintatico.y"
                              { ADD_BIN_EXP((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 5137 "sintatico.tab.c"
    break;

  case 97: /* exp: exp IN exp  */
#line 561 "sintatico.y"
                              { ADD_BIN_EXP((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 5143 "sintatico.tab.c"
    break;

  case 98: /* exp: exp OPBIN1 exp  */
#line 562 "sintatico.y"
                              { ADD_BIN_EXP((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 5149 "sintatico.tab.c"
    break;

  case 99: /* exp: exp OPBIN2 exp  */
#line 563 "sintatico.y"
                              { ADD_BIN_EXP((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 5155 "sintatico.tab.c"
    break;

  case 100: /* exp: exp OPBIN3 exp  */
#line 564 "sintatico.y"
                              { ADD_BIN_EXP((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 5161 "sintatico.tab.c"
    break;

  case 101: /* exp: exp OPBIN4 exp  */
#line 565 "sintatico.y"
                              { ADD_BIN_EXP((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 5167 "sintatico.tab.c"
    break;

  case 102: /* exp: exp OPBIN5 exp  */
#line 566 "sintatico.y"
                              { ADD_BIN_EXP((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 5173 "sintatico.tab.c"
    break;

  case 103: /* exp: exp OPBIN6 exp  */
#line 567 "sintatico.y"
                              { ADD_BIN_EXP((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 5179 "sintatico.tab.c"
    break;

  case 104: /* exp: exp OPBIN7 exp  */
#line 568 "sintatico.y"
                              { ADD_BIN_EXP((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 5185 "sintatico.tab.c"
    break;

  case 105: /* exp: exp '?' exp ':' exp  */
#line 569 "sintatico.y"
                              {
		node_t exp = create_node(strdup("<exp>"));
		node_t op1 = create_node(strdup("<opter>"));
		node_t op2 = create_node(strdup("<opter>"));
		add_child((yyvsp[-3].node), op1);
		add_child((yyvsp[-1].node), op2);
		add_child((yyvsp[-4].node), exp);
		add_child(op1, exp);
		add_child((yyvsp[-2].node), exp);
		add_child(op2, exp);
		add_child((yyvsp[0].node), exp);
		(yyval.node) = exp;
	}
#line 5203 "sintatico.tab.c"
    break;

  case 106: /* exp: ID OPASSIGN exp  */
#line 582 "sintatico.y"
                          {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opassign>"));
		add_child((yyvsp[-1].node), op);
		add_child((yyvsp[-2].node), exp);
		add_child(op, exp);
		add_child((yyvsp[0].node), exp);
		(yyval.node) = exp;
	}
#line 5217 "sintatico.tab.c"
    break;

  case 107: /* @28: %empty  */
#line 591 "sintatico.y"
             {
		(yyval.node) = create_node(strdup("<fn>"));
		add_child((yyvsp[0].node), (yyval.node));
		insert(0, (yyval.node), parents);
	}
#line 5227 "sintatico.tab.c"
    break;

  case 108: /* exp: ID @28 fntail  */
#line 595 "sintatico.y"
                 {
		(yyval.node) = (yyvsp[-1].node);
		removeAt(0, parents);
	}
#line 5236 "sintatico.tab.c"
    break;

  case 109: /* exp: '(' exp ')'  */
#line 599 "sintatico.y"
                      { add_child((yyvsp[-1].node), ((yyval.node) = create_node(strdup("<exp>")))); }
#line 5242 "sintatico.tab.c"
    break;

  case 110: /* exp: exp '*' error  */
#line 601 "sintatico.y"
                           { ADD_BIN_EXP_ERR((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 5248 "sintatico.tab.c"
    break;

  case 111: /* exp: exp '/' error  */
#line 602 "sintatico.y"
                           { ADD_BIN_EXP_ERR((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 5254 "sintatico.tab.c"
    break;

  case 112: /* exp: exp '%' error  */
#line 603 "sintatico.y"
                           { ADD_BIN_EXP_ERR((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 5260 "sintatico.tab.c"
    break;

  case 113: /* exp: exp '+' error  */
#line 604 "sintatico.y"
                           { ADD_BIN_EXP_ERR((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 5266 "sintatico.tab.c"
    break;

  case 114: /* exp: exp '-' error  */
#line 605 "sintatico.y"
                           { ADD_BIN_EXP_ERR((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 5272 "sintatico.tab.c"
    break;

  case 115: /* exp: exp OPBIN1 error  */
#line 606 "sintatico.y"
                           { ADD_BIN_EXP_ERR((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 5278 "sintatico.tab.c"
    break;

  case 116: /* exp: exp OPBIN2 error  */
#line 607 "sintatico.y"
                           { ADD_BIN_EXP_ERR((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 5284 "sintatico.tab.c"
    break;

  case 117: /* exp: exp OPBIN3 error  */
#line 608 "sintatico.y"
                           { ADD_BIN_EXP_ERR((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 5290 "sintatico.tab.c"
    break;

  case 118: /* exp: exp OPBIN4 error  */
#line 609 "sintatico.y"
                           { ADD_BIN_EXP_ERR((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 5296 "sintatico.tab.c"
    break;

  case 119: /* exp: exp OPBIN5 error  */
#line 610 "sintatico.y"
                           { ADD_BIN_EXP_ERR((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 5302 "sintatico.tab.c"
    break;

  case 120: /* exp: exp OPBIN6 error  */
#line 611 "sintatico.y"
                           { ADD_BIN_EXP_ERR((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 5308 "sintatico.tab.c"
    break;

  case 121: /* exp: exp OPBIN7 error  */
#line 612 "sintatico.y"
                           { ADD_BIN_EXP_ERR((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 5314 "sintatico.tab.c"
    break;

  case 122: /* exp: exp OPBIN8 error  */
#line 613 "sintatico.y"
                           { ADD_BIN_EXP_ERR((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 5320 "sintatico.tab.c"
    break;

  case 123: /* exp: ID OPASSIGN error  */
#line 614 "sintatico.y"
                            {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opassign>"));
		add_child((yyvsp[-1].node), op);
		add_child((yyvsp[-2].node), exp);
		add_child(op, exp);
		node_t err = create_node(ERR_TOKEN);
		add_child(err, exp);
		(yyval.node) = exp;
		ssprintf(
			syn_errormsg,
			"Expected expression in '%s %s'",
			FIRSTCHILD_VALUE((yyvsp[-2].node)),
			(yyvsp[-1].node)->value
			);
	}
#line 5341 "sintatico.tab.c"
    break;

  case 125: /* fntail: '(' arglist error  */
#line 633 "sintatico.y"
                            { ssprintf(syn_errormsg, "Expected ')'"); }
#line 5347 "sintatico.tab.c"
    break;

  case 127: /* arglist: exp argtail  */
#line 637 "sintatico.y"
                      { add_child((yyvsp[-1].node), parents->first->value); }
#line 5353 "sintatico.tab.c"
    break;

  case 129: /* argtail: ',' exp argtail  */
#line 641 "sintatico.y"
                          { add_child((yyvsp[-1].node), parents->first->value); }
#line 5359 "sintatico.tab.c"
    break;


#line 5363 "sintatico.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (max, childrenCount, YY_("syntax error"));
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
                      yytoken, &yylval, max, childrenCount);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, max, childrenCount);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

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


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (max, childrenCount, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, max, childrenCount);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, max, childrenCount);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 644 "sintatico.y"


int yyerror(int *max, int *childrenCount, char *s) {
	if (*syn_errormsg) {
		fprintf(stderr, ERR_TEMPLATE, syn_errormsg);
	}
	fprintf(stderr, ERR_LOCATION, filename, lnum, lcol);
	*syn_errormsg = '\0';
	return 0;
}

void ssprintf(char *target, char *template, ...) {
	va_list ap;
	va_start(ap, template);
	vsnprintf(target, NAMESIZE, template, ap);
	va_end(ap);
}

void print(node_t node, void *data) {
	printData_t *dataSt = data;
	int *childrenCount = dataSt->childrenCount;

	int l = level(node);
	childrenCount[l - 1] = node->children->size;
	int isLast = 1;
	if (node->parent != NULL) {
		int idx = indexOf(node, node->parent->children);
		isLast = idx < 0 || idx == node->parent->children->size - 1;
	}
	if (isLast) {
		childrenCount[l - 1] = 0;
	}

	for (int i = 0; i < l - 1; i++) {
		printf("%s ", childrenCount[i] ? TREECHILD : " ");
	}
	if (l > 1) {
		printf(
			"%s" TREEBRANCH "%s" TREEBRANCH TREELEAF " ",
			!isLast ? TREECHILDMID : TREECHILDLAST,
			node->children->size ? TREECHILDFIRST : TREEBRANCH
			);
	}
	printf("%s",
		node->children->size > 0 && node->parent != NULL ?
			TREEROOTCOLOR :
			TREELEAFCOLOR
		);
	dataSt->val_print(node);
	printf("\033[0m\n");
}

void print_syntatic(node_t node) {
	printf("%s", (char *) node->value);
}

void print_context(node_t node) {
	elem_t it = ((list_t) node->value)->first;
	for (; it != NULL; it = it->next) {
		printf("%s%s", (char *) it->value, it->next != NULL ? ", " : "");
	}
}

void max_level(node_t node, void *data) {
	int *max = (int *) data;
	int l = level(node);
	if (*max < l) *max = l;
}

void free_values(node_t node, void *data) {
	if (strcmp(node->value, ERR_TOKEN) && strcmp(node->value, filename)) {
		free(node->value);
	}
}

void free_context(node_t node, void *data) {
	elem_t it = ((list_t) node->value)->first;
	for (; it != NULL; it = it->next) {
		free(it->value);
	}
	delete_list(node->value);
}

int main(int argc, char **argv) {
	if (argc < 2) {
		fprintf(stderr, "No input file\n");
		exit(EXIT_FAILURE);
	}

	/** ============= Inicializando valores ================ **/
	strncpy(filename, argv[1], FILENAMESIZE);               /**/
	root = create_node(filename);                           /**/
	context = create_node(create_list());                   /**/
	current_context = context;                              /**/
	parents = create_list();                                /**/
	int max = 0, *childrenCount = NULL;                     /**/
                                                            /**/
	yyin = fopen(argv[1], "r");                             /**/
	insert(0, root, parents);                               /**/
	/** ==================================================== **/

	int ret;
	if ((ret = yyparse(&max, childrenCount))) {
		fprintf(stderr, "Unhandled error while parsing\n");
	}

	if (*syn_errormsg) {
		fprintf(stderr, ERR_TEMPLATE, syn_errormsg);
	}

	/** ============== Finalizando valores ================= **/
	removeAt(0, parents);                                   /**/
                                                            /**/
		/* Pega a profundidade da árvore */                 /**/
	depth_pre(max_level, context, &max, NULL, NULL);        /**/
	childrenCount = (int *) calloc(max, sizeof(int));       /**/
		/* Imprime contextos */                             /**/
	printf("Árvore de contextos / Tabela de símbolos\n");   /**/
	printData_t ctx_data = {childrenCount, print_context};  /**/
	depth_pre(print, context, &ctx_data, NULL, NULL);       /**/
	free(childrenCount);                                    /**/
	/* Limpa o contexto */                                  /**/
	depth_pos(free_context, context, NULL, NULL, NULL);     /**/
	delete_node(context);                                   /**/
                                                            /**/
		/* Sublinha o nome do arquivo */                    /**/
                                                            /**/
	/* sprintf(              */                             /**/
	/*  root->value,         */                             /**/
	/*  "\033[4m%s\033[0m",  */                             /**/
	/*  (char *) root->value */                             /**/
	/* );                    */                             /**/
                                                            /**/
		/* Pega a profundidade da árvore */                 /**/
	depth_pre(max_level, root, &max, NULL, NULL);           /**/
	childrenCount = (int *) calloc(max, sizeof(int));       /**/
		/* Imprime a árvore sintática */                    /**/
	printf("Árvore sintática abstrata\n");                  /**/
	printData_t syn_data = {childrenCount, print_syntatic}; /**/
	depth_pre(print, root, &syn_data, NULL, NULL);          /**/
	free(childrenCount);                                    /**/
		/* Limpa a árvore sintática */                      /**/
	depth_pos(free_values, root, NULL, NULL, NULL);         /**/
	delete_node(root);                                      /**/
	delete_list(parents);                                   /**/
                                                            /**/
		/* Limpa coisas do flex */                          /**/
	fclose(yyin);                                           /**/
	yylex_destroy();                                        /**/
	/** ==================================================== **/

	return ret;
}
