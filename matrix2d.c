#include "matrix2d.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define EPSILON 0.000001f

// Функция для очистки буфера ввода
void clear() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// Вспомогательная функция: абсолютное значение float
static float _fabs(float x) {
    return (x < 0.0f) ? -x : x;
}

// Проверка, создана ли матрица
int is_matrix_created(const matrix2d* m) {
    if (!m) {
        printf("Матрица не создана!\n");
        return 0;
    }
    return 1;
}

// Норма Фробениуса (квадрат нормы - без корня)
float matrix2d_norm(const matrix2d* m) {
    if (!m) return 0.0f;
    float sum = 0.0f;
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            float val = m->data[i][j];
            sum += val * val;
        }
    }
    return sum;
}

matrix2d* matrix2d_default() {
    return matrix2d_create(1, 1);
}

matrix2d* matrix2d_create(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        printf("Ошибка: размеры матрицы должны быть положительными!\n");
        return NULL;
    }
        matrix2d* m = (matrix2d*)malloc(sizeof(matrix2d));
    if (!m) {
        printf("Ошибка выделения памяти!\n");
        return NULL;
    }
    
    m->rows = rows;
    m->cols = cols;
    m->has_diag = (rows == cols) ? 1 : 0;
    
    m->data = (float**)malloc(rows * sizeof(float*));
    if (!m->data) {
        free(m);
        printf("Ошибка выделения памяти!\n");
        return NULL;
    }
    
    for (int i = 0; i < rows; i++) {
        m->data[i] = (float*)calloc(cols, sizeof(float));
        if (!m->data[i]) {
            for (int j = 0; j < i; j++) {
                free(m->data[j]);
            }
            free(m->data);
            free(m);
            printf("Ошибка выделения памяти!\n");
            return NULL;
        }
    }
    
    return m;
}

matrix2d* matrix2d_copy(const matrix2d* src) {
    if (!src) {
        printf("Ошибка: исходная матрица не существует!\n");
        return NULL;
    }
    
    matrix2d* m = matrix2d_create(src->rows, src->cols);
    if (!m) return NULL;
    
    for (int i = 0; i < src->rows; i++) {
        memcpy(m->data[i], src->data[i], src->cols * sizeof(float));
    }
    
    return m;
}

void matrix2d_destroy(matrix2d* m) {    if (!m) return;
    
    if (m->data) {
        for (int i = 0; i < m->rows; i++) {
            free(m->data[i]);
        }
        free(m->data);
    }
    free(m);
}

int matrix2d_eq(const matrix2d* m1, const matrix2d* m2) {
    if (!m1 || !m2) return 0;
    if (m1->rows != m2->rows || m1->cols != m2->cols) return 0;
    
    for (int i = 0; i < m1->rows; i++) {
        for (int j = 0; j < m1->cols; j++) {
            if (_fabs(m1->data[i][j] - m2->data[i][j]) > EPSILON) {
                return 0;
            }
        }
    }
    return 1;
}

int matrix2d_ne(const matrix2d* m1, const matrix2d* m2) {
    return !matrix2d_eq(m1, m2);
}

int matrix2d_lt(const matrix2d* m1, const matrix2d* m2) {
    float norm1 = matrix2d_norm(m1);
    float norm2 = matrix2d_norm(m2);
    return (norm1 < norm2 - EPSILON) ? 1 : 0;
}

int matrix2d_gt(const matrix2d* m1, const matrix2d* m2) {
    float norm1 = matrix2d_norm(m1);
    float norm2 = matrix2d_norm(m2);
    return (norm1 > norm2 + EPSILON) ? 1 : 0;
}

int matrix2d_le(const matrix2d* m1, const matrix2d* m2) {
    return !matrix2d_gt(m1, m2);
}

int matrix2d_ge(const matrix2d* m1, const matrix2d* m2) {
    return !matrix2d_lt(m1, m2);
}

void matrix2d_input(matrix2d* m) {    if (!m) {
        printf("Ошибка: матрица не создана!\n");
        return;
    }
    
    printf("Введите %d элементов матрицы %dx%d:\n", m->rows * m->cols, m->rows, m->cols);
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            printf("  [%d][%d] = ", i, j);
            scanf("%f", &m->data[i][j]);
        }
    }
}

void matrix2d_print(const matrix2d* m) {
    if (!m) {
        printf("[NULL matrix]\n");
        return;
    }
    
    printf("Матрица %dx%d [%s диагональ]:\n", 
           m->rows, m->cols, m->has_diag ? "с" : "без");
    
    for (int i = 0; i < m->rows; i++) {
        printf("[");
        for (int j = 0; j < m->cols; j++) {
            printf("%8.3f", m->data[i][j]);
            if (j < m->cols - 1) printf(" ");
        }
        printf("]\n");
    }
}

void matrix2d_set(matrix2d* m, int row, int col, float value) {
    if (!m) {
        printf("Ошибка: матрица не создана!\n");
        return;
    }
    if (row < 0 || row >= m->rows || col < 0 || col >= m->cols) {
        printf("Ошибка: индекс вне диапазона!\n");
        return;
    }
    m->data[row][col] = value;
}

float matrix2d_get(const matrix2d* m, int row, int col) {
    if (!m) return 0.0f;
    if (row < 0 || row >= m->rows || col < 0 || col >= m->cols) {
        printf("Ошибка: индекс вне диапазона!\n");
        return 0.0f;    }
    return m->data[row][col];
}

void matrix2d_inc(matrix2d* m) {
    if (!m) {
        printf("Ошибка: матрица не создана!\n");
        return;
    }
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            m->data[i][j] += 1.0f;
        }
    }
}

void matrix2d_dec(matrix2d* m) {
    if (!m) {
        printf("Ошибка: матрица не создана!\n");
        return;
    }
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            m->data[i][j] -= 1.0f;
        }
    }
}

void matrix2d_fill_random(matrix2d* m, float min, float max) {
    if (!m) {
        printf("Ошибка: матрица не создана!\n");
        return;
    }
    
    static int seeded = 0;
    if (!seeded) {
        srand((unsigned int)time(NULL));
        seeded = 1;
    }
    
    float range = max - min;
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            m->data[i][j] = min + range * (float)rand() / (RAND_MAX + 1.0f);
        }
    }
}

static matrix2d* _matrix2d_minor(const matrix2d* m, int skip_row, int skip_col) {
    if (!m || !m->has_diag || m->rows <= 1) return NULL;    
    int n = m->rows - 1;
    matrix2d* minor = matrix2d_create(n, n);
    if (!minor) return NULL;
    
    int di = 0;
    for (int i = 0; i < m->rows; i++) {
        if (i == skip_row) continue;
        int dj = 0;
        for (int j = 0; j < m->cols; j++) {
            if (j == skip_col) continue;
            minor->data[di][dj++] = m->data[i][j];
        }
        di++;
    }
    
    return minor;
}

matrix2d* matrix2d_get_row(const matrix2d* m, int row_idx) {
    if (!m) {
        printf("Ошибка: матрица не создана!\n");
        return NULL;
    }
    if (row_idx < 0 || row_idx >= m->rows) {
        printf("Ошибка: индекс строки вне диапазона!\n");
        return NULL;
    }
    
    matrix2d* row = matrix2d_create(1, m->cols);
    if (!row) return NULL;
    
    memcpy(row->data[0], m->data[row_idx], m->cols * sizeof(float));
    return row;
}

matrix2d* matrix2d_get_col(const matrix2d* m, int col_idx) {
    if (!m) {
        printf("Ошибка: матрица не создана!\n");
        return NULL;
    }
    if (col_idx < 0 || col_idx >= m->cols) {
        printf("Ошибка: индекс столбца вне диапазона!\n");
        return NULL;
    }
    
    matrix2d* col = matrix2d_create(m->rows, 1);
    if (!col) return NULL;
    
    for (int i = 0; i < m->rows; i++) {        col->data[i][0] = m->data[i][col_idx];
    }
    return col;
}

matrix2d* matrix2d_transpose(const matrix2d* m) {
    if (!m) {
        printf("Ошибка: матрица не создана!\n");
        return NULL;
    }
    
    matrix2d* t = matrix2d_create(m->cols, m->rows);
    if (!t) return NULL;
    
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            t->data[j][i] = m->data[i][j];
        }
    }
    
    return t;
}

float matrix2d_determinant(const matrix2d* m) {
    if (!m) {
        printf("Ошибка: матрица не создана!\n");
        return 0.0f;
    }
    if (!m->has_diag) {
        printf("Ошибка: определитель можно найти только для квадратной матрицы!\n");
        return 0.0f;
    }
    
    int n = m->rows;
    
    if (n == 1) return m->data[0][0];
    if (n == 2) {
        return m->data[0][0] * m->data[1][1] - m->data[0][1] * m->data[1][0];
    }
    
    float det = 0.0f;
    for (int j = 0; j < n; j++) {
        matrix2d* minor = _matrix2d_minor(m, 0, j);
        if (minor) {
            float subdet = matrix2d_determinant(minor);
            det += ((j % 2) ? -1.0f : 1.0f) * m->data[0][j] * subdet;
            matrix2d_destroy(minor);
        }
    }
        return det;
}

matrix2d* matrix2d_inverse(const matrix2d* m) {
    if (!m) {
        printf("Ошибка: матрица не создана!\n");
        return NULL;
    }
    if (!m->has_diag) {
        printf("Ошибка: обратную матрицу можно найти только для квадратной матрицы!\n");
        return NULL;
    }
    
    float det = matrix2d_determinant(m);
    if (_fabs(det) < EPSILON) {
        printf("Ошибка: матрица вырожденная, обратная не существует!\n");
        return NULL;
    }
    
    int n = m->rows;
    matrix2d* inv = matrix2d_create(n, n);
    if (!inv) return NULL;
    
    if (n == 1) {
        inv->data[0][0] = 1.0f / m->data[0][0];
        return inv;
    }
    if (n == 2) {
        inv->data[0][0] =  m->data[1][1] / det;
        inv->data[0][1] = -m->data[0][1] / det;
        inv->data[1][0] = -m->data[1][0] / det;
        inv->data[1][1] =  m->data[0][0] / det;
        return inv;
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix2d* minor = _matrix2d_minor(m, i, j);
            if (minor) {
                float subdet = matrix2d_determinant(minor);
                inv->data[j][i] = (((i + j) % 2) ? -1.0f : 1.0f) * subdet / det;
                matrix2d_destroy(minor);
            }
        }
    }
    
    return inv;
}

void menu_create_matrix(matrix2d** m) {    if (*m) {
        printf("Матрица уже существует! Уничтожьте её сначала.\n");
        return;
    }
    
    int rows, cols;
    printf("\nСоздание матрицы:\n");
    printf("Введите количество строк: ");
    scanf("%d", &rows);
    clear();
    
    printf("Введите количество столбцов: ");
    scanf("%d", &cols);
    clear();
    
    if (rows <= 0 || cols <= 0) {
        printf("Ошибка: размеры должны быть положительными!\n");
        return;
    }
    
    *m = matrix2d_create(rows, cols);
    if (!*m) {
        printf("Ошибка создания матрицы!\n");
        return;
    }
    
    int choice;
    printf("Хотите ввести данные вручную? (1 - да, 0 - нет): ");
    scanf("%d", &choice);
    clear();
    
    if (choice == 1) {
        matrix2d_input(*m);
    }
    
    printf("Матрица успешно создана!\n");
    matrix2d_print(*m);
}

void menu_print_matrix(const matrix2d* m) {
    if (!is_matrix_created(m)) return;
    
    printf("\nТекущая матрица:\n");
    matrix2d_print(m);
}

void menu_fill_random(matrix2d* m) {
    if (!is_matrix_created(m)) return;
    
    float min, max;    printf("\nЗаполнение случайными значениями:\n");
    printf("Введите минимальное значение: ");
    scanf("%f", &min);
    clear();
    
    printf("Введите максимальное значение: ");
    scanf("%f", &max);
    clear();
    
    if (min >= max) {
        printf("Ошибка: минимальное значение должно быть меньше максимального!\n");
        return;
    }
    
    matrix2d_fill_random(m, min, max);
    printf("Матрица заполнена случайными значениями!\n");
    matrix2d_print(m);
}

void menu_set_element(matrix2d* m) {
    if (!is_matrix_created(m)) return;
    
    int row, col;
    float value;
    
    printf("\nИзменение элемента матрицы:\n");
    printf("Текущая матрица:\n");
    matrix2d_print(m);
    
    printf("Введите номер строки (0-%d): ", m->rows - 1);
    scanf("%d", &row);
    clear();
    
    printf("Введите номер столбца (0-%d): ", m->cols - 1);
    scanf("%d", &col);
    clear();
    
    if (row < 0 || row >= m->rows || col < 0 || col >= m->cols) {
        printf("Ошибка: индекс вне диапазона!\n");
        return;
    }
    
    printf("Введите новое значение: ");
    scanf("%f", &value);
    clear();
    
    matrix2d_set(m, row, col, value);
    printf("Элемент [%d][%d] изменен на %.3f!\n", row, col, value);
    matrix2d_print(m);
}
void menu_increment(matrix2d* m) {
    if (!is_matrix_created(m)) return;
    
    printf("\nИнкремент матрицы (++): все элементы + 1\n");
    printf("До:\n");
    matrix2d_print(m);
    
    matrix2d_inc(m);
    
    printf("После:\n");
    matrix2d_print(m);
    printf("Инкремент выполнен!\n");
}

void menu_decrement(matrix2d* m) {
    if (!is_matrix_created(m)) return;
    
    printf("\nДекремент матрицы (--): все элементы - 1\n");
    printf("До:\n");
    matrix2d_print(m);
    
    matrix2d_dec(m);
    
    printf("После:\n");
    matrix2d_print(m);
    printf("Декремент выполнен!\n");
}

void menu_get_row(const matrix2d* m) {
    if (!is_matrix_created(m)) return;
    
    int row_idx;
    printf("\nПолучение строки матрицы:\n");
    printf("Введите номер строки (0-%d): ", m->rows - 1);
    scanf("%d", &row_idx);
    clear();
    
    if (row_idx < 0 || row_idx >= m->rows) {
        printf("Ошибка: индекс строки вне диапазона!\n");
        return;
    }
    
    matrix2d* row = matrix2d_get_row(m, row_idx);
    if (!row) {
        printf("Ошибка получения строки!\n");
        return;
    }
    
    printf("Строка %d:\n", row_idx);    matrix2d_print(row);
    matrix2d_destroy(row);
}

void menu_get_col(const matrix2d* m) {
    if (!is_matrix_created(m)) return;
    
    int col_idx;
    printf("\nПолучение столбца матрицы:\n");
    printf("Введите номер столбца (0-%d): ", m->cols - 1);
    scanf("%d", &col_idx);
    clear();
    
    if (col_idx < 0 || col_idx >= m->cols) {
        printf("Ошибка: индекс столбца вне диапазона!\n");
        return;
    }
    
    matrix2d* col = matrix2d_get_col(m, col_idx);
    if (!col) {
        printf("Ошибка получения столбца!\n");
        return;
    }
    
    printf("Столбец %d:\n", col_idx);
    matrix2d_print(col);
    matrix2d_destroy(col);
}

void menu_transpose(matrix2d** m) {
    if (!is_matrix_created(*m)) return;
    
    printf("\nТранспонирование матрицы:\n");
    printf("Исходная:\n");
    matrix2d_print(*m);
    
    matrix2d* transposed = matrix2d_transpose(*m);
    if (!transposed) {
        printf("Ошибка транспонирования!\n");
        return;
    }
    
    printf("Транспонированная:\n");
    matrix2d_print(transposed);
    
    int choice;
    printf("Заменить исходную матрицу? (1 - да, 0 - нет): ");
    scanf("%d", &choice);
    clear();
        if (choice == 1) {
        matrix2d_destroy(*m);
        *m = transposed;
        printf("Матрица заменена!\n");
    } else {
        matrix2d_destroy(transposed);
        printf("Матрица осталась без изменений.\n");
    }
}

void menu_determinant(const matrix2d* m) {
    if (!is_matrix_created(m)) return;
    
    if (!m->has_diag) {
        printf("Ошибка: определитель можно найти только для квадратной матрицы!\n");
        printf("Текущая матрица: %dx%d\n", m->rows, m->cols);
        return;
    }
    
    printf("\nВычисление определителя:\n");
    matrix2d_print(m);
    
    float det = matrix2d_determinant(m);
    printf("Определитель det = %.6f\n", det);
}

void menu_inverse(const matrix2d* m) {
    if (!is_matrix_created(m)) return;
    
    if (!m->has_diag) {
        printf("Ошибка: обратную матрицу можно найти только для квадратной матрицы!\n");
        printf("Текущая матрица: %dx%d\n", m->rows, m->cols);
        return;
    }
    
    printf("\nВычисление обратной матрицы:\n");
    printf("Исходная:\n");
    matrix2d_print(m);
    
    float det = matrix2d_determinant(m);
    printf("Определитель: %.6f\n", det);
    
    if (_fabs(det) < 1e-6f) {
        printf("Матрица вырожденная - обратная не существует!\n");
        return;
    }
    
    matrix2d* inverse = matrix2d_inverse(m);
    if (!inverse) {
        printf("Ошибка вычисления!\n");        return;
    }
    
    printf("Обратная матрица:\n");
    matrix2d_print(inverse);
    
    float det_inv = matrix2d_determinant(inverse);
    printf("Проверка: det(A) * det(A^-1) = %.6f\n", det * det_inv);
    
    matrix2d_destroy(inverse);
}

void menu_compare(const matrix2d* m1, const matrix2d* m2) {
    if (!is_matrix_created(m1)) {
        printf("Матрица A не создана!\n");
        return;
    }
    if (!is_matrix_created(m2)) {
        printf("Матрица B не создана!\n");
        return;
    }
    
    printf("\nСравнение матриц A и B:\n");
    printf("Матрица A:\n");
    matrix2d_print(m1);
    
    printf("Матрица B:\n");
    matrix2d_print(m2);
    
    printf("\nРезультаты сравнения:\n");
    printf("A == B: %s\n", matrix2d_eq(m1, m2) ? "true" : "false");
    printf("A != B: %s\n", matrix2d_ne(m1, m2) ? "true" : "false");
    printf("A > B:  %s\n", matrix2d_gt(m1, m2) ? "true" : "false");
    printf("A < B:  %s\n", matrix2d_lt(m1, m2) ? "true" : "false");
    printf("A >= B: %s\n", matrix2d_ge(m1, m2) ? "true" : "false");
    printf("A <= B: %s\n", matrix2d_le(m1, m2) ? "true" : "false");
}

void menu_destroy(matrix2d** m) {
    if (!*m) {
        printf("Матрица не создана!\n");
        return;
    }
    
    matrix2d_destroy(*m);
    *m = NULL;
    printf("Матрица уничтожена.\n");
}