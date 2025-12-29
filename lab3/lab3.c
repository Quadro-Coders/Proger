#include <stdio.h>

int main() {
    float number;
    printf("Введите число с плавающей запятой: ");
    scanf("%f", &number);
    printf("Вводом является %.1f или %.1e\n", number, number);
    printf("Вводом является %.3f или %.3e\n", number, number);
    return 0;
}