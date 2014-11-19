#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include "shared_stuff.h"
#include "writer.h"
#include "writer_constants.h"


int main(int argc, char *argv[]){
    int i, file_num;
    char *rand_str;
    int cycle_count;
    struct timeval time_now;

    /* use the current micro seconds as a random seed */
    gettimeofday(&time_now, NULL);
    srand (time_now.tv_usec);

    /* read cycle_count from argv */
    if (argc > 1) {
        sscanf(argv[1], "%d", &cycle_count);
	}
    else {
        cycle_count = TOTAL_WRITER_CYCLE_COUNT;
    }

    DBG_PRINTF("writer cycle_count: %d\n", cycle_count);

    for ( i = 0; i < cycle_count; i++ ) {
        file_num = RANDOM_RANGE(0, 4);
        rand_str = get_writer_string( RANDOM_RANGE(0, WRITER_STRING_COUNT - 1) );
        writer(file_num, rand_str, WRITER_STRING_LEN);
    }

    return 0;
}
