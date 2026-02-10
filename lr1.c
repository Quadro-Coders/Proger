#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

double wtime() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int getrand(int min, int max) {
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

void fill_rand(int* arr, int n, int min, int max) {
    for (int i = 0; i < n; i++) {
        arr[i] = getrand(min, max);
    }
}

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
    if (!temp) {
        fprintf(stderr, "Error: malloc failed for temp array (size %d)\n", n);
        exit(EXIT_FAILURE);
    }
    merge_sort_recursive(arr, temp, 0, n - 1);
    free(temp);
}

int linear_search(int* arr, int n, int key) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == key)
            return i;
    }
    return -1;
}

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
            right = mid - 1;    }
    return -1;
}

void fill_table_1() {
    const int min_val = 0;
    const int max_val = 10000000;
    const int step = 250000;
    const int max_n = 5000000;
    const int iterations = 1000;

    printf("#\tElements\tLinear,us\tBinary,us\tExponential,us\n");
    for (int n = step; n <= max_n; n += step) {
        int* arr = (int*)malloc(sizeof(int) * n);
        if (!arr) {
            fprintf(stderr, "Error: malloc failed for array (size %d)\n", n);
            exit(EXIT_FAILURE);
        }
        fill_rand(arr, n, min_val, max_val);

        int* sorted_arr = (int*)malloc(sizeof(int) * n);
        if (!sorted_arr) {
            fprintf(stderr, "Error: malloc failed for sorted array (size %d)\n", n);
            free(arr);
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < n; i++) sorted_arr[i] = arr[i];
        merge_sort(sorted_arr, n);

        int key = arr[n / 2];

        double t_linear = 0.0;
        for (int iter = 0; iter < iterations; iter++) {
            double start = wtime();
            linear_search(arr, n, key);
            t_linear += wtime() - start;
        }
        t_linear = (t_linear / iterations) * 1000000.0;

        double t_binary = 0.0;
        for (int iter = 0; iter < iterations; iter++) {
            double start = wtime();
            binary_search(sorted_arr, n, key);
            t_binary += wtime() - start;
        }
        t_binary = (t_binary / iterations) * 1000000.0;

        double t_exponential = 0.0;
        for (int iter = 0; iter < iterations; iter++) {
            double start = wtime();            exponential_search(sorted_arr, n, key);
            t_exponential += wtime() - start;
        }
        t_exponential = (t_exponential / iterations) * 1000000.0;

        printf("%d\t%d\t\t%.3f\t\t%.3f\t\t%.3f\n",
               n / step, n, t_linear, t_binary, t_exponential);

        free(arr);
        free(sorted_arr);
    }
}

void fill_table_2() {
    const int min_val = 0;
    const int max_val = 10000000;
    const int iterations = 100;

    struct { int n; int searches; } cases[] = {
        {1000000, 50}, {1000000, 100}, {1000000, 150}, {1000000, 200},
        {1000000, 250}, {1000000, 300}, {1000000, 350}, {1000000, 400},
        {1000000, 450}, {1000000, 500},
        {5000000, 100}, {5000000, 200}, {5000000, 300}, {5000000, 400},
        {5000000, 500}, {5000000, 600}, {5000000, 700}, {5000000, 800},
        {5000000, 900}, {5000000, 1000}
    };
    const int num_cases = sizeof(cases) / sizeof(cases[0]);

    printf("\n#\tn\t\tSearches\tLinear,us\tBinary,us\tBin+Sort,us\tSort,us\n");
    for (int idx = 0; idx < num_cases; idx++) {
        int n = cases[idx].n;
        int num_searches = cases[idx].searches;

        int* arr = (int*)malloc(sizeof(int) * n);
        if (!arr) {
            fprintf(stderr, "Error: malloc failed for array (size %d)\n", n);
            exit(EXIT_FAILURE);
        }
        fill_rand(arr, n, min_val, max_val);

        double t_linear_total = 0.0;
        for (int iter = 0; iter < iterations; iter++) {
            int* arr_copy = (int*)malloc(sizeof(int) * n);
            if (!arr_copy) {
                fprintf(stderr, "Error: malloc failed for arr_copy (size %d)\n", n);
                free(arr);
                exit(EXIT_FAILURE);
            }
            for (int i = 0; i < n; i++) arr_copy[i] = arr[i];
            double start = wtime();            for (int s = 0; s < num_searches; s++) {
                int key = getrand(min_val, max_val);
                linear_search(arr_copy, n, key);
            }
            t_linear_total += (wtime() - start) * 1000000.0;
            free(arr_copy);
        }
        t_linear_total /= iterations;

        int* sorted_arr = (int*)malloc(sizeof(int) * n);
        if (!sorted_arr) {
            fprintf(stderr, "Error: malloc failed for sorted_arr (size %d)\n", n);
            free(arr);
            exit(EXIT_FAILURE);
        }

        double t_sort = 0.0;
        for (int iter = 0; iter < iterations; iter++) {
            for (int i = 0; i < n; i++) sorted_arr[i] = arr[i];
            double start = wtime();
            merge_sort(sorted_arr, n);
            t_sort += (wtime() - start) * 1000000.0;
        }
        t_sort /= iterations;

        double t_binary_total = 0.0;
        for (int iter = 0; iter < iterations; iter++) {
            double start = wtime();
            for (int s = 0; s < num_searches; s++) {
                int key = getrand(min_val, max_val);
                binary_search(sorted_arr, n, key);
            }
            t_binary_total += (wtime() - start) * 1000000.0;
        }
        t_binary_total /= iterations;

        double t_binary_with_sort = t_sort + t_binary_total;

        printf("%2d\t%-10d\t%-8d\t%.2f\t\t%.2f\t\t%.2f\t\t%.2f\n",
               idx + 1, n, num_searches,
               t_linear_total, t_binary_total, t_binary_with_sort, t_sort);

        free(arr);
        free(sorted_arr);
    }
}

int main() {
    srand(123);
    printf("TABLE 1: Search time for ONE element\n");
    printf("=====================================\n");
    fill_table_1();

    printf("\nTABLE 2: Total search time for MULTIPLE elements (with single sort)\n");
    printf("=====================================================================\n");
    fill_table_2();

    printf("\nBREAK-EVEN ANALYSIS (n = 1000000)\n");
    printf("=================================\n");

    const int n = 1000000;
    const int min_val = 0;
    const int max_val = 10000000;
    const int iterations = 100;

    int* arr = (int*)malloc(sizeof(int) * n);
    if (!arr) {
        fprintf(stderr, "Error: malloc failed for break-even analysis array\n");
        exit(EXIT_FAILURE);
    }
    fill_rand(arr, n, min_val, max_val);

    double t_linear_single = 0.0;
    for (int iter = 0; iter < iterations * 10; iter++) {
        int key = getrand(min_val, max_val);
        double start = wtime();
        linear_search(arr, n, key);
        t_linear_single += (wtime() - start) * 1000000.0;
    }
    t_linear_single /= (iterations * 10);

    int* sorted_arr = (int*)malloc(sizeof(int) * n);
    if (!sorted_arr) {
        fprintf(stderr, "Error: malloc failed for sorted_arr in break-even analysis\n");
        free(arr);
        exit(EXIT_FAILURE);
    }

    double t_sort = 0.0;
    for (int iter = 0; iter < iterations; iter++) {
        for (int i = 0; i < n; i++) sorted_arr[i] = arr[i];
        double start = wtime();
        merge_sort(sorted_arr, n);
        t_sort += (wtime() - start) * 1000000.0;
    }
    t_sort /= iterations;

    double t_binary_single = 0.0;
    for (int iter = 0; iter < iterations * 10; iter++) {        int key = getrand(min_val, max_val);
        double start = wtime();
        binary_search(sorted_arr, n, key);
        t_binary_single += (wtime() - start) * 1000000.0;
    }
    t_binary_single /= (iterations * 10);

    double k_break_even = t_sort / (t_linear_single - t_binary_single);

    printf("Avg linear search time:   %.4f us\n", t_linear_single);
    printf("Avg binary search time:   %.4f us\n", t_binary_single);
    printf("Merge sort time:          %.2f us\n", t_sort);
    printf("Break-even point:         %.1f searches\n", k_break_even);
    printf("Conclusion: Binary search with sorting becomes faster than linear\n");
    printf("            search when number of searches exceeds %.0f.\n", k_break_even);

    free(arr);
    free(sorted_arr);

    return 0;
}