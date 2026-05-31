#include <stdio.h>
#include <wchar.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "");
    
    int count = 0;
    wint_t ch;
    
    printf("Введите текст (Ctrl+D для завершения):\n");
    
    while ((ch = getwchar()) != WEOF) {
        count++;
    }
    
    printf("\nКоличество символов во входных данных: %d\n", count);
    
    return 0;
}