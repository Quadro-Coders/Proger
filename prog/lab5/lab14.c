#include <stdio.h>

int main(void)
{
    int n1[8], n2[8];
    int i;
    int summ = 0;

    printf("Введите 8 значений: ");

    n2[0] = 0;
    for (i = 0; i < 8; i++)
    {
        scanf("%d", &n1[i]);
        summ += n1[i];
        n2[i] = summ;
    }
    
    i = 0;
    for (i = 0; i < 8; i++)
    {
        printf("%5d", n1[i]);
    }
    
    i = 0;
    printf("\n");
    for (i = 0; i < 8; i++)
    {
        printf("%5d", n2[i]);
    }
    return 0;
}