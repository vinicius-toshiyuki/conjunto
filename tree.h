#ifndef __TREE_H__
#define __TREE_H__

#include "list.h"

enum {
	DEPTHPRE,
	DEPTHPOS
};

typedef struct node {
	struct node *parent;
	void *value;
	list_t children;
} * node_t;

node_t create_node(void *value);

void add_child(node_t child, node_t node);
node_t remove_node(node_t node);

void delete_node(node_t node);

size_t level(node_t node);

void breadth(void (*action)(node_t node, void *data), node_t node, void *data, void (*init)(), void (*end)());
void depth_pre(void (*action)(node_t node, void *data), node_t node, void *data, void (*init)(), void (*end)());
void depth_pos(void (*action)(node_t node, void *data), node_t node, void *data, void (*init)(), void (*end)());

#endif
