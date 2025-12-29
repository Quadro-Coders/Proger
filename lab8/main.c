#include "myarrfunc.h"

int main() {
    char choice;
    
    do {
        printf("\nМЕНЮ ДЛЯ РАБОТЫ С МАССИВОМ\n");
        printf("a. Задать размер массива\n");
        printf("b. Заполнить массив\n");
        printf("c. Представление массива (значения, адреса)\n");
        printf("d. Найти мин и макс значения\n");
        printf("e. Разница мин/макс в диапазоне\n");
        printf("f. Сумма элементов выше значения\n");
        printf("g. Выход\n");
        printf("Выберите опцию: ");
        
        if (scanf(" %c", &choice) == EOF) {
            printf("\n");
            choice = 'g';
        }
        
        clear();
        
        switch (choice) {
            case 'a':
                set_array_size();
                break;
            case 'b':
                fill_array();
                break;
            case 'c':
                print_array();
                break;
            case 'd':
                min_max();
                break;
            case 'e':
                min_max_arr();
                break;
            case 'f':
                sum_value();
                break;
            case 'g':
                printf("Выход из программы...\n");
                break;
            default:
                printf("Неверный выбор! Попробуйте снова.\n");
        }
        
    } while (choice != 'g');
    
    return 0;
}
