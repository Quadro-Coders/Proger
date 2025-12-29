#include <stdio.h>

int main(void)
{
    char input[255];
    int i = 0;

    printf("Введите строку: ");

    while (scanf("%c", &input[i]), input[i] != '\n')
        i++;

    for (; i >= 0; i--)
        printf("%c", input[i]);

    return 0;
}