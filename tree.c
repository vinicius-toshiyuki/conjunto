#include "tree.h"
#include <assert.h>
#include <stdio.h>

node_t create_node(void *value) {
	node_t node = (node_t) malloc(sizeof(struct node));
	assert(node);
	node->parent = NULL;
	node->value = value;
	node->children = create_list();
	return node;
}

void add_child(node_t child, node_t node) {
	child->parent = node;
	insert(node->children->size, create_elem(child), node->children);
}

node_t remove_node(node_t node) {
	elem_t it = node->parent->children->first;
	int i = 0;
	while (it->value != node) it = it->next, i++;
	node_t ret = removeAt(i, node->parent->children)->value;
	node->parent = NULL;
	return ret;
}

void delete_node(node_t node) {
	/* TODO */
}

size_t level(node_t node) {
	size_t l = 0;
	while (node != NULL) {
		l++;
		node = node->parent;
	}
	return l;
}

void breadth(void (*action)(node_t node, void *data), node_t node, void *data, void (*init)(), void (*end)()) {
	if (init != NULL) {
		init();
	}
	list_t queue = create_list();
	insert(0, create_elem(node), queue); // Queue first node
	while (queue->size > 0) { // While has node in queue
		node_t cur = (node_t) queue->first->value;
		action(cur, data);
		elem_t it = cur->children->first;
		while (it != NULL) {
			insert(queue->size, create_elem(it->value), queue); // Queue leaf nodes
			it = it->next;
		}
		delete_elem(removeAt(0, queue));
	}
	if (end != NULL) {
		end();
	}
}

void depth(void (*action)(node_t node, void *data), int mode, node_t node, void *data) {
	if (node != NULL) {
		if (mode == DEPTHPRE) {
			action(node, data);
		}
		elem_t it = node->children->first;
		while (it != NULL) {
			depth(action, mode, it->value, data);
			it = it->next;
		}
		if (mode == DEPTHPOS) {
			action(node, data);
		}
	}
}

void depth_pre(void (*action)(node_t node, void *data), node_t node, void *data, void (*init)(), void (*end)()) {
	if (init != NULL) {
		init();
	}
	depth(action, DEPTHPRE, node, data);
	if (end != NULL) {
		end();
	}
}

void depth_pos(void (*action)(node_t node, void *data), node_t node, void *data, void (*init)(), void (*end)()) {
	if (init != NULL) {
		init();
	}
	depth(action, DEPTHPOS, node, data);
	if (end != NULL) {
		end();
	}
}
