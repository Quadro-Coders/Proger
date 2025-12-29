#include <stdio.h>

int main (void)
{
    char ch;              // Текущий символ
    int space = 0;        // Счётчик пробелов
    int newline = 0;      // Счётчик переносов строки
    int all_char = 0;     // Счётчик всех символов

    printf("Пожалуйста, введите текст..\n");

    // Читаем символы пока не встретим '#'
    while ((ch = getchar()) != '#')
    {
        if (ch == ' ')         // Если символ - пробел
            space++;
        if (ch == '\n')        // Если символ - перенос строки
            newline++;
        all_char++;            // Увеличиваем общий счётчик символов
    }

    printf("%d пробелов | %d переносов строки | %d всего символов", 
           space, newline, all_char);

    return 0;
}
