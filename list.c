#include "list.h"
#include <stdio.h>

elem_t create_elem(void *value) {
	elem_t elem = (elem_t) malloc(sizeof(struct elem));
	elem->next = NULL;
	elem->prev = NULL;
	elem->value = value;
	return elem;
}

list_t create_list() {
	list_t list = (list_t) malloc(sizeof(struct list));
	list->first = NULL;
	list->last = NULL;
	list->size = 0;
	return list;
}

void insert(int idx, elem_t elem, list_t list) {
	if (idx < 0 || idx > list->size) {
		fprintf(stderr, "Invalid index in insert()\n");
		exit(EXIT_FAILURE);
	}

	if (list->size == 0) {
		list->first = elem;
		list->last = elem;
		elem->prev = NULL;
		elem->next = NULL;
	} if (idx == list->size) {
		list->last->next = elem;
		elem->prev = list->last;
		elem->next = NULL;
		list->last = elem;
	} else if (idx == 0) {
		list->first->prev = elem;
		elem->next = list->first;
		elem->prev = NULL;
		list->first = elem;
	} else {
		elem_t it = list->first;
		for (int i = 0; i < idx; i++) it = it->next;
		/* it tem o elemento próximo */
		elem->next = it;
		elem->prev = it->prev;
		it->prev->next = elem;
		it->next->prev = elem;
		it->prev = elem;
	}
	list->size++;
}

elem_t removeAt(int idx, list_t list) {
	if (idx < 0 || idx >= list->size) {
		fprintf(stderr, "Invalid index in removeAt()\n");
		exit(EXIT_FAILURE);
	}

	elem_t elem;
	if (idx == 0) {
		elem = list->first;
		list->first = list->first->next;
		if (list->first == NULL) {
			list->last = NULL;
		} else {
			list->first->prev = NULL;
		}
	} else if (idx == list->size) {
		elem = list->last;
		list->last = list->last->prev;
		if (list->last == NULL) {
			list->first = NULL;
		} else {
			list->last->next = NULL;
		}
	} else {
		elem_t it = list->first;
		for (int i = 0; i < idx; i++) it = it->next;
		elem = it;
		it->next->prev = it->prev;
		it->prev->next = it->next;
	}
	elem->next = NULL;
	elem->prev = NULL;
	list->size--;
	return elem;
}

void delete_list(list_t list) {
	elem_t it = list->first;
	while (list->size > 0) {
		delete_elem(removeAt(0, list));
	}
	free(list);
}

void delete_elem(elem_t elem) {
	free(elem);
}
