#include <stdio.h>
#include <float.h>

int main() {
    double d_val = 1.0 / 3.0;
    float f_val = 1.0 / 3.0;
    printf("double значение 1.0/3.0:\n");
    printf("4 цифры: %.4f\n", d_val);
    printf("12 цифр: %.12f\n", d_val);
    printf("16 цифр: %.16f\n", d_val);
    printf("\nfloat значение 1.0/3.0:\n");
    printf("4 цифры: %.4f\n", f_val);
    printf("12 цифр: %.12f\n", f_val);
    printf("16 цифр: %.16f\n", f_val);
    printf("\nFLT_DIG = %d\n", FLT_DIG);
    printf("DBL_DIG = %d\n", DBL_DIG);
    return 0;
}