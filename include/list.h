#ifndef __LIST_H__
#define __LIST_H__

#include <stdlib.h>

enum { ITER_DOWN, ITER_UP };

/**
 * Armazena um elemento de lista.
 * Deve ser usado pelos usuários para iterar sobre uma lista.
 * Quando um elemento é o primeiro ou último de uma lista, o valor de `prev` e
 * `next` é NULL, respectivamente.
 */
typedef struct elem {
  void *value;       /* Valor do elemento */
  struct elem *next; /* Aponta para o próximo elemento */
  struct elem *prev; /* Aponta para o elemento anterior */
} * elem_t;

/**
 * Representa um iterador de uma lista;
 */
typedef struct iter {
  elem_t cur;
  int direction;
  void *value;
} iter_t;

/**
 * Representa uma lista.
 * Todos os valores devem ser usados como 'read-only'.
 * `first` e `last` são NULL sse `size` == 0.
 */
typedef struct list {
  elem_t first; /* Aponta para o primeiro elemento da lista */
  elem_t last;  /* Aponta para o último elemento da lista */
  size_t size;  /* Contém o tamanho da lista */
} * list_t;

/**
 * Cria um elemento.
 * Não precisa ser usada a não ser que saiba o que está fazendo.
 */
elem_t create_elem(void *value);

/**
 * Cria uma nova lista
 */
list_t create_list();

/**
 * Insere um valor em uma lista.
 */
void insert(int idx, void *value, list_t list);

/**
 * Insere um valor no final de uma lista.
 */
void append(void *value, list_t list);

/**
 * Insere um valor no começo de uma lista.
 */
void prepend(void *value, list_t list);

/**
 * Remove um valor de uma lista e o retorna.
 */
void *removeAt(int idx, list_t list);

/**
 * Retorna o elemento em uma posição da lista.
 */
void *elementAt(int idx, list_t list);

/**
 * Procura por um valor na lista.
 * A comparação de itens é feita com seus endereços de memória.
 * Para uma busca com alguma função específica veja reduce().
 */
int indexOf(void *value, list_t list);

/**
 * Mapeia uma função sobre uma lista e retorna uma nova lista com os resultados.
 * Não deve ser usada para alterar os itens de uma lista 'in place', use
 * for_each().
 */
list_t map(void *(*action)(int index, void *value), list_t list);

/**
 * Aplica uma função sobre uma lista e atualiza seus itens com os resultados.
 * Os retornos de `action` substituem os items na lista, então caso esses
 * retornos não sejam os mesmos ponteiros originais, a memória dos itens antigos
 * deve ser liberada dentro de `action`.
 */
void for_each(void *(*action)(int index, void *value), list_t list);

/**
 * Reduz uma lista a um valor.
 * `value` é usado para passar o valor inicial de `reduction` em `action` e
 * também é usado para armazenar o resultado final. O ponteiro retornado é o
 * mesmo de `value`.
 */
void *reduce(void (*action)(void *reduction, void *value), void *value,
             list_t list);

/**
 * Itera sobre uma lista e executa o código passado em `MAP_code`.
 * O valor do elemento atual na iteração está disponível em `MAP_val`.
 * Diferente da função map(), essa macro não cria uma nova lista nem atualiza os
 * valores dos elementos (diretamente), simplesmente executa um loop com tantas
 * iterações quanto elementos na lista.
 */
#define MAP(MAP_code, MAP_list)                                                \
  {                                                                            \
    void *MAP_val;                                                             \
    elem_t MAP_it = ((list_t)MAP_list)->first;                                 \
    for (size_t MAP_i = 0; MAP_i < ((list_t)MAP_list)->size; MAP_i++) {        \
      MAP_val = MAP_it->value;                                                 \
      MAP_code;                                                                \
      MAP_it = MAP_it->next;                                                   \
      if (MAP_val)                                                             \
        ;                                                                      \
    }                                                                          \
  }

/**
 * Retorna um iterador de uso único da lista.
 * Itera do começo até o fim se a direção for ITER_UP e do fim até o começo se a
 * direção for ITER_DOWN.
 */
#define ITERATOR(ITER_list, ITER_dir)                                          \
  ((iter_t){(ITER_dir == ITER_UP ? ITER_list->first : ITER_list->last),        \
            ITER_dir, NULL})

/**
 * Itera uma vez sobre um iterador e retorna um valor do tipo indicado.
 * O valor retornado é ((`ITER_iter`)<valor>).
 * Caso o valor do iterador seja NULL, o valor retornado é `ITER_default`.
 */
#define ITER(ITER_iter, ITER_type, ITER_default)                               \
  (((ITER_iter.cur =                                                           \
         ITER_iter.cur == NULL ||                                              \
                 ((ITER_iter.value = ITER_iter.cur->value) && 0)               \
             ? NULL                                                            \
             : (ITER_iter.direction == ITER_UP ? ITER_iter.cur->next           \
                                               : ITER_iter.cur->prev)) &&      \
    0)                                                                         \
       ? *((ITER_type *)NULL) /* Nunca acontece */                             \
       : (ITER_iter.value != NULL ? ((ITER_type)ITER_iter.value)               \
                                  : ITER_default))

/**
 * Retorna o valor atual do iterador.
 * Diferente de ITER(), o valor retornado não é dereferenciado e um ponteiro de
 * void é retornado.
 */
#define ITER_TOP(ITER_iter) (ITER_iter.cur->value)

/**
 * Retorna o mesmo valor retornado pela última chamada de ITER().
 * O valor não é dereferenciado.
 */
#define ITER_OLD(ITER_iter) (ITER_iter.value)

/**
 * Checa se o iterador ainda tem itens.
 */
#define ITER_HAS(ITER_iter) (ITER_iter.cur != NULL)

/**
 * Deleta uma lista e limpa a memória alocada.
 * Os valores de cada elemento não são modificados e devem ter suas memórias
 * liberadas antes de deletar a lista. A função free_list() pode ser usada com
 * for_each() para fazer a liberação 'simples' da memória de cada valor da
 * lista.
 */
void delete_list(list_t list);

/**
 * Simplemente chama free() sobre `value`.
 * Compatível com a função for_each().
 */
void *free_list(int idx, void *value);

#endif
