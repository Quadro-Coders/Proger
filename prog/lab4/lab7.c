#include <stdio.h>

void cube(double num) {
    double result = num * num * num;
    printf("Куб числа %.2f равен %.2f\n", num, result);
}

int main() {
    double number;
    
    printf("Введите число: ");
    scanf("%lf", &number);
    
    cube(number);
    
    return 0;
}