#ifndef BITRGBLED_H
#define BITRGBLED_H

#include <stdio.h>
#include <stdlib.h>

// Реализация 4 (чисто для сравнения затраты памяти)
// Структура с побитовыми полями (компилятор выравнивает)
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

// Структура с побитовыми полями (без выравнивания, pragma pack)
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

// Реализация 5 (структура для реализации побитовой арифметики)
// Основная структура (хранит всё в одном числе)
typedef struct
{
    unsigned long long data; // 64 бита для хранения всех полей
} Rgbled;

// Константы смещения (Shift)
#define SHIFT_RED 0     // 0-7 биты (8 бит)
#define SHIFT_GREEN 8   // 8-15 биты (8 бит)
#define SHIFT_BLUE 16   // 16-23 биты (8 бит)
#define SHIFT_BRIGHT 24 // 24-31 биты (8 бит)
#define SHIFT_TEMP 32   // 32-45 биты (14 бит)
#define SHIFT_MODULE 46 // 46-47 биты (2 бита)
#define SHIFT_MODE 48   // 48-49 биты (2 бита)

// Константы масок (Mask)
#define MASK_RED 0xFF    // 8 бит: 11111111
#define MASK_GREEN 0xFF  // 8 бит
#define MASK_BLUE 0xFF   // 8 бит
#define MASK_BRIGHT 0xFF // 8 бит
#define MASK_TEMP 0x3FFF // 14 бит: 11111111111111
#define MASK_MODULE 0x03 // 2 бита: 11
#define MASK_MODE 0x03   // 2 бита: 11

// Структура-обертка (встраивание)
typedef struct
{
    int id;
    Rgbled *pixel; // Указатель на динамический объект
} DeviceSystem;

// Методы для Rgbled
// Конструктор
Rgbled *rgbled_create(unsigned int r, unsigned int g, unsigned int b, unsigned int bright, unsigned int temp, unsigned int module, unsigned int mode);
void rgbled_destroy(Rgbled *led);     // Деструктор
void rgbled_print(const Rgbled *led); // Вывод

// Методы для DeviceSystem
DeviceSystem *system_create(int id, Rgbled *pixel); // Конструктор
void system_destroy(DeviceSystem *sys);             // Деструктор

#endif
