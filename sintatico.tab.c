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
#line 3 "sintatico.y"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <locale.h>
#include <wchar.h>
#include "lex.yy.h"
#include <assert.h>
#include "tree.h"

#define NAMESIZE 32768
#define YYDEBUG 1

#define __TREE_WIDE_CHARS__
#ifdef __TREE_WIDE_CHARS__
#define TREECHILDFIRST "┬"
#define TREECHILDMID "├"
#define TREECHILDLAST "└"
#define TREECHILD "│"
#define TREELEAF "○"
#define TREEBRANCH "─"
#else
#define TREECHILDFIRST "."
#define TREECHILDMID "+"
#define TREECHILDLAST "+"
#define TREECHILD "|"
#define TREELEAF ">"
#define TREEBRANCH "-"
#endif

#define ERR_COLOR "145;40;40"
#define ERR_TOKEN "\033[48;2;" ERR_COLOR "m<error>\033[0m"
#define ERR_TEMPLATE "\033[48;2;" ERR_COLOR "m  > %s\033[0m\n\033[48;2;" ERR_COLOR "m====\033[0m\n"
#define ERR_LOCATION "\033[48;2;" ERR_COLOR "m%s:%d:%d\033[0m\n"

int yylex();
int yyerror(int *max, int *childrenCount, char *s);
void ssprintf(char *target, char *template, ...);
void print(node_t node, void *data);
void max_level(node_t node, void *data);
void free_values(node_t node, void *data);

char filename[512];
char syn_errormsg[NAMESIZE];
extern int lnum, lcol;
node_t root;
node_t parent = NULL;
list_t parents;

#line 122 "sintatico.tab.c"

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
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_TYPE = 4,                       /* TYPE  */
  YYSYMBOL_OPPOS = 5,                      /* OPPOS  */
  YYSYMBOL_OPUNI = 6,                      /* OPUNI  */
  YYSYMBOL_IN = 7,                         /* IN  */
  YYSYMBOL_OPBIN3 = 8,                     /* OPBIN3  */
  YYSYMBOL_OPBIN4 = 9,                     /* OPBIN4  */
  YYSYMBOL_OPBIN5 = 10,                    /* OPBIN5  */
  YYSYMBOL_OPBIN6 = 11,                    /* OPBIN6  */
  YYSYMBOL_OPBIN7 = 12,                    /* OPBIN7  */
  YYSYMBOL_OPBIN8 = 13,                    /* OPBIN8  */
  YYSYMBOL_OPBIN9 = 14,                    /* OPBIN9  */
  YYSYMBOL_OPBIN10 = 15,                   /* OPBIN10  */
  YYSYMBOL_OPASSIGN = 16,                  /* OPASSIGN  */
  YYSYMBOL_STRING = 17,                    /* STRING  */
  YYSYMBOL_CHAR = 18,                      /* CHAR  */
  YYSYMBOL_INT = 19,                       /* INT  */
  YYSYMBOL_FLOAT = 20,                     /* FLOAT  */
  YYSYMBOL_IF = 21,                        /* IF  */
  YYSYMBOL_WHILE = 22,                     /* WHILE  */
  YYSYMBOL_FORALL = 23,                    /* FORALL  */
  YYSYMBOL_FOR = 24,                       /* FOR  */
  YYSYMBOL_ELSE = 25,                      /* ELSE  */
  YYSYMBOL_RETURN = 26,                    /* RETURN  */
  YYSYMBOL_EMPTY = 27,                     /* EMPTY  */
  YYSYMBOL_28_ = 28,                       /* '?'  */
  YYSYMBOL_29_ = 29,                       /* ':'  */
  YYSYMBOL_30_ = 30,                       /* '+'  */
  YYSYMBOL_31_ = 31,                       /* '-'  */
  YYSYMBOL_32_ = 32,                       /* '*'  */
  YYSYMBOL_33_ = 33,                       /* '/'  */
  YYSYMBOL_34_ = 34,                       /* '%'  */
  YYSYMBOL_35_ = 35,                       /* '!'  */
  YYSYMBOL_36_ = 36,                       /* '~'  */
  YYSYMBOL_37_ = 37,                       /* '&'  */
  YYSYMBOL_38_ = 38,                       /* '('  */
  YYSYMBOL_39_ = 39,                       /* ')'  */
  YYSYMBOL_40_ = 40,                       /* ';'  */
  YYSYMBOL_41_ = 41,                       /* '{'  */
  YYSYMBOL_42_ = 42,                       /* '}'  */
  YYSYMBOL_43_ = 43,                       /* ','  */
  YYSYMBOL_44_ = 44,                       /* '='  */
  YYSYMBOL_YYACCEPT = 45,                  /* $accept  */
  YYSYMBOL_prog = 46,                      /* prog  */
  YYSYMBOL_47_1 = 47,                      /* $@1  */
  YYSYMBOL_cmds = 48,                      /* cmds  */
  YYSYMBOL_49_2 = 49,                      /* $@2  */
  YYSYMBOL_cmdstail = 50,                  /* cmdstail  */
  YYSYMBOL_51_3 = 51,                      /* $@3  */
  YYSYMBOL_cmd = 52,                       /* cmd  */
  YYSYMBOL_53_4 = 53,                      /* @4  */
  YYSYMBOL_54_5 = 54,                      /* $@5  */
  YYSYMBOL_55_6 = 55,                      /* $@6  */
  YYSYMBOL_56_7 = 56,                      /* @7  */
  YYSYMBOL_57_8 = 57,                      /* @8  */
  YYSYMBOL_58_9 = 58,                      /* @9  */
  YYSYMBOL_59_10 = 59,                     /* @10  */
  YYSYMBOL_60_11 = 60,                     /* @11  */
  YYSYMBOL_61_12 = 61,                     /* $@12  */
  YYSYMBOL_62_13 = 62,                     /* @13  */
  YYSYMBOL_63_14 = 63,                     /* @14  */
  YYSYMBOL_64_15 = 64,                     /* $@15  */
  YYSYMBOL_declr_fntail = 65,              /* declr_fntail  */
  YYSYMBOL_66_16 = 66,                     /* $@16  */
  YYSYMBOL_67_17 = 67,                     /* $@17  */
  YYSYMBOL_68_18 = 68,                     /* $@18  */
  YYSYMBOL_parlist = 69,                   /* parlist  */
  YYSYMBOL_70_19 = 70,                     /* $@19  */
  YYSYMBOL_71_20 = 71,                     /* $@20  */
  YYSYMBOL_partail = 72,                   /* partail  */
  YYSYMBOL_forargs = 73,                   /* forargs  */
  YYSYMBOL_74_21 = 74,                     /* $@21  */
  YYSYMBOL_75_22 = 75,                     /* $@22  */
  YYSYMBOL_76_23 = 76,                     /* $@23  */
  YYSYMBOL_77_24 = 77,                     /* $@24  */
  YYSYMBOL_78_25 = 78,                     /* $@25  */
  YYSYMBOL_fordeclrlist = 79,              /* fordeclrlist  */
  YYSYMBOL_fortail = 80,                   /* fortail  */
  YYSYMBOL_idlist = 81,                    /* idlist  */
  YYSYMBOL_82_26 = 82,                     /* $@26  */
  YYSYMBOL_83_27 = 83,                     /* $@27  */
  YYSYMBOL_exp = 84,                       /* exp  */
  YYSYMBOL_85_28 = 85,                     /* @28  */
  YYSYMBOL_fntail = 86,                    /* fntail  */
  YYSYMBOL_arglist = 87,                   /* arglist  */
  YYSYMBOL_argtail = 88                    /* argtail  */
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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   14035

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  44
/* YYNRULES -- Number of rules.  */
#define YYNRULES  124
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  819

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
       2,     2,     2,    35,     2,     2,     2,    34,    37,     2,
      38,    39,    32,    30,    43,    31,     2,    33,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    29,    40,
       2,    44,     2,    28,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    41,     2,    42,    36,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   104,   104,   104,   120,   121,   121,   126,   127,   127,
     132,   137,   143,   148,   153,   157,   153,   163,   166,   170,
     170,   177,   180,   180,   204,   204,   217,   225,   234,   234,
     244,   244,   255,   262,   268,   262,   275,   284,   291,   275,
     300,   300,   310,   310,   324,   324,   339,   340,   345,   345,
     352,   352,   361,   362,   367,   380,   389,   380,   392,   400,
     392,   403,   403,   406,   413,   414,   420,   423,   428,   429,
     429,   432,   432,   440,   445,   450,   453,   458,   463,   471,
     479,   487,   495,   503,   511,   519,   527,   536,   545,   554,
     563,   572,   581,   590,   599,   608,   617,   626,   635,   644,
     657,   666,   666,   675,   678,   683,   695,   707,   719,   731,
     743,   755,   767,   779,   791,   803,   815,   827,   839,   853,
     854,   860,   861,   866,   867
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
  "\"end of file\"", "error", "\"invalid token\"", "ID", "TYPE", "OPPOS",
  "OPUNI", "IN", "OPBIN3", "OPBIN4", "OPBIN5", "OPBIN6", "OPBIN7",
  "OPBIN8", "OPBIN9", "OPBIN10", "OPASSIGN", "STRING", "CHAR", "INT",
  "FLOAT", "IF", "WHILE", "FORALL", "FOR", "ELSE", "RETURN", "EMPTY",
  "'?'", "':'", "'+'", "'-'", "'*'", "'/'", "'%'", "'!'", "'~'", "'&'",
  "'('", "')'", "';'", "'{'", "'}'", "','", "'='", "$accept", "prog",
  "$@1", "cmds", "$@2", "cmdstail", "$@3", "cmd", "@4", "$@5", "$@6", "@7",
  "@8", "@9", "@10", "@11", "$@12", "@13", "@14", "$@15", "declr_fntail",
  "$@16", "$@17", "$@18", "parlist", "$@19", "$@20", "partail", "forargs",
  "$@21", "$@22", "$@23", "$@24", "$@25", "fordeclrlist", "fortail",
  "idlist", "$@26", "$@27", "exp", "@28", "fntail", "arglist", "argtail", YY_NULLPTR
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
     275,   276,   277,   278,   279,   280,   281,   282,    63,    58,
      43,    45,    42,    47,    37,    33,   126,    38,    40,    41,
      59,   123,   125,    44,    61
};
#endif

#define YYPACT_NINF (-714)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-125)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    3399,     3,  3438,  -714, 10237,    73, 10270, 10438, 10472, 10483,
   10517,    -6,    37,    56,    61,   586, 10528, 10270, 10270, 10270,
   10270, 10270, 10270, 10292,  3477,   105,  3516,    68, 10562, 10573,
    6637,    81,   128,   272,    84,    83, 10607,  6659,  6681,  6703,
      97,   125, 10618, 10652, 10663, 10697, 10708, 10742, 10753, 11698,
    3555,  5255, 10270,  6725,  6747,  6769,  6791,  6813,  6835,  6857,
     182, 10314,  6879,  6901,  6923,  6945,  6967,  3594, 10787, 10798,
     841, 10832,   151,    74,    78,   137,   232,   153,   168, 11731,
     180, 11741,   191, 11774,  6599,  3633,  3672, 10843,   234,  3711,
     210, 10877, 10888, 10922, 10933, 10967, 10978, 11012, 11023, 11057,
   11068, 11102, 11113, 11147, 11158, 11192, 11203, 13076, 11237, 11248,
   11282, 11293, 11327, 11338, 11372, 11383, 11417, 11428,   424,   111,
     157,   219,    74,    74,    89,    85,   235,   267,  6295,  6295,
    6334,  6373,  6412,  6373,   286,  6989,   266,   280, 11462,  3555,
    3750, 10270, 10336,   123, 11473, 11507,   288,  3789,   292,  3828,
     287,   303,   100,    67,   100,   320,   371,  2502,  2541,  6373,
    3867,  6373,  3906,     2, 11518,  6451,   305,   335,   374, 11552,
     424,  5295,    40,   373,   375,   377,   341,   380,   342,  3945,
    6373,  6373,  3984,  4023, 10358,    74,  6373,   280,   147,  5255,
     344,  5335,   100,   379,   346,   350,  5255,  4062,  4101,  8445,
     351,  4140,   353,   348,  5375,  5255,   393,   100,   354,   173,
     335,  4179,  5255,   355,   394,   398,   397,   361,   280,   360,
    4218,   402,   363,   335,   365,  4257,  4296, 10358,   280,  8482,
     366,   368, 10392, 10292, 11784, 11817, 11827, 11860, 11870, 10292,
   10292, 10292, 10292, 10292, 10292, 10292, 10292,  7027,  7049,  7071,
    7093,  7115,  7137,  7159,   413, 10314,  7181,  7203,  7225,  7247,
    7269,   171,   378,   382,   383,    61,  7291,  5415,  5455,   381,
   11563, 10427, 10314, 13104, 13113, 13141, 13150, 13178, 10314, 10314,
   10314, 10314, 10314, 10314, 10292,   190, 10336,   631,   721,   786,
     823,   874, 10336, 10336, 10336, 10336, 10336, 10336, 10292, 10314,
    7313,  7335,  7357,  7379,  7401,  7423,  7445,   417, 10314,  7467,
    7489,  7511,  7533,  7555, 10336,  7577,  7599,  7621,  7643,  7665,
    7687,  7709,   423, 10314,  7731,  7753,  7775,  7797,  7819,   172,
     388,   389,   390,    61,  7841,  2580,   399, 11597, 10202,   426,
     437,  6566, 10358,  8519,  8556,  8593,  8630,  8667, 10358, 10358,
   10358, 10358, 10358, 10358, 10292, 10358,  7863,  7885,  7907,  7929,
    7951,  7973,  7995,   441, 10314,  8017,  8039,  8061,  8083,  8105,
   11903,  8127,   406, 11913, 11946, 11956, 11989, 11999, 12032, 12042,
   12075, 12085, 12118, 12128, 12161, 12171, 12204, 12214, 12247, 12257,
   12290, 12300, 12333, 12343, 12376, 12386, 12419, 13187, 12429, 12462,
   12472, 12505, 12515, 12548, 12558, 12591, 12601, 12634,   222,   408,
      83,  8149,  8171,  8193,   409,   411, 11608,  5495,  5255,  5535,
   13215,  8215,   410, 13224, 13252, 13261, 13289, 13298, 13326, 13335,
   12644,   917,  8237,   415,   994,  1053,  1093,  1132,  1169,  1206,
    1243, 12677, 13363, 13372, 13400, 13409, 13437, 13446, 13474, 13483,
   13511, 13520, 13548, 13557, 13585, 13594, 13622, 13631, 13659, 13668,
   13696, 13705, 13733, 13742, 13770, 13779, 13807, 13816, 13844,  1280,
    1317,  1354,  1391,  1428,  1465,  1502,  1539,  1576,  1613,  1650,
    1687,  1724,  1761,  1798,  1835, 13853,  1872,  1909,  1946,  1983,
    2020,  2057,  2094,  2131,  2168,  2205,   229,   421,    83,  8259,
    8281,  8303,   422,   428, 11642,  5255,  2619, 12687,    67,   446,
    8704,  8325,   431,  8741,  8778,  8815,  8852,  8889,  8926,  8963,
   12720,  9000,  9037,  9074,  9111,  9148,  9185,  9222,  9259,  9296,
    9333,  9370,  9407,  9444,  9481,  9518,  9555, 13881,  9592,  9629,
    9666,  9703,  9740,  9777,  9814,  9851,  9888,  9925, 12730, 12763,
     841, 12773, 12806, 10292,   151,    74,   232,   433,   427, 12816,
     436, 12849,   440, 12859,  6599,  5575,  5615,   419,  5655,   420,
   13890, 13918,   841, 13927, 13955,  2242,  2279,   841,  2316,  2353,
   10314, 10336,   151,    74,   232,   444,   442, 12892,   447, 12902,
     448, 12935,  6599,  2658,  2697,   438,   449,    67,  9962,  9999,
     841, 10036, 10073, 10358,   148, 12945,   334,   450,   452,   267,
    6490,  6490,  6334,  6529,  6412,  6529,   453,  5495,  5695,   169,
     188, 13964,  2390,   338,   454,   456,   267,  6295,  6295,  6334,
    6295,  6412,  6295,   457,  2736,   462,   193, 10110, 12978, 12988,
     464,  5735,   467,  5775,   320,   488,   223,   455,   465,   469,
      61,  8347,  4335,  4375,   471, 11653,  4415,  6529,  5815,  6529,
    5855,  6451,   466, 13992, 14001,  2427,  2464,   472,  2775,   475,
    2814,   320,   509,  2853,  2892,  6295,  2931,  6295,  2970,  6451,
   10147, 10184,  5295,    79,   474,  5895,   290,   478,    83,  8369,
    8391,  8413,   480,   479, 11687,  6529,  5255,  4455,  6529,  5935,
    5975,  6529,  5295,    95,   481,  3009,  6295,  6295,  3048,  3087,
    6295,  5255,   485,  5335,  5255,   151,    74,   232,   486,   482,
   13021,   489, 13031,   491, 13064,  6599,  4495,  4535,  6015,   490,
    6055,  6095,  5255,   487,  5335,  5255,  3126,  3165,  3204,   492,
    5375,  5255,   493,   367,   496,   494,   267,  6490,  6490,  6334,
    6490,  6412,  6490,   498,  4575,   499,  5375,  5255,   500,  6135,
    5255,   501,   398,   497,  4615,   505,  4655,   320,   519,  4695,
    4735,  6490,  4775,  6490,  4815,  6451,  3243,  5255,   503,   398,
     504,  6175,   530,  5295,   101,   506,  4855,  6490,  6490,  4895,
    4935,  6490,   507,  3282,   539,  6215,  6255,  5255,   510,  5335,
    5255,  4975,  5015,  5055,  3321,  3360,   511,  5375,  5255,   512,
    5095,  5255,   513,   398,   514,  5135,   551,  5175,  5215
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     1,     0,     0,     0,     0,     0,     0,
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
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -714,  -714,  -714,   -20,   289,  -134,   -10,   284,  -264,  -587,
     343,  -399,  -543,  -605,  -606,  -400,  -582,  -259,  -586,  -713,
    -576,  -691,  -676,  -673,  -106,  -714,  -714,  -120,  -552,  -714,
    -714,  -714,  -714,  -714,   330,   -72,   -44,  -714,  -714,    -2,
    -194,  -349,  -447,   391
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    25,    50,    88,   139,   268,    40,   186,
     269,    73,   120,   159,   161,    77,   156,    34,   178,   221,
     147,   205,   189,   212,   126,   152,   154,   175,   136,   209,
     223,   185,   210,   167,   217,   137,    35,   123,   122,   270,
      31,    71,   119,   143
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      28,   414,   409,     3,    36,   168,   711,   657,   659,   555,
     557,   606,   616,    42,   148,    43,    44,    45,    46,    47,
      48,    49,   741,   551,   675,   677,   732,   645,    69,   121,
     641,    90,    37,   176,   177,    79,    81,    83,   372,   623,
     633,   190,   -58,   757,   672,   -58,   184,   668,    28,   782,
      91,    93,    95,    97,    99,   101,   103,   105,   684,   107,
     109,   111,   113,   115,   117,   166,   794,   760,   118,   502,
     497,   339,   206,   573,   701,    38,    32,   422,   150,   151,
     712,   191,   138,   777,   578,   704,   -50,   214,   153,   -50,
     -48,   433,   710,   -48,    39,   187,   733,   583,   585,   -14,
     816,   -52,   798,   604,   173,    -3,   -52,   797,   808,    51,
     340,   -36,   144,   -68,   -68,   202,    33,    33,   -71,    70,
     713,   -71,    76,   -33,  -122,   619,   337,   337,   -50,    28,
     620,    28,   -48,   164,   811,    84,   734,    28,   218,   169,
     170,   200,   799,   174,   771,   773,   224,   512,  -124,   638,
     145,   228,   -24,   636,   -24,   -24,   230,    28,   146,    28,
     124,   125,  -122,   601,   768,    85,    72,   764,   -22,   203,
     663,   -22,   743,   753,   408,   496,   208,   -69,    28,    28,
     -69,   785,   199,   106,    28,   213,  -124,   639,   791,   665,
     -24,  -103,   219,   127,   680,   431,   -46,  -103,  -103,  -103,
    -103,  -103,  -103,  -103,  -103,  -103,   432,   128,   664,   -36,
     -36,   -68,   -68,   -64,    33,    33,   216,   410,  -103,   130,
    -103,  -103,  -103,  -103,  -103,   229,   686,   666,  -101,  -103,
     132,   373,   681,  -103,    -6,   124,   125,   374,   375,   376,
     377,   378,   379,   380,   381,   383,   385,   387,   389,   391,
     393,   395,   140,   397,   399,   401,   403,   405,   407,   149,
     554,   -36,   -22,   -68,   416,   -22,    33,   582,   -34,   -22,
     423,   -46,   -22,    74,   155,    75,   424,   425,   426,   427,
     428,   429,   430,   567,   434,   498,    26,   716,   718,   163,
     435,   436,   437,   438,   439,   440,   441,   442,   444,   446,
     448,   450,   452,   454,   456,   165,   458,   460,   462,   464,
     466,   468,   469,   471,   473,   475,   477,   479,   481,   483,
     338,   485,   487,   489,   491,   493,   495,   -72,   715,   171,
     -22,   172,   504,   -22,    89,   640,   507,   124,   125,   667,
     513,   124,   125,   -70,   -63,    27,   514,   515,   516,   517,
     518,   519,   520,   521,   523,   525,   527,   529,   531,   533,
     535,   -37,   537,   539,   541,   543,   545,   547,   763,   549,
     124,   125,   179,   -46,    -9,   135,   192,   -46,   194,   193,
     -47,   195,   207,   196,   204,   -49,   692,   687,   596,   -51,
     211,   -59,   -62,    27,   -54,   -53,   215,   220,   569,   -38,
     222,   -56,   225,   226,   -60,   -57,   -46,   227,   -65,   559,
     561,   563,   157,   158,   396,   160,   411,   162,   457,   571,
     412,   413,   418,    89,   484,  -123,   499,   500,   501,   508,
     576,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     505,   509,   536,   182,   550,   183,   556,   564,   572,   597,
     608,   565,   323,   577,   324,   325,   326,   327,   328,   584,
     592,    -6,   618,  -123,   197,   198,   610,   142,   593,   600,
     201,   336,   336,   609,    27,   612,    27,   635,   625,   614,
     634,   627,    27,   662,   626,   595,   629,   631,   -54,   685,
     643,   644,   661,   689,   670,   671,   679,   587,   589,   591,
     642,   -53,    27,   690,    27,   682,   683,   691,    -9,   599,
     705,   607,   696,   702,   703,   714,   717,   669,   725,   726,
     786,   747,   735,    27,    27,   740,   746,   756,   749,    27,
     751,   796,   754,   767,   759,   762,   766,   775,   783,   624,
     805,   776,   779,   781,   784,   793,   795,   800,   118,   804,
     807,   605,   818,   810,   813,   815,   817,   417,   617,   231,
       0,   188,   138,     0,     0,     0,     0,     0,     0,     0,
     118,     0,     0,     0,     0,   118,     0,     0,   621,   622,
       0,     0,     0,     0,     0,     0,     0,    41,     0,     4,
     138,     0,     6,     0,     0,     0,     0,     0,   118,     0,
       0,   637,   688,     7,     8,     9,    10,     0,   655,   655,
       0,   745,     0,    16,     0,     0,    17,    18,    19,     0,
       0,    20,    21,    22,    23,   337,   337,     0,   337,     0,
     337,     0,   -76,     0,     0,     0,     0,   765,   -76,   -76,
     -76,   -76,   -76,   -76,   -76,   -76,   -76,     0,     0,   694,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -76,
       0,   -76,   -76,   -76,   -76,   -76,     0,     0,     0,     0,
     -76,     0,   744,   337,   -76,   337,   729,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   720,   722,   724,
       0,   739,     0,     0,   742,     0,     0,     0,     0,     0,
       0,   568,     0,     0,   337,   337,     0,     0,   337,     0,
       0,     0,   755,     0,     0,   758,     0,     0,     0,     0,
       0,   761,   -77,   138,     0,     0,     0,     0,   -77,   -77,
     -77,   -77,   -77,   -77,   -77,   -77,   -77,   778,     0,     0,
     780,     0,     0,     0,     0,   655,   655,     0,   655,   -77,
     655,   -77,   -77,   -77,   -77,   -77,     0,   792,     0,     0,
     -77,     0,     0,     0,   -77,     0,     0,     0,     0,   655,
       0,   655,     0,     0,     0,     0,     0,   806,     0,     0,
     809,     0,     0,     0,     0,   655,   655,   -73,   812,   655,
       0,   814,     0,   -73,   -73,   -73,   -73,   -73,   -73,   -73,
     -73,   -73,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -73,     0,   -73,   -73,   -73,   -73,
     -73,     0,     0,     0,   -74,   -73,     0,     0,     0,   -73,
     -74,   -74,   -74,   -74,   -74,   -74,   -74,   -74,   -74,     0,
       0,     0,  -121,     0,   285,     0,     0,   286,     0,     0,
       0,   -74,     0,   -74,   -74,   -74,   -74,   -74,   287,   288,
     289,   290,   -74,     0,     0,     0,   -74,     0,   291,     0,
       0,   292,   293,   294,     0,   -75,   295,   296,   297,   298,
    -121,   -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,
       0,     0,     0,     0,   653,   656,     0,   658,     0,   660,
       0,   568,   -75,     0,   -75,   -75,   -75,   -75,   -75,     0,
       0,   673,   674,   -75,   676,     0,   678,   -75,   -78,     0,
       0,     0,     0,     0,   -78,   -78,   -78,   -78,   -78,   -78,
     -78,   -78,   -78,     0,     0,     0,     0,     0,     0,     0,
       0,   699,     0,   700,     0,   -78,     0,   -78,   -78,   -78,
     -78,   -78,     0,   654,   654,     0,   -78,     0,     0,   708,
     -78,   709,     0,     0,     0,     0,     0,     0,     0,     0,
     336,   336,     0,   336,     0,   336,     0,     0,     0,   728,
       0,     0,   730,     0,     0,   731,     0,     0,     0,     0,
     736,   737,     0,     0,   738,   -85,     0,     0,     0,     0,
       0,   -85,   -85,   -85,   -85,   -85,   -85,   -85,   -85,   -85,
       0,     0,     0,     0,     0,     0,     0,     0,   336,     0,
     336,     0,   -85,     0,   -85,   -85,   -85,   -85,   -85,     0,
       0,   769,   770,   -85,   772,     0,   774,   -85,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   336,
     336,     0,     0,   336,   -80,   789,     0,   790,     0,     0,
     -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,     0,
       0,   801,   802,     0,     0,   803,     0,     0,     0,     0,
       0,   -80,     0,   -80,   -80,   -80,   -80,   -80,     0,     0,
     654,   654,   -80,   654,   -81,   654,   -80,     0,     0,     0,
     -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,     0,
       0,     0,     0,     0,   654,     0,   654,     0,     0,     0,
       0,   -81,     0,   -81,   -81,   -81,   -81,   -81,     0,     0,
     654,   654,   -81,   -79,   654,     0,   -81,     0,     0,   -79,
     -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -79,     0,   -79,   -79,   -79,   -79,   -79,     0,     0,     0,
     -82,   -79,     0,     0,     0,   -79,   -82,   -82,   -82,   -82,
     -82,   -82,   -82,   -82,   -82,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -82,     0,   -82,
     -82,   -82,   -82,   -82,     0,     0,     0,   -83,   -82,     0,
       0,     0,   -82,   -83,   -83,   -83,   -83,   -83,   -83,   -83,
     -83,   -83,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -83,     0,   -83,   -83,   -83,   -83,
     -83,     0,     0,     0,   -84,   -83,     0,     0,     0,   -83,
     -84,   -84,   -84,   -84,   -84,   -84,   -84,   -84,   -84,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -84,     0,   -84,   -84,   -84,   -84,   -84,     0,     0,
       0,   -91,   -84,     0,     0,     0,   -84,   -91,   -91,   -91,
     -91,   -91,   -91,   -91,   -91,   -91,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -91,     0,
     -91,   -91,   -91,   -91,   -91,     0,     0,     0,  -110,   -91,
       0,     0,     0,   -91,  -110,  -110,  -110,  -110,  -110,  -110,
    -110,  -110,  -110,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -110,     0,  -110,  -110,  -110,
    -110,  -110,     0,     0,     0,   -92,  -110,     0,     0,     0,
    -110,   314,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -92,     0,   324,   325,   326,   327,   328,     0,
       0,     0,  -111,   -92,     0,     0,     0,   -92,  -111,  -111,
    -111,  -111,  -111,  -111,  -111,  -111,  -111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -111,
       0,  -111,  -111,  -111,  -111,  -111,     0,     0,     0,   -93,
    -111,     0,     0,     0,  -111,   314,   315,   -93,   -93,   -93,
     -93,   -93,   -93,   -93,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -93,     0,   324,   325,
     326,   327,   328,     0,     0,     0,  -112,   -93,     0,     0,
       0,   -93,  -112,  -112,  -112,  -112,  -112,  -112,  -112,  -112,
    -112,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -112,     0,  -112,  -112,  -112,  -112,  -112,
       0,     0,     0,   -94,  -112,     0,     0,     0,  -112,   314,
     315,   316,   -94,   -94,   -94,   -94,   -94,   -94,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -94,     0,   324,   325,   326,   327,   328,     0,     0,     0,
    -113,   -94,     0,     0,     0,   -94,  -113,  -113,  -113,  -113,
    -113,  -113,  -113,  -113,  -113,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -113,     0,  -113,
    -113,  -113,  -113,  -113,     0,     0,     0,   -95,  -113,     0,
       0,     0,  -113,   314,   315,   316,   317,   -95,   -95,   -95,
     -95,   -95,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -95,     0,   324,   325,   326,   327,
     328,     0,     0,     0,  -114,   -95,     0,     0,     0,   -95,
    -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -114,     0,  -114,  -114,  -114,  -114,  -114,     0,     0,
       0,   -96,  -114,     0,     0,     0,  -114,   314,   315,   316,
     317,   318,   -96,   -96,   -96,   -96,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -96,     0,
     324,   325,   326,   327,   328,     0,     0,     0,  -115,   -96,
       0,     0,     0,   -96,  -115,  -115,  -115,  -115,  -115,  -115,
    -115,  -115,  -115,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -115,     0,  -115,  -115,  -115,
    -115,  -115,     0,     0,     0,   -97,  -115,     0,     0,     0,
    -115,   314,   315,   316,   317,   318,   319,   -97,   -97,   -97,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -97,     0,   324,   325,   326,   327,   328,     0,
       0,     0,  -116,   -97,     0,     0,     0,   -97,  -116,  -116,
    -116,  -116,  -116,  -116,  -116,  -116,  -116,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -116,
       0,  -116,  -116,  -116,  -116,  -116,     0,     0,     0,   -98,
    -116,     0,     0,     0,  -116,   314,   315,   316,   317,   318,
     319,   320,   -98,   -98,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -98,     0,   324,   325,
     326,   327,   328,     0,     0,     0,  -117,   -98,     0,     0,
       0,   -98,  -117,  -117,  -117,  -117,  -117,  -117,  -117,  -117,
    -117,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -117,     0,  -117,  -117,  -117,  -117,  -117,
       0,     0,     0,  -108,  -117,     0,     0,     0,  -117,  -108,
    -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -108,     0,  -108,  -108,  -108,  -108,  -108,     0,     0,     0,
     -89,  -108,     0,     0,     0,  -108,   314,   -89,   -89,   -89,
     -89,   -89,   -89,   -89,   -89,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -89,     0,   -89,
     -89,   326,   327,   328,     0,     0,     0,  -109,   -89,     0,
       0,     0,   -89,  -109,  -109,  -109,  -109,  -109,  -109,  -109,
    -109,  -109,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -109,     0,  -109,  -109,  -109,  -109,
    -109,     0,     0,     0,   -90,  -109,     0,     0,     0,  -109,
     314,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -90,     0,   -90,   -90,   326,   327,   328,     0,     0,
       0,  -105,   -90,     0,     0,     0,   -90,  -105,  -105,  -105,
    -105,  -105,  -105,  -105,  -105,  -105,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -105,     0,
    -105,  -105,  -105,  -105,  -105,     0,     0,     0,   -86,  -105,
       0,     0,     0,  -105,   314,   -86,   -86,   -86,   -86,   -86,
     -86,   -86,   -86,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -86,     0,   -86,   -86,   -86,
     -86,   -86,     0,     0,     0,  -106,   -86,     0,     0,     0,
     -86,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -106,     0,  -106,  -106,  -106,  -106,  -106,     0,
       0,     0,   -87,  -106,     0,     0,     0,  -106,   314,   -87,
     -87,   -87,   -87,   -87,   -87,   -87,   -87,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -87,
       0,   -87,   -87,   -87,   -87,   -87,     0,     0,     0,  -107,
     -87,     0,     0,     0,   -87,  -107,  -107,  -107,  -107,  -107,
    -107,  -107,  -107,  -107,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -107,     0,  -107,  -107,
    -107,  -107,  -107,     0,     0,     0,   -88,  -107,     0,     0,
       0,  -107,   314,   -88,   -88,   -88,   -88,   -88,   -88,   -88,
     -88,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -88,     0,   -88,   -88,   -88,   -88,   -88,
       0,     0,     0,  -118,   -88,     0,     0,     0,   -88,  -118,
    -118,  -118,  -118,  -118,  -118,  -118,  -118,  -118,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -118,     0,  -118,  -118,  -118,  -118,  -118,     0,     0,     0,
    -100,  -118,     0,     0,     0,  -118,   314,   315,   316,   317,
     318,   319,   320,   321,   322,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   323,     0,   324,
     325,   326,   327,   328,     0,     0,     0,  -102,  -100,     0,
       0,     0,  -100,  -102,  -102,  -102,  -102,  -102,  -102,  -102,
    -102,  -102,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -102,     0,  -102,  -102,  -102,  -102,
    -102,     0,     0,     0,  -104,  -102,     0,     0,     0,  -102,
    -104,  -104,  -104,  -104,  -104,  -104,  -104,  -104,  -104,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -104,     0,  -104,  -104,  -104,  -104,  -104,     0,     0,
       0,   -99,  -104,     0,     0,     0,  -104,   314,   315,   316,
     317,   318,   319,   320,   321,   322,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   323,     0,
     324,   325,   326,   327,   328,     0,     0,     0,  -120,   -99,
       0,     0,     0,   -99,  -120,  -120,  -120,  -120,  -120,  -120,
    -120,  -120,  -120,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -120,     0,  -120,  -120,  -120,
    -120,  -120,     0,     0,     0,  -119,  -120,     0,     0,     0,
    -120,  -119,  -119,  -119,  -119,  -119,  -119,  -119,  -119,  -119,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -119,     0,  -119,  -119,  -119,  -119,  -119,     0,
       0,     0,   -26,  -119,     0,   -26,   -26,  -119,   -26,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -26,
     -26,   -26,   -26,   -26,   -26,   -26,   -26,   180,   -26,   -26,
       0,     0,   -26,   -26,   -26,     0,     0,   -26,   -26,   -26,
     -26,   -10,   -26,   -26,   -10,   -10,     0,   -10,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -10,   -10,
     -10,   -10,   -10,   -10,   -10,   -10,   181,   -10,   -10,     0,
       0,   -10,   -10,   -10,     0,     0,   -10,   -10,   -10,   -10,
     -21,   -10,   -10,   -21,   -21,     0,   -21,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -21,   -21,   -21,
     -21,   -21,   -21,   -21,   -21,   -21,   -21,   -21,     0,     0,
     -21,   -21,   -21,     0,     0,   -21,   -21,   -21,   -21,   -17,
     -21,   -21,   -17,   -17,     0,   -17,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -17,   -17,   -17,   -17,
     -17,   -17,   -17,   -17,   -17,   -17,   -17,     0,     0,   -17,
     -17,   -17,     0,     0,   -17,   -17,   -17,   -17,   -32,   -17,
     -17,   -32,   -32,     0,   -32,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -32,   -32,   -32,   -32,   -32,
     -32,   -32,   -32,   -32,   -32,   -32,     0,     0,   -32,   -32,
     -32,     0,     0,   -32,   -32,   -32,   -32,   -18,   -32,   -32,
     -18,   -18,     0,   -18,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -18,   -18,   -18,   -18,   -18,   -18,
     -18,   -18,   -18,   -18,   -18,     0,     0,   -18,   -18,   -18,
       0,     0,   -18,   -18,   -18,   -18,   -20,   -18,   -18,   -20,
     -20,     0,   -20,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -20,   -20,   -20,   -20,   -20,   -20,   -20,
     -20,   -20,   -20,   -20,     0,     0,   -20,   -20,   -20,     0,
       0,   -20,   -20,   -20,   -20,   -25,   -20,   -20,   -25,   -25,
       0,   -25,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -25,   -25,   -25,   -25,   -25,   -25,   -25,   -25,
     -25,   -25,   -25,     0,     0,   -25,   -25,   -25,     0,     0,
     -25,   -25,   -25,   -25,   -23,   -25,   -25,   -23,   -23,     0,
     -23,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -23,   -23,   -23,   -23,   -23,   -23,   -23,   -23,   -23,
     -23,   -23,     0,     0,   -23,   -23,   -23,     0,     0,   -23,
     -23,   -23,   -23,   -26,   -23,   -23,   -26,   -26,     0,   -26,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -26,   -26,   -26,   -26,   -26,   -26,   -26,   -26,   706,   -26,
     -26,     0,     0,   -26,   -26,   -26,     0,     0,   -26,   -26,
     -26,   -26,   -10,   -26,   -26,   -10,   -10,     0,   -10,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -10,
     -10,   -10,   -10,   -10,   -10,   -10,   -10,   707,   -10,   -10,
       0,     0,   -10,   -10,   -10,     0,     0,   -10,   -10,   -10,
     -10,   -12,   -10,   -10,   -12,   -12,     0,   -12,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -12,   -12,
     -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,     0,
       0,   -12,   -12,   -12,     0,     0,   -12,   -12,   -12,   -12,
     -13,   -12,   -12,   -13,   -13,     0,   -13,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -13,   -13,   -13,
     -13,   -13,   -13,   -13,   -13,   -13,   -13,   -13,     0,     0,
     -13,   -13,   -13,     0,     0,   -13,   -13,   -13,   -13,   -35,
     -13,   -13,   -35,   -35,     0,   -35,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -35,   -35,   -35,   -35,
     -35,   -35,   -35,   -35,   -35,   -35,   -35,     0,     0,   -35,
     -35,   -35,     0,     0,   -35,   -35,   -35,   -35,   -29,   -35,
     -35,   -29,   -29,     0,   -29,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -29,   -29,   -29,   -29,   -29,
     -29,   -29,   -29,   -29,   -29,   -29,     0,     0,   -29,   -29,
     -29,     0,     0,   -29,   -29,   -29,   -29,   -31,   -29,   -29,
     -31,   -31,     0,   -31,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -31,   -31,   -31,   -31,   -31,   -31,
     -31,   -31,   -31,   -31,   -31,     0,     0,   -31,   -31,   -31,
       0,     0,   -31,   -31,   -31,   -31,   -27,   -31,   -31,   -27,
     -27,     0,   -27,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -27,   -27,   -27,   -27,   -27,   -27,   -27,
     -27,   -27,   -27,   -27,     0,     0,   -27,   -27,   -27,     0,
       0,   -27,   -27,   -27,   -27,   -11,   -27,   -27,   -11,   -11,
       0,   -11,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -11,   -11,   -11,   -11,   -11,   -11,   -11,   -11,
     -11,   -11,   -11,     0,     0,   -11,   -11,   -11,     0,     0,
     -11,   -11,   -11,   -11,   -16,   -11,   -11,   -16,   -16,     0,
     -16,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -16,   -16,   -16,   -16,   -16,   -16,   -16,   -16,   -16,
     -16,   -16,     0,     0,   -16,   -16,   -16,     0,     0,   -16,
     -16,   -16,   -16,   -43,   -16,   -16,   -43,   -43,     0,   -43,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,
     -43,     0,     0,   -43,   -43,   -43,     0,     0,   -43,   -43,
     -43,   -43,   -41,   -43,   -43,   -41,   -41,     0,   -41,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -41,
     -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,
       0,     0,   -41,   -41,   -41,     0,     0,   -41,   -41,   -41,
     -41,   -45,   -41,   -41,   -45,   -45,     0,   -45,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -45,   -45,
     -45,   -45,   -45,   -45,   -45,   -45,   -45,   -45,   -45,     0,
       0,   -45,   -45,   -45,     0,     0,   -45,   -45,   -45,   -45,
     -39,   -45,   -45,   -39,   -39,     0,   -39,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -39,   -39,   -39,
     -39,   -39,   -39,   -39,   -39,   -39,   -39,   -39,     0,     0,
     -39,   -39,   -39,     0,     0,   -39,   -39,   -39,   -39,    -2,
     -39,   -39,    -2,    -2,     0,    -2,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    -2,    -2,    -2,    -2,
      -2,    -2,    -2,    -2,     0,    -2,    -2,     0,     0,    -2,
      -2,    -2,     0,     0,    -2,    -2,    -2,    -2,    -4,    -2,
      -2,     4,     5,     0,     6,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     7,     8,     9,    10,    11,
      12,    13,    14,     0,    15,    16,     0,     0,    17,    18,
      19,     0,     0,    20,    21,    22,    23,   -21,    24,   -19,
     -21,   -21,     0,   -21,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -21,   -21,   -21,   -21,   -21,   -21,
     -21,   -21,     0,   -21,   -21,     0,     0,   -21,   -21,   -21,
       0,     0,   -21,   -21,   -21,   -21,    -5,   -21,   -21,    -5,
      -5,     0,    -5,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    -5,    -5,    -5,    -5,    -5,    -5,    -5,
      -5,     0,    -5,    -5,     0,     0,    -5,    -5,    -5,     0,
       0,    -5,    -5,    -5,    -5,    -7,    -5,    -5,     4,     5,
       0,     6,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     7,     8,     9,    10,    11,    12,    13,    14,
       0,    15,    16,     0,     0,    17,    18,    19,     0,     0,
      20,    21,    22,    23,   -17,    24,   -19,   -17,   -17,     0,
     -17,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -17,   -17,   -17,   -17,   -17,   -17,   -17,   -17,     0,
     -17,   -17,     0,     0,   -17,   -17,   -17,     0,     0,   -17,
     -17,   -17,   -17,   -32,   -17,   -17,   -32,   -32,     0,   -32,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -32,   -32,   -32,   -32,   -32,   -32,   -32,   -32,     0,   -32,
     -32,     0,     0,   -32,   -32,   -32,     0,     0,   -32,   -32,
     -32,   -32,   -18,   -32,   -32,   -18,   -18,     0,   -18,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -18,
     -18,   -18,   -18,   -18,   -18,   -18,   -18,     0,   -18,   -18,
       0,     0,   -18,   -18,   -18,     0,     0,   -18,   -18,   -18,
     -18,    -8,   -18,   -18,    -8,    -8,     0,    -8,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    -8,    -8,
      -8,    -8,    -8,    -8,    -8,    -8,     0,    -8,    -8,     0,
       0,    -8,    -8,    -8,     0,     0,    -8,    -8,    -8,    -8,
     -20,    -8,    -8,   -20,   -20,     0,   -20,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -20,   -20,   -20,
     -20,   -20,   -20,   -20,   -20,     0,   -20,   -20,     0,     0,
     -20,   -20,   -20,     0,     0,   -20,   -20,   -20,   -20,   -25,
     -20,   -20,   -25,   -25,     0,   -25,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -25,   -25,   -25,   -25,
     -25,   -25,   -25,   -25,     0,   -25,   -25,     0,     0,   -25,
     -25,   -25,     0,     0,   -25,   -25,   -25,   -25,   -23,   -25,
     -25,   -23,   -23,     0,   -23,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -23,   -23,   -23,   -23,   -23,
     -23,   -23,   -23,     0,   -23,   -23,     0,     0,   -23,   -23,
     -23,     0,     0,   -23,   -23,   -23,   -23,   -12,   -23,   -23,
     -12,   -12,     0,   -12,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -12,   -12,   -12,   -12,   -12,   -12,
     -12,   -12,     0,   -12,   -12,     0,     0,   -12,   -12,   -12,
       0,     0,   -12,   -12,   -12,   -12,   -13,   -12,   -12,   -13,
     -13,     0,   -13,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -13,   -13,   -13,   -13,   -13,   -13,   -13,
     -13,     0,   -13,   -13,     0,     0,   -13,   -13,   -13,     0,
       0,   -13,   -13,   -13,   -13,   -35,   -13,   -13,   -35,   -35,
       0,   -35,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -35,   -35,   -35,   -35,   -35,   -35,   -35,   -35,
       0,   -35,   -35,     0,     0,   -35,   -35,   -35,     0,     0,
     -35,   -35,   -35,   -35,   -29,   -35,   -35,   -29,   -29,     0,
     -29,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -29,   -29,   -29,   -29,   -29,   -29,   -29,   -29,     0,
     -29,   -29,     0,     0,   -29,   -29,   -29,     0,     0,   -29,
     -29,   -29,   -29,   -31,   -29,   -29,   -31,   -31,     0,   -31,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -31,   -31,   -31,   -31,   -31,   -31,   -31,   -31,     0,   -31,
     -31,     0,     0,   -31,   -31,   -31,     0,     0,   -31,   -31,
     -31,   -31,   -27,   -31,   -31,   -27,   -27,     0,   -27,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -27,
     -27,   -27,   -27,   -27,   -27,   -27,   -27,     0,   -27,   -27,
       0,     0,   -27,   -27,   -27,     0,     0,   -27,   -27,   -27,
     -27,   -11,   -27,   -27,   -11,   -11,     0,   -11,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -11,   -11,
     -11,   -11,   -11,   -11,   -11,   -11,     0,   -11,   -11,     0,
       0,   -11,   -11,   -11,     0,     0,   -11,   -11,   -11,   -11,
     -16,   -11,   -11,   -16,   -16,     0,   -16,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -16,   -16,   -16,
     -16,   -16,   -16,   -16,   -16,     0,   -16,   -16,     0,     0,
     -16,   -16,   -16,     0,     0,   -16,   -16,   -16,   -16,   -43,
     -16,   -16,   -43,   -43,     0,   -43,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -43,   -43,   -43,   -43,
     -43,   -43,   -43,   -43,     0,   -43,   -43,     0,     0,   -43,
     -43,   -43,     0,     0,   -43,   -43,   -43,   -43,   -41,   -43,
     -43,   -41,   -41,     0,   -41,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -41,   -41,   -41,   -41,   -41,
     -41,   -41,   -41,     0,   -41,   -41,     0,     0,   -41,   -41,
     -41,     0,     0,   -41,   -41,   -41,   -41,   -45,   -41,   -41,
     -45,   -45,     0,   -45,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -45,   -45,   -45,   -45,   -45,   -45,
     -45,   -45,     0,   -45,   -45,     0,     0,   -45,   -45,   -45,
       0,     0,   -45,   -45,   -45,   -45,   -39,   -45,   -45,   -39,
     -39,     0,   -39,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -39,   -39,   -39,   -39,   -39,   -39,   -39,
     -39,     0,   -39,   -39,     0,     0,   -39,   -39,   -39,     0,
       0,   -39,   -39,   -39,   -39,     0,   -39,   -39,   -21,   -21,
       0,   -21,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -21,   -21,   -21,   -21,   -21,   -21,   -21,   -21,
     -21,   -21,   -21,     0,     0,   -21,   -21,   -21,     0,     0,
     -21,   -21,   -21,   -21,     0,   -21,   -21,   -21,   -26,   -26,
       0,   -26,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -26,   -26,   -26,   -26,   -26,   -26,   -26,   -26,
     695,   -26,   -26,     0,     0,   -26,   -26,   -26,     0,     0,
     -26,   -26,   -26,   -26,     0,   -26,   -26,   -26,   -10,   -10,
       0,   -10,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -10,   -10,   -10,   -10,   -10,   -10,   -10,   -10,
     698,   -10,   -10,     0,     0,   -10,   -10,   -10,     0,     0,
     -10,   -10,   -10,   -10,     0,   -10,   -10,   -10,   -17,   -17,
       0,   -17,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -17,   -17,   -17,   -17,   -17,   -17,   -17,   -17,
     -17,   -17,   -17,     0,     0,   -17,   -17,   -17,     0,     0,
     -17,   -17,   -17,   -17,     0,   -17,   -17,   -17,   -32,   -32,
       0,   -32,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -32,   -32,   -32,   -32,   -32,   -32,   -32,   -32,
     -32,   -32,   -32,     0,     0,   -32,   -32,   -32,     0,     0,
     -32,   -32,   -32,   -32,     0,   -32,   -32,   -32,   -18,   -18,
       0,   -18,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -18,   -18,   -18,   -18,   -18,   -18,   -18,   -18,
     -18,   -18,   -18,     0,     0,   -18,   -18,   -18,     0,     0,
     -18,   -18,   -18,   -18,     0,   -18,   -18,   -18,   -20,   -20,
       0,   -20,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -20,   -20,   -20,   -20,   -20,   -20,   -20,   -20,
     -20,   -20,   -20,     0,     0,   -20,   -20,   -20,     0,     0,
     -20,   -20,   -20,   -20,     0,   -20,   -20,   -20,   -25,   -25,
       0,   -25,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -25,   -25,   -25,   -25,   -25,   -25,   -25,   -25,
     -25,   -25,   -25,     0,     0,   -25,   -25,   -25,     0,     0,
     -25,   -25,   -25,   -25,     0,   -25,   -25,   -25,   -23,   -23,
       0,   -23,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -23,   -23,   -23,   -23,   -23,   -23,   -23,   -23,
     -23,   -23,   -23,     0,     0,   -23,   -23,   -23,     0,     0,
     -23,   -23,   -23,   -23,     0,   -23,   -23,   -23,   -26,   -26,
       0,   -26,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -26,   -26,   -26,   -26,   -26,   -26,   -26,   -26,
     787,   -26,   -26,     0,     0,   -26,   -26,   -26,     0,     0,
     -26,   -26,   -26,   -26,     0,   -26,   -26,   -26,   -10,   -10,
       0,   -10,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -10,   -10,   -10,   -10,   -10,   -10,   -10,   -10,
     788,   -10,   -10,     0,     0,   -10,   -10,   -10,     0,     0,
     -10,   -10,   -10,   -10,     0,   -10,   -10,   -10,   -12,   -12,
       0,   -12,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,
     -12,   -12,   -12,     0,     0,   -12,   -12,   -12,     0,     0,
     -12,   -12,   -12,   -12,     0,   -12,   -12,   -12,   -13,   -13,
       0,   -13,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -13,   -13,   -13,   -13,   -13,   -13,   -13,   -13,
     -13,   -13,   -13,     0,     0,   -13,   -13,   -13,     0,     0,
     -13,   -13,   -13,   -13,     0,   -13,   -13,   -13,   -35,   -35,
       0,   -35,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -35,   -35,   -35,   -35,   -35,   -35,   -35,   -35,
     -35,   -35,   -35,     0,     0,   -35,   -35,   -35,     0,     0,
     -35,   -35,   -35,   -35,     0,   -35,   -35,   -35,   -29,   -29,
       0,   -29,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -29,   -29,   -29,   -29,   -29,   -29,   -29,   -29,
     -29,   -29,   -29,     0,     0,   -29,   -29,   -29,     0,     0,
     -29,   -29,   -29,   -29,     0,   -29,   -29,   -29,   -31,   -31,
       0,   -31,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -31,   -31,   -31,   -31,   -31,   -31,   -31,   -31,
     -31,   -31,   -31,     0,     0,   -31,   -31,   -31,     0,     0,
     -31,   -31,   -31,   -31,     0,   -31,   -31,   -31,   -27,   -27,
       0,   -27,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -27,   -27,   -27,   -27,   -27,   -27,   -27,   -27,
     -27,   -27,   -27,     0,     0,   -27,   -27,   -27,     0,     0,
     -27,   -27,   -27,   -27,     0,   -27,   -27,   -27,   -11,   -11,
       0,   -11,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -11,   -11,   -11,   -11,   -11,   -11,   -11,   -11,
     -11,   -11,   -11,     0,     0,   -11,   -11,   -11,     0,     0,
     -11,   -11,   -11,   -11,     0,   -11,   -11,   -11,   -16,   -16,
       0,   -16,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -16,   -16,   -16,   -16,   -16,   -16,   -16,   -16,
     -16,   -16,   -16,     0,     0,   -16,   -16,   -16,     0,     0,
     -16,   -16,   -16,   -16,     0,   -16,   -16,   -16,   -43,   -43,
       0,   -43,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,
     -43,   -43,   -43,     0,     0,   -43,   -43,   -43,     0,     0,
     -43,   -43,   -43,   -43,     0,   -43,   -43,   -43,   -41,   -41,
       0,   -41,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,
     -41,   -41,   -41,     0,     0,   -41,   -41,   -41,     0,     0,
     -41,   -41,   -41,   -41,     0,   -41,   -41,   -41,   -45,   -45,
       0,   -45,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -45,   -45,   -45,   -45,   -45,   -45,   -45,   -45,
     -45,   -45,   -45,     0,     0,   -45,   -45,   -45,     0,     0,
     -45,   -45,   -45,   -45,     0,   -45,   -45,   -45,   -39,   -39,
       0,   -39,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -39,   -39,   -39,   -39,   -39,   -39,   -39,   -39,
     -39,   -39,   -39,     0,     0,   -39,   -39,   -39,     0,     0,
     -39,   -39,   -39,   -39,     0,   -39,   -39,   -39,     4,   261,
       0,     6,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     7,     8,     9,    10,   262,   263,   264,   265,
       0,   266,    16,     0,     0,    17,    18,    19,     0,     0,
      20,    21,    22,    23,     0,   267,   -19,    -4,   -42,   -42,
       0,   -42,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -42,   -42,   -42,   -42,   -42,   -42,   -42,   -42,
       0,   -42,   -42,     0,     0,   -42,   -42,   -42,     0,     0,
     -42,   -42,   -42,   -42,     0,   -42,   -42,   -42,   -40,   -40,
       0,   -40,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -40,   -40,   -40,   -40,   -40,   -40,   -40,   -40,
       0,   -40,   -40,     0,     0,   -40,   -40,   -40,     0,     0,
     -40,   -40,   -40,   -40,     0,   -40,   -40,   -40,   -44,   -44,
       0,   -44,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -44,   -44,   -44,   -44,   -44,   -44,   -44,   -44,
       0,   -44,   -44,     0,     0,   -44,   -44,   -44,     0,     0,
     -44,   -44,   -44,   -44,     0,   -44,   -44,   -44,   -21,   -21,
       0,   -21,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -21,   -21,   -21,   -21,   -21,   -21,   -21,   -21,
       0,   -21,   -21,     0,     0,   -21,   -21,   -21,     0,     0,
     -21,   -21,   -21,   -21,     0,   -21,   -21,   -21,    -5,    -5,
       0,    -5,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    -5,    -5,    -5,    -5,    -5,    -5,    -5,    -5,
       0,    -5,    -5,     0,     0,    -5,    -5,    -5,     0,     0,
      -5,    -5,    -5,    -5,     0,    -5,    -5,    -5,     4,   261,
       0,     6,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     7,     8,     9,    10,   262,   263,   264,   265,
       0,   266,    16,     0,     0,    17,    18,    19,     0,     0,
      20,    21,    22,    23,     0,   267,   -19,    -7,   -17,   -17,
       0,   -17,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -17,   -17,   -17,   -17,   -17,   -17,   -17,   -17,
       0,   -17,   -17,     0,     0,   -17,   -17,   -17,     0,     0,
     -17,   -17,   -17,   -17,     0,   -17,   -17,   -17,   -32,   -32,
       0,   -32,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -32,   -32,   -32,   -32,   -32,   -32,   -32,   -32,
       0,   -32,   -32,     0,     0,   -32,   -32,   -32,     0,     0,
     -32,   -32,   -32,   -32,     0,   -32,   -32,   -32,   -18,   -18,
       0,   -18,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -18,   -18,   -18,   -18,   -18,   -18,   -18,   -18,
       0,   -18,   -18,     0,     0,   -18,   -18,   -18,     0,     0,
     -18,   -18,   -18,   -18,     0,   -18,   -18,   -18,    -8,    -8,
       0,    -8,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    -8,    -8,    -8,    -8,    -8,    -8,    -8,    -8,
       0,    -8,    -8,     0,     0,    -8,    -8,    -8,     0,     0,
      -8,    -8,    -8,    -8,     0,    -8,    -8,    -8,   -20,   -20,
       0,   -20,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -20,   -20,   -20,   -20,   -20,   -20,   -20,   -20,
       0,   -20,   -20,     0,     0,   -20,   -20,   -20,     0,     0,
     -20,   -20,   -20,   -20,     0,   -20,   -20,   -20,   -25,   -25,
       0,   -25,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -25,   -25,   -25,   -25,   -25,   -25,   -25,   -25,
       0,   -25,   -25,     0,     0,   -25,   -25,   -25,     0,     0,
     -25,   -25,   -25,   -25,     0,   -25,   -25,   -25,   -23,   -23,
       0,   -23,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -23,   -23,   -23,   -23,   -23,   -23,   -23,   -23,
       0,   -23,   -23,     0,     0,   -23,   -23,   -23,     0,     0,
     -23,   -23,   -23,   -23,     0,   -23,   -23,   -23,   -12,   -12,
       0,   -12,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,
       0,   -12,   -12,     0,     0,   -12,   -12,   -12,     0,     0,
     -12,   -12,   -12,   -12,     0,   -12,   -12,   -12,   -13,   -13,
       0,   -13,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -13,   -13,   -13,   -13,   -13,   -13,   -13,   -13,
       0,   -13,   -13,     0,     0,   -13,   -13,   -13,     0,     0,
     -13,   -13,   -13,   -13,     0,   -13,   -13,   -13,   -35,   -35,
       0,   -35,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -35,   -35,   -35,   -35,   -35,   -35,   -35,   -35,
       0,   -35,   -35,     0,     0,   -35,   -35,   -35,     0,     0,
     -35,   -35,   -35,   -35,     0,   -35,   -35,   -35,   -29,   -29,
       0,   -29,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -29,   -29,   -29,   -29,   -29,   -29,   -29,   -29,
       0,   -29,   -29,     0,     0,   -29,   -29,   -29,     0,     0,
     -29,   -29,   -29,   -29,     0,   -29,   -29,   -29,   -31,   -31,
       0,   -31,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -31,   -31,   -31,   -31,   -31,   -31,   -31,   -31,
       0,   -31,   -31,     0,     0,   -31,   -31,   -31,     0,     0,
     -31,   -31,   -31,   -31,     0,   -31,   -31,   -31,   -27,   -27,
       0,   -27,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -27,   -27,   -27,   -27,   -27,   -27,   -27,   -27,
       0,   -27,   -27,     0,     0,   -27,   -27,   -27,     0,     0,
     -27,   -27,   -27,   -27,     0,   -27,   -27,   -27,   -11,   -11,
       0,   -11,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -11,   -11,   -11,   -11,   -11,   -11,   -11,   -11,
       0,   -11,   -11,     0,     0,   -11,   -11,   -11,     0,     0,
     -11,   -11,   -11,   -11,     0,   -11,   -11,   -11,   -16,   -16,
       0,   -16,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -16,   -16,   -16,   -16,   -16,   -16,   -16,   -16,
       0,   -16,   -16,     0,     0,   -16,   -16,   -16,     0,     0,
     -16,   -16,   -16,   -16,     0,   -16,   -16,   -16,   -43,   -43,
       0,   -43,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,
       0,   -43,   -43,     0,     0,   -43,   -43,   -43,     0,     0,
     -43,   -43,   -43,   -43,     0,   -43,   -43,   -43,   -41,   -41,
       0,   -41,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,
       0,   -41,   -41,     0,     0,   -41,   -41,   -41,     0,     0,
     -41,   -41,   -41,   -41,     0,   -41,   -41,   -41,   -45,   -45,
       0,   -45,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -45,   -45,   -45,   -45,   -45,   -45,   -45,   -45,
       0,   -45,   -45,     0,     0,   -45,   -45,   -45,     0,     0,
     -45,   -45,   -45,   -45,     0,   -45,   -45,   -45,   -39,   -39,
       0,   -39,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -39,   -39,   -39,   -39,   -39,   -39,   -39,   -39,
       0,   -39,   -39,     0,     0,   -39,   -39,   -39,     0,     0,
     -39,   -39,   -39,   -39,     0,   -39,   -39,   -39,     4,   329,
       0,     6,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     7,     8,     9,    10,   330,   331,   332,   333,
       0,   334,    16,     0,     0,    17,    18,    19,     0,     0,
      20,    21,    22,    23,     0,   335,   -19,   -28,   -28,     0,
     -28,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,     0,
     -28,   -28,     0,     0,   -28,   -28,   -28,     0,     0,   -28,
     -28,   -28,   -28,     0,   -28,   -28,     4,     5,     0,     6,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       7,     8,     9,    10,    11,    12,    13,    14,     0,    15,
      16,     0,     0,    17,    18,    19,     0,     0,    20,    21,
      22,    23,     0,    24,   -19,   -30,   -30,     0,   -30,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -30,
     -30,   -30,   -30,   -30,   -30,   -30,   -30,     0,   -30,   -30,
       0,     0,   -30,   -30,   -30,     0,     0,   -30,   -30,   -30,
     -30,     0,   -30,   -30,   -15,   -15,     0,   -15,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -15,   -15,
     -15,   -15,   -15,   -15,   -15,   -15,     0,   -15,   -15,     0,
       0,   -15,   -15,   -15,     0,     0,   -15,   -15,   -15,   -15,
       0,   -15,   -15,     4,   646,     0,     6,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     7,     8,     9,
      10,   647,   648,   649,   650,     0,   651,    16,     0,     0,
      17,    18,    19,     0,     0,    20,    21,    22,    23,     0,
     652,   -19,     4,   261,     0,     6,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     7,     8,     9,    10,
     262,   263,   264,   265,     0,   266,    16,     0,     0,    17,
      18,    19,     0,     0,    20,    21,    22,    23,     0,   267,
     -19,   510,     0,  -103,  -103,  -103,  -103,  -103,  -103,  -103,
    -103,  -103,   511,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -103,     0,  -103,  -103,  -103,  -103,
    -103,     0,     4,   134,  -101,     6,  -103,     0,     0,  -103,
       0,     0,     0,     0,     0,     0,     7,     8,     9,    10,
       0,     0,     0,     0,     0,     0,    16,     0,     0,    17,
      18,    19,     0,     0,    20,    21,    22,    23,    68,   135,
       4,     0,     0,     6,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     7,     8,     9,    10,     0,     0,
      78,     0,   232,     0,    16,   233,     0,    17,    18,    19,
       0,     0,    20,    21,    22,    23,   234,   235,   236,   237,
       0,     0,    80,     0,   232,     0,   238,   233,     0,   239,
     240,   241,     0,     0,   242,   243,   244,   245,   234,   235,
     236,   237,     0,     0,    82,     0,   232,     0,   238,   233,
       0,   239,   240,   241,     0,     0,   242,   243,   244,   245,
     234,   235,   236,   237,     0,     0,    92,     0,     4,     0,
     238,     6,     0,   239,   240,   241,     0,     0,   242,   243,
     244,   245,     7,     8,     9,    10,     0,     0,    94,     0,
       4,     0,    16,     6,     0,    17,    18,    19,     0,     0,
      20,    21,    22,    23,     7,     8,     9,    10,     0,     0,
      96,     0,     4,     0,    16,     6,     0,    17,    18,    19,
       0,     0,    20,    21,    22,    23,     7,     8,     9,    10,
       0,     0,    98,     0,     4,     0,    16,     6,     0,    17,
      18,    19,     0,     0,    20,    21,    22,    23,     7,     8,
       9,    10,     0,     0,   100,     0,     4,     0,    16,     6,
       0,    17,    18,    19,     0,     0,    20,    21,    22,    23,
       7,     8,     9,    10,     0,     0,   102,     0,     4,     0,
      16,     6,     0,    17,    18,    19,     0,     0,    20,    21,
      22,    23,     7,     8,     9,    10,     0,     0,   104,     0,
       4,     0,    16,     6,     0,    17,    18,    19,     0,     0,
      20,    21,    22,    23,     7,     8,     9,    10,     0,     0,
     108,     0,     4,     0,    16,     6,     0,    17,    18,    19,
       0,     0,    20,    21,    22,    23,     7,     8,     9,    10,
       0,     0,   110,     0,     4,     0,    16,     6,     0,    17,
      18,    19,     0,     0,    20,    21,    22,    23,     7,     8,
       9,    10,     0,     0,   112,     0,     4,     0,    16,     6,
       0,    17,    18,    19,     0,     0,    20,    21,    22,    23,
       7,     8,     9,    10,     0,     0,   114,     0,     4,     0,
      16,     6,     0,    17,    18,    19,     0,     0,    20,    21,
      22,    23,     7,     8,     9,    10,     0,     0,   116,     0,
       4,     0,    16,     6,     0,    17,    18,    19,     0,     0,
      20,    21,    22,    23,     7,     8,     9,    10,     0,     0,
       0,     0,     4,     0,    16,     6,     0,    17,    18,    19,
       0,     0,    20,    21,    22,    23,     7,     8,     9,    10,
       0,     0,     0,     0,     0,     0,    16,     0,     0,    17,
      18,    19,     0,     0,    20,    21,    22,    23,   382,   -67,
     232,     0,     0,   233,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   234,   235,   236,   237,     0,     0,
     384,     0,   232,     0,   238,   233,     0,   239,   240,   241,
       0,     0,   242,   243,   244,   245,   234,   235,   236,   237,
       0,     0,   386,     0,   232,     0,   238,   233,     0,   239,
     240,   241,     0,     0,   242,   243,   244,   245,   234,   235,
     236,   237,     0,     0,   388,     0,   232,     0,   238,   233,
       0,   239,   240,   241,     0,     0,   242,   243,   244,   245,
     234,   235,   236,   237,     0,     0,   390,     0,   232,     0,
     238,   233,     0,   239,   240,   241,     0,     0,   242,   243,
     244,   245,   234,   235,   236,   237,     0,     0,   392,     0,
     232,     0,   238,   233,     0,   239,   240,   241,     0,     0,
     242,   243,   244,   245,   234,   235,   236,   237,     0,     0,
     394,     0,   232,     0,   238,   233,     0,   239,   240,   241,
       0,     0,   242,   243,   244,   245,   234,   235,   236,   237,
       0,     0,   398,     0,   232,     0,   238,   233,     0,   239,
     240,   241,     0,     0,   242,   243,   244,   245,   234,   235,
     236,   237,     0,     0,   400,     0,   232,     0,   238,   233,
       0,   239,   240,   241,     0,     0,   242,   243,   244,   245,
     234,   235,   236,   237,     0,     0,   402,     0,   232,     0,
     238,   233,     0,   239,   240,   241,     0,     0,   242,   243,
     244,   245,   234,   235,   236,   237,     0,     0,   404,     0,
     232,     0,   238,   233,     0,   239,   240,   241,     0,     0,
     242,   243,   244,   245,   234,   235,   236,   237,     0,     0,
     406,     0,   232,     0,   238,   233,     0,   239,   240,   241,
       0,     0,   242,   243,   244,   245,   234,   235,   236,   237,
       0,     0,   415,     0,     4,     0,   238,     6,     0,   239,
     240,   241,     0,     0,   242,   243,   244,   245,     7,     8,
       9,    10,     0,     0,   443,     0,   271,     0,    16,   272,
       0,    17,    18,    19,     0,     0,    20,    21,    22,    23,
     273,   274,   275,   276,     0,     0,   445,     0,   271,     0,
     277,   272,     0,   278,   279,   280,     0,     0,   281,   282,
     283,   284,   273,   274,   275,   276,     0,     0,   447,     0,
     271,     0,   277,   272,     0,   278,   279,   280,     0,     0,
     281,   282,   283,   284,   273,   274,   275,   276,     0,     0,
     449,     0,   271,     0,   277,   272,     0,   278,   279,   280,
       0,     0,   281,   282,   283,   284,   273,   274,   275,   276,
       0,     0,   451,     0,   271,     0,   277,   272,     0,   278,
     279,   280,     0,     0,   281,   282,   283,   284,   273,   274,
     275,   276,     0,     0,   453,     0,   271,     0,   277,   272,
       0,   278,   279,   280,     0,     0,   281,   282,   283,   284,
     273,   274,   275,   276,     0,     0,   455,     0,   271,     0,
     277,   272,     0,   278,   279,   280,     0,     0,   281,   282,
     283,   284,   273,   274,   275,   276,     0,     0,   459,     0,
     271,     0,   277,   272,     0,   278,   279,   280,     0,     0,
     281,   282,   283,   284,   273,   274,   275,   276,     0,     0,
     461,     0,   271,     0,   277,   272,     0,   278,   279,   280,
       0,     0,   281,   282,   283,   284,   273,   274,   275,   276,
       0,     0,   463,     0,   271,     0,   277,   272,     0,   278,
     279,   280,     0,     0,   281,   282,   283,   284,   273,   274,
     275,   276,     0,     0,   465,     0,   271,     0,   277,   272,
       0,   278,   279,   280,     0,     0,   281,   282,   283,   284,
     273,   274,   275,   276,     0,     0,   467,     0,   271,     0,
     277,   272,     0,   278,   279,   280,     0,     0,   281,   282,
     283,   284,   273,   274,   275,   276,     0,     0,   470,     0,
     285,     0,   277,   286,     0,   278,   279,   280,     0,     0,
     281,   282,   283,   284,   287,   288,   289,   290,     0,     0,
     472,     0,   285,     0,   291,   286,     0,   292,   293,   294,
       0,     0,   295,   296,   297,   298,   287,   288,   289,   290,
       0,     0,   474,     0,   285,     0,   291,   286,     0,   292,
     293,   294,     0,     0,   295,   296,   297,   298,   287,   288,
     289,   290,     0,     0,   476,     0,   285,     0,   291,   286,
       0,   292,   293,   294,     0,     0,   295,   296,   297,   298,
     287,   288,   289,   290,     0,     0,   478,     0,   285,     0,
     291,   286,     0,   292,   293,   294,     0,     0,   295,   296,
     297,   298,   287,   288,   289,   290,     0,     0,   480,     0,
     285,     0,   291,   286,     0,   292,   293,   294,     0,     0,
     295,   296,   297,   298,   287,   288,   289,   290,     0,     0,
     482,     0,   285,     0,   291,   286,     0,   292,   293,   294,
       0,     0,   295,   296,   297,   298,   287,   288,   289,   290,
       0,     0,   486,     0,   285,     0,   291,   286,     0,   292,
     293,   294,     0,     0,   295,   296,   297,   298,   287,   288,
     289,   290,     0,     0,   488,     0,   285,     0,   291,   286,
       0,   292,   293,   294,     0,     0,   295,   296,   297,   298,
     287,   288,   289,   290,     0,     0,   490,     0,   285,     0,
     291,   286,     0,   292,   293,   294,     0,     0,   295,   296,
     297,   298,   287,   288,   289,   290,     0,     0,   492,     0,
     285,     0,   291,   286,     0,   292,   293,   294,     0,     0,
     295,   296,   297,   298,   287,   288,   289,   290,     0,     0,
     494,     0,   285,     0,   291,   286,     0,   292,   293,   294,
       0,     0,   295,   296,   297,   298,   287,   288,   289,   290,
       0,     0,   503,     0,     4,     0,   291,     6,     0,   292,
     293,   294,     0,     0,   295,   296,   297,   298,     7,     8,
       9,    10,     0,     0,   522,     0,   341,     0,    16,   342,
       0,    17,    18,    19,     0,     0,    20,    21,    22,    23,
     343,   344,   345,   346,     0,     0,   524,     0,   341,     0,
     347,   342,     0,   348,   349,   350,     0,     0,   351,   352,
     353,   354,   343,   344,   345,   346,     0,     0,   526,     0,
     341,     0,   347,   342,     0,   348,   349,   350,     0,     0,
     351,   352,   353,   354,   343,   344,   345,   346,     0,     0,
     528,     0,   341,     0,   347,   342,     0,   348,   349,   350,
       0,     0,   351,   352,   353,   354,   343,   344,   345,   346,
       0,     0,   530,     0,   341,     0,   347,   342,     0,   348,
     349,   350,     0,     0,   351,   352,   353,   354,   343,   344,
     345,   346,     0,     0,   532,     0,   341,     0,   347,   342,
       0,   348,   349,   350,     0,     0,   351,   352,   353,   354,
     343,   344,   345,   346,     0,     0,   534,     0,   341,     0,
     347,   342,     0,   348,   349,   350,     0,     0,   351,   352,
     353,   354,   343,   344,   345,   346,     0,     0,   538,     0,
     341,     0,   347,   342,     0,   348,   349,   350,     0,     0,
     351,   352,   353,   354,   343,   344,   345,   346,     0,     0,
     540,     0,   341,     0,   347,   342,     0,   348,   349,   350,
       0,     0,   351,   352,   353,   354,   343,   344,   345,   346,
       0,     0,   542,     0,   341,     0,   347,   342,     0,   348,
     349,   350,     0,     0,   351,   352,   353,   354,   343,   344,
     345,   346,     0,     0,   544,     0,   341,     0,   347,   342,
       0,   348,   349,   350,     0,     0,   351,   352,   353,   354,
     343,   344,   345,   346,     0,     0,   546,     0,   341,     0,
     347,   342,     0,   348,   349,   350,     0,     0,   351,   352,
     353,   354,   343,   344,   345,   346,     0,     0,   548,     0,
     232,     0,   347,   233,     0,   348,   349,   350,     0,     0,
     351,   352,   353,   354,   234,   235,   236,   237,     0,     0,
     558,     0,   232,     0,   238,   233,     0,   239,   240,   241,
       0,     0,   242,   243,   244,   245,   234,   235,   236,   237,
       0,     0,   560,     0,   232,     0,   238,   233,     0,   239,
     240,   241,     0,     0,   242,   243,   244,   245,   234,   235,
     236,   237,     0,     0,   562,     0,   232,     0,   238,   233,
       0,   239,   240,   241,     0,     0,   242,   243,   244,   245,
     234,   235,   236,   237,     0,     0,   570,     0,   271,     0,
     238,   272,     0,   239,   240,   241,     0,     0,   242,   243,
     244,   245,   273,   274,   275,   276,     0,     0,   575,     0,
     285,     0,   277,   286,     0,   278,   279,   280,     0,     0,
     281,   282,   283,   284,   287,   288,   289,   290,     0,     0,
     586,     0,   232,     0,   291,   233,     0,   292,   293,   294,
       0,     0,   295,   296,   297,   298,   234,   235,   236,   237,
       0,     0,   588,     0,   232,     0,   238,   233,     0,   239,
     240,   241,     0,     0,   242,   243,   244,   245,   234,   235,
     236,   237,     0,     0,   590,     0,   232,     0,   238,   233,
       0,   239,   240,   241,     0,     0,   242,   243,   244,   245,
     234,   235,   236,   237,     0,     0,   598,     0,   341,     0,
     238,   342,     0,   239,   240,   241,     0,     0,   242,   243,
     244,   245,   343,   344,   345,   346,     0,     0,   693,     0,
       4,     0,   347,     6,     0,   348,   349,   350,     0,     0,
     351,   352,   353,   354,     7,     8,     9,    10,     0,     0,
     719,     0,   232,     0,    16,   233,     0,    17,    18,    19,
       0,     0,    20,    21,    22,    23,   234,   235,   236,   237,
       0,     0,   721,     0,   232,     0,   238,   233,     0,   239,
     240,   241,     0,     0,   242,   243,   244,   245,   234,   235,
     236,   237,     0,     0,   723,     0,   232,     0,   238,   233,
       0,   239,   240,   241,     0,     0,   242,   243,   244,   245,
     234,   235,   236,   237,     0,     0,     0,     0,     0,     0,
     238,     0,     0,   239,   240,   241,     0,     0,   242,   243,
     244,   245,   355,   356,   357,   358,   359,   360,   361,   362,
     363,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   364,     0,   365,   366,   367,   368,   369,
       0,     0,     0,     0,     0,   -55,     0,     0,   -55,   355,
     356,   357,   358,   359,   360,   361,   362,   363,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     364,     0,   365,   366,   367,   368,   369,     0,     0,     0,
       0,     0,   -64,     0,     0,   216,   -76,   -76,   -76,   -76,
     -76,   -76,   -76,   -76,   -76,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -76,     0,   -76,
     -76,   -76,   -76,   -76,     0,     0,     0,     0,     0,   -76,
       0,     0,   -76,   -77,   -77,   -77,   -77,   -77,   -77,   -77,
     -77,   -77,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -77,     0,   -77,   -77,   -77,   -77,
     -77,     0,     0,     0,     0,     0,   -77,     0,     0,   -77,
     -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -73,     0,   -73,   -73,   -73,   -73,   -73,     0,     0,
       0,     0,     0,   -73,     0,     0,   -73,   -74,   -74,   -74,
     -74,   -74,   -74,   -74,   -74,   -74,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -74,     0,
     -74,   -74,   -74,   -74,   -74,     0,     0,     0,     0,     0,
     -74,     0,     0,   -74,   -75,   -75,   -75,   -75,   -75,   -75,
     -75,   -75,   -75,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -75,     0,   -75,   -75,   -75,
     -75,   -75,     0,     0,     0,     0,     0,   -75,     0,     0,
     -75,   -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -78,     0,   -78,   -78,   -78,   -78,   -78,     0,
       0,     0,     0,     0,   -78,     0,     0,   -78,   -85,   -85,
     -85,   -85,   -85,   -85,   -85,   -85,   -85,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -85,
       0,   -85,   -85,   -85,   -85,   -85,     0,     0,     0,     0,
       0,   -85,     0,     0,   -85,   -80,   -80,   -80,   -80,   -80,
     -80,   -80,   -80,   -80,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -80,     0,   -80,   -80,
     -80,   -80,   -80,     0,     0,     0,     0,     0,   -80,     0,
       0,   -80,   -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,
     -81,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -81,     0,   -81,   -81,   -81,   -81,   -81,
       0,     0,     0,     0,     0,   -81,     0,     0,   -81,   -79,
     -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -79,     0,   -79,   -79,   -79,   -79,   -79,     0,     0,     0,
       0,     0,   -79,     0,     0,   -79,   -82,   -82,   -82,   -82,
     -82,   -82,   -82,   -82,   -82,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -82,     0,   -82,
     -82,   -82,   -82,   -82,     0,     0,     0,     0,     0,   -82,
       0,     0,   -82,   -83,   -83,   -83,   -83,   -83,   -83,   -83,
     -83,   -83,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -83,     0,   -83,   -83,   -83,   -83,
     -83,     0,     0,     0,     0,     0,   -83,     0,     0,   -83,
     -84,   -84,   -84,   -84,   -84,   -84,   -84,   -84,   -84,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -84,     0,   -84,   -84,   -84,   -84,   -84,     0,     0,
       0,     0,     0,   -84,     0,     0,   -84,   -91,   -91,   -91,
     -91,   -91,   -91,   -91,   -91,   -91,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -91,     0,
     -91,   -91,   -91,   -91,   -91,     0,     0,     0,     0,     0,
     -91,     0,     0,   -91,  -110,  -110,  -110,  -110,  -110,  -110,
    -110,  -110,  -110,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -110,     0,  -110,  -110,  -110,
    -110,  -110,     0,     0,     0,     0,     0,  -110,     0,     0,
    -110,   355,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -92,     0,   365,   366,   367,   368,   369,     0,
       0,     0,     0,     0,   -92,     0,     0,   -92,  -111,  -111,
    -111,  -111,  -111,  -111,  -111,  -111,  -111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -111,
       0,  -111,  -111,  -111,  -111,  -111,     0,     0,     0,     0,
       0,  -111,     0,     0,  -111,   355,   356,   -93,   -93,   -93,
     -93,   -93,   -93,   -93,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -93,     0,   365,   366,
     367,   368,   369,     0,     0,     0,     0,     0,   -93,     0,
       0,   -93,  -112,  -112,  -112,  -112,  -112,  -112,  -112,  -112,
    -112,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -112,     0,  -112,  -112,  -112,  -112,  -112,
       0,     0,     0,     0,     0,  -112,     0,     0,  -112,   355,
     356,   357,   -94,   -94,   -94,   -94,   -94,   -94,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -94,     0,   365,   366,   367,   368,   369,     0,     0,     0,
       0,     0,   -94,     0,     0,   -94,  -113,  -113,  -113,  -113,
    -113,  -113,  -113,  -113,  -113,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -113,     0,  -113,
    -113,  -113,  -113,  -113,     0,     0,     0,     0,     0,  -113,
       0,     0,  -113,   355,   356,   357,   358,   -95,   -95,   -95,
     -95,   -95,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -95,     0,   365,   366,   367,   368,
     369,     0,     0,     0,     0,     0,   -95,     0,     0,   -95,
    -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -114,     0,  -114,  -114,  -114,  -114,  -114,     0,     0,
       0,     0,     0,  -114,     0,     0,  -114,   355,   356,   357,
     358,   359,   -96,   -96,   -96,   -96,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -96,     0,
     365,   366,   367,   368,   369,     0,     0,     0,     0,     0,
     -96,     0,     0,   -96,  -115,  -115,  -115,  -115,  -115,  -115,
    -115,  -115,  -115,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -115,     0,  -115,  -115,  -115,
    -115,  -115,     0,     0,     0,     0,     0,  -115,     0,     0,
    -115,   355,   356,   357,   358,   359,   360,   -97,   -97,   -97,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -97,     0,   365,   366,   367,   368,   369,     0,
       0,     0,     0,     0,   -97,     0,     0,   -97,  -116,  -116,
    -116,  -116,  -116,  -116,  -116,  -116,  -116,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -116,
       0,  -116,  -116,  -116,  -116,  -116,     0,     0,     0,     0,
       0,  -116,     0,     0,  -116,   355,   356,   357,   358,   359,
     360,   361,   -98,   -98,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -98,     0,   365,   366,
     367,   368,   369,     0,     0,     0,     0,     0,   -98,     0,
       0,   -98,  -117,  -117,  -117,  -117,  -117,  -117,  -117,  -117,
    -117,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -117,     0,  -117,  -117,  -117,  -117,  -117,
       0,     0,     0,     0,     0,  -117,     0,     0,  -117,  -108,
    -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -108,     0,  -108,  -108,  -108,  -108,  -108,     0,     0,     0,
       0,     0,  -108,     0,     0,  -108,   355,   -89,   -89,   -89,
     -89,   -89,   -89,   -89,   -89,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -89,     0,   -89,
     -89,   367,   368,   369,     0,     0,     0,     0,     0,   -89,
       0,     0,   -89,  -109,  -109,  -109,  -109,  -109,  -109,  -109,
    -109,  -109,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -109,     0,  -109,  -109,  -109,  -109,
    -109,     0,     0,     0,     0,     0,  -109,     0,     0,  -109,
     355,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -90,     0,   -90,   -90,   367,   368,   369,     0,     0,
       0,     0,     0,   -90,     0,     0,   -90,  -105,  -105,  -105,
    -105,  -105,  -105,  -105,  -105,  -105,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -105,     0,
    -105,  -105,  -105,  -105,  -105,     0,     0,     0,     0,     0,
    -105,     0,     0,  -105,   355,   -86,   -86,   -86,   -86,   -86,
     -86,   -86,   -86,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -86,     0,   -86,   -86,   -86,
     -86,   -86,     0,     0,     0,     0,     0,   -86,     0,     0,
     -86,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -106,     0,  -106,  -106,  -106,  -106,  -106,     0,
       0,     0,     0,     0,  -106,     0,     0,  -106,   355,   -87,
     -87,   -87,   -87,   -87,   -87,   -87,   -87,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -87,
       0,   -87,   -87,   -87,   -87,   -87,     0,     0,     0,     0,
       0,   -87,     0,     0,   -87,  -107,  -107,  -107,  -107,  -107,
    -107,  -107,  -107,  -107,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -107,     0,  -107,  -107,
    -107,  -107,  -107,     0,     0,     0,     0,     0,  -107,     0,
       0,  -107,   355,   -88,   -88,   -88,   -88,   -88,   -88,   -88,
     -88,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -88,     0,   -88,   -88,   -88,   -88,   -88,
       0,     0,     0,     0,     0,   -88,     0,     0,   -88,  -118,
    -118,  -118,  -118,  -118,  -118,  -118,  -118,  -118,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -118,     0,  -118,  -118,  -118,  -118,  -118,     0,     0,     0,
       0,     0,  -118,     0,     0,  -118,   355,   356,   357,   358,
     359,   360,   361,   362,   363,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   364,     0,   365,
     366,   367,   368,   369,     0,     0,     0,     0,     0,  -100,
       0,     0,  -100,  -102,  -102,  -102,  -102,  -102,  -102,  -102,
    -102,  -102,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -102,     0,  -102,  -102,  -102,  -102,
    -102,     0,     0,     0,     0,     0,  -102,     0,     0,  -102,
    -104,  -104,  -104,  -104,  -104,  -104,  -104,  -104,  -104,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -104,     0,  -104,  -104,  -104,  -104,  -104,     0,     0,
       0,     0,     0,  -104,     0,     0,  -104,   355,   356,   357,
     358,   359,   360,   361,   362,   363,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   364,     0,
     365,   366,   367,   368,   369,     0,     0,     0,     0,     0,
     -99,     0,     0,   -99,  -120,  -120,  -120,  -120,  -120,  -120,
    -120,  -120,  -120,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -120,     0,  -120,  -120,  -120,
    -120,  -120,     0,     0,     0,     0,     0,  -120,     0,     0,
    -120,  -119,  -119,  -119,  -119,  -119,  -119,  -119,  -119,  -119,
       0,     0,     0,     0,     0,   232,     0,     0,   233,     0,
       0,     0,  -119,     0,  -119,  -119,  -119,  -119,  -119,   234,
     235,   236,   237,     0,  -119,     0,     0,  -119,     0,   238,
       0,     0,   239,   240,   241,     0,     0,   242,   243,   244,
     245,   -67,    29,     0,  -103,  -103,  -103,  -103,  -103,  -103,
    -103,  -103,  -103,    30,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -103,     0,  -103,  -103,  -103,
    -103,  -103,     0,     4,     0,  -101,     6,  -103,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     7,     8,     9,
      10,     0,     0,     0,     0,   232,     0,    16,   233,     0,
      17,    18,    19,     0,     0,    20,    21,    22,    23,   234,
     235,   236,   237,     0,     0,     0,     0,   271,     0,   238,
     272,     0,   239,   240,   241,     0,     0,   242,   243,   244,
     245,   273,   274,   275,   276,     0,     0,     0,     0,   285,
       0,   277,   286,     0,   278,   279,   280,     0,     0,   281,
     282,   283,   284,   287,   288,   289,   290,     0,     0,     0,
       0,   341,     0,   291,   342,     0,   292,   293,   294,     0,
       0,   295,   296,   297,   298,   343,   344,   345,   346,     0,
       0,     0,     0,     0,     0,   347,     0,     0,   348,   349,
     350,     0,     0,   351,   352,   353,   354,   370,     0,  -103,
    -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,   371,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -103,     0,  -103,  -103,  -103,  -103,  -103,     0,     0,     0,
    -101,  -103,   420,     0,  -103,  -103,  -103,  -103,  -103,  -103,
    -103,  -103,  -103,   421,     0,   -76,   -76,   -76,   -76,   -76,
     -76,   -76,   -76,   -76,     0,  -103,  -103,  -103,  -103,  -103,
    -103,  -103,     0,     0,     0,  -101,   -76,     0,   -76,   -76,
     -76,   -76,   -76,     0,     0,     0,     0,     0,   -76,   -77,
     -77,   -77,   -77,   -77,   -77,   -77,   -77,   -77,     0,     0,
     -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,     0,
     -77,     0,   -77,   -77,   -77,   -77,   -77,     0,     0,     0,
       0,   -73,   -77,   -73,   -73,   -73,   -73,   -73,     0,     0,
       0,     0,     0,   -73,   -74,   -74,   -74,   -74,   -74,   -74,
     -74,   -74,   -74,     0,     0,   -75,   -75,   -75,   -75,   -75,
     -75,   -75,   -75,   -75,     0,   -74,     0,   -74,   -74,   -74,
     -74,   -74,     0,     0,     0,     0,   -75,   -74,   -75,   -75,
     -75,   -75,   -75,     0,     0,     0,     0,     0,   -75,    52,
      53,    54,    55,    56,    57,    58,    59,    60,     0,     0,
     -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,     0,
      61,     0,    62,    63,    64,    65,    66,     0,     0,     0,
       0,   -78,    67,   -78,   -78,   -78,   -78,   -78,     0,     0,
       0,     0,     0,   -78,   -85,   -85,   -85,   -85,   -85,   -85,
     -85,   -85,   -85,     0,     0,    52,    53,    54,    55,    56,
      57,    58,    59,    60,     0,   -85,     0,   -85,   -85,   -85,
     -85,   -85,     0,     0,     0,     0,    61,   -85,    62,    63,
      64,    65,    66,     0,     0,     0,     0,     0,    86,   -80,
     -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,     0,     0,
     -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,     0,
     -80,     0,   -80,   -80,   -80,   -80,   -80,     0,     0,     0,
       0,   -81,   -80,   -81,   -81,   -81,   -81,   -81,     0,     0,
       0,     0,     0,   -81,   -79,   -79,   -79,   -79,   -79,   -79,
     -79,   -79,   -79,     0,     0,   -82,   -82,   -82,   -82,   -82,
     -82,   -82,   -82,   -82,     0,   -79,     0,   -79,   -79,   -79,
     -79,   -79,     0,     0,     0,     0,   -82,   -79,   -82,   -82,
     -82,   -82,   -82,     0,     0,     0,     0,     0,   -82,   -83,
     -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,     0,     0,
     -84,   -84,   -84,   -84,   -84,   -84,   -84,   -84,   -84,     0,
     -83,     0,   -83,   -83,   -83,   -83,   -83,     0,     0,     0,
       0,   -84,   -83,   -84,   -84,   -84,   -84,   -84,     0,     0,
       0,     0,     0,   -84,  -118,  -118,  -118,  -118,  -118,  -118,
    -118,  -118,  -118,     0,     0,    52,    53,    54,    55,    56,
      57,    58,    59,    60,     0,  -118,     0,  -118,  -118,  -118,
    -118,  -118,     0,     0,     0,     0,    61,  -118,    62,    63,
      64,    65,    66,     0,     0,     0,     0,     0,  -100,  -102,
    -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,     0,     0,
    -104,  -104,  -104,  -104,  -104,  -104,  -104,  -104,  -104,     0,
    -102,     0,  -102,  -102,  -102,  -102,  -102,     0,     0,     0,
       0,  -104,  -102,  -104,  -104,  -104,  -104,  -104,     0,     0,
       0,     0,     0,  -104,   -91,   -91,   -91,   -91,   -91,   -91,
     -91,   -91,   -91,     0,     0,  -110,  -110,  -110,  -110,  -110,
    -110,  -110,  -110,  -110,     0,   -91,     0,   -91,   -91,   -91,
     -91,   -91,     0,     0,     0,     0,  -110,   -91,  -110,  -110,
    -110,  -110,  -110,     0,     0,     0,     0,     0,  -110,    52,
     -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,     0,     0,
    -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,     0,
     -92,     0,    62,    63,    64,    65,    66,     0,     0,     0,
       0,  -111,   -92,  -111,  -111,  -111,  -111,  -111,     0,     0,
       0,     0,     0,  -111,    52,    53,   -93,   -93,   -93,   -93,
     -93,   -93,   -93,     0,     0,  -112,  -112,  -112,  -112,  -112,
    -112,  -112,  -112,  -112,     0,   -93,     0,    62,    63,    64,
      65,    66,     0,     0,     0,     0,  -112,   -93,  -112,  -112,
    -112,  -112,  -112,     0,     0,     0,     0,     0,  -112,    52,
      53,    54,   -94,   -94,   -94,   -94,   -94,   -94,     0,     0,
    -113,  -113,  -113,  -113,  -113,  -113,  -113,  -113,  -113,     0,
     -94,     0,    62,    63,    64,    65,    66,     0,     0,     0,
       0,  -113,   -94,  -113,  -113,  -113,  -113,  -113,     0,     0,
       0,     0,     0,  -113,    52,    53,    54,    55,   -95,   -95,
     -95,   -95,   -95,     0,     0,  -114,  -114,  -114,  -114,  -114,
    -114,  -114,  -114,  -114,     0,   -95,     0,    62,    63,    64,
      65,    66,     0,     0,     0,     0,  -114,   -95,  -114,  -114,
    -114,  -114,  -114,     0,     0,     0,     0,     0,  -114,    52,
      53,    54,    55,    56,   -96,   -96,   -96,   -96,     0,     0,
    -115,  -115,  -115,  -115,  -115,  -115,  -115,  -115,  -115,     0,
     -96,     0,    62,    63,    64,    65,    66,     0,     0,     0,
       0,  -115,   -96,  -115,  -115,  -115,  -115,  -115,     0,     0,
       0,     0,     0,  -115,    52,    53,    54,    55,    56,    57,
     -97,   -97,   -97,     0,     0,  -116,  -116,  -116,  -116,  -116,
    -116,  -116,  -116,  -116,     0,   -97,     0,    62,    63,    64,
      65,    66,     0,     0,     0,     0,  -116,   -97,  -116,  -116,
    -116,  -116,  -116,     0,     0,     0,     0,     0,  -116,    52,
      53,    54,    55,    56,    57,    58,   -98,   -98,     0,     0,
    -117,  -117,  -117,  -117,  -117,  -117,  -117,  -117,  -117,     0,
     -98,     0,    62,    63,    64,    65,    66,     0,     0,     0,
       0,  -117,   -98,  -117,  -117,  -117,  -117,  -117,     0,     0,
       0,     0,     0,  -117,  -108,  -108,  -108,  -108,  -108,  -108,
    -108,  -108,  -108,     0,     0,    52,   -89,   -89,   -89,   -89,
     -89,   -89,   -89,   -89,     0,  -108,     0,  -108,  -108,  -108,
    -108,  -108,     0,     0,     0,     0,   -89,  -108,   -89,   -89,
      64,    65,    66,     0,     0,     0,     0,     0,   -89,  -109,
    -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,     0,     0,
      52,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,     0,
    -109,     0,  -109,  -109,  -109,  -109,  -109,     0,     0,     0,
       0,   -90,  -109,   -90,   -90,    64,    65,    66,     0,     0,
       0,     0,     0,   -90,  -105,  -105,  -105,  -105,  -105,  -105,
    -105,  -105,  -105,     0,     0,    52,   -86,   -86,   -86,   -86,
     -86,   -86,   -86,   -86,     0,  -105,     0,  -105,  -105,  -105,
    -105,  -105,     0,     0,     0,     0,   -86,  -105,   -86,   -86,
     -86,   -86,   -86,     0,     0,     0,     0,     0,   -86,  -106,
    -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,     0,     0,
      52,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,     0,
    -106,     0,  -106,  -106,  -106,  -106,  -106,     0,     0,     0,
       0,   -87,  -106,   -87,   -87,   -87,   -87,   -87,     0,     0,
       0,     0,     0,   -87,  -107,  -107,  -107,  -107,  -107,  -107,
    -107,  -107,  -107,     0,     0,    52,   -88,   -88,   -88,   -88,
     -88,   -88,   -88,   -88,     0,  -107,     0,  -107,  -107,  -107,
    -107,  -107,     0,     0,     0,     0,   -88,  -107,   -88,   -88,
     -88,   -88,   -88,     0,     0,     0,     0,     0,   -88,    52,
      53,    54,    55,    56,    57,    58,    59,    60,     0,     0,
    -120,  -120,  -120,  -120,  -120,  -120,  -120,  -120,  -120,     0,
      61,     0,    62,    63,    64,    65,    66,     0,     0,     0,
       0,  -120,   -61,  -120,  -120,  -120,  -120,  -120,     0,     0,
       0,     0,     0,  -120,  -119,  -119,  -119,  -119,  -119,  -119,
    -119,  -119,  -119,     0,     0,    52,    53,    54,    55,    56,
      57,    58,    59,    60,     0,  -119,     0,  -119,  -119,  -119,
    -119,  -119,     0,     0,     0,     0,    61,  -119,    62,    63,
      64,    65,    66,     0,     0,     0,     0,     0,   -66,    52,
      53,    54,    55,    56,    57,    58,    59,    60,     0,     0,
      52,    53,    54,    55,    56,    57,    58,    59,    60,     0,
      61,     0,    62,    63,    64,    65,    66,     0,     0,     0,
       0,    61,   -99,    62,    63,    64,    65,    66,     0,     0,
       0,     0,     0,   419,    52,    53,    54,    55,    56,    57,
      58,    59,    60,     0,     0,    52,    53,    54,    55,    56,
      57,    58,    59,    60,     0,    61,     0,    62,    63,    64,
      65,    66,     0,     0,     0,     0,    61,   506,    62,    63,
      64,    65,    66,     0,     0,     0,     0,     0,   566,    52,
      53,    54,    55,    56,    57,    58,    59,    60,     0,     0,
      52,    53,    54,    55,    56,    57,    58,    59,    60,     0,
      61,     0,    62,    63,    64,    65,    66,     0,     0,     0,
       0,    61,   594,    62,    63,    64,    65,    66,     0,     0,
       0,     0,     0,   697,    52,    53,    54,    55,    56,    57,
      58,    59,    60,     0,     0,   246,   247,   248,   249,   250,
     251,   252,   253,   254,     0,    61,     0,    62,    63,    64,
      65,    66,     0,     0,     0,     0,   255,   727,   256,   257,
     258,   259,   260,     0,     0,     0,     0,    87,   246,   247,
     248,   249,   250,   251,   252,   253,   254,     0,   246,   247,
     248,   249,   250,   251,   252,   253,   254,     0,     0,   255,
       0,   256,   257,   258,   259,   260,     0,     0,     0,   255,
     129,   256,   257,   258,   259,   260,     0,     0,     0,     0,
     131,   246,   247,   248,   249,   250,   251,   252,   253,   254,
       0,   -76,   -76,   -76,   -76,   -76,   -76,   -76,   -76,   -76,
       0,     0,   255,     0,   256,   257,   258,   259,   260,     0,
       0,     0,   -76,   133,   -76,   -76,   -76,   -76,   -76,     0,
       0,     0,     0,   -76,   -77,   -77,   -77,   -77,   -77,   -77,
     -77,   -77,   -77,     0,   -73,   -73,   -73,   -73,   -73,   -73,
     -73,   -73,   -73,     0,     0,   -77,     0,   -77,   -77,   -77,
     -77,   -77,     0,     0,     0,   -73,   -77,   -73,   -73,   -73,
     -73,   -73,     0,     0,     0,     0,   -73,   -74,   -74,   -74,
     -74,   -74,   -74,   -74,   -74,   -74,     0,   -75,   -75,   -75,
     -75,   -75,   -75,   -75,   -75,   -75,     0,     0,   -74,     0,
     -74,   -74,   -74,   -74,   -74,     0,     0,     0,   -75,   -74,
     -75,   -75,   -75,   -75,   -75,     0,     0,     0,     0,   -75,
     -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,     0,
     -85,   -85,   -85,   -85,   -85,   -85,   -85,   -85,   -85,     0,
       0,   -78,     0,   -78,   -78,   -78,   -78,   -78,     0,     0,
       0,   -85,   -78,   -85,   -85,   -85,   -85,   -85,     0,     0,
       0,     0,   -85,   -80,   -80,   -80,   -80,   -80,   -80,   -80,
     -80,   -80,     0,   -81,   -81,   -81,   -81,   -81,   -81,   -81,
     -81,   -81,     0,     0,   -80,     0,   -80,   -80,   -80,   -80,
     -80,     0,     0,     0,   -81,   -80,   -81,   -81,   -81,   -81,
     -81,     0,     0,     0,     0,   -81,   -79,   -79,   -79,   -79,
     -79,   -79,   -79,   -79,   -79,     0,   -82,   -82,   -82,   -82,
     -82,   -82,   -82,   -82,   -82,     0,     0,   -79,     0,   -79,
     -79,   -79,   -79,   -79,     0,     0,     0,   -82,   -79,   -82,
     -82,   -82,   -82,   -82,     0,     0,     0,     0,   -82,   -83,
     -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,     0,   -84,
     -84,   -84,   -84,   -84,   -84,   -84,   -84,   -84,     0,     0,
     -83,     0,   -83,   -83,   -83,   -83,   -83,     0,     0,     0,
     -84,   -83,   -84,   -84,   -84,   -84,   -84,     0,     0,     0,
       0,   -84,   246,   247,   248,   249,   250,   251,   252,   253,
     254,     0,   -91,   -91,   -91,   -91,   -91,   -91,   -91,   -91,
     -91,     0,     0,   255,     0,   256,   257,   258,   259,   260,
       0,     0,     0,   -91,   552,   -91,   -91,   -91,   -91,   -91,
       0,     0,     0,     0,   -91,  -110,  -110,  -110,  -110,  -110,
    -110,  -110,  -110,  -110,     0,   246,   -92,   -92,   -92,   -92,
     -92,   -92,   -92,   -92,     0,     0,  -110,     0,  -110,  -110,
    -110,  -110,  -110,     0,     0,     0,   -92,  -110,   256,   257,
     258,   259,   260,     0,     0,     0,     0,   -92,  -111,  -111,
    -111,  -111,  -111,  -111,  -111,  -111,  -111,     0,   246,   247,
     -93,   -93,   -93,   -93,   -93,   -93,   -93,     0,     0,  -111,
       0,  -111,  -111,  -111,  -111,  -111,     0,     0,     0,   -93,
    -111,   256,   257,   258,   259,   260,     0,     0,     0,     0,
     -93,  -112,  -112,  -112,  -112,  -112,  -112,  -112,  -112,  -112,
       0,   246,   247,   248,   -94,   -94,   -94,   -94,   -94,   -94,
       0,     0,  -112,     0,  -112,  -112,  -112,  -112,  -112,     0,
       0,     0,   -94,  -112,   256,   257,   258,   259,   260,     0,
       0,     0,     0,   -94,  -113,  -113,  -113,  -113,  -113,  -113,
    -113,  -113,  -113,     0,   246,   247,   248,   249,   -95,   -95,
     -95,   -95,   -95,     0,     0,  -113,     0,  -113,  -113,  -113,
    -113,  -113,     0,     0,     0,   -95,  -113,   256,   257,   258,
     259,   260,     0,     0,     0,     0,   -95,  -114,  -114,  -114,
    -114,  -114,  -114,  -114,  -114,  -114,     0,   246,   247,   248,
     249,   250,   -96,   -96,   -96,   -96,     0,     0,  -114,     0,
    -114,  -114,  -114,  -114,  -114,     0,     0,     0,   -96,  -114,
     256,   257,   258,   259,   260,     0,     0,     0,     0,   -96,
    -115,  -115,  -115,  -115,  -115,  -115,  -115,  -115,  -115,     0,
     246,   247,   248,   249,   250,   251,   -97,   -97,   -97,     0,
       0,  -115,     0,  -115,  -115,  -115,  -115,  -115,     0,     0,
       0,   -97,  -115,   256,   257,   258,   259,   260,     0,     0,
       0,     0,   -97,  -116,  -116,  -116,  -116,  -116,  -116,  -116,
    -116,  -116,     0,   246,   247,   248,   249,   250,   251,   252,
     -98,   -98,     0,     0,  -116,     0,  -116,  -116,  -116,  -116,
    -116,     0,     0,     0,   -98,  -116,   256,   257,   258,   259,
     260,     0,     0,     0,     0,   -98,  -117,  -117,  -117,  -117,
    -117,  -117,  -117,  -117,  -117,     0,  -108,  -108,  -108,  -108,
    -108,  -108,  -108,  -108,  -108,     0,     0,  -117,     0,  -117,
    -117,  -117,  -117,  -117,     0,     0,     0,  -108,  -117,  -108,
    -108,  -108,  -108,  -108,     0,     0,     0,     0,  -108,   246,
     -89,   -89,   -89,   -89,   -89,   -89,   -89,   -89,     0,  -109,
    -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,     0,     0,
     -89,     0,   -89,   -89,   258,   259,   260,     0,     0,     0,
    -109,   -89,  -109,  -109,  -109,  -109,  -109,     0,     0,     0,
       0,  -109,   246,   -90,   -90,   -90,   -90,   -90,   -90,   -90,
     -90,     0,  -105,  -105,  -105,  -105,  -105,  -105,  -105,  -105,
    -105,     0,     0,   -90,     0,   -90,   -90,   258,   259,   260,
       0,     0,     0,  -105,   -90,  -105,  -105,  -105,  -105,  -105,
       0,     0,     0,     0,  -105,   246,   -86,   -86,   -86,   -86,
     -86,   -86,   -86,   -86,     0,  -106,  -106,  -106,  -106,  -106,
    -106,  -106,  -106,  -106,     0,     0,   -86,     0,   -86,   -86,
     -86,   -86,   -86,     0,     0,     0,  -106,   -86,  -106,  -106,
    -106,  -106,  -106,     0,     0,     0,     0,  -106,   246,   -87,
     -87,   -87,   -87,   -87,   -87,   -87,   -87,     0,  -107,  -107,
    -107,  -107,  -107,  -107,  -107,  -107,  -107,     0,     0,   -87,
       0,   -87,   -87,   -87,   -87,   -87,     0,     0,     0,  -107,
     -87,  -107,  -107,  -107,  -107,  -107,     0,     0,     0,     0,
    -107,   246,   -88,   -88,   -88,   -88,   -88,   -88,   -88,   -88,
       0,   246,   247,   248,   249,   250,   251,   252,   253,   254,
       0,     0,   -88,     0,   -88,   -88,   -88,   -88,   -88,     0,
       0,     0,   255,   -88,   256,   257,   258,   259,   260,     0,
       0,     0,     0,   574,   246,   247,   248,   249,   250,   251,
     252,   253,   254,     0,   246,   247,   248,   249,   250,   251,
     252,   253,   254,     0,     0,   255,     0,   256,   257,   258,
     259,   260,     0,     0,     0,   255,   579,   256,   257,   258,
     259,   260,     0,     0,     0,     0,   -66,   246,   247,   248,
     249,   250,   251,   252,   253,   254,     0,  -118,  -118,  -118,
    -118,  -118,  -118,  -118,  -118,  -118,     0,     0,   255,     0,
     256,   257,   258,   259,   260,     0,     0,     0,  -118,   602,
    -118,  -118,  -118,  -118,  -118,     0,     0,     0,     0,  -118,
     246,   247,   248,   249,   250,   251,   252,   253,   254,     0,
    -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,     0,
       0,   255,     0,   256,   257,   258,   259,   260,     0,     0,
       0,  -102,  -100,  -102,  -102,  -102,  -102,  -102,     0,     0,
       0,     0,  -102,  -104,  -104,  -104,  -104,  -104,  -104,  -104,
    -104,  -104,     0,   246,   247,   248,   249,   250,   251,   252,
     253,   254,     0,     0,  -104,     0,  -104,  -104,  -104,  -104,
    -104,     0,     0,     0,   255,  -104,   256,   257,   258,   259,
     260,     0,     0,     0,     0,   611,   246,   247,   248,   249,
     250,   251,   252,   253,   254,     0,   246,   247,   248,   249,
     250,   251,   252,   253,   254,     0,     0,   255,     0,   256,
     257,   258,   259,   260,     0,     0,     0,   255,   613,   256,
     257,   258,   259,   260,     0,     0,     0,     0,   615,   246,
     247,   248,   249,   250,   251,   252,   253,   254,     0,   246,
     247,   248,   249,   250,   251,   252,   253,   254,     0,     0,
     255,     0,   256,   257,   258,   259,   260,     0,     0,     0,
     255,   628,   256,   257,   258,   259,   260,     0,     0,     0,
       0,   630,   246,   247,   248,   249,   250,   251,   252,   253,
     254,     0,   246,   247,   248,   249,   250,   251,   252,   253,
     254,     0,     0,   255,     0,   256,   257,   258,   259,   260,
       0,     0,     0,   255,   632,   256,   257,   258,   259,   260,
       0,     0,     0,     0,   -99,  -120,  -120,  -120,  -120,  -120,
    -120,  -120,  -120,  -120,     0,  -119,  -119,  -119,  -119,  -119,
    -119,  -119,  -119,  -119,     0,     0,  -120,     0,  -120,  -120,
    -120,  -120,  -120,     0,     0,     0,  -119,  -120,  -119,  -119,
    -119,  -119,  -119,     0,     0,     0,     0,  -119,   246,   247,
     248,   249,   250,   251,   252,   253,   254,     0,   246,   247,
     248,   249,   250,   251,   252,   253,   254,     0,     0,   255,
       0,   256,   257,   258,   259,   260,     0,     0,     0,   255,
     748,   256,   257,   258,   259,   260,     0,     0,     0,     0,
     750,   246,   247,   248,   249,   250,   251,   252,   253,   254,
       0,     0,     0,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   255,     0,   256,   257,   258,   259,   260,     0,
       0,     0,     0,   752,   308,   141,   309,   310,   311,   312,
     313,   -76,   -76,   -76,   -76,   -76,   -76,   -76,   -76,   -76,
     -77,   -77,   -77,   -77,   -77,   -77,   -77,   -77,   -77,     0,
       0,     0,   -76,   -76,   -76,   -76,   -76,   -76,   -76,     0,
       0,   -77,   -77,   -77,   -77,   -77,   -77,   -77,   -73,   -73,
     -73,   -73,   -73,   -73,   -73,   -73,   -73,   -74,   -74,   -74,
     -74,   -74,   -74,   -74,   -74,   -74,     0,     0,     0,   -73,
     -73,   -73,   -73,   -73,   -73,   -73,     0,     0,   -74,   -74,
     -74,   -74,   -74,   -74,   -74,   -75,   -75,   -75,   -75,   -75,
     -75,   -75,   -75,   -75,   299,   300,   301,   302,   303,   304,
     305,   306,   307,     0,     0,     0,   -75,   -75,   -75,   -75,
     -75,   -75,   -75,     0,     0,   308,   553,   309,   310,   311,
     312,   313,   -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,
     -78,   -85,   -85,   -85,   -85,   -85,   -85,   -85,   -85,   -85,
       0,     0,     0,   -78,   -78,   -78,   -78,   -78,   -78,   -78,
       0,     0,   -85,   -85,   -85,   -85,   -85,   -85,   -85,   -80,
     -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -81,   -81,
     -81,   -81,   -81,   -81,   -81,   -81,   -81,     0,     0,     0,
     -80,   -80,   -80,   -80,   -80,   -80,   -80,     0,     0,   -81,
     -81,   -81,   -81,   -81,   -81,   -81,   -79,   -79,   -79,   -79,
     -79,   -79,   -79,   -79,   -79,   -82,   -82,   -82,   -82,   -82,
     -82,   -82,   -82,   -82,     0,     0,     0,   -79,   -79,   -79,
     -79,   -79,   -79,   -79,     0,     0,   -82,   -82,   -82,   -82,
     -82,   -82,   -82,   -83,   -83,   -83,   -83,   -83,   -83,   -83,
     -83,   -83,   -84,   -84,   -84,   -84,   -84,   -84,   -84,   -84,
     -84,     0,     0,     0,   -83,   -83,   -83,   -83,   -83,   -83,
     -83,     0,     0,   -84,   -84,   -84,   -84,   -84,   -84,   -84,
     -91,   -91,   -91,   -91,   -91,   -91,   -91,   -91,   -91,  -110,
    -110,  -110,  -110,  -110,  -110,  -110,  -110,  -110,     0,     0,
       0,   -91,   -91,   -91,   -91,   -91,   -91,   -91,     0,     0,
    -110,  -110,  -110,  -110,  -110,  -110,  -110,   299,   -92,   -92,
     -92,   -92,   -92,   -92,   -92,   -92,  -111,  -111,  -111,  -111,
    -111,  -111,  -111,  -111,  -111,     0,     0,     0,   -92,   -92,
     309,   310,   311,   312,   313,     0,     0,  -111,  -111,  -111,
    -111,  -111,  -111,  -111,   299,   300,   -93,   -93,   -93,   -93,
     -93,   -93,   -93,  -112,  -112,  -112,  -112,  -112,  -112,  -112,
    -112,  -112,     0,     0,     0,   -93,   -93,   309,   310,   311,
     312,   313,     0,     0,  -112,  -112,  -112,  -112,  -112,  -112,
    -112,   299,   300,   301,   -94,   -94,   -94,   -94,   -94,   -94,
    -113,  -113,  -113,  -113,  -113,  -113,  -113,  -113,  -113,     0,
       0,     0,   -94,   -94,   309,   310,   311,   312,   313,     0,
       0,  -113,  -113,  -113,  -113,  -113,  -113,  -113,   299,   300,
     301,   302,   -95,   -95,   -95,   -95,   -95,  -114,  -114,  -114,
    -114,  -114,  -114,  -114,  -114,  -114,     0,     0,     0,   -95,
     -95,   309,   310,   311,   312,   313,     0,     0,  -114,  -114,
    -114,  -114,  -114,  -114,  -114,   299,   300,   301,   302,   303,
     -96,   -96,   -96,   -96,  -115,  -115,  -115,  -115,  -115,  -115,
    -115,  -115,  -115,     0,     0,     0,   -96,   -96,   309,   310,
     311,   312,   313,     0,     0,  -115,  -115,  -115,  -115,  -115,
    -115,  -115,   299,   300,   301,   302,   303,   304,   -97,   -97,
     -97,  -116,  -116,  -116,  -116,  -116,  -116,  -116,  -116,  -116,
       0,     0,     0,   -97,   -97,   309,   310,   311,   312,   313,
       0,     0,  -116,  -116,  -116,  -116,  -116,  -116,  -116,   299,
     300,   301,   302,   303,   304,   305,   -98,   -98,  -117,  -117,
    -117,  -117,  -117,  -117,  -117,  -117,  -117,     0,     0,     0,
     -98,   -98,   309,   310,   311,   312,   313,     0,     0,  -117,
    -117,  -117,  -117,  -117,  -117,  -117,   299,   300,   301,   302,
     303,   304,   305,   306,   307,  -108,  -108,  -108,  -108,  -108,
    -108,  -108,  -108,  -108,     0,     0,     0,   308,   580,   309,
     310,   311,   312,   313,     0,     0,  -108,  -108,  -108,  -108,
    -108,  -108,  -108,   299,   -89,   -89,   -89,   -89,   -89,   -89,
     -89,   -89,  -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,
    -109,     0,     0,     0,   -89,   -89,   -89,   -89,   311,   312,
     313,     0,     0,  -109,  -109,  -109,  -109,  -109,  -109,  -109,
     299,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,  -105,
    -105,  -105,  -105,  -105,  -105,  -105,  -105,  -105,     0,     0,
       0,   -90,   -90,   -90,   -90,   311,   312,   313,     0,     0,
    -105,  -105,  -105,  -105,  -105,  -105,  -105,   299,   -86,   -86,
     -86,   -86,   -86,   -86,   -86,   -86,  -106,  -106,  -106,  -106,
    -106,  -106,  -106,  -106,  -106,     0,     0,     0,   -86,   -86,
     -86,   -86,   -86,   -86,   -86,     0,     0,  -106,  -106,  -106,
    -106,  -106,  -106,  -106,   299,   -87,   -87,   -87,   -87,   -87,
     -87,   -87,   -87,  -107,  -107,  -107,  -107,  -107,  -107,  -107,
    -107,  -107,     0,     0,     0,   -87,   -87,   -87,   -87,   -87,
     -87,   -87,     0,     0,  -107,  -107,  -107,  -107,  -107,  -107,
    -107,   299,   -88,   -88,   -88,   -88,   -88,   -88,   -88,   -88,
     299,   300,   301,   302,   303,   304,   305,   306,   307,     0,
       0,     0,   -88,   -88,   -88,   -88,   -88,   -88,   -88,     0,
       0,   308,   581,   309,   310,   311,   312,   313,   299,   300,
     301,   302,   303,   304,   305,   306,   307,  -118,  -118,  -118,
    -118,  -118,  -118,  -118,  -118,  -118,     0,     0,     0,   308,
     603,   309,   310,   311,   312,   313,     0,     0,  -118,  -118,
    -118,  -118,  -118,  -118,  -118,   299,   300,   301,   302,   303,
     304,   305,   306,   307,  -102,  -102,  -102,  -102,  -102,  -102,
    -102,  -102,  -102,     0,     0,     0,   308,  -100,   309,   310,
     311,   312,   313,     0,     0,  -102,  -102,  -102,  -102,  -102,
    -102,  -102,  -104,  -104,  -104,  -104,  -104,  -104,  -104,  -104,
    -104,   299,   300,   301,   302,   303,   304,   305,   306,   307,
       0,     0,     0,  -104,  -104,  -104,  -104,  -104,  -104,  -104,
       0,     0,   308,   -99,   309,   310,   311,   312,   313,  -120,
    -120,  -120,  -120,  -120,  -120,  -120,  -120,  -120,  -119,  -119,
    -119,  -119,  -119,  -119,  -119,  -119,  -119,     0,     0,     0,
    -120,  -120,  -120,  -120,  -120,  -120,  -120,     0,     0,  -119,
    -119,  -119,  -119,  -119,  -119,  -119
};

static const yytype_int16 yycheck[] =
{
       2,   265,   261,     0,     6,   139,   682,   612,   614,   408,
     410,   554,   564,    15,   120,    17,    18,    19,    20,    21,
      22,    23,   713,   372,   629,   631,   702,   609,    30,    73,
     606,    51,    38,   153,   154,    37,    38,    39,   232,   582,
     592,     1,    40,   734,   626,    43,    44,   623,    50,   762,
      52,    53,    54,    55,    56,    57,    58,    59,   644,    61,
      62,    63,    64,    65,    66,   137,   779,   740,    70,   333,
     329,     4,   192,   422,   661,    38,     3,   271,   122,   123,
       1,    41,    84,   756,   433,   671,     1,   207,     3,     4,
       1,   285,   679,     4,    38,   167,     1,   496,   498,    38,
     813,     1,     1,   550,     4,     0,    39,   783,   799,    41,
      43,    38,     1,    40,    40,   187,    43,    43,    40,    38,
      41,    43,    38,    40,     1,   572,   128,   129,    43,   131,
     577,   133,    43,   135,   807,    38,    41,   139,   210,   141,
     142,   185,    41,    43,   749,   751,   218,   341,     1,     1,
      39,   223,     1,   600,     3,     4,   228,   159,     1,   161,
       3,     4,    39,   512,   746,    40,    38,   743,    40,   189,
       1,    43,   715,   725,     3,     3,   196,    40,   180,   181,
      43,   767,   184,     1,   186,   205,    39,    39,   775,     1,
      39,     1,   212,    40,     1,     5,    39,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    39,    39,    38,
      38,    40,    40,    40,    43,    43,    43,   261,    28,    39,
      30,    31,    32,    33,    34,   227,     3,    39,    38,    39,
      39,   233,    39,    43,     0,     3,     4,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,    42,   255,   256,   257,   258,   259,   260,    40,
      38,    38,    40,    40,   266,    43,    43,    38,     1,    40,
     272,    39,    43,     1,    39,     3,   278,   279,   280,   281,
     282,   283,   284,   417,   286,   329,     2,   686,   688,     3,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,    39,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,   321,
      40,   323,   324,   325,   326,   327,   328,    40,    38,    41,
      40,    39,   334,    43,    50,     1,   338,     3,     4,     1,
     342,     3,     4,    40,    39,     2,   348,   349,   350,   351,
     352,   353,   354,   355,   356,   357,   358,   359,   360,   361,
     362,    41,   364,   365,   366,   367,   368,   369,     1,   371,
       3,     4,     1,    39,     0,    40,     3,    39,     1,     4,
      39,     1,     3,    41,    40,    39,   650,   646,   508,    39,
      42,    40,    39,    50,     1,     1,    42,    42,   418,     1,
       3,    40,    42,     1,    39,    39,    39,    44,    40,   411,
     412,   413,   128,   129,     1,   131,    38,   133,     1,   421,
      38,    38,    41,   139,     1,     1,    38,    38,    38,     3,
     432,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      41,     4,     1,   159,    38,   161,    38,    38,    38,     3,
     556,    40,    28,    38,    30,    31,    32,    33,    34,    38,
      38,    42,    42,    39,   180,   181,    39,    43,    40,    38,
     186,   128,   129,    40,   131,    39,   133,   597,   584,    39,
      42,    39,   139,   617,    40,   505,    39,    39,    39,     1,
      40,    39,    39,    38,    40,    39,    39,   499,   500,   501,
     606,    39,   159,    38,   161,    41,    39,    38,    42,   511,
       1,   555,    41,    41,    39,    41,    38,   623,    38,    40,
       1,    39,    41,   180,   181,    40,    40,    40,    39,   186,
      39,     1,    42,    39,    42,    42,    40,    39,    41,   583,
       1,    42,    42,    42,    39,    42,    42,    41,   550,    42,
      40,   553,     1,    42,    42,    42,    42,   268,   568,   229,
      -1,   170,   564,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     572,    -1,    -1,    -1,    -1,   577,    -1,    -1,   580,   581,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,     3,
     592,    -1,     6,    -1,    -1,    -1,    -1,    -1,   600,    -1,
      -1,   603,   646,    17,    18,    19,    20,    -1,   610,   611,
      -1,   717,    -1,    27,    -1,    -1,    30,    31,    32,    -1,
      -1,    35,    36,    37,    38,   627,   628,    -1,   630,    -1,
     632,    -1,     1,    -1,    -1,    -1,    -1,   743,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    -1,    -1,   651,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,
      -1,    30,    31,    32,    33,    34,    -1,    -1,    -1,    -1,
      39,    -1,   716,   675,    43,   677,   696,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   689,   690,   691,
      -1,   711,    -1,    -1,   714,    -1,    -1,    -1,    -1,    -1,
      -1,   417,    -1,    -1,   706,   707,    -1,    -1,   710,    -1,
      -1,    -1,   732,    -1,    -1,   735,    -1,    -1,    -1,    -1,
      -1,   741,     1,   725,    -1,    -1,    -1,    -1,     7,     8,
       9,    10,    11,    12,    13,    14,    15,   757,    -1,    -1,
     760,    -1,    -1,    -1,    -1,   747,   748,    -1,   750,    28,
     752,    30,    31,    32,    33,    34,    -1,   777,    -1,    -1,
      39,    -1,    -1,    -1,    43,    -1,    -1,    -1,    -1,   771,
      -1,   773,    -1,    -1,    -1,    -1,    -1,   797,    -1,    -1,
     800,    -1,    -1,    -1,    -1,   787,   788,     1,   808,   791,
      -1,   811,    -1,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    -1,    30,    31,    32,    33,
      34,    -1,    -1,    -1,     1,    39,    -1,    -1,    -1,    43,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      -1,    -1,     1,    -1,     3,    -1,    -1,     6,    -1,    -1,
      -1,    28,    -1,    30,    31,    32,    33,    34,    17,    18,
      19,    20,    39,    -1,    -1,    -1,    43,    -1,    27,    -1,
      -1,    30,    31,    32,    -1,     1,    35,    36,    37,    38,
      39,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,    -1,    -1,    -1,   610,   611,    -1,   613,    -1,   615,
      -1,   617,    28,    -1,    30,    31,    32,    33,    34,    -1,
      -1,   627,   628,    39,   630,    -1,   632,    43,     1,    -1,
      -1,    -1,    -1,    -1,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   657,    -1,   659,    -1,    28,    -1,    30,    31,    32,
      33,    34,    -1,   610,   611,    -1,    39,    -1,    -1,   675,
      43,   677,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     627,   628,    -1,   630,    -1,   632,    -1,    -1,    -1,   695,
      -1,    -1,   698,    -1,    -1,   701,    -1,    -1,    -1,    -1,
     706,   707,    -1,    -1,   710,     1,    -1,    -1,    -1,    -1,
      -1,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   675,    -1,
     677,    -1,    28,    -1,    30,    31,    32,    33,    34,    -1,
      -1,   747,   748,    39,   750,    -1,   752,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   706,
     707,    -1,    -1,   710,     1,   771,    -1,   773,    -1,    -1,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      -1,   787,   788,    -1,    -1,   791,    -1,    -1,    -1,    -1,
      -1,    28,    -1,    30,    31,    32,    33,    34,    -1,    -1,
     747,   748,    39,   750,     1,   752,    43,    -1,    -1,    -1,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      -1,    -1,    -1,    -1,   771,    -1,   773,    -1,    -1,    -1,
      -1,    28,    -1,    30,    31,    32,    33,    34,    -1,    -1,
     787,   788,    39,     1,   791,    -1,    43,    -1,    -1,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      28,    -1,    30,    31,    32,    33,    34,    -1,    -1,    -1,
       1,    39,    -1,    -1,    -1,    43,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    30,
      31,    32,    33,    34,    -1,    -1,    -1,     1,    39,    -1,
      -1,    -1,    43,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    -1,    30,    31,    32,    33,
      34,    -1,    -1,    -1,     1,    39,    -1,    -1,    -1,    43,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    28,    -1,    30,    31,    32,    33,    34,    -1,    -1,
      -1,     1,    39,    -1,    -1,    -1,    43,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,
      30,    31,    32,    33,    34,    -1,    -1,    -1,     1,    39,
      -1,    -1,    -1,    43,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    -1,    30,    31,    32,
      33,    34,    -1,    -1,    -1,     1,    39,    -1,    -1,    -1,
      43,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    28,    -1,    30,    31,    32,    33,    34,    -1,
      -1,    -1,     1,    39,    -1,    -1,    -1,    43,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,
      -1,    30,    31,    32,    33,    34,    -1,    -1,    -1,     1,
      39,    -1,    -1,    -1,    43,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    30,    31,
      32,    33,    34,    -1,    -1,    -1,     1,    39,    -1,    -1,
      -1,    43,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    -1,    30,    31,    32,    33,    34,
      -1,    -1,    -1,     1,    39,    -1,    -1,    -1,    43,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      28,    -1,    30,    31,    32,    33,    34,    -1,    -1,    -1,
       1,    39,    -1,    -1,    -1,    43,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    30,
      31,    32,    33,    34,    -1,    -1,    -1,     1,    39,    -1,
      -1,    -1,    43,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    -1,    30,    31,    32,    33,
      34,    -1,    -1,    -1,     1,    39,    -1,    -1,    -1,    43,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    28,    -1,    30,    31,    32,    33,    34,    -1,    -1,
      -1,     1,    39,    -1,    -1,    -1,    43,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,
      30,    31,    32,    33,    34,    -1,    -1,    -1,     1,    39,
      -1,    -1,    -1,    43,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    -1,    30,    31,    32,
      33,    34,    -1,    -1,    -1,     1,    39,    -1,    -1,    -1,
      43,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    28,    -1,    30,    31,    32,    33,    34,    -1,
      -1,    -1,     1,    39,    -1,    -1,    -1,    43,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,
      -1,    30,    31,    32,    33,    34,    -1,    -1,    -1,     1,
      39,    -1,    -1,    -1,    43,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    30,    31,
      32,    33,    34,    -1,    -1,    -1,     1,    39,    -1,    -1,
      -1,    43,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    -1,    30,    31,    32,    33,    34,
      -1,    -1,    -1,     1,    39,    -1,    -1,    -1,    43,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      28,    -1,    30,    31,    32,    33,    34,    -1,    -1,    -1,
       1,    39,    -1,    -1,    -1,    43,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    30,
      31,    32,    33,    34,    -1,    -1,    -1,     1,    39,    -1,
      -1,    -1,    43,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    -1,    30,    31,    32,    33,
      34,    -1,    -1,    -1,     1,    39,    -1,    -1,    -1,    43,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    28,    -1,    30,    31,    32,    33,    34,    -1,    -1,
      -1,     1,    39,    -1,    -1,    -1,    43,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,
      30,    31,    32,    33,    34,    -1,    -1,    -1,     1,    39,
      -1,    -1,    -1,    43,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    -1,    30,    31,    32,
      33,    34,    -1,    -1,    -1,     1,    39,    -1,    -1,    -1,
      43,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    28,    -1,    30,    31,    32,    33,    34,    -1,
      -1,    -1,     1,    39,    -1,    -1,    -1,    43,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,
      -1,    30,    31,    32,    33,    34,    -1,    -1,    -1,     1,
      39,    -1,    -1,    -1,    43,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    30,    31,
      32,    33,    34,    -1,    -1,    -1,     1,    39,    -1,    -1,
      -1,    43,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    -1,    30,    31,    32,    33,    34,
      -1,    -1,    -1,     1,    39,    -1,    -1,    -1,    43,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      28,    -1,    30,    31,    32,    33,    34,    -1,    -1,    -1,
       1,    39,    -1,    -1,    -1,    43,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    30,
      31,    32,    33,    34,    -1,    -1,    -1,     1,    39,    -1,
      -1,    -1,    43,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    -1,    30,    31,    32,    33,
      34,    -1,    -1,    -1,     1,    39,    -1,    -1,    -1,    43,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    28,    -1,    30,    31,    32,    33,    34,    -1,    -1,
      -1,     1,    39,    -1,    -1,    -1,    43,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,
      30,    31,    32,    33,    34,    -1,    -1,    -1,     1,    39,
      -1,    -1,    -1,    43,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    -1,    30,    31,    32,
      33,    34,    -1,    -1,    -1,     1,    39,    -1,    -1,    -1,
      43,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    28,    -1,    30,    31,    32,    33,    34,    -1,
      -1,    -1,     0,    39,    -1,     3,     4,    43,     6,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      -1,    -1,    30,    31,    32,    -1,    -1,    35,    36,    37,
      38,     0,    40,    41,     3,     4,    -1,     6,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    -1,
      -1,    30,    31,    32,    -1,    -1,    35,    36,    37,    38,
       0,    40,    41,     3,     4,    -1,     6,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    -1,    -1,
      30,    31,    32,    -1,    -1,    35,    36,    37,    38,     0,
      40,    41,     3,     4,    -1,     6,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    -1,    -1,    30,
      31,    32,    -1,    -1,    35,    36,    37,    38,     0,    40,
      41,     3,     4,    -1,     6,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    -1,    -1,    30,    31,
      32,    -1,    -1,    35,    36,    37,    38,     0,    40,    41,
       3,     4,    -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    -1,    -1,    30,    31,    32,
      -1,    -1,    35,    36,    37,    38,     0,    40,    41,     3,
       4,    -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    -1,    -1,    30,    31,    32,    -1,
      -1,    35,    36,    37,    38,     0,    40,    41,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,     0,    40,    41,     3,     4,    -1,
       6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,    35,
      36,    37,    38,     0,    40,    41,     3,     4,    -1,     6,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    -1,    -1,    30,    31,    32,    -1,    -1,    35,    36,
      37,    38,     0,    40,    41,     3,     4,    -1,     6,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      -1,    -1,    30,    31,    32,    -1,    -1,    35,    36,    37,
      38,     0,    40,    41,     3,     4,    -1,     6,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    -1,
      -1,    30,    31,    32,    -1,    -1,    35,    36,    37,    38,
       0,    40,    41,     3,     4,    -1,     6,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    -1,    -1,
      30,    31,    32,    -1,    -1,    35,    36,    37,    38,     0,
      40,    41,     3,     4,    -1,     6,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    -1,    -1,    30,
      31,    32,    -1,    -1,    35,    36,    37,    38,     0,    40,
      41,     3,     4,    -1,     6,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    -1,    -1,    30,    31,
      32,    -1,    -1,    35,    36,    37,    38,     0,    40,    41,
       3,     4,    -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    -1,    -1,    30,    31,    32,
      -1,    -1,    35,    36,    37,    38,     0,    40,    41,     3,
       4,    -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    -1,    -1,    30,    31,    32,    -1,
      -1,    35,    36,    37,    38,     0,    40,    41,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,     0,    40,    41,     3,     4,    -1,
       6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,    35,
      36,    37,    38,     0,    40,    41,     3,     4,    -1,     6,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    -1,    -1,    30,    31,    32,    -1,    -1,    35,    36,
      37,    38,     0,    40,    41,     3,     4,    -1,     6,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      -1,    -1,    30,    31,    32,    -1,    -1,    35,    36,    37,
      38,     0,    40,    41,     3,     4,    -1,     6,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    -1,
      -1,    30,    31,    32,    -1,    -1,    35,    36,    37,    38,
       0,    40,    41,     3,     4,    -1,     6,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    -1,    -1,
      30,    31,    32,    -1,    -1,    35,    36,    37,    38,     0,
      40,    41,     3,     4,    -1,     6,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    17,    18,    19,    20,
      21,    22,    23,    24,    -1,    26,    27,    -1,    -1,    30,
      31,    32,    -1,    -1,    35,    36,    37,    38,     0,    40,
      41,     3,     4,    -1,     6,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    17,    18,    19,    20,    21,
      22,    23,    24,    -1,    26,    27,    -1,    -1,    30,    31,
      32,    -1,    -1,    35,    36,    37,    38,     0,    40,    41,
       3,     4,    -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    17,    18,    19,    20,    21,    22,
      23,    24,    -1,    26,    27,    -1,    -1,    30,    31,    32,
      -1,    -1,    35,    36,    37,    38,     0,    40,    41,     3,
       4,    -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    17,    18,    19,    20,    21,    22,    23,
      24,    -1,    26,    27,    -1,    -1,    30,    31,    32,    -1,
      -1,    35,    36,    37,    38,     0,    40,    41,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      -1,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,     0,    40,    41,     3,     4,    -1,
       6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    17,    18,    19,    20,    21,    22,    23,    24,    -1,
      26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,    35,
      36,    37,    38,     0,    40,    41,     3,     4,    -1,     6,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      17,    18,    19,    20,    21,    22,    23,    24,    -1,    26,
      27,    -1,    -1,    30,    31,    32,    -1,    -1,    35,    36,
      37,    38,     0,    40,    41,     3,     4,    -1,     6,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    17,
      18,    19,    20,    21,    22,    23,    24,    -1,    26,    27,
      -1,    -1,    30,    31,    32,    -1,    -1,    35,    36,    37,
      38,     0,    40,    41,     3,     4,    -1,     6,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    17,    18,
      19,    20,    21,    22,    23,    24,    -1,    26,    27,    -1,
      -1,    30,    31,    32,    -1,    -1,    35,    36,    37,    38,
       0,    40,    41,     3,     4,    -1,     6,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    17,    18,    19,
      20,    21,    22,    23,    24,    -1,    26,    27,    -1,    -1,
      30,    31,    32,    -1,    -1,    35,    36,    37,    38,     0,
      40,    41,     3,     4,    -1,     6,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    17,    18,    19,    20,
      21,    22,    23,    24,    -1,    26,    27,    -1,    -1,    30,
      31,    32,    -1,    -1,    35,    36,    37,    38,     0,    40,
      41,     3,     4,    -1,     6,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    17,    18,    19,    20,    21,
      22,    23,    24,    -1,    26,    27,    -1,    -1,    30,    31,
      32,    -1,    -1,    35,    36,    37,    38,     0,    40,    41,
       3,     4,    -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    17,    18,    19,    20,    21,    22,
      23,    24,    -1,    26,    27,    -1,    -1,    30,    31,    32,
      -1,    -1,    35,    36,    37,    38,     0,    40,    41,     3,
       4,    -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    17,    18,    19,    20,    21,    22,    23,
      24,    -1,    26,    27,    -1,    -1,    30,    31,    32,    -1,
      -1,    35,    36,    37,    38,     0,    40,    41,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      -1,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,     0,    40,    41,     3,     4,    -1,
       6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    17,    18,    19,    20,    21,    22,    23,    24,    -1,
      26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,    35,
      36,    37,    38,     0,    40,    41,     3,     4,    -1,     6,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      17,    18,    19,    20,    21,    22,    23,    24,    -1,    26,
      27,    -1,    -1,    30,    31,    32,    -1,    -1,    35,    36,
      37,    38,     0,    40,    41,     3,     4,    -1,     6,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    17,
      18,    19,    20,    21,    22,    23,    24,    -1,    26,    27,
      -1,    -1,    30,    31,    32,    -1,    -1,    35,    36,    37,
      38,     0,    40,    41,     3,     4,    -1,     6,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    17,    18,
      19,    20,    21,    22,    23,    24,    -1,    26,    27,    -1,
      -1,    30,    31,    32,    -1,    -1,    35,    36,    37,    38,
       0,    40,    41,     3,     4,    -1,     6,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    17,    18,    19,
      20,    21,    22,    23,    24,    -1,    26,    27,    -1,    -1,
      30,    31,    32,    -1,    -1,    35,    36,    37,    38,     0,
      40,    41,     3,     4,    -1,     6,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    17,    18,    19,    20,
      21,    22,    23,    24,    -1,    26,    27,    -1,    -1,    30,
      31,    32,    -1,    -1,    35,    36,    37,    38,     0,    40,
      41,     3,     4,    -1,     6,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    17,    18,    19,    20,    21,
      22,    23,    24,    -1,    26,    27,    -1,    -1,    30,    31,
      32,    -1,    -1,    35,    36,    37,    38,     0,    40,    41,
       3,     4,    -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    17,    18,    19,    20,    21,    22,
      23,    24,    -1,    26,    27,    -1,    -1,    30,    31,    32,
      -1,    -1,    35,    36,    37,    38,     0,    40,    41,     3,
       4,    -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    17,    18,    19,    20,    21,    22,    23,
      24,    -1,    26,    27,    -1,    -1,    30,    31,    32,    -1,
      -1,    35,    36,    37,    38,    -1,    40,    41,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      -1,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      -1,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      -1,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      -1,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      -1,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      -1,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      -1,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      -1,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      -1,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      -1,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      -1,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      -1,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      -1,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      -1,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      -1,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      -1,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      -1,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      -1,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      -1,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      -1,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      -1,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      -1,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      -1,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      -1,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      -1,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      -1,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,     3,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      -1,    26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,     3,     4,    -1,
       6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    17,    18,    19,    20,    21,    22,    23,    24,    -1,
      26,    27,    -1,    -1,    30,    31,    32,    -1,    -1,    35,
      36,    37,    38,    -1,    40,    41,     3,     4,    -1,     6,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      17,    18,    19,    20,    21,    22,    23,    24,    -1,    26,
      27,    -1,    -1,    30,    31,    32,    -1,    -1,    35,    36,
      37,    38,    -1,    40,    41,     3,     4,    -1,     6,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    17,
      18,    19,    20,    21,    22,    23,    24,    -1,    26,    27,
      -1,    -1,    30,    31,    32,    -1,    -1,    35,    36,    37,
      38,    -1,    40,    41,     3,     4,    -1,     6,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    17,    18,
      19,    20,    21,    22,    23,    24,    -1,    26,    27,    -1,
      -1,    30,    31,    32,    -1,    -1,    35,    36,    37,    38,
      -1,    40,    41,     3,     4,    -1,     6,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    17,    18,    19,
      20,    21,    22,    23,    24,    -1,    26,    27,    -1,    -1,
      30,    31,    32,    -1,    -1,    35,    36,    37,    38,    -1,
      40,    41,     3,     4,    -1,     6,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    17,    18,    19,    20,
      21,    22,    23,    24,    -1,    26,    27,    -1,    -1,    30,
      31,    32,    -1,    -1,    35,    36,    37,    38,    -1,    40,
      41,     5,    -1,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    -1,    30,    31,    32,    33,
      34,    -1,     3,     4,    38,     6,    40,    -1,    -1,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    17,    18,    19,    20,
      -1,    -1,    -1,    -1,    -1,    -1,    27,    -1,    -1,    30,
      31,    32,    -1,    -1,    35,    36,    37,    38,     1,    40,
       3,    -1,    -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    17,    18,    19,    20,    -1,    -1,
       1,    -1,     3,    -1,    27,     6,    -1,    30,    31,    32,
      -1,    -1,    35,    36,    37,    38,    17,    18,    19,    20,
      -1,    -1,     1,    -1,     3,    -1,    27,     6,    -1,    30,
      31,    32,    -1,    -1,    35,    36,    37,    38,    17,    18,
      19,    20,    -1,    -1,     1,    -1,     3,    -1,    27,     6,
      -1,    30,    31,    32,    -1,    -1,    35,    36,    37,    38,
      17,    18,    19,    20,    -1,    -1,     1,    -1,     3,    -1,
      27,     6,    -1,    30,    31,    32,    -1,    -1,    35,    36,
      37,    38,    17,    18,    19,    20,    -1,    -1,     1,    -1,
       3,    -1,    27,     6,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    17,    18,    19,    20,    -1,    -1,
       1,    -1,     3,    -1,    27,     6,    -1,    30,    31,    32,
      -1,    -1,    35,    36,    37,    38,    17,    18,    19,    20,
      -1,    -1,     1,    -1,     3,    -1,    27,     6,    -1,    30,
      31,    32,    -1,    -1,    35,    36,    37,    38,    17,    18,
      19,    20,    -1,    -1,     1,    -1,     3,    -1,    27,     6,
      -1,    30,    31,    32,    -1,    -1,    35,    36,    37,    38,
      17,    18,    19,    20,    -1,    -1,     1,    -1,     3,    -1,
      27,     6,    -1,    30,    31,    32,    -1,    -1,    35,    36,
      37,    38,    17,    18,    19,    20,    -1,    -1,     1,    -1,
       3,    -1,    27,     6,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    17,    18,    19,    20,    -1,    -1,
       1,    -1,     3,    -1,    27,     6,    -1,    30,    31,    32,
      -1,    -1,    35,    36,    37,    38,    17,    18,    19,    20,
      -1,    -1,     1,    -1,     3,    -1,    27,     6,    -1,    30,
      31,    32,    -1,    -1,    35,    36,    37,    38,    17,    18,
      19,    20,    -1,    -1,     1,    -1,     3,    -1,    27,     6,
      -1,    30,    31,    32,    -1,    -1,    35,    36,    37,    38,
      17,    18,    19,    20,    -1,    -1,     1,    -1,     3,    -1,
      27,     6,    -1,    30,    31,    32,    -1,    -1,    35,    36,
      37,    38,    17,    18,    19,    20,    -1,    -1,     1,    -1,
       3,    -1,    27,     6,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    17,    18,    19,    20,    -1,    -1,
      -1,    -1,     3,    -1,    27,     6,    -1,    30,    31,    32,
      -1,    -1,    35,    36,    37,    38,    17,    18,    19,    20,
      -1,    -1,    -1,    -1,    -1,    -1,    27,    -1,    -1,    30,
      31,    32,    -1,    -1,    35,    36,    37,    38,     1,    40,
       3,    -1,    -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    17,    18,    19,    20,    -1,    -1,
       1,    -1,     3,    -1,    27,     6,    -1,    30,    31,    32,
      -1,    -1,    35,    36,    37,    38,    17,    18,    19,    20,
      -1,    -1,     1,    -1,     3,    -1,    27,     6,    -1,    30,
      31,    32,    -1,    -1,    35,    36,    37,    38,    17,    18,
      19,    20,    -1,    -1,     1,    -1,     3,    -1,    27,     6,
      -1,    30,    31,    32,    -1,    -1,    35,    36,    37,    38,
      17,    18,    19,    20,    -1,    -1,     1,    -1,     3,    -1,
      27,     6,    -1,    30,    31,    32,    -1,    -1,    35,    36,
      37,    38,    17,    18,    19,    20,    -1,    -1,     1,    -1,
       3,    -1,    27,     6,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    17,    18,    19,    20,    -1,    -1,
       1,    -1,     3,    -1,    27,     6,    -1,    30,    31,    32,
      -1,    -1,    35,    36,    37,    38,    17,    18,    19,    20,
      -1,    -1,     1,    -1,     3,    -1,    27,     6,    -1,    30,
      31,    32,    -1,    -1,    35,    36,    37,    38,    17,    18,
      19,    20,    -1,    -1,     1,    -1,     3,    -1,    27,     6,
      -1,    30,    31,    32,    -1,    -1,    35,    36,    37,    38,
      17,    18,    19,    20,    -1,    -1,     1,    -1,     3,    -1,
      27,     6,    -1,    30,    31,    32,    -1,    -1,    35,    36,
      37,    38,    17,    18,    19,    20,    -1,    -1,     1,    -1,
       3,    -1,    27,     6,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    17,    18,    19,    20,    -1,    -1,
       1,    -1,     3,    -1,    27,     6,    -1,    30,    31,    32,
      -1,    -1,    35,    36,    37,    38,    17,    18,    19,    20,
      -1,    -1,     1,    -1,     3,    -1,    27,     6,    -1,    30,
      31,    32,    -1,    -1,    35,    36,    37,    38,    17,    18,
      19,    20,    -1,    -1,     1,    -1,     3,    -1,    27,     6,
      -1,    30,    31,    32,    -1,    -1,    35,    36,    37,    38,
      17,    18,    19,    20,    -1,    -1,     1,    -1,     3,    -1,
      27,     6,    -1,    30,    31,    32,    -1,    -1,    35,    36,
      37,    38,    17,    18,    19,    20,    -1,    -1,     1,    -1,
       3,    -1,    27,     6,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    17,    18,    19,    20,    -1,    -1,
       1,    -1,     3,    -1,    27,     6,    -1,    30,    31,    32,
      -1,    -1,    35,    36,    37,    38,    17,    18,    19,    20,
      -1,    -1,     1,    -1,     3,    -1,    27,     6,    -1,    30,
      31,    32,    -1,    -1,    35,    36,    37,    38,    17,    18,
      19,    20,    -1,    -1,     1,    -1,     3,    -1,    27,     6,
      -1,    30,    31,    32,    -1,    -1,    35,    36,    37,    38,
      17,    18,    19,    20,    -1,    -1,     1,    -1,     3,    -1,
      27,     6,    -1,    30,    31,    32,    -1,    -1,    35,    36,
      37,    38,    17,    18,    19,    20,    -1,    -1,     1,    -1,
       3,    -1,    27,     6,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    17,    18,    19,    20,    -1,    -1,
       1,    -1,     3,    -1,    27,     6,    -1,    30,    31,    32,
      -1,    -1,    35,    36,    37,    38,    17,    18,    19,    20,
      -1,    -1,     1,    -1,     3,    -1,    27,     6,    -1,    30,
      31,    32,    -1,    -1,    35,    36,    37,    38,    17,    18,
      19,    20,    -1,    -1,     1,    -1,     3,    -1,    27,     6,
      -1,    30,    31,    32,    -1,    -1,    35,    36,    37,    38,
      17,    18,    19,    20,    -1,    -1,     1,    -1,     3,    -1,
      27,     6,    -1,    30,    31,    32,    -1,    -1,    35,    36,
      37,    38,    17,    18,    19,    20,    -1,    -1,     1,    -1,
       3,    -1,    27,     6,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    17,    18,    19,    20,    -1,    -1,
       1,    -1,     3,    -1,    27,     6,    -1,    30,    31,    32,
      -1,    -1,    35,    36,    37,    38,    17,    18,    19,    20,
      -1,    -1,     1,    -1,     3,    -1,    27,     6,    -1,    30,
      31,    32,    -1,    -1,    35,    36,    37,    38,    17,    18,
      19,    20,    -1,    -1,     1,    -1,     3,    -1,    27,     6,
      -1,    30,    31,    32,    -1,    -1,    35,    36,    37,    38,
      17,    18,    19,    20,    -1,    -1,     1,    -1,     3,    -1,
      27,     6,    -1,    30,    31,    32,    -1,    -1,    35,    36,
      37,    38,    17,    18,    19,    20,    -1,    -1,     1,    -1,
       3,    -1,    27,     6,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    17,    18,    19,    20,    -1,    -1,
       1,    -1,     3,    -1,    27,     6,    -1,    30,    31,    32,
      -1,    -1,    35,    36,    37,    38,    17,    18,    19,    20,
      -1,    -1,     1,    -1,     3,    -1,    27,     6,    -1,    30,
      31,    32,    -1,    -1,    35,    36,    37,    38,    17,    18,
      19,    20,    -1,    -1,     1,    -1,     3,    -1,    27,     6,
      -1,    30,    31,    32,    -1,    -1,    35,    36,    37,    38,
      17,    18,    19,    20,    -1,    -1,     1,    -1,     3,    -1,
      27,     6,    -1,    30,    31,    32,    -1,    -1,    35,    36,
      37,    38,    17,    18,    19,    20,    -1,    -1,     1,    -1,
       3,    -1,    27,     6,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    17,    18,    19,    20,    -1,    -1,
       1,    -1,     3,    -1,    27,     6,    -1,    30,    31,    32,
      -1,    -1,    35,    36,    37,    38,    17,    18,    19,    20,
      -1,    -1,     1,    -1,     3,    -1,    27,     6,    -1,    30,
      31,    32,    -1,    -1,    35,    36,    37,    38,    17,    18,
      19,    20,    -1,    -1,     1,    -1,     3,    -1,    27,     6,
      -1,    30,    31,    32,    -1,    -1,    35,    36,    37,    38,
      17,    18,    19,    20,    -1,    -1,     1,    -1,     3,    -1,
      27,     6,    -1,    30,    31,    32,    -1,    -1,    35,    36,
      37,    38,    17,    18,    19,    20,    -1,    -1,     1,    -1,
       3,    -1,    27,     6,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    17,    18,    19,    20,    -1,    -1,
       1,    -1,     3,    -1,    27,     6,    -1,    30,    31,    32,
      -1,    -1,    35,    36,    37,    38,    17,    18,    19,    20,
      -1,    -1,     1,    -1,     3,    -1,    27,     6,    -1,    30,
      31,    32,    -1,    -1,    35,    36,    37,    38,    17,    18,
      19,    20,    -1,    -1,     1,    -1,     3,    -1,    27,     6,
      -1,    30,    31,    32,    -1,    -1,    35,    36,    37,    38,
      17,    18,    19,    20,    -1,    -1,     1,    -1,     3,    -1,
      27,     6,    -1,    30,    31,    32,    -1,    -1,    35,    36,
      37,    38,    17,    18,    19,    20,    -1,    -1,     1,    -1,
       3,    -1,    27,     6,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    17,    18,    19,    20,    -1,    -1,
       1,    -1,     3,    -1,    27,     6,    -1,    30,    31,    32,
      -1,    -1,    35,    36,    37,    38,    17,    18,    19,    20,
      -1,    -1,     1,    -1,     3,    -1,    27,     6,    -1,    30,
      31,    32,    -1,    -1,    35,    36,    37,    38,    17,    18,
      19,    20,    -1,    -1,     1,    -1,     3,    -1,    27,     6,
      -1,    30,    31,    32,    -1,    -1,    35,    36,    37,    38,
      17,    18,    19,    20,    -1,    -1,     1,    -1,     3,    -1,
      27,     6,    -1,    30,    31,    32,    -1,    -1,    35,    36,
      37,    38,    17,    18,    19,    20,    -1,    -1,     1,    -1,
       3,    -1,    27,     6,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    17,    18,    19,    20,    -1,    -1,
       1,    -1,     3,    -1,    27,     6,    -1,    30,    31,    32,
      -1,    -1,    35,    36,    37,    38,    17,    18,    19,    20,
      -1,    -1,     1,    -1,     3,    -1,    27,     6,    -1,    30,
      31,    32,    -1,    -1,    35,    36,    37,    38,    17,    18,
      19,    20,    -1,    -1,     1,    -1,     3,    -1,    27,     6,
      -1,    30,    31,    32,    -1,    -1,    35,    36,    37,    38,
      17,    18,    19,    20,    -1,    -1,     1,    -1,     3,    -1,
      27,     6,    -1,    30,    31,    32,    -1,    -1,    35,    36,
      37,    38,    17,    18,    19,    20,    -1,    -1,     1,    -1,
       3,    -1,    27,     6,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    17,    18,    19,    20,    -1,    -1,
       1,    -1,     3,    -1,    27,     6,    -1,    30,    31,    32,
      -1,    -1,    35,    36,    37,    38,    17,    18,    19,    20,
      -1,    -1,     1,    -1,     3,    -1,    27,     6,    -1,    30,
      31,    32,    -1,    -1,    35,    36,    37,    38,    17,    18,
      19,    20,    -1,    -1,     1,    -1,     3,    -1,    27,     6,
      -1,    30,    31,    32,    -1,    -1,    35,    36,    37,    38,
      17,    18,    19,    20,    -1,    -1,     1,    -1,     3,    -1,
      27,     6,    -1,    30,    31,    32,    -1,    -1,    35,    36,
      37,    38,    17,    18,    19,    20,    -1,    -1,     1,    -1,
       3,    -1,    27,     6,    -1,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    17,    18,    19,    20,    -1,    -1,
       1,    -1,     3,    -1,    27,     6,    -1,    30,    31,    32,
      -1,    -1,    35,    36,    37,    38,    17,    18,    19,    20,
      -1,    -1,     1,    -1,     3,    -1,    27,     6,    -1,    30,
      31,    32,    -1,    -1,    35,    36,    37,    38,    17,    18,
      19,    20,    -1,    -1,     1,    -1,     3,    -1,    27,     6,
      -1,    30,    31,    32,    -1,    -1,    35,    36,    37,    38,
      17,    18,    19,    20,    -1,    -1,    -1,    -1,    -1,    -1,
      27,    -1,    -1,    30,    31,    32,    -1,    -1,    35,    36,
      37,    38,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    -1,    30,    31,    32,    33,    34,
      -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,    43,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      28,    -1,    30,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    -1,    40,    -1,    -1,    43,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    30,
      31,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,    40,
      -1,    -1,    43,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    -1,    30,    31,    32,    33,
      34,    -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,    43,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    28,    -1,    30,    31,    32,    33,    34,    -1,    -1,
      -1,    -1,    -1,    40,    -1,    -1,    43,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,
      30,    31,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,
      40,    -1,    -1,    43,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    -1,    30,    31,    32,
      33,    34,    -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,
      43,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    28,    -1,    30,    31,    32,    33,    34,    -1,
      -1,    -1,    -1,    -1,    40,    -1,    -1,    43,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,
      -1,    30,    31,    32,    33,    34,    -1,    -1,    -1,    -1,
      -1,    40,    -1,    -1,    43,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    30,    31,
      32,    33,    34,    -1,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    43,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    -1,    30,    31,    32,    33,    34,
      -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,    43,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      28,    -1,    30,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    -1,    40,    -1,    -1,    43,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    30,
      31,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,    40,
      -1,    -1,    43,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    -1,    30,    31,    32,    33,
      34,    -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,    43,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    28,    -1,    30,    31,    32,    33,    34,    -1,    -1,
      -1,    -1,    -1,    40,    -1,    -1,    43,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,
      30,    31,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,
      40,    -1,    -1,    43,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    -1,    30,    31,    32,
      33,    34,    -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,
      43,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    28,    -1,    30,    31,    32,    33,    34,    -1,
      -1,    -1,    -1,    -1,    40,    -1,    -1,    43,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,
      -1,    30,    31,    32,    33,    34,    -1,    -1,    -1,    -1,
      -1,    40,    -1,    -1,    43,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    30,    31,
      32,    33,    34,    -1,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    43,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    -1,    30,    31,    32,    33,    34,
      -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,    43,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      28,    -1,    30,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    -1,    40,    -1,    -1,    43,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    30,
      31,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,    40,
      -1,    -1,    43,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    -1,    30,    31,    32,    33,
      34,    -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,    43,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    28,    -1,    30,    31,    32,    33,    34,    -1,    -1,
      -1,    -1,    -1,    40,    -1,    -1,    43,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,
      30,    31,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,
      40,    -1,    -1,    43,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    -1,    30,    31,    32,
      33,    34,    -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,
      43,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    28,    -1,    30,    31,    32,    33,    34,    -1,
      -1,    -1,    -1,    -1,    40,    -1,    -1,    43,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,
      -1,    30,    31,    32,    33,    34,    -1,    -1,    -1,    -1,
      -1,    40,    -1,    -1,    43,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    30,    31,
      32,    33,    34,    -1,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    43,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    -1,    30,    31,    32,    33,    34,
      -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,    43,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      28,    -1,    30,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    -1,    40,    -1,    -1,    43,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    30,
      31,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,    40,
      -1,    -1,    43,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    -1,    30,    31,    32,    33,
      34,    -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,    43,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    28,    -1,    30,    31,    32,    33,    34,    -1,    -1,
      -1,    -1,    -1,    40,    -1,    -1,    43,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,
      30,    31,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,
      40,    -1,    -1,    43,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    -1,    30,    31,    32,
      33,    34,    -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,
      43,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    28,    -1,    30,    31,    32,    33,    34,    -1,
      -1,    -1,    -1,    -1,    40,    -1,    -1,    43,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,
      -1,    30,    31,    32,    33,    34,    -1,    -1,    -1,    -1,
      -1,    40,    -1,    -1,    43,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    30,    31,
      32,    33,    34,    -1,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    43,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    -1,    30,    31,    32,    33,    34,
      -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,    43,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      28,    -1,    30,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    -1,    40,    -1,    -1,    43,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    30,
      31,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,    40,
      -1,    -1,    43,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    -1,    30,    31,    32,    33,
      34,    -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,    43,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    28,    -1,    30,    31,    32,    33,    34,    -1,    -1,
      -1,    -1,    -1,    40,    -1,    -1,    43,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,
      30,    31,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,
      40,    -1,    -1,    43,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    -1,    30,    31,    32,
      33,    34,    -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,
      43,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,    -1,    -1,    -1,    -1,     3,    -1,    -1,     6,    -1,
      -1,    -1,    28,    -1,    30,    31,    32,    33,    34,    17,
      18,    19,    20,    -1,    40,    -1,    -1,    43,    -1,    27,
      -1,    -1,    30,    31,    32,    -1,    -1,    35,    36,    37,
      38,    39,     5,    -1,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    -1,    30,    31,    32,
      33,    34,    -1,     3,    -1,    38,     6,    40,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    17,    18,    19,
      20,    -1,    -1,    -1,    -1,     3,    -1,    27,     6,    -1,
      30,    31,    32,    -1,    -1,    35,    36,    37,    38,    17,
      18,    19,    20,    -1,    -1,    -1,    -1,     3,    -1,    27,
       6,    -1,    30,    31,    32,    -1,    -1,    35,    36,    37,
      38,    17,    18,    19,    20,    -1,    -1,    -1,    -1,     3,
      -1,    27,     6,    -1,    30,    31,    32,    -1,    -1,    35,
      36,    37,    38,    17,    18,    19,    20,    -1,    -1,    -1,
      -1,     3,    -1,    27,     6,    -1,    30,    31,    32,    -1,
      -1,    35,    36,    37,    38,    17,    18,    19,    20,    -1,
      -1,    -1,    -1,    -1,    -1,    27,    -1,    -1,    30,    31,
      32,    -1,    -1,    35,    36,    37,    38,     5,    -1,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      28,    -1,    30,    31,    32,    33,    34,    -1,    -1,    -1,
      38,    39,     5,    -1,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    -1,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    28,    29,    30,    31,    32,
      33,    34,    -1,    -1,    -1,    38,    28,    -1,    30,    31,
      32,    33,    34,    -1,    -1,    -1,    -1,    -1,    40,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      28,    -1,    30,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    28,    40,    30,    31,    32,    33,    34,    -1,    -1,
      -1,    -1,    -1,    40,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    -1,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    28,    -1,    30,    31,    32,
      33,    34,    -1,    -1,    -1,    -1,    28,    40,    30,    31,
      32,    33,    34,    -1,    -1,    -1,    -1,    -1,    40,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      28,    -1,    30,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    28,    40,    30,    31,    32,    33,    34,    -1,    -1,
      -1,    -1,    -1,    40,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    -1,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    28,    -1,    30,    31,    32,
      33,    34,    -1,    -1,    -1,    -1,    28,    40,    30,    31,
      32,    33,    34,    -1,    -1,    -1,    -1,    -1,    40,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      28,    -1,    30,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    28,    40,    30,    31,    32,    33,    34,    -1,    -1,
      -1,    -1,    -1,    40,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    -1,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    28,    -1,    30,    31,    32,
      33,    34,    -1,    -1,    -1,    -1,    28,    40,    30,    31,
      32,    33,    34,    -1,    -1,    -1,    -1,    -1,    40,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      28,    -1,    30,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    28,    40,    30,    31,    32,    33,    34,    -1,    -1,
      -1,    -1,    -1,    40,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    -1,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    28,    -1,    30,    31,    32,
      33,    34,    -1,    -1,    -1,    -1,    28,    40,    30,    31,
      32,    33,    34,    -1,    -1,    -1,    -1,    -1,    40,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      28,    -1,    30,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    28,    40,    30,    31,    32,    33,    34,    -1,    -1,
      -1,    -1,    -1,    40,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    -1,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    28,    -1,    30,    31,    32,
      33,    34,    -1,    -1,    -1,    -1,    28,    40,    30,    31,
      32,    33,    34,    -1,    -1,    -1,    -1,    -1,    40,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      28,    -1,    30,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    28,    40,    30,    31,    32,    33,    34,    -1,    -1,
      -1,    -1,    -1,    40,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    -1,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    28,    -1,    30,    31,    32,
      33,    34,    -1,    -1,    -1,    -1,    28,    40,    30,    31,
      32,    33,    34,    -1,    -1,    -1,    -1,    -1,    40,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      28,    -1,    30,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    28,    40,    30,    31,    32,    33,    34,    -1,    -1,
      -1,    -1,    -1,    40,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    -1,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    28,    -1,    30,    31,    32,
      33,    34,    -1,    -1,    -1,    -1,    28,    40,    30,    31,
      32,    33,    34,    -1,    -1,    -1,    -1,    -1,    40,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      28,    -1,    30,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    28,    40,    30,    31,    32,    33,    34,    -1,    -1,
      -1,    -1,    -1,    40,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    -1,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    28,    -1,    30,    31,    32,
      33,    34,    -1,    -1,    -1,    -1,    28,    40,    30,    31,
      32,    33,    34,    -1,    -1,    -1,    -1,    -1,    40,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      28,    -1,    30,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    28,    40,    30,    31,    32,    33,    34,    -1,    -1,
      -1,    -1,    -1,    40,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    -1,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    28,    -1,    30,    31,    32,
      33,    34,    -1,    -1,    -1,    -1,    28,    40,    30,    31,
      32,    33,    34,    -1,    -1,    -1,    -1,    -1,    40,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      28,    -1,    30,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    28,    40,    30,    31,    32,    33,    34,    -1,    -1,
      -1,    -1,    -1,    40,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    -1,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    28,    -1,    30,    31,    32,
      33,    34,    -1,    -1,    -1,    -1,    28,    40,    30,    31,
      32,    33,    34,    -1,    -1,    -1,    -1,    -1,    40,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      28,    -1,    30,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    28,    40,    30,    31,    32,    33,    34,    -1,    -1,
      -1,    -1,    -1,    40,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    -1,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    28,    -1,    30,    31,    32,
      33,    34,    -1,    -1,    -1,    -1,    28,    40,    30,    31,
      32,    33,    34,    -1,    -1,    -1,    -1,    -1,    40,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      28,    -1,    30,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    28,    40,    30,    31,    32,    33,    34,    -1,    -1,
      -1,    -1,    -1,    40,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    -1,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    28,    -1,    30,    31,    32,
      33,    34,    -1,    -1,    -1,    -1,    28,    40,    30,    31,
      32,    33,    34,    -1,    -1,    -1,    -1,    -1,    40,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      28,    -1,    30,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    28,    40,    30,    31,    32,    33,    34,    -1,    -1,
      -1,    -1,    -1,    40,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    -1,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    28,    -1,    30,    31,    32,
      33,    34,    -1,    -1,    -1,    -1,    28,    40,    30,    31,
      32,    33,    34,    -1,    -1,    -1,    -1,    -1,    40,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      28,    -1,    30,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    28,    40,    30,    31,    32,    33,    34,    -1,    -1,
      -1,    -1,    -1,    40,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    -1,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    28,    -1,    30,    31,    32,
      33,    34,    -1,    -1,    -1,    -1,    28,    40,    30,    31,
      32,    33,    34,    -1,    -1,    -1,    -1,    39,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    -1,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    -1,    -1,    28,
      -1,    30,    31,    32,    33,    34,    -1,    -1,    -1,    28,
      39,    30,    31,    32,    33,    34,    -1,    -1,    -1,    -1,
      39,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,    -1,    28,    -1,    30,    31,    32,    33,    34,    -1,
      -1,    -1,    28,    39,    30,    31,    32,    33,    34,    -1,
      -1,    -1,    -1,    39,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    -1,    28,    -1,    30,    31,    32,
      33,    34,    -1,    -1,    -1,    28,    39,    30,    31,    32,
      33,    34,    -1,    -1,    -1,    -1,    39,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    -1,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    -1,    -1,    28,    -1,
      30,    31,    32,    33,    34,    -1,    -1,    -1,    28,    39,
      30,    31,    32,    33,    34,    -1,    -1,    -1,    -1,    39,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      -1,    28,    -1,    30,    31,    32,    33,    34,    -1,    -1,
      -1,    28,    39,    30,    31,    32,    33,    34,    -1,    -1,
      -1,    -1,    39,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    -1,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    -1,    -1,    28,    -1,    30,    31,    32,    33,
      34,    -1,    -1,    -1,    28,    39,    30,    31,    32,    33,
      34,    -1,    -1,    -1,    -1,    39,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    -1,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    -1,    -1,    28,    -1,    30,
      31,    32,    33,    34,    -1,    -1,    -1,    28,    39,    30,
      31,    32,    33,    34,    -1,    -1,    -1,    -1,    39,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
      28,    -1,    30,    31,    32,    33,    34,    -1,    -1,    -1,
      28,    39,    30,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    39,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    -1,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    -1,    -1,    28,    -1,    30,    31,    32,    33,    34,
      -1,    -1,    -1,    28,    39,    30,    31,    32,    33,    34,
      -1,    -1,    -1,    -1,    39,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    -1,    28,    -1,    30,    31,
      32,    33,    34,    -1,    -1,    -1,    28,    39,    30,    31,
      32,    33,    34,    -1,    -1,    -1,    -1,    39,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    -1,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    -1,    -1,    28,
      -1,    30,    31,    32,    33,    34,    -1,    -1,    -1,    28,
      39,    30,    31,    32,    33,    34,    -1,    -1,    -1,    -1,
      39,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,    -1,    28,    -1,    30,    31,    32,    33,    34,    -1,
      -1,    -1,    28,    39,    30,    31,    32,    33,    34,    -1,
      -1,    -1,    -1,    39,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    -1,    28,    -1,    30,    31,    32,
      33,    34,    -1,    -1,    -1,    28,    39,    30,    31,    32,
      33,    34,    -1,    -1,    -1,    -1,    39,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    -1,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    -1,    -1,    28,    -1,
      30,    31,    32,    33,    34,    -1,    -1,    -1,    28,    39,
      30,    31,    32,    33,    34,    -1,    -1,    -1,    -1,    39,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      -1,    28,    -1,    30,    31,    32,    33,    34,    -1,    -1,
      -1,    28,    39,    30,    31,    32,    33,    34,    -1,    -1,
      -1,    -1,    39,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    -1,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    -1,    -1,    28,    -1,    30,    31,    32,    33,
      34,    -1,    -1,    -1,    28,    39,    30,    31,    32,    33,
      34,    -1,    -1,    -1,    -1,    39,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    -1,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    -1,    -1,    28,    -1,    30,
      31,    32,    33,    34,    -1,    -1,    -1,    28,    39,    30,
      31,    32,    33,    34,    -1,    -1,    -1,    -1,    39,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
      28,    -1,    30,    31,    32,    33,    34,    -1,    -1,    -1,
      28,    39,    30,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    39,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    -1,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    -1,    -1,    28,    -1,    30,    31,    32,    33,    34,
      -1,    -1,    -1,    28,    39,    30,    31,    32,    33,    34,
      -1,    -1,    -1,    -1,    39,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    -1,    28,    -1,    30,    31,
      32,    33,    34,    -1,    -1,    -1,    28,    39,    30,    31,
      32,    33,    34,    -1,    -1,    -1,    -1,    39,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    -1,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    -1,    -1,    28,
      -1,    30,    31,    32,    33,    34,    -1,    -1,    -1,    28,
      39,    30,    31,    32,    33,    34,    -1,    -1,    -1,    -1,
      39,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,    -1,    28,    -1,    30,    31,    32,    33,    34,    -1,
      -1,    -1,    28,    39,    30,    31,    32,    33,    34,    -1,
      -1,    -1,    -1,    39,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    -1,    28,    -1,    30,    31,    32,
      33,    34,    -1,    -1,    -1,    28,    39,    30,    31,    32,
      33,    34,    -1,    -1,    -1,    -1,    39,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    -1,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    -1,    -1,    28,    -1,
      30,    31,    32,    33,    34,    -1,    -1,    -1,    28,    39,
      30,    31,    32,    33,    34,    -1,    -1,    -1,    -1,    39,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      -1,    28,    -1,    30,    31,    32,    33,    34,    -1,    -1,
      -1,    28,    39,    30,    31,    32,    33,    34,    -1,    -1,
      -1,    -1,    39,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    -1,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    -1,    -1,    28,    -1,    30,    31,    32,    33,
      34,    -1,    -1,    -1,    28,    39,    30,    31,    32,    33,
      34,    -1,    -1,    -1,    -1,    39,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    -1,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    -1,    -1,    28,    -1,    30,
      31,    32,    33,    34,    -1,    -1,    -1,    28,    39,    30,
      31,    32,    33,    34,    -1,    -1,    -1,    -1,    39,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
      28,    -1,    30,    31,    32,    33,    34,    -1,    -1,    -1,
      28,    39,    30,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    39,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    -1,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    -1,    -1,    28,    -1,    30,    31,    32,    33,    34,
      -1,    -1,    -1,    28,    39,    30,    31,    32,    33,    34,
      -1,    -1,    -1,    -1,    39,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    -1,    28,    -1,    30,    31,
      32,    33,    34,    -1,    -1,    -1,    28,    39,    30,    31,
      32,    33,    34,    -1,    -1,    -1,    -1,    39,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    -1,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    -1,    -1,    28,
      -1,    30,    31,    32,    33,    34,    -1,    -1,    -1,    28,
      39,    30,    31,    32,    33,    34,    -1,    -1,    -1,    -1,
      39,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,    -1,    -1,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    28,    -1,    30,    31,    32,    33,    34,    -1,
      -1,    -1,    -1,    39,    28,    29,    30,    31,    32,    33,
      34,     7,     8,     9,    10,    11,    12,    13,    14,    15,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      -1,    -1,    28,    29,    30,    31,    32,    33,    34,    -1,
      -1,    28,    29,    30,    31,    32,    33,    34,     7,     8,
       9,    10,    11,    12,    13,    14,    15,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    -1,    -1,    -1,    28,
      29,    30,    31,    32,    33,    34,    -1,    -1,    28,    29,
      30,    31,    32,    33,    34,     7,     8,     9,    10,    11,
      12,    13,    14,    15,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    -1,    -1,    28,    29,    30,    31,
      32,    33,    34,    -1,    -1,    28,    29,    30,    31,    32,
      33,    34,     7,     8,     9,    10,    11,    12,    13,    14,
      15,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,    -1,    -1,    28,    29,    30,    31,    32,    33,    34,
      -1,    -1,    28,    29,    30,    31,    32,    33,    34,     7,
       8,     9,    10,    11,    12,    13,    14,    15,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    -1,    -1,    -1,
      28,    29,    30,    31,    32,    33,    34,    -1,    -1,    28,
      29,    30,    31,    32,    33,    34,     7,     8,     9,    10,
      11,    12,    13,    14,    15,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    -1,    -1,    28,    29,    30,
      31,    32,    33,    34,    -1,    -1,    28,    29,    30,    31,
      32,    33,    34,     7,     8,     9,    10,    11,    12,    13,
      14,    15,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    -1,    -1,    -1,    28,    29,    30,    31,    32,    33,
      34,    -1,    -1,    28,    29,    30,    31,    32,    33,    34,
       7,     8,     9,    10,    11,    12,    13,    14,    15,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
      -1,    28,    29,    30,    31,    32,    33,    34,    -1,    -1,
      28,    29,    30,    31,    32,    33,    34,     7,     8,     9,
      10,    11,    12,    13,    14,    15,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    -1,    -1,    -1,    28,    29,
      30,    31,    32,    33,    34,    -1,    -1,    28,    29,    30,
      31,    32,    33,    34,     7,     8,     9,    10,    11,    12,
      13,    14,    15,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    -1,    -1,    -1,    28,    29,    30,    31,    32,
      33,    34,    -1,    -1,    28,    29,    30,    31,    32,    33,
      34,     7,     8,     9,    10,    11,    12,    13,    14,    15,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      -1,    -1,    28,    29,    30,    31,    32,    33,    34,    -1,
      -1,    28,    29,    30,    31,    32,    33,    34,     7,     8,
       9,    10,    11,    12,    13,    14,    15,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    -1,    -1,    -1,    28,
      29,    30,    31,    32,    33,    34,    -1,    -1,    28,    29,
      30,    31,    32,    33,    34,     7,     8,     9,    10,    11,
      12,    13,    14,    15,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    -1,    -1,    28,    29,    30,    31,
      32,    33,    34,    -1,    -1,    28,    29,    30,    31,    32,
      33,    34,     7,     8,     9,    10,    11,    12,    13,    14,
      15,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,    -1,    -1,    28,    29,    30,    31,    32,    33,    34,
      -1,    -1,    28,    29,    30,    31,    32,    33,    34,     7,
       8,     9,    10,    11,    12,    13,    14,    15,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    -1,    -1,    -1,
      28,    29,    30,    31,    32,    33,    34,    -1,    -1,    28,
      29,    30,    31,    32,    33,    34,     7,     8,     9,    10,
      11,    12,    13,    14,    15,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    -1,    -1,    28,    29,    30,
      31,    32,    33,    34,    -1,    -1,    28,    29,    30,    31,
      32,    33,    34,     7,     8,     9,    10,    11,    12,    13,
      14,    15,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    -1,    -1,    -1,    28,    29,    30,    31,    32,    33,
      34,    -1,    -1,    28,    29,    30,    31,    32,    33,    34,
       7,     8,     9,    10,    11,    12,    13,    14,    15,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
      -1,    28,    29,    30,    31,    32,    33,    34,    -1,    -1,
      28,    29,    30,    31,    32,    33,    34,     7,     8,     9,
      10,    11,    12,    13,    14,    15,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    -1,    -1,    -1,    28,    29,
      30,    31,    32,    33,    34,    -1,    -1,    28,    29,    30,
      31,    32,    33,    34,     7,     8,     9,    10,    11,    12,
      13,    14,    15,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    -1,    -1,    -1,    28,    29,    30,    31,    32,
      33,    34,    -1,    -1,    28,    29,    30,    31,    32,    33,
      34,     7,     8,     9,    10,    11,    12,    13,    14,    15,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      -1,    -1,    28,    29,    30,    31,    32,    33,    34,    -1,
      -1,    28,    29,    30,    31,    32,    33,    34,     7,     8,
       9,    10,    11,    12,    13,    14,    15,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    -1,    -1,    -1,    28,
      29,    30,    31,    32,    33,    34,    -1,    -1,    28,    29,
      30,    31,    32,    33,    34,     7,     8,     9,    10,    11,
      12,    13,    14,    15,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    -1,    -1,    28,    29,    30,    31,
      32,    33,    34,    -1,    -1,    28,    29,    30,    31,    32,
      33,    34,     7,     8,     9,    10,    11,    12,    13,    14,
      15,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,    -1,    -1,    28,    29,    30,    31,    32,    33,    34,
      -1,    -1,    28,    29,    30,    31,    32,    33,    34,     7,
       8,     9,    10,    11,    12,    13,    14,    15,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    -1,    -1,    -1,
      28,    29,    30,    31,    32,    33,    34,    -1,    -1,    28,
      29,    30,    31,    32,    33,    34
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    46,    47,     0,     3,     4,     6,    17,    18,    19,
      20,    21,    22,    23,    24,    26,    27,    30,    31,    32,
      35,    36,    37,    38,    40,    48,    52,    55,    84,     5,
      16,    85,     3,    43,    62,    81,    84,    38,    38,    38,
      53,     1,    84,    84,    84,    84,    84,    84,    84,    84,
      49,    41,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    28,    30,    31,    32,    33,    34,    40,     1,    84,
      38,    86,    38,    56,     1,     3,    38,    60,     1,    84,
       1,    84,     1,    84,    38,    40,    40,    39,    50,    52,
      48,    84,     1,    84,     1,    84,     1,    84,     1,    84,
       1,    84,     1,    84,     1,    84,     1,    84,     1,    84,
       1,    84,     1,    84,     1,    84,     1,    84,    84,    87,
      57,    81,    83,    82,     3,     4,    69,    40,    39,    39,
      39,    39,    39,    39,     4,    40,    73,    80,    84,    51,
      42,    29,    43,    88,     1,    39,     1,    65,    69,    40,
      81,    81,    70,     3,    71,    39,    61,    52,    52,    58,
      52,    59,    52,     3,    84,    39,    80,    78,    50,    84,
      84,    41,    39,     4,    43,    72,    72,    72,    63,     1,
      25,    25,    52,    52,    44,    76,    54,    80,    88,    67,
       1,    41,     3,     4,     1,     1,    41,    52,    52,    84,
      81,    52,    80,    48,    40,    66,    72,     3,    48,    74,
      77,    42,    68,    48,    72,    42,    43,    79,    80,    48,
      42,    64,     3,    75,    80,    42,     1,    44,    80,    84,
      80,    79,     3,     6,    17,    18,    19,    20,    27,    30,
      31,    32,    35,    36,    37,    38,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    28,    30,    31,    32,    33,
      34,     4,    21,    22,    23,    24,    26,    40,    52,    55,
      84,     3,     6,    17,    18,    19,    20,    27,    30,    31,
      32,    35,    36,    37,    38,     3,     6,    17,    18,    19,
      20,    27,    30,    31,    32,    35,    36,    37,    38,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    28,    30,
      31,    32,    33,    34,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    28,    30,    31,    32,    33,    34,     4,
      21,    22,    23,    24,    26,    40,    55,    84,    40,     4,
      43,     3,     6,    17,    18,    19,    20,    27,    30,    31,
      32,    35,    36,    37,    38,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    28,    30,    31,    32,    33,    34,
       5,    16,    85,    84,    84,    84,    84,    84,    84,    84,
      84,    84,     1,    84,     1,    84,     1,    84,     1,    84,
       1,    84,     1,    84,     1,    84,     1,    84,     1,    84,
       1,    84,     1,    84,     1,    84,     1,    84,     3,    62,
      81,    38,    38,    38,    53,     1,    84,    49,    41,    40,
       5,    16,    85,    84,    84,    84,    84,    84,    84,    84,
      84,     5,    16,    85,    84,    84,    84,    84,    84,    84,
      84,    84,    84,     1,    84,     1,    84,     1,    84,     1,
      84,     1,    84,     1,    84,     1,    84,     1,    84,     1,
      84,     1,    84,     1,    84,     1,    84,     1,    84,    84,
       1,    84,     1,    84,     1,    84,     1,    84,     1,    84,
       1,    84,     1,    84,     1,    84,     1,    84,     1,    84,
       1,    84,     1,    84,     1,    84,     3,    62,    81,    38,
      38,    38,    53,     1,    84,    41,    40,    84,     3,     4,
       5,    16,    85,    84,    84,    84,    84,    84,    84,    84,
      84,    84,     1,    84,     1,    84,     1,    84,     1,    84,
       1,    84,     1,    84,     1,    84,     1,    84,     1,    84,
       1,    84,     1,    84,     1,    84,     1,    84,     1,    84,
      38,    86,    39,    29,    38,    56,    38,    60,     1,    84,
       1,    84,     1,    84,    38,    40,    40,    50,    52,    48,
       1,    84,    38,    86,    39,     1,    84,    38,    86,    39,
      29,    29,    38,    56,    38,    60,     1,    84,     1,    84,
       1,    84,    38,    40,    40,    48,    72,     3,     1,    84,
      38,    86,    39,    29,    87,    84,    57,    81,    69,    40,
      39,    39,    39,    39,    39,    39,    73,    51,    42,    87,
      87,    84,    84,    57,    81,    69,    40,    39,    39,    39,
      39,    39,    39,    73,    42,    72,    87,    84,     1,    39,
       1,    65,    69,    40,    39,    61,     4,    21,    22,    23,
      24,    26,    40,    52,    55,    84,    52,    58,    52,    59,
      52,    39,    50,     1,    39,     1,    39,     1,    65,    69,
      40,    39,    61,    52,    52,    58,    52,    59,    52,    39,
       1,    39,    41,    39,    63,     1,     3,    62,    81,    38,
      38,    38,    53,     1,    84,    25,    41,    40,    25,    52,
      52,    54,    41,    39,    63,     1,    25,    25,    52,    52,
      54,    67,     1,    41,    41,    38,    56,    38,    60,     1,
      84,     1,    84,     1,    84,    38,    40,    40,    52,    48,
      52,    52,    67,     1,    41,    41,    52,    52,    52,    48,
      40,    66,    48,    57,    81,    69,    40,    39,    39,    39,
      39,    39,    39,    73,    42,    48,    40,    66,    48,    42,
      68,    48,    42,     1,    65,    69,    40,    39,    61,    52,
      52,    58,    52,    59,    52,    39,    42,    68,    48,    42,
      48,    42,    64,    41,    39,    63,     1,    25,    25,    52,
      52,    54,    48,    42,    64,    42,     1,    67,     1,    41,
      41,    52,    52,    52,    42,     1,    48,    40,    66,    48,
      42,    68,    48,    42,    48,    42,    64,    42,     1
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    45,    47,    46,    48,    49,    48,    50,    51,    50,
      52,    52,    52,    52,    53,    54,    52,    52,    52,    55,
      52,    52,    56,    52,    57,    52,    52,    52,    58,    52,
      59,    52,    52,    60,    61,    52,    62,    63,    64,    52,
      66,    65,    67,    65,    68,    65,    69,    69,    70,    69,
      71,    69,    72,    72,    72,    74,    75,    73,    76,    77,
      73,    78,    73,    73,    79,    79,    80,    80,    81,    82,
      81,    83,    81,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    85,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    86,
      86,    87,    87,    88,    88
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     0,     0,     3,     0,     0,     3,
       5,     7,     5,     5,     0,     0,     7,     2,     3,     0,
       4,     1,     0,     5,     0,     5,     5,     7,     0,     6,
       0,     6,     3,     0,     0,     6,     0,     0,     0,    11,
       0,     6,     0,     5,     0,     7,     0,     3,     0,     4,
       0,     4,     0,     4,     3,     0,     0,     9,     0,     0,
       7,     0,     4,     2,     0,     5,     2,     1,     0,     0,
       4,     0,     4,     1,     1,     1,     1,     1,     2,     2,
       2,     2,     2,     2,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     5,
       3,     0,     3,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     0,     2,     0,     3
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
  YYUSE (yykind);
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
  case 2: /* $@1: %empty  */
#line 104 "sintatico.y"
      {
		insert(0, root, parents);
	}
#line 4293 "sintatico.tab.c"
    break;

  case 3: /* prog: $@1 cmds  */
#line 106 "sintatico.y"
               {
		removeAt(0, parents);
		// fprintf(stderr, "len parents: %lu\n", parents->size);
		// fprintf(stderr, "len root: %lu\n", root->children->size);
		depth_pre(max_level, root, max, NULL, NULL); // Pega a profundidade da árvore
		childrenCount = (int *) calloc(*max, sizeof(int));
		sprintf(root->value, "\033[4m%s\033[0m", (char *) root->value);
		depth_pre(print, root, childrenCount, NULL, NULL);
		free(childrenCount);
		depth_pos(free_values, root, NULL, NULL, NULL);
		delete_node(root);
	}
#line 4310 "sintatico.tab.c"
    break;

  case 4: /* cmds: %empty  */
#line 120 "sintatico.y"
             {}
#line 4316 "sintatico.tab.c"
    break;

  case 5: /* $@2: %empty  */
#line 121 "sintatico.y"
              {
		add_child((yyvsp[0].node), parents->first->value);
	}
#line 4324 "sintatico.tab.c"
    break;

  case 7: /* cmdstail: %empty  */
#line 126 "sintatico.y"
                 {}
#line 4330 "sintatico.tab.c"
    break;

  case 8: /* $@3: %empty  */
#line 127 "sintatico.y"
              {
		add_child((yyvsp[0].node), parents->first->value);
	}
#line 4338 "sintatico.tab.c"
    break;

  case 10: /* cmd: IF '(' exp ')' cmd  */
#line 132 "sintatico.y"
                                 {
		(yyval.node) = create_node(strdup("<if>"));
		add_child((yyvsp[-2].node), (yyval.node));
		add_child((yyvsp[0].node), (yyval.node));
	}
#line 4348 "sintatico.tab.c"
    break;

  case 11: /* cmd: IF '(' exp ')' cmd ELSE cmd  */
#line 137 "sintatico.y"
                                                 {
		(yyval.node) = create_node(strdup("<if-else>"));
		add_child((yyvsp[-4].node), (yyval.node));
		add_child((yyvsp[-2].node), (yyval.node));
		add_child((yyvsp[0].node), (yyval.node));
	}
#line 4359 "sintatico.tab.c"
    break;

  case 12: /* cmd: WHILE '(' exp ')' cmd  */
#line 143 "sintatico.y"
                                {
		(yyval.node) = create_node(strdup("<while>"));
		add_child((yyvsp[-2].node), (yyval.node));
		add_child((yyvsp[0].node), (yyval.node));
	}
#line 4369 "sintatico.tab.c"
    break;

  case 13: /* cmd: FORALL '(' exp ')' cmd  */
#line 148 "sintatico.y"
                                 {
		(yyval.node) = create_node(strdup("<forall>"));
		add_child((yyvsp[-2].node), (yyval.node));
		add_child((yyvsp[0].node), (yyval.node));
	}
#line 4379 "sintatico.tab.c"
    break;

  case 14: /* @4: %empty  */
#line 153 "sintatico.y"
              {
		(yyval.node) = create_node(strdup("<for>"));
		// fprintf(stderr, "Inserindo no for: %lu\n", parents->size);
		insert(0, (yyval.node), parents);
	}
#line 4389 "sintatico.tab.c"
    break;

  case 15: /* $@5: %empty  */
#line 157 "sintatico.y"
                          {
		removeAt(0, parents);
	}
#line 4397 "sintatico.tab.c"
    break;

  case 16: /* cmd: FOR @4 '(' forargs ')' $@5 cmd  */
#line 159 "sintatico.y"
              {
		(yyval.node) = (yyvsp[-5].node);
		add_child((yyvsp[0].node), (yyval.node));
	}
#line 4406 "sintatico.tab.c"
    break;

  case 17: /* cmd: exp ';'  */
#line 163 "sintatico.y"
                  {
		(yyval.node) = (yyvsp[-1].node);
	}
#line 4414 "sintatico.tab.c"
    break;

  case 18: /* cmd: RETURN exp ';'  */
#line 166 "sintatico.y"
                         {
		(yyval.node) = create_node(strdup("<return>"));
		add_child((yyvsp[-1].node), (yyval.node));
	}
#line 4423 "sintatico.tab.c"
    break;

  case 19: /* $@6: %empty  */
#line 170 "sintatico.y"
          {
		// fprintf(stderr, "Inserindo no {}: %lu\n", parents->size);
		insert(0, create_node(strdup("<block>")), parents);
	}
#line 4432 "sintatico.tab.c"
    break;

  case 20: /* cmd: $@6 '{' cmds '}'  */
#line 173 "sintatico.y"
                       {
		(yyval.node) = parents->first->value;
		removeAt(0, parents);
	}
#line 4441 "sintatico.tab.c"
    break;

  case 21: /* cmd: ';'  */
#line 177 "sintatico.y"
              {
		(yyval.node) = create_node(strdup("<emptycmd>"));
	}
#line 4449 "sintatico.tab.c"
    break;

  case 22: /* @7: %empty  */
#line 180 "sintatico.y"
                  {
		printf("AAAAAAAAAAAAA %s %s\n", (yyvsp[-1].node)->value, (yyvsp[0].node)->value);
		(yyval.node) = create_node(strdup("<declr>"));
		add_child((yyvsp[-1].node), (yyval.node));
		add_child((yyvsp[0].node), (yyval.node));
		// fprintf(stderr, "Inserindo no declr: %lu\n", parents->size);
		insert(0, (yyval.node), parents);
	}
#line 4462 "sintatico.tab.c"
    break;

  case 23: /* cmd: TYPE ID @7 idlist ';'  */
#line 187 "sintatico.y"
                     {
		(yyval.node) = (yyvsp[-2].node);
		removeAt(0, parents);
	}
#line 4471 "sintatico.tab.c"
    break;

  case 24: /* @8: %empty  */
#line 204 "sintatico.y"
                      {
		(yyval.node) = create_node(strdup("<declr_fn>"));
		add_child((yyvsp[-2].node), (yyval.node));
		add_child((yyvsp[-1].node), (yyval.node));

		node_t pars = create_node(strdup("<parlist>"));
		add_child(pars, (yyval.node));
		// fprintf(stderr, "Inserindo no declr_fn (%s): %lu\n", (char *) ((node_t) $2->children->first->value)->value, parents->size);
		insert(0, pars, parents); /* É removido dentro de declr_fntail */
	}
#line 4486 "sintatico.tab.c"
    break;

  case 25: /* cmd: TYPE ID '(' @8 declr_fntail  */
#line 213 "sintatico.y"
                       {
		(yyval.node) = (yyvsp[-1].node);
	}
#line 4494 "sintatico.tab.c"
    break;

  case 26: /* cmd: IF '(' error ')' cmd  */
#line 217 "sintatico.y"
                                        {
		(yyval.node) = create_node(strdup("<if>"));
		node_t err = create_node(ERR_TOKEN);
		add_child((yyvsp[-2].node), err);
		add_child(err, (yyval.node));
		add_child((yyvsp[0].node), (yyval.node));
		ssprintf(syn_errormsg, "Expected condition in '%s' statment", (yyvsp[-4].name));
	}
#line 4507 "sintatico.tab.c"
    break;

  case 27: /* cmd: IF '(' error ')' cmd ELSE cmd  */
#line 225 "sintatico.y"
                                                   {
		(yyval.node) = create_node(strdup("<if-else>"));
		node_t err = create_node(ERR_TOKEN);
		add_child((yyvsp[-4].node), err);
		add_child(err, (yyval.node));
		add_child((yyvsp[-2].node), (yyval.node));
		add_child((yyvsp[0].node), (yyval.node));
		ssprintf(syn_errormsg, "Expected condition in '%s' statment", (yyvsp[-6].name));
	}
#line 4521 "sintatico.tab.c"
    break;

  case 28: /* @9: %empty  */
#line 234 "sintatico.y"
                              {
		(yyval.node) = create_node(strdup("<while>"));
		node_t err = create_node(ERR_TOKEN);
		add_child((yyvsp[-1].node), err);
		add_child(err, (yyval.node));
		// add_child($5, $$);
		ssprintf(syn_errormsg, "Expected condition in '%s' statment", (yyvsp[-3].name));
	}
#line 4534 "sintatico.tab.c"
    break;

  case 29: /* cmd: WHILE '(' error ')' @9 cmd  */
#line 241 "sintatico.y"
              {
		(yyval.node) = (yyvsp[-1].node);
	}
#line 4542 "sintatico.tab.c"
    break;

  case 30: /* @10: %empty  */
#line 244 "sintatico.y"
                               {
		(yyval.node) = create_node(strdup("<forall>"));
		node_t err = create_node(ERR_TOKEN);
		add_child((yyvsp[-1].node), err);
		add_child(err, (yyval.node));
		// add_child($5, $$);
		ssprintf(syn_errormsg, "Expected in-expression in '%s' statment", (yyvsp[-3].name));
	}
#line 4555 "sintatico.tab.c"
    break;

  case 31: /* cmd: FORALL '(' error ')' @10 cmd  */
#line 251 "sintatico.y"
              {
		(yyval.node) = (yyvsp[-1].node);
		add_child((yyvsp[0].node), (yyval.node));
	}
#line 4564 "sintatico.tab.c"
    break;

  case 32: /* cmd: RETURN error ';'  */
#line 255 "sintatico.y"
                           {
		(yyval.node) = create_node(strdup("<return>"));
		node_t err = create_node(ERR_TOKEN);
		add_child((yyvsp[-1].node), err);
		add_child(err, (yyval.node));
		ssprintf(syn_errormsg, "Expected return expression");
	}
#line 4576 "sintatico.tab.c"
    break;

  case 33: /* @11: %empty  */
#line 262 "sintatico.y"
                      {
		(yyval.node) = create_node(strdup("<declr>"));
		add_child((yyvsp[-1].node), (yyval.node));
		add_child(create_node(ERR_TOKEN), (yyval.node));
		// fprintf(stderr, "Inserindo no declr_error: %lu\n", parents->size);
		insert(0, (yyval.node), parents);
	}
#line 4588 "sintatico.tab.c"
    break;

  case 34: /* $@12: %empty  */
#line 268 "sintatico.y"
              {
		removeAt(0, parents);
		YYERROR;
	}
#line 4597 "sintatico.tab.c"
    break;

  case 35: /* cmd: TYPE idlist @11 ';' $@12 error  */
#line 271 "sintatico.y"
                {
		(yyval.node) = (yyvsp[-3].node);
		ssprintf(syn_errormsg, "Expected identifier of type '%s' lookahead: %c", ((node_t) (yyvsp[-5].node)->children->first->value)->value, yychar);
	}
#line 4606 "sintatico.tab.c"
    break;

  case 36: /* @13: %empty  */
#line 275 "sintatico.y"
               {
		(yyval.node) = create_node(strdup("<declr_fn>"));
		add_child((yyvsp[0].node), (yyval.node));
		add_child(create_node(ERR_TOKEN), (yyval.node));

		node_t pars = create_node(strdup("<parlist>"));
		add_child(pars, (yyval.node));
		// fprintf(stderr, "Inserindo no declr_fn error: %lu\n", parents->size);
		insert(0, pars, parents);
	}
#line 4621 "sintatico.tab.c"
    break;

  case 37: /* @14: %empty  */
#line 284 "sintatico.y"
                          {
		removeAt(0, parents);
		(yyval.node) = (yyvsp[-3].node);
		node_t block = create_node(strdup("<block>"));
		add_child(block, (yyval.node));
		// fprintf(stderr, "Inserindo no declr_fn {} error: %lu\n", parents->size);
		insert(0, block, parents);
	}
#line 4634 "sintatico.tab.c"
    break;

  case 38: /* $@15: %empty  */
#line 291 "sintatico.y"
                       {
		removeAt(0, parents);
		YYERROR;
	}
#line 4643 "sintatico.tab.c"
    break;

  case 39: /* cmd: TYPE @13 '(' parlist ')' @14 '{' cmds '}' $@15 error  */
#line 294 "sintatico.y"
                {
		(yyval.node) = (yyvsp[-5].node);
		ssprintf(syn_errormsg, "Expected identifier of type '%s' in function declaration", (yyvsp[-10].node)->value);
	}
#line 4652 "sintatico.tab.c"
    break;

  case 40: /* $@16: %empty  */
#line 300 "sintatico.y"
                              {
		node_t block = create_node(strdup("<block>"));
		add_child(block, ((node_t) parents->first->value)->parent);
		// fprintf(stderr, "Inserindo no declr_fn {}: %lu\n", parents->size);
		removeAt(0, parents); /* Inserido no que vem antes */
		insert(0, block, parents);
	}
#line 4664 "sintatico.tab.c"
    break;

  case 41: /* declr_fntail: parlist ')' '{' $@16 cmds '}'  */
#line 306 "sintatico.y"
                   {
		removeAt(0, parents);
	}
#line 4672 "sintatico.tab.c"
    break;

  case 42: /* $@17: %empty  */
#line 310 "sintatico.y"
                    {
		node_t block = create_node(strdup("<block>"));
		add_child(block, ((node_t) parents->first->value)->parent);
		// fprintf(stderr, "Inserindo no declr_fn error 1 {}: %lu\n", parents->size);
		node_t err = create_node(ERR_TOKEN);
		add_child(err, parents->first->value);
		add_child((yyvsp[-1].node), err);
		removeAt(0, parents); /* Inserido no que vem antes */
		insert(0, block, parents);
		ssprintf(syn_errormsg, "Expected a ')'");
		// printf("----------(%s) (%d)\n", $<node>1->value, $<node>1->id);
	}
#line 4689 "sintatico.tab.c"
    break;

  case 43: /* declr_fntail: error '{' $@17 cmds '}'  */
#line 321 "sintatico.y"
                   {
		removeAt(0, parents);
	}
#line 4697 "sintatico.tab.c"
    break;

  case 44: /* $@18: %empty  */
#line 324 "sintatico.y"
                                {
		node_t err = create_node(ERR_TOKEN);
		node_t block = create_node(strdup("<block>"));
		add_child(err, block);
		add_child(block, ((node_t) parents->first->value)->parent);
		// add_child($<node>3, block);
		// fprintf(stderr, "Inserindo no declr_fn error 2 {}: %lu\n", parents->size);
		removeAt(0, parents); /* Inserido no que vem antes */
		insert(0, err, parents);
		ssprintf(syn_errormsg, "Expected a '{'");
	}
#line 4713 "sintatico.tab.c"
    break;

  case 45: /* declr_fntail: parlist ')' error ';' $@18 cmds '}'  */
#line 334 "sintatico.y"
                   {
		removeAt(0, parents);
	}
#line 4721 "sintatico.tab.c"
    break;

  case 46: /* parlist: %empty  */
#line 339 "sintatico.y"
                {}
#line 4727 "sintatico.tab.c"
    break;

  case 47: /* parlist: TYPE ID partail  */
#line 340 "sintatico.y"
                          {
		add_child((yyvsp[-2].node), parents->first->value);
		add_child((yyvsp[-1].node), parents->first->value);
	}
#line 4736 "sintatico.tab.c"
    break;

  case 48: /* $@19: %empty  */
#line 345 "sintatico.y"
             { /* Missing type */
		add_child(create_node(ERR_TOKEN), parents->first->value);
		add_child((yyvsp[0].node), parents->first->value);
		YYERROR;
	}
#line 4746 "sintatico.tab.c"
    break;

  case 49: /* parlist: ID $@19 partail error  */
#line 349 "sintatico.y"
                        {
		ssprintf(syn_errormsg, "Expected a type for '%s'", (char *) ((node_t) (yyvsp[-3].node)->children->first->value)->value);
	}
#line 4754 "sintatico.tab.c"
    break;

  case 50: /* $@20: %empty  */
#line 352 "sintatico.y"
               { /* Missing id */
		add_child((yyvsp[0].node), parents->first->value);
		add_child(create_node(ERR_TOKEN), parents->first->value);
		YYERROR;
	}
#line 4764 "sintatico.tab.c"
    break;

  case 51: /* parlist: TYPE $@20 partail error  */
#line 356 "sintatico.y"
                        {
		ssprintf(syn_errormsg, "Expected an identifier of type '%s'", (char *) ((node_t) (yyvsp[-3].node)->children->first->value)->value);
	}
#line 4772 "sintatico.tab.c"
    break;

  case 52: /* partail: %empty  */
#line 361 "sintatico.y"
                {}
#line 4778 "sintatico.tab.c"
    break;

  case 53: /* partail: ',' TYPE ID partail  */
#line 362 "sintatico.y"
                              {
		add_child((yyvsp[-2].node), parents->first->value);
		add_child((yyvsp[-1].node), parents->first->value);
	}
#line 4787 "sintatico.tab.c"
    break;

  case 54: /* partail: TYPE ID partail  */
#line 367 "sintatico.y"
                          {
		add_child((yyvsp[-2].node), parents->first->value);
		add_child((yyvsp[-1].node), parents->first->value);
		ssprintf(syn_errormsg, "Expected a ','");
	}
#line 4797 "sintatico.tab.c"
    break;

  case 55: /* $@21: %empty  */
#line 380 "sintatico.y"
                         {
		node_t arg = create_node(strdup("<declr_init>"));
		add_child((yyvsp[-3].node), arg);
		add_child((yyvsp[-2].node), arg);
		add_child((yyvsp[0].node), arg);

		add_child(arg, parents->first->value);
		// fprintf(stderr, "Inserindo no for arg 1: %lu\n", parents->size);
		insert(0, arg, parents);
	}
#line 4812 "sintatico.tab.c"
    break;

  case 56: /* $@22: %empty  */
#line 389 "sintatico.y"
                       { /* TODO: Tem que poder fazer várias declarações no for */
		removeAt(0, parents);
	}
#line 4820 "sintatico.tab.c"
    break;

  case 58: /* $@23: %empty  */
#line 392 "sintatico.y"
                  {
		node_t arg = create_node(strdup("<declr>"));
		add_child((yyvsp[-1].node), arg);
		add_child((yyvsp[0].node), arg);

		add_child(arg, parents->first->value);
		// fprintf(stderr, "Inserindo no for arg 1: %lu\n", parents->size);
		insert(0, arg, parents);
	}
#line 4834 "sintatico.tab.c"
    break;

  case 59: /* $@24: %empty  */
#line 400 "sintatico.y"
                 {
		removeAt(0, parents);
	}
#line 4842 "sintatico.tab.c"
    break;

  case 61: /* $@25: %empty  */
#line 403 "sintatico.y"
              {
		add_child((yyvsp[0].node), parents->first->value);
	}
#line 4850 "sintatico.tab.c"
    break;

  case 63: /* forargs: fortail fortail  */
#line 406 "sintatico.y"
                          {
		node_t exp = create_node(strdup("<emptyexp>"));
		exp->parent = parents->first->value;
		insert(0, exp, parents->first->value);
	}
#line 4860 "sintatico.tab.c"
    break;

  case 65: /* fordeclrlist: ',' ID '=' exp fordeclrlist  */
#line 414 "sintatico.y"
                                      {
		add_child((yyvsp[-3].node), parents->first->value);
		add_child((yyvsp[-1].node), parents->first->value);
	}
#line 4869 "sintatico.tab.c"
    break;

  case 66: /* fortail: ';' exp  */
#line 420 "sintatico.y"
                 {
		add_child((yyvsp[0].node), parents->first->value);
	}
#line 4877 "sintatico.tab.c"
    break;

  case 67: /* fortail: ';'  */
#line 423 "sintatico.y"
              {
		add_child(create_node(strdup("<emptyexp>")), parents->first->value);
	}
#line 4885 "sintatico.tab.c"
    break;

  case 69: /* $@26: %empty  */
#line 429 "sintatico.y"
                 {
		add_child((yyvsp[0].node), parents->first->value);
	}
#line 4893 "sintatico.tab.c"
    break;

  case 71: /* $@27: %empty  */
#line 432 "sintatico.y"
                    {
		node_t err = create_node(ERR_TOKEN);
		add_child(err, parents->first->value);
		add_child((yyvsp[0].node), err);
		ssprintf(syn_errormsg, "Expected an indentifier");
	}
#line 4904 "sintatico.tab.c"
    break;

  case 73: /* exp: INT  */
#line 440 "sintatico.y"
         {
		node_t aux = create_node(strdup("<int>"));
		add_child((yyvsp[0].node), aux);
		(yyval.node) = aux;
	}
#line 4914 "sintatico.tab.c"
    break;

  case 74: /* exp: FLOAT  */
#line 445 "sintatico.y"
                {
		node_t aux = create_node(strdup("<float>"));
		add_child((yyvsp[0].node), aux);
		(yyval.node) = aux;
	}
#line 4924 "sintatico.tab.c"
    break;

  case 75: /* exp: EMPTY  */
#line 450 "sintatico.y"
                {
		(yyval.node) = create_node(strdup("<empty>"));
	}
#line 4932 "sintatico.tab.c"
    break;

  case 76: /* exp: STRING  */
#line 453 "sintatico.y"
                 {
		node_t aux = create_node(strdup("<string>"));
		add_child((yyvsp[0].node), aux);
		(yyval.node) = aux;
	}
#line 4942 "sintatico.tab.c"
    break;

  case 77: /* exp: CHAR  */
#line 458 "sintatico.y"
               {
		node_t aux = create_node(strdup("<char>"));
		add_child((yyvsp[0].node), aux);
		(yyval.node) = aux;
	}
#line 4952 "sintatico.tab.c"
    break;

  case 78: /* exp: ID OPPOS  */
#line 463 "sintatico.y"
                   {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<oppos>"));
		add_child((yyvsp[0].node), op);
		add_child((yyvsp[-1].node), exp);
		add_child(op, exp);
		(yyval.node) = exp;
	}
#line 4965 "sintatico.tab.c"
    break;

  case 79: /* exp: '*' exp  */
#line 471 "sintatico.y"
                              {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opuni>"));
		add_child((yyvsp[-1].node), op);
		add_child(op, exp);
		add_child((yyvsp[0].node), exp);
		(yyval.node) = exp;
	}
#line 4978 "sintatico.tab.c"
    break;

  case 80: /* exp: '+' exp  */
#line 479 "sintatico.y"
                              {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opuni>"));
		add_child((yyvsp[-1].node), op);
		add_child(op, exp);
		add_child((yyvsp[0].node), exp);
		(yyval.node) = exp;
	}
#line 4991 "sintatico.tab.c"
    break;

  case 81: /* exp: '-' exp  */
#line 487 "sintatico.y"
                              {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opuni>"));
		add_child((yyvsp[-1].node), op);
		add_child(op, exp);
		add_child((yyvsp[0].node), exp);
		(yyval.node) = exp;
	}
#line 5004 "sintatico.tab.c"
    break;

  case 82: /* exp: '!' exp  */
#line 495 "sintatico.y"
                              {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opuni>"));
		add_child((yyvsp[-1].node), op);
		add_child(op, exp);
		add_child((yyvsp[0].node), exp);
		(yyval.node) = exp;
	}
#line 5017 "sintatico.tab.c"
    break;

  case 83: /* exp: '~' exp  */
#line 503 "sintatico.y"
                              {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opuni>"));
		add_child((yyvsp[-1].node), op);
		add_child(op, exp);
		add_child((yyvsp[0].node), exp);
		(yyval.node) = exp;
	}
#line 5030 "sintatico.tab.c"
    break;

  case 84: /* exp: '&' exp  */
#line 511 "sintatico.y"
                              {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opuni>"));
		add_child((yyvsp[-1].node), op);
		add_child(op, exp);
		add_child((yyvsp[0].node), exp);
		(yyval.node) = exp;
	}
#line 5043 "sintatico.tab.c"
    break;

  case 85: /* exp: OPUNI exp  */
#line 519 "sintatico.y"
                    {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opuni>"));
		add_child((yyvsp[-1].node), op);
		add_child(op, exp);
		add_child((yyvsp[0].node), exp);
		(yyval.node) = exp;
	}
#line 5056 "sintatico.tab.c"
    break;

  case 86: /* exp: exp '*' exp  */
#line 527 "sintatico.y"
                      {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child((yyvsp[-1].node), op);
		add_child((yyvsp[-2].node), exp);
		add_child(op, exp);
		add_child((yyvsp[0].node), exp);
		(yyval.node) = exp;
	}
#line 5070 "sintatico.tab.c"
    break;

  case 87: /* exp: exp '/' exp  */
#line 536 "sintatico.y"
                      {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child((yyvsp[-1].node), op);
		add_child((yyvsp[-2].node), exp);
		add_child(op, exp);
		add_child((yyvsp[0].node), exp);
		(yyval.node) = exp;
	}
#line 5084 "sintatico.tab.c"
    break;

  case 88: /* exp: exp '%' exp  */
#line 545 "sintatico.y"
                      {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child((yyvsp[-1].node), op);
		add_child((yyvsp[-2].node), exp);
		add_child(op, exp);
		add_child((yyvsp[0].node), exp);
		(yyval.node) = exp;
	}
#line 5098 "sintatico.tab.c"
    break;

  case 89: /* exp: exp '+' exp  */
#line 554 "sintatico.y"
                      {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child((yyvsp[-1].node), op);
		add_child((yyvsp[-2].node), exp);
		add_child(op, exp);
		add_child((yyvsp[0].node), exp);
		(yyval.node) = exp;
	}
#line 5112 "sintatico.tab.c"
    break;

  case 90: /* exp: exp '-' exp  */
#line 563 "sintatico.y"
                      {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child((yyvsp[-1].node), op);
		add_child((yyvsp[-2].node), exp);
		add_child(op, exp);
		add_child((yyvsp[0].node), exp);
		(yyval.node) = exp;
	}
#line 5126 "sintatico.tab.c"
    break;

  case 91: /* exp: exp IN exp  */
#line 572 "sintatico.y"
                     {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child((yyvsp[-1].node), op);
		add_child((yyvsp[-2].node), exp);
		add_child(op, exp);
		add_child((yyvsp[0].node), exp);
		(yyval.node) = exp;
	}
#line 5140 "sintatico.tab.c"
    break;

  case 92: /* exp: exp OPBIN3 exp  */
#line 581 "sintatico.y"
                         {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child((yyvsp[-1].node), op);
		add_child((yyvsp[-2].node), exp);
		add_child(op, exp);
		add_child((yyvsp[0].node), exp);
		(yyval.node) = exp;
	}
#line 5154 "sintatico.tab.c"
    break;

  case 93: /* exp: exp OPBIN4 exp  */
#line 590 "sintatico.y"
                         {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child((yyvsp[-1].node), op);
		add_child((yyvsp[-2].node), exp);
		add_child(op, exp);
		add_child((yyvsp[0].node), exp);
		(yyval.node) = exp;
	}
#line 5168 "sintatico.tab.c"
    break;

  case 94: /* exp: exp OPBIN5 exp  */
#line 599 "sintatico.y"
                         {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child((yyvsp[-1].node), op);
		add_child((yyvsp[-2].node), exp);
		add_child(op, exp);
		add_child((yyvsp[0].node), exp);
		(yyval.node) = exp;
	}
#line 5182 "sintatico.tab.c"
    break;

  case 95: /* exp: exp OPBIN6 exp  */
#line 608 "sintatico.y"
                         {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child((yyvsp[-1].node), op);
		add_child((yyvsp[-2].node), exp);
		add_child(op, exp);
		add_child((yyvsp[0].node), exp);
		(yyval.node) = exp;
	}
#line 5196 "sintatico.tab.c"
    break;

  case 96: /* exp: exp OPBIN7 exp  */
#line 617 "sintatico.y"
                         {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child((yyvsp[-1].node), op);
		add_child((yyvsp[-2].node), exp);
		add_child(op, exp);
		add_child((yyvsp[0].node), exp);
		(yyval.node) = exp;
	}
#line 5210 "sintatico.tab.c"
    break;

  case 97: /* exp: exp OPBIN8 exp  */
#line 626 "sintatico.y"
                         {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child((yyvsp[-1].node), op);
		add_child((yyvsp[-2].node), exp);
		add_child(op, exp);
		add_child((yyvsp[0].node), exp);
		(yyval.node) = exp;
	}
#line 5224 "sintatico.tab.c"
    break;

  case 98: /* exp: exp OPBIN9 exp  */
#line 635 "sintatico.y"
                         {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child((yyvsp[-1].node), op);
		add_child((yyvsp[-2].node), exp);
		add_child(op, exp);
		add_child((yyvsp[0].node), exp);
		(yyval.node) = exp;
	}
#line 5238 "sintatico.tab.c"
    break;

  case 99: /* exp: exp '?' exp ':' exp  */
#line 644 "sintatico.y"
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
#line 5256 "sintatico.tab.c"
    break;

  case 100: /* exp: ID OPASSIGN exp  */
#line 657 "sintatico.y"
                          {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opassign>"));
		add_child((yyvsp[-1].node), op);
		add_child((yyvsp[-2].node), exp);
		add_child(op, exp);
		add_child((yyvsp[0].node), exp);
		(yyval.node) = exp;
	}
#line 5270 "sintatico.tab.c"
    break;

  case 101: /* @28: %empty  */
#line 666 "sintatico.y"
             {
		(yyval.node) = create_node(strdup("<fn>"));
		add_child((yyvsp[0].node), (yyval.node));
		// fprintf(stderr, "Inserindo no fn id: %lu\n", parents->size);
		insert(0, (yyval.node), parents);
	}
#line 5281 "sintatico.tab.c"
    break;

  case 102: /* exp: ID @28 fntail  */
#line 671 "sintatico.y"
                 {
		(yyval.node) = (yyvsp[-1].node);
		removeAt(0, parents);
	}
#line 5290 "sintatico.tab.c"
    break;

  case 103: /* exp: ID  */
#line 675 "sintatico.y"
             {
		(yyval.node) = (yyvsp[0].node);
	}
#line 5298 "sintatico.tab.c"
    break;

  case 104: /* exp: '(' exp ')'  */
#line 678 "sintatico.y"
                      {
		(yyval.node) = create_node(strdup("<exp>"));
		add_child((yyvsp[-1].node), (yyval.node));
	}
#line 5307 "sintatico.tab.c"
    break;

  case 105: /* exp: exp '*' error  */
#line 683 "sintatico.y"
                        {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child((yyvsp[-1].node), op);
		add_child((yyvsp[-2].node), exp);
		add_child(op, exp);
		node_t err = create_node(ERR_TOKEN);
		add_child((yyvsp[0].node), err);
		add_child(err, exp);
		(yyval.node) = exp;
		sprintf(syn_errormsg, "Expected expression while processing '*'");
	}
#line 5324 "sintatico.tab.c"
    break;

  case 106: /* exp: exp '/' error  */
#line 695 "sintatico.y"
                        {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child((yyvsp[-1].node), op);
		add_child((yyvsp[-2].node), exp);
		add_child(op, exp);
		node_t err = create_node(ERR_TOKEN);
		add_child((yyvsp[0].node), err);
		add_child(err, exp);
		(yyval.node) = exp;
		sprintf(syn_errormsg, "Expected expression while processing '/'");
	}
#line 5341 "sintatico.tab.c"
    break;

  case 107: /* exp: exp '%' error  */
#line 707 "sintatico.y"
                        {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child((yyvsp[-1].node), op);
		add_child((yyvsp[-2].node), exp);
		add_child(op, exp);
		node_t err = create_node(ERR_TOKEN);
		add_child((yyvsp[0].node), err);
		add_child(err, exp);
		(yyval.node) = exp;
		sprintf(syn_errormsg, "Expected expression while processing '%%'");
	}
#line 5358 "sintatico.tab.c"
    break;

  case 108: /* exp: exp '+' error  */
#line 719 "sintatico.y"
                        {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child((yyvsp[-1].node), op);
		add_child((yyvsp[-2].node), exp);
		add_child(op, exp);
		node_t err = create_node(ERR_TOKEN);
		add_child((yyvsp[0].node), err);
		add_child(err, exp);
		(yyval.node) = exp;
		sprintf(syn_errormsg, "Expected expression while processing '+'");
	}
#line 5375 "sintatico.tab.c"
    break;

  case 109: /* exp: exp '-' error  */
#line 731 "sintatico.y"
                        {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child((yyvsp[-1].node), op);
		add_child((yyvsp[-2].node), exp);
		add_child(op, exp);
		node_t err = create_node(ERR_TOKEN);
		add_child((yyvsp[0].node), err);
		add_child(err, exp);
		(yyval.node) = exp;
		sprintf(syn_errormsg, "Expected expression while processing '-'");
	}
#line 5392 "sintatico.tab.c"
    break;

  case 110: /* exp: exp OPBIN3 error  */
#line 743 "sintatico.y"
                           {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child((yyvsp[-1].node), op);
		add_child((yyvsp[-2].node), exp);
		add_child(op, exp);
		node_t err = create_node(ERR_TOKEN);
		add_child((yyvsp[0].node), err);
		add_child(err, exp);
		(yyval.node) = exp;
		ssprintf(syn_errormsg, "Expected expression while processing '%s'", (yyvsp[-1].node)->value);
	}
#line 5409 "sintatico.tab.c"
    break;

  case 111: /* exp: exp OPBIN4 error  */
#line 755 "sintatico.y"
                           {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child((yyvsp[-1].node), op);
		add_child((yyvsp[-2].node), exp);
		add_child(op, exp);
		node_t err = create_node(ERR_TOKEN);
		add_child((yyvsp[0].node), err);
		add_child(err, exp);
		(yyval.node) = exp;
		ssprintf(syn_errormsg, "Expected expression while processing '%s'", (yyvsp[-1].node)->value);
	}
#line 5426 "sintatico.tab.c"
    break;

  case 112: /* exp: exp OPBIN5 error  */
#line 767 "sintatico.y"
                           {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child((yyvsp[-1].node), op);
		add_child((yyvsp[-2].node), exp);
		add_child(op, exp);
		node_t err = create_node(ERR_TOKEN);
		add_child((yyvsp[0].node), err);
		add_child(err, exp);
		(yyval.node) = exp;
		ssprintf(syn_errormsg, "Expected expression while processing '%s'", (yyvsp[-1].node)->value);
	}
#line 5443 "sintatico.tab.c"
    break;

  case 113: /* exp: exp OPBIN6 error  */
#line 779 "sintatico.y"
                           {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child((yyvsp[-1].node), op);
		add_child((yyvsp[-2].node), exp);
		add_child(op, exp);
		node_t err = create_node(ERR_TOKEN);
		add_child((yyvsp[0].node), err);
		add_child(err, exp);
		(yyval.node) = exp;
		ssprintf(syn_errormsg, "Expected expression while processing '%s'", (yyvsp[-1].node)->value);
	}
#line 5460 "sintatico.tab.c"
    break;

  case 114: /* exp: exp OPBIN7 error  */
#line 791 "sintatico.y"
                           {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child((yyvsp[-1].node), op);
		add_child((yyvsp[-2].node), exp);
		add_child(op, exp);
		node_t err = create_node(ERR_TOKEN);
		add_child((yyvsp[0].node), err);
		add_child(err, exp);
		(yyval.node) = exp;
		ssprintf(syn_errormsg, "Expected expression while processing '%s'", (yyvsp[-1].node)->value);
	}
#line 5477 "sintatico.tab.c"
    break;

  case 115: /* exp: exp OPBIN8 error  */
#line 803 "sintatico.y"
                           {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child((yyvsp[-1].node), op);
		add_child((yyvsp[-2].node), exp);
		add_child(op, exp);
		node_t err = create_node(ERR_TOKEN);
		add_child((yyvsp[0].node), err);
		add_child(err, exp);
		(yyval.node) = exp;
		ssprintf(syn_errormsg, "Expected expression while processing '%s'", (yyvsp[-1].node)->value);
	}
#line 5494 "sintatico.tab.c"
    break;

  case 116: /* exp: exp OPBIN9 error  */
#line 815 "sintatico.y"
                           {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child((yyvsp[-1].node), op);
		add_child((yyvsp[-2].node), exp);
		add_child(op, exp);
		node_t err = create_node(ERR_TOKEN);
		add_child((yyvsp[0].node), err);
		add_child(err, exp);
		(yyval.node) = exp;
		ssprintf(syn_errormsg, "Expected expression while processing '%s'", (yyvsp[-1].node)->value);
	}
#line 5511 "sintatico.tab.c"
    break;

  case 117: /* exp: exp OPBIN10 error  */
#line 827 "sintatico.y"
                            {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opbin>"));
		add_child((yyvsp[-1].node), op);
		add_child((yyvsp[-2].node), exp);
		add_child(op, exp);
		node_t err = create_node(ERR_TOKEN);
		add_child((yyvsp[0].node), err);
		add_child(err, exp);
		(yyval.node) = exp;
		ssprintf(syn_errormsg, "Expected expression while processing '%s'", (yyvsp[-1].node)->value);
	}
#line 5528 "sintatico.tab.c"
    break;

  case 118: /* exp: ID OPASSIGN error  */
#line 839 "sintatico.y"
                            {
		node_t exp = create_node(strdup("<exp>"));
		node_t op = create_node(strdup("<opassign>"));
		add_child((yyvsp[-1].node), op);
		add_child((yyvsp[-2].node), exp);
		add_child(op, exp);
		node_t err = create_node(ERR_TOKEN);
		add_child((yyvsp[0].node), err);
		add_child(err, exp);
		(yyval.node) = exp;
		ssprintf(syn_errormsg, "Expected expression in '%s %s'", ((node_t) (yyvsp[-2].node)->children->first->value)->value, (yyvsp[-1].node)->value);
	}
#line 5545 "sintatico.tab.c"
    break;

  case 120: /* fntail: '(' arglist error  */
#line 854 "sintatico.y"
                            {
		/* TODO: Incluir algo na árvore? */
		ssprintf(syn_errormsg, "Expected ')'");
	}
#line 5554 "sintatico.tab.c"
    break;

  case 121: /* arglist: %empty  */
#line 860 "sintatico.y"
                {}
#line 5560 "sintatico.tab.c"
    break;

  case 122: /* arglist: exp argtail  */
#line 861 "sintatico.y"
                      {
		add_child((yyvsp[-1].node), parents->first->value);
	}
#line 5568 "sintatico.tab.c"
    break;

  case 123: /* argtail: %empty  */
#line 866 "sintatico.y"
                {}
#line 5574 "sintatico.tab.c"
    break;

  case 124: /* argtail: ',' exp argtail  */
#line 867 "sintatico.y"
                          {
		add_child((yyvsp[-1].node), parents->first->value);
	}
#line 5582 "sintatico.tab.c"
    break;


#line 5586 "sintatico.tab.c"

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

#line 872 "sintatico.y"


int yyerror(int *max, int *childrenCount, char *s) {
	if (*syn_errormsg) {
		fprintf(stderr, ERR_TEMPLATE, syn_errormsg);
	}
	fprintf(stderr, ERR_LOCATION, filename, lnum, lcol);
	*syn_errormsg = '\0';
	return 0;
}

int main(int argc, char **argv) {
	if (argc < 2) {
		fprintf(stderr, "No input file\n");
		exit(EXIT_FAILURE);
	}
	setlocale(LC_ALL, "");

	strcpy(filename, argv[1]);
	root = create_node(filename);
	parents = create_list();
	int max, *childrenCount = NULL;

	yyin = fopen(argv[1], "r");

	if (yyparse(&max, childrenCount)) {
		fprintf(stderr, "Unhandled error while parsing\n");
		delete_list(parents);
		exit(EXIT_FAILURE);
	}

	if (*syn_errormsg) {
		fprintf(stderr, ERR_TEMPLATE, syn_errormsg);
	}
	return 0;
}

void ssprintf(char *target, char *template, ...) {
	va_list ap;
	va_start(ap, template);
	vsprintf(target, template, ap);
	va_end(ap);
}

void print(node_t node, void *data) {
	int *childrenCount = (int *) data;

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
	printf("%s\n", (char *) node->value);
}

void max_level(node_t node, void *data) {
	int *max = (int *) data;
	int l = level(node);
	if (*max < l) *max = l;
}

void free_values(node_t node, void *data) {
	if (strcmp(node->value, ERR_TOKEN) && strcmp(node->value, filename)) {
		printf("Liberando (%d) (%s) ", node->id, (char *) node->value);
		if (node->parent != NULL)
			printf("Pai (%d) (%s)\n", node->parent->id, (char *) node->parent->value);
		else
			printf("\n");
		free(node->value);
	} else {
		printf("Não liberando (%d) (%s) ", node->id, (char *) node->value);
		if (node->parent != NULL)
			printf("Pai (%d) (%s)\n", node->parent->id, (char *) node->parent->value);
		else
			printf("\n");
	}
}
