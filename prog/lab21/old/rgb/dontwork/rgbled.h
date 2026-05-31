#ifndef RGBLED_H
#define RGBLED_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

// ============================================================================
// КОНСТАНТЫ ПОБИТОВОЙ АРИФМЕТИКИ (Задание 5)
// ============================================================================
// Распределение в uint64_t (64 бита):
// [07:00]   Красный (8 бит)
// [15:08]   Зелёный (8 бит)
// [23:16]   Синий (8 бит)
// [31:24]   Яркость (8 бит)
// [47:32]   Температура (16 бит)
// [51:48]   Тип модуля (4 бита)
// [54:52]   Режим работы (3 бита)
// [63:55]   Резерв (9 бит)

// Смещения (Offsets)
#define OFFSET_RED 0
#define OFFSET_GREEN 8
#define OFFSET_BLUE 16
#define OFFSET_BRIGHT 24
#define OFFSET_TEMP 32
#define OFFSET_MODULE 48
#define OFFSET_MODE 52

// Маски (Masks)
#define MASK_RED 0xFFULL
#define MASK_GREEN 0xFFULL
#define MASK_BLUE 0xFFULL
#define MASK_BRIGHT 0xFFULL
#define MASK_TEMP 0xFFFFULL
#define MASK_MODULE 0xFULL
#define MASK_MODE 0x7ULL

// Сдвинутые маски для очистки полей
#define MASK_RED_SHIFT (MASK_RED << OFFSET_RED)
#define MASK_GREEN_SHIFT (MASK_GREEN << OFFSET_GREEN)
#define MASK_BLUE_SHIFT (MASK_BLUE << OFFSET_BLUE)
#define MASK_BRIGHT_SHIFT (MASK_BRIGHT << OFFSET_BRIGHT)
#define MASK_TEMP_SHIFT (MASK_TEMP << OFFSET_TEMP)
#define MASK_MODULE_SHIFT (MASK_MODULE << OFFSET_MODULE)
#define MASK_MODE_SHIFT (MASK_MODE << OFFSET_MODE)

// Режимы работы
#define MODE_GLOWING 0
#define MODE_FLICKERING 1
#define MODE_FADING 2

// Начальный размер динамического массива
#define INITIAL_ARRAY_SIZE 10

// ============================================================================
// СТРУКТУРА RGBLED
// ============================================================================
typedef struct
{
    uint64_t data; // Все поля упакованы в одно 64-битное число
} rgbled;

// ============================================================================
// СТРУКТУРА ДИНАМИЧЕСКОГО МАССИВА RGBLED
// ============================================================================
typedef struct
{
    rgbled **leds;   // Массив указателей на rgbled
    size_t count;    // Текущее количество элементов
    size_t capacity; // Текущая вместимость массива
} rgbled_array;

// ============================================================================
// КОНСТРУКТОРЫ И ДЕСТРУКТОР RGBLED
// ============================================================================
rgbled *rgbled_create(void);
rgbled *rgbled_create_full(uint8_t r, uint8_t g, uint8_t b, uint8_t bright,
                           uint16_t temp, uint8_t module, uint8_t mode);
rgbled *rgbled_copy(const rgbled *src);
void rgbled_destroy(rgbled *led);

// ============================================================================
// ФУНКЦИИ ДИНАМИЧЕСКОГО МАССИВА
// ============================================================================
rgbled_array *array_create(void);
void array_destroy(rgbled_array *arr);
int array_add(rgbled_array *arr, rgbled *led);
int array_remove(rgbled_array *arr, size_t index);
rgbled *array_get(rgbled_array *arr, size_t index);
size_t array_count(rgbled_array *arr);
void array_print_all(rgbled_array *arr);

// ============================================================================
// ГЕТТЕРЫ И СЕТТЕРЫ (Побитовая арифметика)
// ============================================================================
uint8_t rgbled_get_red(const rgbled *led);
uint8_t rgbled_get_green(const rgbled *led);
uint8_t rgbled_get_blue(const rgbled *led);
uint8_t rgbled_get_brightness(const rgbled *led);
uint16_t rgbled_get_temp(const rgbled *led);
uint8_t rgbled_get_module(const rgbled *led);
uint8_t rgbled_get_mode(const rgbled *led);

void rgbled_set_red(rgbled *led, uint8_t val);
void rgbled_set_green(rgbled *led, uint8_t val);
void rgbled_set_blue(rgbled *led, uint8_t val);
void rgbled_set_brightness(rgbled *led, uint8_t val);
void rgbled_set_temp(rgbled *led, uint16_t val);
void rgbled_set_module(rgbled *led, uint8_t val);
void rgbled_set_mode(rgbled *led, uint8_t val);

// ============================================================================
// ОПЕРАЦИИ И МЕНЮ
// ============================================================================
void rgbled_print(const rgbled *led);
void rgbled_fill_random(rgbled *led);
int rgbled_eq(const rgbled *l1, const rgbled *l2);

void menu_create_rgbled(rgbled_array *arr);
void menu_print_all(rgbled_array *arr);
void menu_edit_rgbled(rgbled_array *arr);
void menu_compare_rgbled(rgbled_array *arr);
void menu_remove_rgbled(rgbled_array *arr);
void menu_destroy_all(rgbled_array *arr);

// Вспомогательная
void clear_input();

#endif
