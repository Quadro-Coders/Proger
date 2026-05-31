#include <stdio.h>
#include <string.h>
#include "calc.h"

// Функция для обработки присваивания (x=5)
// Она должна быть отдельной, так как меняет переменные
double parse_assignment(void)
{
    skip_spaces();

    // Если начинается с буквы и дальше стоит '='
    if (isalpha(*input_ptr))
    {
        char var_name = tolower(*input_ptr);
        const char *temp_ptr = input_ptr + 1;
        // Пропускаем пробелы чтобы проверить '='
        while (*temp_ptr == ' ')
            temp_ptr++;

        if (*temp_ptr == '=')
        {
            input_ptr += 2; // пропускаем "x="
            double value = parse_expression();
            variables[var_name - 'a'] = value;
            return value;
        }
    }
    // Если не присваивание, считаем как обычное выражение
    return parse_expression();
}

void print_banner()
{
    printf("  КАЛЬКУЛЯТОР (Режим: Интерактивный)\n");
    printf("  Поддержка: + - * / %% ^ & | << >>\n");
    printf("  Переменные: a-z (например x=5)\n");
    printf("  Введите 'exit' для выхода\n");
}

int main(int argc, char *argv[])
{
    // Инициализация переменных нулями
    for (int i = 0; i < 26; i++)
        variables[i] = 0;

    // --- РЕЖИМ 1: КОМАНДНАЯ СТРОКА (По методичке) ---
    if (argc > 1)
    {
        input_ptr = argv[1];

        // Вычисляем
        double result = parse_assignment();

        // Проверка, что строка закончилась (валидация по методичке)
        skip_spaces();
        if (*input_ptr != '\0')
        {
            error_exit("Лишние символы в конце выражения");
        }

        // Вывод результата (красивый формат: целые без .0)
        if (result == (long long)result)
            printf("%lld\n", (long long)result);
        else
            printf("%g\n", result);

        return 0; // Успех
    }

    // --- РЕЖИМ 2: ИНТЕРАКТИВНЫЙ (Как на картинке) ---
    char buffer[256];
    print_banner();

    while (1)
    {
        printf("> ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
            break;

        // Удаляем перенос строки
        buffer[strcspn(buffer, "\n")] = 0;

        if (strlen(buffer) == 0)
            continue;
        if (strcmp(buffer, "exit") == 0 || strcmp(buffer, "quit") == 0)
            break;
        if (strcmp(buffer, "help") == 0)
        {
            print_banner();
            continue;
        }

        input_ptr = buffer;

        // В интерактивном режиме мы не хотим, чтобы программа закрывалась при ошибке (exit(1))
        // Поэтому используем setjmp/longjmp или просто ловим ошибки мягко.
        // Для простоты 1 курса: если ошибка - просто пишем и просим заново.
        // Но parse_primary вызывает exit(1). Чтобы это обойти, можно убрать exit(1)
        // и возвращать ошибку, но это усложнит код.
        // Оставим как есть: в интерактивном режиме ошибка закроет программу.
        // *УЛУЧШЕНИЕ:* Сделаем мягкую ошибку для интерактивного режима.

        // Временный хак для студента: в интерактивном режиме ошибки не фатальны?
        // Нет, проще оставить exit(1), так как в методичке требуется код возврата 1.
        // Но для удобства я добавлю простую проверку.

        double result = parse_assignment();

        skip_spaces();
        if (*input_ptr != '\0')
        {
            fprintf(stderr, "Ошибка: лишние символы '%s'\n", input_ptr);
            continue; // Не выходим, а просим новое
        }

        if (result == (long long)result)
            printf("%lld\n", (long long)result);
        else
            printf("%g\n", result);
    }

    return 0;
}
