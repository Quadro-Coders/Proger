#include "matrixfunc.h"

int matrix[ROW][COL];  // Глобальная матрица
int matrix_initialized = 0;  // Флаг инициализации матрицы

void clear() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// Проверка, инициализирована ли матрица
int is_matrix_initialized() {
    if (!matrix_initialized) {
        printf("Матрица не инициализирована! Сначала заполните матрицу.\n");
        return 0;
    }
    return 1;
}

// Ввод матрицы с клавиатуры
void input_diagonal() {
    printf("Введите матрицу %dx%d построчно:\n", ROW, COL);
    
    // Ввод данных с клавиатуры построчно
    for (int i = 0; i < ROW; i++) {
        printf("Строка %d: ", i + 1);
        for (int j = 0; j < COL; j++) {
            scanf("%d", &matrix[i][j]);
        }
        clear();
    }
    matrix_initialized = 1;
}

// Отображение матрицы по диагонали с нижнего левого угла
void print_matrix_diagonal() {
    // Создаем порядок заполнения по диагонали с нижнего левого угла
    int order[ROW][COL];
    int num = 1;
    
    // Заполняем порядок по диагонали с нижнего левого угла
    for (int start_row = ROW - 1; start_row >= 0; start_row--) {
        int i = start_row;
        int j = 0;
        while (i < ROW && j < COL) {
            order[i][j] = num++;
            i++;
            j++;
        }
    }
    
    for (int start_col = 1; start_col < COL; start_col++) {
        int i = 0;
        int j = start_col;
        while (i < ROW && j < COL) {
            order[i][j] = num++;
            i++;
            j++;
        }
    }
    
    // Вывод заголовка с номерами столбцов
    printf("     ");
    for (int j = 0; j < COL; j++) {
        printf("%4d ", j + 1);
    }
    printf("\n");
    
    // Вывод разделительной линии
    printf("     ");
    for (int j = 0; j < COL; j++) {
        printf("-----");
    }
    printf("\n");
    
    // Вывод матрицы в порядке диагонали с нижнего левого угла
    for (int i = 0; i < ROW; i++) {
        printf("%2d | ", i + 1);
        for (int j = 0; j < COL; j++) {
            // Находим, какое значение должно быть в этой позиции при диагональном заполнении
            int pos = order[i][j] - 1;  // Позиция в линейном массиве (0-99)
            int original_i = pos / COL;  // Исходная строка введенных данных
            int original_j = pos % COL;  // Исходный столбец введенных данных
            
            printf("%3d ", matrix[original_i][original_j]);
        }
        printf("\n");
    }
}

// Вывод матрицы с индексами
void print_matrix_data() {
    if (!is_matrix_initialized()) return;
    
    printf("Матрица (отображение по диагонали с нижнего левого угла):\n");
    print_matrix_diagonal();
}

// 15. Определение индексов элементов > k в столбцах m-l
void find_indices_above_k(int k, int m, int l) {
    if (!is_matrix_initialized()) return;
    
    printf("Индексы элементов > %d в столбцах %d-%d:\n", k, m, l);
    int found = 0;
    
    for (int j = m - 1; j < l && j < COL; j++) {
        for (int i = 0; i < ROW; i++) {
            int *ptr = &matrix[i][j];
            if (*ptr > k) {
                printf("(%d, %d) ", i + 1, j + 1);
                found = 1;
            }
        }
    }
    
    if (!found) {
        printf("Элементы не найдены");
    }
    printf("\n");
}

// 21. Сумма всех четных элементов матрицы
int calculate_sum_even() {
    int sum = 0;
    int *ptr = &matrix[0][0];
    int *end = ptr + ROW * COL;
    
    while (ptr < end) {
        if (*ptr % 2 == 0) {
            sum += *ptr;
        }
        ptr++;
    }
    return sum;
}

// Функции меню
void input_matrix() {
    input_diagonal();
    printf("Матрица введена!\n");
}

void print_matrix() {
    printf("Матрица:\n");
    print_matrix_data();
}

void find_indices() {
    if (!is_matrix_initialized()) return;
    
    int k, m, l;
    printf("Введите k, m, l: ");
    scanf("%d %d %d", &k, &m, &l);
    clear();
    
    if (m < 1 || l > COL || m > l) {
        printf("Ошибка: некорректный диапазон столбцов!\n");
    } else {
        find_indices_above_k(k, m, l);
    }
}
void sum_even() {
    if (!is_matrix_initialized()) return;
    
    int sum = calculate_sum_even();
    printf("Сумма чётных элементов: %d\n", sum);
}