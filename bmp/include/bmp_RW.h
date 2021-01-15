#ifndef ASSIGNMENT_IMAGE_ROTATION_BPM_RW_H
#define ASSIGNMENT_IMAGE_ROTATION_BPM_RW_H


#include <stdio.h>
#include "include/image.h"


//TODO check for other statuses
enum  write_status  {
    WRITE_OK = 0,
    WRITE_DATA_ERROR,
    WRITE_HEADER_ERROR
};

//TODO check for other statuses
enum read_status  {
    READ_OK = 0,
    READ_INVALID_SIGNATURE,
    READ_INVALID_BITS,
    READ_INVALID_HEADER,
    READ_INVALID_DATA_SIZE
};

enum read_status from_bmp( FILE* in, struct image* img );
enum write_status to_bmp( FILE* out, struct image const* img );

#endif //ASSIGNMENT_IMAGE_ROTATION_BPM_RW_H
