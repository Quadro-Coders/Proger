#include <stdio.h>

int main (void)
{
    int category;     // категория налогоплательщика
    int bracket;      // выбранная налоговая категория
    int gross;        // валовый доход
    const int b1 = 17850;   // налоговые категории в $
    const int b2 = 23900;
    const int b3 = 29750;
    const int b4 = 14875;
    const float rate_1 = 0.15f;  // налоговая ставка 15%
    const float rate_2 = 0.28f;  // налоговая ставка 28%
    float tax;        // сумма налога
    float net;        // чистый доход
    int flag;         // флаг продолжения главного цикла

    do { // НАЧАЛО ГЛАВНОГО ЦИКЛА

        printf("Выберите вашу налоговую категорию:\n");

        printf("1) Холост/Не замужем: \
        (15%% от первых $17,850 плюс 28%% от превышения\n");
        printf("2) Глава household: \
        15%% от первых $23,900 плюс 28%% от превышения\n");
        printf("3) Женат/Замужем, совместно: \
        15%% от первых $29,750 плюс 28%% от превышения\n");
        printf("4) Женат/Замужем, раздельно: \
        15%% от первых $14,875 плюс 28%% от превышения\n");
        printf("5) Выход\n");

        scanf("%d", &category);

        // Проверка корректности ввода категории
        while (!(category < 5) && !(category > 0))
        {   
            while (getchar() != '\n')
                ;  // очистка буфера ввода
            scanf("%d", &category);
        }

        switch(category)
        {
            case 1:
            { bracket = b1;
                break; }
            case 2:
            { bracket = b2;
                break; }
            case 3:
            { bracket = b3;
                break; }
            case 4:
            { bracket = b4;
                break; }
            case 5:
                goto end;
        }

        printf("Введите ваш валовый доход:\n");

        // Проверка корректности ввода дохода
        while (scanf("%d", &gross) != 1)
            while (getchar() != '\n')  // очистка буфера
                continue;

        // Расчет налога
        if (gross <= bracket)
            tax = gross * rate_1;  // 15% от всего дохода
        else
            tax = (bracket * rate_1) + ((gross - bracket) * rate_2);  // 15% + 28% от превышения

        net = gross - tax;  // чистый доход

        printf("Валовый доход: %d; налог: %.0f; чистый доход: %.0f\n",
               gross, tax, net);
        
        while (getchar() != '\n')  // очистка буфера
            continue;

        printf("Сделать еще один расчет (y) или любая клавиша для выхода\n");

        if (getchar() == 'y')
            flag = 1;

    } while (flag == 1);  // КОНЕЦ ГЛАВНОГО ЦИКЛА

end: printf("До свидания!");

    return 0;
}