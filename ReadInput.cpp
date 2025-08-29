#include <stdio.h>
#include <math.h>
#include "ReadInput.h"
#include <assert.h>

const int expectedInputNumber = 3;

bool ReadInput (Coefficients *coefficient)
{
    assert( coefficient != NULL);

    printf("введите значения коэффициентов уравнения\n");
    printf("вида a*x^2+b*x+c=0\n");
    printf("a, b, и с: \n");

    int inputNumber = scanf ("%lf %lf %lf", &coefficient -> a, &coefficient -> b, &coefficient -> c);

    if (isfinite ((*coefficient).a) == 0 || isfinite ((*coefficient).b) == 0 || isfinite ((*coefficient).c) == 0
        || inputNumber < expectedInputNumber)
        return false;
    else
        return true;
}
