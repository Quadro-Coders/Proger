#include <stdio.h>
#include <wchar.h>
#include <locale.h>

void printik(wchar_t simvol, int width, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            wprintf(L"%lc", simvol);
        }
        wprintf(L"\n");
    }
}

int main() {
    wchar_t simvol;
    int width, height;
    int result;
    
    setlocale(LC_ALL, "");
    
    wprintf(L"Введите символ: ");
    wscanf(L"%lc", &simvol);
    
    while (1) {
        wprintf(L"Введите ширину (количество символов в строке): ");
        result = wscanf(L"%d", &width);
        
        if (result != 1) {
            wprintf(L"Ошибка! Пожалуйста, введите число.\n");
            while (getwchar() != L'\n');
        } else if (width <= 0) {
            wprintf(L"Ошибка! Ширина должна быть положительным числом.\n");
        } else {
            break;
        }
    }
    
    while (1) {
        wprintf(L"Введите высоту (количество строк): ");
        result = wscanf(L"%d", &height);
        
        if (result != 1) {
            wprintf(L"Ошибка! Пожалуйста, введите число.\n");
            while (getwchar() != L'\n');
        } else if (height <= 0) {
            wprintf(L"Ошибка! Высота должна быть положительным числом.\n");
        } else {
            break;
        }
    }
    
    printik(simvol, width, height);
    
    return 0;
}
