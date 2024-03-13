#include "image.h" //Relative paths here are bad practice, but fuck it

/*
    Functions to help with image generation and management
    The types "Image" and "Color" are placeholders until we know
    the types we will use - that will depend on the libaries.
*/

Color get_color_from_velocity(int velocity, int max_iterations){
    Color ret;

    ret.hue = 170; // light blue, arbitrarily picked
    ret.saturation = 100;
    ret.lightness = (int) 100 * velocity/max_iterations;

    return ret;
}

Image get_image(int width, int height) {
    // TODO: implement
}


void put_pixel(Image image, Color color, int x_pixel, int y_pixel) {
    // TODO: implement
}