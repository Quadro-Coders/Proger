#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 1000  // Максимальная длина входного текста

char input[MAX_LEN];  // Буфер для хранения входного текста
int pos = 0;          // Текущая позиция в буфере

// Функция пропуска пробелов, табуляций и переводов строк
void skip_spaces() {
    while (input[pos] == ' ' || input[pos] == '\t' || 
           input[pos] == '\n' || input[pos] == '\r') {
        pos++;
    }
}

// Проверка, является ли слово ключевым словом Python
bool is_keyword(const char* word) {
    const char* keywords[] = {"if", "while", "for", "print", 
                              "int", "input", "range"};
    int num_keywords = 7;
    
    for (int i = 0; i < num_keywords; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return true;
        }
    }
    return false;
}

// Сбор всех переменных из исходного кода Python
void collect_variables() {
    int temp_pos = 0;           // Временная позиция для анализа
    char vars[100][100];        // Массив для хранения имен переменных
    int var_count = 0;          // Счетчик переменных
    
    while (temp_pos < strlen(input)) {
        // Пропускаем пробельные символы
        while (input[temp_pos] == ' ' || input[temp_pos] == '\t' || 
               input[temp_pos] == '\n' || input[temp_pos] == '\r') {
            temp_pos++;
        }
        
        if (input[temp_pos] == '\0') break;
        
        // Пропускаем комментарии Python
        if (input[temp_pos] == '#') {
            while (input[temp_pos] != '\n' && input[temp_pos] != '\0') {
                temp_pos++;
            }
            continue;
        }
        
        // Пропускаем строковые литералы (не извлекаем из них "переменные")
        if (input[temp_pos] == '"') {
            temp_pos++;
            while (input[temp_pos] != '"' && input[temp_pos] != '\0') {
                temp_pos++;
            }
            if (input[temp_pos] == '"') temp_pos++;
            continue;
        }
        
        // Если текущий символ - начало идентификатора
        if (isalpha((unsigned char)input[temp_pos]) || input[temp_pos] == '_') {
            // Читаем идентификатор
            char ident[100];
            int i = 0;
            while (isalnum((unsigned char)input[temp_pos]) || 
                   input[temp_pos] == '_') {
                ident[i++] = input[temp_pos++];
            }
            ident[i] = '\0';
            
            // Пропускаем ключевые слова
            if (is_keyword(ident)) {
                continue;
            }
            
            // Пропускаем пробелы после идентификатора
            while (input[temp_pos] == ' ' || input[temp_pos] == '\t') {
                temp_pos++;
            }
            
            // Если после идентификатора идет '=', это присваивание переменной
            if (input[temp_pos] == '=') {
                // Проверяем, не добавлена ли уже эта переменная
                bool exists = false;
                for (int j = 0; j < var_count; j++) {
                    if (strcmp(vars[j], ident) == 0) {
                        exists = true;
                        break;
                    }
                }
                
                // Добавляем новую переменную
                if (!exists) {
                    strcpy(vars[var_count++], ident);
                }
            }
            
            // Сбор переменных из условий if/while
            if (strcmp(ident, "if") == 0 || strcmp(ident, "while") == 0) {
                // Пропускаем пробелы после ключевого слова
                while (input[temp_pos] == ' ' || input[temp_pos] == '\t') {
                    temp_pos++;
                }
                
                // Читаем первую переменную в условии
                char cond_var[100];
                int k = 0;
                while (isalnum((unsigned char)input[temp_pos]) || 
                       input[temp_pos] == '_') {
                    cond_var[k++] = input[temp_pos++];
                }
                cond_var[k] = '\0';
                
                // Добавляем переменную из условия, если это не ключевое слово
                if (!is_keyword(cond_var) && k > 0) {
                    bool exists = false;
                    for (int j = 0; j < var_count; j++) {
                        if (strcmp(vars[j], cond_var) == 0) {
                            exists = true;
                            break;
                        }
                    }
                    
                    if (!exists) {
                        strcpy(vars[var_count++], cond_var);
                    }
                }
            }
            
            continue;
        }
        
        temp_pos++;
    }
    
    // Выводим объявления всех собранных переменных
    for (int i = 0; i < var_count; i++) {
        printf("    int %s;\n", vars[i]);
    }
    
    // Пустая строка для лучшей читаемости
    if (var_count > 0) {
        printf("\n");
    }
}

// Основная функция программы
int main() {
    // Чтение всего входного текста посимвольно
    int c;
    int idx = 0;
    while ((c = getchar()) != EOF && idx < MAX_LEN - 1) {
        input[idx++] = c;
    }
    input[idx] = '\0';

    // Заголовок генерируемой C программы
    printf("#include <stdio.h>\n\n");
    printf("int main() {\n");
    
    // Сбор и вывод объявлений переменных
    collect_variables();

    // Основной цикл преобразования конструкций Python в C
    pos = 0;
    
    while (pos < idx) {
        skip_spaces();
        
        if (input[pos] == '\0') break;
        
        // Пропускаем комментарии Python
        if (input[pos] == '#') {
            while (input[pos] != '\n' && input[pos] != '\0') {
                pos++;
            }
            continue;
        }
        
        // 1. Обработка присваивания (variable = expression)
        if (isalpha((unsigned char)input[pos]) || input[pos] == '_') {
            char var_name[100];
            int i = 0;
            
            // Чтение имени переменной
            while (isalnum((unsigned char)input[pos]) || input[pos] == '_') {
                var_name[i++] = input[pos++];
            }
            var_name[i] = '\0';
            
            // Пропускаем ключевые слова
            if (is_keyword(var_name)) {
                pos -= i;
            } else {
                skip_spaces();
                
                // Если после имени идет '=', это присваивание
                if (input[pos] == '=') {
                    pos++; // пропускаем '='
                    skip_spaces();
                    
                    // Проверка на конструкцию input()
                    if (strncmp(&input[pos], "int(input())", 12) == 0) {
                        pos += 12;
                        printf("    scanf(\"%%d\", &%s);\n", var_name);
                    } else {
                        // Обычное присваивание
                        printf("    %s = ", var_name);
                        
                        // Чтение выражения до конца строки
                        while (input[pos] != '\n' && input[pos] != '\0' && 
                               input[pos] != '#') {
                            // Обработка строковых литералов внутри выражений
                            if (input[pos] == '"') {
                                putchar(input[pos++]);
                                while (input[pos] != '"' && input[pos] != '\0' && 
                                       input[pos] != '\n') {
                                    putchar(input[pos++]);
                                }
                                if (input[pos] == '"') {
                                    putchar(input[pos++]);
                                }
                            } else {
                                putchar(input[pos++]);
                            }
                        }
                        printf(";\n");
                    }
                    
                    continue;
                } else {
                    // Не присваивание
                    pos -= i;
                }
            }
        }
        
        // 2. Обработка условного оператора if
        if (strncmp(&input[pos], "if", 2) == 0) {
            pos += 2;
            skip_spaces();
            
            printf("    if (");
            
            // Чтение условия до двоеточия
            while (input[pos] != ':' && input[pos] != '\0') {
                putchar(input[pos++]);
            }
            
            printf(")");
            
            if (input[pos] == ':') {
                pos++; // пропускаем ':'
                skip_spaces();
                
                // Проверка, есть ли тело на той же строке
                if (input[pos] != '\n' && input[pos] != '\0' && 
                    input[pos] != '#') {
                    printf(" ");
                    
                    // Чтение тела if
                    while (input[pos] != '\n' && input[pos] != '\0' && 
                           input[pos] != '#') {
                        putchar(input[pos++]);
                    }
                    
                    printf(";\n");
                } else {
                    printf("\n");
                }
            }
            
            continue;
        }
        
        // 3. Обработка цикла while
        if (strncmp(&input[pos], "while", 5) == 0) {
            pos += 5;
            skip_spaces();
            
            printf("    while (");
            
            // Чтение условия до двоеточия
            while (input[pos] != ':' && input[pos] != '\0') {
                putchar(input[pos++]);
            }
            
            printf(")");
            
            if (input[pos] == ':') {
                pos++; // пропускаем ':'
                skip_spaces();
                
                // Проверка, есть ли тело на той же строке
                if (input[pos] != '\n' && input[pos] != '\0' && 
                    input[pos] != '#') {
                    printf(" ");
                    
                    // Чтение тела while
                    while (input[pos] != '\n' && input[pos] != '\0' && 
                           input[pos] != '#') {
                        putchar(input[pos++]);
                    }
                    
                    printf(";\n");
                } else {
                    printf("\n");
                }
            }
            
            continue;
        }
        
        // 4. Обработка цикла for
        if (strncmp(&input[pos], "for", 3) == 0) {
            pos += 3;
            skip_spaces();
            
            // Чтение переменной цикла
            char loop_var[100];
            int i = 0;
            while (isalnum((unsigned char)input[pos]) || input[pos] == '_') {
                loop_var[i++] = input[pos++];
            }
            loop_var[i] = '\0';
            
            skip_spaces();
            
            // Проверка конструкции "in range()"
            if (strncmp(&input[pos], "in", 2) == 0) {
                pos += 2;
                skip_spaces();
                
                if (strncmp(&input[pos], "range(", 6) == 0) {
                    pos += 6;
                    
                    // Чтение аргумента range()
                    char range_arg[100];
                    int arg_len = 0;
                    while (input[pos] != ')' && input[pos] != '\0') {
                        if (input[pos] != ' ') {
                            range_arg[arg_len++] = input[pos++];
                        } else {
                            pos++;
                        }
                    }
                    range_arg[arg_len] = '\0';
                    
                    if (input[pos] == ')') pos++;
                    
                    // Генерация заголовка цикла for на C
                    printf("    for(size_t %s=0;%s<%s;%s++)\n", 
                           loop_var, loop_var, range_arg, loop_var);
                    
                    // Поиск двоеточия
                    while (input[pos] != ':' && input[pos] != '\0') pos++;
                    
                    if (input[pos] == ':') {
                        pos++; // пропускаем ':'
                        skip_spaces();
                        
                        // Проверка, есть ли тело на той же строке
                        if (input[pos] != '\n' && input[pos] != '\0' && 
                            input[pos] != '#') {
                            printf("    ");
                            
                            // Проверка, является ли тело print()
                            if (strncmp(&input[pos], "print(", 6) == 0) {
                                pos += 6; // пропускаем "print("
                                
                                printf("printf(\"%%d\", ");
                                
                                // Чтение аргумента print
                                while (input[pos] != ')' && input[pos] != '\0') {
                                    putchar(input[pos++]);
                                }
                                
                                printf(")");
                                
                                if (input[pos] == ')') pos++;
                            } else {
                                // Другое тело цикла
                                while (input[pos] != '\n' && input[pos] != '\0' && 
                                       input[pos] != '#') {
                                    putchar(input[pos++]);
                                }
                            }
                            
                            printf(";\n");
                        }
                    }
                }
            }
            
            continue;
        }
        
        // 5. Обработка команды вывода print()
        if (strncmp(&input[pos], "print", 5) == 0) {
            pos += 5;
            skip_spaces();
            
            if (input[pos] == '(') {
                pos++; // пропускаем '('
                skip_spaces();
                
                printf("    printf(");
                
                // Проверка типа аргумента: строковый литерал или выражение
                if (input[pos] == '"') {
                    // Строковый литерал
                    printf("\"%%s\", \"");
                    pos++; // пропускаем открывающую кавычку Python
                    
                    // Копирование содержимого строки
                    while (input[pos] != '"' && input[pos] != '\0') {
                        putchar(input[pos++]);
                    }
                    
                    if (input[pos] == '"') {
                        pos++; // пропускаем закрывающую кавычку Python
                        putchar('"'); // закрывающая кавычка для C
                    }
                } else {
                    // Числовое выражение
                    printf("\"%%d\", ");
                    
                    // Чтение выражения
                    while (input[pos] != ')' && input[pos] != '\0' && 
                           input[pos] != '\n') {
                        putchar(input[pos++]);
                    }
                }
                
                // Завершение printf
                while (input[pos] != ')' && input[pos] != '\0') pos++;
                if (input[pos] == ')') pos++;
                
                printf(");\n");
            }
            
            continue;
        }
        
        // Пропуск непонятных символов
        pos++;
    }

    // Завершение функции main()
    printf("    return 0;\n");
    printf("}\n");
    return 0;
}