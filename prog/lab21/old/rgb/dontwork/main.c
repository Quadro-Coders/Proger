#include "rgbled.h"

int main()
{
    rgbled_array *arr = NULL;
    char choice;

    printf("=================================================================\n");
    printf("ПРАКТИЧЕСКАЯ РАБОТА №1 (Вариант 2)\n");
    printf("Структура: RGB LED Pixel (Побитовая арифметика)\n");
    printf("Динамический массив - без ограничения количества!\n");
    printf("=================================================================\n");

    // Создаём динамический массив
    arr = array_create();
    if (!arr)
    {
        printf("Ошибка создания массива! Завершение программы.\n");
        return 1;
    }

    do
    {
        printf("\n--- ГЛАВНОЕ МЕНЮ ---\n");
        printf("1. Создать новый RGB LED\n");
        printf("2. Показать все RGB LED\n");
        printf("3. Редактировать RGB LED\n");
        printf("4. Сравнить два RGB LED\n");
        printf("5. Удалить RGB LED\n");
        printf("6. Удалить все RGB LED\n");
        printf("7. Информация о структуре (выравнивание)\n");
        printf("0. Выход\n");
        printf("Текущее количество: %zu (без ограничений)\n", array_count(arr));
        printf("Выбор: ");

        if (scanf(" %c", &choice) == EOF)
        {
            printf("\nЗавершение программы...\n");
            break;
        }
        clear_input();

        switch (choice)
        {
        case '1':
            menu_create_rgbled(arr);
            break;

        case '2':
            menu_print_all(arr);
            break;

        case '3':
            menu_edit_rgbled(arr);
            break;

        case '4':
            menu_compare_rgbled(arr);
            break;

        case '5':
            menu_remove_rgbled(arr);
            break;

        case '6':
            menu_destroy_all(arr);
            break;

        case '7':
            printf("\n--- ИНФОРМАЦИЯ О СТРУКТУРЕ ---\n");
            printf("Размер rgbled: %zu байт\n", sizeof(rgbled));
            printf("Размер uint64_t: %zu байт\n", sizeof(uint64_t));
            printf("\nРаспределение битов (60 из 64 используются):\n");
            printf("  [07:00]   Красный      - смещение %d\n", OFFSET_RED);
            printf("  [15:08]   Зелёный      - смещение %d\n", OFFSET_GREEN);
            printf("  [23:16]   Синий        - смещение %d\n", OFFSET_BLUE);
            printf("  [31:24]   Яркость      - смещение %d\n", OFFSET_BRIGHT);
            printf("  [47:32]   Температура  - смещение %d\n", OFFSET_TEMP);
            printf("  [51:48]   Тип модуля   - смещение %d\n", OFFSET_MODULE);
            printf("  [54:52]   Режим работы - смещение %d\n", OFFSET_MODE);
            printf("  [63:55]   Резерв       - 9 бит\n");
            printf("\nЭффективность: %.1f%%\n", 60.0 / 64.0 * 100);
            printf("\nДинамический массив:\n");
            printf("  Начальная вместимость: %d\n", INITIAL_ARRAY_SIZE);
            printf("  Стратегия: удвоение при заполнении\n");
            printf("  Автоматическое сжатие при <25%% заполнения\n");
            break;

        case '0':
            printf("До свидания!\n");
            break;

        default:
            printf("Неверный выбор!\n");
        }

        if (choice != '0')
        {
            printf("\nНажмите Enter для продолжения...");
            getchar();
        }
    } while (choice != '0');

    // Освобождаем память
    if (arr)
    {
        array_destroy(arr);
    }

    return 0;
}
