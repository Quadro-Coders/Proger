#include "minheap.h"
#include <stdio.h>

#define MINHEAP_DEFAULT_CAPACITY 102400

// Вспомогательные функции
static void swap_nodes(heap_node *a, heap_node *b)
{
    heap_node tmp = *a;
    *a = *b;
    *b = tmp;
}

// Подъём элемента вверх (Heapify Up)
static void sift_up(minheap *h, int idx)
{
    while (idx > 0)
    {
        int parent = (idx - 1) / 2;
        if (h->nodes[idx].key < h->nodes[parent].key)
        {
            swap_nodes(&h->nodes[idx], &h->nodes[parent]);
            idx = parent;
        }
        else
        {
            break;
        }
    }
}

// Спуск элемента вниз (Heapify Down)
static void sift_down(minheap *h, int idx)
{
    int size = h->size;
    while (1)
    {
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        int smallest = idx;

        if (left < size && h->nodes[left].key < h->nodes[smallest].key)
            smallest = left;
        if (right < size && h->nodes[right].key < h->nodes[smallest].key)
            smallest = right;

        if (smallest != idx)
        {
            swap_nodes(&h->nodes[idx], &h->nodes[smallest]);
            idx = smallest;
        }
        else
        {
            break;
        }
    }
}

// Создание кучи
minheap *minheap_create(int capacity)
{
    minheap *h = (minheap *)malloc(sizeof(minheap));
    if (!h)
        return NULL;
    h->capacity = (capacity > 0) ? capacity : MINHEAP_DEFAULT_CAPACITY;
    h->size = 0;
    h->nodes = (heap_node *)calloc(h->capacity, sizeof(heap_node));
    if (!h->nodes)
    {
        free(h);
        return NULL;
    }
    return h;
}

void minheap_free(minheap *heap)
{
    if (!heap)
        return;
    for (int i = 0; i < heap->size; i++)
        free(heap->nodes[i].value);
    free(heap->nodes);
    free(heap);
}

// Insert: O(log N)
minheap *minheap_insert(minheap *heap, uint32_t key, char *value)
{
    if (!heap)
        return NULL;
    if (heap->size >= heap->capacity)
    {
        heap->capacity *= 2;
        heap_node *tmp = (heap_node *)realloc(heap->nodes, heap->capacity * sizeof(heap_node));
        if (!tmp)
            return NULL;
        heap->nodes = tmp;
    }
    heap->nodes[heap->size].key = key;
    heap->nodes[heap->size].value = value ? malloc(strlen(value) + 1) : NULL;
    if (value)
        strcpy(heap->nodes[heap->size].value, value);
    heap->size++;
    sift_up(heap, heap->size - 1);
    return heap;
}

// Build: O(N) - линейный алгоритм снизу вверх
void *build_minheap(uint32_t *arr, int n)
{
    minheap *h = minheap_create(n);
    if (!h)
        return NULL;
    for (int i = 0; i < n; i++)
    {
        h->nodes[i].key = arr[i];
        h->nodes[i].value = NULL;
    }
    h->size = n;
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        sift_down(h, i);
    }
    return (void *)h;
}

// Min: O(1)
minheap *minheap_min(minheap *heap)
{
    return (heap && heap->size > 0) ? heap : NULL;
}

// Union: O(N1+N2) через конкатенацию и перестроение
minheap *minheap_union(minheap *heap1, minheap *heap2)
{
    if (!heap1)
        return heap2;
    if (!heap2)
        return heap1;

    // 1. Выделяем новый массив
    int new_size = heap1->size + heap2->size;
    heap_node *new_nodes = (heap_node *)malloc(new_size * sizeof(heap_node));
    if (!new_nodes)
        return NULL;

    // 2. Копируем элементы обеих куч
    memcpy(new_nodes, heap1->nodes, heap1->size * sizeof(heap_node));
    memcpy(new_nodes + heap1->size, heap2->nodes, heap2->size * sizeof(heap_node));

    // 3. Строим кучу за O(N)
    minheap *res = minheap_create(new_size);
    res->size = new_size;
    free(res->nodes);
    res->nodes = new_nodes;

    for (int i = new_size / 2 - 1; i >= 0; i--)
        sift_down(res, i);

    minheap_free(heap1);
    minheap_free(heap2);
    return res;
}

// ExtractMin: O(log N)
minheap *minheap_extractmin(minheap *heap)
{
    if (!heap || heap->size == 0)
        return heap;
    swap_nodes(&heap->nodes[0], &heap->nodes[heap->size - 1]);
    heap->size--;
    free(heap->nodes[heap->size].value);
    heap->nodes[heap->size].value = NULL;
    if (heap->size > 0)
        sift_down(heap, 0);
    return heap;
}

// DecreaseKey: O(N) поиск + O(log N) подъём
minheap *minheap_decrease_key(minheap *heap, uint32_t key, uint32_t newkey)
{
    if (!heap || newkey >= key)
        return heap;
    for (int i = 0; i < heap->size; i++)
    {
        if (heap->nodes[i].key == key)
        {
            heap->nodes[i].key = newkey;
            sift_up(heap, i);
            return heap;
        }
    }
    return heap;
}

// Delete: O(N) поиск + O(log N) восстановление
minheap *minheap_delete(minheap *heap, uint32_t key)
{
    if (!heap)
        return heap;
    for (int i = 0; i < heap->size; i++)
    {
        if (heap->nodes[i].key == key)
        {
            swap_nodes(&heap->nodes[i], &heap->nodes[heap->size - 1]);
            heap->size--;
            free(heap->nodes[heap->size].value);
            heap->nodes[heap->size].value = NULL;
            if (i < heap->size)
            {
                if (i > 0 && heap->nodes[i].key < heap->nodes[(i - 1) / 2].key)
                    sift_up(heap, i);
                else
                    sift_down(heap, i);
            }
            return heap;
        }
    }
    return heap;
}
