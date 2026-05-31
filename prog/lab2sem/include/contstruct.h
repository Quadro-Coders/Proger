#ifndef CONTSTRUCT_H
#define CONTSTRUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>
#include "matrix2d.h"

// Тип данных в очереди — указатель на Matrix2D
typedef Matrix2D *QueueValue;

// Узел очереди (один элемент)
typedef struct QueueNode
{
    QueueValue data;
    struct QueueNode *next;
} QueueNode;

// Итератор для перебора
typedef struct QueueIterator
{
    QueueNode *current;
    struct Queue *queue;
} QueueIterator;

// Сама очередь
typedef struct Queue
{
    QueueNode *front; // Первый элемент (отсюда удаляем)
    QueueNode *back;  // Последний элемент (сюда добавляем)
    size_t size;      // Количество элементов
    size_t capacity;  // Ёмкость (для резервирования)
} Queue;

// ========== Конструкторы и деструктор ==========
Queue *queue_create(void);
void queue_free(Queue *q);

// ========== Задание 3 ==========
int queue_enqueue(Queue *q, QueueValue value);
QueueValue queue_dequeue(Queue *q);
int queue_is_empty(const Queue *q);

// ========== Задание 4 ==========
size_t queue_size(const Queue *q);
QueueValue queue_peek(const Queue *q);
void queue_clear(Queue *q);

// ========== Задание 5 ==========
int queue_fenqueue(Queue *q, QueueValue value);
Queue *queue_copy(const Queue *q);
Queue *queue_merge(Queue *q1, Queue *q2);

// Итераторы
QueueIterator queue_begin(Queue *q);
QueueIterator queue_end(Queue *q);
int queue_iterator_next(QueueIterator *it);
int queue_iterator_equal(QueueIterator it1, QueueIterator it2);
int queue_iterator_points_to(QueueIterator it, Queue *q);

// Резервирование памяти (коэффициент √2)
void queue_reserve(Queue *q, size_t new_capacity);

#endif
