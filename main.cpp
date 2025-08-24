#include <stdio.h>
#include <math.h>
#include <ctype.h>

void Output (int check, double x, double x1, double x2);
int CheckInput(double *a, double *b, double *c);
void SolveEquation (double a, double b, double c, double *x, double *x1, double *x2);
double Linear (double b, double c);
void Quadratic (double x, double y, double z, double *k1, double *k2);

int main()
{
    double a = 0, b = 0, c = 0;
    double x = NAN, x1 = NAN, x2 = NAN;
    int check = CheckInput(&a, &b, &c);
    SolveEquation (a, b, c, &x, &x1, &x2);
    Output( check, x, x1, x2);
    return 0;
}

int CheckInput(double *a, double *b, double *c)
{
    double A = NAN, B = NAN, C = NAN;
    printf("Введите значения коэффициентов уравнения\n");
    printf("вида a*x^2+b*x+c=0\n");
    printf("a, b, и с: \n");
    int nInput = scanf("%lf %lf %lf", &A, &B, &C ); // заполняет локальные A, B, C
    if (isfinite(A) == 0 || isfinite(B) == 0 || isfinite(C) == 0 || nInput<3)
    {
        return 0;
    } else
    {
        *a = A;
        *b = B;   // заполняет a, b, c для main
        *c = C;
        return 1;
    }    
}

void SolveEquation (double a, double b, double c, double *x, double *x1, double *x2) 
   // a, b, c копируются из main
{
    const double EPS = 1e-6;
    if (fabs(a)<EPS)
    {
        *x = Linear (b, c); // возвращает х в main из Linear
    } else
    {
         double X1 = NAN, X2 =NAN;
        Quadratic (a, b, c, &X1, &X2); // заполняет локальные X1 и X2 из Quadratic
        // возвращает значения в х1 и х2 для main
        *x1 = X1;
        *x2 = X2;
    }
}

double Linear (double b, double c) // берет копии b, c из SolveEquation <-- b,c из main
{
    const double EPS =1e-6;
    if (fabs(b)<EPS)
        {
            return NAN;
        } else           // возвращает значение функции в SolveEquation 
        {
            return -c/b;
        }
}

void Quadratic (double x, double y, double z, double *k1, double *k2 )
{
    double discriminant= y*y- 4*x*z; // x, y z <-- a, b, c из SolveEquation <-- a, b, c из main

    if (discriminant<0)
    {
        *k1 = NAN; // возвращает значения в Х1 и Х2 в SolveEquation
        *k2 = NAN;
    } else
    {
        *k1 = (-y - sqrt(discriminant)) / (2*x);
        *k2 = (-y + sqrt(discriminant)) / (2*x);
    }
}

void Output (int check, double x, double x1, double x2)
{
    if (check == 0)
    {
        printf("Неверный ввод\n");
    } else
    {
        if (x == NAN && x1 == NAN && x2 == NAN )
        {
           printf("Уравнение не имеет решений\n"); 
        } else
        {     
            if (x != NAN)
            {
                printf("Единственное решение х= %lf\n", x);
            }   else
                {   /*const double EPS = 1e-6;
                    if (fabs(x1-x2)<EPS)
                    {
                        printf("Единственное решение х= %lf\n", x1 );
                    } else
                    {*/
                        printf("x1 = %lf\n", x1);
                        printf("x2 = %lf\n", x2);
                    
                }
        }
    }
}


