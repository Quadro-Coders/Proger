#include "bitrgbled.h"

// Конструктор
Rgbled *rgbled_create(unsigned int r, unsigned int g, unsigned int b, unsigned int bright, unsigned int temp, unsigned int module, unsigned int mode)
{
    Rgbled *new_led = (Rgbled *)malloc(sizeof(Rgbled));
    if (new_led == NULL)
    {
        return NULL;
    }

    // Все биты ставим в 0
    new_led->data = 0;

    // Записываем каждое поле с помощью побитовых операций
    // Формула: (Значение & Маска) << Сдвиг
    // Красный (8 бит, сдвиг 0)
    new_led->data |= ((unsigned long long)(r & MASK_RED) << SHIFT_RED);

    // Зеленый (8 бит, сдвиг 8)
    new_led->data |= ((unsigned long long)(g & MASK_GREEN) << SHIFT_GREEN);

    // Синий (8 бит, сдвиг 16)
    new_led->data |= ((unsigned long long)(b & MASK_BLUE) << SHIFT_BLUE);

    // Яркость (4 бита, сдвиг 24)
    new_led->data |= ((unsigned long long)(bright & MASK_BRIGHT) << SHIFT_BRIGHT);

    // Температура (10 бит, сдвиг 28)
    new_led->data |= ((unsigned long long)(temp & MASK_TEMP) << SHIFT_TEMP);

    // Модуль управления (2 бита, сдвиг 38)
    new_led->data |= ((unsigned long long)(module & MASK_MODULE) << SHIFT_MODULE);

    // Режим (2 бита, сдвиг 40)
    new_led->data |= ((unsigned long long)(mode & MASK_MODE) << SHIFT_MODE);

    return new_led;
}

// Деструктор для Rgbled
void rgbled_destroy(Rgbled *led)
{
    if (led != NULL)
    {
        free(led);
        led = NULL;
    }
}

// Вывод для Rgbled
void rgbled_print(const Rgbled *led)
{
    if (led == NULL)
    {
        printf("Rgbled: NULL\n");
        return;
    }

    // Читаем поля через побитовые операции
    // Формула: (Данные >> Сдвиг) & Маска
    unsigned int r = (led->data >> SHIFT_RED) & MASK_RED;
    unsigned int g = (led->data >> SHIFT_GREEN) & MASK_GREEN;
    unsigned int b = (led->data >> SHIFT_BLUE) & MASK_BLUE;
    unsigned int bright = (led->data >> SHIFT_BRIGHT) & MASK_BRIGHT;
    unsigned int temp = (led->data >> SHIFT_TEMP) & MASK_TEMP;
    unsigned int module = (led->data >> SHIFT_MODULE) & MASK_MODULE;
    unsigned int mode = (led->data >> SHIFT_MODE) & MASK_MODE;

    printf("RGB: R=%d, G=%d, B=%d\n", r, g, b);
    printf("Яркость: %d\n", bright);
    printf("Температура: %d K\n", temp);
    printf("Модуль: %d\n", module);
    printf("Режим: %d (0-свечение, 1-мерцание, 2-затухание)\n", mode);
}

// Методы для DeviceSystem (Обертка)

// Конструктор для обертки
DeviceSystem *system_create(int id, Rgbled *pixel)
{
    DeviceSystem *sys = (DeviceSystem *)malloc(sizeof(DeviceSystem));
    if (sys == NULL)
    {
        return NULL;
    }
    sys->id = id;
    sys->pixel = pixel; // Сохраняем указатель на rgbled
    return sys;
}

// Деструктор для системы отображения
void system_destroy(DeviceSystem *sys)
{
    if (sys != NULL)
    {
        rgbled_destroy(sys->pixel); // Сначала удаляем вложенный объект
        free(sys);                  // Потом удаляем саму обёртку
        sys = NULL;
    }
}
