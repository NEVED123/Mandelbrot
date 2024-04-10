#include <complex.h>
#include "mandelbrot-helper.hpp" 
/*
    Functions to help with the actual mandelbrot calcuations
*/

// scales a value from one range to another
double scale(int value, int fromLow, int fromHigh, int toLow, int toHigh) {
    return (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
}

// determines the escape velocity of a given complex number, returning a 0 indicates that it does not escape
// and should be colored black by the renderer
int get_velocity(std::complex<double> c, int iterations) {
    std::complex<double> z = 0;
    for (int i = 0; i < iterations; i++) {
        z = mandelbrot(z, c);
        if (abs(z) > 2) {
            return iterations - i;
        }
    }

    return 0;
}

// the actual mandelbrot function
std::complex<double> mandelbrot(std::complex<double> z, std::complex<double> c) {
    return pow(z, 2) + c;
}