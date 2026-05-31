#include <stdio.h>

int main(void) {
    int row, space, down, up;
    char bukva, a, b;


    printf("Введите прописную букву: ");
    scanf("%c", &bukva);

    int rows = bukva - 'A' + 1;

    for (row = 0; row < rows; row++) {
        for(space = row; space < rows - 1; space++)
            printf(" ");
        for(down = 0, a = 'A'; down <= row; down++, a++)
            printf("%c", a);
        for(up = 0, b = 'A' + row - 1; up < row; up++, b--)
            printf("%c", b);
        
        printf("\n");
    }
    return 0;
}