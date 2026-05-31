#include "list.h"

/* Вспомогательная функция создания узла данных */
static struct data *create_data_node(int key, double value)
{
    struct data *new_node = (struct data *)malloc(sizeof(struct data));
    if (!new_node)
    {
        fprintf(stderr, "Ошибка: не удалось выделить память\n");
        return NULL;
    }
    new_node->key = key;
    new_node->value = value;
    return new_node;
}

/* Добавление в начало списка */
void data_add_front(struct list_head *head, int key, double value)
{
    struct data *new_node = create_data_node(key, value);
    if (!new_node)
        return;
    /* Вставляем после head (между head и head->next) */
    __list_add(&new_node->list, head, head->next);
}

/* Добавление в конец списка */
void data_add_tail(struct list_head *head, int key, double value)
{
    struct data *new_node = create_data_node(key, value);
    if (!new_node)
        return;
    /* Вставляем перед head (между head->prev и head) */
    __list_add(&new_node->list, head->prev, head);
}

/* Удаление элемента по ключу */
void data_delete(struct list_head *head, int key)
{
    struct list_head *pos, *n;
    int found = 0;

    if (head->next == head)
    {
        printf("Список пуст.\n");
        return;
    }

    /* Используем безопасную итерацию для возможности удаления */
    list_for_each_safe(pos, n, head)
    {
        struct data *data_ptr = container_of(pos, struct data, list);
        if (data_ptr->key == key)
        {
            __list_del(pos->prev, pos->next);
            free(data_ptr);
            found = 1;
            printf("Элемент с ключом %d удалён.\n", key);
            break; /* Удаляем только первое вхождение */
        }
    }

    if (!found)
    {
        printf("Элемент с ключом %d не найден.\n", key);
    }
}

/* Поиск элемента по ключу */
double data_lookup(struct list_head *head, int key)
{
    struct list_head *pos;

    if (head->next == head)
    {
        return -1.0; /* Ошибка: список пуст */
    }

    list_for_each(pos, head)
    {
        struct data *data_ptr = container_of(pos, struct data, list);
        if (data_ptr->key == key)
        {
            return data_ptr->value;
        }
    }

    return -1.0; /* Ошибка: не найдено */
}

/* Подсчет количества элементов */
int list_count(struct list_head *head)
{
    struct list_head *pos;
    int count = 0;
    list_for_each(pos, head)
    {
        count++;
    }
    return count;
}

/* Вывод всех элементов */
void list_print(struct list_head *head)
{
    struct list_head *pos;
    int count = 0;

    if (head->next == head)
    {
        printf("Список пуст.\n");
        return;
    }

    printf("Содержимое списка (Ключ, Значение):\n");
    printf("-------------------------------------------------\n");
    list_for_each(pos, head)
    {
        struct data *data_ptr = container_of(pos, struct data, list);
        printf("[%3d] Ключ: %7d, Значение: %10.2f\n", count++, data_ptr->key, data_ptr->value);
    }
    printf("-------------------------------------------------\n");
    printf("Всего элементов: %d\n", count);
}

/* Очистка списка */
void list_clear(struct list_head *head)
{
    struct list_head *pos, *n;

    list_for_each_safe(pos, n, head)
    {
        struct data *data_ptr = container_of(pos, struct data, list);
        free(data_ptr);
    }
    init_list_head(head);
}

/* Добавление элементов из стандартного ввода (stdin) */
/* Использование: ./lab3 < data.txt */
int list_add_from_stdin(struct list_head *head)
{
    int key;
    double value;
    int count = 0;

    printf("Ввод данных из потока (завершите ввод Ctrl+D или EOF)...\n");
    while (scanf("%d %lf", &key, &value) == 2)
    {
        data_add_tail(head, key, value);
        count++;
    }
    /* Очистка флага EOF для дальнейшей работы меню */
    clearerr(stdin);

    printf("Добавлено %d элементов из потока.\n", count);
    return count;
}
