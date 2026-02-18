#include "matrix2d.h"

int main()
{
    matrix2d *matrix_a = NULL;
    matrix2d *matrix_b = NULL;
    char choice;

    printf("ПРАКТИЧЕСКАЯ РАБОТА №1 (Вариант 2)\n");
    printf("Структура: Двумерная матрица (matrix2d)\n");

    do
    {
        printf("\nМЕНЮ:\n");
        printf("a. Создать матрицу A\n");
        printf("b. Вывести матрицу A\n");
        printf("c. Заполнить A случайными значениями\n");
        printf("d. Изменить элемент матрицы A\n");
        printf("e. Инкремент матрицы A (++)\n");
        printf("f. Декремент матрицы A (--)\n");
        printf("g. Получить строку матрицы A\n");
        printf("h. Получить столбец матрицы A\n");
        printf("i. Транспонировать матрицу A\n");
        printf("j. Определитель матрицы A\n");
        printf("k. Обратная матрица для A\n");
        printf("l. Создать матрицу B\n");
        printf("m. Сравнить матрицы A и B\n");
        printf("n. Уничтожить матрицу A\n");
        printf("o. Уничтожить матрицу B\n");
        printf("q. Выход\n");

        printf("Состояние: A=%s B=%s\n",
               is_matrix_created(matrix_a) ? "создана" : "не создана",
               is_matrix_created(matrix_b) ? "создана" : "не создана");

        printf("Выберите действие: ");
        if (scanf(" %c", &choice) == EOF)
        {
            printf("\nОбнаружен конец ввода (EOF). Завершение программы...\n");
            printf("До свидания!\n");
            return 0;
        }
        clear();

        switch (choice)
        {
        case 'a':
            menu_create_matrix(&matrix_a);
            break;
        case 'b':            menu_print_matrix(matrix_a);
            break;
        case 'c':
            menu_fill_random(matrix_a);
            break;
        case 'd':
            menu_set_element(matrix_a);
            break;
        case 'e':
            menu_increment(matrix_a);
            break;
        case 'f':
            menu_decrement(matrix_a);
            break;
        case 'g':
            menu_get_row(matrix_a);
            break;
        case 'h':
            menu_get_col(matrix_a);
            break;
        case 'i':
            menu_transpose(&matrix_a);
            break;
        case 'j':
            menu_determinant(matrix_a);
            break;
        case 'k':
            menu_inverse(matrix_a);
            break;
        case 'l':
            menu_create_matrix(&matrix_b);
            break;
        case 'm':
            menu_compare(matrix_a, matrix_b);
            break;
        case 'n':
            menu_destroy(&matrix_a);
            break;
        case 'o':
            menu_destroy(&matrix_b);
            break;
        case 'q':
            printf("До свидания!\n");
            break;
        default:
            printf("Неверный выбор!\n");
        }

        if (choice != 'q')
        {            printf("\nНажмите Enter для продолжения...");
            getchar();
        }

    } while (choice != 'q');

    return 0;
}