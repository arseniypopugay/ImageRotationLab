#include <stdio.h>
#include "include/fileOpenClose.h"

enum open_status open_file(FILE** in, const char* path, const char* type)
{
    *in = fopen(path, type);
    if (*in == NULL) return OPEN_NULL;
    return OPEN_OK;
}

enum close_status close_file(FILE** out)
{
    int status = fclose(*out);
    if (!status)
        return CLOSE_OK;
    return CLOSE_WRONG;
}