#include "list.h"
#include <unistd.h>
#include <time.h>

int main()
{
    list_node *HEAD = NULL;
    int exit_program = 0;
    int n;
    char c;

    // Инициализация генератора случайных чисел
    srand(time(NULL));

    while (!exit_program)
    {
        menu();

        if (scanf("%d", &n) != 1)
        {
            printf("Ошибка ввода команды\n");
            while ((c = getchar()) != '\n' && c != EOF)
                ;
            continue;
        }
        while ((c = getchar()) != '\n' && c != EOF)
            ;

        switch (n)
        {
        case 1:
            list_clear(&HEAD);
            HEAD = list_init();
            printf("Создан новый список\n");
            break;
        case 2:
            list_add_front_multi(&HEAD);
            break;
        case 3:
            list_add_tail_multi(&HEAD);
            break;
        case 4:
            list_add_index_multi(&HEAD);
            break;
        case 5:
            list_add_from_file(&HEAD);
            break;
        case 6:
            list_lookup_multi(HEAD);
            break;
        case 7:
            list_delete_multi(&HEAD);
            break;
        case 8:
            list_for_each(HEAD);
            break;
        case 9:
            list_clear(&HEAD);
            break;
        case 10:
            experiment_table(&HEAD);
            break;
        case 11:
            experiment(&HEAD);
            break;
        case 0:
            list_clear(&HEAD);
            exit_program = 1;
            printf("Завершение работы программы\n");
            break;
        default:
            printf("Такой команды нет. Выберите из доступных опций.\n");
        }
    }

    return 0;
}
