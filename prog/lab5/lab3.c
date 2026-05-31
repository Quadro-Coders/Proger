#include <stdio.h>

int main(void) {
    int row, col;
    char bukva;

    for (row = 0; row < 6; row++) {
        bukva = 'F';
        for (col = 0; col <= row; col++) {
            printf("%c", bukva--);
        }
        printf("\n");
    }
    return 0;
}