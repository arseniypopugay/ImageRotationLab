#include "include/bmp_RW.h"
#include "include/image.h"
#include "include/fileOpenClose.h"
#include "include/bmp.h"
#include <inttypes.h>
#include <stdio.h>
#include <malloc.h>

uint32_t count_padding(const uint32_t width)
{
    return width * sizeof(struct pixel) % 4 ? 4 - width * sizeof(struct pixel) % 4 : 0;
}

struct bmp_header construct_bmp_header(const struct image* img){
    struct bmp_header header = {0};
    header.bfType = 19778;
    header.bfileSize = ((img->width)*sizeof(struct pixel) + count_padding(img->width))*(img->height);
    header.bOffBits= sizeof(struct bmp_header);
    header.biSize = 40;
    header.biWidth = img->width;
    header.biHeight = img->height;
    header.biPlanes = 1;
    header.biBitCount = 24;
    return header;
}


enum read_status from_bmp( FILE* in, struct image* img )
{
    struct bmp_header header;

    if (fread( &header, sizeof( struct bmp_header ), 1, in) != 1)
        return READ_INVALID_HEADER;

    img->width = header.biWidth;
    img->height = header.biHeight;
    img->data = malloc(img->height * img -> height * sizeof(struct pixel));

    if (header.bfType!=19778)
        return READ_INVALID_SIGNATURE;

    if (header.biBitCount!=24)
        return READ_INVALID_BITS;


    uint32_t padding = count_padding(img->width);

    for (size_t y = 0; y < img->height; y++) {
        if (fread(img->data + y * (img->width), sizeof(struct pixel), img->width, in) != img->width)
            return READ_INVALID_DATA_SIZE;
        if(fseek(in, padding, SEEK_CUR))
            return READ_INVALID_DATA_SIZE;
    }

    return READ_OK;
}



enum write_status to_bmp( FILE* out, struct image const* img )
{
    uint32_t padding = count_padding(img->width);
    struct bmp_header header = construct_bmp_header(img);

    if (!fwrite(&header, 1, sizeof(struct bmp_header), out))
        return WRITE_HEADER_ERROR;

    char zeros[4] = {0};
    for (size_t y = 0; y < img->height; y++)
    {
        if (fwrite(img->data + y*(img->width), sizeof(struct pixel), img->width, out) != img->width)
            return WRITE_DATA_ERROR;
        if (fwrite(zeros, sizeof(char), padding, out) != padding)
            return WRITE_DATA_ERROR;
    }

    return WRITE_OK;

}
