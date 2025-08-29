#ifndef TESTS_H
#define TESTS_H

#include "ReadInput.h"
#include "SolveEquation.h"

struct TestParameters {
    Coefficients arg;
    RootsData vol;
};

void AllTests ();
void RunTest (TestParameters, int);

#endif
