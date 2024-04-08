#include <stdio.h>
#include <time.h>
#include <complex.h>
#include "image.hpp"
#include "mandelbrot-helper.hpp"
#include "video.hpp"
#include "opencv2/opencv.hpp"

// only links OMP if we are going to use it, this is why it is a bit faster to do that gross command
#ifdef OMP
    #include "omp.h"
#endif

int num_frames = 24 * 30; //24 frames per second to create 30 second video
int iterations = 10000; //This is the number of iterations we will use to calculate the veloci   ty of the mandelbrot set
int width = 1000;
int height = 1000;

// According to https://en.wikipedia.org/wiki/Misiurewicz_point, this is a good point to zoom in on. Will set it as this for default
double zoom_point_real = -.77568377;
double zoom_point_imaginary = .13646737;
double zoom_factor = .001; //This is the amount we will zoom in by between each frame

//These will change as we zoom in, real and imaginary max and min.
//Keeping them as real numbers for now, since the imaginary conversion happens in in the loop.
double r_min = -2;
double r_max = 2;
double i_min = -2;
double i_max = 2;

void serial() {
    printf("bruh serial mandelbrot generation\n");

    // Create a blank black image (assuming you want it black)
    cv::Mat image = cv::Mat::zeros(height, width, CV_8UC3);

    // Add colored pixels to the image
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            double x_scaled = scale(x, 0, width, r_min, r_max);
            double y_scaled = scale(y, 0, height, i_min, i_max);

            std::complex<double> c = std::complex(x_scaled, y_scaled);
            int velocity = get_velocity(c, iterations);
            cv::Vec3b color = get_color_from_velocity(velocity, iterations);

            image.at<cv::Vec3b>(y, x) = color;
        }
    }

    // Display the image
    cv::imwrite("output_image.jpg", image);

    printf("done\n");
}

void parallel() {
    printf("Beginning parallel mandelbrot generation!\n");
}

int main (int argc, char *argv[]) {

    // --- Arguments --- TODO - Create a bash script that will handle arguments/flags, I will get on this to make our lives easier

    // If the OMP flag is on, it will trigger the parallel version - otherwise it will do the serial version
    #ifdef OMP=ON
        parallel();
    #else
        serial();
    #endif

    return 0;
}

