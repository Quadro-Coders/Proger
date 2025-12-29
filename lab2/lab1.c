#include <stdio.h>
#include <limits.h>
#include <float.h>

int main() {
    int i = INT_MAX;
    printf("INT_MAX = %d\n", i);
    printf("INT_MAX + 1 = %d\n", i + 1);

    float f = FLT_MAX;
    printf("FLT_MAX = %e\n", f);
    printf("FLT_MAX * 2 = %e\n", f * 2);

    double d = 1.0e20;
    double loss = (d + 1.0) - d;
    printf("Потеря значимости: (1e20 + 1) - 1e20 = %.20f\n", loss);

    int m = INT_MIN;
    printf("INT_MIN = %d\n", m);
    printf("INT_MIN - 1 = %d\n", m - 1);

    float small = FLT_MIN;
    printf("FLT_MIN = %e\n", small);
    printf("FLT_MIN / 10 = %e\n", small / 10);

    float zero = 0.0;
    printf("Деление на ноль: 1.0 / 0.0 = %e\n", 1.0 / zero);

    float besk = 1.0 / zero;
    printf("Бесконечность - бесконечность: inf - inf = %e\n", besk - besk);

    float nolik = zero / zero;
    printf("Ноль на ноль: 0.0 / 0.0 = %e\n", nolik);

    int big = 1000000;
    int big2 = 1000000;
    printf("Переполнение при умножении: %d * %d = %d\n", big, big2, big * big2);

    float tiny = 1e-30;
    float tiny2 = 1e-30;
    printf("Сложение очень малых: %e + %e = %e\n", tiny, tiny2, tiny + tiny2);

    double huge = 1e308;
    printf("Очень большое double: %e\n", huge);
    printf("Умножение больших: %e * 10 = %e\n", huge, huge * 10);

    return 0;
}
