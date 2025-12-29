#include <stdio.h>

int main() {
    int divisor, operand, result;
    
    printf("Эта программа вычисляет результаты деления по модулю.\n");
    
    printf("Введите целое число, которое будет служить вторым операндом: ");
    scanf("%d", &divisor);
    
    while (1) {
        printf("Введите число для первого операнда (<= 0 для выхода из программы): ");
        scanf("%d", &operand);
        
        if (operand <= 0) {
            break;
        }
        
        result = operand % divisor;
        printf("%d %% %d равно %d\n\n", operand, divisor, result);
    }
    
    printf("Готово\n");
    return 0;
}