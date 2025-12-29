#include <stdio.h>

int main(void) {
    float n1, n2;

    printf("Введите два числа с плавающей запятой: ");

    while (scanf("%f %f", &n1, &n2))
    {
        printf("Результат: %f\n",((n1-n2)/(n1*n2)));
        printf("Введите два числа с плавающей запятой или букву для выхода:\n");
    }
    return 0;
}