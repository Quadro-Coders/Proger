#include "stringfunc.h"

#define MAX_TEXT_LENGTH 10000
#define MAX_RESULT_LENGTH 20000

int main(int argc, char* argv[]) {
    // Установка локали для поддержки широких символов
    setlocale(LC_ALL, "");
    
    // Проверка наличия аргумента с номером функции
    if (argc < 2) {
        wprintf(L"Ошибка: не указан номер функции.\n");
        wprintf(L"Использование: ./main <номер_функции> [параметры] < входной_файл > выходной_файл\n");
        wprintf(L"Пример: ./main 2 < in.txt > out.txt\n");
        wprintf(L"Доступные функции:\n");
        wprintf(L"  1 - Подсчет количества каждого символа в тексте\n");
        wprintf(L"  2 - Определение средней длины слова\n");
        wprintf(L"  3 - Количество слов между первой и последней запятой\n");
        wprintf(L"  4 - Разделение каждого слова на две части\n");
        return 1;
    }
    
    // Чтение входного текста
    wchar_t text[MAX_TEXT_LENGTH];
    int textLength = 0;
    wchar_t ch;
    
    // Чтение текста из стандартного ввода
    while ((ch = getwchar()) != WEOF && textLength < MAX_TEXT_LENGTH - 1) {
        text[textLength++] = ch;
    }
    text[textLength] = L'\0';
    
    // Преобразование номера функции из аргумента
    int functionNumber = atoi(argv[1]);
    
    // Выполнение выбранной функции
    switch (functionNumber) {
        case 1: {
            // Функция 1: Подсчет количества каждого символа в тексте
            countCharacters(text);
            break;
        }
        
        case 2: {
            // Функция 2: Определение средней длины слова в тексте
            double avgLength = averageWordLength(text);
            wprintf(L"Средняя длина слова: %.2f\n", avgLength);
            break;
        }
        
        case 3: {
            // Функция 3: Вычисление количества слов между первой и последней запятой
            int wordCount = wordsBetweenCommas(text);
            wprintf(L"Количество слов между первой и последней запятой: %d\n", wordCount);
            break;
        }
        
        case 4: {
            // Функция 4: Делит КАЖДОЕ слово на два и оставляет меньшую часть
            wchar_t result[MAX_RESULT_LENGTH];
            splitTextWords(text, result);
            wprintf(L"%ls", result);
            break;
        }
        
        default:
            wprintf(L"Ошибка: неверный номер функции. Допустимые значения: 1-4.\n");
            return 1;
    }
    
    return 0;
}
