#include <stdio.h>
#include <math.h>
#include <ctype.h>

// TODO RootsNumber
enum cases  {
    ZERO, // TODO ZERO_ROOTS
    ONE,
    TWO,
    INF
};

const double EPS =1e-6;

void PrintOutput (int nRoots, double x1, double x2);
bool ReadInput(double *a, double *b, double *c);
int SolveEquation (double a, double b, double c, double *x1, double *x2);
int SolveLinear ( double *x, double b, double c);
int SolveQuadratic (double a, double b, double c, double *x1, double *x2);

int main()
{
    double a = 0, b = 0, c = 0;
    double x1 = NAN, x2 = NAN; 

    if (ReadInput(&a, &b, &c) == false )
    {
        printf("Неверный ввод\n");
        return 0;
    }

    int nRoots = SolveEquation (a, b, c, &x1, &x2);
    PrintOutput(nRoots, x1, x2);
    
    return 0;
}

bool ReadInput(double *a, double *b, double *c)
{
    printf("Введите значения коэффициентов уравнения\n");
    printf("вида a*x^2+b*x+c=0\n");
    printf("a, b, и с: \n");

    int nInput = scanf("%lf %lf %lf", a, b, c );
    
    if ( isfinite (*a) == 0 || isfinite (*b) == 0 || isfinite (*c) == 0 || nInput<3 )
        return false;
    else
        return true;
}

// TODO return type
int SolveEquation (double a, double b, double c, double *x1, double *x2) 
{ 
    if (fabs(a) < EPS)
        return SolveLinear (x1, b, c); 
    else
        return SolveQuadratic (a, b, c, x1, x2);
}

// TODO return type
int SolveLinear (double *x1, double b, double c) 
{
    if (fabs(b)<EPS)
    {
        if ( fabs (c) < EPS)
            return INF;
        else
            return ZERO;
    } 
    else           
    {
        *x1 = -c/b;
        return ONE;
    }
}

// TODO change return type
int SolveQuadratic (double a, double b, double c, double *x1, double *x2 )
{
    double discriminant= b*b- 4*a*c; 

    if ( discriminant < -EPS)
    {
        return ZERO;
    } 
    else 
    {
        if (fabs (discriminant) < EPS)
        {
            *x1 = -b / (2 * a);
            return ONE;
        } 
        else
        {
            *x1 = (-b - sqrt (discriminant)) / (2 * a);
            *x2 = (-b + sqrt (discriminant)) / (2 * a);
            return TWO;
        }
    }
}

// TODO RootsNumber
void PrintOutput (int nRoots, double x1, double x2)
{   
    switch (nRoots)
    {
        case ZERO:
            printf("Уравнение не имеет решений\n");
            break;
        case TWO:
            printf("x1 = %lf\n", x1);
            printf("x2 = %lf\n", x2);
            break;
        case INF:
            printf("Уравнение имеет бесконечное количество корней\n");
            break;
        case ONE:
            printf("Единственное решение х= %lf\n", x1);
            break;  
            
        // TODO default case
    }
}
