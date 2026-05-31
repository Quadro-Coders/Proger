#ifndef MATRIX2D_H
#define MATRIX2D_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "bitrgbled.h"

#define ACCURACY 0.000001f

typedef struct
{
    int rows;      // Количество строк
    int cols;      // Количество столбцов
    int square;    // Флаг: квадратная ли матрица
    float **data;  // Динамический массив указателей на строки
    rgbled **leds; // Массив светодиодов для каждой ячейки (Лаба 2)
} Matrix2D;

// ========== ПРАКТИЧЕСКАЯ РАБОТА №1 ==========
Matrix2D *Matrix2D_create(int rows, int cols);
Matrix2D *Matrix2D_create_default(void);
Matrix2D *Matrix2D_copy(const Matrix2D *other);
void Matrix2D_free(Matrix2D *m);
float Matrix2D_abs_sum(const Matrix2D *m);
int Matrix2D_eq(const Matrix2D *a, const Matrix2D *b);
int Matrix2D_ne(const Matrix2D *a, const Matrix2D *b);
int Matrix2D_gt(const Matrix2D *a, const Matrix2D *b);
int Matrix2D_lt(const Matrix2D *a, const Matrix2D *b);
int Matrix2D_ge(const Matrix2D *a, const Matrix2D *b);
int Matrix2D_le(const Matrix2D *a, const Matrix2D *b);
void Matrix2D_input(Matrix2D *m);
void Matrix2D_print(const Matrix2D *m);
void Matrix2D_set(Matrix2D *m, int row, int col, float val);
float Matrix2D_get(const Matrix2D *m, int row, int col);
void Matrix2D_inc(Matrix2D *m);
void Matrix2D_dec(Matrix2D *m);
void Matrix2D_fill_random(Matrix2D *m, float min, float max);
Matrix2D *Matrix2D_get_row(const Matrix2D *m, int row_idx);
Matrix2D *Matrix2D_get_col(const Matrix2D *m, int col_idx);
Matrix2D *Matrix2D_transpose(const Matrix2D *m);
float Matrix2D_det(const Matrix2D *m);

// ========== ПРАКТИЧЕСКАЯ РАБОТА №2 ==========
void Matrix2D_set_led(Matrix2D *m, int row, int col, int r, int g, int b,
                      int bright, int temp, int ctrl, led_mode mode);
void Matrix2D_print_led(const Matrix2D *m, int row, int col);
void Matrix2D_print_all(const Matrix2D *m);

#endif
