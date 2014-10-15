#include "writer.h"
#include <time.h>
#include "shared_stuff.h"
#include <stdlib.h>

int main (int argc, char *argv[]){
    int i, file_num;
    char *rand_str;

    srand (time(NULL));

    for ( i = 0; i < CYCLE_COUNT; i++ ){
    	file_num = RANDOM_RANGE(0, 4);
    	rand_str = get_writer_string( RANDOM_RANGE(0, WRITER_STRING_COUNT - 1) );
		writer(file_num, rand_str, WRITER_STRING_LEN);
    }

    return 0;
}
