#include "Tests.h"
#include <stdio.h>
#include <math.h>

extern const double EPS;

void AllTests()
{
    FILE *testfile = fopen ("Tests.txt", "r");
    TestParameters test;
    int nRead = 6;
    while (nRead == 6)
    {
        nRead = fscanf(testfile, "%lf %lf %lf %d %lf %lf", &test.arg.a, &test.arg.b, &test.arg.c, &test.vol.number, &test.vol.x1, &test.vol.x2);
        if (nRead == 6)
            RunTest (test);
    }
}

void RunTest (TestParameters test)
{
    RootsData root;
    root.number = SolveEquation (test.arg, &root);

    if (root.number == test.vol.number)
    {
        switch (root.number)
        {
            case ZERO_ROOTS:

                printf("Получен верный ответ\n");
                break;
            case ONE_ROOT:
                if (fabs (root.x1 - test.vol.x1) < EPS || fabs (root.x1 - test.vol.x2) < EPS)
                    printf("Получен верный ответ\n");
                break;
            case TWO_ROOTS:
                if ((fabs (root.x1 - test.vol.x1) < EPS && fabs (root.x2 - test.vol.x2) < EPS) ||
                    (fabs (root.x1 - test.vol.x2) < EPS && fabs (root.x2 - test.vol.x1) < EPS))
                        printf("Получен верный ответ\n");
                break;
            case INFINITE_ROOTS:
                printf("Получен верный ответ\n");
                break;
            default:
                printf("Неверный формат параметров вывода\n");
                break;
        }
    }
    else
    {
        printf("Получен неверный  ответ\n");
        printf ("nRoots = %d, x1 = %lf, x2 = %lf \n", root.number, root.x1, root.x2);
    }
}

