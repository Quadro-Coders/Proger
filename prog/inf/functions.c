#include <stdio.h>

// Функция инкремента через указатель
void increment(int *ptr) {
    (*ptr)++;
}

// Функция декремента через указатель  
void decrement(int *ptr) {
    (*ptr)--;
}

int main() {
    int num = 10;
    
    printf("Исходное значение: %d\n", num);
    
    increment(&num);
    printf("После increment: %d\n", num);
    
    decrement(&num);
    printf("После decrement: %d\n", num);
    
    return 0;
}