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
#line 1 "sintatico.y"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "lex.yy.h"
#include "tree.h"
#include <assert.h>

#define NAMESIZE 32768

int yylex();
int yyerror(char *s);
void ssprintf(char *target, char *template, ...);
void print(node_t node, void *data);

char filename[512];
char syn_errormsg[NAMESIZE];
extern int lnum, lcol;
node_t root;

#line 93 "sintatico.tab.c"

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
  YYSYMBOL_IF = 5,                         /* IF  */
  YYSYMBOL_WHILE = 6,                      /* WHILE  */
  YYSYMBOL_FORALL = 7,                     /* FORALL  */
  YYSYMBOL_FOR = 8,                        /* FOR  */
  YYSYMBOL_ELSE = 9,                       /* ELSE  */
  YYSYMBOL_RETURN = 10,                    /* RETURN  */
  YYSYMBOL_OPPOS = 11,                     /* OPPOS  */
  YYSYMBOL_OPUNI = 12,                     /* OPUNI  */
  YYSYMBOL_OPTER = 13,                     /* OPTER  */
  YYSYMBOL_OPBIN3 = 14,                    /* OPBIN3  */
  YYSYMBOL_OPBIN4 = 15,                    /* OPBIN4  */
  YYSYMBOL_OPBIN5 = 16,                    /* OPBIN5  */
  YYSYMBOL_OPBIN6 = 17,                    /* OPBIN6  */
  YYSYMBOL_OPBIN7 = 18,                    /* OPBIN7  */
  YYSYMBOL_OPBIN8 = 19,                    /* OPBIN8  */
  YYSYMBOL_OPBIN9 = 20,                    /* OPBIN9  */
  YYSYMBOL_OPBIN10 = 21,                   /* OPBIN10  */
  YYSYMBOL_OPASSIGN = 22,                  /* OPASSIGN  */
  YYSYMBOL_STRING = 23,                    /* STRING  */
  YYSYMBOL_CHAR = 24,                      /* CHAR  */
  YYSYMBOL_INT = 25,                       /* INT  */
  YYSYMBOL_FLOAT = 26,                     /* FLOAT  */
  YYSYMBOL_EMPTY = 27,                     /* EMPTY  */
  YYSYMBOL_28_ = 28,                       /* '!'  */
  YYSYMBOL_29_ = 29,                       /* '~'  */
  YYSYMBOL_30_ = 30,                       /* '&'  */
  YYSYMBOL_31_ = 31,                       /* '*'  */
  YYSYMBOL_32_ = 32,                       /* '/'  */
  YYSYMBOL_33_ = 33,                       /* '%'  */
  YYSYMBOL_34_ = 34,                       /* '+'  */
  YYSYMBOL_35_ = 35,                       /* '-'  */
  YYSYMBOL_36_ = 36,                       /* '?'  */
  YYSYMBOL_37_ = 37,                       /* ':'  */
  YYSYMBOL_38_ = 38,                       /* '('  */
  YYSYMBOL_39_ = 39,                       /* ')'  */
  YYSYMBOL_40_ = 40,                       /* ';'  */
  YYSYMBOL_41_ = 41,                       /* '{'  */
  YYSYMBOL_42_ = 42,                       /* '}'  */
  YYSYMBOL_43_ = 43,                       /* '='  */
  YYSYMBOL_44_ = 44,                       /* ','  */
  YYSYMBOL_YYACCEPT = 45,                  /* $accept  */
  YYSYMBOL_prog = 46,                      /* prog  */
  YYSYMBOL_cmds = 47,                      /* cmds  */
  YYSYMBOL_cmdstail = 48,                  /* cmdstail  */
  YYSYMBOL_cmd = 49,                       /* cmd  */
  YYSYMBOL_forargs = 50,                   /* forargs  */
  YYSYMBOL_fortail = 51,                   /* fortail  */
  YYSYMBOL_idlist = 52,                    /* idlist  */
  YYSYMBOL_parlist = 53,                   /* parlist  */
  YYSYMBOL_partail = 54,                   /* partail  */
  YYSYMBOL_exp = 55,                       /* exp  */
  YYSYMBOL_arglist = 56,                   /* arglist  */
  YYSYMBOL_argtail = 57                    /* argtail  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYFINAL  47
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1073

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  13
/* YYNRULES -- Number of rules.  */
#define YYNRULES  88
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  176

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
       2,     2,     2,    28,     2,     2,     2,    33,    30,     2,
      38,    39,    31,    34,    44,    35,     2,    32,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    37,    40,
       2,    43,     2,    36,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    41,     2,    42,    29,     2,     2,     2,
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
       0,    70,    70,    76,    79,    84,    87,    92,    95,    98,
     101,   104,   107,   110,   113,   116,   119,   122,   125,   129,
     133,   137,   141,   145,   149,   153,   159,   162,   165,   168,
     173,   176,   181,   184,   189,   192,   196,   202,   205,   209,
     213,   219,   222,   225,   228,   231,   234,   237,   240,   243,
     246,   249,   252,   255,   258,   261,   264,   267,   270,   273,
     276,   279,   282,   285,   288,   291,   294,   297,   300,   303,
     306,   310,   314,   318,   322,   326,   330,   334,   338,   342,
     346,   350,   354,   358,   362,   368,   369,   374,   375
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
  "\"end of file\"", "error", "\"invalid token\"", "ID", "TYPE", "IF",
  "WHILE", "FORALL", "FOR", "ELSE", "RETURN", "OPPOS", "OPUNI", "OPTER",
  "OPBIN3", "OPBIN4", "OPBIN5", "OPBIN6", "OPBIN7", "OPBIN8", "OPBIN9",
  "OPBIN10", "OPASSIGN", "STRING", "CHAR", "INT", "FLOAT", "EMPTY", "'!'",
  "'~'", "'&'", "'*'", "'/'", "'%'", "'+'", "'-'", "'?'", "':'", "'('",
  "')'", "';'", "'{'", "'}'", "'='", "','", "$accept", "prog", "cmds",
  "cmdstail", "cmd", "forargs", "fortail", "idlist", "parlist", "partail",
  "exp", "arglist", "argtail", YY_NULLPTR
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
     275,   276,   277,   278,   279,   280,   281,   282,    33,   126,
      38,    42,    47,    37,    43,    45,    63,    58,    40,    41,
      59,   123,   125,    61,    44
};
#endif

#define YYPACT_NINF (-137)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-38)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     175,    -5,    28,    -6,    -1,    13,    24,   244,   849,  -137,
    -137,  -137,  -137,  -137,   849,   849,   849,   849,   849,   849,
     849,  -137,   175,    60,  -137,   175,   137,  -137,   280,   849,
      20,   -14,   316,   352,   388,   208,    25,   905,  1037,  1037,
    1037,  1037,  1037,  1037,  1037,   959,    26,  -137,  -137,   175,
      29,   424,   460,   496,   532,   568,   604,   640,    69,   676,
     712,   748,   784,   820,   849,  -137,  -137,  -137,   874,    32,
      70,    50,    87,    53,    33,   968,    61,   994,    72,  1003,
      96,   849,    73,    80,   932,  -137,  -137,  -137,  -137,  -137,
    -137,  -137,   127,  -137,    59,  -137,    88,  -137,   171,  -137,
      77,  -137,    -2,  -137,   -16,  -137,  -137,    68,  -137,    68,
    -137,    68,  -137,   821,  -137,   821,  1029,   849,  -137,  -137,
      20,  -137,    39,    82,  -137,   175,   175,   175,   175,   175,
     175,    -4,  1037,   175,  -137,    80,   849,   874,  -137,    22,
      22,    18,   114,   116,  -137,  -137,  -137,  -137,   849,    80,
    -137,  -137,    90,  -137,    83,   124,  -137,  -137,  -137,   175,
     175,   175,   932,  -137,  -137,    40,    89,  -137,  -137,    80,
      91,    22,  -137,  -137,  -137,  -137
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,    69,     0,     0,     0,     0,     0,     0,     0,    44,
      45,    41,    42,    43,     0,     0,     0,     0,     0,     0,
       0,    15,     3,     0,     2,     5,     0,    46,     0,    85,
      32,    32,     0,     0,     0,     0,     0,     0,    53,    50,
      51,    52,    47,    48,    49,     0,     0,     1,     4,     5,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    12,    84,    67,    87,     0,
       0,     0,    34,     0,     0,     0,     0,     0,     0,     0,
       0,    31,     0,     0,     0,    24,    13,    70,    14,     6,
      23,    76,    59,    77,    60,    78,    61,    79,    62,    80,
      63,    81,    64,    82,    65,    83,    71,    54,    72,    55,
      73,    56,    74,    57,    75,    58,     0,     0,    86,    68,
      32,    25,     0,     0,    16,     0,     0,     0,     0,     0,
       0,     0,    30,     0,    29,     0,     0,    87,    33,     0,
       0,     0,    19,     7,    21,     9,    22,    10,     0,     0,
      11,    28,    66,    88,     0,     0,    36,    35,    17,     3,
       0,     0,     0,    27,    39,     0,     0,    20,     8,     0,
       0,     0,    18,    26,    40,    38
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -137,  -137,   -20,    84,   -11,  -137,   -68,   -28,  -137,  -136,
      -7,  -137,    -3
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    23,    24,    48,    25,    82,    83,    71,   123,   156,
      26,    69,   118
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      37,    38,    46,    73,   157,    58,    27,    39,    40,    41,
      42,    43,    44,    45,    49,   134,   135,    28,    57,    58,
      64,    67,    68,   154,    72,    75,    77,    79,    84,    30,
      70,    31,    32,    29,    64,   175,    81,    33,    49,   148,
     139,   170,   140,   171,    92,    94,    96,    98,   100,   102,
     104,    34,   107,   109,   111,   113,   115,   116,   158,   159,
      47,   -37,    35,   149,    70,    85,   155,   151,    88,    90,
     105,   119,   125,   120,   132,    53,    54,    55,    56,    57,
      58,   163,    51,    52,    53,    54,    55,    56,    57,    58,
     121,   122,   138,   124,   169,    64,    56,    57,    58,   131,
     127,   173,    62,    63,    64,    54,    55,    56,    57,    58,
     137,   129,   133,    64,   142,   143,   144,   145,   146,   147,
      81,   141,   150,   160,    64,   161,    64,   164,   165,   152,
     174,   172,     0,    89,   153,     0,     0,     0,    50,   166,
       0,   162,    52,    53,    54,    55,    56,    57,    58,   167,
     168,    51,    52,    53,    54,    55,    56,    57,    58,     0,
       0,     0,     0,    64,     0,     0,     0,     0,    59,    60,
      61,    62,    63,    64,     0,     0,     0,    65,     1,     2,
       3,     4,     5,     6,     0,     7,     0,     8,     0,    55,
      56,    57,    58,     0,     0,     0,     0,     0,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    64,     0,    18,
      19,     1,    80,    20,     0,    21,    22,     0,     0,     0,
       8,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     9,    10,    11,    12,    13,    14,    15,    16,    17,
       0,     0,    18,    19,     0,    36,    20,     1,    81,     0,
       0,     0,     0,     0,     0,     0,     8,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     9,    10,    11,
      12,    13,    14,    15,    16,    17,     0,     0,    18,    19,
       0,    66,    20,     1,     0,     0,     0,     0,     0,     0,
       0,     0,     8,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     9,    10,    11,    12,    13,    14,    15,
      16,    17,     0,     0,    18,    19,     0,    74,    20,     1,
       0,     0,     0,     0,     0,     0,     0,     0,     8,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     9,
      10,    11,    12,    13,    14,    15,    16,    17,     0,     0,
      18,    19,     0,    76,    20,     1,     0,     0,     0,     0,
       0,     0,     0,     0,     8,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     9,    10,    11,    12,    13,
      14,    15,    16,    17,     0,     0,    18,    19,     0,    78,
      20,     1,     0,     0,     0,     0,     0,     0,     0,     0,
       8,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     9,    10,    11,    12,    13,    14,    15,    16,    17,
       0,     0,    18,    19,     0,    91,    20,     1,     0,     0,
       0,     0,     0,     0,     0,     0,     8,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     9,    10,    11,
      12,    13,    14,    15,    16,    17,     0,     0,    18,    19,
       0,    93,    20,     1,     0,     0,     0,     0,     0,     0,
       0,     0,     8,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     9,    10,    11,    12,    13,    14,    15,
      16,    17,     0,     0,    18,    19,     0,    95,    20,     1,
       0,     0,     0,     0,     0,     0,     0,     0,     8,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     9,
      10,    11,    12,    13,    14,    15,    16,    17,     0,     0,
      18,    19,     0,    97,    20,     1,     0,     0,     0,     0,
       0,     0,     0,     0,     8,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     9,    10,    11,    12,    13,
      14,    15,    16,    17,     0,     0,    18,    19,     0,    99,
      20,     1,     0,     0,     0,     0,     0,     0,     0,     0,
       8,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     9,    10,    11,    12,    13,    14,    15,    16,    17,
       0,     0,    18,    19,     0,   101,    20,     1,     0,     0,
       0,     0,     0,     0,     0,     0,     8,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     9,    10,    11,
      12,    13,    14,    15,    16,    17,     0,     0,    18,    19,
       0,   103,    20,     1,     0,     0,     0,     0,     0,     0,
       0,     0,     8,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     9,    10,    11,    12,    13,    14,    15,
      16,    17,     0,     0,    18,    19,     0,   106,    20,     1,
       0,     0,     0,     0,     0,     0,     0,     0,     8,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     9,
      10,    11,    12,    13,    14,    15,    16,    17,     0,     0,
      18,    19,     0,   108,    20,     1,     0,     0,     0,     0,
       0,     0,     0,     0,     8,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     9,    10,    11,    12,    13,
      14,    15,    16,    17,     0,     0,    18,    19,     0,   110,
      20,     1,     0,     0,     0,     0,     0,     0,     0,     0,
       8,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     9,    10,    11,    12,    13,    14,    15,    16,    17,
       0,     0,    18,    19,     0,   112,    20,     1,     0,     0,
       0,     0,     0,     0,     0,     0,     8,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     9,    10,    11,
      12,    13,    14,    15,    16,    17,     0,     0,    18,    19,
       0,   114,    20,     1,     0,     0,     0,     0,     0,     0,
       0,     0,     8,     0,     0,    51,    52,    53,    54,    55,
      56,    57,    58,     9,    10,    11,    12,    13,    14,    15,
      16,    17,     1,     0,    18,    19,     0,    64,    20,     0,
       0,     8,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     9,    10,    11,    12,    13,    14,    15,    16,
      17,     0,     0,    18,    19,     0,     0,    20,    51,    52,
      53,    54,    55,    56,    57,    58,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    59,    60,    61,    62,    63,
      64,     0,     0,     0,     0,     0,     0,     0,   117,    51,
      52,    53,    54,    55,    56,    57,    58,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    59,    60,    61,    62,
      63,    64,     0,     0,     0,    86,    51,    52,    53,    54,
      55,    56,    57,    58,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    59,    60,    61,    62,    63,    64,     0,
       0,     0,    81,    51,    52,    53,    54,    55,    56,    57,
      58,     0,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,     0,     0,    87,    59,
      60,    61,    62,    63,    64,     0,     0,   126,    51,    52,
      53,    54,    55,    56,    57,    58,     0,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,     0,     0,   128,    59,    60,    61,    62,    63,    64,
       0,     0,   130,    51,    52,    53,    54,    55,    56,    57,
      58,    51,    52,    53,    54,    55,    56,    57,    58,     0,
      59,    60,    61,    62,    63,    64,   136,     0,    59,    60,
      61,    62,    63,    64
};

static const yytype_int16 yycheck[] =
{
       7,     8,    22,    31,   140,    21,    11,    14,    15,    16,
      17,    18,    19,    20,    25,    83,    84,    22,    20,    21,
      36,    28,    29,     1,    38,    32,    33,    34,    35,     1,
      44,     3,    38,    38,    36,   171,    40,    38,    49,    43,
       1,     1,     3,     3,    51,    52,    53,    54,    55,    56,
      57,    38,    59,    60,    61,    62,    63,    64,    40,    41,
       0,    39,    38,   131,    44,    40,    44,   135,    42,    40,
       1,    39,    39,     3,    81,    16,    17,    18,    19,    20,
      21,   149,    14,    15,    16,    17,    18,    19,    20,    21,
      40,     4,   120,    40,   162,    36,    19,    20,    21,     3,
      39,   169,    34,    35,    36,    17,    18,    19,    20,    21,
     117,    39,    39,    36,   125,   126,   127,   128,   129,   130,
      40,    39,   133,     9,    36,     9,    36,    44,     4,   136,
      39,    42,    -1,    49,   137,    -1,    -1,    -1,     1,   159,
      -1,   148,    15,    16,    17,    18,    19,    20,    21,   160,
     161,    14,    15,    16,    17,    18,    19,    20,    21,    -1,
      -1,    -1,    -1,    36,    -1,    -1,    -1,    -1,    31,    32,
      33,    34,    35,    36,    -1,    -1,    -1,    40,     3,     4,
       5,     6,     7,     8,    -1,    10,    -1,    12,    -1,    18,
      19,    20,    21,    -1,    -1,    -1,    -1,    -1,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    36,    -1,    34,
      35,     3,     4,    38,    -1,    40,    41,    -1,    -1,    -1,
      12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      -1,    -1,    34,    35,    -1,     1,    38,     3,    40,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    12,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    -1,    -1,    34,    35,
      -1,     1,    38,     3,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    -1,    -1,    34,    35,    -1,     1,    38,     3,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    12,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    -1,    -1,
      34,    35,    -1,     1,    38,     3,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    12,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    -1,    -1,    34,    35,    -1,     1,
      38,     3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      -1,    -1,    34,    35,    -1,     1,    38,     3,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    12,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    -1,    -1,    34,    35,
      -1,     1,    38,     3,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    -1,    -1,    34,    35,    -1,     1,    38,     3,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    12,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    -1,    -1,
      34,    35,    -1,     1,    38,     3,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    12,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    -1,    -1,    34,    35,    -1,     1,
      38,     3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      -1,    -1,    34,    35,    -1,     1,    38,     3,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    12,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    -1,    -1,    34,    35,
      -1,     1,    38,     3,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    -1,    -1,    34,    35,    -1,     1,    38,     3,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    12,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    -1,    -1,
      34,    35,    -1,     1,    38,     3,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    12,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    -1,    -1,    34,    35,    -1,     1,
      38,     3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      -1,    -1,    34,    35,    -1,     1,    38,     3,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    12,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    -1,    -1,    34,    35,
      -1,     1,    38,     3,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    12,    -1,    -1,    14,    15,    16,    17,    18,
      19,    20,    21,    23,    24,    25,    26,    27,    28,    29,
      30,    31,     3,    -1,    34,    35,    -1,    36,    38,    -1,
      -1,    12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    -1,    -1,    34,    35,    -1,    -1,    38,    14,    15,
      16,    17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,    35,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    14,
      15,    16,    17,    18,    19,    20,    21,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,
      35,    36,    -1,    -1,    -1,    40,    14,    15,    16,    17,
      18,    19,    20,    21,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    31,    32,    33,    34,    35,    36,    -1,
      -1,    -1,    40,    14,    15,    16,    17,    18,    19,    20,
      21,    -1,    14,    15,    16,    17,    18,    19,    20,    21,
      31,    32,    33,    34,    35,    36,    -1,    -1,    39,    31,
      32,    33,    34,    35,    36,    -1,    -1,    39,    14,    15,
      16,    17,    18,    19,    20,    21,    -1,    14,    15,    16,
      17,    18,    19,    20,    21,    31,    32,    33,    34,    35,
      36,    -1,    -1,    39,    31,    32,    33,    34,    35,    36,
      -1,    -1,    39,    14,    15,    16,    17,    18,    19,    20,
      21,    14,    15,    16,    17,    18,    19,    20,    21,    -1,
      31,    32,    33,    34,    35,    36,    37,    -1,    31,    32,
      33,    34,    35,    36
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,    10,    12,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    34,    35,
      38,    40,    41,    46,    47,    49,    55,    11,    22,    38,
       1,     3,    38,    38,    38,    38,     1,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    47,     0,    48,    49,
       1,    14,    15,    16,    17,    18,    19,    20,    21,    31,
      32,    33,    34,    35,    36,    40,     1,    55,    55,    56,
      44,    52,    38,    52,     1,    55,     1,    55,     1,    55,
       4,    40,    50,    51,    55,    40,    40,    39,    42,    48,
      40,     1,    55,     1,    55,     1,    55,     1,    55,     1,
      55,     1,    55,     1,    55,     1,     1,    55,     1,    55,
       1,    55,     1,    55,     1,    55,    55,    44,    57,    39,
       3,    40,     4,    53,    40,    39,    39,    39,    39,    39,
      39,     3,    55,    39,    51,    51,    37,    55,    52,     1,
       3,    39,    49,    49,    49,    49,    49,    49,    43,    51,
      49,    51,    55,    57,     1,    44,    54,    54,    40,    41,
       9,     9,    55,    51,    44,     4,    47,    49,    49,    51,
       1,     3,    42,    51,    39,    54
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    45,    46,    47,    47,    48,    48,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    50,    50,    50,    50,
      51,    51,    52,    52,    53,    53,    53,    54,    54,    54,
      54,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    56,    56,    57,    57
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     0,     2,     5,     7,     5,
       5,     5,     2,     3,     3,     1,     4,     6,     8,     5,
       7,     5,     5,     3,     3,     4,     6,     4,     3,     2,
       2,     1,     0,     3,     0,     3,     3,     0,     4,     2,
       4,     1,     1,     1,     1,     1,     2,     2,     2,     2,
       2,     2,     2,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     5,     3,     4,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     0,     2,     0,     3
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
        yyerror (YY_("syntax error: cannot back up")); \
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
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
                 int yyrule)
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
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
yyparse (void)
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
  case 2: /* prog: cmds  */
#line 70 "sintatico.y"
           {
		printf("%s\n", (yyvsp[0].name));
		depth_pre(print, root, NULL, NULL, NULL);
	}
#line 1425 "sintatico.tab.c"
    break;

  case 3: /* cmds: %empty  */
#line 76 "sintatico.y"
             {
		ssprintf((yyval.name), "<block>");
	}
#line 1433 "sintatico.tab.c"
    break;

  case 4: /* cmds: cmd cmdstail  */
#line 79 "sintatico.y"
                       {
		ssprintf((yyval.name), "<block, %s%s>", (yyvsp[-1].name), (yyvsp[0].name));
	}
#line 1441 "sintatico.tab.c"
    break;

  case 5: /* cmdstail: %empty  */
#line 84 "sintatico.y"
                 {
		*(yyval.name) = '\0';
	}
#line 1449 "sintatico.tab.c"
    break;

  case 6: /* cmdstail: cmd cmdstail  */
#line 87 "sintatico.y"
                       {
		ssprintf((yyval.name), ", %s%s", (yyvsp[-1].name), (yyvsp[0].name));
	}
#line 1457 "sintatico.tab.c"
    break;

  case 7: /* cmd: IF '(' exp ')' cmd  */
#line 92 "sintatico.y"
                                 {
		ssprintf((yyval.name), "<%s, %s, %s, <emptycmd>>", (yyvsp[-4].name), (yyvsp[-2].name), (yyvsp[0].name));
	}
#line 1465 "sintatico.tab.c"
    break;

  case 8: /* cmd: IF '(' exp ')' cmd ELSE cmd  */
#line 95 "sintatico.y"
                                                 {
		ssprintf((yyval.name), "<%s, %s, %s, %s>", (yyvsp[-6].name), (yyvsp[-4].name), (yyvsp[-2].name), (yyvsp[0].name));
	}
#line 1473 "sintatico.tab.c"
    break;

  case 9: /* cmd: WHILE '(' exp ')' cmd  */
#line 98 "sintatico.y"
                                {
		ssprintf((yyval.name), "<%s, %s, %s>", (yyvsp[-4].name), (yyvsp[-2].name), (yyvsp[0].name));
	}
#line 1481 "sintatico.tab.c"
    break;

  case 10: /* cmd: FORALL '(' exp ')' cmd  */
#line 101 "sintatico.y"
                                 {
		ssprintf((yyval.name), "<%s, %s, %s>", (yyvsp[-4].name), (yyvsp[-2].name), (yyvsp[0].name));
	}
#line 1489 "sintatico.tab.c"
    break;

  case 11: /* cmd: FOR '(' forargs ')' cmd  */
#line 104 "sintatico.y"
                                  {
		ssprintf((yyval.name), "<%s, %s, %s>", (yyvsp[-4].name), (yyvsp[-2].name), (yyvsp[0].name));
	}
#line 1497 "sintatico.tab.c"
    break;

  case 12: /* cmd: exp ';'  */
#line 107 "sintatico.y"
                  {
		ssprintf((yyval.name), "<cmd, %s>", (yyvsp[-1].name));
	}
#line 1505 "sintatico.tab.c"
    break;

  case 13: /* cmd: RETURN exp ';'  */
#line 110 "sintatico.y"
                         {
		ssprintf((yyval.name), "<%s, %s>", (yyvsp[-2].name), (yyvsp[-1].name));
	}
#line 1513 "sintatico.tab.c"
    break;

  case 14: /* cmd: '{' cmds '}'  */
#line 113 "sintatico.y"
                       {
		strcpy((yyval.name), (yyvsp[-1].name));
	}
#line 1521 "sintatico.tab.c"
    break;

  case 15: /* cmd: ';'  */
#line 116 "sintatico.y"
              {
		ssprintf((yyval.name), "<emptycmd>");
	}
#line 1529 "sintatico.tab.c"
    break;

  case 16: /* cmd: TYPE ID idlist ';'  */
#line 119 "sintatico.y"
                             {
		ssprintf((yyval.name), "<declr, %s, %s%s>", (yyvsp[-3].name), (yyvsp[-2].name), (yyvsp[-1].name));
	}
#line 1537 "sintatico.tab.c"
    break;

  case 17: /* cmd: TYPE ID '(' parlist ')' ';'  */
#line 122 "sintatico.y"
                                      {
		ssprintf((yyval.name), "<declr_fn_header, %s, %s%s>", (yyvsp[-5].name), (yyvsp[-4].name), (yyvsp[-2].name));
	}
#line 1545 "sintatico.tab.c"
    break;

  case 18: /* cmd: TYPE ID '(' parlist ')' '{' cmds '}'  */
#line 125 "sintatico.y"
                                               {
		ssprintf((yyval.name), "<declr_fn, %s, %s, %s%s>", (yyvsp[-7].name), (yyvsp[-6].name), (yyvsp[-1].name), (yyvsp[-4].name));
	}
#line 1553 "sintatico.tab.c"
    break;

  case 19: /* cmd: IF '(' error ')' cmd  */
#line 129 "sintatico.y"
                                        {
		ssprintf((yyval.name), "<%s, <err_exp>, %s>", (yyvsp[-4].name), (yyvsp[0].name));
		ssprintf(syn_errormsg, "Expected condition in '%s' statment", (yyvsp[-4].name));
	}
#line 1562 "sintatico.tab.c"
    break;

  case 20: /* cmd: IF '(' error ')' cmd ELSE cmd  */
#line 133 "sintatico.y"
                                                   {
		ssprintf((yyval.name), "<%s, <err_exp>, %s, %s>", (yyvsp[-6].name), (yyvsp[-2].name), (yyvsp[0].name));
		ssprintf(syn_errormsg, "Expected condition in '%s' statment", (yyvsp[-6].name));
	}
#line 1571 "sintatico.tab.c"
    break;

  case 21: /* cmd: WHILE '(' error ')' cmd  */
#line 137 "sintatico.y"
                                  {
		ssprintf((yyval.name), "<%s, <err_exp>, %s>", (yyvsp[-4].name), (yyvsp[0].name));
		ssprintf(syn_errormsg, "Expected condition in '%s' statment", (yyvsp[-4].name));
	}
#line 1580 "sintatico.tab.c"
    break;

  case 22: /* cmd: FORALL '(' error ')' cmd  */
#line 141 "sintatico.y"
                                   {
		ssprintf((yyval.name), "<%s, <err_exp>, %s>", (yyvsp[-4].name), (yyvsp[0].name));
		ssprintf(syn_errormsg, "Expected in-expression in '%s' statment", (yyvsp[-4].name));
	}
#line 1589 "sintatico.tab.c"
    break;

  case 23: /* cmd: exp error ';'  */
#line 145 "sintatico.y"
                        {
		ssprintf((yyval.name), "<err_exp, %s>", (yyvsp[-2].name));
		ssprintf(syn_errormsg, "Expected expression or ';'");
	}
#line 1598 "sintatico.tab.c"
    break;

  case 24: /* cmd: RETURN error ';'  */
#line 149 "sintatico.y"
                           {
		ssprintf((yyval.name), "<err_exp, %s>", (yyvsp[-2].name));
		ssprintf(syn_errormsg, "Expected return expression");
	}
#line 1607 "sintatico.tab.c"
    break;

  case 25: /* cmd: TYPE error idlist ';'  */
#line 153 "sintatico.y"
                                {
		ssprintf((yyval.name), "<err_exp, declr, %s><declr, %s%s>", (yyvsp[-3].name), (yyvsp[-3].name), (yyvsp[-1].name));
		ssprintf(syn_errormsg, "Expected identifier of type '%s'", (yyvsp[-3].name));
	}
#line 1616 "sintatico.tab.c"
    break;

  case 26: /* forargs: TYPE ID '=' exp fortail fortail  */
#line 159 "sintatico.y"
                                         {
		ssprintf((yyval.name), "<forargs, <declr_init, %s, %s, %s>, %s, %s>", (yyvsp[-5].name), (yyvsp[-4].name), (yyvsp[-2].name), (yyvsp[-1].name), (yyvsp[0].name));
	}
#line 1624 "sintatico.tab.c"
    break;

  case 27: /* forargs: TYPE ID fortail fortail  */
#line 162 "sintatico.y"
                                  {
		ssprintf((yyval.name), "<forargs, <declr, %s, %s>, %s, %s>", (yyvsp[-3].name), (yyvsp[-2].name), (yyvsp[-1].name), (yyvsp[0].name));
	}
#line 1632 "sintatico.tab.c"
    break;

  case 28: /* forargs: exp fortail fortail  */
#line 165 "sintatico.y"
                              {
		ssprintf((yyval.name), "<forargs, %s, %s, %s>", (yyvsp[-2].name), (yyvsp[-1].name), (yyvsp[0].name));
	}
#line 1640 "sintatico.tab.c"
    break;

  case 29: /* forargs: fortail fortail  */
#line 168 "sintatico.y"
                          {
		ssprintf((yyval.name), "<forargs, <emptyexp>, %s, %s>", (yyvsp[-1].name), (yyvsp[0].name));
	}
#line 1648 "sintatico.tab.c"
    break;

  case 30: /* fortail: ';' exp  */
#line 173 "sintatico.y"
                 {
		ssprintf((yyval.name), "%s", (yyvsp[0].name));
	}
#line 1656 "sintatico.tab.c"
    break;

  case 31: /* fortail: ';'  */
#line 176 "sintatico.y"
              {
		strcpy((yyval.name), "<emptyexp>");
	}
#line 1664 "sintatico.tab.c"
    break;

  case 32: /* idlist: %empty  */
#line 181 "sintatico.y"
               {
		*(yyval.name) = '\0';
	}
#line 1672 "sintatico.tab.c"
    break;

  case 33: /* idlist: ',' ID idlist  */
#line 184 "sintatico.y"
                        {
		ssprintf((yyval.name), ", %s%s", (yyvsp[-1].name), (yyvsp[0].name));
	}
#line 1680 "sintatico.tab.c"
    break;

  case 34: /* parlist: %empty  */
#line 189 "sintatico.y"
                {
		*(yyval.name) = '\0';
	}
#line 1688 "sintatico.tab.c"
    break;

  case 35: /* parlist: TYPE ID partail  */
#line 192 "sintatico.y"
                          {
		ssprintf((yyval.name), ", <par, %s, %s>%s", (yyvsp[-2].name), (yyvsp[-1].name), (yyvsp[0].name));
	}
#line 1696 "sintatico.tab.c"
    break;

  case 36: /* parlist: TYPE error partail  */
#line 196 "sintatico.y"
                             {
		ssprintf(syn_errormsg, "Expected identifier of type '%s'", (yyvsp[-2].name));
		ssprintf((yyval.name), ", <err_par, %s>%s", (yyvsp[-2].name), (yyvsp[0].name));
	}
#line 1705 "sintatico.tab.c"
    break;

  case 37: /* partail: %empty  */
#line 202 "sintatico.y"
                {
		*(yyval.name) = '\0';
	}
#line 1713 "sintatico.tab.c"
    break;

  case 38: /* partail: ',' TYPE ID partail  */
#line 205 "sintatico.y"
                              {
		ssprintf((yyval.name), "<par, %s, %s>%s", (yyvsp[-2].name), (yyvsp[-1].name), (yyvsp[0].name));
	}
#line 1721 "sintatico.tab.c"
    break;

  case 39: /* partail: error ','  */
#line 209 "sintatico.y"
                    {
		ssprintf(syn_errormsg, "Expected a ','");
		ssprintf((yyval.name), "<err_par>");
	}
#line 1730 "sintatico.tab.c"
    break;

  case 40: /* partail: ',' TYPE error ')'  */
#line 213 "sintatico.y"
                             {
		ssprintf(syn_errormsg, "Expected identifier of type '%s'", (yyvsp[-2].name));
		ssprintf((yyval.name), "<err_par, %s>", (yyvsp[-2].name));
	}
#line 1739 "sintatico.tab.c"
    break;

  case 41: /* exp: INT  */
#line 219 "sintatico.y"
         {
		ssprintf((yyval.name), "<int, %d>", (yyvsp[0].dval));
	}
#line 1747 "sintatico.tab.c"
    break;

  case 42: /* exp: FLOAT  */
#line 222 "sintatico.y"
                {
		ssprintf((yyval.name), "<float, %f>", (yyvsp[0].fval));
	}
#line 1755 "sintatico.tab.c"
    break;

  case 43: /* exp: EMPTY  */
#line 225 "sintatico.y"
                {
		ssprintf((yyval.name), "<empty>");
	}
#line 1763 "sintatico.tab.c"
    break;

  case 44: /* exp: STRING  */
#line 228 "sintatico.y"
                 {
		ssprintf((yyval.name), "<str, %s>", (yyvsp[0].name));
	}
#line 1771 "sintatico.tab.c"
    break;

  case 45: /* exp: CHAR  */
#line 231 "sintatico.y"
               {
		ssprintf((yyval.name), "<char, %s>", (yyvsp[0].name));
	}
#line 1779 "sintatico.tab.c"
    break;

  case 46: /* exp: ID OPPOS  */
#line 234 "sintatico.y"
                   {
		ssprintf((yyval.name), "<exp, <id, %s><oppos, %s>>", (yyvsp[-1].name), (yyvsp[0].name));
	}
#line 1787 "sintatico.tab.c"
    break;

  case 47: /* exp: '*' exp  */
#line 237 "sintatico.y"
                              {
		ssprintf((yyval.name), "<exp, <opuni, %s>%s>", (yyvsp[-1].name), (yyvsp[0].name));
	}
#line 1795 "sintatico.tab.c"
    break;

  case 48: /* exp: '+' exp  */
#line 240 "sintatico.y"
                              {
		ssprintf((yyval.name), "<exp, <opuni, %s>%s>", (yyvsp[-1].name), (yyvsp[0].name));
	}
#line 1803 "sintatico.tab.c"
    break;

  case 49: /* exp: '-' exp  */
#line 243 "sintatico.y"
                              {
		ssprintf((yyval.name), "<exp, <opuni, %s>%s>", (yyvsp[-1].name), (yyvsp[0].name));
	}
#line 1811 "sintatico.tab.c"
    break;

  case 50: /* exp: '!' exp  */
#line 246 "sintatico.y"
                              {
		ssprintf((yyval.name), "<exp, <opuni, %s>%s>", (yyvsp[-1].name), (yyvsp[0].name));
	}
#line 1819 "sintatico.tab.c"
    break;

  case 51: /* exp: '~' exp  */
#line 249 "sintatico.y"
                              {
		ssprintf((yyval.name), "<exp, <opuni, %s>%s>", (yyvsp[-1].name), (yyvsp[0].name));
	}
#line 1827 "sintatico.tab.c"
    break;

  case 52: /* exp: '&' exp  */
#line 252 "sintatico.y"
                              {
		ssprintf((yyval.name), "<exp, <opuni, %s>%s>", (yyvsp[-1].name), (yyvsp[0].name));
	}
#line 1835 "sintatico.tab.c"
    break;

  case 53: /* exp: OPUNI exp  */
#line 255 "sintatico.y"
                    {
		ssprintf((yyval.name), "<exp, <opuni, %s>%s>", (yyvsp[-1].name), (yyvsp[0].name));
	}
#line 1843 "sintatico.tab.c"
    break;

  case 54: /* exp: exp '*' exp  */
#line 258 "sintatico.y"
                      {
		ssprintf((yyval.name), "<exp, %s<opbin, %s>%s>", (yyvsp[-2].name), (yyvsp[-1].name), (yyvsp[0].name));
	}
#line 1851 "sintatico.tab.c"
    break;

  case 55: /* exp: exp '/' exp  */
#line 261 "sintatico.y"
                      {
		ssprintf((yyval.name), "<exp, %s<opbin, %s>%s>", (yyvsp[-2].name), (yyvsp[-1].name), (yyvsp[0].name));
	}
#line 1859 "sintatico.tab.c"
    break;

  case 56: /* exp: exp '%' exp  */
#line 264 "sintatico.y"
                      {
		ssprintf((yyval.name), "<exp, %s<opbin, %s>%s>", (yyvsp[-2].name), (yyvsp[-1].name), (yyvsp[0].name));
	}
#line 1867 "sintatico.tab.c"
    break;

  case 57: /* exp: exp '+' exp  */
#line 267 "sintatico.y"
                      {
		ssprintf((yyval.name), "<exp, %s<opbin, %s>%s>", (yyvsp[-2].name), (yyvsp[-1].name), (yyvsp[0].name));
	}
#line 1875 "sintatico.tab.c"
    break;

  case 58: /* exp: exp '-' exp  */
#line 270 "sintatico.y"
                      {
		ssprintf((yyval.name), "<exp, %s<opbin, %s>%s>", (yyvsp[-2].name), (yyvsp[-1].name), (yyvsp[0].name));
	}
#line 1883 "sintatico.tab.c"
    break;

  case 59: /* exp: exp OPBIN3 exp  */
#line 273 "sintatico.y"
                         {
		ssprintf((yyval.name), "<exp, %s<opbin, %s>%s>", (yyvsp[-2].name), (yyvsp[-1].name), (yyvsp[0].name));
	}
#line 1891 "sintatico.tab.c"
    break;

  case 60: /* exp: exp OPBIN4 exp  */
#line 276 "sintatico.y"
                         {
		ssprintf((yyval.name), "<exp, %s<opbin, %s>%s>", (yyvsp[-2].name), (yyvsp[-1].name), (yyvsp[0].name));
	}
#line 1899 "sintatico.tab.c"
    break;

  case 61: /* exp: exp OPBIN5 exp  */
#line 279 "sintatico.y"
                         {
		ssprintf((yyval.name), "<exp, %s<opbin, %s>%s>", (yyvsp[-2].name), (yyvsp[-1].name), (yyvsp[0].name));
	}
#line 1907 "sintatico.tab.c"
    break;

  case 62: /* exp: exp OPBIN6 exp  */
#line 282 "sintatico.y"
                         {
		ssprintf((yyval.name), "<exp, %s<opbin, %s>%s>", (yyvsp[-2].name), (yyvsp[-1].name), (yyvsp[0].name));
	}
#line 1915 "sintatico.tab.c"
    break;

  case 63: /* exp: exp OPBIN7 exp  */
#line 285 "sintatico.y"
                         {
		ssprintf((yyval.name), "<exp, %s<opbin, %s>%s>", (yyvsp[-2].name), (yyvsp[-1].name), (yyvsp[0].name));
	}
#line 1923 "sintatico.tab.c"
    break;

  case 64: /* exp: exp OPBIN8 exp  */
#line 288 "sintatico.y"
                         {
		ssprintf((yyval.name), "<exp, %s<opbin, %s>%s>", (yyvsp[-2].name), (yyvsp[-1].name), (yyvsp[0].name));
	}
#line 1931 "sintatico.tab.c"
    break;

  case 65: /* exp: exp OPBIN9 exp  */
#line 291 "sintatico.y"
                         {
		ssprintf((yyval.name), "<exp, %s<opbin, %s>%s>", (yyvsp[-2].name), (yyvsp[-1].name), (yyvsp[0].name));
	}
#line 1939 "sintatico.tab.c"
    break;

  case 66: /* exp: exp '?' exp ':' exp  */
#line 294 "sintatico.y"
                              {
		ssprintf((yyval.name), "<exp, %s<opter, ?>%s<opter, :>%s", (yyvsp[-4].name), (yyvsp[-2].name), (yyvsp[0].name));
	}
#line 1947 "sintatico.tab.c"
    break;

  case 67: /* exp: ID OPASSIGN exp  */
#line 297 "sintatico.y"
                          {
		ssprintf((yyval.name), "<exp, <id, %s><opassign, %s>%s>", (yyvsp[-2].name), (yyvsp[-1].name), (yyvsp[0].name));
	}
#line 1955 "sintatico.tab.c"
    break;

  case 68: /* exp: ID '(' arglist ')'  */
#line 300 "sintatico.y"
                             {
		ssprintf((yyval.name), "<fn, %s%s>", (yyvsp[-3].name), (yyvsp[-1].name));
	}
#line 1963 "sintatico.tab.c"
    break;

  case 69: /* exp: ID  */
#line 303 "sintatico.y"
             {
		ssprintf((yyval.name), "<id, %s>", (yyvsp[0].name));
	}
#line 1971 "sintatico.tab.c"
    break;

  case 70: /* exp: '(' exp ')'  */
#line 306 "sintatico.y"
                      {
		ssprintf((yyval.name), "<exp, %s>", (yyvsp[-1].name));
	}
#line 1979 "sintatico.tab.c"
    break;

  case 71: /* exp: exp '*' error  */
#line 310 "sintatico.y"
                        {
		sprintf(syn_errormsg, "Expected expression while processing '*'");
		ssprintf((yyval.name), "<err_exp, %s<opbin, %s>>", (yyvsp[-2].name), (yyvsp[-1].name));
	}
#line 1988 "sintatico.tab.c"
    break;

  case 72: /* exp: exp '/' error  */
#line 314 "sintatico.y"
                        {
		sprintf(syn_errormsg, "Expected expression while processing '/'");
		ssprintf((yyval.name), "<err_exp, %s<opbin, %s>>", (yyvsp[-2].name), (yyvsp[-1].name));
	}
#line 1997 "sintatico.tab.c"
    break;

  case 73: /* exp: exp '%' error  */
#line 318 "sintatico.y"
                        {
		sprintf(syn_errormsg, "Expected expression while processing '%%'");
		ssprintf((yyval.name), "<err_exp, %s<opbin, %s>>", (yyvsp[-2].name), (yyvsp[-1].name));
	}
#line 2006 "sintatico.tab.c"
    break;

  case 74: /* exp: exp '+' error  */
#line 322 "sintatico.y"
                        {
		sprintf(syn_errormsg, "Expected expression while processing '+'");
		ssprintf((yyval.name), "<err_exp, %s<opbin, %s>>", (yyvsp[-2].name), (yyvsp[-1].name));
	}
#line 2015 "sintatico.tab.c"
    break;

  case 75: /* exp: exp '-' error  */
#line 326 "sintatico.y"
                        {
		sprintf(syn_errormsg, "Expected expression while processing '-'");
		ssprintf((yyval.name), "<err_exp, %s<opbin, %s>>", (yyvsp[-2].name), (yyvsp[-1].name));
	}
#line 2024 "sintatico.tab.c"
    break;

  case 76: /* exp: exp OPBIN3 error  */
#line 330 "sintatico.y"
                           {
		ssprintf(syn_errormsg, "Expected expression while processing '%s'", (yyvsp[-1].name));
		ssprintf((yyval.name), "<err_exp, %s<opbin, %s>>", (yyvsp[-2].name), (yyvsp[-1].name));
	}
#line 2033 "sintatico.tab.c"
    break;

  case 77: /* exp: exp OPBIN4 error  */
#line 334 "sintatico.y"
                           {
		ssprintf(syn_errormsg, "Expected expression while processing '%s'", (yyvsp[-1].name));
		ssprintf((yyval.name), "<err_exp, %s<opbin, %s>>", (yyvsp[-2].name), (yyvsp[-1].name));
	}
#line 2042 "sintatico.tab.c"
    break;

  case 78: /* exp: exp OPBIN5 error  */
#line 338 "sintatico.y"
                           {
		ssprintf(syn_errormsg, "Expected expression while processing '%s'", (yyvsp[-1].name));
		ssprintf((yyval.name), "<err_exp, %s<opbin, %s>>", (yyvsp[-2].name), (yyvsp[-1].name));
	}
#line 2051 "sintatico.tab.c"
    break;

  case 79: /* exp: exp OPBIN6 error  */
#line 342 "sintatico.y"
                           {
		ssprintf(syn_errormsg, "Expected expression while processing '%s'", (yyvsp[-1].name));
		ssprintf((yyval.name), "<err_exp, %s<opbin, %s>>", (yyvsp[-2].name), (yyvsp[-1].name));
	}
#line 2060 "sintatico.tab.c"
    break;

  case 80: /* exp: exp OPBIN7 error  */
#line 346 "sintatico.y"
                           {
		ssprintf(syn_errormsg, "Expected expression while processing '%s'", (yyvsp[-1].name));
		ssprintf((yyval.name), "<err_exp, %s<opbin, %s>>", (yyvsp[-2].name), (yyvsp[-1].name));
	}
#line 2069 "sintatico.tab.c"
    break;

  case 81: /* exp: exp OPBIN8 error  */
#line 350 "sintatico.y"
                           {
		ssprintf(syn_errormsg, "Expected expression while processing '%s'", (yyvsp[-1].name));
		ssprintf((yyval.name), "<err_exp, %s<opbin, %s>>", (yyvsp[-2].name), (yyvsp[-1].name));
	}
#line 2078 "sintatico.tab.c"
    break;

  case 82: /* exp: exp OPBIN9 error  */
#line 354 "sintatico.y"
                           {
		ssprintf(syn_errormsg, "Expected expression while processing '%s'", (yyvsp[-1].name));
		ssprintf((yyval.name), "<err_exp, %s<opbin, %s>>", (yyvsp[-2].name), (yyvsp[-1].name));
	}
#line 2087 "sintatico.tab.c"
    break;

  case 83: /* exp: exp OPBIN10 error  */
#line 358 "sintatico.y"
                            {
		ssprintf(syn_errormsg, "Expected expression while processing '%s'", (yyvsp[-1].name));
		ssprintf((yyval.name), "<err_exp, %s<opbin, %s>%s>", (yyvsp[-2].name), (yyvsp[-1].name));
	}
#line 2096 "sintatico.tab.c"
    break;

  case 84: /* exp: ID OPASSIGN error  */
#line 362 "sintatico.y"
                            {
		ssprintf(syn_errormsg, "Expected expression in '%s %s'", (yyvsp[-2].name), (yyvsp[-1].name));
		ssprintf((yyval.name), "<err_exp, <id, %s><opassign, %s>>", (yyvsp[-2].name), (yyvsp[-1].name));
	}
#line 2105 "sintatico.tab.c"
    break;

  case 85: /* arglist: %empty  */
#line 368 "sintatico.y"
                { *(yyval.name) = '\0'; }
#line 2111 "sintatico.tab.c"
    break;

  case 86: /* arglist: exp argtail  */
#line 369 "sintatico.y"
                      {
		ssprintf((yyval.name), ", %s%s", (yyvsp[-1].name), (yyvsp[0].name));
	}
#line 2119 "sintatico.tab.c"
    break;

  case 87: /* argtail: %empty  */
#line 374 "sintatico.y"
                { *(yyval.name) = '\0'; }
#line 2125 "sintatico.tab.c"
    break;

  case 88: /* argtail: ',' exp argtail  */
#line 375 "sintatico.y"
                          {
		ssprintf((yyval.name), ", %s%s", (yyvsp[-1].name), (yyvsp[0].name));
	}
#line 2133 "sintatico.tab.c"
    break;


#line 2137 "sintatico.tab.c"

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
      yyerror (YY_("syntax error"));
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
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
  yyerror (YY_("memory exhausted"));
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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 380 "sintatico.y"


int yyerror(char *s) {
	if (*syn_errormsg) {
		fprintf(stderr, "\033[48;2;145;0;0m  > %s\033[0m\n", syn_errormsg);
	}
	fprintf(stderr, "\033[48;2;145;0;0m%s:%d:%d\033[0m\n", filename, lnum + 1, lcol);
	*syn_errormsg = '\0';
	return 0;
}

int main(int argc, char **argv) {
	if (argc < 2) {
		fprintf(stderr, "No input file\n");
		exit(EXIT_FAILURE);
	}
	strcpy(filename, argv[1]);
	root = create_node(filename);
	yyin = fopen(argv[1], "r");
	yyparse();
	if (*syn_errormsg) {
		fprintf(stderr, "\033[48;2;145;0;0m  > %s\033[0m\n", syn_errormsg);
	}
	printf("\n");
	return 0;
}

void ssprintf(char *target, char *template, ...) {
	va_list ap;
	va_start(ap, template);
	vsprintf(target, template, ap);
	va_end(ap);
}

void print(node_t node, void *data) {
	int l = level(node);
	for (int i = 0; i < l - 1; i++) {
		printf("  ");
	}
	if (l > 1) {
		printf("|---> ");
	}
	printf("%s\n", (char *) node->value);
}
