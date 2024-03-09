#include <complex.h>
#include <tgmath.h>
#include "mandelbrot-helper.h" //Relative paths here are bad practice, but fuck it

/*
    Functions to help with the actual mandelbrot calcuations
*/

// scales a value from one range to another
double scale(int value, int fromLow, int fromHigh, int toLow, int toHigh) {
    return (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
}

// determines the escape velocity of a given complex number, returning a 0 indicates that it does not escape
// and should be colored black by the renderer
int get_velocity(double _Complex c, int iterations) {
    double _Complex z = 0;
    for (int i = 0; i < iterations; i++) {
        z = mandelbrot(z, c);
        if (cabs(z) > 2) {
            return iterations - i;
        }
    }

    return 0;
}

// the actual mandelbrot function
double _Complex mandelbrot(double _Complex z, double _Complex c) {
    return cpow(z, 2) + c;
}