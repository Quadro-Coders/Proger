#ifndef MINHEAP_H
#define MINHEAP_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    uint32_t key;
    char *value;
} heap_node;

typedef struct minheap
{
    heap_node *nodes;
    int size;
    int capacity;
} minheap;

// Сигнатуры
minheap *minheap_insert(minheap *heap, uint32_t key, char *value);
void *build_minheap(uint32_t *arr, int n);
minheap *minheap_min(minheap *heap);
minheap *minheap_union(minheap *heap1, minheap *heap2);
minheap *minheap_extractmin(minheap *heap);
minheap *minheap_decrease_key(minheap *heap, uint32_t key, uint32_t newkey);
minheap *minheap_delete(minheap *heap, uint32_t key);

// Вспомогательные функции
minheap *minheap_create(int capacity);
void minheap_free(minheap *heap);

#endif
