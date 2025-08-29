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
        return ZERO_ROOTS;

    if (fabs (discriminant) < EPS)
    {
        root -> x1 = -coefficient.b / (2 * coefficient.a);
        return ONE_ROOT;
    }
    double intermediateValue = sqrt (discriminant) / (2 * coefficient.a);
    root -> x1 = -coefficient.b/ (2 * coefficient.a) - intermediateValue;
    root -> x2 = root -> x1 + 2 * intermediateValue;
    return TWO_ROOTS;
}

RootsNumber SolveLinear (RootsData *root, Coefficients coefficient)
{
    assert (isfinite (coefficient.a));
    assert (isfinite (coefficient.b));
    assert (isfinite (coefficient.c));

    assert (root != NULL);

    if (fabs (coefficient.b) < EPS)
    {
        if (fabs (coefficient.c) < EPS)
            return INFINITE_ROOTS;

        return ZERO_ROOTS;
    } else
    {
        root -> x1 = -coefficient.c/coefficient.b;
        return ONE_ROOT;
    }
}
