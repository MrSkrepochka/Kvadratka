#ifndef TESTS_H
#define TESTS_H

#include "ReadInput.h"
#include "SolveEquation.h"

struct TestParameters {
    Coefficients arg;
    RootsData values;
};

void RunAllTests ();
void RunTest (TestParameters, int);

#endif
