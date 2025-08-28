#ifndef INPUT_H
#define INPUT_H

struct Coefficients {
    double a;
    double b;
    double c;
};

bool ReadInput (Coefficients *coefficient);

#endif
