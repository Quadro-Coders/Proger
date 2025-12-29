#include <stdio.h>
 
int main(void) {

    int row, col;
    char bukva = 'A';

    for (row=0; row<6; row++) {
        for(col=0; col<=row; col++)
        printf("%c", bukva++);
        printf("\n");
    }
    return 0;
}