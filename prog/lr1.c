#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

// --- Функция для измерения времени ---
double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

// --- Функции генерации случайных чисел ---
void fill_rand(int *arr, int n, int min_val, int max_val)
{
    for (int i = 0; i < n; i++)
    {
        // Формула для генерации в интервале [min_val, max_val]
        arr[i] = min_val + (rand() % (max_val - min_val + 1));
    }
}

// --- Функции сортировки ---
void merge(int *arr, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void merge_sort(int *arr, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// --- Функции поиска ---
int linear_search(int *A, int n, int key)
{
    for (int i = 0; i < n; i++)
    {
        if (A[i] == key)
        {
            return i;
        }
    }
    return -1;
}

int binary_search(int *A, int n, int key)
{
    int left = 0;
    int right = n - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (A[mid] == key)
        {
            return mid;
        }
        if (A[mid] < key)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return -1;
}

int binary_search_range(int *A, int left, int right, int key)
{
    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (A[mid] == key)
        {
            return mid;
        }
        if (A[mid] < key)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return -1;
}

int exponential_search(int *A, int n, int key)
{
    if (n == 0)
        return -1;
    if (A[0] == key)
        return 0;

    int bound = 1;
    while (bound < n && A[bound] <= key)
    {
        bound *= 2;
    }

    int left = bound / 2;
    int right = (bound < n) ? bound : n - 1;

    return binary_search_range(A, left, right, key);
}

int main()
{
    srand(123); // Фиксированный сид для воспроизводимости результатов

    // Параметры эксперимента
    const int min_val = 0;
    const int max_val = 10000000;
    const int iterations = 100; // Количество повторов для усреднения времени в Табл. 1

    // --- Таблица 1 ---
    printf("#\tКоличество элементов\tЛинейный поиск, мкс\tБинарный поиск, мкс\tЭкспоненциальный поиск, мкс\n");

    int table1_sizes[] = {250000, 500000, 750000, 1000000, 1250000, 1500000, 1750000, 2000000, 2250000, 2500000, 2750000, 3000000, 3250000, 3500000, 3750000, 4000000, 4250000, 4500000, 4750000, 5000000};
    int num_table1_sizes = sizeof(table1_sizes) / sizeof(table1_sizes[0]);

    for (int s_idx = 0; s_idx < num_table1_sizes; s_idx++)
    {
        int n = table1_sizes[s_idx];

        // Выделение памяти для исходного массива
        int *arr = (int *)malloc(sizeof(int) * n);
        if (arr == NULL)
        {
            fprintf(stderr, "Ошибка выделения памяти для массива размером %d\n", n);
            return 1;
        }

        // Заполнение массива случайными числами
        fill_rand(arr, n, min_val, max_val);

        // Копия для сортировки (чтобы не портить исходный массив)
        int *sorted_arr = (int *)malloc(sizeof(int) * n);
        if (sorted_arr == NULL)
        {
            fprintf(stderr, "Ошибка выделения памяти для копии массива\n");
            free(arr);
            return 1;
        }
        for (int i = 0; i < n; i++)
            sorted_arr[i] = arr[i];

        // Сортировка копии (время сортировки НЕ учитывается в таблице 1)
        merge_sort(sorted_arr, 0, n - 1);

        // Генерация ключа для поиска (гарантированно присутствует в массиве)
        int key = arr[n / 2]; // Берём элемент из середины исходного массива

        // ===== Линейный поиск =====
        double t_linear = 0.0;
        for (int iter = 0; iter < iterations; iter++)
        {
            double t_start = wtime();
            linear_search(arr, n, key);
            t_linear += wtime() - t_start;
        }
        t_linear = (t_linear / iterations) * 1000000.0; // мкс

        // ===== Бинарный поиск =====
        double t_binary = 0.0;
        for (int iter = 0; iter < iterations; iter++)
        {
            double t_start = wtime();
            binary_search(sorted_arr, n, key);
            t_binary += wtime() - t_start;
        }
        t_binary = (t_binary / iterations) * 1000000.0; // мкс

        // ===== Экспоненциальный поиск =====
        double t_exponential = 0.0;
        for (int iter = 0; iter < iterations; iter++)
        {
            double t_start = wtime();
            exponential_search(sorted_arr, n, key);
            t_exponential += wtime() - t_start;
        }
        t_exponential = (t_exponential / iterations) * 1000000.0; // мкс

        // Вывод результатов
        printf("%d\t%d\t\t\t%.2f\t\t\t%.2f\t\t\t%.2f\n",
               s_idx + 1, n, t_linear, t_binary, t_exponential);

        // Освобождение памяти
        free(arr);
        free(sorted_arr);
    }

    // --- Таблица 2 ---
    printf("\n#\tКол-во элементов в массиве\tКол-во элементов для поиска\tЛинейный поиск, мкс\tБинарный поиск, мкс\tБинарный поиск с сортировкой, мкс\tСортировка, мкс\n");

    int table2_sizes[] = {1000000, 5000000};
    int num_table2_sizes = sizeof(table2_sizes) / sizeof(table2_sizes[0]);
    int search_counts_1m[] = {50, 100, 150, 200, 250, 300, 350, 400, 450, 500};
    int search_counts_5m[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
    int num_search_counts_1m = sizeof(search_counts_1m) / sizeof(search_counts_1m[0]);
    int num_search_counts_5m = sizeof(search_counts_5m) / sizeof(search_counts_5m[0]);

    int row_counter = 1;

    for (int s_idx = 0; s_idx < num_table2_sizes; s_idx++)
    {
        int n = table2_sizes[s_idx];
        int num_search_counts = (n == 1000000) ? num_search_counts_1m : num_search_counts_5m;
        int *search_counts_array = (n == 1000000) ? search_counts_1m : search_counts_5m;

        // Выделение памяти
        int *arr = (int *)malloc(sizeof(int) * n);
        if (arr == NULL)
        {
            fprintf(stderr, "Ошибка выделения памяти для массива размером %d\n", n);
            return 1;
        }

        // Заполнение массива
        fill_rand(arr, n, min_val, max_val);

        // Сортировка и измерение времени сортировки
        int *sorted_arr_for_sort_time = (int *)malloc(sizeof(int) * n);
        if (sorted_arr_for_sort_time == NULL)
        {
            fprintf(stderr, "Ошибка выделения памяти для копии массива\n");
            free(arr);
            return 1;
        }
        for (int i = 0; i < n; i++)
            sorted_arr_for_sort_time[i] = arr[i];

        double sort_start_time = wtime();
        merge_sort(sorted_arr_for_sort_time, 0, n - 1);
        double sort_time_s = wtime() - sort_start_time;
        long long sort_time_us = (long long)(sort_time_s * 1000000);

        // Цикл по количеству поисков
        for (int sc_idx = 0; sc_idx < num_search_counts; sc_idx++)
        {
            int num_searches = search_counts_array[sc_idx];

            // Генерация ключей поиска
            int *search_keys = (int *)malloc(num_searches * sizeof(int));
            for (int i = 0; i < num_searches; i++)
            {
                search_keys[i] = sorted_arr_for_sort_time[rand() % n];
            }

            // Линейный поиск (на оригинальном неотсортированном)
            double t_linear = 0.0;
            for (int iter = 0; iter < num_searches; iter++)
            { // Измеряем на num_searches итерациях
                double t_start = wtime();
                linear_search(arr, n, search_keys[iter]);
                t_linear += wtime() - t_start;
            }
            t_linear = t_linear * 1000000.0; // мкс

            // Бинарный поиск (на уже отсортированном)
            double t_binary = 0.0;
            for (int iter = 0; iter < num_searches; iter++)
            { // Измеряем на num_searches итерациях
                double t_start = wtime();
                binary_search(sorted_arr_for_sort_time, n, search_keys[iter]);
                t_binary += wtime() - t_start;
            }
            t_binary = t_binary * 1000000.0; // мкс

            // Время бинарного поиска + время сортировки
            long long binary_with_sort_time_us = (long long)(t_binary) + sort_time_us;

            // ИСПРАВЛЕНАЯ строка printf
            printf("%d\t%d\t\t\t%d\t\t\t%.2f\t\t\t%.2f\t\t%.2f\t\t\t\t%lld\n",
                   row_counter, n, num_searches, t_linear, t_binary, (double)binary_with_sort_time_us, sort_time_us);

            row_counter++;
            free(search_keys);
        }
        free(arr);
        free(sorted_arr_for_sort_time);
    }
    return 0;
}
