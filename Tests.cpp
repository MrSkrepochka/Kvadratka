#include "Tests.h"
#include "StringToRootsCount.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

const int maxNumberLine = 17;
const int expectedReadResult = 6;

void RunAllTests()
{
    FILE *testfile = fopen ("Tests.txt", "r");
    TestParameters test = {};

    int ReadResult = expectedReadResult;
    char rootsNumberLine [maxNumberLine] = "";
    int nTest = 1;
    while (ReadResult == expectedReadResult)
    {
        ReadResult = fscanf(testfile, "%lf %lf %lf %16s %lf %lf" , &test.arg.a, &test.arg.b, &test.arg.c,
                            rootsNumberLine, &test.values.x1, &test.values.x2 );

        if (ReadResult == 6)
        {
            if (StringToRootsCount (rootsNumberLine, &test) == true)
            {
                RunTest (test, nTest);
                nTest++;
            }
            else
            {
                printf("Неверный формат тестового файла\n");
            }
        }
    }

    fclose(testfile);
}

void RunTest (TestParameters test, int nTest)
{

    RootsData root = {.number = SolveEquation (test.arg, &root)};

    if (root.number != test.values.number) {
        printf("Тест номер %d провален\n", nTest);
        printf ("nRoots = %d, x1 = %lf, x2 = %lf \n", root.number, root.x1, root.x2);
        return;
    }

    switch (root.number)
    {
        case ZERO_ROOTS:
            printf("Тест номер %d прошел успешно\n", nTest);
            break;
        case ONE_ROOT:
            if (fabs (root.x1 - test.values.x1) < EPS || fabs (root.x1 - test.values.x2) < EPS)
                printf("Тест номер %d прошел успешно\n", nTest);
            break;
        case TWO_ROOTS:
            if ((fabs (root.x1 - test.values.x1) < EPS && fabs (root.x2 - test.values.x2) < EPS) ||
                (fabs (root.x1 - test.values.x2) < EPS && fabs (root.x2 - test.values.x1) < EPS))
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

