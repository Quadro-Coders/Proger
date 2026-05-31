#include <stdio.h>

int main() {
    int years;
    double seconds = 3.156e7;
    printf("Введите ваш возраст в годах: ");
    scanf("%d", &years);
    printf("Ваш возраст в секундах: %.0f\n", years * seconds);
    return 0;
}