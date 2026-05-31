#include <stdio.h>

float calc (float n1, float n2) {
    return ((n1-n2)/(n1*n2));
}

int main(void) {
    float n1, n2;

    printf("Введите два числа с плавающей запятой: ");

    while (scanf("%f %f", &n1, &n2))
    {
        printf("Результат: %f\n",calc(n1, n2));
        printf("Введите два числа с плавающей запятой или букву для выхода:\n");
    }
    return 0;
}
