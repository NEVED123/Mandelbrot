#include "image.hpp"
#include <opencv2/core/mat.hpp>
#include <opencv2/core/hal/interface.h>
#include <math.h>
#include "mandelbrot-helper.hpp" 

/*
    Functions to help with image manipulation.
*/

cv::Vec3b get_color_from_velocity(int velocity, int iterations){
    
    //The idea here is that most points to not take more than a hundred points to
    //Escape. Therefore, we end up with velocity/iteration fractions very close to one
    //resulting in almost entirely black/white images. Raising the fraction to the power of 512
    //Creates a steeper color curve for the high values of velocity. Note that 512 is arbitrary 
    double light_value = pow((double) velocity / iterations, 512);
    double light_value_scaled = light_value * 255;

    int r = 0;
    int g = 0;
    int b = 0;

    if(light_value < 1/7.0) {
        r = light_value_scaled;
    } else if (light_value< 2/7.0) {
        r = light_value_scaled;
        b = light_value_scaled;
    } else if (light_value< 3/7.0) {
        r = 1 - light_value_scaled;
        b = light_value_scaled;
    } else if (light_value< 4/7.0){
        g = light_value_scaled;
        b = light_value_scaled;
    } else if (light_value< 5/7.0) {
        g = light_value_scaled;
        b = 1 - light_value_scaled;
    } else if (light_value< 6/7.0){
        r = light_value_scaled;
        g = light_value_scaled;
    } else {
        r = light_value_scaled;
        g = light_value_scaled;
        b = light_value_scaled;
    }
    
    //  0/7       1/7      2/7      3/7     4/7      5/7      6/7      7/7
    // 000000 - FF0000 - FF00FF - 0000FF - 00FFFF - 00FF00 - FFFF00 - FFFFFF

    cv::Vec3b ret(r, g, b);

    return ret;
}