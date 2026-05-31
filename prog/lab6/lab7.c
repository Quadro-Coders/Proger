#include <stdio.h>

#define STAVKA 10

#define OVERTIME 40
#define OVERWORK 1.5

#define NALOG_1 300.0f
#define KOF_1 0.15

#define NALOG_2 150.0f
#define KOF_2 0.2

#define KOF_3 0.25

int main (void) {

    int h = 0;
    float total = 0.0;
    float kof = 0.0;
    float zp = 0.0;

    printf("Введите количество часов, отработанных за неделю (q для выхода): ");

    while (scanf("%d", &h) == 1)
    {
        total = (float)h * STAVKA;
        if (h > OVERTIME)
        total *= OVERWORK;
        if (total <= NALOG_1)
        kof = total * KOF_1;

        if (total > NALOG_1 && total < NALOG_1 + NALOG_2)
        {
            kof = NALOG_1 * KOF_1;
            kof +=((total - NALOG_1) * KOF_2);
        }
        if (total >= NALOG_1 + NALOG_2)
        {
            kof = NALOG_1 * KOF_1;
            kof +=(NALOG_2 * KOF_2);
            kof +=((total - (NALOG_1+NALOG_2)) * KOF_3);
        }
        zp = total - kof;

        printf("Всего: %.0f (-%.0f$ налоги). Заработано: %.0f\n", total, kof, zp);
        printf("Введите количество часов, отработанных за неделю (q для выхода): ");
    }

    return 0;
}