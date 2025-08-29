#include "SolveEquation.h"
#include <stdio.h>
#include <math.h>
#include <assert.h>

RootsNumber SolveEquation (Coefficients coefficient, RootsData *root)
{
    assert (isfinite (coefficient.a));
    assert (isfinite (coefficient.b));
    assert (isfinite (coefficient.c));

    assert (root != NULL);

    if (fabs(coefficient.a) < EPS)
        return SolveLinear (root, coefficient);
    else
        return SolveQuadratic (coefficient, root);

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

    if (fabs (discriminant) < EPS)
    {
        root -> x1 = -coefficient.b / (2 * coefficient.a);
        root -> x2 = NAN;
        return ONE_ROOT;
    }

    // TODO do not compute sqrt / 2a twice
    root -> x1 = (-coefficient.b - sqrt (discriminant)) / (2 * coefficient.a);
    root -> x2 = (-coefficient.b + sqrt (discriminant)) / (2 * coefficient.a);
    return TWO_ROOTS;
}

RootsNumber SolveLinear (RootsData *root, Coefficients coefficient)
{
    assert (isfinite (coefficient.a));
    assert (isfinite (coefficient.b));
    assert (isfinite (coefficient.c));

    assert (root != NULL);

    // TODO reduce nesting
    if (fabs (coefficient.b) < EPS)
    {
        if (fabs (coefficient.c) < EPS)
            return INFINITE_ROOTS;
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
