#include <stdio.h>

#define MIH 60

int main() {
    int minutes;
    
    printf("Введите время в минутах: ");
    scanf("%d", &minutes);
    
    while (minutes > 0) {
        int hours = minutes / MIH;
        int remaining_minutes = minutes % MIH;
        
        printf("%d минут = %d часов и %d минут\n", 
               minutes, hours, remaining_minutes);
        
        printf("Введите время в минутах (<=0 для выхода): ");
        scanf("%d", &minutes);
    }
    
    printf("Программа завершена.\n");
    return 0;
}
