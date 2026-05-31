#include <stdio.h>

int main (void) {
    int ch;
    printf("Введите какой-нибудь код символа: ");
    scanf("%d", &ch); /* пользователь вводит символ */
    printf("Код: %d символ: %c.\n", ch, ch);
    return 0;
}