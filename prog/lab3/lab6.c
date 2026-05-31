#include <stdio.h>
#include <string.h>

int main() {
    char name[20], surname[20];
    int len_name, len_surname;
    printf("Введите ваше имя и фамилию: ");
    scanf("%s %s", name, surname);
    len_name = strlen(name);
    len_surname = strlen(surname);
    printf("Вариант 1\n");
    printf("%s %s\n", name, surname);
    printf("%*d %*d\n", len_name, len_name, len_surname, len_surname);
    printf("Вариант 2\n");
    printf("%s %s\n", name, surname);
    printf("%-*d %-*d\n", len_name, len_name, len_surname, len_surname);
    return 0;
}