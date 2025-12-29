#include <stdio.h>

int main(void) 
{
    int count, sum, limit;
    
    count = 0;
    sum = 0;
 
    printf("Введите количество дней: ");
    scanf("%d", &limit);
    
    while (count++ < limit) 
        sum = sum + (count * count);
    
    printf("Общая сумма за %d дней = %d\n", limit, sum);
    
    return 0;
}