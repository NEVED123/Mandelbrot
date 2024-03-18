#pragma once

#include <opencv2/core/mat.hpp>

cv::Vec3b get_color_from_velocity(int velocity);
cv::Mat get_image(int width, int height);
void put_pixel(cv::Mat image, cv::Vec3b color, int x_pixel, int y_pixel);

