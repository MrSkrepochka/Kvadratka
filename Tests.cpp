#include "Tests.h"
#include <stdio.h>
#include <math.h>

extern const double EPS;

void AllTests()
{
    FILE *testfile = fopen ("Tests.txt", "r");
    TestParameters test;
    int nRead = 6;
    int nTest = 1;
    while (nRead == 6)
    {
        nRead = fscanf(testfile, "%lf %lf %lf %d %lf %lf", &test.arg.a, &test.arg.b, &test.arg.c, &test.vol.number, &test.vol.x1, &test.vol.x2);
        if (nRead == 6)
            {
            RunTest (test, nTest);
            nTest++;
            }
    }
}

void RunTest (TestParameters test, int nTest)
{
    RootsData root;
    root.number = SolveEquation (test.arg, &root);

    if (root.number == test.vol.number)
    {
        switch (root.number)
        {
            case ZERO_ROOTS:

                printf("Тест номер %d прошел успешно\n", nTest);
                break;
            case ONE_ROOT:
                if (fabs (root.x1 - test.vol.x1) < EPS || fabs (root.x1 - test.vol.x2) < EPS)
                    printf("Тест номер %d прошел успешно\n", nTest);
                break;
            case TWO_ROOTS:
                if ((fabs (root.x1 - test.vol.x1) < EPS && fabs (root.x2 - test.vol.x2) < EPS) ||
                    (fabs (root.x1 - test.vol.x2) < EPS && fabs (root.x2 - test.vol.x1) < EPS))
                        printf("Тест номер %d прошел успешно\n", nTest);
                break;
            case INFINITE_ROOTS:
                printf("Тест номер %d прошел успешно\n", nTest);
                break;
            default:
                printf("Неверный формат параметров вывода\n");
                break;
        }
    }
    else
    {
        printf("Тест номер %d провален\n", nTest);
        printf ("nRoots = %d, x1 = %lf, x2 = %lf \n", root.number, root.x1, root.x2);
    }
}

