#ifndef SOLVE_H
#define SOLVE_H

#include "ReadInput.h"

enum RootsNumber {
    ZERO_ROOTS = 0, 
    ONE_ROOT = 1,
    TWO_ROOTS = 2,
    INFINITE_ROOTS =-1,
};

struct RootsData {
    RootsNumber number;
    double x1;
    double x2;
};
const double EPS = 1e-6;

RootsNumber SolveLinear (RootsData *root, Coefficients coefficient);
RootsNumber SolveQuadratic (Coefficients coefficient, RootsData *root);
RootsNumber SolveEquation (Coefficients coefficient, RootsData *root);

#endif
