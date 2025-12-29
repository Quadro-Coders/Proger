#include "stringfunc.h"


// Функция 1: подсчет количества каждого символа в тексте и вывод таблицы
void countCharacters(const wchar_t* text) {
    int charCounts[65536] = {0};
    
    // Подсчет символов
    for (int i = 0; text[i] != L'\0'; i++) {
        wchar_t ch = text[i];
        if (ch >= 0 && ch < 65536) {
            charCounts[ch]++;
        }
    }
    
    // Вывод заголовка таблицы
    wprintf(L"Символ\t\tКоличество\n");
    
    // Вывод результатов
    for (int i = 0; i < 65536; i++) {
        if (charCounts[i] > 0) {
            wchar_t ch = i;
            
            // Специальная обработка для непечатных символов
            if (ch == L'\n') {
                wprintf(L"'\\n'\t\t%d\n", charCounts[i]);
            } else if (ch == L'\t') {
                wprintf(L"'\\t'\t\t%d\n", charCounts[i]);
            } else if (ch == L'\r') {
                wprintf(L"'\\r'\t\t%d\n", charCounts[i]);
            } else if (ch == L' ') {
                wprintf(L"пробел\t\t%d\n", charCounts[i]);
            } else if (ch < 32 || ch == 127) {
                // Управляющие символы ASCII
                wprintf(L"Ctrl+%c\t\t%d\n", i + 64, charCounts[i]);
            } else {
                // Обычные печатные символы
                wprintf(L"'%lc'\t\t%d\n", ch, charCounts[i]);
            }
        }
    }
}

// Функция 2: определение средней длины слова в тексте
double averageWordLength(const wchar_t* text) {
    int totalLength = 0;
    int wordCount = 0;
    int inWord = 0; // Флаг нахождения внутри слова
    int currentLength = 0;
    
    for (int i = 0; text[i] != L'\0'; i++) {
        wchar_t ch = text[i];
        
        // Проверяем, является ли символ частью слова (буква или цифра)
        if ((ch >= L'a' && ch <= L'z') || (ch >= L'A' && ch <= L'Z') || 
            (ch >= L'0' && ch <= L'9') || (ch >= L'а' && ch <= L'я') || 
            (ch >= L'А' && ch <= L'Я')) {
            if (!inWord) {
                inWord = 1;
                wordCount++;
            }
            currentLength++;
        } else {
            if (inWord) {
                totalLength += currentLength;
                currentLength = 0;
                inWord = 0;
            }
        }
    }
    
    // Обработка последнего слова, если текст заканчивается словом
    if (inWord) {
        totalLength += currentLength;
    }
    
    if (wordCount == 0) return 0.0;
    return (double)totalLength / wordCount;
}

// Функция 3: вычисление количества слов между первой и последней запятой
int wordsBetweenCommas(const wchar_t* text) {
    int firstComma = -1;
    int lastComma = -1;
    int length = 0;
    
    // Находим длину строки и позиции запятых
    for (int i = 0; text[i] != L'\0'; i++) {
        length++;
        if (text[i] == L',') {
            if (firstComma == -1) {
                firstComma = i;
            }
            lastComma = i;
        }
    }
    
    // Если нет хотя бы двух запятых, возвращаем 0
    if (firstComma == -1 || lastComma == -1 || firstComma == lastComma) {
        return 0;
    }
    
    // Подсчет слов между запятыми
    int wordCount = 0;
    int inWord = 0;
    
    for (int i = firstComma + 1; i < lastComma; i++) {
        wchar_t ch = text[i];
        
        // Проверяем, является ли символ частью слова
        if ((ch >= L'a' && ch <= L'z') || (ch >= L'A' && ch <= L'Z') || 
            (ch >= L'0' && ch <= L'9') || (ch >= L'а' && ch <= L'я') || 
            (ch >= L'А' && ch <= L'Я')) {
            if (!inWord) {
                inWord = 1;
                wordCount++;
            }
        } else {
            inWord = 0;
        }
    }
    
    return wordCount;
}

// Функция 4: деление КАЖДОГО слова на две части и оставление меньшей части
void splitTextWords(const wchar_t* text, wchar_t* result) {
    int i = 0; // индекс в исходном тексте
    int j = 0; // индекс в результате
    int wordStart = -1;
    int wordLength = 0;
    
    while (1) {
        wchar_t ch = text[i];
        
        // Проверяем, является ли символ частью слова
        int isWordChar = 0;
        if ((ch >= L'a' && ch <= L'z') || (ch >= L'A' && ch <= L'Z') || 
            (ch >= L'0' && ch <= L'9') || (ch >= L'а' && ch <= L'я') || 
            (ch >= L'А' && ch <= L'Я') || ch == L'-' || ch == L'\'') {
            isWordChar = 1;
        }
        
        if (isWordChar && wordStart == -1) {
            // Начало нового слова
            wordStart = i;
            wordLength = 1;
        } else if (isWordChar && wordStart != -1) {
            // Продолжение слова
            wordLength++;
        } else {
            // Конец слова или не-буквенный символ
            if (wordStart != -1) {
                // Обрабатываем найденное слово
                int half = wordLength / 2;
                
                // Определяем, какую часть оставить
                // Если длина нечетная, берем вторую половину (большую)
                // Если четная, берем первую половину (меньшую)
                int startPos, partLength;
                
                if (wordLength % 2 == 0) {
                    // Четная длина: берем первую половину
                    startPos = wordStart;
                    partLength = half;
                } else {
                    // Нечетная длина: берем вторую половину
                    startPos = wordStart + half;
                    partLength = half + 1;
                }
                
                // Копируем выбранную часть в результат
                for (int k = 0; k < partLength; k++) {
                    result[j++] = text[startPos + k];
                }
                
                // Добавляем пробел после слова
                if (ch != L'\0' && ch != L'\n' && ch != L'\r') {
                    result[j++] = L' ';
                }
                
                wordStart = -1;
                wordLength = 0;
            }
            
            // Если это конец строки, выходим
            if (ch == L'\0') {
                break;
            }
            
            // Если это не конец строки и не слово, пропускаем символ
            // (в примере видно, что сохраняются пробелы между словами)
        }
        
        i++;
    }
    
    result[j] = L'\0';
}