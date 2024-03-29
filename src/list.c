#include "../include/list.h"
#include <stdio.h>

elem_t create_elem(void *value) {
  elem_t elem = (elem_t)malloc(sizeof(struct elem));
  elem->next = NULL;
  elem->prev = NULL;
  elem->value = value;
  return elem;
}

list_t create_list() {
  list_t list = (list_t)malloc(sizeof(struct list));
  list->first = NULL;
  list->last = NULL;
  list->size = 0;
  return list;
}

void insert(int idx, void *value, list_t list) {
  if (idx < 0 || idx > list->size) {
    fprintf(stderr, "Invalid index in insert()\n");
    exit(EXIT_FAILURE);
  }

  elem_t elem = create_elem(value);
  if (list->size == 0) {
    list->first = elem;
    list->last = elem;
    elem->prev = NULL;
    elem->next = NULL;
  } else if (idx == list->size) {
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
    for (int i = 0; i < idx; i++)
      it = it->next;
    /* it tem o elemento próximo */
    elem->next = it;
    elem->prev = it->prev;
    it->prev->next = elem;
    it->next->prev = elem;
    it->prev = elem;
  }
  list->size++;
}

void append(void *value, list_t list) { insert(list->size, value, list); }

void prepend(void *value, list_t list) { insert(0, value, list); }

void *removeAt(int idx, list_t list) {
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
  } else if (idx == list->size - 1) {
    elem = list->last;
    list->last = list->last->prev;
    if (list->last == NULL) {
      list->first = NULL;
    } else {
      list->last->next = NULL;
    }
  } else {
    elem_t it = list->first;
    for (int i = 0; i < idx; i++)
      it = it->next;
    elem = it;
    it->next->prev = it->prev;
    it->prev->next = it->next;
  }
  elem->next = NULL;
  elem->prev = NULL;
  list->size--;
  void *ret = elem->value;
  free(elem);
  return ret;
}

void *elementAt(int idx, list_t list) {
  if (idx < 0 || idx >= list->size) {
    fprintf(stderr, "Invalid index in elementAt(): %d\n", idx);
    exit(EXIT_FAILURE);
  }
  void *ret = NULL;
  MAP(
      if (MAP_i == idx) { ret = MAP_val; }, list);

  return ret;
}

int indexOf(void *value, list_t list) {
  elem_t it = list->first;
  int ret = -1, i = 0;
  while (it != NULL) {
    if (value == it->value) {
      ret = i;
      break;
    }
    it = it->next;
    i++;
  }
  return ret;
}

void delete_list(list_t list) {
  while (list->size > 0) {
    removeAt(0, list);
  }
  free(list);
}

list_t map(void *(*action)(int index, void *value), list_t list) {
  list_t new = create_list();
  elem_t it;
  int i;
  for (i = 0, it = list->first; it != NULL; it = it->next, i++) {
    append(action(i, it->value), new);
  }
  return new;
}

void for_each(void *(*action)(int index, void *value), list_t list) {
  elem_t it;
  int i;
  for (i = 0, it = list->first; it != NULL; it = it->next, i++) {
    it->value = action(i, it->value);
  }
}

void *reduce(void (*action)(void *reduction, void *value), void *value,
             list_t list) {
  void *res = value;
  elem_t it;
  for (it = list->first; it != NULL; it = it->next) {
    action(res, it->value);
  }
  return res;
}

void *free_list(int idx, void *value) {
  free(value);
  return value;
}
