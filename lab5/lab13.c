#include <stdio.h>

int main(void) {
    int array[8];
    int ch=1;
    int i;

    for (i=0; i < 8; i++)
    {
        ch*=2;
        array[i]=ch;
    }
    i=0;
    do {
        printf("[%d] = %d\n", i, array[i]);
        i++;
    } while (i<8);

    return 0;
}