#include <stdio.h>

int main() {
    char name[20], surname[20];
    printf("Введите ваше имя: ");
    scanf("%s", name);
    printf("Введите вашу фамилию: ");
    scanf("%s", surname);
    printf("%s, %s\n", surname, name);
    return 0;
}
