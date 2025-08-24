#include <stdio.h>
#include <math.h>
#include <ctype.h>

struct сoefficients {
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

const double EPS =1e-6;

void PrintOutput (int nRoots, double x1, double x2);
bool ReadInput ( сoefficients *kf, double a,  double b, double c);
RootsNumber SolveEquation (сoefficients kf, double *x1, double *x2);
RootsNumber SolveLinear ( double *x, сoefficients kf);
RootsNumber SolveQuadratic (сoefficients kf, double *x1, double *x2);

int main()
{
    double a = 0, b = 0, c = 0;
    struct сoefficients kf; // структура для хранения значений коэффициентов a, b, c
    double x1 = NAN, x2 = NAN; 

    if (ReadInput( &kf, a, b, c) == false )
    {
        printf("Неверный ввод\n");
        return 0;
    }

    int nRoots = SolveEquation (kf, &x1, &x2);
    PrintOutput(nRoots, x1, x2);
    
    return 0;
}

bool ReadInput (сoefficients *kf, double a, double b, double c)
{
    printf("Введите значения коэффициентов уравнения\n");
    printf("вида a*x^2+b*x+c=0\n");
    printf("a, b, и с: \n");

    int nInput = scanf("%lf %lf %lf", &a, &b, &c ); // как ввести через scanf сразу в kf.a, ... 
    (*kf).a = a;                                    // и окончательно избавиться от локальных
    (*kf).b = b;                                    // переменных a, b, c?
    (*kf).c = c;
    
    if ( isfinite ((*kf).a) == 0 || isfinite ((*kf).b) == 0 || isfinite ((*kf).c) == 0 || nInput<3 )
        return false;
    else
        return true;
}


RootsNumber SolveEquation (сoefficients kf, double *x1, double *x2) 
{ 
    if (fabs(kf.a) < EPS)
        return SolveLinear (x1, kf); 
    else
        return SolveQuadratic (kf, x1, x2);
}


RootsNumber SolveLinear (double *x1, сoefficients kf) 
{
    if (fabs(kf.b)<EPS)
    {
        if ( fabs (kf.c) < EPS)
            return INFINITE_ROOTS;
        else
            return ZERO_ROOTS;
    } 
    else           
    {
        *x1 = -kf.c/kf.b;
        return ONE_ROOT;
    }
}


RootsNumber SolveQuadratic (сoefficients kf, double *x1, double *x2 )
{
    double discriminant= kf.b * kf.b - 4* kf.a * kf.c; 

    if ( discriminant < -EPS)
    {
        return ZERO_ROOTS;
    } 
    else 
    {
        if (fabs (discriminant) < EPS)
        {
            *x1 = -kf.b / (2 * kf.a);
            return ONE_ROOT;
        } 
        else
        {
            *x1 = (-kf.b - sqrt (discriminant)) / (2 * kf.a);
            *x2 = (-kf.b + sqrt (discriminant)) / (2 * kf.a);
            return TWO_ROOTS;
        }
    }
}


void PrintOutput (int nRoots, double x1, double x2)
{   
    switch (nRoots)
    {
        case ZERO_ROOTS:
            printf("Уравнение не имеет решений\n");
            break;
        case TWO_ROOTS:
            printf("x1 = %lf\n", x1);
            printf("x2 = %lf\n", x2);
            break;
        case INFINITE_ROOTS:
            printf("Уравнение имеет бесконечное количество корней\n");
            break;
        case ONE_ROOT:
            printf("Единственное решение х= %lf\n", x1);
            break;
        default:
            printf("Неверный формат параметров вывода\n");
            break;  
            
        
    }
}