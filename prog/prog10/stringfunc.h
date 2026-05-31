#ifndef STRINGFUNC_H
#define STRINGFUNC_H

#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>

#define MAX_TEXT_LENGTH 10000
#define MAX_RESULT_LENGTH 20000


// Функция 1: подсчет количества каждого символа в тексте
void countCharacters(const wchar_t* text);

// Функция 2: определение средней длины слова в тексте
double averageWordLength(const wchar_t* text);

// Функция 3: вычисление количества слов между первой и последней запятой
int wordsBetweenCommas(const wchar_t* text);

// Функция 4: деление слова на две части и возврат меньшей части
void splitTextWords(const wchar_t* text, wchar_t* result);

#endif