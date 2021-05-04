#ifndef __TRANSLATION_H__
#define __TRANSLATION_H__

#include <context.h>
#include <syntatic_node.h>
#include <tree.h>

enum { T9N_DECLR_FN, T9N_CODE };

typedef struct t9n {
  int type;
  void *value;
} * t9n_t;

typedef struct t9n_data {
  node_t context;
  list_t temps;
  char *curfun;
  list_t loops;
} t9n_data_t;

t9n_t create_t9n(int type, void *value);
void delete_t9n(t9n_t t9n);

void translate(node_t tree, node_t context);

void create_table(node_t tree);
void __create_table_header();
int __create_table(node_t node, void *data);
void create_code(node_t tree, node_t context);
int __create_code(node_t node, void *data);
void __create_code_header();
node_t get_translation_tree(node_t tree);
int __get_exp_code(node_t node, void *value);
void __translate_bin_exp(node_t op, t9n_data_t *data);
void __translate_uni_exp(node_t op, t9n_data_t *data);
void __translate_cast(node_t node, t9n_data_t *data);
const char *tac_op_string(int type);

CTX_sym_t get_symbol_identifier(char *name, char *id, node_t context);
int __get_symbol_identifier(node_t node, void *data);
size_t __get_declr_index(char *id, char *curfun, node_t context);

void __get_fun_suffix(char *fun_name, node_t context, char *buffer);
int __search_fun(node_t node, void *data);

#endif
