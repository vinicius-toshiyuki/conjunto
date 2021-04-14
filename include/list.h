#ifndef __LIST_H__
#define __LIST_H__

#include <stdlib.h>

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
void *removeAt(int idx, list_t);

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
      MAP_code MAP_it = MAP_it->next;                                          \
    }                                                                          \
  }

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

/* TODO: Iterator com índice? Para não ter que mexer mesmo com elem_t e permitir
 * organizar a lista em buckets */

#endif
