#include <stdio.h>

int main() {
    float cm, inch;
    const float INCH_TO_CM = 2.54;
    printf("Введите рост в сантиметрах: ");
    scanf("%f", &cm);
    inch = cm / INCH_TO_CM;
    printf("Рост в дюймах: %.2f\n", inch);
    return 0;
}