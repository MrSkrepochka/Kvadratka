#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>

struct Coefficients {
    double a;
    double b;
    double c;
};

enum RootsNumber  {
    ZERO_ROOTS, 
    ONE_ROOT,
    TWO_ROOTS,
    INFINITE_ROOTS,
};

struct RootsData {
    RootsNumber number;
    double x1;
    double x2;
};

const double EPS =1e-6;

void AllTests ();

void PrintOutput (RootsData root);
bool ReadInput (Coefficients *coefficient);
void RunTest (double a, double b, double c, Coefficients coefficient, RootsData root, int nRoots, double x1, double x2);
RootsNumber SolveEquation (Coefficients coefficient,  RootsData *root);
RootsNumber SolveLinear (RootsData *root, Coefficients coefficient);
RootsNumber SolveQuadratic (Coefficients coefficient, RootsData *root);

int main()
{
    RootsData root;
    Coefficients coefficient; 
    AllTests ();

    if (!ReadInput( &coefficient ))
    {
        printf("Неверный ввод\n");
        return 0;
    }

    root.number = SolveEquation (coefficient, &root);
    PrintOutput(root);
    
    return 0;
}

bool ReadInput (Coefficients *coefficient)
{
    assert( coefficient != NULL);

    printf("Введите значения коэффициентов уравнения\n");
    printf("вида a*x^2+b*x+c=0\n");
    printf("a, b, и с: \n");

    int nInput = scanf ("%lf %lf %lf", &coefficient -> a, &coefficient -> b, &coefficient -> c);
    
    if ( isfinite ((*coefficient).a) == 0 || isfinite ((*coefficient).b) == 0 || isfinite ((*coefficient).c) == 0 || nInput<3 )
        return false;
    else
        return true;
}


RootsNumber SolveEquation (Coefficients coefficient, RootsData *r) 
{ 
    assert (isfinite (coefficient.a));
    assert (isfinite (coefficient.b));
    assert (isfinite (coefficient.c));

    assert (r != NULL);

    if (fabs(coefficient.a) < EPS)
        return SolveLinear (r, coefficient); 
    else
        return SolveQuadratic (coefficient, r);
}


RootsNumber SolveLinear (RootsData *root, Coefficients coefficient) 
{
    assert (isfinite (coefficient.a));
    assert (isfinite (coefficient.b));
    assert (isfinite (coefficient.c));

    assert (root != NULL);

    if (fabs (coefficient.b)<EPS)
    {
        if (fabs (coefficient.c) < EPS)
            return INFINITE_ROOTS;
        else
        {
            root -> x1 = 0;
            root -> x2 = 0;
            return ZERO_ROOTS;
        }    
    } 
    else           
    {
        root -> x1 = -coefficient.c/coefficient.b;
        root -> x2 = -coefficient.c/coefficient.b;
        return ONE_ROOT;
    }
}

RootsNumber SolveQuadratic (Coefficients coefficient, RootsData *root)
{
    assert (isfinite (coefficient.a));
    assert (isfinite (coefficient.b));
    assert (isfinite (coefficient.c));

    assert (root != NULL);

    double discriminant= coefficient.b * coefficient.b - 4 * coefficient.a * coefficient.c; 

    if ( discriminant < -EPS)
    {
        root -> x1 = 0;
        root -> x2 = 0;
        return ZERO_ROOTS;
    } 
    else 
    {
        if (fabs (discriminant) < EPS)
        {
            root -> x1 = -coefficient.b / (2 * coefficient.a);
            root -> x2 = -coefficient.b / (2 * coefficient.a);
            return ONE_ROOT;
        } 
        else
        {
            root -> x1 = (-coefficient.b - sqrt (discriminant)) / (2 * coefficient.a);
            root -> x2 = (-coefficient.b + sqrt (discriminant)) / (2 * coefficient.a);
            return TWO_ROOTS;
        }
    }
}

void PrintOutput (RootsData root)
{
    assert (isfinite (root.x1));
    assert (isfinite (root.x2));
    //assert (isfinite (r.number));

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
void AllTests()
{
    RootsData root;
    Coefficients coefficient;
    
    RunTest (1, -5 , 6, coefficient, root, 2, 2, 3 );
    RunTest (1, -5 , 6, coefficient, root, 2, 3, 2 );
    RunTest (-1, 5, -6, coefficient, root, 2, 3, 2);
    RunTest (1, 2, 1, coefficient, root, 1, -1, -1);
    RunTest (1, -4, 3, coefficient, root, 2, 1, 3);
    RunTest (1, -4, 3, coefficient, root, 2, 3, 1);
    RunTest (1, 5 , 7, coefficient, root, 0, 0, 0);
    RunTest (1, 0, -25, coefficient, root, 2, -5, 5);
    RunTest (1, 0, 25, coefficient, root, 0, 0, 0);
    RunTest (0, 5, 10, coefficient, root, 1, -2, -2);
    RunTest (1, 5, 0, coefficient, root, 2, -5, 0);

}

void RunTest ( double a, double b, double c, Coefficients coefficient, RootsData root, int nRoots, double x1, double x2)
{
    /*assert (isfinite(a));
    assert (isfinite(b));
    assert (isfinite(c));
    assert (isfinite(nRoots));
    assert (isfinite(x1));
    assert (isfinite(x2));*/
    //assert (isfinite (root.number));



    coefficient.a = a;
    coefficient.b = b;
    coefficient.c = c;

    root.number = SolveEquation (coefficient, &root);
    if (root.number == nRoots)
    {
        if ((fabs (root.x1 - x1) < EPS && fabs (root.x2 - x2) < EPS) || ( fabs (root.x1 - x2) < EPS && fabs (root.x2 - x1) < EPS) )
        {
            printf("Получен верный ответ\n");
        }
        else
        {
            printf("Получен неверный  ответ\n");
            printf ("nRoots = %d, x1 = %lf, x2 = %lf \n", root.number, root.x1, root.x2);
        }
    } 
    else
        {
            printf("Получен неверный  ответ\n");
            printf ("nRoots = %d, x1 = %lf, x2 = %lf \n", root.number, root.x1, root.x2);
        }
}