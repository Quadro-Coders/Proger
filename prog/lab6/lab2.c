#include <stdio.h>
#include <wchar.h>
#include <locale.h>

int main(void)
{
    setlocale(LC_ALL, "");
    wint_t ch;
    int n = 0;
    
    printf("Пожалуйста, введите что-нибудь (# для выхода)\n");
    
    while ((ch = getwchar()) != L'#')
    {
        if (ch != L'\n' && ch != L' ')
        {
            printf("%lc-%d ", ch, ch);
            n++;
        }
        if ((n % 8) == 0)
            printf("\n");
    }
    return 0;
}