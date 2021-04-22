#ifndef __SET_H__
#define __SET_H__

#include <list.h>

/**
 * Representa um elemento em um conjunto.
 */
typedef struct set_elem {
  int data_type; /* O tipo de dados do elemento */
  void *value;   /* O valor do elemento */
  int (*comparator)(void *a,
                    void *b); /* Compara dois elementos de mesmo `data_type` */
  void (*destructor)(void *value); /* Libera a memória de um elemento */
} * set_elem_t;

/**
 * Representa um conjunto.
 * Não existem elementos repetidos em um conjunto.
 */
typedef list_t set_t;

/**
 * Faz o cast para set_elem_t.
 */
#define SET_ELEM(ELEM) ((set_elem_t)ELEM)

/**
 * Cria um conjunto vazio
 */
set_t create_set();
/**
 * Libera a memória usada por um conjunto.
 * Os `value` em cada set_elem_t são liberados usando o `destructor`.
 */
void delete_set(set_t set);

/**
 * Cria um elemento de um conjunto.
 * A função `comparator` é usada para comparar dois elementos dentro de um
 * conjunto que tenham o mesmo `data_type`.
 */
set_elem_t create_set_elem(int data_type, void *value,
                           int (*comparator)(void *a, void *b),
                           void (*destructor)(void *value));

/**
 * Libera a memória utilizada por um elemento.
 * O `value` de um elemento é liberado pelo `destructor` se for diferente de
 * NULL.
 */
void delete_set_elem(set_elem_t elem);

/**
 * Adiciona um elemento em um conjunto, se já não estiver.
 * Retorna 1 se teve sucesso, 0 caso contrário.
 */
int set_add(set_elem_t elem, set_t set);

/**
 * Remove um elemento do conjunto e o retorna.
 * Lança um erro caso o elemento não esteja presente no conjunto.
 */
set_elem_t set_remove(set_elem_t elem, set_t set);

/**
 * Procura por um elemento dentro de um conjunto.
 * Retorna NULL caso o elemento não esteja presente.
 */
set_elem_t set_in(set_elem_t elem, set_t set);

#endif
