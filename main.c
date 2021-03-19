#include <stdio.h>
#include "tree.h"
#include <assert.h>

void print(node_t node, void *data);
void printend() {
	printf("\n");
}

int main() {
	node_t node = create_node("raiz");
	add_child(create_node("folha 1"), node);
	add_child(create_node("folha 2"), node);

	int l = level(node);
	breadth(print, node, &l, NULL, printend);
	printf("\n");

	node_t root = create_node("raiz verdadeira");
	add_child(node, root);

	l = level(root);
	depth_pre(print, root, &l, NULL, printend);
	printf("\n");

	remove_node(node);

	l = level(root);
	breadth(print, root, &l, NULL, printend);
	printf("\n");

	l = level(node);
	breadth(print, node, &l, NULL, printend);
	printf("\n");

	return 0;
}

void print(node_t node, void *data) {
	assert(data);
	int l = *((int *) data);
	if (l < level(node)) {
		*((int *) data) = level(node);
		//printf("\n");
	}
	l = level(node);
	for (int i = 0; i < l - 1; i++) {
		printf("  ");
	}
	if (l > 1) {
		printf("|---> ");
	}
	printf("%s\n", (char *) node->value);
}
