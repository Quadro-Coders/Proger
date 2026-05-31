#ifndef CALC_H
#define CALC_H

// Набор необходимых библиотек
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h> // Нужен для математических операций, при компиляции вручную нужен флаг -lm

#define MAX_STACK 256      // Макс. количество операндов/операторов, которые могут находиться в стеке одновременно во время вычисления
#define MAX_NUM_STR_LEN 64 // Макс. длина строки одного числа

int calc_evaluate(const char *expression, double *result);
// expression указатель на строку с выражением
// result указатель для записи результата

#endif // CALC_H
