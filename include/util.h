#ifndef __UTIL_H__
#define __UTIL_H__

#include <config.h>
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

#else

#define TREECHILDFIRST "."
#define TREECHILDMID "|"
#define TREECHILDLAST "+"
#define TREECHILD "|"
#define TREELEAF ">"
#define TREEEXTENSION "~"
#define TREEBRANCH "-"

#define SEPARATOR "=========="

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
    err_loc_t *loc = removeAt(0, err_loc);                                     \
    fprintf(stderr, ERR_LOCATION, filename, loc->errlnum, loc->errlcol);       \
    fprintf(stderr, ERR_TEMPLATE, ERR_MSG);                                    \
    free(loc);                                                                 \
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
#define TOK_RETURN "<return>"
#define TOK_BLOCK "<block>"
#define TOK_EMPTYCMD "<emptycmd>"
#define TOK_EMPTY "<empty>"
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

#define IS_TOK(TOK)                                                            \
  (((char *)TOK) == &ERR_TOKEN[0] || ((char *)TOK) == &TOK_EXP[0] ||           \
   ((char *)TOK) == &TOK_OPBIN[0] || ((char *)TOK) == &TOK_OPUNI[0] ||         \
   ((char *)TOK) == &TOK_IF[0] || ((char *)TOK) == &TOK_IF_ELSE[0] ||          \
   ((char *)TOK) == &TOK_WHILE[0] || ((char *)TOK) == &TOK_FORALL[0] ||        \
   ((char *)TOK) == &TOK_FOR[0] || ((char *)TOK) == &TOK_RETURN[0] ||          \
   ((char *)TOK) == &TOK_BLOCK[0] || ((char *)TOK) == &TOK_EMPTYCMD[0] ||      \
   ((char *)TOK) == &TOK_EMPTY[0] || ((char *)TOK) == &TOK_DECLR[0] ||         \
   ((char *)TOK) == &TOK_PARLIST[0] || ((char *)TOK) == &TOK_EMPTYEXP[0] ||    \
   ((char *)TOK) == &TOK_INT[0] || ((char *)TOK) == &TOK_FLOAT[0] ||           \
   ((char *)TOK) == &TOK_STRING[0] || ((char *)TOK) == &TOK_CHAR[0] ||         \
   ((char *)TOK) == &TOK_OPPOS[0] || ((char *)TOK) == &TOK_OPTER[0] ||         \
   ((char *)TOK) == &TOK_OPASSIGN[0] || ((char *)TOK) == &TOK_FN[0] ||         \
   ((char *)TOK) == &TOK_ID[0] || ((char *)TOK) == &TOK_TYPE[0] ||             \
   ((char *)TOK) == &TOK_DECLR_FN[0] || ((char *)TOK) == &TOK_DECLR_INIT[0])

#endif
