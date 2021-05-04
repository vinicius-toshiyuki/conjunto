#ifndef __UTIL_H__
#define __UTIL_H__

#include <config.h>

/* Informações sobre tamanhos de strings */
#define NAMESIZE 32768
#define FILENAMESIZE 512

/* ======== Definição de caracteres para impressão da árvore ===== */
#ifdef WITH_UNICODE

#define TREECHILDFIRST "┬"
#define TREECHILDMID "├"
#define TREECHILDLAST "└"
#define TREECHILD "│"
#define TREELEAF "○"
#define TREEEXTENSION "◇"
#define TREEBRANCH "─"

#define SEPARATOR "══════════"

#define BOX_TOP_RIGHT "┐"
#define BOX_TOP_LEFT "┌"
#define BOX_BOT_RIGHT "┘"
#define BOX_BOT_LEFT "└"
#define BOX_VERT "│"
#define BOX_HOR "─"
#define BOX_CROSS_IN "┼"
#define BOX_CROSS_LEFT "├"
#define BOX_CROSS_RIGHT "┤"
#define BOX_CROSS_TOP "┬"
#define BOX_CROSS_BOT "┴"
#define BOX_HEADER_HOR "━"
#define BOX_HEADER_LEFT "┝"
#define BOX_HEADER_RIGHT "┥"
#define BOX_HEADER_MID "┿"

#else

#define TREECHILDFIRST "."
#define TREECHILDMID "|"
#define TREECHILDLAST "+"
#define TREECHILD "|"
#define TREELEAF ">"
#define TREEEXTENSION "~"
#define TREEBRANCH "-"

#define SEPARATOR "=========="

#define BOX_TOP_RIGHT "+"
#define BOX_TOP_LEFT "+"
#define BOX_BOT_RIGHT "+"
#define BOX_BOT_LEFT "+"
#define BOX_VERT "|"
#define BOX_HOR "-"
#define BOX_CROSS_IN "+"
#define BOX_CROSS_LEFT "|"
#define BOX_CROSS_RIGHT "|"
#define BOX_CROSS_TOP "-"
#define BOX_CROSS_BOT "-"
#define BOX_HEADER_HOR "="
#define BOX_HEADER_LEFT "|"
#define BOX_HEADER_RIGHT "|"
#define BOX_HEADER_MID "="

#endif
/* ============================================================== */

/* ================== Definição de cores ======================== */
#define PARSER_CLEARCOLOR "\033[0m"
#ifdef WITH_TRUECOLOR

#define TREEFADECOLOR "\033[38;2;170;170;170m"
#define TREEACCENTCOLOR "\033[1m"

#define ERR_COLOR "\033[48;2;145;40;40m"
#define ERR_TOKEN ERR_COLOR "<error>" PARSER_CLEARCOLOR
#define ERR_TEMPLATE                                                           \
  ERR_COLOR "  > %s" PARSER_CLEARCOLOR                                         \
            "\n" ERR_COLOR SEPARATOR PARSER_CLEARCOLOR "\n"
#define ERR_LOCATION ERR_COLOR "%s:%d:%d" PARSER_CLEARCOLOR "\n"

#else

#define TREEFADECOLOR "\033[37m"
#define TREEACCENTCOLOR "\033[1m"

#define ERR_COLOR "\033[31;7m"
#define ERR_TOKEN ERR_COLOR "<error>" PARSER_CLEARCOLOR
#define ERR_TEMPLATE                                                           \
  ERR_COLOR "  > %s" PARSER_CLEARCOLOR                                         \
            "\n" ERR_COLOR SEPARATOR PARSER_CLEARCOLOR "\n"
#define ERR_LOCATION ERR_COLOR "%s:%d:%d" PARSER_CLEARCOLOR "\n"
#endif
/* ============================================================== */

typedef struct err_location {
  int errlnum; /* Armazena a linha onde um erro ocorre */
  int errlcol; /* Armazena a coluna onde um erro ocorre */
} err_loc_t;

#define HANDLE_ERROR(ERR_MSG)                                                  \
  {                                                                            \
    got_error = 1;                                                             \
    err_loc_t *loc = removeAt(0, err_loc);                                     \
    fprintf(stderr, ERR_LOCATION, filename, loc->errlnum, loc->errlcol);       \
    fprintf(stderr, ERR_TEMPLATE, ERR_MSG);                                    \
    free(loc);                                                                 \
  }

#define SET_ERROR_LOCATION(LNUM, LCOL, ERR_LOC)                                \
  {                                                                            \
    err_loc_t *loc = (err_loc_t *)malloc(sizeof(err_loc_t));                   \
    loc->errlnum = LNUM;                                                       \
    loc->errlcol = LCOL;                                                       \
    prepend(loc, ERR_LOC);                                                     \
  }

/* Tokens */
#define TOK_EXP "<exp>"
#define TOK_OPBIN "<opbin>"
#define TOK_OPUNI "<opuni>"
#define TOK_IF "<if>"
#define TOK_IF_ELSE "<if_else>"
#define TOK_WHILE "<while>"
#define TOK_FORALL "<forall>"
#define TOK_FOR "<for>"
#define TOK_BREAK "<break>"
#define TOK_RETURN "<return>"
#define TOK_BLOCK "<block>"
#define TOK_EMPTYCMD "<emptycmd>"
#define TOK_EMPTY "EMPTY"
#define TOK_DECLR "<declr>"
#define TOK_PARLIST "<parlist>"
#define TOK_EMPTYEXP "<emptyexp>"
#define TOK_INT "<int>"
#define TOK_FLOAT "<float>"
#define TOK_STRING "<string>"
#define TOK_CHAR "<char>"
#define TOK_OPPOS "<oppos>"
#define TOK_OPTER "<opter>"
#define TOK_OPASSIGN "<opassign>"
#define TOK_FN "<fn>"
#define TOK_ID "<id>"
#define TOK_TYPE "<type>"
#define TOK_DECLR_FN "<declr_fn>"
#define TOK_DECLR_INIT "<declr_init>"

/* Built-ins */
#define BUILTIN_WRITE "write"
#define BUILTIN_WRITELN "writeln"
#define BUILTIN_READ "read"
#define BUILTIN_ISSET "is_set"
#define BUILTIN_ADD "add"
#define BUILTIN_REMOVE "remove"
#define BUILTIN_EXISTS "exists"

#define IS_BUILTIN(fun_name)                                                   \
  (strcmp(fun_name, BUILTIN_WRITE) == 0 ||                                     \
   strcmp(fun_name, BUILTIN_WRITELN) == 0 ||                                   \
   strcmp(fun_name, BUILTIN_READ) == 0 ||                                      \
   strcmp(fun_name, BUILTIN_ISSET) == 0 ||                                     \
   strcmp(fun_name, BUILTIN_ADD) == 0 ||                                       \
   strcmp(fun_name, BUILTIN_REMOVE) == 0 ||                                    \
   strcmp(fun_name, BUILTIN_EXISTS) == 0)

/* Tipos */
#define TYPE_INT "int"
#define TYPE_FLOAT "float"
#define TYPE_ELEM "elem"
#define TYPE_SET "set"

#define FUN_MAIN "main"

#ifdef __GNUC__
#define DEPRECATED(fun) fun __attribute__((deprecated))
#else
#define DEPRECATED(fun) fun
#endif

char *unscape(const char *str);

#endif
