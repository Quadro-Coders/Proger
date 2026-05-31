#include <stdio.h>
#include <string.h>

char memory[65536];
char cpu_model[100];

int main() {
    setbuf(stdin, NULL);
    
    int data_size = 256 * 1024;
    char data[256 * 1024];
    
    // Чтение модели CPU
    int idx = 0;
    char c;
    while ((c = getchar()) != '\n' && c != EOF && idx < 99) {
        cpu_model[idx++] = c;
    }
    cpu_model[idx] = '\0';
    
    // Чтение числа N
    int N = 0;
    while ((c = getchar()) != '\n' && c != EOF) {
        if (c >= '0' && c <= '9') {
            N = N * 10 + (c - '0');
        }
    }
    
    int sum = 0;
    for (int i = 1; i <= N; i++) {
        sum += i;
        memory[i % 65536] = i % 256;
        data[i % data_size] = (sum + i) % 256;
    }
    
    // Вывод незашифрованной суммы
    char digits[20];
    int temp = sum;
    int count = 0;
    
    if (temp == 0) {
        putchar('0');
    } else {
        while (temp > 0) {
            digits[count++] = (temp % 10) + '0';
            temp /= 10;
        }
        for (int i = count - 1; i >= 0; i--) {
            putchar(digits[i]);
        }
    }
    putchar('\n');
    
    // Шифрование и вывод
    temp = sum;
    count = 0;
    
    if (temp == 0) {
        int encrypted = (0 + cpu_model[0]) % 10;
        putchar(encrypted + '0');
    } else {
        while (temp > 0) {
            digits[count++] = (temp % 10) + '0';
            temp /= 10;
        }
        
        for (int i = count - 1; i >= 0; i--) {
            int digit = digits[i] - '0';
            char cpu_char = cpu_model[(count - 1 - i) % idx];
            int encrypted = (digit + cpu_char) % 10;
            putchar(encrypted + '0');
        }
    }
    putchar('\n');
    
    return 0;
}