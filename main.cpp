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

    char option = '0';
    int status = 1;
    while (status == 1)
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
            AllTests();
            break;
        case 'q':
            status = 0;
            break;
        default:
        printf("Неверный выбор опции\n");
        break;
        }
        while (getchar() != '\n')
        {
            continue;
        }
    }

    return 0;
}
