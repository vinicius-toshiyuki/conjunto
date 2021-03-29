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
  YYSYMBOL_cmds = 47,                      /* cmds  */
  YYSYMBOL_48_1 = 48,                      /* $@1  */
  YYSYMBOL_cmdstail = 49,                  /* cmdstail  */
  YYSYMBOL_50_2 = 50,                      /* $@2  */
  YYSYMBOL_cmd = 51,                       /* cmd  */
  YYSYMBOL_52_3 = 52,                      /* @3  */
  YYSYMBOL_53_4 = 53,                      /* $@4  */
  YYSYMBOL_54_5 = 54,                      /* $@5  */
  YYSYMBOL_55_6 = 55,                      /* @6  */
  YYSYMBOL_56_7 = 56,                      /* @7  */
  YYSYMBOL_57_8 = 57,                      /* @8  */
  YYSYMBOL_58_9 = 58,                      /* $@9  */
  YYSYMBOL_59_10 = 59,                     /* @10  */
  YYSYMBOL_60_11 = 60,                     /* @11  */
  YYSYMBOL_61_12 = 61,                     /* $@12  */
  YYSYMBOL_declr_fntail = 62,              /* declr_fntail  */
  YYSYMBOL_63_13 = 63,                     /* $@13  */
  YYSYMBOL_64_14 = 64,                     /* $@14  */
  YYSYMBOL_65_15 = 65,                     /* $@15  */
  YYSYMBOL_parlist = 66,                   /* parlist  */
  YYSYMBOL_67_16 = 67,                     /* @16  */
  YYSYMBOL_68_17 = 68,                     /* $@17  */
  YYSYMBOL_69_18 = 69,                     /* $@18  */
  YYSYMBOL_partail = 70,                   /* partail  */
  YYSYMBOL_forargs = 71,                   /* forargs  */
  YYSYMBOL_72_19 = 72,                     /* $@19  */
  YYSYMBOL_73_20 = 73,                     /* $@20  */
  YYSYMBOL_74_21 = 74,                     /* $@21  */
  YYSYMBOL_75_22 = 75,                     /* $@22  */
  YYSYMBOL_76_23 = 76,                     /* $@23  */
  YYSYMBOL_fordeclrlist = 77,              /* fordeclrlist  */
  YYSYMBOL_fortail = 78,                   /* fortail  */
  YYSYMBOL_idlist = 79,                    /* idlist  */
  YYSYMBOL_80_24 = 80,                     /* $@24  */
  YYSYMBOL_81_25 = 81,                     /* $@25  */
  YYSYMBOL_exp = 82,                       /* exp  */
  YYSYMBOL_83_26 = 83,                     /* @26  */
  YYSYMBOL_fntail = 84,                    /* fntail  */
  YYSYMBOL_arglist = 85,                   /* arglist  */
  YYSYMBOL_argtail = 86                    /* argtail  */
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
#define YYFINAL  48
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   15657

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  122
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  811

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
     285,   288,   288,   298,   298,   313,   319,   326,   332,   338,
     343,   348,   343,   359,   368,   374,   359,   384,   384,   393,
     393,   405,   405,   419,   420,   420,   428,   428,   435,   435,
     444,   445,   453,   463,   471,   463,   474,   481,   474,   484,
     484,   487,   494,   495,   501,   504,   509,   510,   510,   513,
     513,   519,   520,   521,   522,   523,   524,   525,   533,   534,
     535,   536,   537,   538,   539,   540,   541,   542,   543,   544,
     545,   546,   547,   548,   549,   550,   551,   552,   553,   566,
     575,   575,   583,   585,   586,   587,   588,   589,   590,   591,
     592,   593,   594,   595,   596,   597,   598,   616,   617,   620,
     621,   624,   625
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
  "';'", "'{'", "'}'", "','", "'='", "$accept", "prog", "cmds", "$@1",
  "cmdstail", "$@2", "cmd", "@3", "$@4", "$@5", "@6", "@7", "@8", "$@9",
  "@10", "@11", "$@12", "declr_fntail", "$@13", "$@14", "$@15", "parlist",
  "@16", "$@17", "$@18", "partail", "forargs", "$@19", "$@20", "$@21",
  "$@22", "$@23", "fordeclrlist", "fortail", "idlist", "$@24", "$@25",
  "exp", "@26", "fntail", "arglist", "argtail", YY_NULLPTR
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

#define YYPACT_NINF (-727)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-123)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    3197, 10846, 10875, 10904, 10933, 10816,   188,   727,   727,   727,
     727,   727,   727,   727,   -16,    -4,    -2,    12,   397, 10962,
    9143,  3236,    80,   100,  3275,    51, 10991, 11020,  6247,    58,
      79,    20,    63,    66, 11049, 11078, 11107, 11136, 11165, 11194,
   11223,  6283,  6319,  6355,   112,    84, 11252, 12498,  -727,  3314,
    4974,   727,  6391,  6427,  6463,  6499,  6535,  6571,  6607,   135,
    6643,  6679,  6715,  6751,  6787,  9169,  3353, 11281, 11310,   658,
   11339,   107,    83,   243,   291,   170,   111,   126, 12526,   128,
   12554,   137, 12582,  6209,  3392,  3431, 11368,   186,  3470,   159,
   11397, 11426, 11455, 11484, 11513, 11542, 11571, 11600, 11629, 11658,
   11687, 11716, 11745, 11774, 11803, 11832, 11861, 11890, 11919, 11948,
   11977, 12006, 12035, 12064, 12093, 12122, 14320,   503,    98,   163,
     172,    83,    83,    77,    96,   182,   210,  6014,  6014,  6053,
    6053,  6053,  6053,   216,   456,   194,   220, 12151,  3314,  3509,
     727,  9195,   106, 12180, 12209,   201,  3548,   222,  3587,   227,
     231,   101,   191,   101,   244,   271,  2300,  2339,  3626,  3665,
    3704,  3743,   219, 12238,  6092,   266,   280,   327, 12267,   503,
    5014,    47,   322,   331,   341,   332,   342,   310,  3782,  6053,
    6053,  9221,    83,  6053,   220,   109,  4974,   321,  5054,   101,
     371,   340,   343,   344,  4974,  3821,  3860,  9280,   345,  3899,
     347,   338,  5094,  4974,   380,   101,   349,   295,   280,  3938,
    4974,   350,   383,   388,   386,   354,   220,   353,  3977,   396,
     355,   280,   367,  4016,  4055,  9221,   220,  9312,   368,   373,
   12610, 12638, 12666, 12694, 12470,  9143,  9143,  9143,  9143,  9143,
    9143,  9143, 12722,  9143,  9143,  6823,  6859,  6895,  6931,  6967,
    7003,  7039,   413,  7075,  7111,  7147,  7183,  7219,  9169,   189,
     377,   378,   379,    12,  7255,  5134,  5174,   381, 12296, 14346,
   14372, 14398, 14424, 14290,  9169,  9169,  9169,  9169,  9169,  9169,
    9169, 14450,  9143,   800,   836,   869,   902,   432,  9195,  9195,
    9195,  9195,  9195,  9195,  9195,   945,  9143,  9169,  7291,  7327,
    7363,  7399,  7435,  7471,  7507,   425,  7543,  7579,  7615,  7651,
    7687,  9169,  9195,  7723,  7759,  7795,  7831,  7867,  7903,  7939,
     426,  7975,  8011,  8047,  8083,  8119,  9169,   330,   390,   391,
     393,    12,  8155,  2378,   398, 12325,  9117,   427,   429,  9344,
    9376,  9408,  9440,  9248,  9221,  9221,  9221,  9221,  9221,  9221,
    9221,  9472,  9143,  9221,  8191,  8227,  8263,  8299,  8335,  8371,
    8407,   437,  8443,  8479,  8515,  8551,  8587,  9169, 12750,  8623,
     405, 12778, 12806, 12834, 12862, 12890, 12918, 12946, 12974, 13002,
   13030, 13058, 13086, 13114, 13142, 13170, 13198, 13226, 13254, 13282,
   13310, 13338, 13366, 13394, 13422, 13450, 13478, 13506, 13534, 13562,
   13590, 13618, 13646, 13674, 13702, 14476,   154,   420,    66,  8659,
    8695,  8731,   428,   433, 12354,  5214,  4974,  5254, 14502,  8767,
     431, 14528, 14554, 14580, 14606, 14632, 14658, 14684, 13730,   994,
    8803,   434,  1026,  1058,  1090,  1122,  1154,  1186,  1218, 13758,
   14710, 14736, 14762, 14788, 14814, 14840, 14866, 14892, 14918, 14944,
   14970, 14996, 15022, 15048, 15074, 15100, 15126, 15152, 15178, 15204,
   15230, 15256, 15282, 15308, 15334, 15360, 15386,  1250,  1282,  1314,
    1346,  1378,  1410,  1442,  1474,  1506,  1538,  1570,  1602,  1634,
    1666,  1698,  1730,  1762,  1794,  1826,  1858,  1890,  1922,  1954,
    1986,  2018,  2050, 15412,   230,   436,    66,  8839,  8875,  8911,
     438,   445, 12383,  4974,  2417, 13786,   332,   471,  9504,  8947,
     449,  9536,  9568,  9600,  9632,  9664,  9696,  9728, 13814,  9760,
    9792,  9824,  9856,  9888,  9920,  9952,  9984, 10016, 10048, 10080,
   10112, 10144, 10176, 10208, 10240, 10272, 10304, 10336, 10368, 10400,
   10432, 10464, 10496, 10528, 10560, 15438, 13842, 13870,   658, 13898,
   13926,  9143,   107,    83,   170,   448,   450, 13954,   451, 13982,
     453, 14010,  6209,  5294,  5334,   458,  5374,   459, 15464, 15490,
     658, 15516, 15542,  2082,  2114,   658,  2146,  2178,  9169,  9195,
     107,    83,   170,   455,   454, 14038,   463, 14066,   466, 14094,
    6209,  2456,  2495,   464,   468,   332, 10592, 10624,   658, 10656,
   10688,  9221,   120, 14122,   167,   470,   469,   210,  6131,  6131,
    6170,  6170,  6170,  6170,   472,  5214,  5414,   148,   168, 15568,
    2210,   181,   474,   484,   210,  6014,  6014,  6014,  6014,  6014,
    6014,   496,  2534,   497,   171, 10720, 14150, 14178,   499,  5454,
     504,  5494,   244,   537,   334,   506,   507,   525,    12,  8983,
     526,  4094,   524, 12412,  4134,  5534,  5574,  5614,  5654,  6092,
     527, 15594, 15620,  2242,  2274,   530,  2573,   533,  2612,   244,
     572,  2651,  2690,  2729,  2768,  2807,  2846,  6092, 10752, 10784,
    5014,    70,   535,  5694,   290,   536,    66,  9019,  9055,  9091,
     539,   540, 12441,  6170,  4974,  4174,  6170,  6170,  5014,    71,
     541,  2885,  6014,  6014,  6014,  4974,   543,  5054,  4974,   107,
      83,   170,   544,   542, 14206,   546, 14234,   547, 14262,  6209,
    4214,  4254,  5734,   545,  5774,  5814,  4974,   548,  5054,  4974,
    2924,  2963,  3002,   549,  5094,  4974,   550,   183,   554,   556,
     210,  6131,  6131,  6131,  6131,  6131,  6131,   557,  4294,   555,
    5094,  4974,   558,  5854,  4974,   560,   388,   562,  4334,   566,
    4374,   244,   588,  4414,  4454,  4494,  4534,  4574,  4614,  6092,
    3041,  4974,   564,   388,   565,  5894,   598,  5014,    92,   569,
    4654,  6131,  6131,  6131,   570,  3080,   610,  5934,  5974,  4974,
     573,  5054,  4974,  4694,  4734,  4774,  3119,  3158,   574,  5094,
    4974,   575,  4814,  4974,   578,   388,   579,  4854,   613,  4894,
    4934
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,     0,
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
       0
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -727,  -727,   202,   356,  -134,    49,    25,  -261,  -644,    86,
    -400,  -549,  -391,  -578,  -254,  -603,  -726,  -537,  -693,  -661,
    -710,  -118,  -727,  -727,  -727,  -130,  -546,  -727,  -727,  -727,
    -727,  -727,   404,   -23,   -40,  -727,  -727,     0,  -196,  -344,
    -480,   473
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    22,    23,    49,    87,   138,   266,    44,   183,   267,
      72,   119,    76,   155,    32,   177,   219,   146,   203,   186,
     210,   125,   175,   151,   153,   174,   135,   207,   221,   182,
     208,   166,   215,   136,    33,   122,   121,   268,    29,    70,
     118,   142
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      26,   147,   412,   604,   167,   407,   553,    34,    35,    36,
      37,    38,    39,    40,   735,   697,   614,   555,    46,   705,
      47,    73,    41,   176,   754,    24,   549,    74,    68,   643,
     776,   621,   120,   704,    42,   751,    43,   726,   370,   682,
     771,    78,    80,    82,   631,   192,   670,   786,   187,    26,
     -13,    90,    92,    94,    96,    98,   100,   102,   104,   204,
     107,   109,   111,   113,   115,   116,   700,   639,   602,   117,
     500,   706,   727,   495,    88,   212,   571,   420,   -46,   808,
      48,   149,   150,   137,   666,   -46,    25,   576,   188,   803,
     617,   431,    50,   790,   581,   618,    69,   -48,   800,   143,
      -2,    75,   -50,   152,   -48,   583,   -30,  -120,   -23,   172,
    -122,   707,   728,   165,   -23,   -23,   789,    71,   634,   -21,
     -46,   636,   -21,   -66,    84,   783,    31,   335,   335,    26,
      26,    26,    26,   791,   163,    25,   105,   144,    26,   -48,
     168,   169,   198,   184,   173,  -120,   -23,   510,  -122,   661,
      83,   126,   156,   157,   158,   159,   160,   161,   779,   637,
     737,   200,   762,    88,   145,   127,   599,   129,   638,   663,
     123,   124,   678,   747,   123,   124,   131,   123,   124,    26,
      26,   197,   665,    26,   757,   216,    -5,   662,   123,   124,
     123,   124,   552,   222,   -21,    30,   406,   -21,   226,   -44,
     758,   139,   -43,   228,   195,   196,   -43,   664,   199,   -43,
     679,   -31,   148,   334,   334,    25,    25,    25,    25,   408,
     -43,   154,   -43,   162,    25,   227,   -33,   -33,   -66,   -66,
     -44,    31,    31,   164,   -44,   371,   372,   373,   374,   375,
     376,   377,   170,   378,   379,   381,   383,   385,   387,   389,
     391,   393,    89,   396,   398,   400,   402,   404,   405,   -56,
     336,   171,   -56,   181,   414,    25,    25,   -70,   580,    25,
     -21,   -68,   178,   -21,   421,   422,   423,   424,   425,   426,
     427,   565,   428,   -69,   710,   -34,   -69,   496,   432,   433,
     434,   435,   436,   437,   438,   712,   439,   440,   442,   444,
     446,   448,   450,   452,   454,   -61,   457,   459,   461,   463,
     465,   466,   467,   469,   471,   473,   475,   477,   479,   481,
     134,   484,   486,   488,   490,   492,   493,    -8,   709,   189,
     -21,   -67,   502,   -21,   -67,   -62,   505,   494,   214,   190,
     337,   684,   191,   193,   511,   512,   513,   514,   515,   516,
     517,   194,   518,   519,   521,   523,   525,   527,   529,   531,
     533,   202,   536,   538,   540,   542,   544,   545,   -33,   547,
     -66,   -50,   -33,    31,   -66,   338,   594,    31,   205,   -47,
     209,   -52,   -45,   -49,   -51,   -57,   -60,   690,   201,   -35,
     685,   213,   218,   220,   -54,   223,   206,   224,    45,   225,
       1,     2,     3,     4,     5,   211,   -58,   -55,     7,   557,
     559,   561,   217,   -63,   394,   409,   410,   411,     8,   569,
       9,    10,   416,    11,    12,    13,   455,   482,   497,   498,
     574,   499,    19,   -76,   506,    20,   606,   507,   534,   503,
     566,   -76,   429,   548,   -76,   -76,   -76,   -76,   -76,   -76,
     -76,   -76,   430,   -76,   -76,   -76,   -76,   -76,   554,     1,
       2,     3,     4,     5,   623,   633,   562,     7,   -76,   570,
    -100,   -76,   575,   563,   582,   -76,   590,     8,   595,     9,
      10,   660,    11,    12,    13,   591,   640,   598,   607,   608,
     610,    19,   612,   625,    20,   624,   -65,   585,   587,   589,
      -5,   616,   627,   667,  -121,   629,   632,   -52,   642,   597,
     641,   659,   312,   605,   668,   313,   314,   315,   316,   317,
     318,   319,   320,   669,   321,   322,   323,   324,   325,   -20,
     -20,   -20,   -20,   -20,   -20,   677,   -51,   -20,   683,   326,
     680,   622,  -121,   681,   687,   688,   141,   -20,   117,   -20,
     -20,   603,   -20,   -20,   -20,   -20,   -20,   -20,   -20,   -20,
     -20,   -20,   137,   689,   -20,   694,   -20,   -20,   -20,    -8,
     117,   698,   699,   701,   711,   117,   708,   719,   619,   620,
     720,   741,   729,   734,   740,   743,   745,   748,   750,   780,
     137,   753,   756,   739,   760,   761,   769,   770,   117,   788,
     773,   635,   775,   777,   686,   778,   785,   787,   653,   653,
     792,   797,   796,   799,   810,   615,   802,   805,   567,   759,
     807,   809,   415,     0,     0,   335,   335,   335,   335,   335,
     335,   229,     0,   651,   654,   655,   656,   657,   658,     0,
     566,     0,   185,     0,     0,     0,     0,     0,     0,   692,
     671,   672,   673,   674,   675,   676,     0,     0,     0,  -119,
       0,   283,   284,   285,   286,   287,     0,     0,     0,   288,
     738,     0,     0,     0,     0,     0,     0,     0,     0,   289,
       0,   290,   291,     0,   292,   293,   294,   714,   716,   718,
       0,     0,     0,   295,   652,   652,   296,  -119,     0,     0,
       0,     0,   335,   335,   335,   593,     0,     0,     0,     0,
       0,   334,   334,   334,   334,   334,   334,     0,   722,   137,
       0,   724,   725,     0,     0,     0,     0,   730,   731,   732,
       1,     2,     3,     4,     5,     0,     0,     0,     7,     0,
       0,   653,   653,   653,   653,   653,   653,     0,     8,     0,
       9,    10,     0,    11,    12,    13,     0,     0,     0,     0,
       0,     0,    19,     0,     0,    20,   763,   764,   765,   766,
     767,   768,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   653,   653,   653,     0,     0,     0,     0,   334,   334,
     334,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -74,     0,     0,     0,     0,   793,   794,   795,   -74,
       0,     0,   -74,   -74,   -74,   -74,   -74,   -74,   -74,   -74,
       0,   -74,   -74,   -74,   -74,   -74,     0,   652,   652,   652,
     652,   652,   652,     0,     0,     0,   -74,   -75,     0,   -74,
       0,     0,     0,   -74,     0,   -75,     0,     0,   -75,   -75,
     -75,   -75,   -75,   -75,   -75,   -75,     0,   -75,   -75,   -75,
     -75,   -75,     0,     0,     0,     0,     0,   652,   652,   652,
     -71,     0,   -75,     0,     0,   -75,     0,     0,   -71,   -75,
       0,   -71,   -71,   -71,   -71,   -71,   -71,   -71,   -71,     0,
     -71,   -71,   -71,   -71,   -71,     0,   723,     0,     0,     0,
       0,     0,     0,   -72,     0,   -71,     0,   733,   -71,     0,
     736,   -72,   -71,     0,   -72,   -72,   -72,   -72,   -72,   -72,
     -72,   -72,     0,   -72,   -72,   -72,   -72,   -72,   749,     0,
       0,   752,     0,     0,     0,     0,     0,   755,   -72,     0,
       0,   -72,     0,     0,     0,   -72,   -73,     0,     0,     0,
       0,     0,     0,   772,   -73,     0,   774,   -73,   -73,   -73,
     -73,   -73,   -73,   -73,   -73,     0,   -73,   -73,   -73,   -73,
     -73,     0,     0,   784,     0,     0,     0,     0,     0,     0,
       0,   -73,     0,     0,   -73,     0,     0,     0,   -73,     0,
       0,   798,     0,     0,   801,   -77,     0,     0,     0,     0,
       0,     0,   804,   -77,     0,   806,   -77,   -77,   -77,   -77,
     -77,   -77,   -77,   -77,     0,   -77,   -77,   -77,   -77,   -77,
       0,     0,     0,     0,     0,     0,     0,   -84,     0,     0,
     -77,     0,     0,   -77,     0,   -84,     0,   -77,   -84,   -84,
     -84,   -84,   -84,   -84,   -84,   -84,     0,   -84,   -84,   -84,
     -84,   -84,     0,     0,     0,     0,     0,     0,     0,   -78,
       0,     0,   -84,     0,     0,   -84,     0,   -78,     0,   -84,
     -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,     0,   -78,
     -78,   -78,   -78,   -78,     0,     0,     0,     0,     0,     0,
       0,   -79,     0,     0,   -78,     0,     0,   -78,     0,   -79,
       0,   -78,   -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,
       0,   -79,   -79,   -79,   -79,   -79,     0,     0,     0,     0,
       0,     0,     0,   -80,     0,     0,   -79,     0,     0,   -79,
       0,   -80,     0,   -79,   -80,   -80,   -80,   -80,   -80,   -80,
     -80,   -80,     0,   -80,   -80,   -80,   -80,   -80,     0,     0,
       0,     0,     0,     0,     0,   -81,     0,     0,   -80,     0,
       0,   -80,     0,   -81,     0,   -80,   -81,   -81,   -81,   -81,
     -81,   -81,   -81,   -81,     0,   -81,   -81,   -81,   -81,   -81,
       0,     0,     0,     0,     0,     0,     0,   -82,     0,     0,
     -81,     0,     0,   -81,     0,   -82,     0,   -81,   -82,   -82,
     -82,   -82,   -82,   -82,   -82,   -82,     0,   -82,   -82,   -82,
     -82,   -82,     0,     0,     0,     0,     0,     0,     0,   -83,
       0,     0,   -82,     0,     0,   -82,     0,   -83,     0,   -82,
     -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,     0,   -83,
     -83,   -83,   -83,   -83,     0,     0,     0,     0,     0,     0,
       0,   -90,     0,     0,   -83,     0,     0,   -83,     0,   -90,
       0,   -83,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,
       0,   -90,   -90,   -90,   -90,   -90,     0,     0,     0,     0,
       0,     0,     0,  -108,     0,     0,   -90,     0,     0,   -90,
       0,  -108,     0,   -90,  -108,  -108,  -108,  -108,  -108,  -108,
    -108,  -108,     0,  -108,  -108,  -108,  -108,  -108,     0,     0,
       0,     0,     0,     0,     0,   -91,     0,     0,  -108,     0,
       0,  -108,     0,   312,     0,  -108,   -91,   -91,   -91,   -91,
     -91,   -91,   -91,   -91,     0,   321,   322,   323,   324,   325,
       0,     0,     0,     0,     0,     0,     0,  -109,     0,     0,
     -91,     0,     0,   -91,     0,  -109,     0,   -91,  -109,  -109,
    -109,  -109,  -109,  -109,  -109,  -109,     0,  -109,  -109,  -109,
    -109,  -109,     0,     0,     0,     0,     0,     0,     0,   -92,
       0,     0,  -109,     0,     0,  -109,     0,   312,     0,  -109,
     313,   -92,   -92,   -92,   -92,   -92,   -92,   -92,     0,   321,
     322,   323,   324,   325,     0,     0,     0,     0,     0,     0,
       0,  -110,     0,     0,   -92,     0,     0,   -92,     0,  -110,
       0,   -92,  -110,  -110,  -110,  -110,  -110,  -110,  -110,  -110,
       0,  -110,  -110,  -110,  -110,  -110,     0,     0,     0,     0,
       0,     0,     0,   -93,     0,     0,  -110,     0,     0,  -110,
       0,   312,     0,  -110,   313,   314,   -93,   -93,   -93,   -93,
     -93,   -93,     0,   321,   322,   323,   324,   325,     0,     0,
       0,     0,     0,     0,     0,  -111,     0,     0,   -93,     0,
       0,   -93,     0,  -111,     0,   -93,  -111,  -111,  -111,  -111,
    -111,  -111,  -111,  -111,     0,  -111,  -111,  -111,  -111,  -111,
       0,     0,     0,     0,     0,     0,     0,   -94,     0,     0,
    -111,     0,     0,  -111,     0,   312,     0,  -111,   313,   314,
     315,   -94,   -94,   -94,   -94,   -94,     0,   321,   322,   323,
     324,   325,     0,     0,     0,     0,     0,     0,     0,  -112,
       0,     0,   -94,     0,     0,   -94,     0,  -112,     0,   -94,
    -112,  -112,  -112,  -112,  -112,  -112,  -112,  -112,     0,  -112,
    -112,  -112,  -112,  -112,     0,     0,     0,     0,     0,     0,
       0,   -95,     0,     0,  -112,     0,     0,  -112,     0,   312,
       0,  -112,   313,   314,   315,   316,   -95,   -95,   -95,   -95,
       0,   321,   322,   323,   324,   325,     0,     0,     0,     0,
       0,     0,     0,  -113,     0,     0,   -95,     0,     0,   -95,
       0,  -113,     0,   -95,  -113,  -113,  -113,  -113,  -113,  -113,
    -113,  -113,     0,  -113,  -113,  -113,  -113,  -113,     0,     0,
       0,     0,     0,     0,     0,   -96,     0,     0,  -113,     0,
       0,  -113,     0,   312,     0,  -113,   313,   314,   315,   316,
     317,   -96,   -96,   -96,     0,   321,   322,   323,   324,   325,
       0,     0,     0,     0,     0,     0,     0,  -114,     0,     0,
     -96,     0,     0,   -96,     0,  -114,     0,   -96,  -114,  -114,
    -114,  -114,  -114,  -114,  -114,  -114,     0,  -114,  -114,  -114,
    -114,  -114,     0,     0,     0,     0,     0,     0,     0,   -97,
       0,     0,  -114,     0,     0,  -114,     0,   312,     0,  -114,
     313,   314,   315,   316,   317,   318,   -97,   -97,     0,   321,
     322,   323,   324,   325,     0,     0,     0,     0,     0,     0,
       0,  -115,     0,     0,   -97,     0,     0,   -97,     0,  -115,
       0,   -97,  -115,  -115,  -115,  -115,  -115,  -115,  -115,  -115,
       0,  -115,  -115,  -115,  -115,  -115,     0,     0,     0,     0,
       0,     0,     0,  -103,     0,     0,  -115,     0,     0,  -115,
       0,  -103,     0,  -115,  -103,  -103,  -103,  -103,  -103,  -103,
    -103,  -103,     0,  -103,  -103,  -103,  -103,  -103,     0,     0,
       0,     0,     0,     0,     0,   -85,     0,     0,  -103,     0,
       0,  -103,     0,   312,     0,  -103,   -85,   -85,   -85,   -85,
     -85,   -85,   -85,   -85,     0,   -85,   -85,   -85,   -85,   -85,
       0,     0,     0,     0,     0,     0,     0,  -104,     0,     0,
     -85,     0,     0,   -85,     0,  -104,     0,   -85,  -104,  -104,
    -104,  -104,  -104,  -104,  -104,  -104,     0,  -104,  -104,  -104,
    -104,  -104,     0,     0,     0,     0,     0,     0,     0,   -86,
       0,     0,  -104,     0,     0,  -104,     0,   312,     0,  -104,
     -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,     0,   -86,
     -86,   -86,   -86,   -86,     0,     0,     0,     0,     0,     0,
       0,  -106,     0,     0,   -86,     0,     0,   -86,     0,  -106,
       0,   -86,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,
       0,  -106,  -106,  -106,  -106,  -106,     0,     0,     0,     0,
       0,     0,     0,   -88,     0,     0,  -106,     0,     0,  -106,
       0,   312,     0,  -106,   -88,   -88,   -88,   -88,   -88,   -88,
     -88,   -88,     0,   321,   322,   -88,   -88,   325,     0,     0,
       0,     0,     0,     0,     0,  -107,     0,     0,   -88,     0,
       0,   -88,     0,  -107,     0,   -88,  -107,  -107,  -107,  -107,
    -107,  -107,  -107,  -107,     0,  -107,  -107,  -107,  -107,  -107,
       0,     0,     0,     0,     0,     0,     0,   -89,     0,     0,
    -107,     0,     0,  -107,     0,   312,     0,  -107,   -89,   -89,
     -89,   -89,   -89,   -89,   -89,   -89,     0,   321,   322,   -89,
     -89,   325,     0,     0,     0,     0,     0,     0,     0,  -105,
       0,     0,   -89,     0,     0,   -89,     0,  -105,     0,   -89,
    -105,  -105,  -105,  -105,  -105,  -105,  -105,  -105,     0,  -105,
    -105,  -105,  -105,  -105,     0,     0,     0,     0,     0,     0,
       0,   -87,     0,     0,  -105,     0,     0,  -105,     0,   312,
       0,  -105,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,
       0,   -87,   -87,   -87,   -87,   -87,     0,     0,     0,     0,
       0,     0,     0,  -116,     0,     0,   -87,     0,     0,   -87,
       0,  -116,     0,   -87,  -116,  -116,  -116,  -116,  -116,  -116,
    -116,  -116,     0,  -116,  -116,  -116,  -116,  -116,     0,     0,
       0,     0,     0,     0,     0,   -99,     0,     0,  -116,     0,
       0,  -116,     0,   312,     0,  -116,   313,   314,   315,   316,
     317,   318,   319,   320,     0,   321,   322,   323,   324,   325,
       0,     0,     0,     0,     0,     0,     0,  -101,     0,     0,
     326,     0,     0,   -99,     0,  -101,     0,   -99,  -101,  -101,
    -101,  -101,  -101,  -101,  -101,  -101,     0,  -101,  -101,  -101,
    -101,  -101,     0,     0,     0,     0,     0,     0,     0,  -102,
       0,     0,  -101,     0,     0,  -101,     0,  -102,     0,  -101,
    -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,     0,  -102,
    -102,  -102,  -102,  -102,     0,     0,     0,     0,     0,     0,
       0,   -98,     0,     0,  -102,     0,     0,  -102,     0,   312,
       0,  -102,   313,   314,   315,   316,   317,   318,   319,   320,
       0,   321,   322,   323,   324,   325,     0,     0,     0,     0,
       0,     0,     0,  -118,     0,     0,   326,     0,     0,   -98,
       0,  -118,     0,   -98,  -118,  -118,  -118,  -118,  -118,  -118,
    -118,  -118,     0,  -118,  -118,  -118,  -118,  -118,     0,     0,
       0,     0,     0,     0,     0,  -117,     0,     0,  -118,     0,
       0,  -118,     0,  -117,     0,  -118,  -117,  -117,  -117,  -117,
    -117,  -117,  -117,  -117,     0,  -117,  -117,  -117,  -117,  -117,
     -25,     0,     0,   -25,   -25,   -25,   -25,   -25,   -25,     0,
    -117,   -25,     0,  -117,     0,     0,     0,  -117,     0,     0,
       0,   -25,     0,   -25,   -25,     0,   -25,   -25,   -25,   -25,
     -25,   -25,   -25,   179,   -25,   -25,     0,     0,   -25,    -9,
     -25,   -25,    -9,    -9,    -9,    -9,    -9,    -9,     0,     0,
      -9,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      -9,     0,    -9,    -9,     0,    -9,    -9,    -9,    -9,    -9,
      -9,    -9,   180,    -9,    -9,     0,     0,    -9,   -20,    -9,
      -9,   -20,   -20,   -20,   -20,   -20,   -20,     0,     0,   -20,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -20,
       0,   -20,   -20,     0,   -20,   -20,   -20,   -20,   -20,   -20,
     -20,   -20,   -20,   -20,     0,     0,   -20,   -16,   -20,   -20,
     -16,   -16,   -16,   -16,   -16,   -16,     0,     0,   -16,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -16,     0,
     -16,   -16,     0,   -16,   -16,   -16,   -16,   -16,   -16,   -16,
     -16,   -16,   -16,     0,     0,   -16,   -29,   -16,   -16,   -29,
     -29,   -29,   -29,   -29,   -29,     0,     0,   -29,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -29,     0,   -29,
     -29,     0,   -29,   -29,   -29,   -29,   -29,   -29,   -29,   -29,
     -29,   -29,     0,     0,   -29,   -17,   -29,   -29,   -17,   -17,
     -17,   -17,   -17,   -17,     0,     0,   -17,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -17,     0,   -17,   -17,
       0,   -17,   -17,   -17,   -17,   -17,   -17,   -17,   -17,   -17,
     -17,     0,     0,   -17,   -19,   -17,   -17,   -19,   -19,   -19,
     -19,   -19,   -19,     0,     0,   -19,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -19,     0,   -19,   -19,     0,
     -19,   -19,   -19,   -19,   -19,   -19,   -19,   -19,   -19,   -19,
       0,     0,   -19,   -24,   -19,   -19,   -24,   -24,   -24,   -24,
     -24,   -24,     0,     0,   -24,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -24,     0,   -24,   -24,     0,   -24,
     -24,   -24,   -24,   -24,   -24,   -24,   -24,   -24,   -24,     0,
       0,   -24,   -22,   -24,   -24,   -22,   -22,   -22,   -22,   -22,
     -22,     0,     0,   -22,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -22,     0,   -22,   -22,     0,   -22,   -22,
     -22,   -22,   -22,   -22,   -22,   -22,   -22,   -22,     0,     0,
     -22,   -25,   -22,   -22,   -25,   -25,   -25,   -25,   -25,   -25,
       0,     0,   -25,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -25,     0,   -25,   -25,     0,   -25,   -25,   -25,
     -25,   -25,   -25,   -25,   702,   -25,   -25,     0,     0,   -25,
      -9,   -25,   -25,    -9,    -9,    -9,    -9,    -9,    -9,     0,
       0,    -9,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    -9,     0,    -9,    -9,     0,    -9,    -9,    -9,    -9,
      -9,    -9,    -9,   703,    -9,    -9,     0,     0,    -9,   -27,
      -9,    -9,   -27,   -27,   -27,   -27,   -27,   -27,     0,     0,
     -27,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -27,     0,   -27,   -27,     0,   -27,   -27,   -27,   -27,   -27,
     -27,   -27,   -27,   -27,   -27,     0,     0,   -27,   -11,   -27,
     -27,   -11,   -11,   -11,   -11,   -11,   -11,     0,     0,   -11,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -11,
       0,   -11,   -11,     0,   -11,   -11,   -11,   -11,   -11,   -11,
     -11,   -11,   -11,   -11,     0,     0,   -11,   -28,   -11,   -11,
     -28,   -28,   -28,   -28,   -28,   -28,     0,     0,   -28,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -28,     0,
     -28,   -28,     0,   -28,   -28,   -28,   -28,   -28,   -28,   -28,
     -28,   -28,   -28,     0,     0,   -28,   -12,   -28,   -28,   -12,
     -12,   -12,   -12,   -12,   -12,     0,     0,   -12,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -12,     0,   -12,
     -12,     0,   -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,
     -12,   -12,     0,     0,   -12,   -32,   -12,   -12,   -32,   -32,
     -32,   -32,   -32,   -32,     0,     0,   -32,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -32,     0,   -32,   -32,
       0,   -32,   -32,   -32,   -32,   -32,   -32,   -32,   -32,   -32,
     -32,     0,     0,   -32,   -26,   -32,   -32,   -26,   -26,   -26,
     -26,   -26,   -26,     0,     0,   -26,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -26,     0,   -26,   -26,     0,
     -26,   -26,   -26,   -26,   -26,   -26,   -26,   -26,   -26,   -26,
       0,     0,   -26,   -10,   -26,   -26,   -10,   -10,   -10,   -10,
     -10,   -10,     0,     0,   -10,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -10,     0,   -10,   -10,     0,   -10,
     -10,   -10,   -10,   -10,   -10,   -10,   -10,   -10,   -10,     0,
       0,   -10,   -15,   -10,   -10,   -15,   -15,   -15,   -15,   -15,
     -15,     0,     0,   -15,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -15,     0,   -15,   -15,     0,   -15,   -15,
     -15,   -15,   -15,   -15,   -15,   -15,   -15,   -15,     0,     0,
     -15,   -40,   -15,   -15,   -40,   -40,   -40,   -40,   -40,   -40,
       0,     0,   -40,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -40,     0,   -40,   -40,     0,   -40,   -40,   -40,
     -40,   -40,   -40,   -40,   -40,   -40,   -40,     0,     0,   -40,
     -38,   -40,   -40,   -38,   -38,   -38,   -38,   -38,   -38,     0,
       0,   -38,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -38,     0,   -38,   -38,     0,   -38,   -38,   -38,   -38,
     -38,   -38,   -38,   -38,   -38,   -38,     0,     0,   -38,   -42,
     -38,   -38,   -42,   -42,   -42,   -42,   -42,   -42,     0,     0,
     -42,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -42,     0,   -42,   -42,     0,   -42,   -42,   -42,   -42,   -42,
     -42,   -42,   -42,   -42,   -42,     0,     0,   -42,   -36,   -42,
     -42,   -36,   -36,   -36,   -36,   -36,   -36,     0,     0,   -36,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -36,
       0,   -36,   -36,     0,   -36,   -36,   -36,   -36,   -36,   -36,
     -36,   -36,   -36,   -36,     0,     0,   -36,    -3,   -36,   -36,
       1,     2,     3,     4,     5,     6,     0,     0,     7,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     8,     0,
       9,    10,     0,    11,    12,    13,    14,    15,    16,    17,
       0,    18,    19,     0,     0,    20,   -20,    21,   -18,   -20,
     -20,   -20,   -20,   -20,   -20,     0,     0,   -20,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -20,     0,   -20,
     -20,     0,   -20,   -20,   -20,   -20,   -20,   -20,   -20,     0,
     -20,   -20,     0,     0,   -20,    -4,   -20,   -20,    -4,    -4,
      -4,    -4,    -4,    -4,     0,     0,    -4,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    -4,     0,    -4,    -4,
       0,    -4,    -4,    -4,    -4,    -4,    -4,    -4,     0,    -4,
      -4,     0,     0,    -4,    -6,    -4,    -4,     1,     2,     3,
       4,     5,     6,     0,     0,     7,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     8,     0,     9,    10,     0,
      11,    12,    13,    14,    15,    16,    17,     0,    18,    19,
       0,     0,    20,   -16,    21,   -18,   -16,   -16,   -16,   -16,
     -16,   -16,     0,     0,   -16,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -16,     0,   -16,   -16,     0,   -16,
     -16,   -16,   -16,   -16,   -16,   -16,     0,   -16,   -16,     0,
       0,   -16,   -29,   -16,   -16,   -29,   -29,   -29,   -29,   -29,
     -29,     0,     0,   -29,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -29,     0,   -29,   -29,     0,   -29,   -29,
     -29,   -29,   -29,   -29,   -29,     0,   -29,   -29,     0,     0,
     -29,   -17,   -29,   -29,   -17,   -17,   -17,   -17,   -17,   -17,
       0,     0,   -17,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -17,     0,   -17,   -17,     0,   -17,   -17,   -17,
     -17,   -17,   -17,   -17,     0,   -17,   -17,     0,     0,   -17,
      -7,   -17,   -17,    -7,    -7,    -7,    -7,    -7,    -7,     0,
       0,    -7,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    -7,     0,    -7,    -7,     0,    -7,    -7,    -7,    -7,
      -7,    -7,    -7,     0,    -7,    -7,     0,     0,    -7,   -19,
      -7,    -7,   -19,   -19,   -19,   -19,   -19,   -19,     0,     0,
     -19,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -19,     0,   -19,   -19,     0,   -19,   -19,   -19,   -19,   -19,
     -19,   -19,     0,   -19,   -19,     0,     0,   -19,   -24,   -19,
     -19,   -24,   -24,   -24,   -24,   -24,   -24,     0,     0,   -24,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -24,
       0,   -24,   -24,     0,   -24,   -24,   -24,   -24,   -24,   -24,
     -24,     0,   -24,   -24,     0,     0,   -24,   -22,   -24,   -24,
     -22,   -22,   -22,   -22,   -22,   -22,     0,     0,   -22,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -22,     0,
     -22,   -22,     0,   -22,   -22,   -22,   -22,   -22,   -22,   -22,
       0,   -22,   -22,     0,     0,   -22,   -27,   -22,   -22,   -27,
     -27,   -27,   -27,   -27,   -27,     0,     0,   -27,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -27,     0,   -27,
     -27,     0,   -27,   -27,   -27,   -27,   -27,   -27,   -27,     0,
     -27,   -27,     0,     0,   -27,   -11,   -27,   -27,   -11,   -11,
     -11,   -11,   -11,   -11,     0,     0,   -11,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -11,     0,   -11,   -11,
       0,   -11,   -11,   -11,   -11,   -11,   -11,   -11,     0,   -11,
     -11,     0,     0,   -11,   -28,   -11,   -11,   -28,   -28,   -28,
     -28,   -28,   -28,     0,     0,   -28,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -28,     0,   -28,   -28,     0,
     -28,   -28,   -28,   -28,   -28,   -28,   -28,     0,   -28,   -28,
       0,     0,   -28,   -12,   -28,   -28,   -12,   -12,   -12,   -12,
     -12,   -12,     0,     0,   -12,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -12,     0,   -12,   -12,     0,   -12,
     -12,   -12,   -12,   -12,   -12,   -12,     0,   -12,   -12,     0,
       0,   -12,   -32,   -12,   -12,   -32,   -32,   -32,   -32,   -32,
     -32,     0,     0,   -32,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -32,     0,   -32,   -32,     0,   -32,   -32,
     -32,   -32,   -32,   -32,   -32,     0,   -32,   -32,     0,     0,
     -32,   -26,   -32,   -32,   -26,   -26,   -26,   -26,   -26,   -26,
       0,     0,   -26,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -26,     0,   -26,   -26,     0,   -26,   -26,   -26,
     -26,   -26,   -26,   -26,     0,   -26,   -26,     0,     0,   -26,
     -10,   -26,   -26,   -10,   -10,   -10,   -10,   -10,   -10,     0,
       0,   -10,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -10,     0,   -10,   -10,     0,   -10,   -10,   -10,   -10,
     -10,   -10,   -10,     0,   -10,   -10,     0,     0,   -10,   -15,
     -10,   -10,   -15,   -15,   -15,   -15,   -15,   -15,     0,     0,
     -15,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -15,     0,   -15,   -15,     0,   -15,   -15,   -15,   -15,   -15,
     -15,   -15,     0,   -15,   -15,     0,     0,   -15,   -40,   -15,
     -15,   -40,   -40,   -40,   -40,   -40,   -40,     0,     0,   -40,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -40,
       0,   -40,   -40,     0,   -40,   -40,   -40,   -40,   -40,   -40,
     -40,     0,   -40,   -40,     0,     0,   -40,   -38,   -40,   -40,
     -38,   -38,   -38,   -38,   -38,   -38,     0,     0,   -38,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -38,     0,
     -38,   -38,     0,   -38,   -38,   -38,   -38,   -38,   -38,   -38,
       0,   -38,   -38,     0,     0,   -38,   -42,   -38,   -38,   -42,
     -42,   -42,   -42,   -42,   -42,     0,     0,   -42,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -42,     0,   -42,
     -42,     0,   -42,   -42,   -42,   -42,   -42,   -42,   -42,     0,
     -42,   -42,     0,     0,   -42,   -36,   -42,   -42,   -36,   -36,
     -36,   -36,   -36,   -36,     0,     0,   -36,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -36,     0,   -36,   -36,
       0,   -36,   -36,   -36,   -36,   -36,   -36,   -36,     0,   -36,
     -36,     0,     0,   -36,     0,   -36,   -36,   -25,   -25,   -25,
     -25,   -25,   -25,     0,     0,   -25,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -25,     0,   -25,   -25,     0,
     -25,   -25,   -25,   -25,   -25,   -25,   -25,   693,   -25,   -25,
       0,     0,   -25,     0,   -25,   -25,   -25,    -9,    -9,    -9,
      -9,    -9,    -9,     0,     0,    -9,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    -9,     0,    -9,    -9,     0,
      -9,    -9,    -9,    -9,    -9,    -9,    -9,   696,    -9,    -9,
       0,     0,    -9,     0,    -9,    -9,    -9,   -16,   -16,   -16,
     -16,   -16,   -16,     0,     0,   -16,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -16,     0,   -16,   -16,     0,
     -16,   -16,   -16,   -16,   -16,   -16,   -16,   -16,   -16,   -16,
       0,     0,   -16,     0,   -16,   -16,   -16,   -29,   -29,   -29,
     -29,   -29,   -29,     0,     0,   -29,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -29,     0,   -29,   -29,     0,
     -29,   -29,   -29,   -29,   -29,   -29,   -29,   -29,   -29,   -29,
       0,     0,   -29,     0,   -29,   -29,   -29,   -17,   -17,   -17,
     -17,   -17,   -17,     0,     0,   -17,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -17,     0,   -17,   -17,     0,
     -17,   -17,   -17,   -17,   -17,   -17,   -17,   -17,   -17,   -17,
       0,     0,   -17,     0,   -17,   -17,   -17,   -19,   -19,   -19,
     -19,   -19,   -19,     0,     0,   -19,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -19,     0,   -19,   -19,     0,
     -19,   -19,   -19,   -19,   -19,   -19,   -19,   -19,   -19,   -19,
       0,     0,   -19,     0,   -19,   -19,   -19,   -24,   -24,   -24,
     -24,   -24,   -24,     0,     0,   -24,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -24,     0,   -24,   -24,     0,
     -24,   -24,   -24,   -24,   -24,   -24,   -24,   -24,   -24,   -24,
       0,     0,   -24,     0,   -24,   -24,   -24,   -22,   -22,   -22,
     -22,   -22,   -22,     0,     0,   -22,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -22,     0,   -22,   -22,     0,
     -22,   -22,   -22,   -22,   -22,   -22,   -22,   -22,   -22,   -22,
       0,     0,   -22,     0,   -22,   -22,   -22,   -25,   -25,   -25,
     -25,   -25,   -25,     0,     0,   -25,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -25,     0,   -25,   -25,     0,
     -25,   -25,   -25,   -25,   -25,   -25,   -25,   781,   -25,   -25,
       0,     0,   -25,     0,   -25,   -25,   -25,    -9,    -9,    -9,
      -9,    -9,    -9,     0,     0,    -9,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    -9,     0,    -9,    -9,     0,
      -9,    -9,    -9,    -9,    -9,    -9,    -9,   782,    -9,    -9,
       0,     0,    -9,     0,    -9,    -9,    -9,   -27,   -27,   -27,
     -27,   -27,   -27,     0,     0,   -27,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -27,     0,   -27,   -27,     0,
     -27,   -27,   -27,   -27,   -27,   -27,   -27,   -27,   -27,   -27,
       0,     0,   -27,     0,   -27,   -27,   -27,   -11,   -11,   -11,
     -11,   -11,   -11,     0,     0,   -11,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -11,     0,   -11,   -11,     0,
     -11,   -11,   -11,   -11,   -11,   -11,   -11,   -11,   -11,   -11,
       0,     0,   -11,     0,   -11,   -11,   -11,   -28,   -28,   -28,
     -28,   -28,   -28,     0,     0,   -28,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -28,     0,   -28,   -28,     0,
     -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,
       0,     0,   -28,     0,   -28,   -28,   -28,   -12,   -12,   -12,
     -12,   -12,   -12,     0,     0,   -12,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -12,     0,   -12,   -12,     0,
     -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,
       0,     0,   -12,     0,   -12,   -12,   -12,   -32,   -32,   -32,
     -32,   -32,   -32,     0,     0,   -32,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -32,     0,   -32,   -32,     0,
     -32,   -32,   -32,   -32,   -32,   -32,   -32,   -32,   -32,   -32,
       0,     0,   -32,     0,   -32,   -32,   -32,   -26,   -26,   -26,
     -26,   -26,   -26,     0,     0,   -26,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -26,     0,   -26,   -26,     0,
     -26,   -26,   -26,   -26,   -26,   -26,   -26,   -26,   -26,   -26,
       0,     0,   -26,     0,   -26,   -26,   -26,   -10,   -10,   -10,
     -10,   -10,   -10,     0,     0,   -10,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -10,     0,   -10,   -10,     0,
     -10,   -10,   -10,   -10,   -10,   -10,   -10,   -10,   -10,   -10,
       0,     0,   -10,     0,   -10,   -10,   -10,   -15,   -15,   -15,
     -15,   -15,   -15,     0,     0,   -15,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -15,     0,   -15,   -15,     0,
     -15,   -15,   -15,   -15,   -15,   -15,   -15,   -15,   -15,   -15,
       0,     0,   -15,     0,   -15,   -15,   -15,   -40,   -40,   -40,
     -40,   -40,   -40,     0,     0,   -40,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -40,     0,   -40,   -40,     0,
     -40,   -40,   -40,   -40,   -40,   -40,   -40,   -40,   -40,   -40,
       0,     0,   -40,     0,   -40,   -40,   -40,   -38,   -38,   -38,
     -38,   -38,   -38,     0,     0,   -38,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -38,     0,   -38,   -38,     0,
     -38,   -38,   -38,   -38,   -38,   -38,   -38,   -38,   -38,   -38,
       0,     0,   -38,     0,   -38,   -38,   -38,   -42,   -42,   -42,
     -42,   -42,   -42,     0,     0,   -42,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -42,     0,   -42,   -42,     0,
     -42,   -42,   -42,   -42,   -42,   -42,   -42,   -42,   -42,   -42,
       0,     0,   -42,     0,   -42,   -42,   -42,   -36,   -36,   -36,
     -36,   -36,   -36,     0,     0,   -36,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -36,     0,   -36,   -36,     0,
     -36,   -36,   -36,   -36,   -36,   -36,   -36,   -36,   -36,   -36,
       0,     0,   -36,     0,   -36,   -36,   -36,     1,     2,     3,
       4,     5,   259,     0,     0,     7,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     8,     0,     9,    10,     0,
      11,    12,    13,   260,   261,   262,   263,     0,   264,    19,
       0,     0,    20,     0,   265,   -18,    -3,   -39,   -39,   -39,
     -39,   -39,   -39,     0,     0,   -39,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -39,     0,   -39,   -39,     0,
     -39,   -39,   -39,   -39,   -39,   -39,   -39,     0,   -39,   -39,
       0,     0,   -39,     0,   -39,   -39,   -39,   -37,   -37,   -37,
     -37,   -37,   -37,     0,     0,   -37,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -37,     0,   -37,   -37,     0,
     -37,   -37,   -37,   -37,   -37,   -37,   -37,     0,   -37,   -37,
       0,     0,   -37,     0,   -37,   -37,   -37,   -41,   -41,   -41,
     -41,   -41,   -41,     0,     0,   -41,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -41,     0,   -41,   -41,     0,
     -41,   -41,   -41,   -41,   -41,   -41,   -41,     0,   -41,   -41,
       0,     0,   -41,     0,   -41,   -41,   -41,   -20,   -20,   -20,
     -20,   -20,   -20,     0,     0,   -20,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -20,     0,   -20,   -20,     0,
     -20,   -20,   -20,   -20,   -20,   -20,   -20,     0,   -20,   -20,
       0,     0,   -20,     0,   -20,   -20,   -20,    -4,    -4,    -4,
      -4,    -4,    -4,     0,     0,    -4,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    -4,     0,    -4,    -4,     0,
      -4,    -4,    -4,    -4,    -4,    -4,    -4,     0,    -4,    -4,
       0,     0,    -4,     0,    -4,    -4,    -4,     1,     2,     3,
       4,     5,   259,     0,     0,     7,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     8,     0,     9,    10,     0,
      11,    12,    13,   260,   261,   262,   263,     0,   264,    19,
       0,     0,    20,     0,   265,   -18,    -6,   -16,   -16,   -16,
     -16,   -16,   -16,     0,     0,   -16,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -16,     0,   -16,   -16,     0,
     -16,   -16,   -16,   -16,   -16,   -16,   -16,     0,   -16,   -16,
       0,     0,   -16,     0,   -16,   -16,   -16,   -29,   -29,   -29,
     -29,   -29,   -29,     0,     0,   -29,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -29,     0,   -29,   -29,     0,
     -29,   -29,   -29,   -29,   -29,   -29,   -29,     0,   -29,   -29,
       0,     0,   -29,     0,   -29,   -29,   -29,   -17,   -17,   -17,
     -17,   -17,   -17,     0,     0,   -17,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -17,     0,   -17,   -17,     0,
     -17,   -17,   -17,   -17,   -17,   -17,   -17,     0,   -17,   -17,
       0,     0,   -17,     0,   -17,   -17,   -17,    -7,    -7,    -7,
      -7,    -7,    -7,     0,     0,    -7,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    -7,     0,    -7,    -7,     0,
      -7,    -7,    -7,    -7,    -7,    -7,    -7,     0,    -7,    -7,
       0,     0,    -7,     0,    -7,    -7,    -7,   -19,   -19,   -19,
     -19,   -19,   -19,     0,     0,   -19,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -19,     0,   -19,   -19,     0,
     -19,   -19,   -19,   -19,   -19,   -19,   -19,     0,   -19,   -19,
       0,     0,   -19,     0,   -19,   -19,   -19,   -24,   -24,   -24,
     -24,   -24,   -24,     0,     0,   -24,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -24,     0,   -24,   -24,     0,
     -24,   -24,   -24,   -24,   -24,   -24,   -24,     0,   -24,   -24,
       0,     0,   -24,     0,   -24,   -24,   -24,   -22,   -22,   -22,
     -22,   -22,   -22,     0,     0,   -22,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -22,     0,   -22,   -22,     0,
     -22,   -22,   -22,   -22,   -22,   -22,   -22,     0,   -22,   -22,
       0,     0,   -22,     0,   -22,   -22,   -22,   -27,   -27,   -27,
     -27,   -27,   -27,     0,     0,   -27,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -27,     0,   -27,   -27,     0,
     -27,   -27,   -27,   -27,   -27,   -27,   -27,     0,   -27,   -27,
       0,     0,   -27,     0,   -27,   -27,   -27,   -11,   -11,   -11,
     -11,   -11,   -11,     0,     0,   -11,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -11,     0,   -11,   -11,     0,
     -11,   -11,   -11,   -11,   -11,   -11,   -11,     0,   -11,   -11,
       0,     0,   -11,     0,   -11,   -11,   -11,   -28,   -28,   -28,
     -28,   -28,   -28,     0,     0,   -28,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -28,     0,   -28,   -28,     0,
     -28,   -28,   -28,   -28,   -28,   -28,   -28,     0,   -28,   -28,
       0,     0,   -28,     0,   -28,   -28,   -28,   -12,   -12,   -12,
     -12,   -12,   -12,     0,     0,   -12,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -12,     0,   -12,   -12,     0,
     -12,   -12,   -12,   -12,   -12,   -12,   -12,     0,   -12,   -12,
       0,     0,   -12,     0,   -12,   -12,   -12,   -32,   -32,   -32,
     -32,   -32,   -32,     0,     0,   -32,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -32,     0,   -32,   -32,     0,
     -32,   -32,   -32,   -32,   -32,   -32,   -32,     0,   -32,   -32,
       0,     0,   -32,     0,   -32,   -32,   -32,   -26,   -26,   -26,
     -26,   -26,   -26,     0,     0,   -26,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -26,     0,   -26,   -26,     0,
     -26,   -26,   -26,   -26,   -26,   -26,   -26,     0,   -26,   -26,
       0,     0,   -26,     0,   -26,   -26,   -26,   -10,   -10,   -10,
     -10,   -10,   -10,     0,     0,   -10,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -10,     0,   -10,   -10,     0,
     -10,   -10,   -10,   -10,   -10,   -10,   -10,     0,   -10,   -10,
       0,     0,   -10,     0,   -10,   -10,   -10,   -15,   -15,   -15,
     -15,   -15,   -15,     0,     0,   -15,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -15,     0,   -15,   -15,     0,
     -15,   -15,   -15,   -15,   -15,   -15,   -15,     0,   -15,   -15,
       0,     0,   -15,     0,   -15,   -15,   -15,   -40,   -40,   -40,
     -40,   -40,   -40,     0,     0,   -40,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -40,     0,   -40,   -40,     0,
     -40,   -40,   -40,   -40,   -40,   -40,   -40,     0,   -40,   -40,
       0,     0,   -40,     0,   -40,   -40,   -40,   -38,   -38,   -38,
     -38,   -38,   -38,     0,     0,   -38,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -38,     0,   -38,   -38,     0,
     -38,   -38,   -38,   -38,   -38,   -38,   -38,     0,   -38,   -38,
       0,     0,   -38,     0,   -38,   -38,   -38,   -42,   -42,   -42,
     -42,   -42,   -42,     0,     0,   -42,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -42,     0,   -42,   -42,     0,
     -42,   -42,   -42,   -42,   -42,   -42,   -42,     0,   -42,   -42,
       0,     0,   -42,     0,   -42,   -42,   -42,   -36,   -36,   -36,
     -36,   -36,   -36,     0,     0,   -36,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -36,     0,   -36,   -36,     0,
     -36,   -36,   -36,   -36,   -36,   -36,   -36,     0,   -36,   -36,
       0,     0,   -36,     0,   -36,   -36,   -36,     1,     2,     3,
       4,     5,   327,     0,     0,     7,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     8,     0,     9,    10,     0,
      11,    12,    13,   328,   329,   330,   331,     0,   332,    19,
       0,     0,    20,     0,   333,   -18,     1,     2,     3,     4,
       5,     6,     0,     0,     7,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     8,     0,     9,    10,     0,    11,
      12,    13,    14,    15,    16,    17,     0,    18,    19,     0,
       0,    20,     0,    21,   -18,   -14,   -14,   -14,   -14,   -14,
     -14,     0,     0,   -14,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -14,     0,   -14,   -14,     0,   -14,   -14,
     -14,   -14,   -14,   -14,   -14,     0,   -14,   -14,     0,     0,
     -14,     0,   -14,   -14,     1,     2,     3,     4,     5,   644,
       0,     0,     7,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     8,     0,     9,    10,     0,    11,    12,    13,
     645,   646,   647,   648,     0,   649,    19,     0,     0,    20,
       0,   650,   -18,     1,     2,     3,     4,     5,   259,     0,
       0,     7,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     8,     0,     9,    10,     0,    11,    12,    13,   260,
     261,   262,   263,     0,   264,    19,     0,     0,    20,     0,
     265,   -18,     1,     2,     3,     4,     5,   133,     0,     0,
       7,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       8,     0,     9,    10,     0,    11,    12,    13,     0,     0,
       0,     0,     0,     0,    19,     0,     0,    20,    67,   134,
       1,     2,     3,     4,     5,     0,     0,     0,     7,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     8,     0,
       9,    10,     0,    11,    12,    13,     0,     0,     0,     0,
       0,     0,    19,     0,    77,    20,   230,   231,   232,   233,
     234,     0,     0,     0,   235,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   236,     0,   237,   238,     0,   239,
     240,   241,     0,     0,     0,     0,     0,     0,   242,     0,
      79,   243,   230,   231,   232,   233,   234,     0,     0,     0,
     235,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     236,     0,   237,   238,     0,   239,   240,   241,     0,     0,
       0,     0,     0,     0,   242,     0,    81,   243,   230,   231,
     232,   233,   234,     0,     0,     0,   235,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   236,     0,   237,   238,
       0,   239,   240,   241,     0,     0,     0,     0,     0,     0,
     242,     0,    91,   243,     1,     2,     3,     4,     5,     0,
       0,     0,     7,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     8,     0,     9,    10,     0,    11,    12,    13,
       0,     0,     0,     0,     0,     0,    19,     0,    93,    20,
       1,     2,     3,     4,     5,     0,     0,     0,     7,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     8,     0,
       9,    10,     0,    11,    12,    13,     0,     0,     0,     0,
       0,     0,    19,     0,    95,    20,     1,     2,     3,     4,
       5,     0,     0,     0,     7,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     8,     0,     9,    10,     0,    11,
      12,    13,     0,     0,     0,     0,     0,     0,    19,     0,
      97,    20,     1,     2,     3,     4,     5,     0,     0,     0,
       7,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       8,     0,     9,    10,     0,    11,    12,    13,     0,     0,
       0,     0,     0,     0,    19,     0,    99,    20,     1,     2,
       3,     4,     5,     0,     0,     0,     7,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     8,     0,     9,    10,
       0,    11,    12,    13,     0,     0,     0,     0,     0,     0,
      19,     0,   101,    20,     1,     2,     3,     4,     5,     0,
       0,     0,     7,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     8,     0,     9,    10,     0,    11,    12,    13,
       0,     0,     0,     0,     0,     0,    19,     0,   103,    20,
       1,     2,     3,     4,     5,     0,     0,     0,     7,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     8,     0,
       9,    10,     0,    11,    12,    13,     0,     0,     0,     0,
       0,     0,    19,     0,   106,    20,     1,     2,     3,     4,
       5,     0,     0,     0,     7,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     8,     0,     9,    10,     0,    11,
      12,    13,     0,     0,     0,     0,     0,     0,    19,     0,
     108,    20,     1,     2,     3,     4,     5,     0,     0,     0,
       7,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       8,     0,     9,    10,     0,    11,    12,    13,     0,     0,
       0,     0,     0,     0,    19,     0,   110,    20,     1,     2,
       3,     4,     5,     0,     0,     0,     7,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     8,     0,     9,    10,
       0,    11,    12,    13,     0,     0,     0,     0,     0,     0,
      19,     0,   112,    20,     1,     2,     3,     4,     5,     0,
       0,     0,     7,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     8,     0,     9,    10,     0,    11,    12,    13,
       0,     0,     0,     0,     0,     0,    19,     0,   114,    20,
       1,     2,     3,     4,     5,     0,     0,     0,     7,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     8,     0,
       9,    10,     0,    11,    12,    13,     0,     0,     0,     0,
       0,     0,    19,     0,   380,    20,   230,   231,   232,   233,
     234,     0,     0,     0,   235,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   236,     0,   237,   238,     0,   239,
     240,   241,     0,     0,     0,     0,     0,     0,   242,     0,
     382,   243,   230,   231,   232,   233,   234,     0,     0,     0,
     235,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     236,     0,   237,   238,     0,   239,   240,   241,     0,     0,
       0,     0,     0,     0,   242,     0,   384,   243,   230,   231,
     232,   233,   234,     0,     0,     0,   235,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   236,     0,   237,   238,
       0,   239,   240,   241,     0,     0,     0,     0,     0,     0,
     242,     0,   386,   243,   230,   231,   232,   233,   234,     0,
       0,     0,   235,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   236,     0,   237,   238,     0,   239,   240,   241,
       0,     0,     0,     0,     0,     0,   242,     0,   388,   243,
     230,   231,   232,   233,   234,     0,     0,     0,   235,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   236,     0,
     237,   238,     0,   239,   240,   241,     0,     0,     0,     0,
       0,     0,   242,     0,   390,   243,   230,   231,   232,   233,
     234,     0,     0,     0,   235,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   236,     0,   237,   238,     0,   239,
     240,   241,     0,     0,     0,     0,     0,     0,   242,     0,
     392,   243,   230,   231,   232,   233,   234,     0,     0,     0,
     235,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     236,     0,   237,   238,     0,   239,   240,   241,     0,     0,
       0,     0,     0,     0,   242,     0,   395,   243,   230,   231,
     232,   233,   234,     0,     0,     0,   235,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   236,     0,   237,   238,
       0,   239,   240,   241,     0,     0,     0,     0,     0,     0,
     242,     0,   397,   243,   230,   231,   232,   233,   234,     0,
       0,     0,   235,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   236,     0,   237,   238,     0,   239,   240,   241,
       0,     0,     0,     0,     0,     0,   242,     0,   399,   243,
     230,   231,   232,   233,   234,     0,     0,     0,   235,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   236,     0,
     237,   238,     0,   239,   240,   241,     0,     0,     0,     0,
       0,     0,   242,     0,   401,   243,   230,   231,   232,   233,
     234,     0,     0,     0,   235,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   236,     0,   237,   238,     0,   239,
     240,   241,     0,     0,     0,     0,     0,     0,   242,     0,
     403,   243,   230,   231,   232,   233,   234,     0,     0,     0,
     235,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     236,     0,   237,   238,     0,   239,   240,   241,     0,     0,
       0,     0,     0,     0,   242,     0,   413,   243,     1,     2,
       3,     4,     5,     0,     0,     0,     7,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     8,     0,     9,    10,
       0,    11,    12,    13,     0,     0,     0,     0,     0,     0,
      19,     0,   441,    20,   269,   270,   271,   272,   273,     0,
       0,     0,   274,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   275,     0,   276,   277,     0,   278,   279,   280,
       0,     0,     0,     0,     0,     0,   281,     0,   443,   282,
     269,   270,   271,   272,   273,     0,     0,     0,   274,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   275,     0,
     276,   277,     0,   278,   279,   280,     0,     0,     0,     0,
       0,     0,   281,     0,   445,   282,   269,   270,   271,   272,
     273,     0,     0,     0,   274,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   275,     0,   276,   277,     0,   278,
     279,   280,     0,     0,     0,     0,     0,     0,   281,     0,
     447,   282,   269,   270,   271,   272,   273,     0,     0,     0,
     274,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     275,     0,   276,   277,     0,   278,   279,   280,     0,     0,
       0,     0,     0,     0,   281,     0,   449,   282,   269,   270,
     271,   272,   273,     0,     0,     0,   274,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   275,     0,   276,   277,
       0,   278,   279,   280,     0,     0,     0,     0,     0,     0,
     281,     0,   451,   282,   269,   270,   271,   272,   273,     0,
       0,     0,   274,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   275,     0,   276,   277,     0,   278,   279,   280,
       0,     0,     0,     0,     0,     0,   281,     0,   453,   282,
     269,   270,   271,   272,   273,     0,     0,     0,   274,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   275,     0,
     276,   277,     0,   278,   279,   280,     0,     0,     0,     0,
       0,     0,   281,     0,   456,   282,   269,   270,   271,   272,
     273,     0,     0,     0,   274,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   275,     0,   276,   277,     0,   278,
     279,   280,     0,     0,     0,     0,     0,     0,   281,     0,
     458,   282,   269,   270,   271,   272,   273,     0,     0,     0,
     274,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     275,     0,   276,   277,     0,   278,   279,   280,     0,     0,
       0,     0,     0,     0,   281,     0,   460,   282,   269,   270,
     271,   272,   273,     0,     0,     0,   274,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   275,     0,   276,   277,
       0,   278,   279,   280,     0,     0,     0,     0,     0,     0,
     281,     0,   462,   282,   269,   270,   271,   272,   273,     0,
       0,     0,   274,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   275,     0,   276,   277,     0,   278,   279,   280,
       0,     0,     0,     0,     0,     0,   281,     0,   464,   282,
     269,   270,   271,   272,   273,     0,     0,     0,   274,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   275,     0,
     276,   277,     0,   278,   279,   280,     0,     0,     0,     0,
       0,     0,   281,     0,   468,   282,   283,   284,   285,   286,
     287,     0,     0,     0,   288,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   289,     0,   290,   291,     0,   292,
     293,   294,     0,     0,     0,     0,     0,     0,   295,     0,
     470,   296,   283,   284,   285,   286,   287,     0,     0,     0,
     288,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     289,     0,   290,   291,     0,   292,   293,   294,     0,     0,
       0,     0,     0,     0,   295,     0,   472,   296,   283,   284,
     285,   286,   287,     0,     0,     0,   288,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   289,     0,   290,   291,
       0,   292,   293,   294,     0,     0,     0,     0,     0,     0,
     295,     0,   474,   296,   283,   284,   285,   286,   287,     0,
       0,     0,   288,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   289,     0,   290,   291,     0,   292,   293,   294,
       0,     0,     0,     0,     0,     0,   295,     0,   476,   296,
     283,   284,   285,   286,   287,     0,     0,     0,   288,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   289,     0,
     290,   291,     0,   292,   293,   294,     0,     0,     0,     0,
       0,     0,   295,     0,   478,   296,   283,   284,   285,   286,
     287,     0,     0,     0,   288,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   289,     0,   290,   291,     0,   292,
     293,   294,     0,     0,     0,     0,     0,     0,   295,     0,
     480,   296,   283,   284,   285,   286,   287,     0,     0,     0,
     288,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     289,     0,   290,   291,     0,   292,   293,   294,     0,     0,
       0,     0,     0,     0,   295,     0,   483,   296,   283,   284,
     285,   286,   287,     0,     0,     0,   288,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   289,     0,   290,   291,
       0,   292,   293,   294,     0,     0,     0,     0,     0,     0,
     295,     0,   485,   296,   283,   284,   285,   286,   287,     0,
       0,     0,   288,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   289,     0,   290,   291,     0,   292,   293,   294,
       0,     0,     0,     0,     0,     0,   295,     0,   487,   296,
     283,   284,   285,   286,   287,     0,     0,     0,   288,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   289,     0,
     290,   291,     0,   292,   293,   294,     0,     0,     0,     0,
       0,     0,   295,     0,   489,   296,   283,   284,   285,   286,
     287,     0,     0,     0,   288,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   289,     0,   290,   291,     0,   292,
     293,   294,     0,     0,     0,     0,     0,     0,   295,     0,
     491,   296,   283,   284,   285,   286,   287,     0,     0,     0,
     288,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     289,     0,   290,   291,     0,   292,   293,   294,     0,     0,
       0,     0,     0,     0,   295,     0,   501,   296,     1,     2,
       3,     4,     5,     0,     0,     0,     7,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     8,     0,     9,    10,
       0,    11,    12,    13,     0,     0,     0,     0,     0,     0,
      19,     0,   520,    20,   339,   340,   341,   342,   343,     0,
       0,     0,   344,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   345,     0,   346,   347,     0,   348,   349,   350,
       0,     0,     0,     0,     0,     0,   351,     0,   522,   352,
     339,   340,   341,   342,   343,     0,     0,     0,   344,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   345,     0,
     346,   347,     0,   348,   349,   350,     0,     0,     0,     0,
       0,     0,   351,     0,   524,   352,   339,   340,   341,   342,
     343,     0,     0,     0,   344,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   345,     0,   346,   347,     0,   348,
     349,   350,     0,     0,     0,     0,     0,     0,   351,     0,
     526,   352,   339,   340,   341,   342,   343,     0,     0,     0,
     344,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     345,     0,   346,   347,     0,   348,   349,   350,     0,     0,
       0,     0,     0,     0,   351,     0,   528,   352,   339,   340,
     341,   342,   343,     0,     0,     0,   344,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   345,     0,   346,   347,
       0,   348,   349,   350,     0,     0,     0,     0,     0,     0,
     351,     0,   530,   352,   339,   340,   341,   342,   343,     0,
       0,     0,   344,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   345,     0,   346,   347,     0,   348,   349,   350,
       0,     0,     0,     0,     0,     0,   351,     0,   532,   352,
     339,   340,   341,   342,   343,     0,     0,     0,   344,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   345,     0,
     346,   347,     0,   348,   349,   350,     0,     0,     0,     0,
       0,     0,   351,     0,   535,   352,   339,   340,   341,   342,
     343,     0,     0,     0,   344,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   345,     0,   346,   347,     0,   348,
     349,   350,     0,     0,     0,     0,     0,     0,   351,     0,
     537,   352,   339,   340,   341,   342,   343,     0,     0,     0,
     344,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     345,     0,   346,   347,     0,   348,   349,   350,     0,     0,
       0,     0,     0,     0,   351,     0,   539,   352,   339,   340,
     341,   342,   343,     0,     0,     0,   344,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   345,     0,   346,   347,
       0,   348,   349,   350,     0,     0,     0,     0,     0,     0,
     351,     0,   541,   352,   339,   340,   341,   342,   343,     0,
       0,     0,   344,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   345,     0,   346,   347,     0,   348,   349,   350,
       0,     0,     0,     0,     0,     0,   351,     0,   543,   352,
     339,   340,   341,   342,   343,     0,     0,     0,   344,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   345,     0,
     346,   347,     0,   348,   349,   350,     0,     0,     0,     0,
       0,     0,   351,     0,   546,   352,   230,   231,   232,   233,
     234,     0,     0,     0,   235,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   236,     0,   237,   238,     0,   239,
     240,   241,     0,     0,     0,     0,     0,     0,   242,     0,
     556,   243,   230,   231,   232,   233,   234,     0,     0,     0,
     235,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     236,     0,   237,   238,     0,   239,   240,   241,     0,     0,
       0,     0,     0,     0,   242,     0,   558,   243,   230,   231,
     232,   233,   234,     0,     0,     0,   235,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   236,     0,   237,   238,
       0,   239,   240,   241,     0,     0,     0,     0,     0,     0,
     242,     0,   560,   243,   230,   231,   232,   233,   234,     0,
       0,     0,   235,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   236,     0,   237,   238,     0,   239,   240,   241,
       0,     0,     0,     0,     0,     0,   242,     0,   568,   243,
     269,   270,   271,   272,   273,     0,     0,     0,   274,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   275,     0,
     276,   277,     0,   278,   279,   280,     0,     0,     0,     0,
       0,     0,   281,     0,   573,   282,   283,   284,   285,   286,
     287,     0,     0,     0,   288,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   289,     0,   290,   291,     0,   292,
     293,   294,     0,     0,     0,     0,     0,     0,   295,     0,
     584,   296,   230,   231,   232,   233,   234,     0,     0,     0,
     235,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     236,     0,   237,   238,     0,   239,   240,   241,     0,     0,
       0,     0,     0,     0,   242,     0,   586,   243,   230,   231,
     232,   233,   234,     0,     0,     0,   235,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   236,     0,   237,   238,
       0,   239,   240,   241,     0,     0,     0,     0,     0,     0,
     242,     0,   588,   243,   230,   231,   232,   233,   234,     0,
       0,     0,   235,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   236,     0,   237,   238,     0,   239,   240,   241,
       0,     0,     0,     0,     0,     0,   242,     0,   596,   243,
     339,   340,   341,   342,   343,     0,     0,     0,   344,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   345,     0,
     346,   347,     0,   348,   349,   350,     0,     0,     0,     0,
       0,     0,   351,     0,   691,   352,     1,     2,     3,     4,
       5,     0,     0,     0,     7,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     8,     0,     9,    10,     0,    11,
      12,    13,     0,     0,     0,     0,     0,     0,    19,     0,
     713,    20,   230,   231,   232,   233,   234,     0,     0,     0,
     235,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     236,     0,   237,   238,     0,   239,   240,   241,     0,     0,
       0,     0,     0,     0,   242,     0,   715,   243,   230,   231,
     232,   233,   234,     0,     0,     0,   235,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   236,     0,   237,   238,
       0,   239,   240,   241,     0,     0,     0,     0,     0,     0,
     242,     0,   717,   243,   230,   231,   232,   233,   234,     0,
       0,     0,   235,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   236,     0,   237,   238,     0,   239,   240,   241,
     230,   231,   232,   233,   234,     0,   242,     0,   235,   243,
       0,     0,     0,     0,     0,     0,     0,     0,   236,     0,
     237,   238,     0,   239,   240,   241,   230,   231,   232,   233,
     234,     0,   242,     0,   235,   243,   -65,     0,     0,     0,
       0,     0,     0,     0,   236,     0,   237,   238,     0,   239,
     240,   241,   269,   270,   271,   272,   273,     0,   242,     0,
     274,   243,     0,     0,     0,     0,     0,     0,     0,     0,
     275,     0,   276,   277,     0,   278,   279,   280,   283,   284,
     285,   286,   287,     0,   281,     0,   288,   282,     0,     0,
       0,     0,     0,     0,     0,     0,   289,     0,   290,   291,
       0,   292,   293,   294,   339,   340,   341,   342,   343,     0,
     295,     0,   344,   296,     0,     0,     0,     0,     0,     0,
       0,     0,   345,     0,   346,   347,     0,   348,   349,   350,
       0,     0,     0,     0,     0,     0,   351,   -76,   508,   352,
     -76,   -76,   -76,   -76,   -76,   -76,   -76,   -76,   509,   -76,
     -76,   -76,   -76,   -76,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -76,     0,  -100,     0,   -76,   353,
       0,   -76,   354,   355,   356,   357,   358,   359,   360,   361,
       0,   362,   363,   364,   365,   366,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   367,     0,     0,     0,
     -53,   353,     0,   -53,   354,   355,   356,   357,   358,   359,
     360,   361,     0,   362,   363,   364,   365,   366,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   367,     0,
       0,     0,   -62,   -74,     0,   214,   -74,   -74,   -74,   -74,
     -74,   -74,   -74,   -74,     0,   -74,   -74,   -74,   -74,   -74,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -74,     0,     0,     0,   -74,   -75,     0,   -74,   -75,   -75,
     -75,   -75,   -75,   -75,   -75,   -75,     0,   -75,   -75,   -75,
     -75,   -75,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -75,     0,     0,     0,   -75,   -71,     0,   -75,
     -71,   -71,   -71,   -71,   -71,   -71,   -71,   -71,     0,   -71,
     -71,   -71,   -71,   -71,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -71,     0,     0,     0,   -71,   -72,
       0,   -71,   -72,   -72,   -72,   -72,   -72,   -72,   -72,   -72,
       0,   -72,   -72,   -72,   -72,   -72,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -72,     0,     0,     0,
     -72,   -73,     0,   -72,   -73,   -73,   -73,   -73,   -73,   -73,
     -73,   -73,     0,   -73,   -73,   -73,   -73,   -73,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -73,     0,
       0,     0,   -73,   -77,     0,   -73,   -77,   -77,   -77,   -77,
     -77,   -77,   -77,   -77,     0,   -77,   -77,   -77,   -77,   -77,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -77,     0,     0,     0,   -77,   -84,     0,   -77,   -84,   -84,
     -84,   -84,   -84,   -84,   -84,   -84,     0,   -84,   -84,   -84,
     -84,   -84,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -84,     0,     0,     0,   -84,   -78,     0,   -84,
     -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,     0,   -78,
     -78,   -78,   -78,   -78,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -78,     0,     0,     0,   -78,   -79,
       0,   -78,   -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,
       0,   -79,   -79,   -79,   -79,   -79,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -79,     0,     0,     0,
     -79,   -80,     0,   -79,   -80,   -80,   -80,   -80,   -80,   -80,
     -80,   -80,     0,   -80,   -80,   -80,   -80,   -80,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -80,     0,
       0,     0,   -80,   -81,     0,   -80,   -81,   -81,   -81,   -81,
     -81,   -81,   -81,   -81,     0,   -81,   -81,   -81,   -81,   -81,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -81,     0,     0,     0,   -81,   -82,     0,   -81,   -82,   -82,
     -82,   -82,   -82,   -82,   -82,   -82,     0,   -82,   -82,   -82,
     -82,   -82,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -82,     0,     0,     0,   -82,   -83,     0,   -82,
     -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,     0,   -83,
     -83,   -83,   -83,   -83,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -83,     0,     0,     0,   -83,   -90,
       0,   -83,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,
       0,   -90,   -90,   -90,   -90,   -90,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -90,     0,     0,     0,
     -90,  -108,     0,   -90,  -108,  -108,  -108,  -108,  -108,  -108,
    -108,  -108,     0,  -108,  -108,  -108,  -108,  -108,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -108,     0,
       0,     0,  -108,   353,     0,  -108,   -91,   -91,   -91,   -91,
     -91,   -91,   -91,   -91,     0,   362,   363,   364,   365,   366,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -91,     0,     0,     0,   -91,  -109,     0,   -91,  -109,  -109,
    -109,  -109,  -109,  -109,  -109,  -109,     0,  -109,  -109,  -109,
    -109,  -109,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -109,     0,     0,     0,  -109,   353,     0,  -109,
     354,   -92,   -92,   -92,   -92,   -92,   -92,   -92,     0,   362,
     363,   364,   365,   366,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -92,     0,     0,     0,   -92,  -110,
       0,   -92,  -110,  -110,  -110,  -110,  -110,  -110,  -110,  -110,
       0,  -110,  -110,  -110,  -110,  -110,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -110,     0,     0,     0,
    -110,   353,     0,  -110,   354,   355,   -93,   -93,   -93,   -93,
     -93,   -93,     0,   362,   363,   364,   365,   366,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -93,     0,
       0,     0,   -93,  -111,     0,   -93,  -111,  -111,  -111,  -111,
    -111,  -111,  -111,  -111,     0,  -111,  -111,  -111,  -111,  -111,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -111,     0,     0,     0,  -111,   353,     0,  -111,   354,   355,
     356,   -94,   -94,   -94,   -94,   -94,     0,   362,   363,   364,
     365,   366,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -94,     0,     0,     0,   -94,  -112,     0,   -94,
    -112,  -112,  -112,  -112,  -112,  -112,  -112,  -112,     0,  -112,
    -112,  -112,  -112,  -112,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -112,     0,     0,     0,  -112,   353,
       0,  -112,   354,   355,   356,   357,   -95,   -95,   -95,   -95,
       0,   362,   363,   364,   365,   366,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -95,     0,     0,     0,
     -95,  -113,     0,   -95,  -113,  -113,  -113,  -113,  -113,  -113,
    -113,  -113,     0,  -113,  -113,  -113,  -113,  -113,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -113,     0,
       0,     0,  -113,   353,     0,  -113,   354,   355,   356,   357,
     358,   -96,   -96,   -96,     0,   362,   363,   364,   365,   366,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -96,     0,     0,     0,   -96,  -114,     0,   -96,  -114,  -114,
    -114,  -114,  -114,  -114,  -114,  -114,     0,  -114,  -114,  -114,
    -114,  -114,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -114,     0,     0,     0,  -114,   353,     0,  -114,
     354,   355,   356,   357,   358,   359,   -97,   -97,     0,   362,
     363,   364,   365,   366,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -97,     0,     0,     0,   -97,  -115,
       0,   -97,  -115,  -115,  -115,  -115,  -115,  -115,  -115,  -115,
       0,  -115,  -115,  -115,  -115,  -115,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -115,     0,     0,     0,
    -115,  -103,     0,  -115,  -103,  -103,  -103,  -103,  -103,  -103,
    -103,  -103,     0,  -103,  -103,  -103,  -103,  -103,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -103,     0,
       0,     0,  -103,   353,     0,  -103,   -85,   -85,   -85,   -85,
     -85,   -85,   -85,   -85,     0,   -85,   -85,   -85,   -85,   -85,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -85,     0,     0,     0,   -85,  -104,     0,   -85,  -104,  -104,
    -104,  -104,  -104,  -104,  -104,  -104,     0,  -104,  -104,  -104,
    -104,  -104,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -104,     0,     0,     0,  -104,   353,     0,  -104,
     -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,     0,   -86,
     -86,   -86,   -86,   -86,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -86,     0,     0,     0,   -86,  -106,
       0,   -86,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,
       0,  -106,  -106,  -106,  -106,  -106,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -106,     0,     0,     0,
    -106,   353,     0,  -106,   -88,   -88,   -88,   -88,   -88,   -88,
     -88,   -88,     0,   362,   363,   -88,   -88,   366,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -88,     0,
       0,     0,   -88,  -107,     0,   -88,  -107,  -107,  -107,  -107,
    -107,  -107,  -107,  -107,     0,  -107,  -107,  -107,  -107,  -107,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -107,     0,     0,     0,  -107,   353,     0,  -107,   -89,   -89,
     -89,   -89,   -89,   -89,   -89,   -89,     0,   362,   363,   -89,
     -89,   366,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -89,     0,     0,     0,   -89,  -105,     0,   -89,
    -105,  -105,  -105,  -105,  -105,  -105,  -105,  -105,     0,  -105,
    -105,  -105,  -105,  -105,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -105,     0,     0,     0,  -105,   353,
       0,  -105,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,
       0,   -87,   -87,   -87,   -87,   -87,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -87,     0,     0,     0,
     -87,  -116,     0,   -87,  -116,  -116,  -116,  -116,  -116,  -116,
    -116,  -116,     0,  -116,  -116,  -116,  -116,  -116,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -116,     0,
       0,     0,  -116,   353,     0,  -116,   354,   355,   356,   357,
     358,   359,   360,   361,     0,   362,   363,   364,   365,   366,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     367,     0,     0,     0,   -99,  -101,     0,   -99,  -101,  -101,
    -101,  -101,  -101,  -101,  -101,  -101,     0,  -101,  -101,  -101,
    -101,  -101,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -101,     0,     0,     0,  -101,  -102,     0,  -101,
    -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,     0,  -102,
    -102,  -102,  -102,  -102,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -102,     0,     0,     0,  -102,   353,
       0,  -102,   354,   355,   356,   357,   358,   359,   360,   361,
       0,   362,   363,   364,   365,   366,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   367,     0,     0,     0,
     -98,  -118,     0,   -98,  -118,  -118,  -118,  -118,  -118,  -118,
    -118,  -118,     0,  -118,  -118,  -118,  -118,  -118,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -118,     0,
       0,     0,  -118,  -117,     0,  -118,  -117,  -117,  -117,  -117,
    -117,  -117,  -117,  -117,     0,  -117,  -117,  -117,  -117,  -117,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -117,     0,     0,     0,  -117,   -76,    27,  -117,   -76,   -76,
     -76,   -76,   -76,   -76,   -76,   -76,    28,   -76,   -76,   -76,
     -76,   -76,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -76,     0,  -100,   -74,   -76,     0,   -74,   -74,
     -74,   -74,   -74,   -74,   -74,   -74,     0,   -74,   -74,   -74,
     -74,   -74,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -74,     0,   -75,     0,   -74,   -75,   -75,   -75,
     -75,   -75,   -75,   -75,   -75,     0,   -75,   -75,   -75,   -75,
     -75,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -75,     0,   -71,     0,   -75,   -71,   -71,   -71,   -71,
     -71,   -71,   -71,   -71,     0,   -71,   -71,   -71,   -71,   -71,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -71,     0,   -72,     0,   -71,   -72,   -72,   -72,   -72,   -72,
     -72,   -72,   -72,     0,   -72,   -72,   -72,   -72,   -72,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -72,
       0,   -73,     0,   -72,   -73,   -73,   -73,   -73,   -73,   -73,
     -73,   -73,     0,   -73,   -73,   -73,   -73,   -73,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -73,     0,
      51,     0,   -73,    52,    53,    54,    55,    56,    57,    58,
      59,     0,    60,    61,    62,    63,    64,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    65,     0,   -77,
       0,    66,   -77,   -77,   -77,   -77,   -77,   -77,   -77,   -77,
       0,   -77,   -77,   -77,   -77,   -77,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -77,     0,   -84,     0,
     -77,   -84,   -84,   -84,   -84,   -84,   -84,   -84,   -84,     0,
     -84,   -84,   -84,   -84,   -84,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -84,     0,   -78,     0,   -84,
     -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,     0,   -78,
     -78,   -78,   -78,   -78,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -78,     0,   -79,     0,   -78,   -79,
     -79,   -79,   -79,   -79,   -79,   -79,   -79,     0,   -79,   -79,
     -79,   -79,   -79,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -79,     0,   -80,     0,   -79,   -80,   -80,
     -80,   -80,   -80,   -80,   -80,   -80,     0,   -80,   -80,   -80,
     -80,   -80,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -80,     0,   -81,     0,   -80,   -81,   -81,   -81,
     -81,   -81,   -81,   -81,   -81,     0,   -81,   -81,   -81,   -81,
     -81,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -81,     0,   -82,     0,   -81,   -82,   -82,   -82,   -82,
     -82,   -82,   -82,   -82,     0,   -82,   -82,   -82,   -82,   -82,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -82,     0,   -83,     0,   -82,   -83,   -83,   -83,   -83,   -83,
     -83,   -83,   -83,     0,   -83,   -83,   -83,   -83,   -83,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -83,
       0,    51,     0,   -83,    52,    53,    54,    55,    56,    57,
      58,    59,     0,    60,    61,    62,    63,    64,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    65,     0,
    -116,     0,    85,  -116,  -116,  -116,  -116,  -116,  -116,  -116,
    -116,     0,  -116,  -116,  -116,  -116,  -116,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -116,     0,    51,
       0,  -116,    52,    53,    54,    55,    56,    57,    58,    59,
       0,    60,    61,    62,    63,    64,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    65,     0,  -101,     0,
     -99,  -101,  -101,  -101,  -101,  -101,  -101,  -101,  -101,     0,
    -101,  -101,  -101,  -101,  -101,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -101,     0,  -102,     0,  -101,
    -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,     0,  -102,
    -102,  -102,  -102,  -102,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -102,     0,   -90,     0,  -102,   -90,
     -90,   -90,   -90,   -90,   -90,   -90,   -90,     0,   -90,   -90,
     -90,   -90,   -90,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -90,     0,  -108,     0,   -90,  -108,  -108,
    -108,  -108,  -108,  -108,  -108,  -108,     0,  -108,  -108,  -108,
    -108,  -108,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -108,     0,    51,     0,  -108,   -91,   -91,   -91,
     -91,   -91,   -91,   -91,   -91,     0,    60,    61,    62,    63,
      64,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -91,     0,  -109,     0,   -91,  -109,  -109,  -109,  -109,
    -109,  -109,  -109,  -109,     0,  -109,  -109,  -109,  -109,  -109,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -109,     0,    51,     0,  -109,    52,   -92,   -92,   -92,   -92,
     -92,   -92,   -92,     0,    60,    61,    62,    63,    64,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -92,
       0,  -110,     0,   -92,  -110,  -110,  -110,  -110,  -110,  -110,
    -110,  -110,     0,  -110,  -110,  -110,  -110,  -110,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -110,     0,
      51,     0,  -110,    52,    53,   -93,   -93,   -93,   -93,   -93,
     -93,     0,    60,    61,    62,    63,    64,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -93,     0,  -111,
       0,   -93,  -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,
       0,  -111,  -111,  -111,  -111,  -111,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -111,     0,    51,     0,
    -111,    52,    53,    54,   -94,   -94,   -94,   -94,   -94,     0,
      60,    61,    62,    63,    64,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -94,     0,  -112,     0,   -94,
    -112,  -112,  -112,  -112,  -112,  -112,  -112,  -112,     0,  -112,
    -112,  -112,  -112,  -112,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -112,     0,    51,     0,  -112,    52,
      53,    54,    55,   -95,   -95,   -95,   -95,     0,    60,    61,
      62,    63,    64,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -95,     0,  -113,     0,   -95,  -113,  -113,
    -113,  -113,  -113,  -113,  -113,  -113,     0,  -113,  -113,  -113,
    -113,  -113,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -113,     0,    51,     0,  -113,    52,    53,    54,
      55,    56,   -96,   -96,   -96,     0,    60,    61,    62,    63,
      64,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -96,     0,  -114,     0,   -96,  -114,  -114,  -114,  -114,
    -114,  -114,  -114,  -114,     0,  -114,  -114,  -114,  -114,  -114,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -114,     0,    51,     0,  -114,    52,    53,    54,    55,    56,
      57,   -97,   -97,     0,    60,    61,    62,    63,    64,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -97,
       0,  -115,     0,   -97,  -115,  -115,  -115,  -115,  -115,  -115,
    -115,  -115,     0,  -115,  -115,  -115,  -115,  -115,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -115,     0,
    -103,     0,  -115,  -103,  -103,  -103,  -103,  -103,  -103,  -103,
    -103,     0,  -103,  -103,  -103,  -103,  -103,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -103,     0,    51,
       0,  -103,   -85,   -85,   -85,   -85,   -85,   -85,   -85,   -85,
       0,   -85,   -85,   -85,   -85,   -85,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -85,     0,  -104,     0,
     -85,  -104,  -104,  -104,  -104,  -104,  -104,  -104,  -104,     0,
    -104,  -104,  -104,  -104,  -104,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -104,     0,    51,     0,  -104,
     -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,     0,   -86,
     -86,   -86,   -86,   -86,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -86,     0,  -106,     0,   -86,  -106,
    -106,  -106,  -106,  -106,  -106,  -106,  -106,     0,  -106,  -106,
    -106,  -106,  -106,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -106,     0,    51,     0,  -106,   -88,   -88,
     -88,   -88,   -88,   -88,   -88,   -88,     0,    60,    61,   -88,
     -88,    64,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -88,     0,  -107,     0,   -88,  -107,  -107,  -107,
    -107,  -107,  -107,  -107,  -107,     0,  -107,  -107,  -107,  -107,
    -107,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -107,     0,    51,     0,  -107,   -89,   -89,   -89,   -89,
     -89,   -89,   -89,   -89,     0,    60,    61,   -89,   -89,    64,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -89,     0,  -105,     0,   -89,  -105,  -105,  -105,  -105,  -105,
    -105,  -105,  -105,     0,  -105,  -105,  -105,  -105,  -105,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -105,
       0,    51,     0,  -105,   -87,   -87,   -87,   -87,   -87,   -87,
     -87,   -87,     0,   -87,   -87,   -87,   -87,   -87,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -87,     0,
      51,     0,   -87,    52,    53,    54,    55,    56,    57,    58,
      59,     0,    60,    61,    62,    63,    64,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    65,     0,  -118,
       0,   -59,  -118,  -118,  -118,  -118,  -118,  -118,  -118,  -118,
       0,  -118,  -118,  -118,  -118,  -118,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -118,     0,  -117,     0,
    -118,  -117,  -117,  -117,  -117,  -117,  -117,  -117,  -117,     0,
    -117,  -117,  -117,  -117,  -117,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -117,     0,    51,     0,  -117,
      52,    53,    54,    55,    56,    57,    58,    59,     0,    60,
      61,    62,    63,    64,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    65,     0,    51,     0,   -64,    52,
      53,    54,    55,    56,    57,    58,    59,     0,    60,    61,
      62,    63,    64,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    65,     0,    51,     0,   -98,    52,    53,
      54,    55,    56,    57,    58,    59,     0,    60,    61,    62,
      63,    64,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    65,     0,    51,     0,   417,    52,    53,    54,
      55,    56,    57,    58,    59,     0,    60,    61,    62,    63,
      64,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    65,     0,    51,     0,   504,    52,    53,    54,    55,
      56,    57,    58,    59,     0,    60,    61,    62,    63,    64,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      65,     0,    51,     0,   564,    52,    53,    54,    55,    56,
      57,    58,    59,     0,    60,    61,    62,    63,    64,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    65,
       0,    51,     0,   592,    52,    53,    54,    55,    56,    57,
      58,    59,     0,    60,    61,    62,    63,    64,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    65,     0,
      51,     0,   695,    52,    53,    54,    55,    56,    57,    58,
      59,     0,    60,    61,    62,    63,    64,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    65,     0,   -76,
     368,   721,   -76,   -76,   -76,   -76,   -76,   -76,   -76,   -76,
     369,   -76,   -76,   -76,   -76,   -76,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -76,   244,  -100,   -76,
     245,   246,   247,   248,   249,   250,   251,   252,     0,   253,
     254,   255,   256,   257,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   258,   244,     0,    86,   245,   246,
     247,   248,   249,   250,   251,   252,     0,   253,   254,   255,
     256,   257,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   258,   244,     0,   128,   245,   246,   247,   248,
     249,   250,   251,   252,     0,   253,   254,   255,   256,   257,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     258,   244,     0,   130,   245,   246,   247,   248,   249,   250,
     251,   252,     0,   253,   254,   255,   256,   257,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   258,   -74,
       0,   132,   -74,   -74,   -74,   -74,   -74,   -74,   -74,   -74,
       0,   -74,   -74,   -74,   -74,   -74,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -74,   -75,     0,   -74,
     -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,     0,   -75,
     -75,   -75,   -75,   -75,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -75,   -71,     0,   -75,   -71,   -71,
     -71,   -71,   -71,   -71,   -71,   -71,     0,   -71,   -71,   -71,
     -71,   -71,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -71,   -72,     0,   -71,   -72,   -72,   -72,   -72,
     -72,   -72,   -72,   -72,     0,   -72,   -72,   -72,   -72,   -72,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -72,   -73,     0,   -72,   -73,   -73,   -73,   -73,   -73,   -73,
     -73,   -73,     0,   -73,   -73,   -73,   -73,   -73,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -73,   -77,
       0,   -73,   -77,   -77,   -77,   -77,   -77,   -77,   -77,   -77,
       0,   -77,   -77,   -77,   -77,   -77,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -77,   -84,     0,   -77,
     -84,   -84,   -84,   -84,   -84,   -84,   -84,   -84,     0,   -84,
     -84,   -84,   -84,   -84,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -84,   -78,     0,   -84,   -78,   -78,
     -78,   -78,   -78,   -78,   -78,   -78,     0,   -78,   -78,   -78,
     -78,   -78,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -78,   -79,     0,   -78,   -79,   -79,   -79,   -79,
     -79,   -79,   -79,   -79,     0,   -79,   -79,   -79,   -79,   -79,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -79,   -80,     0,   -79,   -80,   -80,   -80,   -80,   -80,   -80,
     -80,   -80,     0,   -80,   -80,   -80,   -80,   -80,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -80,   -81,
       0,   -80,   -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,
       0,   -81,   -81,   -81,   -81,   -81,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -81,   -82,     0,   -81,
     -82,   -82,   -82,   -82,   -82,   -82,   -82,   -82,     0,   -82,
     -82,   -82,   -82,   -82,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -82,   -83,     0,   -82,   -83,   -83,
     -83,   -83,   -83,   -83,   -83,   -83,     0,   -83,   -83,   -83,
     -83,   -83,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -83,   244,     0,   -83,   245,   246,   247,   248,
     249,   250,   251,   252,     0,   253,   254,   255,   256,   257,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     258,   -90,     0,   550,   -90,   -90,   -90,   -90,   -90,   -90,
     -90,   -90,     0,   -90,   -90,   -90,   -90,   -90,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -90,  -108,
       0,   -90,  -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,
       0,  -108,  -108,  -108,  -108,  -108,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -108,   244,     0,  -108,
     -91,   -91,   -91,   -91,   -91,   -91,   -91,   -91,     0,   253,
     254,   255,   256,   257,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -91,  -109,     0,   -91,  -109,  -109,
    -109,  -109,  -109,  -109,  -109,  -109,     0,  -109,  -109,  -109,
    -109,  -109,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -109,   244,     0,  -109,   245,   -92,   -92,   -92,
     -92,   -92,   -92,   -92,     0,   253,   254,   255,   256,   257,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -92,  -110,     0,   -92,  -110,  -110,  -110,  -110,  -110,  -110,
    -110,  -110,     0,  -110,  -110,  -110,  -110,  -110,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -110,   244,
       0,  -110,   245,   246,   -93,   -93,   -93,   -93,   -93,   -93,
       0,   253,   254,   255,   256,   257,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -93,  -111,     0,   -93,
    -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,     0,  -111,
    -111,  -111,  -111,  -111,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -111,   244,     0,  -111,   245,   246,
     247,   -94,   -94,   -94,   -94,   -94,     0,   253,   254,   255,
     256,   257,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -94,  -112,     0,   -94,  -112,  -112,  -112,  -112,
    -112,  -112,  -112,  -112,     0,  -112,  -112,  -112,  -112,  -112,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -112,   244,     0,  -112,   245,   246,   247,   248,   -95,   -95,
     -95,   -95,     0,   253,   254,   255,   256,   257,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -95,  -113,
       0,   -95,  -113,  -113,  -113,  -113,  -113,  -113,  -113,  -113,
       0,  -113,  -113,  -113,  -113,  -113,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -113,   244,     0,  -113,
     245,   246,   247,   248,   249,   -96,   -96,   -96,     0,   253,
     254,   255,   256,   257,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -96,  -114,     0,   -96,  -114,  -114,
    -114,  -114,  -114,  -114,  -114,  -114,     0,  -114,  -114,  -114,
    -114,  -114,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -114,   244,     0,  -114,   245,   246,   247,   248,
     249,   250,   -97,   -97,     0,   253,   254,   255,   256,   257,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -97,  -115,     0,   -97,  -115,  -115,  -115,  -115,  -115,  -115,
    -115,  -115,     0,  -115,  -115,  -115,  -115,  -115,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -115,  -103,
       0,  -115,  -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,
       0,  -103,  -103,  -103,  -103,  -103,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -103,   244,     0,  -103,
     -85,   -85,   -85,   -85,   -85,   -85,   -85,   -85,     0,   -85,
     -85,   -85,   -85,   -85,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -85,  -104,     0,   -85,  -104,  -104,
    -104,  -104,  -104,  -104,  -104,  -104,     0,  -104,  -104,  -104,
    -104,  -104,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -104,   244,     0,  -104,   -86,   -86,   -86,   -86,
     -86,   -86,   -86,   -86,     0,   -86,   -86,   -86,   -86,   -86,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -86,  -106,     0,   -86,  -106,  -106,  -106,  -106,  -106,  -106,
    -106,  -106,     0,  -106,  -106,  -106,  -106,  -106,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -106,   244,
       0,  -106,   -88,   -88,   -88,   -88,   -88,   -88,   -88,   -88,
       0,   253,   254,   -88,   -88,   257,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -88,  -107,     0,   -88,
    -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,     0,  -107,
    -107,  -107,  -107,  -107,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -107,   244,     0,  -107,   -89,   -89,
     -89,   -89,   -89,   -89,   -89,   -89,     0,   253,   254,   -89,
     -89,   257,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -89,  -105,     0,   -89,  -105,  -105,  -105,  -105,
    -105,  -105,  -105,  -105,     0,  -105,  -105,  -105,  -105,  -105,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -105,   244,     0,  -105,   -87,   -87,   -87,   -87,   -87,   -87,
     -87,   -87,     0,   -87,   -87,   -87,   -87,   -87,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -87,   244,
       0,   -87,   245,   246,   247,   248,   249,   250,   251,   252,
       0,   253,   254,   255,   256,   257,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   258,   244,     0,   572,
     245,   246,   247,   248,   249,   250,   251,   252,     0,   253,
     254,   255,   256,   257,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   258,   244,     0,   577,   245,   246,
     247,   248,   249,   250,   251,   252,     0,   253,   254,   255,
     256,   257,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   258,   244,     0,   -64,   245,   246,   247,   248,
     249,   250,   251,   252,     0,   253,   254,   255,   256,   257,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     258,  -116,     0,   600,  -116,  -116,  -116,  -116,  -116,  -116,
    -116,  -116,     0,  -116,  -116,  -116,  -116,  -116,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -116,   244,
       0,  -116,   245,   246,   247,   248,   249,   250,   251,   252,
       0,   253,   254,   255,   256,   257,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   258,  -101,     0,   -99,
    -101,  -101,  -101,  -101,  -101,  -101,  -101,  -101,     0,  -101,
    -101,  -101,  -101,  -101,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -101,  -102,     0,  -101,  -102,  -102,
    -102,  -102,  -102,  -102,  -102,  -102,     0,  -102,  -102,  -102,
    -102,  -102,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -102,   244,     0,  -102,   245,   246,   247,   248,
     249,   250,   251,   252,     0,   253,   254,   255,   256,   257,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     258,   244,     0,   609,   245,   246,   247,   248,   249,   250,
     251,   252,     0,   253,   254,   255,   256,   257,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   258,   244,
       0,   611,   245,   246,   247,   248,   249,   250,   251,   252,
       0,   253,   254,   255,   256,   257,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   258,   244,     0,   613,
     245,   246,   247,   248,   249,   250,   251,   252,     0,   253,
     254,   255,   256,   257,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   258,   244,     0,   626,   245,   246,
     247,   248,   249,   250,   251,   252,     0,   253,   254,   255,
     256,   257,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   258,   244,     0,   628,   245,   246,   247,   248,
     249,   250,   251,   252,     0,   253,   254,   255,   256,   257,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     258,   244,     0,   630,   245,   246,   247,   248,   249,   250,
     251,   252,     0,   253,   254,   255,   256,   257,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   258,  -118,
       0,   -98,  -118,  -118,  -118,  -118,  -118,  -118,  -118,  -118,
       0,  -118,  -118,  -118,  -118,  -118,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -118,  -117,     0,  -118,
    -117,  -117,  -117,  -117,  -117,  -117,  -117,  -117,     0,  -117,
    -117,  -117,  -117,  -117,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -117,   244,     0,  -117,   245,   246,
     247,   248,   249,   250,   251,   252,     0,   253,   254,   255,
     256,   257,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   258,   244,     0,   742,   245,   246,   247,   248,
     249,   250,   251,   252,     0,   253,   254,   255,   256,   257,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     258,   244,     0,   744,   245,   246,   247,   248,   249,   250,
     251,   252,     0,   253,   254,   255,   256,   257,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   258,   -76,
     418,   746,   -76,   -76,   -76,   -76,   -76,   -76,   -76,   -76,
     419,   -76,   -76,   -76,   -76,   -76,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -76,   -76,  -100,   297,
       0,     0,   298,   299,   300,   301,   302,   303,   304,   305,
       0,   306,   307,   308,   309,   310,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -74,   311,   140,   -74,   -74,
     -74,   -74,   -74,   -74,   -74,   -74,     0,   -74,   -74,   -74,
     -74,   -74,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -75,   -74,   -74,   -75,   -75,   -75,   -75,   -75,   -75,
     -75,   -75,     0,   -75,   -75,   -75,   -75,   -75,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -71,   -75,   -75,
     -71,   -71,   -71,   -71,   -71,   -71,   -71,   -71,     0,   -71,
     -71,   -71,   -71,   -71,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -72,   -71,   -71,   -72,   -72,   -72,   -72,
     -72,   -72,   -72,   -72,     0,   -72,   -72,   -72,   -72,   -72,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -73,
     -72,   -72,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,
       0,   -73,   -73,   -73,   -73,   -73,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   297,   -73,   -73,   298,   299,
     300,   301,   302,   303,   304,   305,     0,   306,   307,   308,
     309,   310,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -77,   311,   551,   -77,   -77,   -77,   -77,   -77,   -77,
     -77,   -77,     0,   -77,   -77,   -77,   -77,   -77,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -84,   -77,   -77,
     -84,   -84,   -84,   -84,   -84,   -84,   -84,   -84,     0,   -84,
     -84,   -84,   -84,   -84,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -78,   -84,   -84,   -78,   -78,   -78,   -78,
     -78,   -78,   -78,   -78,     0,   -78,   -78,   -78,   -78,   -78,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -79,
     -78,   -78,   -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,
       0,   -79,   -79,   -79,   -79,   -79,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -80,   -79,   -79,   -80,   -80,
     -80,   -80,   -80,   -80,   -80,   -80,     0,   -80,   -80,   -80,
     -80,   -80,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -81,   -80,   -80,   -81,   -81,   -81,   -81,   -81,   -81,
     -81,   -81,     0,   -81,   -81,   -81,   -81,   -81,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -82,   -81,   -81,
     -82,   -82,   -82,   -82,   -82,   -82,   -82,   -82,     0,   -82,
     -82,   -82,   -82,   -82,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -83,   -82,   -82,   -83,   -83,   -83,   -83,
     -83,   -83,   -83,   -83,     0,   -83,   -83,   -83,   -83,   -83,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -90,
     -83,   -83,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,
       0,   -90,   -90,   -90,   -90,   -90,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -108,   -90,   -90,  -108,  -108,
    -108,  -108,  -108,  -108,  -108,  -108,     0,  -108,  -108,  -108,
    -108,  -108,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   297,  -108,  -108,   -91,   -91,   -91,   -91,   -91,   -91,
     -91,   -91,     0,   306,   307,   308,   309,   310,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -109,   -91,   -91,
    -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,     0,  -109,
    -109,  -109,  -109,  -109,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   297,  -109,  -109,   298,   -92,   -92,   -92,
     -92,   -92,   -92,   -92,     0,   306,   307,   308,   309,   310,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -110,
     -92,   -92,  -110,  -110,  -110,  -110,  -110,  -110,  -110,  -110,
       0,  -110,  -110,  -110,  -110,  -110,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   297,  -110,  -110,   298,   299,
     -93,   -93,   -93,   -93,   -93,   -93,     0,   306,   307,   308,
     309,   310,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -111,   -93,   -93,  -111,  -111,  -111,  -111,  -111,  -111,
    -111,  -111,     0,  -111,  -111,  -111,  -111,  -111,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   297,  -111,  -111,
     298,   299,   300,   -94,   -94,   -94,   -94,   -94,     0,   306,
     307,   308,   309,   310,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -112,   -94,   -94,  -112,  -112,  -112,  -112,
    -112,  -112,  -112,  -112,     0,  -112,  -112,  -112,  -112,  -112,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   297,
    -112,  -112,   298,   299,   300,   301,   -95,   -95,   -95,   -95,
       0,   306,   307,   308,   309,   310,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -113,   -95,   -95,  -113,  -113,
    -113,  -113,  -113,  -113,  -113,  -113,     0,  -113,  -113,  -113,
    -113,  -113,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   297,  -113,  -113,   298,   299,   300,   301,   302,   -96,
     -96,   -96,     0,   306,   307,   308,   309,   310,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -114,   -96,   -96,
    -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,     0,  -114,
    -114,  -114,  -114,  -114,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   297,  -114,  -114,   298,   299,   300,   301,
     302,   303,   -97,   -97,     0,   306,   307,   308,   309,   310,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -115,
     -97,   -97,  -115,  -115,  -115,  -115,  -115,  -115,  -115,  -115,
       0,  -115,  -115,  -115,  -115,  -115,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -103,  -115,  -115,  -103,  -103,
    -103,  -103,  -103,  -103,  -103,  -103,     0,  -103,  -103,  -103,
    -103,  -103,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   297,  -103,  -103,   -85,   -85,   -85,   -85,   -85,   -85,
     -85,   -85,     0,   -85,   -85,   -85,   -85,   -85,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -104,   -85,   -85,
    -104,  -104,  -104,  -104,  -104,  -104,  -104,  -104,     0,  -104,
    -104,  -104,  -104,  -104,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   297,  -104,  -104,   -86,   -86,   -86,   -86,
     -86,   -86,   -86,   -86,     0,   -86,   -86,   -86,   -86,   -86,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -106,
     -86,   -86,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,
       0,  -106,  -106,  -106,  -106,  -106,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   297,  -106,  -106,   -88,   -88,
     -88,   -88,   -88,   -88,   -88,   -88,     0,   306,   307,   -88,
     -88,   310,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -107,   -88,   -88,  -107,  -107,  -107,  -107,  -107,  -107,
    -107,  -107,     0,  -107,  -107,  -107,  -107,  -107,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   297,  -107,  -107,
     -89,   -89,   -89,   -89,   -89,   -89,   -89,   -89,     0,   306,
     307,   -89,   -89,   310,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -105,   -89,   -89,  -105,  -105,  -105,  -105,
    -105,  -105,  -105,  -105,     0,  -105,  -105,  -105,  -105,  -105,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   297,
    -105,  -105,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,
       0,   -87,   -87,   -87,   -87,   -87,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   297,   -87,   -87,   298,   299,
     300,   301,   302,   303,   304,   305,     0,   306,   307,   308,
     309,   310,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   297,   311,   578,   298,   299,   300,   301,   302,   303,
     304,   305,     0,   306,   307,   308,   309,   310,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   297,   311,   579,
     298,   299,   300,   301,   302,   303,   304,   305,     0,   306,
     307,   308,   309,   310,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -116,   311,   601,  -116,  -116,  -116,  -116,
    -116,  -116,  -116,  -116,     0,  -116,  -116,  -116,  -116,  -116,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   297,
    -116,  -116,   298,   299,   300,   301,   302,   303,   304,   305,
       0,   306,   307,   308,   309,   310,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -101,   311,   -99,  -101,  -101,
    -101,  -101,  -101,  -101,  -101,  -101,     0,  -101,  -101,  -101,
    -101,  -101,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -102,  -101,  -101,  -102,  -102,  -102,  -102,  -102,  -102,
    -102,  -102,     0,  -102,  -102,  -102,  -102,  -102,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   297,  -102,  -102,
     298,   299,   300,   301,   302,   303,   304,   305,     0,   306,
     307,   308,   309,   310,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -118,   311,   -98,  -118,  -118,  -118,  -118,
    -118,  -118,  -118,  -118,     0,  -118,  -118,  -118,  -118,  -118,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -117,
    -118,  -118,  -117,  -117,  -117,  -117,  -117,  -117,  -117,  -117,
       0,  -117,  -117,  -117,  -117,  -117,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -117,  -117
};

static const yytype_int16 yycheck[] =
{
       0,   119,   263,   552,   138,   259,   406,     7,     8,     9,
      10,    11,    12,    13,   707,   659,   562,   408,    18,   680,
      20,     1,    38,   153,   734,     0,   370,     7,    28,   607,
     756,   580,    72,   677,    38,   728,    38,   698,   234,   642,
     750,    41,    42,    43,   590,   175,   624,   773,     1,    49,
      38,    51,    52,    53,    54,    55,    56,    57,    58,   189,
      60,    61,    62,    63,    64,    65,   669,   604,   548,    69,
     331,     1,     1,   327,    49,   205,   420,   273,     1,   805,
       0,   121,   122,    83,   621,     8,     0,   431,    41,   799,
     570,   287,    41,     1,   494,   575,    38,     1,   791,     1,
       0,    38,     1,     7,     8,   496,    40,     1,     1,     8,
       1,    41,    41,   136,     7,     8,   777,    38,   598,    40,
      43,     1,    43,    40,    40,   769,    43,   127,   128,   129,
     130,   131,   132,    41,   134,    49,     1,    39,   138,    43,
     140,   141,   182,   166,    43,    39,    39,   343,    39,     1,
      38,    40,   127,   128,   129,   130,   131,   132,   761,    39,
     709,   184,   740,   138,     1,    39,   510,    39,     1,     1,
       7,     8,     1,   719,     7,     8,    39,     7,     8,   179,
     180,   181,     1,   183,     1,   208,     0,    39,     7,     8,
       7,     8,    38,   216,    40,     7,     7,    43,   221,     8,
     737,    42,    39,   226,   179,   180,    39,    39,   183,    39,
      39,     1,    40,   127,   128,   129,   130,   131,   132,   259,
      39,    39,    39,     7,   138,   225,    38,    38,    40,    40,
      39,    43,    43,    39,    43,   235,   236,   237,   238,   239,
     240,   241,    41,   243,   244,   245,   246,   247,   248,   249,
     250,   251,    50,   253,   254,   255,   256,   257,   258,    40,
      40,    39,    43,    44,   264,   179,   180,    40,    38,   183,
      40,    40,     1,    43,   274,   275,   276,   277,   278,   279,
     280,   415,   282,    40,   684,    41,    43,   327,   288,   289,
     290,   291,   292,   293,   294,   686,   296,   297,   298,   299,
     300,   301,   302,   303,   304,    39,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
      40,   321,   322,   323,   324,   325,   326,     0,    38,     7,
      40,    40,   332,    43,    43,    40,   336,     7,    43,     8,
       8,     7,     1,     1,   344,   345,   346,   347,   348,   349,
     350,    41,   352,   353,   354,   355,   356,   357,   358,   359,
     360,    40,   362,   363,   364,   365,   366,   367,    38,   369,
      40,    39,    38,    43,    40,    43,   506,    43,     7,    39,
      42,     1,    39,    39,     1,    40,    39,   648,   186,     1,
     644,    42,    42,     7,    40,    42,   194,     1,     1,    44,
       3,     4,     5,     6,     7,   203,    39,    39,    11,   409,
     410,   411,   210,    40,     1,    38,    38,    38,    21,   419,
      23,    24,    41,    26,    27,    28,     1,     1,    38,    38,
     430,    38,    35,     1,     7,    38,   554,     8,     1,    41,
     415,     9,    10,    38,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    38,     3,
       4,     5,     6,     7,   582,   595,    38,    11,    36,    38,
      38,    39,    38,    40,    38,    43,    38,    21,     7,    23,
      24,   615,    26,    27,    28,    40,   604,    38,    40,    39,
      39,    35,    39,    39,    38,    40,    40,   497,   498,   499,
      42,    42,    39,   621,     1,    39,    42,    39,    39,   509,
      40,    39,     9,   553,    40,    12,    13,    14,    15,    16,
      17,    18,    19,    39,    21,    22,    23,    24,    25,     3,
       4,     5,     6,     7,     8,    39,    39,    11,     1,    36,
      41,   581,    39,    39,    38,    38,    43,    21,   548,    23,
      24,   551,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,   562,    38,    38,    41,    40,    41,    42,    42,
     570,    41,    39,     1,    38,   575,    41,    38,   578,   579,
      40,    39,    41,    40,    40,    39,    39,    42,    40,     1,
     590,    42,    42,   711,    40,    39,    39,    42,   598,     1,
      42,   601,    42,    41,   644,    39,    42,    42,   608,   609,
      41,     1,    42,    40,     1,   566,    42,    42,   416,   737,
      42,    42,   266,    -1,    -1,   625,   626,   627,   628,   629,
     630,   227,    -1,   608,   609,   610,   611,   612,   613,    -1,
     615,    -1,   169,    -1,    -1,    -1,    -1,    -1,    -1,   649,
     625,   626,   627,   628,   629,   630,    -1,    -1,    -1,     1,
      -1,     3,     4,     5,     6,     7,    -1,    -1,    -1,    11,
     710,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,
      -1,    23,    24,    -1,    26,    27,    28,   687,   688,   689,
      -1,    -1,    -1,    35,   608,   609,    38,    39,    -1,    -1,
      -1,    -1,   702,   703,   704,   503,    -1,    -1,    -1,    -1,
      -1,   625,   626,   627,   628,   629,   630,    -1,   693,   719,
      -1,   696,   697,    -1,    -1,    -1,    -1,   702,   703,   704,
       3,     4,     5,     6,     7,    -1,    -1,    -1,    11,    -1,
      -1,   741,   742,   743,   744,   745,   746,    -1,    21,    -1,
      23,    24,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    -1,    -1,    38,   741,   742,   743,   744,
     745,   746,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   781,   782,   783,    -1,    -1,    -1,    -1,   702,   703,
     704,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    -1,    -1,    -1,    -1,   781,   782,   783,     9,
      -1,    -1,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,   741,   742,   743,
     744,   745,   746,    -1,    -1,    -1,    36,     1,    -1,    39,
      -1,    -1,    -1,    43,    -1,     9,    -1,    -1,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,   781,   782,   783,
       1,    -1,    36,    -1,    -1,    39,    -1,    -1,     9,    43,
      -1,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      21,    22,    23,    24,    25,    -1,   694,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    -1,    36,    -1,   705,    39,    -1,
     708,     9,    43,    -1,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,   726,    -1,
      -1,   729,    -1,    -1,    -1,    -1,    -1,   735,    36,    -1,
      -1,    39,    -1,    -1,    -1,    43,     1,    -1,    -1,    -1,
      -1,    -1,    -1,   751,     9,    -1,   754,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    21,    22,    23,    24,
      25,    -1,    -1,   771,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,    -1,    -1,    39,    -1,    -1,    -1,    43,    -1,
      -1,   789,    -1,    -1,   792,     1,    -1,    -1,    -1,    -1,
      -1,    -1,   800,     9,    -1,   803,    12,    13,    14,    15,
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
       0,    -1,    -1,     3,     4,     5,     6,     7,     8,    -1,
      36,    11,    -1,    39,    -1,    -1,    -1,    43,    -1,    -1,
      -1,    21,    -1,    23,    24,    -1,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    -1,    -1,    38,     0,
      40,    41,     3,     4,     5,     6,     7,     8,    -1,    -1,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      21,    -1,    23,    24,    -1,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    -1,    -1,    38,     0,    40,
      41,     3,     4,     5,     6,     7,     8,    -1,    -1,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,
      -1,    23,    24,    -1,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    -1,    -1,    38,     0,    40,    41,
       3,     4,     5,     6,     7,     8,    -1,    -1,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,
      23,    24,    -1,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    -1,    -1,    38,     0,    40,    41,     3,
       4,     5,     6,     7,     8,    -1,    -1,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,
      24,    -1,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    -1,    -1,    38,     0,    40,    41,     3,     4,
       5,     6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,
      -1,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    -1,    -1,    38,     0,    40,    41,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    38,     0,    40,    41,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    -1,
      -1,    38,     0,    40,    41,     3,     4,     5,     6,     7,
       8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    -1,    -1,
      38,     0,    40,    41,     3,     4,     5,     6,     7,     8,
      -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    21,    -1,    23,    24,    -1,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    -1,    -1,    38,
       0,    40,    41,     3,     4,     5,     6,     7,     8,    -1,
      -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    21,    -1,    23,    24,    -1,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    -1,    -1,    38,     0,
      40,    41,     3,     4,     5,     6,     7,     8,    -1,    -1,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      21,    -1,    23,    24,    -1,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    -1,    -1,    38,     0,    40,
      41,     3,     4,     5,     6,     7,     8,    -1,    -1,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,
      -1,    23,    24,    -1,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    -1,    -1,    38,     0,    40,    41,
       3,     4,     5,     6,     7,     8,    -1,    -1,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,
      23,    24,    -1,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    -1,    -1,    38,     0,    40,    41,     3,
       4,     5,     6,     7,     8,    -1,    -1,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,
      24,    -1,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    -1,    -1,    38,     0,    40,    41,     3,     4,
       5,     6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,
      -1,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    -1,    -1,    38,     0,    40,    41,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    38,     0,    40,    41,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    -1,
      -1,    38,     0,    40,    41,     3,     4,     5,     6,     7,
       8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    -1,    -1,
      38,     0,    40,    41,     3,     4,     5,     6,     7,     8,
      -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    21,    -1,    23,    24,    -1,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    -1,    -1,    38,
       0,    40,    41,     3,     4,     5,     6,     7,     8,    -1,
      -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    21,    -1,    23,    24,    -1,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    -1,    -1,    38,     0,
      40,    41,     3,     4,     5,     6,     7,     8,    -1,    -1,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      21,    -1,    23,    24,    -1,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    -1,    -1,    38,     0,    40,
      41,     3,     4,     5,     6,     7,     8,    -1,    -1,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,
      -1,    23,    24,    -1,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    -1,    -1,    38,     0,    40,    41,
       3,     4,     5,     6,     7,     8,    -1,    -1,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,
      23,    24,    -1,    26,    27,    28,    29,    30,    31,    32,
      -1,    34,    35,    -1,    -1,    38,     0,    40,    41,     3,
       4,     5,     6,     7,     8,    -1,    -1,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,
      24,    -1,    26,    27,    28,    29,    30,    31,    32,    -1,
      34,    35,    -1,    -1,    38,     0,    40,    41,     3,     4,
       5,     6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,
      -1,    26,    27,    28,    29,    30,    31,    32,    -1,    34,
      35,    -1,    -1,    38,     0,    40,    41,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      -1,    -1,    38,     0,    40,    41,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    -1,
      -1,    38,     0,    40,    41,     3,     4,     5,     6,     7,
       8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,    27,
      28,    29,    30,    31,    32,    -1,    34,    35,    -1,    -1,
      38,     0,    40,    41,     3,     4,     5,     6,     7,     8,
      -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    21,    -1,    23,    24,    -1,    26,    27,    28,
      29,    30,    31,    32,    -1,    34,    35,    -1,    -1,    38,
       0,    40,    41,     3,     4,     5,     6,     7,     8,    -1,
      -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    21,    -1,    23,    24,    -1,    26,    27,    28,    29,
      30,    31,    32,    -1,    34,    35,    -1,    -1,    38,     0,
      40,    41,     3,     4,     5,     6,     7,     8,    -1,    -1,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      21,    -1,    23,    24,    -1,    26,    27,    28,    29,    30,
      31,    32,    -1,    34,    35,    -1,    -1,    38,     0,    40,
      41,     3,     4,     5,     6,     7,     8,    -1,    -1,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,
      -1,    23,    24,    -1,    26,    27,    28,    29,    30,    31,
      32,    -1,    34,    35,    -1,    -1,    38,     0,    40,    41,
       3,     4,     5,     6,     7,     8,    -1,    -1,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,
      23,    24,    -1,    26,    27,    28,    29,    30,    31,    32,
      -1,    34,    35,    -1,    -1,    38,     0,    40,    41,     3,
       4,     5,     6,     7,     8,    -1,    -1,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,
      24,    -1,    26,    27,    28,    29,    30,    31,    32,    -1,
      34,    35,    -1,    -1,    38,     0,    40,    41,     3,     4,
       5,     6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,
      -1,    26,    27,    28,    29,    30,    31,    32,    -1,    34,
      35,    -1,    -1,    38,     0,    40,    41,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      -1,    -1,    38,     0,    40,    41,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    -1,
      -1,    38,     0,    40,    41,     3,     4,     5,     6,     7,
       8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,    27,
      28,    29,    30,    31,    32,    -1,    34,    35,    -1,    -1,
      38,     0,    40,    41,     3,     4,     5,     6,     7,     8,
      -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    21,    -1,    23,    24,    -1,    26,    27,    28,
      29,    30,    31,    32,    -1,    34,    35,    -1,    -1,    38,
       0,    40,    41,     3,     4,     5,     6,     7,     8,    -1,
      -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    21,    -1,    23,    24,    -1,    26,    27,    28,    29,
      30,    31,    32,    -1,    34,    35,    -1,    -1,    38,     0,
      40,    41,     3,     4,     5,     6,     7,     8,    -1,    -1,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      21,    -1,    23,    24,    -1,    26,    27,    28,    29,    30,
      31,    32,    -1,    34,    35,    -1,    -1,    38,     0,    40,
      41,     3,     4,     5,     6,     7,     8,    -1,    -1,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,
      -1,    23,    24,    -1,    26,    27,    28,    29,    30,    31,
      32,    -1,    34,    35,    -1,    -1,    38,     0,    40,    41,
       3,     4,     5,     6,     7,     8,    -1,    -1,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,
      23,    24,    -1,    26,    27,    28,    29,    30,    31,    32,
      -1,    34,    35,    -1,    -1,    38,     0,    40,    41,     3,
       4,     5,     6,     7,     8,    -1,    -1,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,
      24,    -1,    26,    27,    28,    29,    30,    31,    32,    -1,
      34,    35,    -1,    -1,    38,     0,    40,    41,     3,     4,
       5,     6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,
      -1,    26,    27,    28,    29,    30,    31,    32,    -1,    34,
      35,    -1,    -1,    38,    -1,    40,    41,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      -1,    -1,    38,    -1,    40,    41,    42,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      -1,    -1,    38,    -1,    40,    41,     3,     4,     5,     6,
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
      -1,    21,    -1,    23,    24,    -1,    26,    27,    28,    29,
      30,    31,    32,    -1,    34,    35,    -1,    -1,    38,    -1,
      40,    41,     3,     4,     5,     6,     7,     8,    -1,    -1,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      21,    -1,    23,    24,    -1,    26,    27,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    35,    -1,    -1,    38,     1,    40,
       3,     4,     5,     6,     7,    -1,    -1,    -1,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,
      23,    24,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    -1,     1,    38,     3,     4,     5,     6,
       7,    -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,
       1,    38,     3,     4,     5,     6,     7,    -1,    -1,    -1,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      21,    -1,    23,    24,    -1,    26,    27,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    35,    -1,     1,    38,     3,     4,
       5,     6,     7,    -1,    -1,    -1,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,
      -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,
      35,    -1,     1,    38,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    21,    -1,    23,    24,    -1,    26,    27,    28,
      -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,     1,    38,
       3,     4,     5,     6,     7,    -1,    -1,    -1,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,
      23,    24,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    -1,     1,    38,     3,     4,     5,     6,
       7,    -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,
       1,    38,     3,     4,     5,     6,     7,    -1,    -1,    -1,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      21,    -1,    23,    24,    -1,    26,    27,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    35,    -1,     1,    38,     3,     4,
       5,     6,     7,    -1,    -1,    -1,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,
      -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,
      35,    -1,     1,    38,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    21,    -1,    23,    24,    -1,    26,    27,    28,
      -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,     1,    38,
       3,     4,     5,     6,     7,    -1,    -1,    -1,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,
      23,    24,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    -1,     1,    38,     3,     4,     5,     6,
       7,    -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,
       1,    38,     3,     4,     5,     6,     7,    -1,    -1,    -1,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      21,    -1,    23,    24,    -1,    26,    27,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    35,    -1,     1,    38,     3,     4,
       5,     6,     7,    -1,    -1,    -1,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,
      -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,
      35,    -1,     1,    38,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    21,    -1,    23,    24,    -1,    26,    27,    28,
      -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,     1,    38,
       3,     4,     5,     6,     7,    -1,    -1,    -1,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,
      23,    24,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    -1,     1,    38,     3,     4,     5,     6,
       7,    -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,
       1,    38,     3,     4,     5,     6,     7,    -1,    -1,    -1,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      21,    -1,    23,    24,    -1,    26,    27,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    35,    -1,     1,    38,     3,     4,
       5,     6,     7,    -1,    -1,    -1,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,
      -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,
      35,    -1,     1,    38,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    21,    -1,    23,    24,    -1,    26,    27,    28,
      -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,     1,    38,
       3,     4,     5,     6,     7,    -1,    -1,    -1,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,
      23,    24,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    -1,     1,    38,     3,     4,     5,     6,
       7,    -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,
       1,    38,     3,     4,     5,     6,     7,    -1,    -1,    -1,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      21,    -1,    23,    24,    -1,    26,    27,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    35,    -1,     1,    38,     3,     4,
       5,     6,     7,    -1,    -1,    -1,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,
      -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,
      35,    -1,     1,    38,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    21,    -1,    23,    24,    -1,    26,    27,    28,
      -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,     1,    38,
       3,     4,     5,     6,     7,    -1,    -1,    -1,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,
      23,    24,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    -1,     1,    38,     3,     4,     5,     6,
       7,    -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,
       1,    38,     3,     4,     5,     6,     7,    -1,    -1,    -1,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      21,    -1,    23,    24,    -1,    26,    27,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    35,    -1,     1,    38,     3,     4,
       5,     6,     7,    -1,    -1,    -1,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,
      -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,
      35,    -1,     1,    38,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    21,    -1,    23,    24,    -1,    26,    27,    28,
      -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,     1,    38,
       3,     4,     5,     6,     7,    -1,    -1,    -1,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,
      23,    24,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    -1,     1,    38,     3,     4,     5,     6,
       7,    -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,
       1,    38,     3,     4,     5,     6,     7,    -1,    -1,    -1,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      21,    -1,    23,    24,    -1,    26,    27,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    35,    -1,     1,    38,     3,     4,
       5,     6,     7,    -1,    -1,    -1,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,
      -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,
      35,    -1,     1,    38,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    21,    -1,    23,    24,    -1,    26,    27,    28,
      -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,     1,    38,
       3,     4,     5,     6,     7,    -1,    -1,    -1,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,
      23,    24,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    -1,     1,    38,     3,     4,     5,     6,
       7,    -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,
       1,    38,     3,     4,     5,     6,     7,    -1,    -1,    -1,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      21,    -1,    23,    24,    -1,    26,    27,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    35,    -1,     1,    38,     3,     4,
       5,     6,     7,    -1,    -1,    -1,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,
      -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,
      35,    -1,     1,    38,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    21,    -1,    23,    24,    -1,    26,    27,    28,
      -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,     1,    38,
       3,     4,     5,     6,     7,    -1,    -1,    -1,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,
      23,    24,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    -1,     1,    38,     3,     4,     5,     6,
       7,    -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,
       1,    38,     3,     4,     5,     6,     7,    -1,    -1,    -1,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      21,    -1,    23,    24,    -1,    26,    27,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    35,    -1,     1,    38,     3,     4,
       5,     6,     7,    -1,    -1,    -1,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,
      -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,
      35,    -1,     1,    38,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    21,    -1,    23,    24,    -1,    26,    27,    28,
      -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,     1,    38,
       3,     4,     5,     6,     7,    -1,    -1,    -1,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,
      23,    24,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    -1,     1,    38,     3,     4,     5,     6,
       7,    -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,
       1,    38,     3,     4,     5,     6,     7,    -1,    -1,    -1,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      21,    -1,    23,    24,    -1,    26,    27,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    35,    -1,     1,    38,     3,     4,
       5,     6,     7,    -1,    -1,    -1,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,
      -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,
      35,    -1,     1,    38,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    21,    -1,    23,    24,    -1,    26,    27,    28,
      -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,     1,    38,
       3,     4,     5,     6,     7,    -1,    -1,    -1,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,
      23,    24,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    -1,     1,    38,     3,     4,     5,     6,
       7,    -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,
       1,    38,     3,     4,     5,     6,     7,    -1,    -1,    -1,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      21,    -1,    23,    24,    -1,    26,    27,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    35,    -1,     1,    38,     3,     4,
       5,     6,     7,    -1,    -1,    -1,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,
      -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,
      35,    -1,     1,    38,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    21,    -1,    23,    24,    -1,    26,    27,    28,
      -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,     1,    38,
       3,     4,     5,     6,     7,    -1,    -1,    -1,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,
      23,    24,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    -1,     1,    38,     3,     4,     5,     6,
       7,    -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,
       1,    38,     3,     4,     5,     6,     7,    -1,    -1,    -1,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      21,    -1,    23,    24,    -1,    26,    27,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    35,    -1,     1,    38,     3,     4,
       5,     6,     7,    -1,    -1,    -1,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,
      -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,
      35,    -1,     1,    38,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    21,    -1,    23,    24,    -1,    26,    27,    28,
      -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,     1,    38,
       3,     4,     5,     6,     7,    -1,    -1,    -1,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,
      23,    24,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    -1,     1,    38,     3,     4,     5,     6,
       7,    -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,
       1,    38,     3,     4,     5,     6,     7,    -1,    -1,    -1,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      21,    -1,    23,    24,    -1,    26,    27,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    35,    -1,     1,    38,     3,     4,
       5,     6,     7,    -1,    -1,    -1,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,
      -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,
      35,    -1,     1,    38,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    21,    -1,    23,    24,    -1,    26,    27,    28,
      -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,     1,    38,
       3,     4,     5,     6,     7,    -1,    -1,    -1,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,
      23,    24,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    -1,     1,    38,     3,     4,     5,     6,
       7,    -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,
       1,    38,     3,     4,     5,     6,     7,    -1,    -1,    -1,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      21,    -1,    23,    24,    -1,    26,    27,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    35,    -1,     1,    38,     3,     4,
       5,     6,     7,    -1,    -1,    -1,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,
      -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,
      35,    -1,     1,    38,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    21,    -1,    23,    24,    -1,    26,    27,    28,
      -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,     1,    38,
       3,     4,     5,     6,     7,    -1,    -1,    -1,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,
      23,    24,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    -1,     1,    38,     3,     4,     5,     6,
       7,    -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,
       1,    38,     3,     4,     5,     6,     7,    -1,    -1,    -1,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      21,    -1,    23,    24,    -1,    26,    27,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    35,    -1,     1,    38,     3,     4,
       5,     6,     7,    -1,    -1,    -1,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,
      -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,
      35,    -1,     1,    38,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    21,    -1,    23,    24,    -1,    26,    27,    28,
      -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,     1,    38,
       3,     4,     5,     6,     7,    -1,    -1,    -1,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,
      23,    24,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    -1,     1,    38,     3,     4,     5,     6,
       7,    -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,
       1,    38,     3,     4,     5,     6,     7,    -1,    -1,    -1,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      21,    -1,    23,    24,    -1,    26,    27,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    35,    -1,     1,    38,     3,     4,
       5,     6,     7,    -1,    -1,    -1,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,
      -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,
      35,    -1,     1,    38,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    21,    -1,    23,    24,    -1,    26,    27,    28,
       3,     4,     5,     6,     7,    -1,    35,    -1,    11,    38,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,
      23,    24,    -1,    26,    27,    28,     3,     4,     5,     6,
       7,    -1,    35,    -1,    11,    38,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    24,    -1,    26,
      27,    28,     3,     4,     5,     6,     7,    -1,    35,    -1,
      11,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      21,    -1,    23,    24,    -1,    26,    27,    28,     3,     4,
       5,     6,     7,    -1,    35,    -1,    11,    38,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    24,
      -1,    26,    27,    28,     3,     4,     5,     6,     7,    -1,
      35,    -1,    11,    38,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    21,    -1,    23,    24,    -1,    26,    27,    28,
      -1,    -1,    -1,    -1,    -1,    -1,    35,     9,    10,    38,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,    -1,    38,    -1,    40,     9,
      -1,    43,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,
      40,     9,    -1,    43,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,
      -1,    -1,    40,     9,    -1,    43,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    -1,    -1,    -1,    40,     9,    -1,    43,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36,    -1,    -1,    -1,    40,     9,    -1,    43,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,    40,     9,
      -1,    43,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,
      40,     9,    -1,    43,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,
      -1,    -1,    40,     9,    -1,    43,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    -1,    -1,    -1,    40,     9,    -1,    43,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36,    -1,    -1,    -1,    40,     9,    -1,    43,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,    40,     9,
      -1,    43,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,
      40,     9,    -1,    43,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,
      -1,    -1,    40,     9,    -1,    43,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    -1,    -1,    -1,    40,     9,    -1,    43,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36,    -1,    -1,    -1,    40,     9,    -1,    43,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,    40,     9,
      -1,    43,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,
      40,     9,    -1,    43,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,
      -1,    -1,    40,     9,    -1,    43,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    -1,    -1,    -1,    40,     9,    -1,    43,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36,    -1,    -1,    -1,    40,     9,    -1,    43,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,    40,     9,
      -1,    43,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,
      40,     9,    -1,    43,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,
      -1,    -1,    40,     9,    -1,    43,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    -1,    -1,    -1,    40,     9,    -1,    43,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36,    -1,    -1,    -1,    40,     9,    -1,    43,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,    40,     9,
      -1,    43,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,
      40,     9,    -1,    43,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,
      -1,    -1,    40,     9,    -1,    43,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    -1,    -1,    -1,    40,     9,    -1,    43,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36,    -1,    -1,    -1,    40,     9,    -1,    43,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,    40,     9,
      -1,    43,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,
      40,     9,    -1,    43,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,
      -1,    -1,    40,     9,    -1,    43,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    -1,    -1,    -1,    40,     9,    -1,    43,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36,    -1,    -1,    -1,    40,     9,    -1,    43,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,    40,     9,
      -1,    43,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,
      40,     9,    -1,    43,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,
      -1,    -1,    40,     9,    -1,    43,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    -1,    -1,    -1,    40,     9,    -1,    43,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36,    -1,    -1,    -1,    40,     9,    -1,    43,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,    40,     9,
      -1,    43,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,
      40,     9,    -1,    43,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,
      -1,    -1,    40,     9,    -1,    43,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    -1,    -1,    -1,    40,     9,    -1,    43,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36,    -1,    -1,    -1,    40,     9,    -1,    43,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,    40,     9,
      -1,    43,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,
      40,     9,    -1,    43,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,
      -1,    -1,    40,     9,    -1,    43,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    -1,    -1,    -1,    40,     9,    10,    43,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36,    -1,    38,     9,    40,    -1,    12,    13,
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
      10,    40,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,     9,    38,    39,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,     9,    -1,    39,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36,     9,    -1,    39,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,     9,    -1,    39,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,     9,
      -1,    39,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,     9,    -1,    39,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,     9,    -1,    39,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36,     9,    -1,    39,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,     9,    -1,    39,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,     9,
      -1,    39,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,     9,    -1,    39,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,     9,    -1,    39,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36,     9,    -1,    39,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,     9,    -1,    39,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,     9,
      -1,    39,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,     9,    -1,    39,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,     9,    -1,    39,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36,     9,    -1,    39,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,     9,    -1,    39,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,     9,
      -1,    39,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,     9,    -1,    39,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,     9,    -1,    39,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36,     9,    -1,    39,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,     9,    -1,    39,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,     9,
      -1,    39,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,     9,    -1,    39,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,     9,    -1,    39,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36,     9,    -1,    39,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,     9,    -1,    39,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,     9,
      -1,    39,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,     9,    -1,    39,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,     9,    -1,    39,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36,     9,    -1,    39,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,     9,    -1,    39,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,     9,
      -1,    39,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,     9,    -1,    39,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,     9,    -1,    39,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36,     9,    -1,    39,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,     9,    -1,    39,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,     9,
      -1,    39,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,     9,    -1,    39,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,     9,    -1,    39,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36,     9,    -1,    39,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,     9,    -1,    39,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,     9,
      -1,    39,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,     9,    -1,    39,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,     9,    -1,    39,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36,     9,    -1,    39,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,     9,    -1,    39,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,     9,
      -1,    39,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,     9,    -1,    39,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,     9,    -1,    39,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36,     9,    -1,    39,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,     9,    -1,    39,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,     9,
      -1,    39,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,     9,    -1,    39,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,     9,    -1,    39,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36,     9,    -1,    39,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,     9,    -1,    39,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,     9,
      -1,    39,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,     9,    -1,    39,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,     9,    -1,    39,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36,     9,    -1,    39,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,     9,    -1,    39,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,     9,
      10,    39,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    37,    38,     9,
      -1,    -1,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     9,    36,    37,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     9,    36,    37,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,    36,    37,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     9,    36,    37,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,
      36,    37,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     9,    36,    37,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     9,    36,    37,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,    36,    37,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     9,    36,    37,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,
      36,    37,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     9,    36,    37,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     9,    36,    37,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,    36,    37,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     9,    36,    37,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,
      36,    37,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     9,    36,    37,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     9,    36,    37,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,    36,    37,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     9,    36,    37,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,
      36,    37,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     9,    36,    37,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     9,    36,    37,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,    36,    37,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     9,    36,    37,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,
      36,    37,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     9,    36,    37,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     9,    36,    37,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,    36,    37,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     9,    36,    37,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,
      36,    37,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     9,    36,    37,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     9,    36,    37,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,    36,    37,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     9,    36,    37,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,
      36,    37,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     9,    36,    37,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     9,    36,    37,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,    36,    37,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     9,    36,    37,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,
      36,    37,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     9,    36,    37,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     9,    36,    37,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,    36,    37,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     9,    36,    37,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,
      36,    37,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     9,    36,    37,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     9,    36,    37,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,    36,    37,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     9,    36,    37,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,
      36,    37,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    37
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,    11,    21,    23,
      24,    26,    27,    28,    29,    30,    31,    32,    34,    35,
      38,    40,    46,    47,    51,    54,    82,    10,    20,    83,
       7,    43,    59,    79,    82,    82,    82,    82,    82,    82,
      82,    38,    38,    38,    52,     1,    82,    82,     0,    48,
      41,     9,    12,    13,    14,    15,    16,    17,    18,    19,
      21,    22,    23,    24,    25,    36,    40,     1,    82,    38,
      84,    38,    55,     1,     7,    38,    57,     1,    82,     1,
      82,     1,    82,    38,    40,    40,    39,    49,    51,    47,
      82,     1,    82,     1,    82,     1,    82,     1,    82,     1,
      82,     1,    82,     1,    82,     1,     1,    82,     1,    82,
       1,    82,     1,    82,     1,    82,    82,    82,    85,    56,
      79,    81,    80,     7,     8,    66,    40,    39,    39,    39,
      39,    39,    39,     8,    40,    71,    78,    82,    50,    42,
      37,    43,    86,     1,    39,     1,    62,    66,    40,    79,
      79,    68,     7,    69,    39,    58,    51,    51,    51,    51,
      51,    51,     7,    82,    39,    78,    76,    49,    82,    82,
      41,    39,     8,    43,    70,    67,    70,    60,     1,    33,
      33,    44,    74,    53,    78,    86,    64,     1,    41,     7,
       8,     1,    70,     1,    41,    51,    51,    82,    79,    51,
      78,    47,    40,    63,    70,     7,    47,    72,    75,    42,
      65,    47,    70,    42,    43,    77,    78,    47,    42,    61,
       7,    73,    78,    42,     1,    44,    78,    82,    78,    77,
       3,     4,     5,     6,     7,    11,    21,    23,    24,    26,
      27,    28,    35,    38,     9,    12,    13,    14,    15,    16,
      17,    18,    19,    21,    22,    23,    24,    25,    36,     8,
      29,    30,    31,    32,    34,    40,    51,    54,    82,     3,
       4,     5,     6,     7,    11,    21,    23,    24,    26,    27,
      28,    35,    38,     3,     4,     5,     6,     7,    11,    21,
      23,    24,    26,    27,    28,    35,    38,     9,    12,    13,
      14,    15,    16,    17,    18,    19,    21,    22,    23,    24,
      25,    36,     9,    12,    13,    14,    15,    16,    17,    18,
      19,    21,    22,    23,    24,    25,    36,     8,    29,    30,
      31,    32,    34,    40,    54,    82,    40,     8,    43,     3,
       4,     5,     6,     7,    11,    21,    23,    24,    26,    27,
      28,    35,    38,     9,    12,    13,    14,    15,    16,    17,
      18,    19,    21,    22,    23,    24,    25,    36,    10,    20,
      83,    82,    82,    82,    82,    82,    82,    82,    82,    82,
       1,    82,     1,    82,     1,    82,     1,    82,     1,    82,
       1,    82,     1,    82,     1,     1,    82,     1,    82,     1,
      82,     1,    82,     1,    82,    82,     7,    59,    79,    38,
      38,    38,    52,     1,    82,    48,    41,    40,    10,    20,
      83,    82,    82,    82,    82,    82,    82,    82,    82,    10,
      20,    83,    82,    82,    82,    82,    82,    82,    82,    82,
      82,     1,    82,     1,    82,     1,    82,     1,    82,     1,
      82,     1,    82,     1,    82,     1,     1,    82,     1,    82,
       1,    82,     1,    82,     1,    82,    82,    82,     1,    82,
       1,    82,     1,    82,     1,    82,     1,    82,     1,    82,
       1,    82,     1,     1,    82,     1,    82,     1,    82,     1,
      82,     1,    82,    82,     7,    59,    79,    38,    38,    38,
      52,     1,    82,    41,    40,    82,     7,     8,    10,    20,
      83,    82,    82,    82,    82,    82,    82,    82,    82,    82,
       1,    82,     1,    82,     1,    82,     1,    82,     1,    82,
       1,    82,     1,    82,     1,     1,    82,     1,    82,     1,
      82,     1,    82,     1,    82,    82,     1,    82,    38,    84,
      39,    37,    38,    55,    38,    57,     1,    82,     1,    82,
       1,    82,    38,    40,    40,    49,    51,    47,     1,    82,
      38,    84,    39,     1,    82,    38,    84,    39,    37,    37,
      38,    55,    38,    57,     1,    82,     1,    82,     1,    82,
      38,    40,    40,    47,    70,     7,     1,    82,    38,    84,
      39,    37,    85,    82,    56,    79,    66,    40,    39,    39,
      39,    39,    39,    39,    71,    50,    42,    85,    85,    82,
      82,    56,    79,    66,    40,    39,    39,    39,    39,    39,
      39,    71,    42,    70,    85,    82,     1,    39,     1,    62,
      66,    40,    39,    58,     8,    29,    30,    31,    32,    34,
      40,    51,    54,    82,    51,    51,    51,    51,    51,    39,
      49,     1,    39,     1,    39,     1,    62,    66,    40,    39,
      58,    51,    51,    51,    51,    51,    51,    39,     1,    39,
      41,    39,    60,     1,     7,    59,    79,    38,    38,    38,
      52,     1,    82,    33,    41,    40,    33,    53,    41,    39,
      60,     1,    33,    33,    53,    64,     1,    41,    41,    38,
      55,    38,    57,     1,    82,     1,    82,     1,    82,    38,
      40,    40,    51,    47,    51,    51,    64,     1,    41,    41,
      51,    51,    51,    47,    40,    63,    47,    56,    79,    66,
      40,    39,    39,    39,    39,    39,    39,    71,    42,    47,
      40,    63,    47,    42,    65,    47,    42,     1,    62,    66,
      40,    39,    58,    51,    51,    51,    51,    51,    51,    39,
      42,    65,    47,    42,    47,    42,    61,    41,    39,    60,
       1,    33,    33,    53,    47,    42,    61,    42,     1,    64,
       1,    41,    41,    51,    51,    51,    42,     1,    47,    40,
      63,    47,    42,    65,    47,    42,    47,    42,    61,    42,
       1
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    45,    46,    47,    48,    47,    49,    50,    49,    51,
      51,    51,    51,    52,    53,    51,    51,    51,    54,    51,
      51,    55,    51,    56,    51,    51,    51,    51,    51,    51,
      57,    58,    51,    59,    60,    61,    51,    63,    62,    64,
      62,    65,    62,    66,    67,    66,    68,    66,    69,    66,
      70,    70,    70,    72,    73,    71,    74,    75,    71,    76,
      71,    71,    77,    77,    78,    78,    79,    80,    79,    81,
      79,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      83,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    84,    84,    85,
      85,    86,    86
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     0,     3,     0,     0,     3,     5,
       7,     5,     5,     0,     0,     7,     2,     3,     0,     4,
       1,     0,     5,     0,     5,     5,     7,     5,     5,     3,
       0,     0,     6,     0,     0,     0,    11,     0,     6,     0,
       5,     0,     7,     0,     0,     4,     0,     4,     0,     4,
       0,     4,     3,     0,     0,     9,     0,     0,     7,     0,
       4,     2,     0,     5,     2,     1,     0,     0,     4,     0,
       4,     1,     1,     1,     1,     1,     1,     2,     2,     2,
       2,     2,     2,     2,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     5,     3,
       0,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     0,
       2,     0,     3
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
#line 4477 "sintatico.tab.c"
        break;

    case YYSYMBOL_CHAR: /* CHAR  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4486 "sintatico.tab.c"
        break;

    case YYSYMBOL_INT: /* INT  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4495 "sintatico.tab.c"
        break;

    case YYSYMBOL_FLOAT: /* FLOAT  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4504 "sintatico.tab.c"
        break;

    case YYSYMBOL_ID: /* ID  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4513 "sintatico.tab.c"
        break;

    case YYSYMBOL_TYPE: /* TYPE  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4522 "sintatico.tab.c"
        break;

    case YYSYMBOL_IN: /* IN  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4531 "sintatico.tab.c"
        break;

    case YYSYMBOL_OPPOS: /* OPPOS  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4540 "sintatico.tab.c"
        break;

    case YYSYMBOL_OPUNI: /* OPUNI  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4549 "sintatico.tab.c"
        break;

    case YYSYMBOL_OPBIN1: /* OPBIN1  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4558 "sintatico.tab.c"
        break;

    case YYSYMBOL_OPBIN2: /* OPBIN2  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4567 "sintatico.tab.c"
        break;

    case YYSYMBOL_OPBIN3: /* OPBIN3  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4576 "sintatico.tab.c"
        break;

    case YYSYMBOL_OPBIN4: /* OPBIN4  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4585 "sintatico.tab.c"
        break;

    case YYSYMBOL_OPBIN5: /* OPBIN5  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4594 "sintatico.tab.c"
        break;

    case YYSYMBOL_OPBIN6: /* OPBIN6  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4603 "sintatico.tab.c"
        break;

    case YYSYMBOL_OPBIN7: /* OPBIN7  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4612 "sintatico.tab.c"
        break;

    case YYSYMBOL_OPBIN8: /* OPBIN8  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4621 "sintatico.tab.c"
        break;

    case YYSYMBOL_OPASSIGN: /* OPASSIGN  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4630 "sintatico.tab.c"
        break;

    case YYSYMBOL_21_: /* '*'  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4639 "sintatico.tab.c"
        break;

    case YYSYMBOL_22_: /* '/'  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4648 "sintatico.tab.c"
        break;

    case YYSYMBOL_23_: /* '+'  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4657 "sintatico.tab.c"
        break;

    case YYSYMBOL_24_: /* '-'  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4666 "sintatico.tab.c"
        break;

    case YYSYMBOL_25_: /* '%'  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4675 "sintatico.tab.c"
        break;

    case YYSYMBOL_26_: /* '!'  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4684 "sintatico.tab.c"
        break;

    case YYSYMBOL_27_: /* '~'  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4693 "sintatico.tab.c"
        break;

    case YYSYMBOL_28_: /* '&'  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4702 "sintatico.tab.c"
        break;

    case YYSYMBOL_cmd: /* cmd  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4711 "sintatico.tab.c"
        break;

    case YYSYMBOL_exp: /* exp  */
#line 186 "sintatico.y"
            {
	depth_pre(free_values, ((*yyvaluep).node), NULL, NULL, NULL);
	delete_node(((*yyvaluep).node));
}
#line 4720 "sintatico.tab.c"
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
#line 4990 "sintatico.tab.c"
    break;

  case 7: /* $@2: %empty  */
#line 238 "sintatico.y"
              {
		add_child((yyvsp[0].node), parents->first->value);
	}
#line 4998 "sintatico.tab.c"
    break;

  case 9: /* cmd: IF '(' exp ')' cmd  */
#line 243 "sintatico.y"
                                 {
		(yyval.node) = create_node(strdup("<if>"));
		add_child((yyvsp[-2].node), (yyval.node));
		add_child((yyvsp[0].node), (yyval.node));
	}
#line 5008 "sintatico.tab.c"
    break;

  case 10: /* cmd: IF '(' exp ')' cmd ELSE cmd  */
#line 248 "sintatico.y"
                                                 {
		(yyval.node) = create_node(strdup("<if-else>"));
		add_child((yyvsp[-4].node), (yyval.node));
		add_child((yyvsp[-2].node), (yyval.node));
		add_child((yyvsp[0].node), (yyval.node));
	}
#line 5019 "sintatico.tab.c"
    break;

  case 11: /* cmd: WHILE '(' exp ')' cmd  */
#line 254 "sintatico.y"
                                {
		(yyval.node) = create_node(strdup("<while>"));
		add_child((yyvsp[-2].node), (yyval.node));
		add_child((yyvsp[0].node), (yyval.node));
	}
#line 5029 "sintatico.tab.c"
    break;

  case 12: /* cmd: FORALL '(' exp ')' cmd  */
#line 259 "sintatico.y"
                                 {
		(yyval.node) = create_node(strdup("<forall>"));
		add_child((yyvsp[-2].node), (yyval.node));
		add_child((yyvsp[0].node), (yyval.node));
	}
#line 5039 "sintatico.tab.c"
    break;

  case 13: /* @3: %empty  */
#line 264 "sintatico.y"
              {
		(yyval.node) = create_node(strdup("<for>"));
		insert(0, (yyval.node), parents);
	}
#line 5048 "sintatico.tab.c"
    break;

  case 14: /* $@4: %empty  */
#line 267 "sintatico.y"
                          {
		removeAt(0, parents);
	}
#line 5056 "sintatico.tab.c"
    break;

  case 15: /* cmd: FOR @3 '(' forargs ')' $@4 cmd  */
#line 269 "sintatico.y"
              {
		(yyval.node) = (yyvsp[-5].node);
		add_child((yyvsp[0].node), (yyval.node));
	}
#line 5065 "sintatico.tab.c"
    break;

  case 16: /* cmd: exp ';'  */
#line 273 "sintatico.y"
                  { (yyval.node) = (yyvsp[-1].node); }
#line 5071 "sintatico.tab.c"
    break;

  case 17: /* cmd: RETURN exp ';'  */
#line 274 "sintatico.y"
                         {
		add_child((yyvsp[-1].node), ((yyval.node) = create_node(strdup("<return>"))));
	}
#line 5079 "sintatico.tab.c"
    break;

  case 18: /* $@5: %empty  */
#line 277 "sintatico.y"
          {
		insert(0, create_node(strdup("<block>")), parents);
		PUSH_CONTEXT;
	}
#line 5088 "sintatico.tab.c"
    break;

  case 19: /* cmd: $@5 '{' cmds '}'  */
#line 280 "sintatico.y"
                       {
		POP_CONTEXT;
		(yyval.node) = parents->first->value;
		removeAt(0, parents);
	}
#line 5098 "sintatico.tab.c"
    break;

  case 20: /* cmd: ';'  */
#line 285 "sintatico.y"
              {
		(yyval.node) = create_node(strdup("<emptycmd>"));
	}
#line 5106 "sintatico.tab.c"
    break;

  case 21: /* @6: %empty  */
#line 288 "sintatico.y"
                  {
		(yyval.node) = create_node(strdup("<declr>"));
		add_child((yyvsp[-1].node), (yyval.node));
		add_child((yyvsp[0].node), (yyval.node));
		ADD_CONTEXT(VAR, FIRSTCHILD_VALUE((yyvsp[0].node)), FIRSTCHILD_VALUE((yyvsp[-1].node)));
		insert(0, (yyval.node), parents);
	}
#line 5118 "sintatico.tab.c"
    break;

  case 22: /* cmd: TYPE ID @6 idlist ';'  */
#line 294 "sintatico.y"
                     {
		(yyval.node) = (yyvsp[-2].node);
		removeAt(0, parents);
	}
#line 5127 "sintatico.tab.c"
    break;

  case 23: /* @7: %empty  */
#line 298 "sintatico.y"
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
#line 5143 "sintatico.tab.c"
    break;

  case 24: /* cmd: TYPE ID '(' @7 declr_fntail  */
#line 308 "sintatico.y"
                       {
		POP_CONTEXT;
		(yyval.node) = (yyvsp[-1].node);
	}
#line 5152 "sintatico.tab.c"
    break;

  case 25: /* cmd: IF '(' error ')' cmd  */
#line 313 "sintatico.y"
                                        {
		(yyval.node) = create_node(strdup("<if>"));
		add_child(create_node(ERR_TOKEN), (yyval.node));
		add_child((yyvsp[0].node), (yyval.node));
		ssprintf(syn_errormsg, "Expected condition in '%s' statment", (yyvsp[-4].name));
	}
#line 5163 "sintatico.tab.c"
    break;

  case 26: /* cmd: IF '(' error ')' cmd ELSE cmd  */
#line 319 "sintatico.y"
                                                   {
		(yyval.node) = create_node(strdup("<if-else>"));
		add_child(create_node(ERR_TOKEN), (yyval.node));
		add_child((yyvsp[-2].node), (yyval.node));
		add_child((yyvsp[0].node), (yyval.node));
		ssprintf(syn_errormsg, "Expected condition in '%s' statment", (yyvsp[-6].name));
	}
#line 5175 "sintatico.tab.c"
    break;

  case 27: /* cmd: WHILE '(' error ')' cmd  */
#line 326 "sintatico.y"
                                  {
		(yyval.node) = create_node(strdup("<while>"));
		add_child(create_node(ERR_TOKEN), (yyval.node));
		add_child((yyvsp[0].node), (yyval.node));
		ssprintf(syn_errormsg, "Expected condition in '%s' statment", (yyvsp[-4].name));
	}
#line 5186 "sintatico.tab.c"
    break;

  case 28: /* cmd: FORALL '(' error ')' cmd  */
#line 332 "sintatico.y"
                                   {
		(yyval.node) = create_node(strdup("<forall>"));
		add_child(create_node(ERR_TOKEN), (yyval.node));
		add_child((yyvsp[0].node), (yyval.node));
		ssprintf(syn_errormsg, "Expected in-expression in '%s' statment", (yyvsp[-4].name));
	}
#line 5197 "sintatico.tab.c"
    break;

  case 29: /* cmd: RETURN error ';'  */
#line 338 "sintatico.y"
                           {
		(yyval.node) = create_node(strdup("<return>"));
		add_child(create_node(ERR_TOKEN), (yyval.node));
		ssprintf(syn_errormsg, "Expected return expression");
	}
#line 5207 "sintatico.tab.c"
    break;

  case 30: /* @8: %empty  */
#line 343 "sintatico.y"
                      {
		(yyval.node) = create_node(strdup("<declr>"));
		add_child((yyvsp[-1].node), (yyval.node));
		add_child(create_node(ERR_TOKEN), (yyval.node));
		insert(0, (yyval.node), parents);
	}
#line 5218 "sintatico.tab.c"
    break;

  case 31: /* $@9: %empty  */
#line 348 "sintatico.y"
              {
		removeAt(0, parents);
		YYERROR;
	}
#line 5227 "sintatico.tab.c"
    break;

  case 32: /* cmd: TYPE idlist @8 ';' $@9 error  */
#line 351 "sintatico.y"
                {
		(yyval.node) = (yyvsp[-3].node);
		ssprintf(
			syn_errormsg,
			"Expected identifier of type '%s'",
			FIRSTCHILD_VALUE((yyvsp[-5].node))
		);
	}
#line 5240 "sintatico.tab.c"
    break;

  case 33: /* @10: %empty  */
#line 359 "sintatico.y"
               {
		(yyval.node) = create_node(strdup("<declr_fn>"));
		add_child((yyvsp[0].node), (yyval.node));
		add_child(create_node(ERR_TOKEN), (yyval.node));

		node_t pars = create_node(strdup("<parlist>"));
		add_child(pars, (yyval.node));
		insert(0, pars, parents);
		PUSH_CONTEXT;
	}
#line 5255 "sintatico.tab.c"
    break;

  case 34: /* @11: %empty  */
#line 368 "sintatico.y"
                          {
		removeAt(0, parents);
		(yyval.node) = (yyvsp[-3].node);
		node_t block = create_node(strdup("<block>"));
		add_child(block, (yyval.node));
		insert(0, block, parents);
	}
#line 5267 "sintatico.tab.c"
    break;

  case 35: /* $@12: %empty  */
#line 374 "sintatico.y"
                       {
		POP_CONTEXT;
		removeAt(0, parents);
		YYERROR;
	}
#line 5277 "sintatico.tab.c"
    break;

  case 36: /* cmd: TYPE @10 '(' parlist ')' @11 '{' cmds '}' $@12 error  */
#line 378 "sintatico.y"
                {
		(yyval.node) = (yyvsp[-5].node);
		ssprintf(syn_errormsg, "Expected identifier of type '%s' in function declaration", (yyvsp[-10].node)->value);
	}
#line 5286 "sintatico.tab.c"
    break;

  case 37: /* $@13: %empty  */
#line 384 "sintatico.y"
                              {
		node_t block = create_node(strdup("<block>"));
		add_child(block, ((node_t) parents->first->value)->parent);
		removeAt(0, parents); /* Inserido no que vem antes */
		insert(0, block, parents);
	}
#line 5297 "sintatico.tab.c"
    break;

  case 38: /* declr_fntail: parlist ')' '{' $@13 cmds '}'  */
#line 389 "sintatico.y"
                   {
		removeAt(0, parents);
	}
#line 5305 "sintatico.tab.c"
    break;

  case 39: /* $@14: %empty  */
#line 393 "sintatico.y"
                    {
		node_t block = create_node(strdup("<block>"));
		add_child(block, ((node_t) parents->first->value)->parent);

		add_child(create_node(ERR_TOKEN), parents->first->value);

		removeAt(0, parents); /* Inserido no que vem antes */
		insert(0, block, parents);
		ssprintf(syn_errormsg, "Expected a ')'");
	}
#line 5320 "sintatico.tab.c"
    break;

  case 40: /* declr_fntail: error '{' $@14 cmds '}'  */
#line 402 "sintatico.y"
                   {
		removeAt(0, parents);
	}
#line 5328 "sintatico.tab.c"
    break;

  case 41: /* $@15: %empty  */
#line 405 "sintatico.y"
                                {
		node_t err = create_node(ERR_TOKEN);
		node_t block = create_node(strdup("<block>"));
		add_child(err, block);
		add_child(block, ((node_t) parents->first->value)->parent);

		removeAt(0, parents); /* Inserido no que vem antes */
		insert(0, err, parents);
		ssprintf(syn_errormsg, "Expected a '{'");
	}
#line 5343 "sintatico.tab.c"
    break;

  case 42: /* declr_fntail: parlist ')' error ';' $@15 cmds '}'  */
#line 414 "sintatico.y"
                   {
		removeAt(0, parents);
	}
#line 5351 "sintatico.tab.c"
    break;

  case 44: /* @16: %empty  */
#line 420 "sintatico.y"
                  {
		(yyval.node) = create_node(strdup("<declr>"));
		add_child((yyvsp[-1].node), (yyval.node));
		add_child((yyvsp[0].node), (yyval.node));
		ADD_CONTEXT(VAR, FIRSTCHILD_VALUE((yyvsp[0].node)), FIRSTCHILD_VALUE((yyvsp[-1].node)));
		add_child((yyval.node), parents->first->value);
	}
#line 5363 "sintatico.tab.c"
    break;

  case 46: /* $@17: %empty  */
#line 428 "sintatico.y"
             { /* Missing type */
		add_child(create_node(ERR_TOKEN), parents->first->value);
		add_child((yyvsp[0].node), parents->first->value);
		YYERROR;
	}
#line 5373 "sintatico.tab.c"
    break;

  case 47: /* parlist: ID $@17 partail error  */
#line 432 "sintatico.y"
                        {
		ssprintf(syn_errormsg, "Expected a type for '%s'", FIRSTCHILD_VALUE((yyvsp[-3].node)));
	}
#line 5381 "sintatico.tab.c"
    break;

  case 48: /* $@18: %empty  */
#line 435 "sintatico.y"
               { /* Missing id */
		add_child((yyvsp[0].node), parents->first->value);
		add_child(create_node(ERR_TOKEN), parents->first->value);
		YYERROR;
	}
#line 5391 "sintatico.tab.c"
    break;

  case 49: /* parlist: TYPE $@18 partail error  */
#line 439 "sintatico.y"
                        {
		ssprintf(syn_errormsg, "Expected an identifier of type '%s'", FIRSTCHILD_VALUE((yyvsp[-3].node)));
	}
#line 5399 "sintatico.tab.c"
    break;

  case 51: /* partail: ',' TYPE ID partail  */
#line 445 "sintatico.y"
                              {
		(yyval.node) = create_node(strdup("<declr>"));
		add_child((yyvsp[-2].node), (yyval.node));
		add_child((yyvsp[-1].node), (yyval.node));
		ADD_CONTEXT(VAR, FIRSTCHILD_VALUE((yyvsp[-1].node)), FIRSTCHILD_VALUE((yyvsp[-2].node)));
		add_child((yyval.node), parents->first->value);
	}
#line 5411 "sintatico.tab.c"
    break;

  case 52: /* partail: TYPE ID partail  */
#line 453 "sintatico.y"
                          {
		(yyval.node) = create_node(strdup("<declr>"));
		add_child((yyvsp[-2].node), (yyval.node));
		add_child((yyvsp[-1].node), (yyval.node));
		ADD_CONTEXT(VAR, FIRSTCHILD_VALUE((yyvsp[-1].node)), FIRSTCHILD_VALUE((yyvsp[-2].node)));
		add_child((yyval.node), parents->first->value);
		ssprintf(syn_errormsg, "Expected a ','");
	}
#line 5424 "sintatico.tab.c"
    break;

  case 53: /* $@19: %empty  */
#line 463 "sintatico.y"
                         {
		node_t arg = create_node(strdup("<declr_init>"));
		add_child((yyvsp[-3].node), arg);
		add_child((yyvsp[-2].node), arg);
		add_child((yyvsp[0].node), arg);

		add_child(arg, parents->first->value);
		insert(0, arg, parents);
	}
#line 5438 "sintatico.tab.c"
    break;

  case 54: /* $@20: %empty  */
#line 471 "sintatico.y"
                       { /* TODO: Tem que poder fazer várias declarações sem iniciar */
		removeAt(0, parents);
	}
#line 5446 "sintatico.tab.c"
    break;

  case 56: /* $@21: %empty  */
#line 474 "sintatico.y"
                  {
		node_t arg = create_node(strdup("<declr>"));
		add_child((yyvsp[-1].node), arg);
		add_child((yyvsp[0].node), arg);

		add_child(arg, parents->first->value);
		insert(0, arg, parents);
	}
#line 5459 "sintatico.tab.c"
    break;

  case 57: /* $@22: %empty  */
#line 481 "sintatico.y"
                 {
		removeAt(0, parents);
	}
#line 5467 "sintatico.tab.c"
    break;

  case 59: /* $@23: %empty  */
#line 484 "sintatico.y"
              {
		add_child((yyvsp[0].node), parents->first->value);
	}
#line 5475 "sintatico.tab.c"
    break;

  case 61: /* forargs: fortail fortail  */
#line 487 "sintatico.y"
                          {
		node_t exp = create_node(strdup("<emptyexp>"));
		exp->parent = parents->first->value;
		insert(0, exp, parents->first->value);
	}
#line 5485 "sintatico.tab.c"
    break;

  case 63: /* fordeclrlist: ',' ID '=' exp fordeclrlist  */
#line 495 "sintatico.y"
                                      {
		add_child((yyvsp[-3].node), parents->first->value);
		add_child((yyvsp[-1].node), parents->first->value);
	}
#line 5494 "sintatico.tab.c"
    break;

  case 64: /* fortail: ';' exp  */
#line 501 "sintatico.y"
                 {
		add_child((yyvsp[0].node), parents->first->value);
	}
#line 5502 "sintatico.tab.c"
    break;

  case 65: /* fortail: ';'  */
#line 504 "sintatico.y"
              {
		add_child(create_node(strdup("<emptyexp>")), parents->first->value);
	}
#line 5510 "sintatico.tab.c"
    break;

  case 67: /* $@24: %empty  */
#line 510 "sintatico.y"
                 {
		add_child((yyvsp[0].node), parents->first->value);
	}
#line 5518 "sintatico.tab.c"
    break;

  case 69: /* $@25: %empty  */
#line 513 "sintatico.y"
                    {
		add_child(create_node(ERR_TOKEN), parents->first->value);
		ssprintf(syn_errormsg, "Expected an indentifier");
	}
#line 5527 "sintatico.tab.c"
    break;

  case 71: /* exp: INT  */
#line 519 "sintatico.y"
             { add_child((yyvsp[0].node), ((yyval.node) = create_node(strdup("<int>"))));    }
#line 5533 "sintatico.tab.c"
    break;

  case 72: /* exp: FLOAT  */
#line 520 "sintatico.y"
                 { add_child((yyvsp[0].node), ((yyval.node) = create_node(strdup("<float>"))));  }
#line 5539 "sintatico.tab.c"
    break;

  case 73: /* exp: EMPTY  */
#line 521 "sintatico.y"
                 { (yyval.node) = create_node(strdup("<empty>"));                   }
#line 5545 "sintatico.tab.c"
    break;

  case 74: /* exp: STRING  */
#line 522 "sintatico.y"
                 { add_child((yyvsp[0].node), ((yyval.node) = create_node(strdup("<string>")))); }
#line 5551 "sintatico.tab.c"
    break;

  case 75: /* exp: CHAR  */
#line 523 "sintatico.y"
                 { add_child((yyvsp[0].node), ((yyval.node) = create_node(strdup("<char>"))));   }
#line 5557 "sintatico.tab.c"
    break;

  case 76: /* exp: ID  */
#line 524 "sintatico.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 5563 "sintatico.tab.c"
    break;

  case 77: /* exp: ID OPPOS  */
#line 525 "sintatico.y"
                   {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<oppos>"));
		add_child((yyvsp[0].node), op);
		add_child((yyvsp[-1].node), exp);
		add_child(op, exp);
		(yyval.node) = exp;
	}
#line 5576 "sintatico.tab.c"
    break;

  case 78: /* exp: '*' exp  */
#line 533 "sintatico.y"
                              { ADD_UNI_EXP((yyval.node), (yyvsp[-1].node), (yyvsp[0].node));     }
#line 5582 "sintatico.tab.c"
    break;

  case 79: /* exp: '+' exp  */
#line 534 "sintatico.y"
                              { ADD_UNI_EXP((yyval.node), (yyvsp[-1].node), (yyvsp[0].node));     }
#line 5588 "sintatico.tab.c"
    break;

  case 80: /* exp: '-' exp  */
#line 535 "sintatico.y"
                              { ADD_UNI_EXP((yyval.node), (yyvsp[-1].node), (yyvsp[0].node));     }
#line 5594 "sintatico.tab.c"
    break;

  case 81: /* exp: '!' exp  */
#line 536 "sintatico.y"
                              { ADD_UNI_EXP((yyval.node), (yyvsp[-1].node), (yyvsp[0].node));     }
#line 5600 "sintatico.tab.c"
    break;

  case 82: /* exp: '~' exp  */
#line 537 "sintatico.y"
                              { ADD_UNI_EXP((yyval.node), (yyvsp[-1].node), (yyvsp[0].node));     }
#line 5606 "sintatico.tab.c"
    break;

  case 83: /* exp: '&' exp  */
#line 538 "sintatico.y"
                              { ADD_UNI_EXP((yyval.node), (yyvsp[-1].node), (yyvsp[0].node));     }
#line 5612 "sintatico.tab.c"
    break;

  case 84: /* exp: OPUNI exp  */
#line 539 "sintatico.y"
                              { ADD_UNI_EXP((yyval.node), (yyvsp[-1].node), (yyvsp[0].node));     }
#line 5618 "sintatico.tab.c"
    break;

  case 85: /* exp: exp '*' exp  */
#line 540 "sintatico.y"
                              { ADD_BIN_EXP((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 5624 "sintatico.tab.c"
    break;

  case 86: /* exp: exp '/' exp  */
#line 541 "sintatico.y"
                              { ADD_BIN_EXP((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 5630 "sintatico.tab.c"
    break;

  case 87: /* exp: exp '%' exp  */
#line 542 "sintatico.y"
                              { ADD_BIN_EXP((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 5636 "sintatico.tab.c"
    break;

  case 88: /* exp: exp '+' exp  */
#line 543 "sintatico.y"
                              { ADD_BIN_EXP((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 5642 "sintatico.tab.c"
    break;

  case 89: /* exp: exp '-' exp  */
#line 544 "sintatico.y"
                              { ADD_BIN_EXP((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 5648 "sintatico.tab.c"
    break;

  case 90: /* exp: exp IN exp  */
#line 545 "sintatico.y"
                              { ADD_BIN_EXP((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 5654 "sintatico.tab.c"
    break;

  case 91: /* exp: exp OPBIN1 exp  */
#line 546 "sintatico.y"
                              { ADD_BIN_EXP((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 5660 "sintatico.tab.c"
    break;

  case 92: /* exp: exp OPBIN2 exp  */
#line 547 "sintatico.y"
                              { ADD_BIN_EXP((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 5666 "sintatico.tab.c"
    break;

  case 93: /* exp: exp OPBIN3 exp  */
#line 548 "sintatico.y"
                              { ADD_BIN_EXP((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 5672 "sintatico.tab.c"
    break;

  case 94: /* exp: exp OPBIN4 exp  */
#line 549 "sintatico.y"
                              { ADD_BIN_EXP((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 5678 "sintatico.tab.c"
    break;

  case 95: /* exp: exp OPBIN5 exp  */
#line 550 "sintatico.y"
                              { ADD_BIN_EXP((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 5684 "sintatico.tab.c"
    break;

  case 96: /* exp: exp OPBIN6 exp  */
#line 551 "sintatico.y"
                              { ADD_BIN_EXP((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 5690 "sintatico.tab.c"
    break;

  case 97: /* exp: exp OPBIN7 exp  */
#line 552 "sintatico.y"
                              { ADD_BIN_EXP((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 5696 "sintatico.tab.c"
    break;

  case 98: /* exp: exp '?' exp ':' exp  */
#line 553 "sintatico.y"
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
#line 5714 "sintatico.tab.c"
    break;

  case 99: /* exp: ID OPASSIGN exp  */
#line 566 "sintatico.y"
                          {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opassign>"));
		add_child((yyvsp[-1].node), op);
		add_child((yyvsp[-2].node), exp);
		add_child(op, exp);
		add_child((yyvsp[0].node), exp);
		(yyval.node) = exp;
	}
#line 5728 "sintatico.tab.c"
    break;

  case 100: /* @26: %empty  */
#line 575 "sintatico.y"
             {
		(yyval.node) = create_node(strdup("<fn>"));
		add_child((yyvsp[0].node), (yyval.node));
		insert(0, (yyval.node), parents);
	}
#line 5738 "sintatico.tab.c"
    break;

  case 101: /* exp: ID @26 fntail  */
#line 579 "sintatico.y"
                 {
		(yyval.node) = (yyvsp[-1].node);
		removeAt(0, parents);
	}
#line 5747 "sintatico.tab.c"
    break;

  case 102: /* exp: '(' exp ')'  */
#line 583 "sintatico.y"
                      { add_child((yyvsp[-1].node), ((yyval.node) = create_node(strdup("<exp>")))); }
#line 5753 "sintatico.tab.c"
    break;

  case 103: /* exp: exp '*' error  */
#line 585 "sintatico.y"
                           { ADD_BIN_EXP_ERR((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 5759 "sintatico.tab.c"
    break;

  case 104: /* exp: exp '/' error  */
#line 586 "sintatico.y"
                           { ADD_BIN_EXP_ERR((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 5765 "sintatico.tab.c"
    break;

  case 105: /* exp: exp '%' error  */
#line 587 "sintatico.y"
                           { ADD_BIN_EXP_ERR((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 5771 "sintatico.tab.c"
    break;

  case 106: /* exp: exp '+' error  */
#line 588 "sintatico.y"
                           { ADD_BIN_EXP_ERR((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 5777 "sintatico.tab.c"
    break;

  case 107: /* exp: exp '-' error  */
#line 589 "sintatico.y"
                           { ADD_BIN_EXP_ERR((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 5783 "sintatico.tab.c"
    break;

  case 108: /* exp: exp OPBIN1 error  */
#line 590 "sintatico.y"
                           { ADD_BIN_EXP_ERR((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 5789 "sintatico.tab.c"
    break;

  case 109: /* exp: exp OPBIN2 error  */
#line 591 "sintatico.y"
                           { ADD_BIN_EXP_ERR((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 5795 "sintatico.tab.c"
    break;

  case 110: /* exp: exp OPBIN3 error  */
#line 592 "sintatico.y"
                           { ADD_BIN_EXP_ERR((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 5801 "sintatico.tab.c"
    break;

  case 111: /* exp: exp OPBIN4 error  */
#line 593 "sintatico.y"
                           { ADD_BIN_EXP_ERR((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 5807 "sintatico.tab.c"
    break;

  case 112: /* exp: exp OPBIN5 error  */
#line 594 "sintatico.y"
                           { ADD_BIN_EXP_ERR((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 5813 "sintatico.tab.c"
    break;

  case 113: /* exp: exp OPBIN6 error  */
#line 595 "sintatico.y"
                           { ADD_BIN_EXP_ERR((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 5819 "sintatico.tab.c"
    break;

  case 114: /* exp: exp OPBIN7 error  */
#line 596 "sintatico.y"
                           { ADD_BIN_EXP_ERR((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 5825 "sintatico.tab.c"
    break;

  case 115: /* exp: exp OPBIN8 error  */
#line 597 "sintatico.y"
                           { ADD_BIN_EXP_ERR((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 5831 "sintatico.tab.c"
    break;

  case 116: /* exp: ID OPASSIGN error  */
#line 598 "sintatico.y"
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
#line 5852 "sintatico.tab.c"
    break;

  case 118: /* fntail: '(' arglist error  */
#line 617 "sintatico.y"
                            { ssprintf(syn_errormsg, "Expected ')'"); }
#line 5858 "sintatico.tab.c"
    break;

  case 120: /* arglist: exp argtail  */
#line 621 "sintatico.y"
                      { add_child((yyvsp[-1].node), parents->first->value); }
#line 5864 "sintatico.tab.c"
    break;

  case 122: /* argtail: ',' exp argtail  */
#line 625 "sintatico.y"
                          { add_child((yyvsp[-1].node), parents->first->value); }
#line 5870 "sintatico.tab.c"
    break;


#line 5874 "sintatico.tab.c"

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

#line 628 "sintatico.y"


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

	/** ========= Inicializando valores ================ **/
	strncpy(filename, argv[1], FILENAMESIZE);           /**/
	root = create_node(filename);                       /**/
	context = create_node(create_list());               /**/
	current_context = context;                          /**/
	parents = create_list();                            /**/
	int max = 0, *childrenCount = NULL;                 /**/
                                                        /**/
	yyin = fopen(argv[1], "r");                         /**/
	insert(0, root, parents);                           /**/
	/** ================================================ **/

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
