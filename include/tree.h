#ifndef __TREE_H__
#define __TREE_H__

#include "list.h"

enum { DEPTHPRE, DEPTHPOS };

typedef struct node {
  void *value;
  struct node *parent;
  list_t children;
  int id;
} * node_t;

/**
 * Cria um nó e associa `value` a ele.
 */
node_t create_node(void *value);

/**
 * Adiciona um nó como filho de outro.
 */
void add_child(node_t child, node_t node);

/**
 * Remove um nó do seu pai.
 * Retorna o próprio nó.
 */
node_t remove_node(node_t node);

/**
 * Libera a memória usada por um nó.
 * O valor do nó não é liberado.
 */
void delete_node(node_t node);

/**
 * Retorna o nível do nó a partir da raiz começando em 1.
 */
size_t level(node_t node);

/**
 * Percorre a árvore em largura executando `action` sobre cada nó.
 * `data` é passado para cada chamada a `action`.
 */
void breadth(void (*action)(node_t node, void *data), node_t node, void *data,
             void (*init)(), void (*end)());

/**
 * Percorre a árvore em pré-ordem executando `action` sobre cada nó.
 * `data` é passado para cada chamada a `action`.
 */
void depth_pre(void (*action)(node_t node, void *data), node_t node, void *data,
               void (*init)(), void (*end)());

/**
 * Percorre a árvore em pós-ordem executando `action` sobre cada nó.
 * `data` é passado para cada chamada a `action`.
 */
void depth_pos(void (*action)(node_t node, void *data), node_t node, void *data,
               void (*init)(), void (*end)());

#endif
