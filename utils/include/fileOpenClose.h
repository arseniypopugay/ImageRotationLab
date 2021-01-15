#ifndef ASSIGNMENT_IMAGE_ROTATION_FILEOPENCLOSE_H
#define ASSIGNMENT_IMAGE_ROTATION_FILEOPENCLOSE_H

#include <stdio.h>

//TODO check for other open statuses
enum open_status  {
    OPEN_OK = 0,
    OPEN_NULL
    /* коды других ошибок  */
};

//TODO check for other open statuses
enum close_status {
    CLOSE_OK = 0,
    CLOSE_WRONG
};

enum open_status open_file(FILE** in, const char* path, const char* type);
enum close_status close_file(FILE** out);


#endif //ASSIGNMENT_IMAGE_ROTATION_FILEOPENCLOSE_H
