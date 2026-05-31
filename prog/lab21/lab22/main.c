#include "bitrgbled.h"

int main()
{
    int id;
    unsigned int red, green, blue, brightness, temperature, module, mode;

    printf("Практическая работа №2: Вариант 2 (rgbled)\n");
    printf("Введите данные для LED пикселя:\n");
    printf("Формат: id красный зелёный синий яркость температура модуль режим(0-свечение, 1-мерцание, 2-затухание)\n");
    printf("Пример: 1 255 255 255 15 10000 3 2\n");
    printf("> ");

    // Читаем из входного потока
    if (scanf("%d %u %u %u %u %u %u %u", &id, &red, &green, &blue, &brightness, &temperature, &module, &mode) != 8)
    {
        printf("Ошибка ввода! Требуется 8 значений.\n");
        return 1;
    }

    // Создаём rgbled через конструктор (побитовая арифметика)
    Rgbled *led = rgbled_create(red, green, blue, brightness, temperature, module, mode);
    if (led == NULL)
    {
        printf("Ошибка: не удалось создать LED!\n");
        return 1;
    }

    // Создаем образец через конструктор
    DeviceSystem *system = system_create(id, led);
    if (system == NULL)
    {
        printf("Ошибка: не удалось создать систему!\n");
        rgbled_destroy(led);
        return 1;
    }

    printf("\nИнформация о структуре (побитовая арифметика)\n");
    printf("ID системы: %d\n", system->id);
    printf("\nДанные LED:\n");
    rgbled_print(system->pixel);

    // Сравнение затрат памяти
    printf("\nВлияние выравнивания и затраты памяти\n");
    printf("1) Побитовые поля без выравнивания (pragma pack): %lu байт\n", sizeof(RgbledFieldsPacked));
    printf("2) Побитовые поля с выравниванием (обычно): %lu байт\n", sizeof(RgbledFields));
    printf("3) Побитовая арифметика (unsigned long long): %lu байт\n", sizeof(Rgbled));
    printf("4) Обычная структура (7 * unsigned int): ~%lu байт\n", 7 * sizeof(unsigned int));

    // Удаление структуры
    system_destroy(system); // Деструктор удалит system и led

    printf("\nРабота завершена успешно.\n");
    return 0;
}
