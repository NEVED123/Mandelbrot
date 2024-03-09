#include <stdio.h>
#include <time.h>
#include "image.h"
#include "mandelbrot-helper.h"
#include "video.h"

int main (int argc, char *argv[]) {
    printf("Beginning serial mandelbrot generation!\n");
    // --- Arguments --- TODO - Create a bash script that will handle arguments/flags, sounds like Eli would have fun with this

    int num_frames = 24 * 30; //24 frames per second to create 30 second video
    int iterations = 1000; //This is the number of iterations we will use to calculate the velocity of the mandelbrot set
    int width = 1920;
    int height = 1080;

    // According to https://en.wikipedia.org/wiki/Misiurewicz_point, this is a good point to zoom in on. Will set it as this for default
    double zoom_point_real = -.77568377;
    double zoom_point_imaginary = .13646737;
    double zoom_factor = .001; //This is the amount we will zoom in by between each frame

    //These will change as we zoom in, real and imaginary max and min.
    //Keeping them as real numbers for now, since the imaginary conversion happens in in the loop.
    double r_min = -2;
    double x_max = 2;
    double i_min = -2;
    double i_max = 2;

    // Video video = get_video();
    // for (int i = 0; i < num_frames; i++) {
    //     Image image = get_image(width, height);
    //     for (int x = 0; x < width; x++) {
    //         for (int y = 0; y < height; y++) {
    //             double real = scale(x, 0, width, r_min, x_max); 
    //             double _Complex imaginary = scale(y, 0, height, i_min, i_max) * I; //We are scaling to complex plane, so we need to multiply by I
    //             int v = get_velocity(real + imaginary, iterations);
    //             Color color = get_color_from_velocity(v);
    //             put_pixel(image, color, x, y);
    //         }
    //     }

    //     add_frame(video, image);

    //     NOTE: At this point in the loop, we will need to change the bounds of the mandelbrot set to create the zoom effect.
    //     If we go deep enough, this may require the use of arbitrary precision libraries to handle the numbers. We will cross this bridge.
    //     I'm not sure how the math works out to do this well, but sounds like a good Eli task to me.
    // }

    // save_video(video, "mandelbrot.mp4");
    return 0;
}