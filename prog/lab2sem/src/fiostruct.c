#include "fiostruct.h"
#include "debug_log.h"

/* Вспомогательная функция для чтения rgbled из текста */
static void read_led_from_text(FILE *f, rgbled *out_led)
{
    unsigned int tmp_r, tmp_g, tmp_b, tmp_br, tmp_te, tmp_ctrl, tmp_mode;
    if (fscanf(f, "%u %u %u %u %u %u %u",
               &tmp_r, &tmp_g, &tmp_b, &tmp_br, &tmp_te, &tmp_ctrl, &tmp_mode) == 7)
    {
        led_set_all(out_led, tmp_r, tmp_g, tmp_b, tmp_br, tmp_te, tmp_ctrl, tmp_mode);
    }
}

/* Упаковка матрицы в плоский буфер для бинарной записи */
static void pack_matrix_to_buffer(const Matrix2D *m, void *buf)
{
    int *p_rows = (int *)buf;
    int *p_cols = p_rows + 1;
    float *p_data = (float *)(p_cols + 1);
    rgbled *p_leds = (rgbled *)(p_data + (m->rows * m->cols));

    *p_rows = m->rows;
    *p_cols = m->cols;
    for (int r = 0; r < m->rows; ++r)
        for (int c = 0; c < m->cols; ++c)
            p_data[r * m->cols + c] = m->data[r][c];
    for (int r = 0; r < m->rows; ++r)
        for (int c = 0; c < m->cols; ++c)
            p_leds[r * m->cols + c] = m->leds[r][c];
}

static Matrix2D *unpack_buffer_to_matrix(const void *buf, int rows, int cols)
{
    Matrix2D *m = Matrix2D_create(rows, cols);
    if (!m)
        return NULL;
    const float *p_data = (const float *)((const int *)buf + 2);
    const rgbled *p_leds = (const rgbled *)(p_data + (rows * cols));
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c)
        {
            m->data[r][c] = p_data[r * cols + c];
            m->leds[r][c] = p_leds[r * cols + c];
        }
    return m;
}

/*  5.1 Генерация  */
Queue *rand_gen_struct_in_container(size_t n, int rows, int cols)
{
    if (rows <= 0 || cols <= 0)
        return NULL;
    Queue *q = queue_create();
    if (!q)
        return NULL;
    for (size_t i = 0; i < n; ++i)
    {
        Matrix2D *m = Matrix2D_create(rows, cols);
        if (!m)
        {
            queue_free(q);
            return NULL;
        }
        Matrix2D_fill_random(m, 0.0f, 99.9f);
        for (int r = 0; r < rows; ++r)
            for (int c = 0; c < cols; ++c)
                Matrix2D_set_led(m, r, c, rand() % 256, rand() % 256, rand() % 256,
                                 rand() % 101, rand() % 10000 + 2000, rand() % 4, rand() % 3);
        queue_enqueue(q, m);
    }
    return q;
}

/*  Сохранение в файл  */
int save_queue_to_file(const char *filename, Queue *q, int binary, size_t element_size)
{
    if (!q || !filename)
    {
        LOG_ERROR("Неверные аргументы save");
        return 0;
    }
    LOG_INFO("Открытие %s (%s)", filename, binary ? "wb" : "w");
    FILE *f = fopen(filename, binary ? "wb" : "w");
    if (!f)
    {
        LOG_ERROR("fopen failed");
        return 0;
    } // логи
    if (!q || !filename)
        return 0;
    // FILE *f = fopen(filename, binary ? "wb" : "w");
    if (!f)
        return 0;

    void *bin_buf = binary ? malloc(element_size) : NULL;
    QueueNode *curr = q->front;

    // АВТО-ЗАГОЛОВОК ДЛЯ БИНАРНОГО РЕЖИМА
    if (binary && curr && curr->data)
    {
        fwrite(&curr->data->rows, sizeof(int), 1, f);
        fwrite(&curr->data->cols, sizeof(int), 1, f);
    }

    while (curr)
    {
        Matrix2D *m = curr->data;
        if (binary)
        {
            pack_matrix_to_buffer(m, bin_buf);
            fwrite(bin_buf, 1, element_size, f);
        }
        else
        {
            fprintf(f, "%d %d ", m->rows, m->cols);
            for (int r = 0; r < m->rows; ++r)
                for (int c = 0; c < m->cols; ++c)
                    fprintf(f, "%.4f ", m->data[r][c]);
            for (int r = 0; r < m->rows; ++r)
                for (int c = 0; c < m->cols; ++c)
                {
                    rgbled l = m->leds[r][c];
                    fprintf(f, "%u %u %u %u %u %u %u ", l.red, l.green, l.blue, l.bright, l.temp, l.module, l.mode);
                }
            fprintf(f, "\n");
        }
        curr = curr->next;
    }

    fclose(f);
    free(bin_buf);
    return 1;
}

/*  Загрузка из файла  */
Queue *load_queue_from_file(const char *filename, int binary, size_t element_size)
{
    if (!filename)
        return NULL;
    FILE *f = fopen(filename, binary ? "rb" : "r");
    if (!f)
        return NULL;

    Queue *q = queue_create();
    void *bin_buf = binary ? malloc(element_size) : NULL;

    if (binary)
    {
        int r = 0, c = 0;
        fread(&r, sizeof(int), 1, f);
        fread(&c, sizeof(int), 1, f);
        size_t real_elem = 2 * sizeof(int) + (r * c) * (sizeof(float) + sizeof(rgbled));

        while (fread(bin_buf, 1, real_elem, f) == real_elem)
        {
            Matrix2D *m = unpack_buffer_to_matrix(bin_buf, r, c);
            if (m)
                queue_enqueue(q, m);
        }
    }
    else
    {
        int r, c;
        while (fscanf(f, "%d %d", &r, &c) == 2)
        {
            Matrix2D *m = Matrix2D_create(r, c);
            if (!m)
                break;
            for (int i = 0; i < r * c; ++i)
                fscanf(f, "%f", &m->data[i / c][i % c]);
            for (int i = 0; i < r * c; ++i)
                read_led_from_text(f, &m->leds[i / c][i % c]);
            queue_enqueue(q, m);
        }
    }

    fclose(f);
    free(bin_buf);
    return q;
}

/*  Утилиты  */
size_t count_objects_in_file(const char *filename, int binary, size_t element_size)
{
    if (!filename)
        return 0;
    FILE *f = fopen(filename, binary ? "rb" : "r");
    if (!f)
        return 0;

    size_t cnt = 0;
    if (binary)
    {
        fseek(f, 2 * sizeof(int), SEEK_SET); // Пропускаем заголовок
        void *dummy = malloc(element_size);
        while (fread(dummy, 1, element_size, f) == element_size)
            cnt++;
        free(dummy);
    }
    else
    {
        int r, c;
        float fv;
        unsigned int tmp;
        while (fscanf(f, "%d %d", &r, &c) == 2)
        {
            cnt++;
            for (int i = 0; i < r * c; ++i)
                fscanf(f, "%f", &fv);
            for (int i = 0; i < r * c; ++i)
                fscanf(f, "%u %u %u %u %u %u %u", &tmp, &tmp, &tmp, &tmp, &tmp, &tmp, &tmp);
        }
    }
    fclose(f);
    return cnt;
}

Matrix2D *get_element_from_text_file(const char *filename, int index)
{
    if (!filename || index < 0)
        return NULL;
    FILE *f = fopen(filename, "r");
    if (!f)
        return NULL;
    Matrix2D *res = NULL;
    for (int i = 0; i <= index; ++i)
    {
        if (i == index)
        {
            int r, c;
            if (fscanf(f, "%d %d", &r, &c) == 2)
            {
                res = Matrix2D_create(r, c);
                if (res)
                {
                    for (int j = 0; j < r * c; ++j)
                        fscanf(f, "%f", &res->data[j / c][j % c]);
                    for (int j = 0; j < r * c; ++j)
                        read_led_from_text(f, &res->leds[j / c][j % c]);
                }
            }
            break;
        }
        int r, c;
        float fv;
        unsigned int tmp;
        if (fscanf(f, "%d %d", &r, &c) != 2)
            break;
        for (int j = 0; j < r * c; ++j)
            fscanf(f, "%f", &fv);
        for (int j = 0; j < r * c; ++j)
            fscanf(f, "%u %u %u %u %u %u %u", &tmp, &tmp, &tmp, &tmp, &tmp, &tmp, &tmp);
    }
    fclose(f);
    return res;
}

int get_element_from_binary_file(const char *filename, int index, size_t element_size, void *result)
{
    if (!filename || index < 0 || !result)
        return 0;
    FILE *f = fopen(filename, "rb");
    if (!f)
        return 0;

    long header_size = 2 * sizeof(int);
    long pos = header_size + (long)index * (long)element_size;
    if (fseek(f, pos, SEEK_SET) != 0)
    {
        fclose(f);
        return 0;
    }

    int ok = (fread(result, 1, element_size, f) == element_size);
    fclose(f);
    return ok;
}

Matrix2D *get_i_th_element(const char *filename, int index, int binary, size_t element_size)
{
    if (binary)
    {
        void *buf = malloc(element_size);
        if (!buf)
            return NULL;
        if (get_element_from_binary_file(filename, index, element_size, buf))
        {
            int r = ((int *)buf)[0];
            int c = ((int *)buf)[1];
            Matrix2D *m = unpack_buffer_to_matrix(buf, r, c);
            free(buf);
            return m;
        }
        free(buf);
        return NULL;
    }
    return get_element_from_text_file(filename, index);
}

void list_file_objects(const char *filename, int binary, size_t element_size)
{
    size_t total = count_objects_in_file(filename, binary, element_size);
    printf("Всего объектов в файле: %zu\n", total);
    for (size_t i = 0; i < total; ++i)
    {
        Matrix2D *m = get_i_th_element(filename, i, binary, element_size);
        if (m)
        {
            // Выводим номер с 1
            printf("Элемент %zu [%dx%d]:\n", i + 1, m->rows, m->cols);
            Matrix2D_print(m);
            Matrix2D_free(m);
        }
    }
}
