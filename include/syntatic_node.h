#ifndef __SYNTATIC_VALUE_H__
#define __SYNTATIC_VALUE_H__

#include <context.h>
#include <tree.h>

/**
 * Indica os tipos de valores da árvore sintática.
 * TODO: conflita com as macros de cast?
 */
enum { SYN_TAG = 0, SYN_EXP, SYN_EXP_COMP, SYN_OP, SYN_TYPE };

enum {
  OP_UNK = -1,
  OP_ASSIGN = 0,
  OP_ASSIGN_ADD,
  OP_ASSIGN_SUB,
  OP_ASSIGN_MUL,
  OP_ASSIGN_DIV,
  OP_ASSIGN_OR,
  OP_ASSIGN_AND,
  OP_ASSIGN_XOR,
  OP_TER_FIRST,
  OP_TER_LAST,
  OP_BIN_OR,
  OP_BIN_AND,
  OP_BIN_BIT_OR,
  OP_BIN_BIT_AND,
  OP_BIN_XOR,
  OP_BIN_EQ,
  OP_BIN_NEQ,
  OP_BIN_LT,
  OP_BIN_GT,
  OP_BIN_LTE,
  OP_BIN_GTE,
  OP_BIN_SHIFT_L,
  OP_BIN_SHIFT_R,
  OP_BIN_IN,
  OP_PLUS,
  OP_MINUS,
  OP_STAR,
  OP_DIV,
  OP_MOD,
  OP_UNI_INC,
  OP_UNI_DEC,
  OP_UNI_REF,
  OP_UNI_NEG,
  OP_UNI_BIT_NEG,
  OP_POS_INC,
  OP_POS_DEC
};

/**
 * Armazena um valor genérico da árvore sintática.
 */
typedef struct syn_value {
  char *name; /* Armazena o nome apresentado na impressão da árvore sintática */
  int type; /* Armazena o tipo de valor sintático armazenado */
} * SYN_value_t;

/**
 * Armazena uma expressão da árvore sintática.
 * Herda de SYN_value_t.
 */
typedef struct syn_exp {
  char *name;
  int type;
  int data_type; /* Armazena o tipo de dados armazenado como em context.h */
  int depth;     /* Armazena a profundidade dos dados armazenados (ponteiro) */
} * SYN_exp_t;

/**
 * Armazena uma expressão composta da árvore sintática.
 */
typedef SYN_exp_t SYN_exp_comp_t;

/**
 * Armazena uma tag da árvore sintática.
 * Herda de SYN_value_t.
 */
typedef struct syn_tag {
  char *name;
  int type;
} * SYN_tag_t;

/**
 * Armazena um operador da árvore sintática.
 * Herda de SYN_value_t.
 */
typedef struct syn_op {
  char *name;
  int type;
  int op_type;
} * SYN_op_t;

/**
 * Armazena um tipo da árvore sintática.
 * Herda de SYN_value_t.
 */
typedef struct syn_type {
  char *name;
  int type;
} * SYN_type_t;

/**
 * Faz o cast de um ponteiro para (SYN_value_t).
 */
#define SYN_VALUE(SYN_val) ((SYN_value_t)SYN_val)

/**
 * Faz o cast de um ponteiro para (SYN_exp_t).
 */
#define SYN_EXP(SYN_val) ((SYN_exp_t)SYN_val)

/**
 * Faz o cast de um ponteiro para (SYN_exp_comp_t).
 */
#define SYN_EXP_COMP(SYN_val) ((SYN_exp_comp_t)SYN_val)

/**
 * Faz o cast de um ponteiro para (SYN_tag_t).
 */
#define SYN_TAG(SYN_val) ((SYN_tag_t)SYN_val)

/**
 * Faz o cast de um ponteiro para (SYN_op_t).
 */
#define SYN_OP(SYN_val) ((SYN_op_t)SYN_val)

/**
 * Faz o cast de um ponteiro para (SYN_type_t).
 */
#define SYN_TYPE(SYN_val) ((SYN_type_t)SYN_val)

/**
 * Cria um valor para um nó da árvore sintática abstrata do tipo especificado.
 * `name` é o nome mostrado na impressão da árvore.
 */
SYN_value_t create_syn_val(int type, char *name);

/**
 * Limpa a memória usada por um valor sintático.
 */
void delete_syn_val(SYN_value_t value);

/**
 * Inicializa um valor sintático de expressão.
 * TODO: acho que está repetindo muita coisa do CTX_var_t.
 */
void init_syn_exp(int data_type, int depth, SYN_exp_t exp);

/**
 * Inicializa um valor sintático de uma tag genérica.
 */
void init_syn_tag(SYN_tag_t tag);

/**
 * Inicializa um valor sintático de um operador.
 */
void init_syn_op(int op_type, SYN_op_t op);

/**
 * Inicializa um valor sintático de um tipo de dados.
 */
void init_syn_type(SYN_type_t type);

void print_syn_exp(SYN_exp_t exp);

const char *operator_string(int code);
int operator_code(const char *string);

#endif
