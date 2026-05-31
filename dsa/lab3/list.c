#include "list.h"

list_node *list_init()
{
    return NULL;
}

list_node *list_create_node()
{
    list_node *node = (list_node *)malloc(sizeof(list_node));
    if (!node)
        return NULL;
    node->next = node;
    node->prev = node;
    node->key = 0;
    node->value = 0.0;
    return node;
}

// Ввод значений для добавления нескольких элементов в начало
void list_add_front_multi(list_node **head)
{
    int key;
    double value;
    int count = 0;

    printf("Ввод элементов (q для выхода):\n");
    for (int i = 1;; i++)
    {
        printf("Элемент %d\n", i);
        if (input_key(&key) == 0)
            break;
        if (input_value(&value) == 0)
            break;
        list_node *new_head = list_add_front(*head, key, value);
        if (new_head == NULL)
        {
            printf("Ошибка: элемент %d не добавлен (нет памяти)\n", i);
            return;
        }
        else
        {
            *head = new_head;
            count++;
        }
    }
    printf("Добавлено элементов: %d\n", count);
}

// Добавление элемента в начало списка
list_node *list_add_front(struct list_node *head, int key, double value)
{
    list_node *new_node = list_create_node();
    if (new_node == NULL)
    {
        printf("Ошибка: нет памяти\n");
        return NULL;
    }
    new_node->key = key;
    new_node->value = value;

    if (head == NULL)
    {
        new_node->next = new_node;
        new_node->prev = new_node;
        return new_node;
    }

    new_node->next = head;
    new_node->prev = head->prev;
    head->prev->next = new_node;
    head->prev = new_node;
    return new_node;
}

// Ввод значений для добавления нескольких элементов в конец
void list_add_tail_multi(list_node **head)
{
    int key;
    double value;
    int count = 0;

    printf("Ввод элементов (q для выхода):\n");
    for (int i = 1;; i++)
    {
        printf("Элемент %d\n", i);
        if (input_key(&key) == 0)
            break;
        if (input_value(&value) == 0)
            break;
        list_node *new_head = list_add_tail(*head, key, value);
        if (new_head == NULL)
        {
            printf("Ошибка: элемент %d не добавлен (нет памяти)\n", i);
            return;
        }
        if (*head == NULL)
        {
            *head = new_head;
        }
        count++;
    }
    printf("Добавлено элементов: %d\n", count);
}

// Добавление элемента в конец списка
list_node *list_add_tail(struct list_node *head, int key, double value)
{
    list_node *new_node = list_create_node();
    if (new_node == NULL)
    {
        printf("Ошибка: нет памяти\n");
        return NULL;
    }
    new_node->key = key;
    new_node->value = value;

    if (head == NULL)
    {
        new_node->next = new_node;
        new_node->prev = new_node;
        return new_node;
    }

    new_node->next = head;
    new_node->prev = head->prev;
    new_node->prev->next = new_node;
    head->prev = new_node;
    return head;
}

// Ввод значений для добавления по индексу
void list_add_index_multi(list_node **head)
{
    int key, index;
    double value;
    int count = 0;

    printf("Ввод элементов (q для выхода):\n");
    for (int i = 1;; i++)
    {
        printf("Элемент %d\n", i);
        if (*head != NULL)
        {
            if (input_index(&index) == 0)
                break;
        }
        else
        {
            printf("Список пуст. Элемент будет добавлен как первый (индекс 0)\n");
            index = 0;
        }
        if (input_key(&key) == 0)
            break;
        if (input_value(&value) == 0)
            break;
        list_node *node = list_add_index(*head, key, value, index);
        if (node == NULL)
        {
            printf("Ошибка: нет памяти\n");
            return;
        }
        *head = node;
        count++;
    }
    printf("Добавлено элементов: %d\n", count);
}

// Добавление по индексу
list_node *list_add_index(struct list_node *head, int key, double value, int index)
{
    if (index < 0)
    {
        printf("Ошибка: индекс не может быть отрицательным\n");
        return head;
    }
    if (index == 0)
    {
        return list_add_front(head, key, value);
    }

    list_node *current = head;
    int i;
    for (i = 0; i < index && current->next != head; i++)
        current = current->next;

    if (i < index)
    {
        printf("Индекс %d больше размера списка, добавляем в конец\n", index);
        list_node *new_head = list_add_tail(head, key, value);
        return (head == NULL) ? new_head : head;
    }

    list_node *node = list_create_node();
    if (node == NULL)
    {
        printf("Ошибка: нет памяти\n");
        return head;
    }
    node->key = key;
    node->value = value;
    node->prev = current->prev;
    node->next = current;
    current->prev->next = node;
    current->prev = node;
    return head;
}

// Добавление элементов из файла
void list_add_from_file(list_node **head)
{
    printf("Не смог реализовать\n");
}

// Вывод списка
void list_for_each(list_node *head)
{
    if (head == NULL)
    {
        printf("Список пуст\n");
        return;
    }

    list_node *current = head;
    int count = 0;
    printf("Элементы списка:\n");
    printf("№\tКлюч\tЗначение\tАдрес\n");
    do
    {
        printf("%d\t%d\t%lf\t%p\n", count + 1, current->key, current->value, (void *)current);
        current = current->next;
        count++;
    } while (current != head);
    printf("Всего элементов: %d\n", count);
}

// Ввод ключа для поиска по ключу
void list_lookup_multi(list_node *head)
{
    int key;

    if (head == NULL)
    {
        printf("Ошибка: список пуст\n");
        return;
    }

    printf("Поиск элементов (q для выхода):\n");
    for (int i = 1;; i++)
    {
        printf("Поиск %d\n", i);
        if (input_key(&key) == 0)
            break;
        list_lookup(head, key);
    }
}

// Поиск по ключу (с выводом результатов)
list_node *list_lookup(struct list_node *head, int key)
{
    if (head == NULL)
    {
        printf("Ошибка: список пуст\n");
        return NULL;
    }

    list_node *current = head;
    int position = 0;
    do
    {
        if (current->key == key)
        {
            printf("Найден элемент с ключом %d:\n", key);
            printf("  Позиция: %d\n", position);
            printf("  Адрес: %p\n", (void *)current);
            printf("  Значение: %lf\n", current->value);
            return current;
        }
        current = current->next;
        position++;
    } while (current != head);

    printf("Элемент с ключом %d не найден\n", key);
    return NULL;
}

// Поиск по ключу (тихий, для экспериментов - без вывода)
list_node *list_lookup_silent(struct list_node *head, int key)
{
    if (head == NULL)
        return NULL;

    list_node *current = head;
    do
    {
        if (current->key == key)
        {
            return current;
        }
        current = current->next;
    } while (current != head);
    return NULL;
}

// Очистка списка (с выводом)
void list_clear(list_node **HEAD)
{
    if (*HEAD == NULL)
        return;

    list_node *last = (*HEAD)->prev;
    last->next = NULL;
    list_node *current = *HEAD;
    int count = 0;

    while (current != NULL)
    {
        list_node *next = current->next;
        free(current);
        current = next;
        count++;
    }
    *HEAD = NULL;
    printf("Очищено элементов: %d\n", count);
}

// Очистка списка (тихая, для экспериментов)
void list_clear_silent(list_node **HEAD)
{
    if (*HEAD == NULL)
        return;

    list_node *last = (*HEAD)->prev;
    last->next = NULL;
    list_node *current = *HEAD;

    while (current != NULL)
    {
        list_node *next = current->next;
        free(current);
        current = next;
    }
    *HEAD = NULL;
}

void list_delete_multi(list_node **head)
{
    int key;
    int count = 0;

    if (*head == NULL)
    {
        printf("Ошибка: список пуст\n");
        return;
    }

    printf("Удаление элементов по ключу (q для выхода):\n");
    for (int i = 1;; i++)
    {
        printf("Удаление %d\n", i);
        if (input_key(&key) == 0)
            break;
        list_node *old_head = *head;
        *head = list_delete(*head, key);
        if (*head != old_head || (old_head != NULL && list_lookup_silent(old_head, key) == NULL))
        {
            count++;
            printf("Элемент по ключу %d удален\n", key);
        }
        else
        {
            printf("Элемент по ключу %d не найден\n", key);
        }
        if (*head == NULL)
        {
            printf("Список пуст\n");
            break;
        }
    }
    printf("Удалено элементов: %d\n", count);
}

// Удаление элемента по ключу
list_node *list_delete(struct list_node *head, int key)
{
    if (!head)
        return NULL;

    list_node *listNodeKey = list_lookup_silent(head, key);
    if (listNodeKey == NULL)
    {
        return head;
    }

    listNodeKey->next->prev = listNodeKey->prev;
    listNodeKey->prev->next = listNodeKey->next;

    if (listNodeKey == head)
    {
        list_node *newHead = head->next;
        if (newHead == head)
        {
            free(listNodeKey);
            return NULL;
        }
        free(listNodeKey);
        return newHead;
    }

    free(listNodeKey);
    return head;
}

// Экспериментальное исследование для таблицы 1
void experiment_table(list_node **head)
{
    printf("\n=== Экспериментальное исследование ===\n");
    printf("Таблица 1: Зависимость времени от количества элементов\n\n");

    printf("# Элементов\tAddTail_ms\tLookup_ms\n");

    int sizes[] = {50000, 100000, 150000, 200000, 250000, 300000, 350000, 400000, 450000, 500000};
    int num_tests = sizeof(sizes) / sizeof(sizes[0]);
    int lookups = 10;

    for (int test = 0; test < num_tests; test++)
    {
        int n = sizes[test];

        // Очищаем список перед каждым тестом (ТИХО)
        list_clear_silent(head);

        // Измерение времени добавления
        double t1 = wtime();
        for (int i = 0; i < n; i++)
        {
            int key = getrand(0, 10000000);
            double value = (double)getrand(0, 10000000);
            if (*head == NULL)
                *head = list_add_tail(*head, key, value);
            else
                list_add_tail(*head, key, value);
        }
        t1 = wtime() - t1;
        double add_time_ms = t1 * 1e3;

        // Измерение времени поиска (ОБЩЕЕ время для 10 попыток)
        double t2_total = 0;
        for (int l = 0; l < lookups; l++)
        {
            int search_key = getrand(0, 10000000);
            double t2 = wtime();
            list_lookup_silent(*head, search_key);
            t2 = wtime() - t2;
            t2_total += t2;
        }
        double lookup_time_ms = t2_total * 1e3;

        printf("%d\t%.2lf\t%.2lf\n", n, add_time_ms, lookup_time_ms);
    }

    list_clear_silent(head);
}

// Быстрый эксперимент
void experiment(list_node **head)
{
    int n;
    int m;
    int ch;

    printf("\n=== Быстрый эксперимент ===\n");
    do
    {
        printf("Количество элементов (q для выхода): ");
        m = scanf(" %d", &n);
        if (m == 0)
        {
            ch = getchar();
            if (ch == 'q' || ch == EOF)
            {
                while ((ch = getchar()) != '\n' && ch != EOF)
                    ;
                return;
            }
            else
            {
                printf("Ввод некорректный. Повторите ввод\n");
                while ((ch = getchar()) != '\n' && ch != EOF)
                    ;
            }
        }
    } while (!m);

    list_clear_silent(head);

    double t1 = wtime();
    for (int i = 0; i < n; i++)
    {
        int key = getrand(0, 10000000);
        double value = (double)getrand(0, 10000000);
        if (*head == NULL)
            *head = list_add_tail(*head, key, value);
        else
            list_add_tail(*head, key, value);
    }
    t1 = wtime() - t1;

    printf("Время добавления %d элементов в конец: %.3lf мс\n", n, t1 * 1e3);

    double t2 = wtime();
    int search_key = getrand(0, 10000000);
    list_lookup(*head, search_key);
    t2 = wtime() - t2;
    printf("Время поиска: %.3lf мс\n", t2 * 1e3);
}

int getrand(int min, int max)
{
    return (int)((double)rand() / (RAND_MAX + 1.0) * (max - min) + min);
}

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int input_key(int *key)
{
    int m;
    char buffer[256];

    do
    {
        printf("Введите ключ (q для выхода): ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
            return 0;

        if (buffer[0] == 'q' || buffer[0] == 'Q')
            return 0;

        m = sscanf(buffer, "%d", key);
        if (m == 0)
        {
            printf("Ввод некорректный. Повторите ввод\n");
        }
    } while (!m);

    return 1;
}

int input_value(double *value)
{
    int m;
    char buffer[256];

    do
    {
        printf("Введите значение (q для выхода): ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
            return 0;

        if (buffer[0] == 'q' || buffer[0] == 'Q')
            return 0;

        m = sscanf(buffer, "%lf", value);
        if (m == 0)
        {
            printf("Ввод некорректный. Повторите ввод\n");
        }
    } while (!m);

    return 1;
}

int input_index(int *index)
{
    int m;
    char buffer[256];

    do
    {
        printf("Введите индекс (q для выхода): ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
            return 0;

        if (buffer[0] == 'q' || buffer[0] == 'Q')
            return 0;

        m = sscanf(buffer, "%d", index);
        if (m == 0)
        {
            printf("Ввод некорректный. Повторите ввод\n");
            continue;
        }

        if (*index < 0)
        {
            printf("Индекс меньше 0. Повторите ввод\n");
            m = 0;
        }
    } while (!m);

    return 1;
}

void menu()
{

    printf("  Циклический двусвязный список\n");
    printf("1)  Создать новый список\n");
    printf("2)  Добавить в начало списка\n");
    printf("3)  Добавить в конец списка\n");
    printf("4)  Добавить по индексу\n");
    printf("5)  Добавить из файла\n");
    printf("6)  Поиск элемента\n");
    printf("7)  Удалить элемент по ключу\n");
    printf("8)  Вывести все элементы списка\n");
    printf("9)  Очистить список\n");
    printf("10) Эксперимент (таблица 1)\n");
    printf("11) Быстрый эксперимент\n");
    printf("0)  Завершить работу\n");
    printf("Выберите операцию: ");
}
