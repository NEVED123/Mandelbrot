#include "image.hpp"
#include <opencv2/core/mat.hpp>
#include <opencv2/core/hal/interface.h>

/*
    Functions to help with image manipulation.
*/

cv::Vec3b get_color_from_velocity(int velocity, int iterations){
    int light_value = (int) 255 * ((double) velocity/iterations);

    cv::Vec3b ret(light_value, light_value, light_value);

    return ret;
}