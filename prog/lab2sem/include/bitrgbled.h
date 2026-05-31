#ifndef BITRGBLED_H
#define BITRGBLED_H

#include <stdio.h>
#include <stdlib.h>

// Режимы работы светодиода
typedef enum
{
    MODE_GLOW = 0,  // Свечение
    MODE_BLINK = 1, // Мерцание
    MODE_FADING = 2 // Затухание
} led_mode;

// ========== РЕАЛИЗАЦИЯ 4: Битовые поля (для сравнения) ==========
// Структура с автоматическим выравниванием компилятора
typedef struct
{
    unsigned int red : 8;    // 0-7 биты
    unsigned int green : 8;  // 8-15 биты
    unsigned int blue : 8;   // 16-23 биты
    unsigned int bright : 8; // 24-31 биты
    unsigned int temp : 14;  // 32-45 биты
    unsigned int module : 2; // 46-47 биты
    unsigned int mode : 2;   // 48-49 биты
} RgbledFields;

// Структура с ручным выравниванием (packed) — экономия памяти
#pragma pack(push, 1)
typedef struct
{
    unsigned int red : 8;
    unsigned int green : 8;
    unsigned int blue : 8;
    unsigned int bright : 8;
    unsigned int temp : 14;
    unsigned int module : 2;
    unsigned int mode : 2;
} RgbledFieldsPacked;
#pragma pack(pop)

//  ОСНОВНАЯ СТРУКТУРА (используем в работе)
// Используем битовые поля для прямого доступа
typedef struct
{
    unsigned int red : 8;    // 0-255
    unsigned int green : 8;  // 0-255
    unsigned int blue : 8;   // 0-255
    unsigned int bright : 8; // 0-255
    unsigned int temp : 14;  // 0-16383
    unsigned int module : 2; // 0-3
    unsigned int mode : 2;   // 0-2
} rgbled;

// КОНСТАНТЫ СДВИГА И МАСОК (для проверок и побитовых операций)
// Константы смещения (Shift)
#define SHIFT_RED 0     // 0-7 биты (8 бит)
#define SHIFT_GREEN 8   // 8-15 биты (8 бит)
#define SHIFT_BLUE 16   // 16-23 биты (8 бит)
#define SHIFT_BRIGHT 24 // 24-31 биты (8 бит)
#define SHIFT_TEMP 32   // 32-45 биты (14 бит)
#define SHIFT_MODULE 46 // 46-47 биты (2 бита)
#define SHIFT_MODE 48   // 48-49 биты (2 бита)

// Константы масок (Mask) — используем вместо "магических чисел"!
#define MASK_RED 0xFF    // 8 бит: 11111111 = 255
#define MASK_GREEN 0xFF  // 8 бит
#define MASK_BLUE 0xFF   // 8 бит
#define MASK_BRIGHT 0xFF // 8 бит
#define MASK_TEMP 0x3FFF // 14 бит: 11111111111111 = 16383
#define MASK_MODULE 0x03 // 2 бита: 11 = 3
#define MASK_MODE 0x03   // 2 бита: 11 = 2 (режимы 0,1,2)

// Структура-обёртка (встраивание)
typedef struct
{
    int id;
    rgbled *pixel; // Указатель на динамический объект
} DeviceSystem;

//  КОНСТРУКТОРЫ И ДЕСТРУКТОРЫ
rgbled *led_create(unsigned int r, unsigned int g, unsigned int b,
                   unsigned int bright, unsigned int temp,
                   unsigned int ctrl, led_mode m);
void led_free(rgbled *led);

//  СЕТТЕРЫ (используют MASK вместо чисел!)
void led_set_red(rgbled *led, unsigned int value);
void led_set_green(rgbled *led, unsigned int value);
void led_set_blue(rgbled *led, unsigned int value);
void led_set_brightness(rgbled *led, unsigned int value);
void led_set_temperature(rgbled *led, unsigned int value);
void led_set_module(rgbled *led, unsigned int value);
void led_set_mode(rgbled *led, led_mode mode);

// Установить все значения сразу
void led_set_all(rgbled *led, unsigned int r, unsigned int g, unsigned int b,
                 unsigned int bright, unsigned int temp,
                 unsigned int ctrl, led_mode m);

//  ГЕТТЕРЫ
unsigned int led_get_red(const rgbled *led);
unsigned int led_get_green(const rgbled *led);
unsigned int led_get_blue(const rgbled *led);
unsigned int led_get_brightness(const rgbled *led);
unsigned int led_get_temperature(const rgbled *led);
unsigned int led_get_module(const rgbled *led);
unsigned int led_get_mode(const rgbled *led);

//  ВЫВОД
void led_print(const rgbled *led);

//  DEVICE SYSTEM
DeviceSystem *system_create(int id, rgbled *pixel);
void system_destroy(DeviceSystem *sys);

//  ДЕМОНСТРАЦИЯ ВЫРАВНИВАНИЯ
void led_show_alignment(void);

#endif
