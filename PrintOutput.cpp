#include "PrintOutput.h"
#include <stdio.h>

void PrintOutput (RootsData root)
{
    switch (root.number)
    {
        case ZERO_ROOTS:
            printf("Уравнение не имеет решений\n");
            break;
        case TWO_ROOTS:
            printf("x1 = %lf\n", root.x1);
            printf("x2 = %lf\n", root.x2);
            break;
        case INFINITE_ROOTS:
            printf("Уравнение имеет бесконечное количество корней\n");
            break;
        case ONE_ROOT:
            printf("Единственное решение х= %lf\n", root.x1);
            break;
        default:
            printf("Неверный формат параметров вывода\n");
            break;
    }
}
