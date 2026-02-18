#include "matrix2d.h"

#define EPSILON 1e-6f  // точность сравнения

// Очистка буфера ввода (до конца строки)
void clear_input()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

// Проверка, создана ли матрица (не NULL)
bool is_matrix_created(const matrix2d *m)
{
    if (!m)
    {
        printf("Матрица не создана!\n");
        return false;
    }
    return true;
}

// Сумма квадратов всех элементов
float matrix2d_norm(const matrix2d *m)
{
    if (!m)
        return 0.0f;
    float sum = 0.0f;
    for (int i = 0; i < m->rows; i++)
        for (int j = 0; j < m->cols; j++)
            sum += m->data[i][j] * m->data[i][j];
    return sum;
}

// Создать матрицу 1x1
matrix2d *matrix2d_default()
{
    return matrix2d_create(1, 1);
}

// Создать матрицу rows x cols (заполнить нулями)
matrix2d *matrix2d_create(int rows, int cols)
{
    if (rows <= 0 || cols <= 0)
    {
        printf("Ошибка: размеры должны быть положительными!\n");
        return NULL;
    }

    matrix2d *m = (matrix2d *)malloc(sizeof(matrix2d));
    if (!m)
    {
        printf("Ошибка выделения памяти!\n");
        return NULL;
    }

    m->rows = rows;
    m->cols = cols;
    m->has_diag = (rows == cols);  // запоминаем, квадратная ли

    // Выделяем память под строки
    m->data = (float **)malloc(rows * sizeof(float *));
    if (!m->data)
    {
        free(m);
        printf("Ошибка выделения памяти!\n");
        return NULL;
    }

    // Для каждой строки выделяем память под столбцы
    for (int i = 0; i < rows; i++)
    {
        m->data[i] = (float *)calloc(cols, sizeof(float));
        if (!m->data[i])
        {
            // Если ошибка - освобождаем всё, что успели выделить
            for (int j = 0; j < i; j++)
                free(m->data[j]);
            free(m->data);
            free(m);
            printf("Ошибка выделения памяти!\n");
            return NULL;
        }
    }

    return m;
}

// Создать копию матрицы
matrix2d *matrix2d_copy(const matrix2d *src)
{
    if (!src)
    {
        printf("Ошибка: исходная матрица не существует!\n");
        return NULL;
    }

    matrix2d *m = matrix2d_create(src->rows, src->cols);
    if (!m)
        return NULL;

    // Копируем данные построчно
    for (int i = 0; i < src->rows; i++)
        memcpy(m->data[i], src->data[i], src->cols * sizeof(float));

    return m;
}

// Освободить память матрицы
void matrix2d_destroy(matrix2d *m)
{
    if (!m)
        return;

    // Сначала удаляем каждую строку
    for (int i = 0; i < m->rows; i++)
        free(m->data[i]);
    free(m->data);  // потом массив указателей
    free(m);        // и саму структуру
}

// Сравнение на равенство (с учётом EPSILON)
bool matrix2d_eq(const matrix2d *m1, const matrix2d *m2)
{
    if (!m1 || !m2)
        return false;
    if (m1->rows != m2->rows || m1->cols != m2->cols)
        return false;

    for (int i = 0; i < m1->rows; i++)
        for (int j = 0; j < m1->cols; j++)
            if (fabsf(m1->data[i][j] - m2->data[i][j]) > EPSILON)
                return false;
    return true;
}

// Не равно
bool matrix2d_ne(const matrix2d *m1, const matrix2d *m2)
{
    return !matrix2d_eq(m1, m2);
}

// Меньше (по норме)
bool matrix2d_lt(const matrix2d *m1, const matrix2d *m2)
{
    return (matrix2d_norm(m1) < matrix2d_norm(m2) - EPSILON);
}

// Больше (по норме)
bool matrix2d_gt(const matrix2d *m1, const matrix2d *m2)
{
    return (matrix2d_norm(m1) > matrix2d_norm(m2) + EPSILON);
}

// Меньше или равно
bool matrix2d_le(const matrix2d *m1, const matrix2d *m2)
{
    return !matrix2d_gt(m1, m2);
}

// Больше или равно
bool matrix2d_ge(const matrix2d *m1, const matrix2d *m2)
{
    return !matrix2d_lt(m1, m2);
}

// Ввод элементов с клавиатуры
void matrix2d_input(matrix2d *m)
{
    if (!m)
    {
        printf("Ошибка: матрица не создана!\n");
        return;
    }

    printf("Введите %d элементов:\n", m->rows * m->cols);
    for (int i = 0; i < m->rows; i++)
        for (int j = 0; j < m->cols; j++)
        {
            printf("[%d][%d] = ", i, j);
            scanf("%f", &m->data[i][j]);
        }
}

// Вывести матрицу на экран
void matrix2d_print(const matrix2d *m)
{
    if (!m)
    {
        printf("[NULL matrix]\n");
        return;
    }

    printf("Матрица %dx%d [%s диагональ]:\n",
           m->rows, m->cols, m->has_diag ? "с" : "без");

    for (int i = 0; i < m->rows; i++)
    {
        printf("[");
        for (int j = 0; j < m->cols; j++)
        {
            printf("%8.3f", m->data[i][j]);
            if (j < m->cols - 1)
                printf(" ");
        }
        printf("]\n");
    }
}

// Изменить элемент
void matrix2d_set(matrix2d *m, int row, int col, float value)
{
    if (!m)
    {
        printf("Ошибка: матрица не создана!\n");
        return;
    }
    if (row < 0 || row >= m->rows || col < 0 || col >= m->cols)
    {
        printf("Ошибка: индекс вне диапазона!\n");
        return;
    }
    m->data[row][col] = value;
}

// Получить элемент
float matrix2d_get(const matrix2d *m, int row, int col)
{
    if (!m || row < 0 || row >= m->rows || col < 0 || col >= m->cols)
    {
        printf("Ошибка доступа к элементу!\n");
        return 0.0f;
    }
    return m->data[row][col];
}

// Увеличить все элементы на 1
void matrix2d_inc(matrix2d *m)
{
    if (!m)
    {
        printf("Ошибка: матрица не создана!\n");
        return;
    }
    for (int i = 0; i < m->rows; i++)
        for (int j = 0; j < m->cols; j++)
            m->data[i][j] += 1.0f;
}

// Уменьшить все элементы на 1
void matrix2d_dec(matrix2d *m)
{
    if (!m)
    {
        printf("Ошибка: матрица не создана!\n");
        return;
    }
    for (int i = 0; i < m->rows; i++)
        for (int j = 0; j < m->cols; j++)
            m->data[i][j] -= 1.0f;
}

// Заполнить случайными числами от min до max
void matrix2d_fill_random(matrix2d *m, float min, float max)
{
    if (!m)
    {
        printf("Ошибка: матрица не создана!\n");
        return;
    }

    static bool seeded = false;
    if (!seeded)
    {
        srand((unsigned int)time(NULL));  // инициализация генератора
        seeded = true;
    }

    float range = max - min;
    for (int i = 0; i < m->rows; i++)
        for (int j = 0; j < m->cols; j++)
            m->data[i][j] = min + range * (float)rand() / (RAND_MAX + 1.0f);
}

// Создать минор (без указанных строки и столбца) - вспомогательная
static matrix2d *_matrix2d_minor(const matrix2d *m, int skip_row, int skip_col)
{
    if (!m || !m->has_diag || m->rows <= 1)
        return NULL;

    int n = m->rows - 1;
    matrix2d *minor = matrix2d_create(n, n);
    if (!minor)
        return NULL;

    int di = 0;
    for (int i = 0; i < m->rows; i++)
    {
        if (i == skip_row) continue;
        int dj = 0;
        for (int j = 0; j < m->cols; j++)
        {
            if (j == skip_col) continue;
            minor->data[di][dj++] = m->data[i][j];
        }
        di++;
    }

    return minor;
}

// Получить строку как матрицу 1xN
matrix2d *matrix2d_get_row(const matrix2d *m, int row_idx)
{
    if (!m || row_idx < 0 || row_idx >= m->rows)
    {
        printf("Ошибка получения строки!\n");
        return NULL;
    }

    matrix2d *row = matrix2d_create(1, m->cols);
    if (row)
        memcpy(row->data[0], m->data[row_idx], m->cols * sizeof(float));
    return row;
}

// Получить столбец как матрицу Mx1
matrix2d *matrix2d_get_col(const matrix2d *m, int col_idx)
{
    if (!m || col_idx < 0 || col_idx >= m->cols)
    {
        printf("Ошибка получения столбца!\n");
        return NULL;
    }

    matrix2d *col = matrix2d_create(m->rows, 1);
    if (col)
        for (int i = 0; i < m->rows; i++)
            col->data[i][0] = m->data[i][col_idx];
    return col;
}

// Транспонировать матрицу
matrix2d *matrix2d_transpose(const matrix2d *m)
{
    if (!m)
    {
        printf("Ошибка: матрица не создана!\n");
        return NULL;
    }

    matrix2d *t = matrix2d_create(m->cols, m->rows);
    if (!t)
        return NULL;

    for (int i = 0; i < m->rows; i++)
        for (int j = 0; j < m->cols; j++)
            t->data[j][i] = m->data[i][j];

    return t;
}

// Определитель (рекурсивно)
float matrix2d_determinant(const matrix2d *m)
{
    if (!m || !m->has_diag)
    {
        printf("Определитель только для квадратных!\n");
        return 0.0f;
    }

    int n = m->rows;

    if (n == 1)
        return m->data[0][0];
    if (n == 2)
        return m->data[0][0] * m->data[1][1] - m->data[0][1] * m->data[1][0];

    float det = 0.0f;
    for (int j = 0; j < n; j++)
    {
        matrix2d *minor = _matrix2d_minor(m, 0, j);
        if (minor)
        {
            float subdet = matrix2d_determinant(minor);
            det += ((j % 2) ? -1.0f : 1.0f) * m->data[0][j] * subdet;
            matrix2d_destroy(minor);
        }
    }

    return det;
}

// Обратная матрица (через миноры)
matrix2d *matrix2d_inverse(const matrix2d *m)
{
    if (!m || !m->has_diag)
    {
        printf("Обратная только для квадратных!\n");
        return NULL;
    }

    float det = matrix2d_determinant(m);
    if (fabsf(det) < EPSILON)
    {
        printf("Матрица вырожденная!\n");
        return NULL;
    }

    int n = m->rows;
    matrix2d *inv = matrix2d_create(n, n);
    if (!inv)
        return NULL;

    // Простые случаи
    if (n == 1)
    {
        inv->data[0][0] = 1.0f / m->data[0][0];
        return inv;
    }
    if (n == 2)
    {
        inv->data[0][0] = m->data[1][1] / det;
        inv->data[0][1] = -m->data[0][1] / det;
        inv->data[1][0] = -m->data[1][0] / det;
        inv->data[1][1] = m->data[0][0] / det;
        return inv;
    }

    // Общий случай
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix2d *minor = _matrix2d_minor(m, i, j);
            if (minor)
            {
                float subdet = matrix2d_determinant(minor);
                inv->data[j][i] = (((i + j) % 2) ? -1.0f : 1.0f) * subdet / det;
                matrix2d_destroy(minor);
            }
        }
    }

    return inv;
}

// ---------- Функции меню ----------

// Меню создания матрицы
void menu_create_matrix(matrix2d **m)
{
    if (*m)
    {
        printf("Матрица уже существует! Уничтожьте её сначала.\n");
        return;
    }

    int rows, cols;
    printf("Строк: ");
    scanf("%d", &rows);
    clear_input();
    printf("Столбцов: ");
    scanf("%d", &cols);
    clear_input();

    *m = matrix2d_create(rows, cols);
    if (!*m) return;

    printf("Ввести данные вручную? (1-да, 0-нет): ");
    int choice;
    scanf("%d", &choice);
    clear_input();

    if (choice == 1)
        matrix2d_input(*m);

    printf("Матрица создана!\n");
    matrix2d_print(*m);
}

// Меню вывода
void menu_print_matrix(const matrix2d *m)
{
    if (!is_matrix_created(m)) return;
    printf("\n");
    matrix2d_print(m);
}

// Меню случайного заполнения
void menu_fill_random(matrix2d *m)
{
    if (!is_matrix_created(m)) return;

    float min, max;
    printf("Мин: ");
    scanf("%f", &min);
    clear_input();
    printf("Макс: ");
    scanf("%f", &max);
    clear_input();

    if (min >= max)
    {
        printf("Мин должно быть меньше макс!\n");
        return;
    }

    matrix2d_fill_random(m, min, max);
    matrix2d_print(m);
}

// Меню изменения элемента
void menu_set_element(matrix2d *m)
{
    if (!is_matrix_created(m)) return;

    matrix2d_print(m);
    int row, col;
    float value;

    printf("Строка (0-%d): ", m->rows-1);
    scanf("%d", &row);
    clear_input();
    printf("Столбец (0-%d): ", m->cols-1);
    scanf("%d", &col);
    clear_input();
    printf("Новое значение: ");
    scanf("%f", &value);
    clear_input();

    matrix2d_set(m, row, col, value);
    matrix2d_print(m);
}

// Меню инкремента
void menu_increment(matrix2d *m)
{
    if (!is_matrix_created(m)) return;
    matrix2d_inc(m);
    printf("Инкремент выполнен\n");
    matrix2d_print(m);
}

// Меню декремента
void menu_decrement(matrix2d *m)
{
    if (!is_matrix_created(m)) return;
    matrix2d_dec(m);
    printf("Декремент выполнен\n");
    matrix2d_print(m);
}

// Меню получения строки
void menu_get_row(const matrix2d *m)
{
    if (!is_matrix_created(m)) return;

    int idx;
    printf("Номер строки (0-%d): ", m->rows-1);
    scanf("%d", &idx);
    clear_input();

    matrix2d *row = matrix2d_get_row(m, idx);
    if (row)
    {
        matrix2d_print(row);
        matrix2d_destroy(row);
    }
}

// Меню получения столбца
void menu_get_col(const matrix2d *m)
{
    if (!is_matrix_created(m)) return;

    int idx;
    printf("Номер столбца (0-%d): ", m->cols-1);
    scanf("%d", &idx);
    clear_input();

    matrix2d *col = matrix2d_get_col(m, idx);
    if (col)
    {
        matrix2d_print(col);
        matrix2d_destroy(col);
    }
}

// Меню транспонирования
void menu_transpose(matrix2d **m)
{
    if (!is_matrix_created(*m)) return;

    matrix2d *t = matrix2d_transpose(*m);
    if (!t) return;

    printf("Транспонированная:\n");
    matrix2d_print(t);

    printf("Заменить исходную? (1-да, 0-нет): ");
    int choice;
    scanf("%d", &choice);
    clear_input();

    if (choice == 1)
    {
        matrix2d_destroy(*m);
        *m = t;
    }
    else
        matrix2d_destroy(t);
}

// Меню определителя
void menu_determinant(const matrix2d *m)
{
    if (!is_matrix_created(m)) return;
    if (!m->has_diag)
    {
        printf("Матрица не квадратная!\n");
        return;
    }

    float det = matrix2d_determinant(m);
    printf("Определитель = %.6f\n", det);
}

// Меню обратной матрицы
void menu_inverse(const matrix2d *m)
{
    if (!is_matrix_created(m)) return;
    if (!m->has_diag)
    {
        printf("Матрица не квадратная!\n");
        return;
    }

    float det = matrix2d_determinant(m);
    printf("Определитель = %.6f\n", det);

    if (fabsf(det) < 1e-6f)
    {
        printf("Вырожденная матрица, обратной нет\n");
        return;
    }

    matrix2d *inv = matrix2d_inverse(m);
    if (inv)
    {
        printf("Обратная матрица:\n");
        matrix2d_print(inv);
        matrix2d_destroy(inv);
    }
}

// Меню сравнения двух матриц
void menu_compare(const matrix2d *m1, const matrix2d *m2)
{
    if (!is_matrix_created(m1) || !is_matrix_created(m2))
    {
        printf("Обе матрицы должны быть созданы\n");
        return;
    }

    printf("A == B: %s\n", matrix2d_eq(m1, m2) ? "да" : "нет");
    printf("A != B: %s\n", matrix2d_ne(m1, m2) ? "да" : "нет");
    printf("A > B:  %s\n", matrix2d_gt(m1, m2) ? "да" : "нет");
    printf("A < B:  %s\n", matrix2d_lt(m1, m2) ? "да" : "нет");
    printf("A >= B: %s\n", matrix2d_ge(m1, m2) ? "да" : "нет");
    printf("A <= B: %s\n", matrix2d_le(m1, m2) ? "да" : "нет");
}

// Меню удаления матрицы
void menu_destroy(matrix2d **m)
{
    if (!*m)
    {
        printf("Матрица не создана!\n");
        return;
    }

    matrix2d_destroy(*m);
    *m = NULL;
    printf("Матрица удалена\n");
}