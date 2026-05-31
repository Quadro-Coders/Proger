#include "bitrgbled.h"

// ========== КОНСТРУКТОР И ДЕСТРУКТОР ==========

rgbled *led_create(unsigned int r, unsigned int g, unsigned int b,
                   unsigned int bright, unsigned int temp,
                   unsigned int ctrl, led_mode m)
{
    rgbled *led = (rgbled *)malloc(sizeof(rgbled));
    if (!led)
        return NULL;

    led_set_all(led, r, g, b, bright, temp, ctrl, m);
    return led;
}

void led_free(rgbled *led)
{
    if (led)
        free(led);
}

// ========== СЕТТЕРЫ (MASK вместо "магических чисел"!) ==========

void led_set_red(rgbled *led, unsigned int value)
{
    if (led && value <= MASK_RED) // Вместо 255 используем MASK_RED
        led->red = value;         // Прямая запись в битовое поле
}

void led_set_green(rgbled *led, unsigned int value)
{
    if (led && value <= MASK_GREEN)
        led->green = value;
}

void led_set_blue(rgbled *led, unsigned int value)
{
    if (led && value <= MASK_BLUE)
        led->blue = value;
}

void led_set_brightness(rgbled *led, unsigned int value)
{
    if (led && value <= MASK_BRIGHT)
        led->bright = value;
}

void led_set_temperature(rgbled *led, unsigned int value)
{
    if (led && value <= MASK_TEMP)
        led->temp = value;
}

void led_set_module(rgbled *led, unsigned int value)
{
    if (led && value <= MASK_MODULE)
        led->module = value;
}

void led_set_mode(rgbled *led, led_mode mode)
{
    if (led && mode <= MASK_MODE) // mode — enum, но проверяем через MASK_MODE
        led->mode = mode;
}

// ========== ГЕТТЕРЫ ==========

unsigned int led_get_red(const rgbled *led)
{
    return led ? led->red : 0;
}

unsigned int led_get_green(const rgbled *led)
{
    return led ? led->green : 0;
}

unsigned int led_get_blue(const rgbled *led)
{
    return led ? led->blue : 0;
}

unsigned int led_get_brightness(const rgbled *led)
{
    return led ? led->bright : 0;
}

unsigned int led_get_temperature(const rgbled *led)
{
    return led ? led->temp : 0;
}

unsigned int led_get_module(const rgbled *led)
{
    return led ? led->module : 0;
}

unsigned int led_get_mode(const rgbled *led)
{
    return led ? led->mode : 0;
}

// ========== УСТАНОВИТЬ ВСЕ ЗНАЧЕНИЯ ==========

void led_set_all(rgbled *led, unsigned int r, unsigned int g, unsigned int b,
                 unsigned int bright, unsigned int temp,
                 unsigned int ctrl, led_mode m)
{
    if (!led)
        return;

    led_set_red(led, r);
    led_set_green(led, g);
    led_set_blue(led, b);
    led_set_brightness(led, bright);
    led_set_temperature(led, temp);
    led_set_module(led, ctrl);
    led_set_mode(led, m);
}

// ========== ВЫВОД ==========

void led_print(const rgbled *led)
{
    if (!led)
    {
        printf("rgbled: NULL\n");
        return;
    }

    printf("Настройки данного LED:\n");
    printf("Цвет: R=%3u, G=%3u, B=%3u\n", led->red, led->green, led->blue);
    printf("Яркость: %3u%%\n", led->bright);
    printf("Температура цвета: %5u K\n", led->temp);
    printf("Тип модуля управления: %u\n", led->module);
    printf("Режим работы: ");

    switch (led->mode)
    {
    case MODE_GLOW:
        printf("Свечение\n");
        break;
    case MODE_BLINK:
        printf("Мерцание\n");
        break;
    case MODE_FADING:
        printf("Затухание\n");
        break;
    default:
        printf("Неизвестный\n");
        break;
    }
}

// ========== DEVICE SYSTEM ==========

DeviceSystem *system_create(int id, rgbled *pixel)
{
    DeviceSystem *sys = (DeviceSystem *)malloc(sizeof(DeviceSystem));
    if (!sys)
        return NULL;

    sys->id = id;
    sys->pixel = pixel;
    return sys;
}

void system_destroy(DeviceSystem *sys)
{
    if (sys)
    {
        led_free(sys->pixel);
        free(sys);
    }
}

// ========== ВЫРАВНИВАНИЕ ==========

void led_show_alignment(void)
{
    printf("Размер RgbledFields (авто-выравнивание): %zu байт\n", sizeof(RgbledFields));
    printf("Размер RgbledFieldsPacked (packed): %zu байт\n", sizeof(RgbledFieldsPacked));
    printf("Размер rgbled (основная): %zu байт\n", sizeof(rgbled));
}
