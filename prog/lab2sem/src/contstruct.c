#include "contstruct.h"
#include "debug_log.h"

#define GROWTH_FACTOR sqrt(2.0)

//  ВСПОМОГАТЕЛЬНАЯ ФУНКЦИЯ

static QueueNode *node_create(QueueValue value)
{
    QueueNode *node = (QueueNode *)malloc(sizeof(QueueNode));
    if (!node)
        return NULL;
    node->data = value;
    node->next = NULL;
    return node;
}

// КОНСТРУКТОР И ДЕСТРУКТОР

Queue *queue_create(void)
{
    LOG_INFO("Создание очереди");
    Queue *q = (Queue *)malloc(sizeof(Queue));
    if (!q)
    {
        LOG_ERROR("malloc вернул NULL");
        return NULL;
    }
    LOG_MEM(q, sizeof(Queue)); // Логи
    // Queue *q = (Queue *)malloc(sizeof(Queue));
    if (!q)
        return NULL;
    q->front = NULL;
    q->back = NULL;
    q->size = 0;
    q->capacity = 4;
    return q;
}

void queue_free(Queue *q)
{
    if (q)
    {
        LOG_INFO("Освобождение очереди %p", (void *)q);
        queue_clear(q);
        free(q);
    }
}

//  ЗАДАНИЕ 3

int queue_enqueue(Queue *q, QueueValue value)
{
    if (!q)
        return 0;

    QueueNode *node = node_create(value);
    if (!node)
        return 0;

    if (queue_is_empty(q))
    {
        q->front = q->back = node;
    }
    else
    {
        q->back->next = node;
        q->back = node;
    }
    q->size++;

    if (q->size > q->capacity)
    {
        queue_reserve(q, q->capacity * 2);
    }
    return 1;
}

QueueValue queue_dequeue(Queue *q)
{
    if (queue_is_empty(q))
        return NULL;

    QueueNode *temp = q->front;
    QueueValue value = temp->data;
    q->front = q->front->next;

    if (q->front == NULL)
        q->back = NULL;

    free(temp);
    q->size--;
    return value;
}

int queue_is_empty(const Queue *q)
{
    return q == NULL || q->size == 0;
}

//  ЗАДАНИЕ 4

size_t queue_size(const Queue *q)
{
    return q ? q->size : 0;
}

QueueValue queue_peek(const Queue *q)
{
    if (queue_is_empty(q))
        return NULL;
    return q->front->data;
}

void queue_clear(Queue *q)
{
    if (!q)
        return;
    while (q->front)
    {
        QueueNode *temp = q->front;
        q->front = q->front->next;
        free(temp);
    }
    q->back = NULL;
    q->size = 0;
}

//  ЗАДАНИЕ 5

int queue_fenqueue(Queue *q, QueueValue value)
{
    if (!q)
        return 0;

    QueueNode *node = node_create(value);
    if (!node)
        return 0;

    if (queue_is_empty(q))
    {
        q->front = q->back = node;
    }
    else
    {
        node->next = q->front;
        q->front = node;
    }
    q->size++;

    if (q->size > q->capacity)
    {
        queue_reserve(q, (size_t)(q->capacity * GROWTH_FACTOR) + 1);
    }
    return 1;
}

Queue *queue_copy(const Queue *q)
{
    if (!q)
        return NULL;

    Queue *new_q = queue_create();
    if (!new_q)
        return NULL;

    QueueNode *current = q->front;
    while (current)
    {
        queue_enqueue(new_q, current->data);
        current = current->next;
    }
    return new_q;
}

Queue *queue_merge(Queue *q1, Queue *q2)
{
    if (!q1 && !q2)
        return NULL;
    if (!q1)
        return queue_copy(q2);
    if (!q2)
        return queue_copy(q1);

    Queue *result = queue_copy(q1);
    if (!result)
        return NULL;

    QueueNode *current = q2->front;
    while (current)
    {
        queue_enqueue(result, current->data);
        current = current->next;
    }
    return result;
}

//  ИТЕРАТОРЫ

QueueIterator queue_begin(Queue *q)
{
    QueueIterator it;
    it.current = q ? q->front : NULL;
    it.queue = q;
    return it;
}

QueueIterator queue_end(Queue *q)
{
    QueueIterator it;
    it.current = NULL;
    it.queue = q;
    return it;
}

int queue_iterator_next(QueueIterator *it)
{
    if (!it || !it->current)
        return 0;
    it->current = it->current->next;
    return it->current != NULL;
}

int queue_iterator_equal(QueueIterator it1, QueueIterator it2)
{
    return it1.current == it2.current && it1.queue == it2.queue;
}

int queue_iterator_points_to(QueueIterator it, Queue *q)
{
    return it.queue == q;
}

//  РЕЗЕРВИРОВАНИЕ ПАМЯТИ

void queue_reserve(Queue *q, size_t new_capacity)
{
    if (!q || new_capacity <= q->capacity)
        return;
    q->capacity = new_capacity;
}
