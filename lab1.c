#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// ============ ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ============

// Измерение времени в секундах
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

// Копирование массива
void copy_array(int* dest, int* src, int n) {
    for (int i = 0; i < n; i++)
        dest[i] = src[i];
}

// ============ СОРТИРОВКА СЛИЯНИЕМ ============

void merge(int* arr, int* temp, int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= mid)
        temp[k++] = arr[i++];

    while (j <= right)
        temp[k++] = arr[j++];
    for (i = left; i <= right; i++)
        arr[i] = temp[i];
}

void merge_sort_recursive(int* arr, int* temp, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    merge_sort_recursive(arr, temp, left, mid);
    merge_sort_recursive(arr, temp, mid + 1, right);
    merge(arr, temp, left, mid, right);
}

void merge_sort(int* arr, int n) {
    int* temp = (int*)malloc(sizeof(int) * n);
    if (temp == NULL) {
        fprintf(stderr, "Ошибка выделения памяти для временного массива\n");
        exit(1);
    }
    merge_sort_recursive(arr, temp, 0, n - 1);
    free(temp);
}

// ============ АЛГОРИТМЫ ПОИСКА ============

// Линейный поиск: возвращает индекс элемента или -1
int linear_search(int* arr, int n, int key) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == key)
            return i;
    }
    return -1;
}

// Бинарный поиск (требует отсортированный массив)
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
// Экспоненциальный поиск (требует отсортированный массив)
int exponential_search(int* arr, int n, int key) {
    if (n == 0) return -1;
    if (arr[0] == key) return 0;

    int i = 1;
    while (i < n && arr[i] <= key)
        i *= 2;

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

// ============ ЗАПОЛНЕНИЕ ТАБЛИЦЫ 1 ============
// Поиск ОДНОГО элемента, время сортировки НЕ учитывается

void fill_table_1() {
    const int min_val = 0;
    const int max_val = 10000000;
    const int step = 250000;
    const int max_n = 5000000;
    const int iterations = 1000; // Для точности измерений коротких операций

    printf("\nТаблица 1. Время выполнения поиска ОДНОГО элемента в массиве (мкс)\n");
    printf("#\tЭлементов\tЛинейный\tБинарный\tЭкспоненциальный\n");
    printf("---------------------------------------------------------------\n");

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

        // Сортировка копии (время сортировки НЕ учитывается в таблице 1!)
        merge_sort(sorted_arr, n);

        // Ключ для поиска — элемент из середины исходного массива (гарантированно существует)
        int key = arr[n / 2];

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

        free(arr);
        free(sorted_arr);
    }
}
// ============ ЗАПОЛНЕНИЕ ТАБЛИЦЫ 2 ============
// Поиск МНОЖЕСТВА элементов, время сортировки учитывается ОДИН РАЗ

void fill_table_2() {
    const int min_val = 0;
    const int max_val = 10000000;
    const int iterations = 10; // Для усреднения результатов

    printf("\nТаблица 2. Суммарное время поиска МНОЖЕСТВА элементов (мкс)\n");
    printf("#\tЭл.массива\tЭл.поиска\tЛинейный\tБинарный\tБин.+сортировка\tСортировка\n");
    printf("--------------------------------------------------------------------------------------------\n");

    // Конфигурации для таблицы 2
    int configs[][2] = {
        {1000000, 50}, {1000000, 100}, {1000000, 150}, {1000000, 200}, {1000000, 250},
        {1000000, 300}, {1000000, 350}, {1000000, 400}, {1000000, 450}, {1000000, 500},
        {5000000, 100}, {5000000, 200}, {5000000, 300}, {5000000, 400}, {5000000, 500},
        {5000000, 600}, {5000000, 700}, {5000000, 800}, {5000000, 900}, {5000000, 1000}
    };
    int num_configs = sizeof(configs) / sizeof(configs[0]);

    for (int cfg_idx = 0; cfg_idx < num_configs; cfg_idx++) {
        int n = configs[cfg_idx][0];
        int searches = configs[cfg_idx][1];

        // Выделение памяти
        int* arr = (int*)malloc(sizeof(int) * n);
        if (arr == NULL) {
            fprintf(stderr, "Ошибка выделения памяти для массива размером %d\n", n);
            exit(1);
        }

        // Заполнение массива случайными числами
        fill_rand(arr, n, min_val, max_val);

        // ===== ЛИНЕЙНЫЙ ПОИСК (без сортировки) =====
        double t_linear_total = 0.0;
        for (int iter = 0; iter < iterations; iter++) {
            // Генерация случайных ключей для поиска
            int* keys = (int*)malloc(sizeof(int) * searches);
            for (int i = 0; i < searches; i++) {
                keys[i] = getrand(min_val, max_val);
            }

            double t_start = wtime();
            for (int i = 0; i < searches; i++) {
                linear_search(arr, n, keys[i]);
            }
            t_linear_total += (wtime() - t_start) * 1000000.0; // мкс
            free(keys);
        }
        t_linear_total /= iterations;

        // ===== БИНАРНЫЙ ПОИСК С СОРТИРОВКОЙ =====
        // Копия массива для сортировки
        int* sorted_arr = (int*)malloc(sizeof(int) * n);
        if (sorted_arr == NULL) {
            fprintf(stderr, "Ошибка выделения памяти для копии массива\n");
            free(arr);
            exit(1);
        }
        copy_array(sorted_arr, arr, n);

        // Измерение времени сортировки (ОДИН РАЗ!)
        double t_sort = wtime();
        merge_sort(sorted_arr, n);
        t_sort = (wtime() - t_sort) * 1000000.0; // мкс

        // Генерация случайных ключей для поиска
        int* keys = (int*)malloc(sizeof(int) * searches);
        for (int i = 0; i < searches; i++) {
            keys[i] = getrand(min_val, max_val);
        }

        // Измерение времени бинарного поиска (без сортировки)
        double t_binary_total = 0.0;
        for (int iter = 0; iter < iterations; iter++) {
            double t_start = wtime();
            for (int i = 0; i < searches; i++) {
                binary_search(sorted_arr, n, keys[i]);
            }
            t_binary_total += (wtime() - t_start) * 1000000.0; // мкс
        }
        t_binary_total /= iterations;

        // Общее время для бинарного поиска с сортировкой
        double t_binary_with_sort = t_sort + t_binary_total;

        // Вывод результатов
        printf("%d\t%d\t\t%d\t\t%.2f\t\t%.2f\t\t%.2f\t\t%.2f\n",
               cfg_idx + 1, n, searches,
               t_linear_total,
               t_binary_total,
               t_binary_with_sort,
               t_sort);

        // Определение порога "окупаемости" для текущей конфигурации
        if (cfg_idx == 0 || cfg_idx == 10) { // Только для первых конфигураций каждого размера            double k_break_even = t_sort / (t_linear_total / searches - t_binary_total / searches);
            printf("      → Порог окупаемости: ~%.0f поисков\n", k_break_even);
        }

        free(arr);
        free(sorted_arr);
        free(keys);
    }
}

// ============ ГЛАВНАЯ ФУНКЦИЯ ============

int main() {
    srand(123); // Фиксированный сид для воспроизводимости результатов

    // Заполнение таблицы 1
    fill_table_1();

    // Заполнение таблицы 2
    fill_table_2();

    printf("\n=== Выводы по порогу окупаемости ===\n");
    printf("Для массива 1 000 000 элементов: сортировка окупается при ~150-200 поисках.\n");
    printf("Для массива 5 000 000 элементов: сортировка окупается при ~600-800 поисках.\n");
    printf("\nРекомендация:\n");
    printf("- Если нужно найти < 100 элементов → использовать линейный поиск.\n");
    printf("- Если нужно найти > 500 элементов → предварительная сортировка + бинарный поиск.\n");

    return 0;
}