#include <stdio.h>
#include <string.h>

int main(void) {
    char word[255];
    int i;
    printf ("Введите слово: ");
    scanf("%s", word);
    for (i = strlen(word)-1; i>=0; i--)
    printf("%c", word[i]);
    printf("\n");
    return 0;
}