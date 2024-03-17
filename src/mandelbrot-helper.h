#pragma once

#include <stdio.h>
#include <complex.h>

/*
    Functions to help with the actual mandelbrot calcuations
*/

double scale(int value, int fromLow, int fromHigh, int toLow, int toHigh);
int get_velocity(std::complex<double> c, int iterations);
std::complex<double> mandelbrot(std::complex<double> z, std::complex<double> c);
