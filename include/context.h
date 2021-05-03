#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include <list.h>
#include <tree.h>

/**
 * Tipos de símbolos.
 * TODO: adicionar constantes?
 */
enum { CTX_VAR = 0, CTX_FUN };

/**
 * Tipos primitivos dos valores dos símbolos.
 */
enum {
  CTX_INV = -2,
  CTX_UNK = -1,
  CTX_INT = 0,
  CTX_FLOAT,
  CTX_CHAR,
  CTX_ELEM,
  CTX_SET,
  CTX_INEXP
};

/**
 * Um símbolo da tabela de símbolos.
 */
typedef struct ctx_symbol {
  int type;      /* Tipo do símbolo                    */
  char *id;      /* Identificador do símbolo           */
  int data_type; /* Tipo primitivo do valor do símbolo */
  int lnum;      /* Linha onde foi declarado           */
  int lcol;      /* Coluna onde foi declarado          */
} * CTX_sym_t;

/**
 * Um símbolo de variável de tipo primitivo.
 * Herda de CTX_id_t.
 */
typedef struct ctx_variable {
  int type;
  char *id;
  int data_type;
  int lnum;
  int lcol;
  int secondary_data_type; /* Tipo secundário da variável polimórfica   */
  void *value;             /* Valor da variável (pode ser NULL)         */
  int depth;               /* Número de dimensões (> 0 é ponteiro)      */
  int *length;             /* Tamanho de cada dimensão (se `depth` > 0) */
} * CTX_var_t;

/**
 * Um símbolo de função.
 * Herda de CTX_id_t.
 * TODO: permitir lista de lista de parâmetros (overload)
 * TODO: (depooooois) permitir diferentes retornos (unificar com os parâmetros)
 */
typedef struct ctx_function {
  int type;
  char *id;
  int data_type;
  int lnum;
  int lcol;
  list_t params;  /* Símbolos dos parâmetros */
  node_t context; /* Contexto criado para a função */
} * CTX_fun_t;

/**
 * Faz o cast de um ponteiro para (CTX_sym_t).
 */
#define CTX_SYM(CTX_pointer) ((CTX_sym_t)CTX_pointer)
/**
 * Faz o cast de um símbolo para (CTX_var_t).
 */
#define CTX_VAR(CTX_sym) ((CTX_var_t)CTX_sym)
/**
 * Faz o cast de um símbolo para (CTX_fun_t).
 */
#define CTX_FUN(CTX_sym) ((CTX_fun_t)CTX_sym)

/**
 * Cria um símbolo do tipo `type`.
 */
CTX_sym_t create_symbol(int type, char *id, int data_type, int lnum, int lcol);

/**
 * Libera a memória usada por um símbolo.
 * Para o tipo VAR, `value` não é deletado da memória.
 */
void delete_symbol(CTX_sym_t sym);

/**
 * Inicializa os valores de `var`.
 */
void init_ctx_var(void *value, int depth, int *length, CTX_var_t var);

/**
 * Inicializa os valores de `fun`.
 */
void init_ctx_fun(list_t params, CTX_fun_t fun);

/**
 * Procura o símbolo com nome `id` mais próximo subindo no nó `ctx`.
 */
CTX_sym_t lookup_symbol(char *id, node_t ctx);

/**
 * Checa se o contexto `local_ctx` tem o símbolo com nome `id`.
 * Retorna 0 se houver.
 * TODO: trocar para 1
 */
int has_symbol(char *id, list_t local_ctx);

/**
 * Retorna uma string que representa o tipo de símbolo `type`.
 */
const char *type_string(int type);

/**
 * Retorna o código do tipo de símbolo `type`.
 */
const int type_code(const char *type);

/**
 * Retorna uma string que representa o tipo de dados `type`.
 */
const char *data_type_string(int type);

/**
 * Retorna o código do tipo de dados `type`.
 */
const int data_type_code(const char *type);

/**
 * Compara dois símbolos pelo nome.
 * Usado como `comparator` para um set.
 */
int compare_symbol(void *a, void *b);

#endif
