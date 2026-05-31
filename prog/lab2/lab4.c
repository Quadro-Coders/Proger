#include <stdio.h>

int main() {
    float value;
    printf("Введите значение с плавающей запятой: ");
    scanf("%f", &value);
    printf("Запись с фиксированной запятой: %f\n", value);      
    printf("Экспоненциальная форма записи: %e\n", value);       
    printf("Двоично-экспоненциальное представление: %a\n", value); 
    return 0;
}