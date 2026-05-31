#include <stdio.h>

int main(void) {
    long i, n;
    int array[7];

    printf("Введите 8 целых чисел: ");

    for (i=0; i<8; i++)
        scanf("%d", &array[i]);

    for (i=7; i>=0; i--)
        printf("%d", array[i]);
    return 0;
}