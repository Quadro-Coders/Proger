#include "inttypes.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct list_node {
  int key;
  double value;
  struct list_node *next;
  struct list_node *prev;
} list_node;

list_node *list_init();
list_node *list_create_node();

// добавление в начало
void list_add_front_multi(list_node **head);
list_node *list_add_front(struct list_node *head, int key, double value);
// добавление в конец
void list_add_tail_multi(list_node **head);
list_node *list_add_tail(struct list_node *head, int key, double value);

// добавление по индексу
void list_add_index_multi(list_node **head);
list_node *list_add_index(struct list_node *head, int key, double value,
                          int index);

// поиск по ключу
void list_lookup_multi(list_node *head);
list_node *list_lookup(struct list_node *head, int key);
// очистка списка
void list_clear(list_node **HEAD);
//
void menu();
// удаление элемента по ключу
void list_delete_multi(list_node **head);
list_node *list_delete(struct list_node *head, int key);
// вывод всех элементов
void list_for_each(struct list_node *head);

//
void experiment(list_node **head);

//
int getrand(int min, int max);
double wtime();

//
int input_key(int *key);
int input_value(double *value);
int input_index(int *index);
void menu();