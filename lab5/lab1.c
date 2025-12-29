#include <stdio.h>

int main() {
    char alphavit[26];

    for (int i = 0; i < 26; i++) {
        alphavit[i] = 'a' + i;
    }
    
    for (int i = 0; i < 26; i++) {
        printf("%c ", alphavit[i]);
    }
    printf("\n");
    
    return 0;
}
