#include <stdio.h>

#define FATTORE_SCALA (5.0f/9.0f)
#define ZERO 32.0f

int main()
{
    float far, cels;
    printf("Inserisci una temperatura in gradi farheneit: ");
    scanf("%f", &far);
    cels = (far - ZERO) * FATTORE_SCALA;
    printf("%f gradi farheneit corrispondono a %f gradi celsius\n", far, cels);
    return 0;
}