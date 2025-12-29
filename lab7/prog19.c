#include <stdio.h>

void clear() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    char choice;
    float num1, num2;
    int invalid;
    
    printf("Выберите желаемую операцию:\n");
    printf("s. сложение    v. вычитание\n");
    printf("u. умножение    d. деление\n");
    printf("z. завершение\n");
    
    while (1) {
        printf("\n");
        int result = scanf(" %c", &choice);
        
        if (result == EOF) {
            printf("\nПрограмма завершена.\n");
            break;
        }
        
        clear();
        
        if (choice == 'z') {
            printf("Программа завершена.\n");
            break;
        }
        
        if (choice != 's' && choice != 'v' && choice != 'u' && choice != 'd') {
            printf("Неверный выбор. Попробуйте снова. s,v,u,d\n");
            continue;
        }
        
        do {
            printf("Введите первое число: ");
            invalid = scanf("%f", &num1);
            
            if (invalid == EOF) {
                printf("\nПрограмма завершена принудительно.\n");
                return 0;
            }
            
            clear();
            if (!invalid) {
                printf("Это не число. Введите число, такое как 2.5, -1.23 или 3: ");
            }
        } while (!invalid);
        
        do {
            printf("Введите второе число: ");
            invalid = scanf("%f", &num2);
            
            if (invalid == EOF) {
                printf("\nрограмма завершена принудительно.\n");
                return 0;
            }
            
            clear();
            if (!invalid) {
                printf("Это не число. Введите число, такое как 2.5, -1.23 или 3: ");
            } else if (choice == 'd' && num2 == 0) {
                printf("Введите число, отличное от 0: ");
                invalid = 0;
            }
        } while (!invalid);
        
        switch (choice) {
            case 's':
                printf("%.1f + %.1f = %.1f\n", num1, num2, num1 + num2);
                break;
            case 'v':
                printf("%.1f - %.1f = %.1f\n", num1, num2, num1 - num2);
                break;
            case 'u':
                printf("%.1f * %.1f = %.1f\n", num1, num2, num1 * num2);
                break;
            case 'd':
                printf("%.1f / %.1f = %.1f\n", num1, num2, num1 / num2);
                break;
        }
        
        printf("Выберите желаемую операцию:\n");
        printf("s. сложение    v. вычитание\n");
        printf("u. умножение    d. деление\n");
        printf("z. завершение\n");
    }
    
    return 0;
}