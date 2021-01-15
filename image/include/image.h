#ifndef ASSIGNMENT_IMAGE_ROTATION_IMAGE_PIXEL_H
#define ASSIGNMENT_IMAGE_ROTATION_IMAGE_PIXEL_H

#include <stdint.h>

struct image {
    uint64_t width, height;
    struct pixel* data;
};

struct pixel {
    uint8_t b, g, r;
};
#endif