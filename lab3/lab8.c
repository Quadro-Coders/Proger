#include <stdio.h>
#define LITERS_PER_GALLON 3.785
#define KM_PER_MILE 1.609

int main() {
    float miles, gallons, mpg, l_per_100km;
    printf("Введите количество преодоленных миль: ");
    scanf("%f", &miles);
    printf("Введите количество израсходованных галлонов: ");
    scanf("%f", &gallons);
    mpg = miles / gallons;
    printf("Расход: %.1f миль на галлон\n", mpg);
    l_per_100km = (100 * LITERS_PER_GALLON) / (miles * KM_PER_MILE / gallons);
    printf("Европейский стандарт: %.1f литров на 100 км\n", l_per_100km);
    return 0;
}
