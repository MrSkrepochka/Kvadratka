#include "ReadInput.h"
#include "SolveEquation.h"
#include "PrintOutput.h"
#include "Tests.h"
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>

int main()
{

    RootsData root;
    Coefficients coefficient;
    int Option = 1;

    printf("Введите '1' для ручного ввода коэффициентов\n");
    printf("Или '2' для диагностики программы на основе заданных тестов\n");
    scanf("%d", &Option);

    switch (Option)
    {
        case 1:
            if (!ReadInput( &coefficient ))
            {
                printf("Неверный ввод\n");
                return 0;
            }
            root.number = SolveEquation (coefficient, &root);
            PrintOutput(root);
            break;
        case 2:
            AllTests();
            break;
        default:
            printf("Неверный выбор опции\n");
            break;
    }

    return 0;
}


