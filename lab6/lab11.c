#include <stdio.h>

#define ARTICHOKE  2.05  // $ цена за фунт артишоков
#define BEET       1.15  // $ цена за фунт свеклы
#define CARROT     1.09  // $ цена за фунт моркови
#define DISCOUNT   0.95   // скидка 5% для заказов >= 100$
#define SHIPPING_1 6.5   // $ доставка для 5-20 фунтов
#define SHIPPING_2 0.5   // $ за фунт для заказов свыше 20 фунтов

// Функция очистки буфера ввода
void flush_buffer (void)
{
    while (getchar () != '\n')
        return;
}

int main (void)
{
    char menu;              // пункты меню a,b,c,q
    float product;          // выбранный продукт из меню
    float weight;           // вес заказа
    float artichoke = 0.0;  // вес артишоков
    float beet = 0.0;       // вес свеклы
    float carrot = 0.0;     // вес моркови
    float artichoke_price;  // стоимость артишоков
    float beet_price;       // стоимость свеклы
    float carrot_price;     // стоимость моркови
    float total;            // стоимость заказа без доставки
    float sum_weight;       // общий вес
    float delivery = 0.0;   // стоимость доставки
    float pay;              // итоговая стоимость

    printf("Какой овощ вы хотите купить?\n");
    printf("a) Артишоки 2.05$\nb) Свекла 1.15$\nc) Морковь 1.09$\
    \nq) Завершить заказ\n");

    // Главный цикл выбора товаров
    while ((menu = getchar ()) != 'q')
    {
        if (menu == '\n')   // пропуск символа новой строки
            continue;       // (чтобы 'q' работал корректно)

        // Проверка корректности ввода
        if (menu != 'a' && menu != 'b' && menu != 'c' && menu != 'q')
            flush_buffer();

        switch (menu)
        {
            case 'a':  // Артишоки
            { 
                printf("Сколько фунтов?\n");
                if (scanf("%f", &weight) != 1 || weight < 0)
                    flush_buffer();
                artichoke += weight;
                break; 
            }
            case 'b':  // Свекла
            { 
                printf("Сколько фунтов?\n");
                if (scanf("%f", &weight) != 1 || weight < 0)
                    flush_buffer();
                beet += weight;
                break; 
            }
            case 'c':  // Морковь
            { 
                printf("Сколько фунтов?\n");
                if (scanf("%f", &weight) != 1 || weight < 0)
                    flush_buffer();
                carrot += weight;
                break; 
            }
        }  // конец switch

        // Повторное отображение меню
        printf("Какой овощ вы хотите купить?\n");
        printf("a) Артишоки 2.05$\nb) Свекла 1.15$\nc) Морковь 1.09$\
        \nq) Завершить заказ\n");

    }  // конец while

    // Расчет стоимости продуктов
    artichoke_price = artichoke * ARTICHOKE;
    beet_price = beet * BEET;
    carrot_price = carrot * CARROT;

    total = artichoke_price + beet_price + carrot_price;

    // Применение скидки 5% для заказов от 100$
    if (total >= 100.0)
        total *= DISCOUNT;

    // Расчет стоимости доставки
    sum_weight = artichoke + beet + carrot;

    if (sum_weight <= 5.0 && sum_weight > 0.0)
        delivery = 6.5;
    else if (sum_weight > 5.0 && sum_weight <= 20.0)
        delivery = 14.0;
    else if (sum_weight > 20.0)
        delivery = 14.0 + ((sum_weight - 20.0) * 0.5);

    pay = total + delivery;

    // Вывод детализированного чека
    printf("\nВы заказали:\n");

    if (artichoke != 0.0)
        printf("%.1f фунт(ов) артишоков на %.1f$ (%.2f$ за 1 фунт)\n",
        artichoke, artichoke_price, ARTICHOKE);
    if (beet != 0.0)
        printf("%.1f фунт(ов) свеклы на %.1f$ (%.2f$ за 1 фунт)\n",
        beet, beet_price, BEET);
    if (carrot != 0.0)
        printf("%.1f фунт(ов) моркови на %.1f$ (%.2f$ за 1 фунт)\n",
        carrot, carrot_price, CARROT);

    printf("Стоимость овощей: %.1f$ ", total);
    if (total >= 100.0)  // примечание о скидке
        printf("(со скидкой 5%%)");
    printf("\n");
    
    if (delivery != 0.0)
        printf("Стоимость доставки: %.1f$\n", delivery);
    
    printf("Итоговая стоимость заказа: %.1f$\n", pay);

    return 0;
}