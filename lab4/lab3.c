#include <stdio.h>

int main() {
    int days;
    
    printf("Введите количество дней: ");
    scanf("%d", &days);
    
    while (days > 0) {
        int weeks = days / 7;
        int remaining_days = days % 7;
        
        printf("%d дней составляют %d недели и %d дня.\n", 
               days, weeks, remaining_days);
        
        printf("Введите количество дней (<=0 для выхода): ");
        scanf("%d", &days);
    }
    
    printf("Программа завершена.\n");
    return 0;
}