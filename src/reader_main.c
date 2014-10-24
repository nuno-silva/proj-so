#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include "shared_stuff.h"
#include "reader.h"

int main() {
    int file_num;
    struct timeval time_now;

    gettimeofday(&time_now, NULL);
    srand (time_now.tv_usec);

    file_num = RANDOM_RANGE(0, 4);

    return reader(file_num);
}
