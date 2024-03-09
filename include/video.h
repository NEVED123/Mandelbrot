#ifndef _VIDEO_H_
#define _VIDEO_H_

#include "image.h"

typedef struct {
    //Placeholder
} Video;

Video get_video();
void add_frame(Video video, Image image);
void save_video(Video video, char* path);

#endif // _VIDEO_H_