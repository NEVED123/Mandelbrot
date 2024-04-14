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
int width = 0;
int height = 0;

double r_min = -2;
double r_max = 2;
double i_min = -2;
double i_max = 2;

double zoom_point_real = 0;
double zoom_point_imaginary = 0;
double real_bound = 2;
double imaginary_bound = 2;

int threads = 1;

void generate_mandelbrot_image(int num_of_threads) {
    printf("Beginning parallel Mandelbrot generation with %d threads!\n", num_of_threads);

    omp_set_num_threads(num_of_threads);

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

    cv::Mat image = cv::Mat::zeros(height, width, CV_8UC3);
    for (auto& private_image : private_images) {
        image += private_image; 
    }

    if (!cv::imwrite("output_image.jpg", image)) {
        printf("Error writing output image.\n");
    } else{
        printf("Done!\n");
    }
}

int main (int argc, char *argv[]) {

    std::string zoom_point_real_string = "0";
    std::string zoom_point_imaginary_string = "0";
    std::string real_bound_string = "2";
    std::string imaginary_bound_string = "2";

    args::null_translator tr{};
    args::parser parser{"Generate a mandelbrot zoom image.",
    args::from_main(argc, argv), &tr};
    parser.arg<int>(iterations, "iterations", "i")
        .opt()
        .help("Number of iterations to calculate velocity (default: 1000)");
    parser.arg<int>(res, "resolution", "r")
        .opt()
        .help("resolution of the image in pixels of the larger side, with the smaller side being scaled appropriately (default: 1000)");
    parser.arg<std::string>(zoom_point_real_string, "zoom_point_real")
        .opt()
        .help("Real point to zoom in on (default: 0)");
    parser.arg<std::string>(zoom_point_imaginary_string, "zoom_point_imaginary")
        .opt()
        .help("Imaginary point to zoom in on (default: 0)");
    parser.arg<std::string>(real_bound_string, "real_bound")
        .opt()
        .help("Real bound of the zoom += zoom_point_real (default: 2)");
    parser.arg<std::string>(imaginary_bound_string, "imaginary_bound")
        .opt()
        .help("Imaginary bound of the zoom += zoom_point_imaginary (default: 2)");
    parser.arg<int>(threads, "threads", "t")
        .opt()
        .help("Maximum imaginary value (default: 1)");

    parser.parse();

    zoom_point_real = std::stod(zoom_point_real_string);
    zoom_point_imaginary = std::stod(zoom_point_imaginary_string);
    real_bound = std::stod(real_bound_string);
    imaginary_bound = std::stod(imaginary_bound_string);

    r_max = zoom_point_real + real_bound;
    r_min = zoom_point_real - real_bound;
    i_max = zoom_point_imaginary + imaginary_bound;
    i_min = zoom_point_imaginary - imaginary_bound;


    if(r_max - r_min > i_max - i_min){
        width = res;
        height = (int)(res * (i_max - i_min) / (r_max - r_min));
    }
    else if(r_max - r_min < i_max - i_min){
        height = res;
        width = (int)(res * (r_max - r_min) / (i_max - i_min));
    } 
    else {
        width = res;
        height = res;
    }

    double start_time = omp_get_wtime();
    generate_mandelbrot_image(threads);
    double elapsed_time = omp_get_wtime() - start_time;
    printf("finished in %.2f seconds\n", elapsed_time);

    return 0;
}

    

