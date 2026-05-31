#include "matrix2d.h"

int main()
{
    matrix2d *matrices[MAX_MATRICES] = {NULL};
    int matrix_count = 0;
    char choice;

    printf("ПРАКТИЧЕСКАЯ РАБОТА №1 (Вариант 2)\n");
    printf("Структура: Двумерная матрица (matrix2d)\n");

    do
    {
        printf("\nМЕНЮ:\n");
        printf("1. Создать новую матрицу\n");
        printf("2. Показать все матрицы\n");
        printf("3. Выбрать матрицу для операций\n");
        printf("4. Сравнить две матрицы\n");
        printf("5. Уничтожить матрицу\n");
        printf("6. Уничтожить все матрицы\n");
        printf("0. Выход\n");

        printf("Текущее количество матриц: %d/%d\n", matrix_count, MAX_MATRICES);

        printf("Выберите действие: ");
        if (scanf(" %c", &choice) == EOF)
        {
            printf("\nОбнаружен конец ввода (EOF). Завершение программы...\n");
            printf("До свидания!\n");

            // Освобождаем всю память
            for (int i = 0; i < MAX_MATRICES; i++)
            {
                if (matrices[i])
                {
                    menu_destroy(&matrices[i]);
                }
            }
            return 0;
        }
        clear();

        switch (choice)
        {
        case '1':
            if (matrix_count >= MAX_MATRICES)
            {
                printf("Достигнуто максимальное количество матриц (%d)!\n", MAX_MATRICES);
                break;
            }

            // Находим первый свободный слот
            int free_index = -1;
            for (int i = 0; i < MAX_MATRICES; i++)
            {
                if (matrices[i] == NULL)
                {
                    free_index = i;
                    break;
                }
            }

            if (free_index != -1)
            {
                printf("\nСоздание матрицы с индексом %d:\n", free_index + 1);
                menu_create_matrix(&matrices[free_index]);
                if (matrices[free_index])
                {
                    matrix_count++;
                    printf("Матрица %d создана успешно!\n", free_index + 1);
                }
            }
            break;

        case '2':
            printf("\n--- СПИСОК ВСЕХ МАТРИЦ ---\n");
            int found = 0;
            for (int i = 0; i < MAX_MATRICES; i++)
            {
                if (matrices[i])
                {
                    found = 1;
                    printf("\nМатрица %d:\n", i + 1);
                    matrix2d_print(matrices[i]);
                }
            }
            if (!found)
            {
                printf("Нет созданных матриц.\n");
            }
            break;

        case '3':
            if (matrix_count == 0)
            {
                printf("Нет созданных матриц!\n");
                break;
            }

            printf("\n--- ВЫБОР МАТРИЦЫ ДЛЯ ОПЕРАЦИЙ ---\n");
            printf("Доступные матрицы: ");
            for (int i = 0; i < MAX_MATRICES; i++)
            {
                if (matrices[i])
                {
                    printf("%d ", i + 1);
                }
            }
            printf("\n");

            int matrix_index;
            printf("Введите номер матрицы: ");
            if (scanf("%d", &matrix_index) != 1)
            {
                printf("Ошибка ввода!\n");
                clear();
                break;
            }
            clear();

            if (matrix_index < 1 || matrix_index > MAX_MATRICES || matrices[matrix_index - 1] == NULL)
            {
                printf("Неверный номер матрицы!\n");
                break;
            }

            matrix_index--; // Переводим в 0-индексацию

            // Подменю для выбранной матрицы
            char sub_choice;
            do
            {
                printf("\n--- ОПЕРАЦИИ С МАТРИЦЕЙ %d ---\n", matrix_index + 1);
                printf("a. Вывести матрицу\n");
                printf("b. Заполнить случайными значениями\n");
                printf("c. Изменить элемент матрицы\n");
                printf("d. Инкремент матрицы (++)\n");
                printf("e. Декремент матрицы (--)\n");
                printf("f. Получить строку матрицы\n");
                printf("g. Получить столбец матрицы\n");
                printf("h. Транспонировать матрицу\n");
                printf("i. Определитель матрицы (если квадратная)\n");
                printf("j. Обратная матрица (если квадратная)\n");
                printf("r. Вернуться в главное меню\n");

                printf("Выберите операцию: ");
                if (scanf(" %c", &sub_choice) == EOF)
                {
                    sub_choice = 'r';
                }
                clear();

                switch (sub_choice)
                {
                case 'a':
                    menu_print_matrix(matrices[matrix_index]);
                    break;
                case 'b':
                    menu_fill_random(matrices[matrix_index]);
                    break;
                case 'c':
                    menu_set_element(matrices[matrix_index]);
                    break;
                case 'd':
                    menu_increment(matrices[matrix_index]);
                    break;
                case 'e':
                    menu_decrement(matrices[matrix_index]);
                    break;
                case 'f':
                    menu_get_row(matrices[matrix_index]);
                    break;
                case 'g':
                    menu_get_col(matrices[matrix_index]);
                    break;
                case 'h':
                    menu_transpose(&matrices[matrix_index]);
                    break;
                case 'i':
                    menu_determinant(matrices[matrix_index]);
                    break;
                case 'j':
                    menu_inverse(matrices[matrix_index]);
                    break;
                case 'r':
                    printf("Возврат в главное меню...\n");
                    break;
                default:
                    printf("Неверный выбор!\n");
                }

                if (sub_choice != 'r')
                {
                    printf("\nНажмите Enter для продолжения...");
                    getchar();
                }

            } while (sub_choice != 'r');
            break;

        case '4':
            if (matrix_count < 2)
            {
                printf("Недостаточно матриц для сравнения! Создайте хотя бы 2 матрицы.\n");
                break;
            }

            printf("\n--- СРАВНЕНИЕ ДВУХ МАТРИЦ ---\n");
            printf("Доступные матрицы: ");
            for (int i = 0; i < MAX_MATRICES; i++)
            {
                if (matrices[i])
                {
                    printf("%d ", i + 1);
                }
            }
            printf("\n");

            int m1_idx, m2_idx;
            printf("Введите номер первой матрицы: ");
            if (scanf("%d", &m1_idx) != 1)
            {
                printf("Ошибка ввода!\n");
                clear();
                break;
            }
            clear();

            printf("Введите номер второй матрицы: ");
            if (scanf("%d", &m2_idx) != 1)
            {
                printf("Ошибка ввода!\n");
                clear();
                break;
            }
            clear();

            if (m1_idx < 1 || m1_idx > MAX_MATRICES || matrices[m1_idx - 1] == NULL)
            {
                printf("Неверный номер первой матрицы!\n");
                break;
            }
            if (m2_idx < 1 || m2_idx > MAX_MATRICES || matrices[m2_idx - 1] == NULL)
            {
                printf("Неверный номер второй матрицы!\n");
                break;
            }

            menu_compare(matrices[m1_idx - 1], matrices[m2_idx - 1]);
            break;

        case '5':
            if (matrix_count == 0)
            {
                printf("Нет созданных матриц!\n");
                break;
            }

            printf("\n--- УНИЧТОЖЕНИЕ МАТРИЦЫ ---\n");
            printf("Доступные матрицы: ");
            for (int i = 0; i < MAX_MATRICES; i++)
            {
                if (matrices[i])
                {
                    printf("%d ", i + 1);
                }
            }
            printf("\n");

            int del_idx;
            printf("Введите номер матрицы для уничтожения: ");
            if (scanf("%d", &del_idx) != 1)
            {
                printf("Ошибка ввода!\n");
                clear();
                break;
            }
            clear();

            if (del_idx < 1 || del_idx > MAX_MATRICES || matrices[del_idx - 1] == NULL)
            {
                printf("Неверный номер матрицы!\n");
                break;
            }

            menu_destroy(&matrices[del_idx - 1]);
            matrix_count--;
            printf("Матрица %d уничтожена.\n", del_idx);
            break;

        case '6':
            if (matrix_count == 0)
            {
                printf("Нет созданных матриц!\n");
                break;
            }

            printf("Уничтожение всех %d матриц...\n", matrix_count);
            for (int i = 0; i < MAX_MATRICES; i++)
            {
                if (matrices[i])
                {
                    menu_destroy(&matrices[i]);
                }
            }
            matrix_count = 0;
            printf("Все матрицы уничтожены.\n");
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

    return 0;
}
