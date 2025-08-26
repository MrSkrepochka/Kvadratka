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
    INFINITE_ROOTS = -1,
};

struct RootsData {
    RootsNumber number;
    double x1;
    double x2;
};

struct TestParameters {
    struct Coefficients arg;
    struct RootsData vol;
};


const double EPS =1e-6;

void AllTests ();

void PrintOutput (RootsData root);
bool ReadInput (Coefficients *coefficient);
int RunTest ( int i, FILE *testfile, RootsData root, TestParameters test);
RootsNumber SolveEquation (Coefficients coefficient,  RootsData *root);
RootsNumber SolveLinear (RootsData *root, Coefficients coefficient);
RootsNumber SolveQuadratic (Coefficients coefficient, RootsData *root);

int main()
{
    RootsData root = {ZERO_ROOTS, NAN, NAN};
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
        {
            root -> x1 = NAN;
            root -> x2 = NAN;
            return INFINITE_ROOTS;
        }
        else
        {
            root -> x1 = NAN;
            root -> x2 = NAN;
            return ZERO_ROOTS;
        }    
    } 
    else           
    {
        root -> x1 = -coefficient.c/coefficient.b;
        root -> x2 = NAN; 
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
        root -> x1 = NAN;
        root -> x2 = NAN;
        return ZERO_ROOTS;
    } 
    else 
    {
        if (fabs (discriminant) < EPS)
        {
            root -> x1 = -coefficient.b / (2 * coefficient.a);
            root -> x2 = NAN;
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
    //assert (isfinite (root.x1)); мешают работе, когда х1 = NAN или x2 = NAN
    //assert (isfinite (root.x2));

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
void AllTests ()
{
    int nTests = 0;
    RootsData root = {ZERO_ROOTS, NAN, NAN};
    FILE *testfile = fopen ("Tests.txt", "r");           // добавить прроверку на правильный формат ввода
    printf ("Введите количчество тестов\n");
    scanf ("%d", &nTests); 
    TestParameters test = {};
    int nRead =0; 

    for ( int i=1; i<=nTests; i++) // TODO rename i
    {
        RunTest( i, testfile, root, test);
    }

    // RunTest()
    // RunTest()
    // RunTest()
}

int RunTest (int i, FILE *testfile, RootsData root, TestParameters test)
{

    fscanf(testfile, "%lf %lf %lf %d %lf %lf", &test.arg.a, &test.arg.b, &test.arg.c, &test.vol.number, &test.vol.x1, &test.vol.x2);
    //добавить проверку на наличие ровно 6 элементов ввода

    root.number = SolveEquation (test.arg, &root);
    if (root.number == test.vol.number)
    {
        if ((fabs (root.x1 - test.vol.x1) < EPS && fabs (root.x2 - test.vol.x2) < EPS) || ( fabs (root.x1 - test.vol.x2) < EPS && fabs (root.x2 - test.vol.x1) < EPS) || (isnan (root.x1) == 1 && isnan(test.vol.x1) == 1 && fabs (root.x2 - test.vol.x2) < EPS) || (isnan (root.x2) == 1 && isnan(test.vol.x1) == 1 && fabs (root.x1 - test.vol.x2) < EPS) || (isnan (root.x1) == 1 && isnan(test.vol.x2) == 1 && fabs (root.x2 - test.vol.x1) < EPS) || (isnan (root.x2) == 1 && isnan(test.vol.x2) == 1 && fabs (root.x1 - test.vol.x1) < EPS) || ( isnan (root.x1) == 1 && isnan (root.x2) == 1 && isnan(test.vol.x1) == 1 && isnan(test.vol.x2) == 1))
        {
            printf("Тест номер %d прошел успешно\n", i);
            return 0;
        }
        else
        {
            printf("Тест номер %d провален\n", i);
            printf ("nRoots = %d, x1 = %lf, x2 = %lf \n", root.number, root.x1, root.x2);
            return 1;
        }
    } 
    else
        {
            printf("Тест номер %d провален\n", i);
            printf ("nRoots = %d, x1 = %lf, x2 = %lf \n", root.number, root.x1, root.x2);
            return 1;
        }
}
