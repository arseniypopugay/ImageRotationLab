#include <stdbool.h>
#include <stdio.h>
#include "include/bmp.h"
#include "include/util.h"
#include "include/image.h"
#include "include/fileOpenClose.h"
#include "include/bmp_RW.h"
#include "include/rotation.h"

void usage() {
    fprintf(stderr, "Usage: ./image_rotate BMP_FILE_NAME OUTPUT_BMP_FILE_NAME\n");
}

int main( int argc, char** argv ) {
    if (argc != 3) usage();
    if (argc < 3) err("Not enough arguments \n" );
    if (argc > 3) err("Too many arguments \n" );


    FILE* input_file;
    FILE* output_file;

    switch (open_file(&input_file, argv[1], "rb")) {
        case OPEN_NULL:
            err("");
        case OPEN_OK:
            break;
    }

    switch (open_file(&output_file, argv[2], "wb")) {
        case OPEN_NULL:
            err("");
        case OPEN_OK:
            break;
    }

    struct image img = {0};

    switch (from_bmp(input_file, &img)) {
        case READ_INVALID_DATA_SIZE:
            err("Invalid pixel-data of file");
        case READ_INVALID_HEADER:
            err("Invalid header of file");
        case READ_INVALID_BITS:
            err("Invalid bits per pixel of file");
        case READ_INVALID_SIGNATURE:
            err("Invalid signature of file");
        case READ_OK:
            break;
    }

    struct image new_img = rotate90deg(img);

    switch (to_bmp(output_file, &new_img)) {
        case WRITE_DATA_ERROR:
            err("Promlen with pixels writing");
        case WRITE_HEADER_ERROR:
            err("Problem with header writing");
        case WRITE_OK:
            break;
    }

    switch (close_file(&input_file)) {
        case CLOSE_WRONG:
            err("Error while closing file");
        case CLOSE_OK:
            break;
    }

    switch (close_file(&output_file)) {
        case CLOSE_WRONG:
            err("Error while closing file");
        case CLOSE_OK:
            break;
    }

    return 0;

}
