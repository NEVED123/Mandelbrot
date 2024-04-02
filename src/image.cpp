#include "image.hpp"
#include <opencv2/core/mat.hpp>
#include <opencv2/core/hal/interface.h>

/*
    Functions to help with image manipulation.
*/

cv::Vec3b get_color_from_velocity(int velocity){
    int light_value = (int) 255 * velocity/1000; // 1000 is the max number of iterations

    cv::Vec3b ret(light_value, light_value, light_value);

    return ret;
}

cv::Mat get_image(int width, int height) {
    // returns blank image
    return cv::Mat::Mat (width, height, cv::CV_8U);
}

void put_pixel(cv::Mat image, cv::Vec3b color, int x_pixel, int y_pixel) {
    // puts a certain color on a certain pixel
    image[y_pixel,x_pixel] = color;
}
