#include <stdio.h>

int main(void) {
    float n1 = 0;
    float n2 = 0;
    float z;
    float x;
    float sign = 1;

    printf("Введите количество элементов для подсчета: ");

    scanf ("%f", &z);

    while (z > 0) {
        for (x = 1; x <= z; x++) {
            n1 += (1 / x);
            n2 += (1 / x) * sign;
            sign = (-sign);
        }
        printf("1 + 1/2 + 1/3 + 1/4 + ... 1/%.0f = %f\n", z, n1);
        printf("1 - 1/2 + 1/3 - 1/4 + ... 1/%.0f = %f\n", z, n2);
        printf("Введите следующее количество элементов или 0 для выхода: ");
        n1 = 0; n2 = 0;
        scanf ("%f", &z);
    }
    return 0;
}