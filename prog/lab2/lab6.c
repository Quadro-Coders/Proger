#include <stdio.h>

int main() {
    double quarts, molecules;
    double grams_per_molecule = 3.0e-23; 
    double grams_per_quart = 950; 
    printf("Введите объем воды в квартах: ");
    scanf("%lf", &quarts);
    molecules = (quarts * grams_per_quart) / grams_per_molecule;
    printf("Количество молекул воды: %.2e\n", molecules);
    return 0;
}