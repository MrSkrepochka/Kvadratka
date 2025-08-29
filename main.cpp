#include "ReadInput.h"
#include "SolveEquation.h"
#include "PrintOutput.h"
#include "Tests.h"
#include <stdio.h>
#include <math.h>


enum ProgramStatus {
    OFF,
    ON,
};

void ClearBuffer();

int main()
{

    RootsData root = {ZERO_ROOTS, NAN, NAN};
    Coefficients coefficient = {NAN, NAN, NAN};

    char option = '0';
    ProgramStatus status = ON;

    while (status == ON)
    {
        printf("Введите '1' для ручного ввода коэффициентов\n");
        printf("Или '2' для диагностики программы на основе заданных тестов.\n");
        printf("Для выхода из программы введите 'q'\n");
        scanf("%c", &option);

        switch (option)
        {
        case '1':
            if (!ReadInput(&coefficient))
            {
                printf("Неверный ввод\n");
            } else
            {
                root.number = SolveEquation (coefficient, &root);
                PrintOutput(root);
            }
            break;
        case '2':
            RunAllTests();
            break;
        case 'q':
            status = OFF;
            break;
        default:
            printf("Неверный выбор опции\n");
            break;
        }

        ClearBuffer();
    }

    return 0;
}

void CLearBuffer()
{
    while (getchar () != EOF)
    {
        continue;
    }
}
