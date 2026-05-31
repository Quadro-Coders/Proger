#include <stdio.h>

int main() {
    float inch, feet;
    char name[20];
    printf("Введите ваш рост в дюймах: ");
    scanf("%f", &inch);
    printf("Введите ваше имя: ");
    scanf("%s", name);
    feet = inch / 12.0;
    printf("%s, ваш рост составляет %.3f футов\n", name, feet);
    return 0;
}