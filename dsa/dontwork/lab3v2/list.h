#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

struct list_head
{
    struct list_head *next;
    struct list_head *prev;
};

struct data
{
    int key;
    double value;
    struct list_head list; /* Включение списка в структуру */
};

#define container_of(ptr, type, member) ({ \
    void *__mptr = (void *)(ptr); \
    ((type *)(__mptr - offsetof(type, member))); })

#define LIST_HEAD_INIT(name) {&(name), &(name)}

#define LIST_HEAD(name) \
    struct list_head name = LIST_HEAD_INIT(name)

static inline void init_list_head(struct list_head *head)
{
    head->next = head;
    head->prev = head;
}

/* Итерация по списку */
#define list_for_each(pos, head) \
    for (pos = (head)->next; pos != (head); pos = pos->next)

/* Безопасная итерация (для удаления элементов в цикле) */
#define list_for_each_safe(pos, n, head) \
    for (pos = (head)->next, n = pos->next; pos != (head); pos = n, n = pos->next)

static inline double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

static inline int getrand(int min, int max)
{
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

void data_add_front(struct list_head *head, int key, double value);
void data_add_tail(struct list_head *head, int key, double value);
void data_delete(struct list_head *head, int key);
double data_lookup(struct list_head *head, int key);
void list_print(struct list_head *head);
void list_clear(struct list_head *head);
int list_add_from_stdin(struct list_head *head);
int list_count(struct list_head *head);

static inline void __list_add(struct list_head *new_node, struct list_head *prev, struct list_head *next)
{
    next->prev = new_node;
    new_node->next = next;
    new_node->prev = prev;
    prev->next = new_node;
}

static inline void __list_del(struct list_head *prev, struct list_head *next)
{
    next->prev = prev;
    prev->next = next;
}

#endif
