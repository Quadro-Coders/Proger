#include <stdio.h>

int main() {
    const double CM_IN_INCH = 2.54;
    const int INCHES_IN_FOOT = 12;
    double cm;
    
    printf("Введите высоту в сантиметрах: ");
    scanf("%lf", &cm);
    
    while (cm > 0) {
        double total_inches = cm / CM_IN_INCH;
        int feet = total_inches / INCHES_IN_FOOT;
        double inches = total_inches - feet * INCHES_IN_FOOT;
        
        printf("%.1f см = %d футов, %.1f дюймов\n", 
               cm, feet, inches);
        
        printf("Введите высоту в сантиметрах (<=0 для выхода): ");
        scanf("%lf", &cm);
    }
    
    printf("Работа завершена.\n");
    return 0;
}