#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

double wtime() {
    struct timeval t; gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int getrand(int min, int max) {
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

void fill_rand(int* arr, int n, int min, int max) {
    for (int i = 0; i < n; i++) arr[i] = getrand(min, max);
}

void merge(int* arr, int* tmp, int l, int m, int r) {
    int i = l, j = m + 1, k = l;
    while (i <= m && j <= r) tmp[k++] = (arr[i] <= arr[j]) ? arr[i++] : arr[j++];
    while (i <= m) tmp[k++] = arr[i++];
    while (j <= r) tmp[k++] = arr[j++];
    for (i = l; i <= r; i++) arr[i] = tmp[i];
}

void merge_sort_rec(int* arr, int* tmp, int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    merge_sort_rec(arr, tmp, l, m);
    merge_sort_rec(arr, tmp, m + 1, r);
    merge(arr, tmp, l, m, r);
}

void merge_sort(int* arr, int n) {
    int* tmp = malloc(sizeof(int) * n);
    merge_sort_rec(arr, tmp, 0, n - 1);
    free(tmp);
}

int linear_search(int* arr, int n, int key) {
    for (int i = 0; i < n; i++) if (arr[i] == key) return i;
    return -1;
}

int binary_search(int* arr, int n, int key) {
    int l = 0, r = n - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (arr[m] == key) return m;
        else if (arr[m] < key) l = m + 1;        else r = m - 1;
    }
    return -1;
}

void table1() {
    const int min_val = 0, max_val = 10000000, step = 250000, max_n = 5000000, iter = 1000;
    printf("\nТаблица 1. Время поиска ОДНОГО элемента (мкс)\n");
    printf("#\tЭл.\tЛинейный\tБинарный\tЭкспоненц.\n");
    printf("-----------------------------------------------------\n");
    
    for (int n = step; n <= max_n; n += step) {
        int *arr = malloc(n * sizeof(int)), *sorted = malloc(n * sizeof(int));
        fill_rand(arr, n, min_val, max_val);
        for (int i = 0; i < n; i++) sorted[i] = arr[i];
        merge_sort(sorted, n);
        int key = arr[n / 2];
        
        double t_lin = 0, t_bin = 0, t_exp = 0;
        for (int i = 0; i < iter; i++) {
            double s = wtime(); linear_search(arr, n, key); t_lin += wtime() - s;
            s = wtime(); binary_search(sorted, n, key); t_bin += wtime() - s;
            s = wtime(); {
                int idx = 0; if (n > 0 && sorted[0] <= key) {
                    int j = 1; while (j < n && sorted[j] <= key) j *= 2;
                    int l = j / 2, r = (j < n) ? j : n - 1;
                    while (l <= r) {
                        int m = l + (r - l) / 2;
                        if (sorted[m] == key) { idx = m; break; }
                        else if (sorted[m] < key) l = m + 1;
                        else r = m - 1;
                    }
                }
            } t_exp += wtime() - s;
        }
        
        printf("%d\t%d\t%.2f\t\t%.2f\t\t%.2f\n", n / step, n,
               t_lin / iter * 1e6, t_bin / iter * 1e6, t_exp / iter * 1e6);
        
        free(arr); free(sorted);
    }
}

void table2() {
    const int min_val = 0, max_val = 10000000, iter = 5;
    int cfg[][2] = {
        {1000000,  50}, {1000000, 100}, {1000000, 150}, {1000000, 200}, {1000000, 250},
        {1000000, 300}, {1000000, 350}, {1000000, 400}, {1000000, 450}, {1000000, 500},
        {5000000, 100}, {5000000, 200}, {5000000, 300}, {5000000, 400}, {5000000, 500},
        {5000000, 600}, {5000000, 700}, {5000000, 800}, {5000000, 900}, {5000000,1000}    };
    int cfg_cnt = 20;  // Ровно 20 вычислений
    
    printf("\nТаблица 2. Суммарное время поиска (мкс)\n");
    printf("#\tЭл.мас.\tПоиски\tЛинейный\tБинарный\tБин.+сортировка\tСортировка\n");
    printf("---------------------------------------------------------------------------\n");
    
    double sort_1m = 0, sort_5m = 0, lin_1m = 0, bin_1m = 0, lin_5m = 0, bin_5m = 0;
    
    for (int idx = 0; idx < cfg_cnt; idx++) {
        int n = cfg[idx][0], searches = cfg[idx][1];
        int *arr = malloc(n * sizeof(int));
        fill_rand(arr, n, min_val, max_val);
        
        // Линейный поиск
        double t_lin = 0;
        for (int i = 0; i < iter; i++) {
            int *keys = malloc(searches * sizeof(int));
            for (int j = 0; j < searches; j++) keys[j] = getrand(min_val, max_val);
            double s = wtime();
            for (int j = 0; j < searches; j++) linear_search(arr, n, keys[j]);
            t_lin += (wtime() - s) * 1e6;
            free(keys);
        }
        t_lin /= iter;
        
        // Бинарный поиск с сортировкой
        int *sorted = malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) sorted[i] = arr[i];
        double s_sort = wtime(); merge_sort(sorted, n); double t_sort = (wtime() - s_sort) * 1e6;
        
        int *keys = malloc(searches * sizeof(int));
        for (int j = 0; j < searches; j++) keys[j] = getrand(min_val, max_val);
        double t_bin = 0;
        for (int i = 0; i < iter; i++) {
            double s = wtime();
            for (int j = 0; j < searches; j++) binary_search(sorted, n, keys[j]);
            t_bin += (wtime() - s) * 1e6;
        }
        t_bin /= iter;
        
        // Сохраняем данные для расчёта порога (берём конфигурацию с 100 поисков)
        if (n == 1000000 && searches == 100) { sort_1m = t_sort; lin_1m = t_lin / searches; bin_1m = t_bin / searches; }
        if (n == 5000000 && searches == 100) { sort_5m = t_sort; lin_5m = t_lin / searches; bin_5m = t_bin / searches; }
        
        printf("%d\t%d\t%d\t%.0f\t\t%.0f\t\t%.0f\t\t%.0f\n", idx + 1, n, searches,
               t_lin, t_bin, t_sort + t_bin, t_sort);
        
        free(arr); free(sorted); free(keys);
    }    
    printf("\n=== Порог окупаемости сортировки ===\n");
    if (lin_1m > bin_1m && sort_1m > 0) {
        double k = sort_1m / (lin_1m - bin_1m);
        printf("1 000 000 элементов: сортировка окупается при %.0f поисках\n", k);
    }
    if (lin_5m > bin_5m && sort_5m > 0) {
        double k = sort_5m / (lin_5m - bin_5m);
        printf("5 000 000 элементов: сортировка окупается при %.0f поисках\n", k);
    }
}

int main() {
    srand(123);
    table1();
    table2();
    return 0;
}