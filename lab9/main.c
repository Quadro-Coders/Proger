#include "matrixfunc.h"

int main() {
    char choice;
    
    do {
        printf("\nМЕНЮ ДЛЯ РАБОТЫ С МАТРИЦЕЙ\n");
        printf("a. Ввод матрицы\n");
        printf("b. Вывод матрицы\n");
        printf("c. Поиск индексов\n");
        printf("d. Сумма четных\n");
        printf("e. Выход\n");
        printf("Выберите опцию: ");
        
        if (scanf(" %c", &choice) == EOF) {
            printf("\n");
            choice = 'e';
        }
        
        clear();
        
        switch (choice) {
            case 'a':
                input_matrix();
                break;
            case 'b':
                print_matrix();
                break;
            case 'c':
                find_indices();
                break;
            case 'd':
                sum_even();
                break;
            case 'e':
                printf("Выход из программы...\n");
                break;
            default:
                printf("Неверный выбор! Попробуйте снова.\n");
        }
        
    } while (choice != 'e');
    
    return 0;
}
