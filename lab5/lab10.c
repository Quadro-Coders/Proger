#include <stdio.h>

int main(void) {
    int min, max;
    int summ = 0;
    int m, M;

    printf("Введите нижний и верхний целочисленные пределы: ");
    scanf("%d %d", &min, &max);

    while (min < max) {
        for (m = min, M = max + 1; m != M; m++)
            summ += m * m;
        printf("Сумма квадратов целых чисел от %d до %d равна %d\n", 
               min * min, max * max, summ);
        summ = 0;
        printf("Введите следующую комбинацию пределов: ");
        scanf("%d %d", &min, &max);
    }
    printf("Работа завершена\n");
    
    return 0;
}