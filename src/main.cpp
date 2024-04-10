#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <complex.h>
#include "image.hpp"
#include "mandelbrot-helper.hpp"
#include "opencv2/opencv.hpp"
#include <args/parser.hpp>
#include <omp.h>

int iterations = 10000; //This is the number of iterations we will use to calculate the velocity of the mandelbrot set
int res = 1000;

std::string r_min_string = "-2";
std::string r_max_string = "2";
std::string i_min_string = "-2";
std::string i_max_string = "2";

double r_min = -2;
double r_max = 2;
double i_min = -2;
double i_max = 2;

int threads = 1;

void generate_mandelbrot_image(int num_of_threads) {
    printf("Beginning parallel Mandelbrot generation with %d threads!\n", num_of_threads);

    //Goofy trick to round double
    int width = res * (int)(r_max - r_min + .5);
    int height = res * (int)(i_max - i_min + .5);

    // Set the number of threads
    omp_set_num_threads(num_of_threads);

    // Create a private image for each thread
    std::vector<cv::Mat> private_images(omp_get_max_threads(), cv::Mat::zeros(height, width, CV_8UC3));

    #pragma omp parallel for collapse(2) firstprivate(private_images)
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double x_scaled = scale(x, 0, width, r_min, r_max);
            double y_scaled = scale(y, 0, height, i_min, i_max);

            std::complex<double> c = std::complex(x_scaled, y_scaled);
            int velocity = get_velocity(c, iterations);
            cv::Vec3b color = get_color_from_velocity(velocity, iterations);

            private_images[omp_get_thread_num()].at<cv::Vec3b>(y, x) = color;
        }
    }

    // Combine private images into the final image
    cv::Mat image = cv::Mat::zeros(height, width, CV_8UC3);
    for (auto& private_image : private_images) {
        image += private_image;
    }

    // Display the image
    if (!cv::imwrite("output_image.jpg", image)) {
        fprintf(stderr, "Error writing output image.\n");
    }

    printf("Done\n");
}

int main (int argc, char *argv[]) {

    args::null_translator tr{};
    args::parser parser{"Generate a mandelbrot zoom image.",
    args::from_main(argc, argv), &tr};
    parser.arg<int>(iterations, "iterations", "i")
        .opt()
        .help("Number of iterations to calculate velocity (default: 1000)");
    parser.arg<int>(res, "resolution", "r")
        .opt()
        .help("resolution of the image in pixels per unit^2 (default: 1000)");
    parser.arg<std::string>(r_min_string, "r_min")
        .opt()
        .help("Minimum real value (default: -2)");
    parser.arg<std::string>(r_max_string, "r_max")
        .opt()
        .help("Maximum real value (default: 2)");
    parser.arg<std::string>(i_min_string, "i_min")
        .opt()
        .help("Minimum imaginary value (default: -2)");
    parser.arg<std::string>(i_max_string, "i_max")
        .opt()
        .help("Maximum imaginary value (default: 2)");
    parser.arg<int>(threads, "threads", "t")
        .opt()
        .help("Maximum imaginary value (default: 1)");

    parser.parse();

    r_min = std::stod(r_min_string);
    r_max = std::stod(r_max_string);
    i_min = std::stod(i_min_string);
    i_max = std::stod(i_max_string);

    double start_time = omp_get_wtime();
    generate_mandelbrot_image(threads);
    double elapsed_time = omp_get_wtime() - start_time;
    printf("finished in %.2f seconds\n", elapsed_time);

    return 0;
}

    

