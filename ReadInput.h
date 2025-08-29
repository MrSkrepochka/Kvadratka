#ifndef INPUT_H
#define INPUT_H

struct Coefficients {
    double a;
    double b;
    double c;
};

void ClearBuffer();
bool ReadInput (Coefficients *coefficient);

#endif
