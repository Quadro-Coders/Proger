#include <stdio.h>

int main() {
    float cups;
    printf("Введите объем в чашках: ");
    scanf("%f", &cups);
    printf("Пинты: %.2f\n", cups / 2);
    printf("Унции: %.2f\n", cups * 8);
    printf("Столовые ложки: %.2f\n", cups * 8 * 2);
    printf("Чайные ложки: %.2f\n", cups * 8 * 2 * 3);
    return 0;
}