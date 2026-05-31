#include <stdio.h>

int main() {
    char id = 9 % 10 + 1;
    const char count_z = 19;
    
    char z1 = id + (count_z % id);
    char z2 = ((id * 3) % count_z) + 1;
    char z3 = ((id * 3) + id) % count_z + 1;
    
    printf("id = %d\nz1 = %d\nz2 = %d\nz3 = %d\n", id, z1, z2, z3);
    
    return 0;
}