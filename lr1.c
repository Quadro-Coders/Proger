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

// Копирование массива
void copy_array(int* dest, int* src, int n) {
    for (int i = 0; i < n; i++)
        dest[i] = src[i];
}

// Заполнение таблицы 1: поиск одного элемента при разном размере массива
void fill_table_1() {
    const int min_val = 0;
    const int max_val = 10000000;
    const int step = 250000;
    const int max_n = 5000000;
    const int iterations = 1000; // Для точности измерений коротких операций

    printf("#\tЭлементов\tЛинейный,мкс\tБинарный,мкс\tЭкспоненц,мкс\n");
    printf("---------------------------------------------------------------\n");

    for (int n = step; n <= max_n; n += step) {
        // Выделение и заполнение исходного массива
        int* arr = (int*)malloc(sizeof(int) * n);
        if (!arr) {
            fprintf(stderr, "Ошибка выделения памяти для %d элементов\n", n);
            exit(1);
        }
        fill_rand(arr, n, min_val, max_val);

        // Создание и сортировка копии для бинарного/экспоненциального поиска
        int* sorted_arr = (int*)malloc(sizeof(int) * n);
        if (!sorted_arr) {
            fprintf(stderr, "Ошибка выделения памяти для копии\n");            free(arr);
            exit(1);
        }
        copy_array(sorted_arr, arr, n);
        merge_sort(sorted_arr, n);

        // Ключ для поиска (гарантированно присутствует)
        int key = arr[n / 2];

        // Линейный поиск
        double t_linear = 0.0;
        for (int iter = 0; iter < iterations; iter++) {
            double start = wtime();
            linear_search(arr, n, key);
            t_linear += wtime() - start;
        }
        t_linear = (t_linear / iterations) * 1000000.0;

        // Бинарный поиск
        double t_binary = 0.0;
        for (int iter = 0; iter < iterations; iter++) {
            double start = wtime();
            binary_search(sorted_arr, n, key);
            t_binary += wtime() - start;
        }
        t_binary = (t_binary / iterations) * 1000000.0;

        // Экспоненциальный поиск
        double t_exponential = 0.0;
        for (int iter = 0; iter < iterations; iter++) {
            double start = wtime();
            exponential_search(sorted_arr, n, key);
            t_exponential += wtime() - start;
        }
        t_exponential = (t_exponential / iterations) * 1000000.0;

        // Вывод результатов
        printf("%d\t%d\t\t%.3f\t\t%.3f\t\t%.3f\n",
               n / step, n, t_linear, t_binary, t_exponential);

        free(arr);
        free(sorted_arr);
    }
}

// Заполнение таблицы 2: поиск множества элементов с учётом однократной сортировки
void fill_table_2() {
    const int min_val = 0;
    const int max_val = 10000000;
    const int iterations = 100; // Для усреднения результатов
    // Параметры эксперимента из таблицы 2
    struct {
        int n;          // Размер массива
        int searches;   // Количество поисков
    } cases[] = {
        {1000000, 50}, {1000000, 100}, {1000000, 150}, {1000000, 200},
        {1000000, 250}, {1000000, 300}, {1000000, 350}, {1000000, 400},
        {1000000, 450}, {1000000, 500},
        {5000000, 100}, {5000000, 200}, {5000000, 300}, {5000000, 400},
        {5000000, 500}, {5000000, 600}, {5000000, 700}, {5Вот полный код на C для лабораторной работы №1, соответствующий всем требованиям из методических указаний (включая корректное заполнение таблицы 2 с учётом однократной сортировки):

```c
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
            return mid;        else if (arr[mid] < key)
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

// Копирование массива
void copy_array(int* dest, int* src, int n) {
    for (int i = 0; i < n; i++)
        dest[i] = src[i];
}

// Заполнение таблицы 1: поиск одного элемента при разном размере массива
void fill_table_1() {
    const int min_val = 0;
    const int max_val = 10000000;
    const int step = 250000;
    const int max_n = 5000000;
    const int iterations = 1000; // Для точности измерений коротких операций

    printf("#\tЭлементов\tЛинейный,мкс\tБинарный,мкс\tЭкспоненц,мкс\n");
    printf("---------------------------------------------------------------\n");
    for (int n = step; n <= max_n; n += step) {
        // Выделение и заполнение исходного массива
        int* arr = (int*)malloc(sizeof(int) * n);
        if (!arr) {
            fprintf(stderr, "Ошибка выделения памяти для %d элементов\n", n);
            exit(1);
        }
        fill_rand(arr, n, min_val, max_val);

        // Создание и сортировка копии для бинарного/экспоненциального поиска
        int* sorted_arr = (int*)malloc(sizeof(int) * n);
        if (!sorted_arr) {
            fprintf(stderr, "Ошибка выделения памяти для копии\n");
            free(arr);
            exit(1);
        }
        copy_array(sorted_arr, arr, n);
        merge_sort(sorted_arr, n);

        // Ключ для поиска (гарантированно присутствует)
        int key = arr[n / 2];

        // Линейный поиск
        double t_linear = 0.0;
        for (int iter = 0; iter < iterations; iter++) {
            double start = wtime();
            linear_search(arr, n, key);
            t_linear += wtime() - start;
        }
        t_linear = (t_linear / iterations) * 1000000.0;

        // Бинарный поиск
        double t_binary = 0.0;
        for (int iter = 0; iter < iterations; iter++) {
            double start = wtime();
            binary_search(sorted_arr, n, key);
            t_binary += wtime() - start;
        }
        t_binary = (t_binary / iterations) * 1000000.0;

        // Экспоненциальный поиск
        double t_exponential = 0.0;
        for (int iter = 0; iter < iterations; iter++) {
            double start = wtime();
            exponential_search(sorted_arr, n, key);
            t_exponential += wtime() - start;
        }
        t_exponential = (t_exponential / iterations) * 1000000.0;

        // Вывод результатов        printf("%d\t%d\t\t%.3f\t\t%.3f\t\t%.3f\n",
               n / step, n, t_linear, t_binary, t_exponential);

        free(arr);
        free(sorted_arr);
    }
}

// Заполнение таблицы 2: поиск множества элементов с учётом однократной сортировки
void fill_table_2() {
    const int min_val = 0;
    const int max_val = 10000000;
    const int iterations = 100; // Для усреднения результатов

    // Параметры эксперимента из таблицы 2
    struct {
        int n;          // Размер массива
        int searches;   // Количество поисков
    } cases[] = {
        {1000000, 50}, {1000000, 100}, {1000000, 150}, {1000000, 200},
        {1000000, 250}, {1000000, 300}, {1000000, 350}, {1000000, 400},
        {1000000, 450}, {1000000, 500},
        {5000000, 100}, {5000000, 200}, {5000000, 300}, {5000000, 400},
        {5000000, 500}, {5000000, 600}, {5000000, 700}, {5000000, 800},
        {5000000, 900}, {5000000, 1000}
    };
    const int num_cases = sizeof(cases) / sizeof(cases[0]);

    printf("\n#   n          Поисков  Линейный,мкс  Бинарный,мкс  Бин+Сорт,мкс  Сортировка,мкс\n");
    printf("-------------------------------------------------------------------------------\n");

    for (int case_idx = 0; case_idx < num_cases; case_idx++) {
        int n = cases[case_idx].n;
        int num_searches = cases[case_idx].searches;

        // Выделение и заполнение исходного массива
        int* arr = (int*)malloc(sizeof(int) * n);
        if (!arr) {
            fprintf(stderr, "Ошибка выделения памяти для %d элементов\n", n);
            exit(1);
        }
        fill_rand(arr, n, min_val, max_val);

        // === ЛИНЕЙНЫЙ ПОИСК (без сортировки) ===
        double t_linear_total = 0.0;
        for (int iter = 0; iter < iterations; iter++) {
            // Создаём копию для каждого итерационного замера
            int* arr_copy = (int*)malloc(sizeof(int) * n);
            copy_array(arr_copy, arr, n);
            double start = wtime();
            for (int s = 0; s < num_searches; s++) {
                int key = getrand(min_val, max_val);
                linear_search(arr_copy, n, key);
            }
            t_linear_total += (wtime() - start) * 1000000.0; // мкс

            free(arr_copy);
        }
        t_linear_total /= iterations;

        // === БИНАРНЫЙ ПОИСК С СОРТИРОВКОЙ ===
        // 1. Измеряем время сортировки ОДИН раз
        int* sorted_arr = (int*)malloc(sizeof(int) * n);
        copy_array(sorted_arr, arr, n);

        double t_sort = 0.0;
        for (int iter = 0; iter < iterations; iter++) {
            copy_array(sorted_arr, arr, n); // Восстанавливаем исходный массив
            double start = wtime();
            merge_sort(sorted_arr, n);
            t_sort += (wtime() - start) * 1000000.0; // мкс
        }
        t_sort /= iterations;

        // 2. Измеряем время бинарного поиска (без сортировки)
        double t_binary_total = 0.0;
        for (int iter = 0; iter < iterations; iter++) {
            double start = wtime();
            for (int s = 0; s < num_searches; s++) {
                int key = getrand(min_val, max_val);
                binary_search(sorted_arr, n, key);
            }
            t_binary_total += (wtime() - start) * 1000000.0; // мкс
        }
        t_binary_total /= iterations;

        // 3. Общее время = сортировка + бинарный поиск
        double t_binary_with_sort = t_sort + t_binary_total;

        // Вывод результатов для текущего случая
        printf("%2d  %-10d %-8d %-13.2f %-13.2f %-15.2f %-15.2f\n",
               case_idx + 1, n, num_searches,
               t_linear_total,
               t_binary_total,
               t_binary_with_sort,
               t_sort);

        free(arr);
        free(sorted_arr);    }
}

int main() {
    srand(123); // Фиксированный сид для воспроизводимости

    printf("ТАБЛИЦА 1. Время поиска ОДНОГО элемента\n");
    printf("========================================\n");
    fill_table_1();

    printf("\n\nТАБЛИЦА 2. Суммарное время поиска МНОЖЕСТВА элементов\n");
    printf("=====================================================\n");
    fill_table_2();

    // Анализ порога окупаемости для массива 1 000 000 элементов
    printf("\n\nАНАЛИЗ ПОРОГА ОКУПАЕМОСТИ (массив 1 000 000 элементов)\n");
    printf("======================================================\n");

    const int n = 1000000;
    const int min_val = 0;
    const int max_val = 10000000;
    const int iterations = 100;

    int* arr = (int*)malloc(sizeof(int) * n);
    fill_rand(arr, n, min_val, max_val);

    // Измеряем среднее время одного линейного поиска
    double t_linear_single = 0.0;
    for (int iter = 0; iter < iterations * 10; iter++) {
        int key = getrand(min_val, max_val);
        double start = wtime();
        linear_search(arr, n, key);
        t_linear_single += (wtime() - start) * 1000000.0;
    }
    t_linear_single /= (iterations * 10);

    // Измеряем время сортировки
    int* sorted_arr = (int*)malloc(sizeof(int) * n);
    copy_array(sorted_arr, arr, n);
    double t_sort = 0.0;
    for (int iter = 0; iter < iterations; iter++) {
        copy_array(sorted_arr, arr, n);
        double start = wtime();
        merge_sort(sorted_arr, n);
        t_sort += (wtime() - start) * 1000000.0;
    }
    t_sort /= iterations;

    // Измеряем среднее время одного бинарного поиска
    double t_binary_single = 0.0;    for (int iter = 0; iter < iterations * 10; iter++) {
        int key = getrand(min_val, max_val);
        double start = wtime();
        binary_search(sorted_arr, n, key);
        t_binary_single += (wtime() - start) * 1000000.0;
    }
    t_binary_single /= (iterations * 10);

    // Расчёт порога окупаемости: k * T_linear = T_sort + k * T_binary
    // k = T_sort / (T_linear - T_binary)
    double k_break_even = t_sort / (t_linear_single - t_binary_single);

    printf("Среднее время линейного поиска:   %.4f мкс\n", t_linear_single);
    printf("Среднее время бинарного поиска:   %.4f мкс\n", t_binary_single);
    printf("Время сортировки слиянием:        %.2f мкс\n", t_sort);
    printf("Порог окупаемости:                %.1f поисков\n", k_break_even);
    printf("Вывод: При количестве поисков > %.0f бинарный поиск с сортировкой становится выгоднее линейного.\n", k_break_even);

    free(arr);
    free(sorted_arr);

    return 0;
}
```

### Особенности реализации для таблицы 2:

1. **Однократная сортировка** — время сортировки измеряется отдельно и добавляется только один раз к суммарному времени бинарного поиска.

2. **Четыре измеряемых величины** для каждой строки таблицы 2:
   - **Линейный поиск** — суммарное время `k` последовательных линейных поисков без сортировки
   - **Бинарный поиск** — суммарное время `k` бинарных поисков (без учёта сортировки)
   - **Бинарный поиск с сортировкой** — `время_сортировки + время_k_бинарных_поисков`
   - **Сортировка** — время однократной сортировки слиянием

3. **Порог окупаемости** рассчитывается по формуле: