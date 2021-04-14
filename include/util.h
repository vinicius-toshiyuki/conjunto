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

#define ERR_SEPARATOR "══════════"

#else

#define TREECHILDFIRST "."
#define TREECHILDMID "+"
#define TREECHILDLAST "+"
#define TREECHILD "|"
#define TREELEAF ">"
#define TREEEXTENSION ">"
#define TREEBRANCH "-"

#define ERR_SEPARATOR "=========="
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
            "\n" ERR_COLOR ERR_SEPARATOR PARSER_CLEARCOLOR "\n"
#define ERR_LOCATION ERR_COLOR "%s:%d:%d" PARSER_CLEARCOLOR "\n"

#else

#define TREEFADECOLOR "\033[37m"
#define TREEACCENTCOLOR "\033[1m"

#define ERR_COLOR "\033[31;7m"
#define ERR_TOKEN ERR_COLOR "<error>" PARSER_CLEARCOLOR
#define ERR_TEMPLATE                                                           \
  ERR_COLOR "  > %s" PARSER_CLEARCOLOR                                         \
            "\n" ERR_COLOR ERR_SEPARATOR PARSER_CLEARCOLOR "\n"
#define ERR_LOCATION ERR_COLOR "%s:%d:%d" PARSER_CLEARCOLOR "\n"
#endif
/* ============================================================== */

#endif
