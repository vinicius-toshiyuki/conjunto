#include <set.h>
#include <stdio.h>
#include <stdlib.h>

set_t create_set() { return create_list(); }

void delete_set(set_t set) {
  MAP(delete_set_elem(MAP_val), set);
  delete_list(set);
}

set_elem_t create_set_elem(int data_type, void *value,
                           int (*comparator)(void *a, void *b),
                           void (*destructor)(void *value)) {
  set_elem_t elem = (set_elem_t)malloc(sizeof(struct set_elem));
  elem->data_type = data_type;
  elem->value = value;
  elem->comparator = comparator;
  elem->destructor = destructor;
  return elem;
}

void delete_set_elem(set_elem_t elem) {
  if (elem->destructor != NULL) {
    elem->destructor(elem->value);
  }
  free(elem);
}

int set_add(set_elem_t elem, set_t set) {
  if (set_in(elem, set) == NULL) {
    append(elem, set);
    return 1;
  }
  return 0;
}

set_elem_t set_remove(set_elem_t elem, set_t set) {
  int idx = -1;
  MAP(
      if (elem->data_type == SET_ELEM(MAP_val)->data_type &&
          elem->comparator(elem->value, SET_ELEM(MAP_val)->value) == 0) {
        idx = MAP_i;
        break;
      },
      set);
  if (idx < 0) {
    fprintf(stderr, "Element not in set in set_remove()\n");
    exit(EXIT_FAILURE);
  }
  return removeAt(idx, set);
}

set_elem_t set_in(set_elem_t elem, set_t set) {
  set_elem_t found = NULL;
  MAP(
      if (elem->data_type == SET_ELEM(MAP_val)->data_type &&
          elem->comparator(elem->value, SET_ELEM(MAP_val)->value) == 0) {
        found = MAP_val;
        break;
      },
      set);
  return found;
}
