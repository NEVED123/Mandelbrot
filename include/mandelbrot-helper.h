#ifndef HELPER_H_
#define HELPER_H_

#include <stdio.h>
#include <complex.h>

double scale(int value, int fromLow, int fromHigh, int toLow, int toHigh);
int get_velocity(double _Complex c, int iterations);
double _Complex mandelbrot(double _Complex z, double _Complex c);

#endif // HELPER_H_
