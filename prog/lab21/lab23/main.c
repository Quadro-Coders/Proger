#include "contstruct.h"

int main(void)
{
    printf("=== Практическая работа №3, Вариант 2 (Очередь) ===\n\n");

    // 1. Создание очереди
    Queue *q = queue_create();
    printf("1. Создана пустая очередь\n");
    printf("   Пустая? %s\n", queue_is_empty(q) ? "Да" : "Нет");

    // 2. Добавление элементов (enqueue)
    printf("\n2. Добавляем элементы: 10, 20, 30\n");
    queue_enqueue(q, 10);
    queue_enqueue(q, 20);
    queue_enqueue(q, 30);
    printf("   Размер: %zu\n", queue_size(q));

    // 3. Добавление в начало (fenqueue, Задание 5)
    printf("\n3. Добавляем 5 в начало (fenqueue)\n");
    queue_fenqueue(q, 5);

    // 4. Печать через итератор
    printf("\n4. Очередь сейчас: ");
    QueueIterator it = queue_begin(q);
    while (it.current != NULL)
    {
        printf("%d ", it.current->data);
        queue_iterator_next(&it);
    }
    printf("\n");

    // 5. Peek и Dequeue
    printf("\n5. Peek (первый элемент): %d\n", queue_peek(q));
    printf("   Dequeue: %d\n", queue_dequeue(q));
    printf("   Размер после dequeue: %zu\n", queue_size(q));

    // 6. Копирование (Задание 5)
    printf("\n6. Копирование очереди\n");
    Queue *q_copy = queue_copy(q);
    printf("   Копия: ");
    it = queue_begin(q_copy);
    while (it.current != NULL)
    {
        printf("%d ", it.current->data);
        queue_iterator_next(&it);
    }
    printf("\n");

    // 7. Слияние (Задание 5)
    printf("\n7. Слияние с другой очередью\n");
    Queue *q2 = queue_create();
    queue_enqueue(q2, 100);
    queue_enqueue(q2, 200);
    Queue *merged = queue_merge(q, q2);
    printf("   Результат слияния: ");
    it = queue_begin(merged);
    while (it.current != NULL)
    {
        printf("%d ", it.current->data);
        queue_iterator_next(&it);
    }
    printf("\n");

    // 8. Очистка
    printf("\n8. Очистка очереди\n");
    queue_clear(q);
    printf("   Пустая? %s\n", queue_is_empty(q) ? "Да" : "Нет");

    // 9. Освобождение памяти
    printf("\n9. Освобождение памяти\n");
    queue_free(q);
    queue_free(q_copy);
    queue_free(q2);
    queue_free(merged);
    printf("   Готово!\n");

    printf("\n=== Программа завершена ===\n");
    return 0;
}
