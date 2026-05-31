#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_STACK 256      // Макс. количество операндов/операторов, которые могут находиться в стеке одновременно во время вычисления
#define MAX_NUM_STR_LEN 64 // Макс. длина строки одного числа

//  СТЕКИ
double num_stack[MAX_STACK];
int num_top = -1;

char op_stack[MAX_STACK];
int op_top = -1;

void push_num(double val)
{
    if (num_top >= MAX_STACK - 1)
    {
        fprintf(stderr, "Ошибка: переполнение стека чисел\n");
        exit(1);
    }
    num_stack[++num_top] = val;
}

double pop_num()
{
    if (num_top < 0)
    {
        fprintf(stderr, "Ошибка: некорректная структура выражения\n");
        exit(1);
    }
    return num_stack[num_top--];
}

void push_op(char op)
{
    if (op_top >= MAX_STACK - 1)
    {
        fprintf(stderr, "Ошибка: переполнение стека операций\n");
        exit(1);
    }
    op_stack[++op_top] = op;
}

char pop_op()
{
    if (op_top < 0)
        return '\0';
    return op_stack[op_top--];
}

char peek_op()
{
    if (op_top < 0)
        return '\0';
    return op_stack[op_top];
}

int is_op_empty() { return op_top == -1; }

//  ЛОГИКА
int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

void apply_op()
{
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
    case '/':
        if (fabs(b) < 1e-9)
        {
            fprintf(stderr, "Ошибка: деление на ноль\n");
            exit(1);
        }
        push_num(a / b);
        break;
    }
}

//  ГЛАВНАЯ ФУНКЦИЯ
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Использование: %s \"выражение\"\n", argv[0]);
        printf("Пример: %s \"(1.5 + 2) * 3\"\n", argv[0]);
        return 1;
    }

    const char *expr = argv[1];
    int len = strlen(expr);

    // 1. Базовая валидация символов и баланса скобок
    int paren = 0;
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

    // 2. Алгоритм вычисления с двумя стеками
    int i = 0;
    int expect_operand = 1; // 1 = ждём операнд, 0 = ждём оператор или ')'

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
                    fprintf(stderr, "Ошибка: некорректное число (две точки)\n");
                    return 1;
                }
                num_str[j++] = expr[i++];
            }
            num_str[j] = '\0';
            push_num(atof(num_str));
            expect_operand = 0;
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
                apply_op();
            }
            if (is_op_empty())
            {
                fprintf(stderr, "Ошибка: лишняя закрывающая скобка\n");
                return 1;
            }
            pop_op(); // убираем '('
            expect_operand = 0;
            i++;
            continue;
        }

        // Операторы
        if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            // Обработка унарного минуса (например: -5 или (-3))
            if (c == '-' && expect_operand)
            {
                push_num(0.0); // превращаем в 0 - x
                push_op('-');
                expect_operand = 1;
                i++;
                continue;
            }

            if (expect_operand)
            {
                fprintf(stderr, "Ошибка: пропущен операнд перед '%c'\n", c);
                return 1;
            }

            // Выталкиваем операции с большим или равным приоритетом
            while (!is_op_empty() && precedence(peek_op()) >= precedence(c) && peek_op() != '(')
            {
                apply_op();
            }
            push_op(c);
            expect_operand = 1;
            i++;
            continue;
        }

        fprintf(stderr, "Ошибка: неизвестный символ\n");
        return 1;
    }

    // 3. Обработка оставшихся операций
    while (!is_op_empty())
    {
        if (peek_op() == '(')
        {
            fprintf(stderr, "Ошибка: не закрыта скобка '('\n");
            return 1;
        }
        apply_op();
    }

    if (num_top != 0)
    {
        fprintf(stderr, "Ошибка: некорректное выражение\n");
        return 1;
    }

    // 4. Вывод результата
    double result = pop_num();
    // Форматирование: целые числа без .0, вещественные без лишних нулей
    if (result == (long long)result)
        printf("%lld\n", (long long)result);
    else
        printf("%g\n", result);

    return 0;
}
