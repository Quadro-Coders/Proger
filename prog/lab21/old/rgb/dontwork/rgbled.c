#include "rgbled.h"

void clear_input()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

// ============================================================================
// КОНСТРУКТОРЫ И ДЕСТРУКТОР RGBLED
// ============================================================================

rgbled *rgbled_create(void)
{
    rgbled *led = (rgbled *)malloc(sizeof(rgbled));
    if (!led)
    {
        printf("Ошибка выделения памяти!\n");
        return NULL;
    }
    led->data = 0;
    return led;
}

rgbled *rgbled_create_full(uint8_t r, uint8_t g, uint8_t b, uint8_t bright,
                           uint16_t temp, uint8_t module, uint8_t mode)
{
    rgbled *led = rgbled_create();
    if (!led)
        return NULL;

    // Побитовая сборка значения
    led->data |= ((uint64_t)(r & MASK_RED) << OFFSET_RED);
    led->data |= ((uint64_t)(g & MASK_GREEN) << OFFSET_GREEN);
    led->data |= ((uint64_t)(b & MASK_BLUE) << OFFSET_BLUE);
    led->data |= ((uint64_t)(bright & MASK_BRIGHT) << OFFSET_BRIGHT);
    led->data |= ((uint64_t)(temp & MASK_TEMP) << OFFSET_TEMP);
    led->data |= ((uint64_t)(module & MASK_MODULE) << OFFSET_MODULE);
    led->data |= ((uint64_t)(mode & MASK_MODE) << OFFSET_MODE);

    return led;
}

rgbled *rgbled_copy(const rgbled *src)
{
    if (!src)
        return NULL;
    rgbled *led = rgbled_create();
    if (led)
        led->data = src->data;
    return led;
}

void rgbled_destroy(rgbled *led)
{
    if (led)
        free(led);
}

// ============================================================================
// ФУНКЦИИ ДИНАМИЧЕСКОГО МАССИВА
// ============================================================================

rgbled_array *array_create(void)
{
    rgbled_array *arr = (rgbled_array *)malloc(sizeof(rgbled_array));
    if (!arr)
    {
        printf("Ошибка выделения памяти!\n");
        return NULL;
    }

    arr->capacity = INITIAL_ARRAY_SIZE;
    arr->count = 0;
    arr->leds = (rgbled **)malloc(arr->capacity * sizeof(rgbled *));

    if (!arr->leds)
    {
        free(arr);
        printf("Ошибка выделения памяти!\n");
        return NULL;
    }

    // Инициализируем все указатели NULL
    for (size_t i = 0; i < arr->capacity; i++)
    {
        arr->leds[i] = NULL;
    }

    return arr;
}

void array_destroy(rgbled_array *arr)
{
    if (!arr)
        return;

    // Уничтожаем все rgbled в массиве
    for (size_t i = 0; i < arr->count; i++)
    {
        if (arr->leds[i])
        {
            rgbled_destroy(arr->leds[i]);
            arr->leds[i] = NULL;
        }
    }

    // Освобождаем массив указателей
    free(arr->leds);
    free(arr);
}

// Увеличение вместимости массива
static int array_resize(rgbled_array *arr, size_t new_capacity)
{
    if (new_capacity <= arr->capacity)
        return 1; // Не нужно уменьшать

    rgbled **new_leds = (rgbled **)realloc(arr->leds, new_capacity * sizeof(rgbled *));
    if (!new_leds)
    {
        printf("Ошибка выделения памяти при расширении массива!\n");
        return 0;
    }

    arr->leds = new_leds;

    // Инициализируем новые элементы NULL
    for (size_t i = arr->capacity; i < new_capacity; i++)
    {
        arr->leds[i] = NULL;
    }

    arr->capacity = new_capacity;
    return 1;
}

int array_add(rgbled_array *arr, rgbled *led)
{
    if (!arr || !led)
        return 0;

    // Если массив заполнен, увеличиваем вместимость
    if (arr->count >= arr->capacity)
    {
        size_t new_capacity = arr->capacity * 2; // Увеличиваем в 2 раза
        if (!array_resize(arr, new_capacity))
            return 0;
    }

    arr->leds[arr->count] = led;
    arr->count++;
    return 1;
}

int array_remove(rgbled_array *arr, size_t index)
{
    if (!arr || index >= arr->count)
        return 0;

    // Уничтожаем rgbled
    rgbled_destroy(arr->leds[index]);

    // Сдвигаем элементы влево
    for (size_t i = index; i < arr->count - 1; i++)
    {
        arr->leds[i] = arr->leds[i + 1];
    }

    arr->leds[arr->count - 1] = NULL;
    arr->count--;

    // Если элементов стало мало, можно уменьшить вместимость (опционально)
    if (arr->count < arr->capacity / 4 && arr->capacity > INITIAL_ARRAY_SIZE)
    {
        size_t new_capacity = arr->capacity / 2;
        array_resize(arr, new_capacity);
    }

    return 1;
}

rgbled *array_get(rgbled_array *arr, size_t index)
{
    if (!arr || index >= arr->count)
        return NULL;
    return arr->leds[index];
}

size_t array_count(rgbled_array *arr)
{
    return arr ? arr->count : 0;
}

void array_print_all(rgbled_array *arr)
{
    if (!arr || arr->count == 0)
    {
        printf("Нет созданных RGB LED.\n");
        return;
    }

    printf("\n--- СПИСОК ВСЕХ RGB LED ---\n");
    printf("Всего: %zu\n", arr->count);
    printf("Вместимость: %zu\n", arr->capacity);

    for (size_t i = 0; i < arr->count; i++)
    {
        printf("\nRGB LED #%zu:\n", i + 1);
        rgbled_print(arr->leds[i]);
    }
}

// ============================================================================
// ГЕТТЕРЫ (Извлечение: (data >> offset) & mask)
// ============================================================================

uint8_t rgbled_get_red(const rgbled *led)
{
    return led ? (uint8_t)((led->data >> OFFSET_RED) & MASK_RED) : 0;
}

uint8_t rgbled_get_green(const rgbled *led)
{
    return led ? (uint8_t)((led->data >> OFFSET_GREEN) & MASK_GREEN) : 0;
}

uint8_t rgbled_get_blue(const rgbled *led)
{
    return led ? (uint8_t)((led->data >> OFFSET_BLUE) & MASK_BLUE) : 0;
}

uint8_t rgbled_get_brightness(const rgbled *led)
{
    return led ? (uint8_t)((led->data >> OFFSET_BRIGHT) & MASK_BRIGHT) : 0;
}

uint16_t rgbled_get_temp(const rgbled *led)
{
    return led ? (uint16_t)((led->data >> OFFSET_TEMP) & MASK_TEMP) : 0;
}

uint8_t rgbled_get_module(const rgbled *led)
{
    return led ? (uint8_t)((led->data >> OFFSET_MODULE) & MASK_MODULE) : 0;
}

uint8_t rgbled_get_mode(const rgbled *led)
{
    return led ? (uint8_t)((led->data >> OFFSET_MODE) & MASK_MODE) : 0;
}

// ============================================================================
// СЕТТЕРЫ (Установка: data = (data & ~mask) | (val << offset))
// ============================================================================

void rgbled_set_red(rgbled *led, uint8_t val)
{
    if (!led)
        return;
    led->data = (led->data & ~MASK_RED_SHIFT) | (((uint64_t)(val & MASK_RED)) << OFFSET_RED);
}

void rgbled_set_green(rgbled *led, uint8_t val)
{
    if (!led)
        return;
    led->data = (led->data & ~MASK_GREEN_SHIFT) | (((uint64_t)(val & MASK_GREEN)) << OFFSET_GREEN);
}

void rgbled_set_blue(rgbled *led, uint8_t val)
{
    if (!led)
        return;
    led->data = (led->data & ~MASK_BLUE_SHIFT) | (((uint64_t)(val & MASK_BLUE)) << OFFSET_BLUE);
}

void rgbled_set_brightness(rgbled *led, uint8_t val)
{
    if (!led)
        return;
    led->data = (led->data & ~MASK_BRIGHT_SHIFT) | (((uint64_t)(val & MASK_BRIGHT)) << OFFSET_BRIGHT);
}

void rgbled_set_temp(rgbled *led, uint16_t val)
{
    if (!led)
        return;
    led->data = (led->data & ~MASK_TEMP_SHIFT) | (((uint64_t)(val & MASK_TEMP)) << OFFSET_TEMP);
}

void rgbled_set_module(rgbled *led, uint8_t val)
{
    if (!led)
        return;
    led->data = (led->data & ~MASK_MODULE_SHIFT) | (((uint64_t)(val & MASK_MODULE)) << OFFSET_MODULE);
}

void rgbled_set_mode(rgbled *led, uint8_t val)
{
    if (!led)
        return;
    led->data = (led->data & ~MASK_MODE_SHIFT) | (((uint64_t)(val & MASK_MODE)) << OFFSET_MODE);
}

// ============================================================================
// ДОПОЛНИТЕЛЬНЫЕ МЕТОДЫ
// ============================================================================

void rgbled_print(const rgbled *led)
{
    if (!led)
    {
        printf("[NULL rgbled]\n");
        return;
    }

    const char *mode_str = "Неизв.";
    switch (rgbled_get_mode(led))
    {
    case MODE_GLOWING:
        mode_str = "Свечение";
        break;
    case MODE_FLICKERING:
        mode_str = "Мерцание";
        break;
    case MODE_FADING:
        mode_str = "Затухание";
        break;
    }

    printf("  Цвет: #%02X%02X%02X (R:%3d G:%3d B:%3d)\n",
           rgbled_get_red(led), rgbled_get_green(led), rgbled_get_blue(led),
           rgbled_get_red(led), rgbled_get_green(led), rgbled_get_blue(led));
    printf("  Яркость: %3d\n", rgbled_get_brightness(led));
    printf("  Температура: %5d K\n", rgbled_get_temp(led));
    printf("  Модуль: %2d\n", rgbled_get_module(led));
    printf("  Режим: %2d (%s)\n", rgbled_get_mode(led), mode_str);
    printf("  RAW (hex): 0x%016llX\n", (unsigned long long)led->data);
}

void rgbled_fill_random(rgbled *led)
{
    if (!led)
        return;
    static int seeded = 0;
    if (!seeded)
    {
        srand((unsigned int)time(NULL));
        seeded = 1;
    }

    rgbled_set_red(led, rand() % 256);
    rgbled_set_green(led, rand() % 256);
    rgbled_set_blue(led, rand() % 256);
    rgbled_set_brightness(led, rand() % 256);
    rgbled_set_temp(led, 2000 + (rand() % 6000));
    rgbled_set_module(led, rand() % 16);
    rgbled_set_mode(led, rand() % 3);
}

int rgbled_eq(const rgbled *l1, const rgbled *l2)
{
    if (!l1 || !l2)
        return 0;
    return (l1->data == l2->data) ? 1 : 0;
}

// ============================================================================
// ФУНКЦИИ МЕНЮ
// ============================================================================

void menu_create_rgbled(rgbled_array *arr)
{
    if (!arr)
    {
        printf("Ошибка: массив не создан!\n");
        return;
    }

    int choice;
    printf("\n1. Пустой\n2. Случайный\n3. Ввод значений\nВыбор: ");
    if (scanf("%d", &choice) != 1)
    {
        clear_input();
        return;
    }
    clear_input();

    rgbled *led = NULL;

    if (choice == 3)
    {
        uint8_t r, g, b, br, mod, mode;
        uint16_t temp;
        printf("Red (0-255): ");
        scanf("%hhu", &r);
        printf("Green (0-255): ");
        scanf("%hhu", &g);
        printf("Blue (0-255): ");
        scanf("%hhu", &b);
        printf("Brightness (0-255): ");
        scanf("%hhu", &br);
        printf("Temp (K): ");
        scanf("%hu", &temp);
        printf("Module (0-15): ");
        scanf("%hhu", &mod);
        printf("Mode (0-2): ");
        scanf("%hhu", &mode);
        clear_input();
        led = rgbled_create_full(r, g, b, br, temp, mod, mode);
    }
    else if (choice == 2)
    {
        led = rgbled_create();
        if (led)
            rgbled_fill_random(led);
    }
    else
    {
        led = rgbled_create();
    }

    if (led)
    {
        if (array_add(arr, led))
        {
            printf("RGB LED создан успешно (всего: %zu)!\n", arr->count);
            rgbled_print(led);
        }
        else
        {
            rgbled_destroy(led);
            printf("Ошибка добавления в массив!\n");
        }
    }
    else
    {
        printf("Ошибка создания RGB LED!\n");
    }
}

void menu_print_all(rgbled_array *arr)
{
    array_print_all(arr);
}

void menu_edit_rgbled(rgbled_array *arr)
{
    if (!arr || arr->count == 0)
    {
        printf("Нет созданных RGB LED!\n");
        return;
    }

    size_t idx;
    printf("Номер RGB LED (1-%zu): ", arr->count);
    if (scanf("%zu", &idx) != 1)
    {
        clear_input();
        return;
    }
    clear_input();

    if (idx < 1 || idx > arr->count)
    {
        printf("Неверный номер!\n");
        return;
    }
    idx--; // 0-индексация

    rgbled *led = array_get(arr, idx);
    if (!led)
        return;

    int field, val;
    printf("\n1.Red 2.Green 3.Blue 4.Bright 5.Temp 6.Module 7.Mode\nВыбор поля: ");
    if (scanf("%d", &field) != 1)
    {
        clear_input();
        return;
    }
    printf("Значение: ");
    if (scanf("%d", &val) != 1)
    {
        clear_input();
        return;
    }
    clear_input();

    switch (field)
    {
    case 1:
        rgbled_set_red(led, (uint8_t)val);
        break;
    case 2:
        rgbled_set_green(led, (uint8_t)val);
        break;
    case 3:
        rgbled_set_blue(led, (uint8_t)val);
        break;
    case 4:
        rgbled_set_brightness(led, (uint8_t)val);
        break;
    case 5:
        rgbled_set_temp(led, (uint16_t)val);
        break;
    case 6:
        rgbled_set_module(led, (uint8_t)val);
        break;
    case 7:
        rgbled_set_mode(led, (uint8_t)val);
        break;
    default:
        printf("Неверное поле.\n");
        return;
    }
    printf("Обновлено.\n");
    rgbled_print(led);
}

void menu_compare_rgbled(rgbled_array *arr)
{
    if (!arr || arr->count < 2)
    {
        printf("Нужно минимум 2 RGB LED для сравнения!\n");
        return;
    }

    size_t i1, i2;
    printf("Номера двух RGB LED (1-%zu): ", arr->count);
    if (scanf("%zu %zu", &i1, &i2) != 2)
    {
        clear_input();
        return;
    }
    clear_input();

    if (i1 < 1 || i1 > arr->count || i2 < 1 || i2 > arr->count)
    {
        printf("Неверные номера!\n");
        return;
    }

    rgbled *l1 = array_get(arr, i1 - 1);
    rgbled *l2 = array_get(arr, i2 - 1);

    if (!l1 || !l2)
        return;

    printf("\nСравнение:\n");
    printf("LED #%zu:\n", i1);
    rgbled_print(l1);
    printf("LED #%zu:\n", i2);
    rgbled_print(l2);
    printf("Результат: %s\n", rgbled_eq(l1, l2) ? "РАВНЫ" : "НЕ РАВНЫ");
}

void menu_remove_rgbled(rgbled_array *arr)
{
    if (!arr || arr->count == 0)
    {
        printf("Нет созданных RGB LED!\n");
        return;
    }

    size_t idx;
    printf("Номер RGB LED для удаления (1-%zu): ", arr->count);
    if (scanf("%zu", &idx) != 1)
    {
        clear_input();
        return;
    }
    clear_input();

    if (idx < 1 || idx > arr->count)
    {
        printf("Неверный номер!\n");
        return;
    }

    if (array_remove(arr, idx - 1))
    {
        printf("RGB LED #%zu удалён (осталось: %zu).\n", idx, arr->count);
    }
    else
    {
        printf("Ошибка удаления!\n");
    }
}

void menu_destroy_all(rgbled_array *arr)
{
    if (!arr || arr->count == 0)
    {
        printf("Нет созданных RGB LED!\n");
        return;
    }

    printf("Уничтожение всех %zu RGB LED...\n", arr->count);

    // Уничтожаем все элементы
    for (size_t i = 0; i < arr->count; i++)
    {
        if (arr->leds[i])
        {
            rgbled_destroy(arr->leds[i]);
            arr->leds[i] = NULL;
        }
    }

    arr->count = 0;

    // Сбрасываем вместимость до начальной
    array_resize(arr, INITIAL_ARRAY_SIZE);

    printf("Все RGB LED уничтожены.\n");
}
