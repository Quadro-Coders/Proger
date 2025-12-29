#include <stdio.h>

int main() {
    int num;
    
    printf("Введите целое число: ");
    scanf("%d", &num);
    
    for (int i = num; i <= num + 10; i++) {
        printf("%d ", i);
    }
    printf("\n");
    
    return 0;
}