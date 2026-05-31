#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "contstruct.h"
#include "matrix2d.h"
#include "fiostruct.h"

// Вспомогательная функция для полного освобождения очереди с матрицами
static void test_queue_free(Queue *q)
{
    if (!q)
        return;
    QueueNode *curr = q->front;
    while (curr)
    {
        Matrix2D_free(curr->data);
        QueueNode *next = curr->next;
        free(curr);
        curr = next;
    }
    free(q);
}

void test_queue_operations()
{
    printf("Тесты очереди\n");
    Queue *q = queue_create();
    assert(q != NULL && "queue_create failed");
    assert(queue_is_empty(q) && "Очередь не пуста после создания");
    assert(queue_size(q) == 0 && "Размер != 0");

    Matrix2D *m = Matrix2D_create(2, 2);
    assert(m != NULL);
    assert(queue_enqueue(q, m) == 1 && "enqueue failed");
    assert(queue_size(q) == 1 && "Размер != 1");
    assert(queue_peek(q) == m && "peek вернул неверный указатель");

    Matrix2D *out = queue_dequeue(q);
    assert(out == m && "dequeue вернул неверный указатель");
    assert(queue_is_empty(q) && "Очередь не пуста после dequeue");

    queue_free(q);
    Matrix2D_free(m);
    printf("Тесты очереди пройдены\n\n");
}

void test_file_io_roundtrip()
{
    printf(" Тесты сохранения/загрузки (Roundtrip)\n");
    const char *bin = "test_rw.bin";
    const char *txt = "test_rw.txt";
    int rows = 3, cols = 3;
    size_t elem = 2 * sizeof(int) + (rows * cols) * (sizeof(float) + sizeof(rgbled));

    Queue *orig = rand_gen_struct_in_container(50, rows, cols);
    assert(orig != NULL && "Генерация не удалась");
    assert(queue_size(orig) == 50);

    // Бинарный режим
    assert(save_queue_to_file(bin, orig, 1, elem) == 1 && "save bin failed");
    Queue *load_bin = load_queue_from_file(bin, 1, elem);
    assert(load_bin != NULL && "load bin failed");
    assert(queue_size(load_bin) == 50 && "Неверное кол-во при загрузке bin");

    // Текстовый режим
    assert(save_queue_to_file(txt, orig, 0, elem) == 1 && "save txt failed");
    Queue *load_txt = load_queue_from_file(txt, 0, elem);
    assert(load_txt != NULL && "load txt failed");
    assert(queue_size(load_txt) == 50 && "Неверное кол-во при загрузке txt");

    test_queue_free(orig);
    test_queue_free(load_bin);
    test_queue_free(load_txt);
    remove(bin);
    remove(txt);
    printf("Тесты файлового ввода/вывода пройдены\n\n");
}

int main()
{
    printf("Запуск Unit-тестов для Практической №5...\n\n");
    test_queue_operations();
    test_file_io_roundtrip();
    printf("ВСЕ ТЕСТЫ ПРОЙДЕНЫ УСПЕШНО!\n");
    return 0;
}
