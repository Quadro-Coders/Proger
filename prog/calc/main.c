#include "calc.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Использование: %s \"выражение\"\n", argv[0]);
        printf("Пример: %s \"(1.5 + 2) * 3\"\n", argv[0]);
        return 1;
    }

    double res;
    if (calc_evaluate(argv[1], &res) != 0)
    {
        return 1;
    }

    // Форматированный вывод: целые без .0, вещественные без лишних нулей
    if (res == (long long)res)
        printf("%lld\n", (long long)res);
    else
        printf("%g\n", res);

    return 0;
}
