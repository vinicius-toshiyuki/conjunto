#ifndef __LIST_H__
#define __LIST_H__

#include <stdlib.h>

typedef struct elem {
	void *value;
	struct elem * next;
	struct elem * prev;
} * elem_t;

typedef struct list {
	elem_t first;
	elem_t last;
	size_t size;
} * list_t;

elem_t create_elem(void *value);
list_t create_list();

void insert(int idx, elem_t elem, list_t list);
elem_t removeAt(int idx, list_t);

void delete_list(list_t list);
void delete_elem(elem_t elem);

#endif
