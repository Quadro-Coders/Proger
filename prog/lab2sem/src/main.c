#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fiostruct.h"
#include "contstruct.h"

/*
  Функция для полного освобождения очереди вместе с матрицами внутри.
  Чтобы не было утечек памяти, проходим по списку и чистим каждый элемент.
 */
static void queue_free_with_data(Queue *q)
{
    if (!q)
        return;
    QueueNode *curr = q->front;
    while (curr)
    {
        Matrix2D_free(curr->data); // Освобождаем память под матрицу
        QueueNode *next = curr->next;
        free(curr); // Освобождаем узел списка
        curr = next;
    }
    free(q);
}

// Справка по командам
void print_usage(const char *prog)
{
    printf("Доступные команды:\n");
    printf("  %s help                              - показать эту справку\n", prog);
    printf("  %s save <file> [опции]               - сохранить 10000 элементов в файл\n", prog);
    printf("  %s load <file> [опции]               - загрузить очередь из файла\n", prog);
    printf("  %s list <file> [опции]               - вывести список всех элементов\n", prog);
    printf("  %s get <номер> <file> [опции]        - вывести N-й элемент\n", prog);
    printf("\nОпции:\n");
    printf("  --binary, -b       - использовать бинарный режим (по умолчанию текстовый)\n");
    printf("  --rows <R>         - количество строк (по умолчанию 3, для файлов определяется автоматически)\n");
    printf("  --cols <C>         - количество столбцов (по умолчанию 3, для файлов определяется автоматически)\n");
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        print_usage(argv[0]);
        return 0;
    }

    const char *cmd = argv[1];
    const char *filename = NULL;
    int binary = 0;
    int index = 0;
    int rows = 3, cols = 3; // константа размера матрицы без параметров
    int rows_given = 0, cols_given = 0;

    if (strcmp(cmd, "help") == 0)
    {
        print_usage(argv[0]);
        return 0;
    }

    if (strcmp(cmd, "get") == 0)
    {
        if (argc < 4)
        {
            printf("Ошибка: для команды 'get' требуется номер элемента и имя файла.\n");
            print_usage(argv[0]);
            return 1;
        }
        index = atoi(argv[2]);
        filename = argv[3];
        for (int i = 4; i < argc; ++i)
        {
            if (strcmp(argv[i], "--binary") == 0 || strcmp(argv[i], "-b") == 0)
                binary = 1;
            else if (strcmp(argv[i], "--rows") == 0 && i + 1 < argc)
            {
                rows = atoi(argv[++i]);
                rows_given = 1;
            }
            else if (strcmp(argv[i], "--cols") == 0 && i + 1 < argc)
            {
                cols = atoi(argv[++i]);
                cols_given = 1;
            }
        }
    }
    else if (strcmp(cmd, "save") == 0 || strcmp(cmd, "load") == 0 || strcmp(cmd, "list") == 0)
    {
        if (argc < 3)
        {
            printf("Ошибка: для команды '%s' требуется имя файла.\n", cmd);
            print_usage(argv[0]);
            return 1;
        }
        filename = argv[2];
        for (int i = 3; i < argc; ++i)
        {
            if (strcmp(argv[i], "--binary") == 0 || strcmp(argv[i], "-b") == 0)
                binary = 1;
            else if (strcmp(argv[i], "--rows") == 0 && i + 1 < argc)
            {
                rows = atoi(argv[++i]);
                rows_given = 1;
            }
            else if (strcmp(argv[i], "--cols") == 0 && i + 1 < argc)
            {
                cols = atoi(argv[++i]);
                cols_given = 1;
            }
        }
    }
    else
    {
        printf("Неизвестная команда: %s\n", cmd);
        print_usage(argv[0]);
        return 1;
    }

    if (!filename)
    {
        print_usage(argv[0]);
        return 1;
    }
    if (rows <= 0 || cols <= 0)
    {
        printf("Ошибка: размеры матрицы должны быть больше 0.\n");
        return 1;
    }

    // АВТО-ОПРЕДЕЛЕНИЕ РАЗМЕРОВ
    if (!rows_given && !cols_given && strcmp(cmd, "save") != 0)
    {
        FILE *f = fopen(filename, binary ? "rb" : "r");
        if (f)
        {
            int fr = 0, fc = 0;
            if (binary)
            {
                fread(&fr, sizeof(int), 1, f);
                fread(&fc, sizeof(int), 1, f);
            }
            else
            {
                fscanf(f, "%d %d", &fr, &fc);
            }
            if (fr > 0 && fc > 0)
            {
                rows = fr;
                cols = fc;
                printf("(Автоматически определены размеры файла: %dx%d)\n", rows, cols);
            }
            fclose(f);
        }
    }

    size_t elem_size = 2 * sizeof(int) + (rows * cols) * (sizeof(float) + sizeof(rgbled));
    printf("Режим: %s | Файл: %s | Матрица: %dx%d | Размер записи: %zu байт\n",
           binary ? "Бинарный" : "Текстовый", filename, rows, cols, elem_size);

    if (strcmp(cmd, "save") == 0)
    {
        printf("Генерация 10000 элементов...\n"); // генерация формально по константе
        Queue *q = rand_gen_struct_in_container(10000, rows, cols);
        if (!q)
        {
            printf("Ошибка генерации!\n");
            return 1;
        }
        if (save_queue_to_file(filename, q, binary, elem_size))
            printf("Успешно сохранено в %s\n", filename);
        else
            printf("Ошибка сохранения!\n");
        queue_free_with_data(q);
    }
    else if (strcmp(cmd, "load") == 0)
    {
        printf("Загрузка данных...\n");
        Queue *q = load_queue_from_file(filename, binary, elem_size);
        if (q)
        {
            printf("Загружено %zu элементов.\n", queue_size(q));
            queue_free_with_data(q);
        }
        else
            printf("Ошибка загрузки или файл пуст!\n");
    }
    else if (strcmp(cmd, "list") == 0)
    {
        list_file_objects(filename, binary, elem_size);
    }
    else if (strcmp(cmd, "get") == 0)
    {
        // Преобразуем ввод пользователя (с 1) во внутренний индекс массива (с 0)
        int target_idx = index - 1;

        printf("Загрузка контейнера из файла...\n");
        Queue *q = load_queue_from_file(filename, binary, elem_size);
        if (!q)
        {
            printf("Ошибка загрузки!\n");
            return 1;
        }

        if (target_idx < 0 || target_idx >= (int)queue_size(q))
        {
            printf("Элемент с номером %d не найден (всего элементов: %zu)\n", index, queue_size(q));
            queue_free_with_data(q);
            return 1;
        }

        // Проходим по очереди до нужного индекса (0-based)
        QueueNode *curr = q->front;
        for (int i = 0; i < target_idx; ++i)
            curr = curr->next;
        Matrix2D *target = curr->data;

        if (target)
        {
            printf("Элемент №%d [%dx%d] из загруженной структуры:\n", index, target->rows, target->cols);
            Matrix2D_print(target);
        }
        queue_free_with_data(q);
    }

    return 0;
}
