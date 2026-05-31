#ifndef FIOSTRUCT_H
#define FIOSTRUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix2d.h"
#include "contstruct.h"

// Генерация n структур Matrix2D с заданными размерами
Queue *rand_gen_struct_in_container(size_t n, int rows, int cols);

// Сохранение/загрузка (binary=1 включает бинарный режим)
int save_queue_to_file(const char *filename, Queue *q, int binary, size_t element_size);
Queue *load_queue_from_file(const char *filename, int binary, size_t element_size);

// Утилиты файла
size_t count_objects_in_file(const char *filename, int binary, size_t element_size);
Matrix2D *get_i_th_element(const char *filename, int index, int binary, size_t element_size);
void list_file_objects(const char *filename, int binary, size_t element_size);

// Точные сигнатуры из ТЗ (Задание 4)
Matrix2D *get_element_from_text_file(const char *filename, int index);
int get_element_from_binary_file(const char *filename, int index, size_t element_size, void *result);

#endif
