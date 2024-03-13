#ifndef _IMAGE_H_
#define _IMAGE_H_

typedef struct {
    // Placeholder
    int width;
    int height;
} Image;

typedef struct {
    // Placeholder
    int hue; // 0-360
    int saturation; // 0-100
    int value; // 0-100
} Color;

Color get_color_from_velocity(int velocity);
Image get_image(int width, int height);
void put_pixel(Image image, Color color, int x_pixel, int y_pixel);

#endif // _IMAGE_H_

