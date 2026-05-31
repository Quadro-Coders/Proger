#include <stdio.h>
// gcc -o programma programma.c
// /.programma
int main() {
    int n;
    
    printf("Введите номер: ");
    scanf("%d", &n);
    
    char id = n % 10 + 1;
    const char count_z = 11;
    
    char z1 = 1 + (count_z % id);
    char z2 = 4 + (count_z % id);
    char z3 = (7 + (count_z % id)) % (count_z + 1);
    
    printf("id = %d\nz1 = %d\nz2 = %d\nz3 = %d\n", id, z1, z2, z3);
    
    return 0;
}