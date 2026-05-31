#include "matrix2d.h"

#define ACCURACY 0.000001f

Matrix2D *Matrix2D_create(int rows, int cols)
{
    if (rows <= 0 || cols <= 0)
    {
        printf("Ошибка: размеры должны быть положительными\n");
        return NULL;
    }

    Matrix2D *m = (Matrix2D *)malloc(sizeof(Matrix2D));
    if (!m)
    {
        printf("Ошибка выделения памяти\n");
        return NULL;
    }

    m->rows = rows;
    m->cols = cols;
    m->square = (rows == cols) ? 1 : 0;

    m->data = (float **)malloc(rows * sizeof(float *));
    if (!m->data)
    {
        free(m);
        printf("Ошибка выделения памяти\n");
        return NULL;
    }

    for (int i = 0; i < rows; i++)
    {
        m->data[i] = (float *)calloc(cols, sizeof(float));
        if (!m->data[i])
        {
            for (int j = 0; j < i; j++)
                free(m->data[j]);
            free(m->data);
            free(m);
            printf("Ошибка выделения памяти\n");
            return NULL;
        }
    }

    // Для практической №2 — светодиоды
    m->leds = (rgbled **)malloc(rows * sizeof(rgbled *));
    if (!m->leds)
    {
        for (int i = 0; i < rows; i++)
            free(m->data[i]);
        free(m->data);
        free(m);
        printf("Ошибка выделения памяти для LED\n");
        return NULL;
    }

    for (int i = 0; i < rows; i++)
    {
        m->leds[i] = (rgbled *)malloc(cols * sizeof(rgbled));
        if (!m->leds[i])
        {
            for (int j = 0; j < i; j++)
                free(m->leds[j]);
            free(m->leds);
            for (int j = 0; j < rows; j++)
                free(m->data[j]);
            free(m->data);
            free(m);
            printf("Ошибка выделения памяти для LED\n");
            return NULL;
        }
        for (int j = 0; j < cols; j++)
            led_set_all(&m->leds[i][j], 0, 0, 0, 50, 6500, 0, MODE_GLOW);
    }

    return m;
}

Matrix2D *Matrix2D_create_default(void)
{
    return Matrix2D_create(1, 1);
}

Matrix2D *Matrix2D_copy(const Matrix2D *other)
{
    if (!other)
    {
        printf("Ошибка: исходная матрица не существует\n");
        return NULL;
    }

    Matrix2D *m = Matrix2D_create(other->rows, other->cols);
    if (!m)
        return NULL;

    for (int i = 0; i < other->rows; i++)
        for (int j = 0; j < other->cols; j++)
        {
            m->data[i][j] = other->data[i][j];
            m->leds[i][j] = other->leds[i][j];
        }

    return m;
}

void Matrix2D_free(Matrix2D *m)
{
    if (m)
    {
        if (m->data)
        {
            for (int i = 0; i < m->rows; i++)
                if (m->data[i])
                    free(m->data[i]);
            free(m->data);
        }
        if (m->leds)
        {
            for (int i = 0; i < m->rows; i++)
                if (m->leds[i])
                    free(m->leds[i]);
            free(m->leds);
        }
        free(m);
    }
}

float Matrix2D_abs_sum(const Matrix2D *m)
{
    float sum = 0.0f;
    for (int i = 0; i < m->rows; i++)
        for (int j = 0; j < m->cols; j++)
        {
            float val = m->data[i][j];
            sum += (val < 0) ? -val : val;
        }
    return sum;
}

int Matrix2D_eq(const Matrix2D *a, const Matrix2D *b)
{
    if (a->rows != b->rows || a->cols != b->cols)
        return 0;

    for (int i = 0; i < a->rows; i++)
        for (int j = 0; j < a->cols; j++)
        {
            float diff = a->data[i][j] - b->data[i][j];
            float abs_diff = (diff < 0) ? -diff : diff;
            if (abs_diff > ACCURACY)
                return 0;
        }
    return 1;
}

int Matrix2D_ne(const Matrix2D *a, const Matrix2D *b)
{
    return !Matrix2D_eq(a, b);
}

int Matrix2D_gt(const Matrix2D *a, const Matrix2D *b)
{
    float absA = Matrix2D_abs_sum(a);
    float absB = Matrix2D_abs_sum(b);
    return (absA > absB + ACCURACY) ? 1 : 0;
}

int Matrix2D_lt(const Matrix2D *a, const Matrix2D *b)
{
    float absA = Matrix2D_abs_sum(a);
    float absB = Matrix2D_abs_sum(b);
    return (absA < absB - ACCURACY) ? 1 : 0;
}

int Matrix2D_ge(const Matrix2D *a, const Matrix2D *b)
{
    return !Matrix2D_lt(a, b);
}

int Matrix2D_le(const Matrix2D *a, const Matrix2D *b)
{
    return !Matrix2D_gt(a, b);
}

void Matrix2D_input(Matrix2D *m)
{
    printf("Введите %d элементов матрицы %dx%d:\n", m->rows * m->cols, m->rows, m->cols);
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
        {
            printf("  [%d][%d] = ", i, j);
            if (scanf("%f", &m->data[i][j]) != 1)
            {
                printf("Ошибка ввода\n");
                int c;
                while ((c = getchar()) != '\n' && c != EOF)
                    ;
                return;
            }
        }
    }
}

void Matrix2D_print(const Matrix2D *m)
{
    printf("Матрица %dx%d:\n", m->rows, m->cols);
    for (int i = 0; i < m->rows; i++)
    {
        printf("  [");
        for (int j = 0; j < m->cols; j++)
        {
            printf("%8.3f", m->data[i][j]);
            if (j < m->cols - 1)
                printf(" ");
        }
        printf("]\n");
    }
}

void Matrix2D_set(Matrix2D *m, int row, int col, float val)
{
    if (row < 0 || row >= m->rows || col < 0 || col >= m->cols)
    {
        printf("Ошибка: индекс вне диапазона\n");
        return;
    }
    m->data[row][col] = val;
}

float Matrix2D_get(const Matrix2D *m, int row, int col)
{
    if (row < 0 || row >= m->rows || col < 0 || col >= m->cols)
    {
        printf("Ошибка: индекс вне диапазона\n");
        return 0.0f;
    }
    return m->data[row][col];
}

void Matrix2D_inc(Matrix2D *m)
{
    for (int i = 0; i < m->rows; i++)
        for (int j = 0; j < m->cols; j++)
            m->data[i][j] += 1.0f;
}

void Matrix2D_dec(Matrix2D *m)
{
    for (int i = 0; i < m->rows; i++)
        for (int j = 0; j < m->cols; j++)
            m->data[i][j] -= 1.0f;
}

void Matrix2D_fill_random(Matrix2D *m, float min, float max)
{
    static int seeded = 0;
    if (!seeded)
    {
        srand((unsigned int)time(NULL));
        seeded = 1;
    }
    float range = max - min;
    for (int i = 0; i < m->rows; i++)
        for (int j = 0; j < m->cols; j++)
            m->data[i][j] = min + range * (float)rand() / (RAND_MAX + 1.0f);
}

Matrix2D *Matrix2D_get_row(const Matrix2D *m, int row_idx)
{
    if (row_idx < 0 || row_idx >= m->rows)
    {
        printf("Ошибка: индекс строки вне диапазона\n");
        return NULL;
    }

    Matrix2D *row = Matrix2D_create(1, m->cols);
    if (!row)
        return NULL;

    for (int j = 0; j < m->cols; j++)
        row->data[0][j] = m->data[row_idx][j];

    return row;
}

Matrix2D *Matrix2D_get_col(const Matrix2D *m, int col_idx)
{
    if (col_idx < 0 || col_idx >= m->cols)
    {
        printf("Ошибка: индекс столбца вне диапазона\n");
        return NULL;
    }

    Matrix2D *col = Matrix2D_create(m->rows, 1);
    if (!col)
        return NULL;

    for (int i = 0; i < m->rows; i++)
        col->data[i][0] = m->data[i][col_idx];

    return col;
}

Matrix2D *Matrix2D_transpose(const Matrix2D *m)
{
    Matrix2D *t = Matrix2D_create(m->cols, m->rows);
    if (!t)
        return NULL;

    for (int i = 0; i < m->rows; i++)
        for (int j = 0; j < m->cols; j++)
            t->data[j][i] = m->data[i][j];

    return t;
}

static Matrix2D *Matrix2D_minor(const Matrix2D *m, int skip_r, int skip_c)
{
    if (!m || !m->square || m->rows <= 1)
        return NULL;

    int n = m->rows - 1;
    Matrix2D *minor = Matrix2D_create(n, n);
    if (!minor)
        return NULL;

    int di = 0;
    for (int i = 0; i < m->rows; i++)
    {
        if (i == skip_r)
            continue;
        int dj = 0;
        for (int j = 0; j < m->cols; j++)
        {
            if (j == skip_c)
                continue;
            minor->data[di][dj++] = m->data[i][j];
        }
        di++;
    }
    return minor;
}

float Matrix2D_det(const Matrix2D *m)
{
    if (!m->square)
    {
        printf("Ошибка: определитель только для квадратных матриц\n");
        return 0.0f;
    }

    int n = m->rows;
    float det = 0.0f;

    if (n == 1)
        det = m->data[0][0];
    else if (n == 2)
        det = m->data[0][0] * m->data[1][1] - m->data[0][1] * m->data[1][0];
    else
    {
        for (int j = 0; j < n; j++)
        {
            Matrix2D *minor = Matrix2D_minor(m, 0, j);
            if (minor)
            {
                float minor_det = Matrix2D_det(minor);
                if (j % 2 == 0)
                    det += m->data[0][j] * minor_det;
                else
                    det -= m->data[0][j] * minor_det;
                Matrix2D_free(minor);
            }
        }
    }
    return det;
}

// ========== ПРАКТИЧЕСКАЯ РАБОТА №2 ==========

void Matrix2D_set_led(Matrix2D *m, int row, int col, int r, int g, int b,
                      int bright, int temp, int ctrl, led_mode mode)
{
    if (row < 0 || row >= m->rows || col < 0 || col >= m->cols)
    {
        printf("Ошибка: индекс вне диапазона\n");
        return;
    }
    led_set_all(&m->leds[row][col], r, g, b, bright, temp, ctrl, mode);
}

void Matrix2D_print_led(const Matrix2D *m, int row, int col)
{
    if (row < 0 || row >= m->rows || col < 0 || col >= m->cols)
    {
        printf("Ошибка: индекс вне диапазона\n");
        return;
    }

    rgbled *led = &m->leds[row][col];
    printf("LED[%d][%d]: [%3u %3u %3u]\n", row, col,
           led->red, led->green, led->blue);
}

void Matrix2D_print_all(const Matrix2D *m)
{
    printf("Матрица %dx%d:\n", m->rows, m->cols);

    printf("Значения (Практическая №1):\n");
    for (int i = 0; i < m->rows; i++)
    {
        printf("Строка %d: [", i);
        for (int j = 0; j < m->cols; j++)
        {
            printf("%8.3f", m->data[i][j]);
            if (j < m->cols - 1)
                printf(" ");
        }
        printf("]\n");
    }

    printf("Цвета LED (Практическая №2):\n");
    for (int i = 0; i < m->rows; i++)
    {
        printf("Строка %d: ", i);
        for (int j = 0; j < m->cols; j++)
        {
            rgbled *led = &m->leds[i][j];
            printf("[%3u %3u %3u] ", led->red, led->green, led->blue);
        }
        printf("\n");
    }
}
