#include "matrix2d.h"

// Главное меню программы
int main()
{
    matrix2d *matrix_a = NULL;  // матрица A
    matrix2d *matrix_b = NULL;  // матрица B
    char choice;

    printf("ПРАКТИЧЕСКАЯ РАБОТА №1\n");
    printf("Двумерная матрица (matrix2d)\n");

    do
    {
        // Меню
        printf("\nМЕНЮ:\n");
        printf("a. Создать матрицу A\n");
        printf("b. Вывести матрицу A\n");
        printf("c. Заполнить A случайно\n");
        printf("d. Изменить элемент A\n");
        printf("e. Инкремент A (++)\n");
        printf("f. Декремент A (--)\n");
        printf("g. Получить строку A\n");
        printf("h. Получить столбец A\n");
        printf("i. Транспонировать A\n");
        printf("j. Определитель A\n");
        printf("k. Обратная матрица для A\n");
        printf("l. Создать матрицу B\n");
        printf("m. Сравнить A и B\n");
        printf("n. Уничтожить A\n");
        printf("o. Уничтожить B\n");
        printf("q. Выход\n");

        // Статус матриц
        printf("Статус: A=%s B=%s\n",
               matrix_a ? "создана" : "нет",
               matrix_b ? "создана" : "нет");

        printf("Выбор: ");
        if (scanf(" %c", &choice) == EOF)  // Ctrl+D / Ctrl+Z
        {
            printf("Выход\n");
            if (matrix_a) menu_destroy(&matrix_a);
            if (matrix_b) menu_destroy(&matrix_b);
            return 0;
        }
        clear_input();

        // Обработка команд
        switch (choice)
        {
        case 'a': menu_create_matrix(&matrix_a); break;
        case 'b': menu_print_matrix(matrix_a); break;
        case 'c': menu_fill_random(matrix_a); break;
        case 'd': menu_set_element(matrix_a); break;
        case 'e': menu_increment(matrix_a); break;
        case 'f': menu_decrement(matrix_a); break;
        case 'g': menu_get_row(matrix_a); break;
        case 'h': menu_get_col(matrix_a); break;
        case 'i': menu_transpose(&matrix_a); break;
        case 'j': menu_determinant(matrix_a); break;
        case 'k': menu_inverse(matrix_a); break;
        case 'l': menu_create_matrix(&matrix_b); break;
        case 'm': menu_compare(matrix_a, matrix_b); break;
        case 'n': menu_destroy(&matrix_a); break;
        case 'o': menu_destroy(&matrix_b); break;
        case 'q': printf("До свидания!\n"); break;
        default: printf("Неверный выбор!\n");
        }

        if (choice != 'q')
        {
            printf("\nEnter для продолжения...");
            getchar();
        }

    } while (choice != 'q');

    return 0;
}