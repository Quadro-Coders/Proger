#include <stdio.h>

int main(void) {
    int min, max;
    int sqrt, cube;

    printf("Введите верхний предел: ");
    scanf("%d", &max);
    printf("Введите нижний предел: ");
    scanf("%d", &min);
    printf("Число Квадрат Куб\n");
    for (min; min <= max; min++)
    printf("%4d %7d %7d\n" , min, min*min, min*min*min);
    printf("\n");
    
    return 0;
}