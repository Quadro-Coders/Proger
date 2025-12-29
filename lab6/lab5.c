#include <stdio.h>

int main (void) {

    char ch;
    int count=0;

    printf("Введите что-нибудь (# для выхода)\n");

    while ((ch = getchar()) != '#')
    {   
        switch (ch) {
            case '.':
            {
                count++;
                putchar('!');
                break;
            }
            case '!':
            {
                putchar('!');
                putchar('!');
                count++;
                break;
            }
            default:
            printf("%c", ch);
        }
    }
    printf("Было выполнено %d замен(ы)", count);

    return 0;
}