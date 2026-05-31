#ifndef CONTSTRUCT_H
#define CONTSTRUCT_H

#include <stdio.h>
#include <stddef.h>
#include <math.h>
#include <stdlib.h>

// Тип данных в очереди (можно менять)
typedef int QueueValue;

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
int queue_enqueue(Queue *q, QueueValue value); // Добавить в конец
QueueValue queue_dequeue(Queue *q);            // Удалить первый
int queue_is_empty(const Queue *q);            // Проверка на пустоту

// ========== Задание 4 ==========
size_t queue_size(const Queue *q);     // Размер
QueueValue queue_peek(const Queue *q); // Посмотреть первый
void queue_clear(Queue *q);            // Очистить

// ========== Задание 5 ==========
int queue_fenqueue(Queue *q, QueueValue value); // Добавить в начало
Queue *queue_copy(const Queue *q);              // Копирование
Queue *queue_merge(Queue *q1, Queue *q2);       // Слияние

// Итераторы
QueueIterator queue_begin(Queue *q);
QueueIterator queue_end(Queue *q);
int queue_iterator_next(QueueIterator *it);
int queue_iterator_equal(QueueIterator it1, QueueIterator it2);
int queue_iterator_points_to(QueueIterator it, Queue *q);

// Резервирование памяти (коэффициент √2)
void queue_reserve(Queue *q, size_t new_capacity);

#endif
