#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "image.hpp"
#include "mandelbrot-helper.hpp"
#include "video.hpp"
#include <args/parser.hpp>
#include <numeric>
#include <vector>
#include <string.h>
#include <opencv2/core/mat.hpp>

// only links OMP if we are going to use it, this is why it is a bit faster to do that gross command
#ifdef OMP
    #include "omp.h"
#endif

int iterations = 1000; //This is the number of iterations we will use to calculate the velocity of the mandelbrot set
int width = 1920;
int height = 1080;

//These will change as we zoom in, real and imaginary max and min.
//Keeping them as real numbers for now, since the imaginary conversion happens in in the loop.
double r_min = -2;
double r_max = 2;
double i_min = -2;
double i_max = 2;

void serial() {

}

void parallel() {
    printf("Beginning parallel mandelbrot generation!\n");
}

int main (int argc, char *argv[]) {

    std::string zoom_point_imaginary_string = ".13646737";
    std::string zoom_point_real_string = "-.77568377";
    std::string zoom_factor_string = ".001";

    args::null_translator tr{};
    args::parser parser{"Generate a mandelbrot zoom video.",
        args::from_main(argc, argv), &tr};
    parser.arg<int>(iterations, "iterations", "i")
        .opt()
        .help("Number of iterations to calculate velocity (default: 1000)");
    parser.arg<int>(width, "width", "w")
        .opt()
        .help("Width of the image (default: 1920)");
    parser.arg<int>(height, "height", "h")
        .opt()
        .help("Height of the image (default: 1080)");
    parser.arg<double>(r_min, "r_min")
        .opt()
        .help("Minimum real value (default: -2)");
    parser.arg<double>(r_max, "r_max")
        .opt()
        .help("Maximum real value (default: 2)");
    parser.arg<double>(i_min, "i_min")
        .opt()
        .help("Minimum imaginary value (default: -2)");
    parser.arg<double>(i_max, "i_max")
        .opt()
        .help("Maximum imaginary value (default: 2)");

    parser.parse();

    //This command line library is really nice, but cannot accept doubles, so we interpret as a string then convert
    zoom_point_real = std::stod(zoom_point_real_string);
    zoom_point_imaginary = std::stod(zoom_point_imaginary_string);
    zoom_factor = std::stod(zoom_factor_string);

    // If the OMP flag is on, it will trigger the parallel version - otherwise it will do the serial version
    #ifdef OMP
        parallel();
    #else
        serial();
    #endif

    return 0;
}

