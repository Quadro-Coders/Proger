#include "myarrfunc.h"

int array[MAX_SIZE];
int size = 0;

void clear() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void set_array_size() {
    printf("Введите размер массива (макс. %d): ", MAX_SIZE);
    scanf("%d", &size);
    clear();
    
    if (size <= 0 || size > MAX_SIZE) {
        printf("Ошибка: размер должен быть от 1 до %d!\n", MAX_SIZE);
        size = 0;
    } else {
        printf("Размер массива установлен: %d\n", size);
    }
}

void fill_array() {
    if (size == 0) {
        printf("Сначала задайте размер массива!\n");
        return;
    }
    
    printf("Заполнение массива:\n");
    for (int i = 0; i < size; i++) {
        printf("Введите элемент [%d]: ", i);
        
        int value;
        int result = scanf("%d", &value);
        
        if (result == EOF) {
            printf("\nВвод данных прерван\n");
            for (int j = i; j < size; j++) {
                array[j] = 0;
            }
            return;
        }
        else if (result == 1) {
            clear();
            array[i] = value;
        }
        else {
            printf("Ошибка: введите целое число!\n");
            clear();
            i--;
        }
    }
}

void print_array() {
    if (size == 0) {
        printf("Массив не инициализирован! Сначала задайте размер.\n");
        return;
    }
    
    printf("Массив (значения и адреса):\n");
    for (int i = 0; i < size; i++) {
        printf("array[%d] = %d \t (адрес %p)\n", i, array[i], &array[i]);
    }
}

void min_max() {
    if (size == 0) {
        printf("Массив не инициализирован!\n");
        return;
    }
    
    int min_val = array[0];
    int max_val = array[0];
    
    for (int i = 1; i < size; i++) {
        if (array[i] < min_val) {
            min_val = array[i];
        }
        if (array[i] > max_val) {
            max_val = array[i];
        }
    }
    
    printf("Минимальное значение: %d\n", min_val);
    printf("Максимальное значение: %d\n", max_val);
}

void min_max_arr() {
    if (size == 0) {
        printf("Массив не инициализирован!\n");
        return;
    }
    
    int k, m;
    printf("Введите начало диапазона k: ");
    scanf("%d", &k);
    clear();
    
    printf("Введите конец диапазона m: ");
    scanf("%d", &m);
    clear();
    
    if (k < 0 || m >= size || k > m) {
        printf("Ошибка: неверный диапазон! Допустимо: 0 <= k <= m < %d\n", size);
        return;
    }
    
    int min_val = array[k];
    int max_val = array[k];
    
    for (int i = k; i <= m; i++) {
        if (array[i] < min_val) {
            min_val = array[i];
        }
        if (array[i] > max_val) {
            max_val = array[i];
        }
    }
    
    printf("Разница между мин и макс в диапазоне [%d,%d]: %d\n", k, m, max_val - min_val);
}

void sum_value() {
    if (size == 0) {
        printf("Массив не инициализирован!\n");
        return;
    }
    
    int k;
    printf("Введите значение k: ");
    scanf("%d", &k);
    clear();
    
    int sum = 0;
    for (int i = 0; i < size; i++) {
        if (array[i] > k) {
            sum += array[i];
        }
    }
    
    printf("Сумма элементов выше %d: %d\n", k, sum);
}