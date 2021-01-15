#include "include/rotation.h"
#include "include/image.h"
#include <stdint.h>
#include <malloc.h>
#include "include/image.h"

struct image rotate90deg(const struct image  original){
    //init new image
    struct image rotated;

    //copy params (not forget to change order)
    rotated.width = original.height;
    rotated.height = original.width;
    rotated.data = (struct pixel*) malloc(rotated.width * rotated.height * sizeof(struct pixel));

    //rotate 90 deg
    for (size_t y = 0; y < original.height; y++)
        for (size_t x = 0; x < original.width; x++)
            rotated.data[(original.height - 1 - y) + original.height * x] = original.data[original.width * y + x];


    return rotated;
}

