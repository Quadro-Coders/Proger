#include "list.h"

void print_menu()
{
    printf("\nМЕНЮ\n");
    printf("1. Добавить элемент(ы) в начало\n");
    printf("2. Добавить элемент(ы) в конец\n");
    printf("3. Удалить элемент по ключу\n");
    printf("4. Найти элемент по ключу\n");
    printf("5. Вывести список\n");
    printf("6. Загрузить элементы из потока (stdin)\n");
    printf("7. Очистить список\n");
    printf("8. Запустить эксперимент (Таблица 1)\n");
    printf("0. Выход\n");
    printf("Выбор: ");
}

void run_experiment()
{
    printf("\n--- Экспериментальное исследование ---\n");
    printf("Генерация данных и измерение времени...\n");
    printf("Пожалуйста, подождите...\n\n");

    printf("| #  | Элементов | Add Tail (мс) | Lookup (мс) |\n");
    printf("|----|-----------|---------------|-------------|\n");

    int counts[] = {50000, 100000, 150000, 200000, 250000, 300000, 350000, 400000, 450000, 500000};
    int num_tests = sizeof(counts) / sizeof(counts[0]);

    /* Инициализация генератора случайных чисел */
    srand(42); /* Фиксированный seed для воспроизводимости */

    /* Файл для построения графиков (gnuplot) */
    FILE *plot_file = fopen("results.dat", "w");
    if (plot_file)
    {
        fprintf(plot_file, "# Элементов\tAddTail_ms\tLookup_ms\n");
    }

    for (int i = 0; i < num_tests; i++)
    {
        int n = counts[i];
        struct list_head test_list;
        init_list_head(&test_list);

        /* === Подготовка данных (не входит в замер) === */
        int *keys = (int *)malloc(n * sizeof(int));
        double *values = (double *)malloc(n * sizeof(double));
        if (!keys || !values)
        {
            fprintf(stderr, "Ошибка выделения памяти для эксперимента\n");
            return;
        }
        for (int j = 0; j < n; j++)
        {
            keys[j] = getrand(1, 1000000);
            values[j] = (double)getrand(0, 10000) / 100.0;
        }

        /* === Измерение list_add_tail === */
        double start = wtime();
        for (int j = 0; j < n; j++)
        {
            data_add_tail(&test_list, keys[j], values[j]);
        }
        double end = wtime();
        double add_time = (end - start) * 1000.0; /* перевод в мс */

        /* === Измерение list_lookup === */
        /* Для экономии времени делаем N/100 поисков, затем масштабируем результат */
        int lookup_count = n / 100;
        if (lookup_count < 1)
            lookup_count = 1;

        start = wtime();
        for (int j = 0; j < lookup_count; j++)
        {
            int idx = getrand(0, n);
            /* Ищем элемент, который точно есть в списке */
            data_lookup(&test_list, keys[idx]);
        }
        end = wtime();
        double lookup_time = (end - start) * 1000.0;

        /* Масштабируем время lookup до эквивалента N поисков для таблицы */
        lookup_time = lookup_time * n / lookup_count;

        printf("| %2d | %7d   | %13.2f | %11.2f |\n", i + 1, n, add_time, lookup_time);

        /* Запись в файл для графиков */
        if (plot_file)
        {
            fprintf(plot_file, "%d\t%.2f\t%.2f\n", n, add_time, lookup_time);
        }

        /* Очистка памяти */
        list_clear(&test_list);
        free(keys);
        free(values);
    }

    if (plot_file)
    {
        fclose(plot_file);
        printf("\nРезультаты сохранены в 'results.dat' для gnuplot.\n");
    }

    printf("\nЭксперимент завершён.\n");
    printf("Примечание: Add Tail - O(1) на операцию, Lookup - O(N) на операцию.\n");
}

int main()
{
    struct list_head main_list;
    init_list_head(&main_list);
    int choice;
    int count, i;
    int key;
    double value;

    while (1)
    {
        print_menu();
        if (scanf("%d", &choice) != 1)
        {
            printf("Неверный ввод. Введите число.\n");
            while (getchar() != '\n')
                ; /* Очистка буфера */
            continue;
        }

        switch (choice)
        {
        case 1: /* Добавить в начало */
        case 2: /* Добавить в конец */
            printf("Сколько элементов добавить? ");
            if (scanf("%d", &count) != 1 || count <= 0)
            {
                printf("Неверное количество.\n");
                break;
            }
            printf("Введите %d пар (ключ значение):\n", count);
            for (i = 0; i < count; i++)
            {
                if (scanf("%d %lf", &key, &value) != 2)
                {
                    printf("Неверный ввод. Остановка добавления.\n");
                    break;
                }
                if (choice == 1)
                    data_add_front(&main_list, key, value);
                else
                    data_add_tail(&main_list, key, value);
            }
            printf("Готово. Добавлено %d элемент(ов).\n", i);
            break;

        case 3: /* Удалить */
            printf("Введите ключ для удаления: ");
            if (scanf("%d", &key) == 1)
                data_delete(&main_list, key);
            break;

        case 4: /* Найти */
            printf("Введите ключ для поиска: ");
            if (scanf("%d", &key) == 1)
            {
                double res = data_lookup(&main_list, key);
                if (res != -1.0)
                    printf("Найдено значение: %.2f\n", res);
                else
                    printf("Элемент с ключом %d не найден.\n", key);
            }
            break;

        case 5: /* Вывести */
            list_print(&main_list);
            break;

        case 6: /* Загрузить из потока */
            printf("Введите данные в формате 'ключ значение' (Ctrl+D для завершения):\n");
            list_add_from_stdin(&main_list);
            break;

        case 7: /* Очистить */
            list_clear(&main_list);
            break;

        case 8: /* Эксперимент */
            run_experiment();
            break;

        case 0: /* Выход */
            list_clear(&main_list);
            printf("Выход из программы...\n");
            return 0;

        default:
            printf("Неверный выбор. Попробуйте снова.\n");
        }
    }
    return 0;
}
