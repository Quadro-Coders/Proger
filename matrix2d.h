#ifndef MATRIX2D_H
#define MATRIX2D_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

// Структура матрицы: размеры, флаг квадратности, данные
typedef struct
{
    int rows;        // число строк
    int cols;        // число столбцов
    bool has_diag;   // квадратная? (rows == cols)
    float **data;    // двумерный массив
} matrix2d;

// Создание/удаление
matrix2d *matrix2d_default();                    // матрица 1x1
matrix2d *matrix2d_create(int rows, int cols);   // создать матрицу
matrix2d *matrix2d_copy(const matrix2d *src);    // копия матрицы
void matrix2d_destroy(matrix2d *m);               // удалить матрицу

// Сравнение по норме
bool matrix2d_eq(const matrix2d *m1, const matrix2d *m2);  // равно
bool matrix2d_ne(const matrix2d *m1, const matrix2d *m2);  // не равно
bool matrix2d_lt(const matrix2d *m1, const matrix2d *m2);  // меньше
bool matrix2d_gt(const matrix2d *m1, const matrix2d *m2);  // больше
bool matrix2d_le(const matrix2d *m1, const matrix2d *m2);  // меньше или равно
bool matrix2d_ge(const matrix2d *m1, const matrix2d *m2);  // больше или равно

// Ввод/вывод
void matrix2d_input(matrix2d *m);                 // ввод с клавиатуры
void matrix2d_print(const matrix2d *m);           // вывод на экран

// Работа с элементами
void matrix2d_set(matrix2d *m, int row, int col, float value);  // изменить элемент
float matrix2d_get(const matrix2d *m, int row, int col);       // получить элемент
void matrix2d_inc(matrix2d *m);                    // прибавить 1 ко всем
void matrix2d_dec(matrix2d *m);                    // вычесть 1 из всех

// Случайные числа
void matrix2d_fill_random(matrix2d *m, float min, float max);  // заполнить случайно

// Извлечение частей
matrix2d *matrix2d_get_row(const matrix2d *m, int row_idx);  // строка как матрица
matrix2d *matrix2d_get_col(const matrix2d *m, int col_idx);  // столбец как матрица

// Транспонирование
matrix2d *matrix2d_transpose(const matrix2d *m);  // транспонированная

// Определитель (только для квадратных)
float matrix2d_determinant(const matrix2d *m);    // найти определитель

// Обратная матрица (только для квадратных)
matrix2d *matrix2d_inverse(const matrix2d *m);    // найти обратную

// Функции меню
void menu_create_matrix(matrix2d **m);            // создать через меню
void menu_print_matrix(const matrix2d *m);        // вывести через меню
void menu_fill_random(matrix2d *m);                // заполнить случайно через меню
void menu_set_element(matrix2d *m);                // изменить элемент через меню
void menu_increment(matrix2d *m);                  // инкремент через меню
void menu_decrement(matrix2d *m);                  // декремент через меню
void menu_get_row(const matrix2d *m);              // получить строку через меню
void menu_get_col(const matrix2d *m);              // получить столбец через меню
void menu_transpose(matrix2d **m);                 // транспонировать через меню
void menu_determinant(const matrix2d *m);          // определитель через меню
void menu_inverse(const matrix2d *m);              // обратная через меню
void menu_compare(const matrix2d *m1, const matrix2d *m2);  // сравнить через меню
void menu_destroy(matrix2d **m);                   // удалить через меню

// Вспомогательное
void clear_input();                                // очистить буфер ввода
bool is_matrix_created(const matrix2d *m);         // проверка на NULL
float matrix2d_norm(const matrix2d *m);            // квадрат нормы

#endif