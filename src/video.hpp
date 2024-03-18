#pragma once

#include "image.hpp"
#include <opencv2/videoio.hpp>

/*
    Functions to help with video manipulation.
*/

cv::VideoWriter get_video();
void add_frame(cv::VideoWriter video, cv::Mat image);
void save_video(cv::VideoWriter video, char* path);
