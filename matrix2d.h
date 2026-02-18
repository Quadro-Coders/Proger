#ifndef MATRIX2D_H
#define MATRIX2D_H

#include <stdio.h>

// Структура двумерной матрицы
typedef struct {
    int rows;          // Количество строк
    int cols;          // Количество столбцов
    int has_diag;      // Флаг: имеет ли матрица главную диагональ (1 - да, 0 - нет)
    float** data;      // Динамический массив указателей на строки
} matrix2d;

// Функция для очистки буфера ввода
void clear();

// Конструкторы и деструктор
matrix2d* matrix2d_default();
matrix2d* matrix2d_create(int rows, int cols);
matrix2d* matrix2d_copy(const matrix2d* src);
void matrix2d_destroy(matrix2d* m);

// Операторы сравнения
int matrix2d_eq(const matrix2d* m1, const matrix2d* m2);
int matrix2d_ne(const matrix2d* m1, const matrix2d* m2);
int matrix2d_lt(const matrix2d* m1, const matrix2d* m2);
int matrix2d_gt(const matrix2d* m1, const matrix2d* m2);
int matrix2d_le(const matrix2d* m1, const matrix2d* m2);
int matrix2d_ge(const matrix2d* m1, const matrix2d* m2);

// Ввод/вывод матриц
void matrix2d_input(matrix2d* m);
void matrix2d_print(const matrix2d* m);

// Изменение данных структуры
void matrix2d_set(matrix2d* m, int row, int col, float value);
float matrix2d_get(const matrix2d* m, int row, int col);
void matrix2d_inc(matrix2d* m);
void matrix2d_dec(matrix2d* m);

// Заполнение матрицы случайными значениями
void matrix2d_fill_random(matrix2d* m, float min, float max);

// Получение столбца/строки
matrix2d* matrix2d_get_row(const matrix2d* m, int row_idx);
matrix2d* matrix2d_get_col(const matrix2d* m, int col_idx);

// Транспонирование матрицы
matrix2d* matrix2d_transpose(const matrix2d* m);

// Нахождение определителя (детерминант)
float matrix2d_determinant(const matrix2d* m);

// Вычисление обратной матрицы
matrix2d* matrix2d_inverse(const matrix2d* m);

// Функции меню
void menu_create_matrix(matrix2d** m);
void menu_print_matrix(const matrix2d* m);
void menu_fill_random(matrix2d* m);
void menu_set_element(matrix2d* m);
void menu_increment(matrix2d* m);
void menu_decrement(matrix2d* m);
void menu_get_row(const matrix2d* m);
void menu_get_col(const matrix2d* m);
void menu_transpose(matrix2d** m);
void menu_determinant(const matrix2d* m);
void menu_inverse(const matrix2d* m);
void menu_compare(const matrix2d* m1, const matrix2d* m2);
void menu_destroy(matrix2d** m);

// Вспомогательные функции
int is_matrix_created(const matrix2d* m);
float matrix2d_norm(const matrix2d* m);

#endif