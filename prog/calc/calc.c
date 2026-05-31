#include "calc.h"

// Стеки для алгоритма вычисления выражений
static double num_stack[MAX_STACK]; // Стек операндов (числа)
static int num_top = -1;            // Указатель вершины стека чисел
static char op_stack[MAX_STACK];    // Стек операций и скобок
static int op_top = -1;             // казатель вершины стека операций

// СПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ДЛЯ РАБОТЫ СО СТЕКАМИ
static int is_op_empty(void) { return op_top == -1; }
static char peek_op(void) { return is_op_empty() ? '\0' : op_stack[op_top]; }
static void push_op(char op) { op_stack[++op_top] = op; }
static char pop_op(void) { return op_stack[op_top--]; }
static void push_num(double val) { num_stack[++num_top] = val; }
static double pop_num(void) { return num_stack[num_top--]; }

// ЛОГИКА ВЫЧИСЛЕНИЙ
static int precedence(char op)
{ // Возвращает приоритет операции. Чем больше число, тем выше приоритет у скобок он 0
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

static int apply_op(void)
{ // Выполнение операций
    char op = pop_op();
    double b = pop_num();
    double a = pop_num();
    switch (op)
    {
    case '+':
        push_num(a + b);
        break;
    case '-':
        push_num(a - b);
        break;
    case '*':
        push_num(a * b);
        break;
    case '/': // Проверка деления на ноль с учётом floating-point
        if (fabs(b) < 1e-9)
        {
            fprintf(stderr, "Ошибка: деление на ноль\n");
            return 1;
        }
        push_num(a / b);
        break;
    }
    return 0;
}

// ГЛАВНАЯ ФУНКЦИЯ ПАРСИНГА И ВЫЧИСЛЕНИЯ
int calc_evaluate(const char *expr, double *result)
{
    if (!expr || !result)
        return 1;

    int len = strlen(expr);
    int paren = 0; // Счётчик баланса скобок
    // 1. ПЕРВИЧНАЯ ВАЛИДАЦИЯ ВХОДНОЙ СТРОКИ
    for (int i = 0; i < len; i++)
    {
        if (expr[i] == '(')
            paren++;
        else if (expr[i] == ')')
            paren--;
        if (paren < 0)
        {
            fprintf(stderr, "Ошибка: лишняя закрывающая скобка ')'\n");
            return 1;
        }

        // Разрешаем только цифры, точку, операторы, скобки и пробелы
        if (!isdigit(expr[i]) && expr[i] != '.' && expr[i] != '+' && expr[i] != '-' &&
            expr[i] != '*' && expr[i] != '/' && expr[i] != '(' && expr[i] != ')' && !isspace(expr[i]))
        {
            fprintf(stderr, "Ошибка: недопустимый символ '%c'\n", expr[i]);
            return 1;
        }
    }
    if (paren != 0)
    {
        fprintf(stderr, "Ошибка: не сбалансированы скобки\n");
        return 1;
    }

    // 2. ОСНОВНОЙ ЦИКЛ РАЗБОРА ВЫРАЖЕНИЯ (Алгоритм двух стеков)
    int i = 0;
    int expect_operand = 1;

    while (i < len)
    {
        char c = expr[i];
        if (isspace(c))
        {
            i++;
            continue;
        }

        // Чтение числа
        if (isdigit(c) || c == '.')
        {
            char num_str[MAX_NUM_STR_LEN];
            int j = 0, dot_count = 0;
            while (i < len && (isdigit(expr[i]) || expr[i] == '.'))
            {
                if (j >= MAX_NUM_STR_LEN - 1)
                {
                    fprintf(stderr, "Ошибка: число слишком длинное\n");
                    return 1;
                }
                if (expr[i] == '.')
                    dot_count++;
                if (dot_count > 1)
                {
                    fprintf(stderr, "Ошибка: некорректное число\n");
                    return 1;
                }
                num_str[j++] = expr[i++];
            }
            num_str[j] = '\0';
            push_num(atof(num_str)); // Преобразуем строку в double и кладём в стек
            expect_operand = 0;      // После числа должен идти оператор или ')'
            continue;
        }

        // Открытая скобка
        if (c == '(')
        {
            push_op(c);
            expect_operand = 1;
            i++;
            continue;
        }

        // Закрытая скобка
        if (c == ')')
        {
            while (!is_op_empty() && peek_op() != '(')
            {
                if (apply_op() != 0)
                    return 1;
            }
            if (is_op_empty())
            {
                fprintf(stderr, "Ошибка: лишняя закрывающая скобка\n");
                return 1;
            }
            pop_op();
            expect_operand = 0;
            i++;
            continue;
        }

        // Операторы
        if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            if (c == '-' && expect_operand)
            { // Унарный минус
                push_num(0.0);
                push_op('-');
                expect_operand = 1;
                i++;
                continue;
            }
            if (expect_operand)
            { // Если ждали операнд, а пришёл оператор
                fprintf(stderr, "Ошибка: пропущен операнд перед '%c'\n", c);
                return 1;
            }
            while (!is_op_empty() && precedence(peek_op()) >= precedence(c) && peek_op() != '(')
            { // Пока приоритет оператора на вершине стека >= текущего, выполняем его
                if (apply_op() != 0)
                    return 1;
            }
            push_op(c);         // Кладём текущий оператор в стек
            expect_operand = 1; // После оператора ждём новый операнд
            i++;
            continue;
        }

        // Если символ не распознан
        fprintf(stderr, "Ошибка: неизвестный символ\n");
        return 1;
    }

    // 3. ДОРАБОТКА ОСТАВШИХСЯ ОПЕРАЦИЙ ПОСЛЕ КОНЦА СТРОКИ
    while (!is_op_empty())
    {
        if (peek_op() == '(')
        {
            fprintf(stderr, "Ошибка: не закрыта скобка '('\n");
            return 1;
        }
        if (apply_op() != 0)
            return 1;
    }

    //  В стеке должно остаться ровно одно число - результат
    if (num_top != 0)
    {
        fprintf(stderr, "Ошибка: некорректное выражение\n");
        return 1;
    }

    *result = pop_num();
    return 0;
}
