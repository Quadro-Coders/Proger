#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

// Функция для измерения времени (в секундах)
double wtime() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

// Генерация псевдослучайного числа в диапазоне [min, max)
int getrand(int min, int max) {
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

// Заполнение массива случайными числами
void fill_rand(int* arr, int n, int min, int max) {
    for (int i = 0; i < n; i++) {
        arr[i] = getrand(min, max);
    }
}

// Вспомогательная функция для слияния двух отсортированных подмассивов
void merge(int* arr, int* temp, int left, int mid, int right) {
    int i = left;      // Индекс левого подмассива
    int j = mid + 1;   // Индекс правого подмассива
    int k = left;      // Индекс результирующего массива

    // Слияние двух подмассивов
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    // Копирование оставшихся элементов левого подмассива
    while (i <= mid)
        temp[k++] = arr[i++];

    // Копирование оставшихся элементов правого подмассива
    while (j <= right)
        temp[k++] = arr[j++];

    // Копирование отсортированных элементов обратно в исходный массив
    for (i = left; i <= right; i++)
        arr[i] = temp[i];
}

// Рекурсивная сортировка слиянием
void merge_sort_recursive(int* arr, int* temp, int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    merge_sort_recursive(arr, temp, left, mid);
    merge_sort_recursive(arr, temp, mid + 1, right);
    merge(arr, temp, left, mid, right);
}

// Интерфейсная функция сортировки слиянием
void merge_sort(int* arr, int n) {
    int* temp = (int*)malloc(sizeof(int) * n);
    if (temp == NULL) {
        fprintf(stderr, "Ошибка выделения памяти для временного массива\n");
        exit(1);
    }
    merge_sort_recursive(arr, temp, 0, n - 1);
    free(temp);
}

// Линейный поиск: возвращает индекс элемента или -1, если не найден
int linear_search(int* arr, int n, int key) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == key)
            return i;
    }
    return -1;
}

// Бинарный поиск (требует отсортированный массив): возвращает индекс или -1
int binary_search(int* arr, int n, int key) {
    int left = 0;
    int right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == key)
            return mid;
        else if (arr[mid] < key)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

// Экспоненциальный поиск (galloping search): возвращает индекс или -1
int exponential_search(int* arr, int n, int key) {
    if (n == 0) return -1;
    if (arr[0] == key) return 0;

    // Находим диапазон для бинарного поиска
    int i = 1;
    while (i < n && arr[i] <= key)
        i *= 2;

    // Выполняем бинарный поиск в найденном диапазоне
    int left = i / 2;
    int right = (i < n) ? i : n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == key)
            return mid;
        else if (arr[mid] < key)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

// Копирование массива (для сохранения исходного состояния)
void copy_array(int* dest, int* src, int n) {
    for (int i = 0; i < n; i++)
        dest[i] = src[i];
}

// Основная программа для экспериментального исследования
int main() {
    srand(123); // Фиксированный сид для воспроизводимости результатов

    // Параметры эксперимента
    const int min_val = 0;
    const int max_val = 10000000;
    const int step = 250000;
    const int max_n = 5000000;
    const int iterations = 100; // Количество повторов для усреднения времени

    printf("Таблица 1. Время выполнения поиска элемента в массиве (мкс)\n");
    printf("#\tЭлементов\tЛинейный\tБинарный\tЭкспоненциальный\n");
    printf("---------------------------------------------------------------\n");

    // Эксперимент для таблицы 1
    for (int n = step; n <= max_n; n += step) {
        // Выделение памяти для исходного массива
        int* arr = (int*)malloc(sizeof(int) * n);
        if (arr == NULL) {
            fprintf(stderr, "Ошибка выделения памяти для массива размером %d\n", n);
            exit(1);
        }

        // Заполнение массива случайными числами
        fill_rand(arr, n, min_val, max_val);

        // Копия для сортировки (чтобы не портить исходный массив)
        int* sorted_arr = (int*)malloc(sizeof(int) * n);
        if (sorted_arr == NULL) {
            fprintf(stderr, "Ошибка выделения памяти для копии массива\n");
            free(arr);
            exit(1);
        }
        copy_array(sorted_arr, arr, n);

        // Сортировка копии (время сортировки НЕ учитывается в таблице 1)
        merge_sort(sorted_arr, n);

        // Генерация ключа для поиска (гарантированно присутствует в массиве)
        int key = arr[n / 2]; // Берём элемент из середины исходного массива

        // ===== Линейный поиск =====
        double t_linear = 0.0;
        for (int iter = 0; iter < iterations; iter++) {
            double t_start = wtime();
            linear_search(arr, n, key);
            t_linear += wtime() - t_start;
        }
        t_linear = (t_linear / iterations) * 1000000.0; // мкс

        // ===== Бинарный поиск =====
        double t_binary = 0.0;
        for (int iter = 0; iter < iterations; iter++) {
            double t_start = wtime();
            binary_search(sorted_arr, n, key);
            t_binary += wtime() - t_start;
        }
        t_binary = (t_binary / iterations) * 1000000.0; // мкс

        // ===== Экспоненциальный поиск =====
        double t_exponential = 0.0;
        for (int iter = 0; iter < iterations; iter++) {
            double t_start = wtime();
            exponential_search(sorted_arr, n, key);
            t_exponential += wtime() - t_start;
        }
        t_exponential = (t_exponential / iterations) * 1000000.0; // мкс

        // Вывод результатов
        printf("%d\t%d\t\t%.2f\t\t%.2f\t\t%.2f\n",
               n / step, n, t_linear, t_binary, t_exponential);

        // Освобождение памяти
        free(arr);
        free(sorted_arr);
    }

    printf("\n=== Эксперимент для таблицы 2 (пример для одного случая) ===\n");
    printf("Массив 1 000 000 элементов, поиск 100 случайных элементов:\n");

    int n = 1000000;
    int* arr = (int*)malloc(sizeof(int) * n);
    if (arr == NULL) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        exit(1);
    }

    fill_rand(arr, n, min_val, max_val);

    // Измерение времени сортировки
    double t_sort = wtime();
    merge_sort(arr, n);
    t_sort = (wtime() - t_sort) * 1000000.0; // мкс

    // Поиск 100 случайных элементов
    int searches = 100;
    double t_binary_total = 0.0;
    for (int i = 0; i < searches; i++) {
        int key = getrand(min_val, max_val);
        double t_start = wtime();
        binary_search(arr, n, key);
        t_binary_total += (wtime() - t_start) * 1000000.0; // мкс
    }

    printf("Время сортировки: %.2f мкс\n", t_sort);
    printf("Суммарное время бинарного поиска (%d элементов): %.2f мкс\n", searches, t_binary_total);
    printf("Общее время (сортировка + поиск): %.2f мкс\n", t_sort + t_binary_total);

    free(arr);

    return 0;
}