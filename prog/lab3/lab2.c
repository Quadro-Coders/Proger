#include <stdio.h>
#include <string.h>

int main() {
    char name[20];
    printf("Введите ваше имя: ");
    scanf("%s", name);
    printf("\"%s\"\n", name);
    printf("\"%20s\"\n", name);
    printf("\"%-20s\"\n", name);
    int length = strlen(name);
    printf("\"%*s\"\n", length+3, name);
    return 0;
}