#include "random.h"
#include "minheap.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void run_lab5_experiment()
{
    printf("Лабораторная работа 5. Бинарная куча (Min-Heap)\n\n");

    // Таблица 1. Добавление элементов
    printf("Таблица 1. Добавление элементов в структуру данных\n");
    printf("Кол-во элементов\tminheap_insert, мкс\tbuild_minheap, мкс\n");

    for (int n = 50000; n <= 400000; n += 50000)
    {
        uint32_t *arr = (uint32_t *)malloc(n * sizeof(uint32_t));
        for (int i = 0; i < n; i++)
            arr[i] = (uint32_t)getrand(10000, 1000000);

        // 1. Последовательная вставка N элементов O(N log N)
        minheap *h_ins = minheap_create(n);
        double t_ins = wtime();
        for (int i = 0; i < n; i++)
            minheap_insert(h_ins, arr[i], NULL);
        t_ins = wtime() - t_ins;
        minheap_free(h_ins);

        // 2. Построение кучи из массива O(N)
        double t_build = wtime();
        minheap *h_build = (minheap *)build_minheap(arr, n);
        t_build = wtime() - t_build;
        minheap_free(h_build);

        printf("%d\t%.5lf\t%.5lf\n", n, t_ins, t_build);
        free(arr);
    }

    printf("\n");

    // Таблица 2. Извлечение и уменьшение приоритета
    printf("Таблица 2. Извлечение и уменьшение приоритета элемента\n");
    printf("Кол-во элементов\tminheap_extractmin, мкс\tminheap_decreasekey, мкс\n");

    for (int n = 50000; n <= 400000; n += 50000)
    {
        uint32_t *arr = (uint32_t *)malloc(n * sizeof(uint32_t));
        for (int i = 0; i < n; i++)
            arr[i] = (uint32_t)getrand(10000, 1000000);

        // Подготовка: быстрое построение кучи
        minheap *h = (minheap *)build_minheap(arr, n);

        // 1. Извлечение минимума (1 вызов) O(log N)
        double t_ext = wtime();
        minheap *h_ext = minheap_extractmin(h);
        t_ext = (wtime() - t_ext) * 1E6;

        // 2. Уменьшение ключа случайного элемента (1 вызов) O(log N)
        int idx = getrand(0, n - 1);
        uint32_t old_key = h_ext->nodes[idx].key;

        // Безопасное уменьшение ключа случайного элемента без риска переполнения uint32_t
        uint32_t new_key = (old_key > 1000) ? old_key - 1000 : old_key / 2;

        double t_dec = wtime();
        minheap *h_dec = minheap_decrease_key(h_ext, old_key, new_key);
        t_dec = (wtime() - t_dec) * 1E6;

        printf("%d\t%.5lf\t%.5lf\n", n, t_ext, t_dec);

        minheap_free(h_dec);
        free(arr);
    }
}

int main()
{
    run_lab5_experiment();
    return 0;
}
