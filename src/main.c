#include <list.h>
//#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
//#include <wchar.h>

void sum(void *a, void *b);
void *idx_mul(int idx, void *value);

int main() {
  // setlocale(LC_ALL, "");
  // wprintf(L"\ue0b0\n");
  list_t list = create_list();
  int i;
  for (i = 0; i < 10; i++) {
    int *val = (int *)malloc(sizeof(int));
    *val = i + 1;
    append(val, list);
  }

  elem_t it;
  for (it = list->first; it != NULL; it = it->next) {
    printf("%d\n", *((int *)it->value));
  }

  int init = 0;
  reduce(sum, &init, list);
  printf("Sum: %d\n", init);

  MAP(
      {
        int val = *((int *)MAP_val);
        if (val % 2 == 0) {
          printf("Par: %d\n", val);
        } else {
          printf("Impar: %d\n", val);
        }
      },
      list);

  iter_t iter = ITERATOR(list, ITER_DOWN);
  printf("===========\n");
  int aa = 0;
  while (ITER_HAS(iter)) {
    printf("%d\n", *ITER(iter, int *, 0));
  }
  printf("===========\n");

  list_t list2 = map(idx_mul, list);

  for (it = list2->first; it != NULL; it = it->next) {
    printf("%d\n", *((int *)it->value));
  }

  init = 0;
  reduce(sum, &init, list2);
  printf("Sum: %d\n", init);

  for_each(free_list, list);
  delete_list(list);
  for_each(free_list, list2);
  delete_list(list2);
  return 0;
}

void sum(void *a, void *b) { *((int *)a) = *((int *)a) + *((int *)b); }
void *idx_mul(int idx, void *value) {
  int *a = (int *)malloc(sizeof(int));
  *a = *((int *)value) * idx;
  return a;
}
