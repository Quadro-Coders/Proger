#include <stdio.h>

int main(void)
{
    float s = 1000000.0f;
    int year = 0;

    while (s > 0)
    {
        year++;
        s -= 100000.0f;
        s = (s * 1.08f);
        printf("Столько лет пройдёт: %d, баланс: %.1f\n", year, s);
    }

    printf("Банкротство через %2d лет (баланс: $ %.1f)\n", year, s);
    
    return 0;
}