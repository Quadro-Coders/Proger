#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>

typedef struct list_node
{
    int key;
    double value;
    struct list_node *next;
    struct list_node *prev;
} list_node;

// Инициализация
list_node *list_init();
list_node *list_create_node();

// Добавление в начало, O(1)
void list_add_front_multi(list_node **head);
list_node *list_add_front(struct list_node *head, int key, double value);

// Добавление в конец, O(1)
void list_add_tail_multi(list_node **head);
list_node *list_add_tail(struct list_node *head, int key, double value);

// Добавление по индексу
void list_add_index_multi(list_node **head);
list_node *list_add_index(struct list_node *head, int key, double value, int index);

// Добавление из файла (stdin)
void list_add_from_file(list_node **head);

// Поиск по ключу
void list_lookup_multi(list_node *head);
list_node *list_lookup(struct list_node *head, int key);
list_node *list_lookup_silent(struct list_node *head, int key);

// Очистка списка
void list_clear(list_node **HEAD);
void list_clear_silent(list_node **HEAD);

// Удаление элемента по ключу
void list_delete_multi(list_node **head);
list_node *list_delete(struct list_node *head, int key);

// Вывод всех элементов
void list_for_each(struct list_node *head);

// Экспериментальные исследования
void experiment(list_node **head);
void experiment_table(list_node **head);

// Вспомогательные функции
int getrand(int min, int max);
double wtime();
int input_key(int *key);
int input_value(double *value);
int input_index(int *index);
void menu();

#endif
