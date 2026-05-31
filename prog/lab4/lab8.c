#include <stdio.h>

int main() {
    int divisor;
    
    printf("Эта программа вычисляет результаты деления по модулю.\n");
    printf("Введите целое число, которое будет служить вторым операндом: ");
    scanf("%d", &divisor);
    
    int dividend;
    printf("Теперь введите первый операнд: ");
    scanf("%d", &dividend);
    
    while (dividend > 0) {
        int result = dividend % divisor;
        printf("%d %% %d равно %d\n", dividend, divisor, result);
        
        printf("Введите следующее число для первого операнда (<=0 для выхода): ");
        scanf("%d", &dividend);
    }
    
    printf("Готово\n");
    return 0;
}