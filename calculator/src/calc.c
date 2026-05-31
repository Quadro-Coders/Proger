#include "calc.h"

double variables[26];
const char *input_ptr;

// Функция для выхода с ошибкой (требование методички)
void error_exit(const char *msg) {
    fprintf(stderr, "Ошибка: %s\n", msg);
    exit(1);
}

void skip_spaces(void) {
    while (*input_ptr == ' ' || *input_ptr == '\t') {
        input_ptr++;
    }
}

// Первичный разбор: числа, переменные, скобки, унарный минус
double parse_primary(void) {
    skip_spaces();

    // 1. Скобки
    if (*input_ptr == '(') {
        input_ptr++;
        double result = parse_expression();
        skip_spaces();
        if (*input_ptr != ')') {
            error_exit("Не закрыта скобка ')'");
        }
        input_ptr++;
        return result;
    }

    // 2. Унарный минус
    if (*input_ptr == '-') {
        input_ptr++;
        return -parse_primary();
    }

    // 3. Унарный плюс
    if (*input_ptr == '+') {
        input_ptr++;
        return parse_primary();
    }

    // 4. Переменные (буквы a-z)
    if (isalpha(*input_ptr)) {
        char var_name = tolower(*input_ptr);
        // Проверяем, не присваивание ли это (например x=5)
        // Но в parse_primary мы только ЧИТАЕМ значение. 
        // Присваивание обрабатывается выше в parse_expression
        
        // Проверяем, есть ли следующая буква (значит это имя переменной)
        // Для простоты считаем одну букву переменной
        input_ptr++;
        return variables[var_name - 'a'];
    }

    // 5. Числа (вещественные)
    if (isdigit(*input_ptr) || *input_ptr == '.') {
        char num_str[64];
        int i = 0;
        while (isdigit(*input_ptr) || *input_ptr == '.') {
            num_str[i++] = *input_ptr++;
        }
        num_str[i] = '\0';
        return atof(num_str);
    }

    error_exit("Неожиданный символ");
    return 0;
}

// Степень (приоритет выше умножения) - используем как побитовое ИЛИ ^ или степень
// В методе 2.2 обычно нет степени, но для твоего функционала оставим
double parse_power(void) {
    double left = parse_primary();
    skip_spaces();
    
    // Если это побитовое ИЛИ ^
    if (*input_ptr == '^') {
        input_ptr++;
        double right = parse_power(); // Правоассоциативность
        return (double)((int)left ^ (int)right);
    }
    return left;
}

// Умножение и деление (и битовые сдвиги << >>)
double parse_term(void) {
    double left = parse_power();

    while (1) {
        skip_spaces();
        char op = *input_ptr;

        if (op == '*' || op == '/' || op == '%') {
            input_ptr++;
            double right = parse_power();

            if (op == '*') left *= right;
            else if (op == '/') {
                if (right == 0.0) error_exit("Деление на ноль");
                left /= right;
            }
            else if (op == '%') {
                // Остаток только для целых
                left = (double)((int)left % (int)right);
            }
        } 
        // Битовые сдвиги (приоритет как у умножения в твоей картинке)
        else if (op == '<' && *(input_ptr + 1) == '<') {
            input_ptr += 2;
            double right = parse_power();
            left = (double)((int)left << (int)right);
        }
        else if (op == '>' && *(input_ptr + 1) == '>') {
            input_ptr += 2;
            double right = parse_power();
            left = (double)((int)left >> (int)right);
        }
        else {
            break;
        }
    }
    return left;
}

// Сложение и вычитание (и битовые & |)
double parse_expression(void) {
    double left = parse_term();

    while (1) {
        skip_spaces();
        char op = *input_ptr;

        if (op == '+' || op == '-') {
            input_ptr++;
            double right = parse_term();
            if (op == '+') left += right;
            else left -= right;
        }
        // Побитовое И &
        else if (op == '&') {
            input_ptr++;
            double right = parse_term();
            left = (double)((int)left & (int)right);
        }
        // Побитовое ИЛИ |
        else if (op == '|') {
            input_ptr++;
            double right = parse_term();
            left = (double)((int)left | (int)right);
        }
        else {
            break;
        }
    }
    return left;
}