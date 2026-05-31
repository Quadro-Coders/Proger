#ifndef CALC_H
#define CALC_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

// Глобальные переменные
extern double variables[26]; // Переменные a-z (храним как double)
extern const char *input_ptr; // Указатель на текущую позицию в строке

// Функции парсера (Рекурсивный спуск)
double parse_expression(void);
double parse_term(void);
double parse_factor(void);
double parse_power(void); // Для степени ^ (битовый XOR или математическая степень)
double parse_unary(void);
double parse_primary(void);

// Вспомогательные функции
void skip_spaces(void);
void error_exit(const char *msg);

#endif // CALC_H