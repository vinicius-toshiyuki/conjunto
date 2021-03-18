#ifndef __TREE_H__
#define __TREE_H__

#include "list.h"

typedef struct node {
	struct node *parent;
	void *value;
	list_t children;
} * node_t;

typedef struct tree {
	node_t root;
} * tree_t;

node_t create_node(void *value);
tree_t create_tree();

void add_child(node_t child, node_t node);
tree_t remove_node(node_t node);

void delete_node(node_t node);
void delete_tree(tree_t tree);

void print_tree(tree_t tree);

#endif
