#include <stdio.h>
int main (void) {

    char ch;
    int count=0;

    printf("что-нибудь (# для выхода)\n");

    while ((ch = getchar()) != '#')
    {
        if (ch == '.') {
            ch = '!';
            count++;
            printf("%c", ch);
        }
        else if (ch == '!') {
            putchar('!');
            putchar('!');
            count++;
        }
        else
        printf("%c", ch);
    }
    printf("Было выполнено %d замен", count);

    return 0;
}