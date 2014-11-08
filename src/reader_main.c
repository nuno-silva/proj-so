#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include "reader.h"
#include "shared_stuff.h"

int main(int argc, char* argv[]) {
	int file_num;
	struct timeval time_now;

	if (argc < 2) {
		// No file number provided, generate a random one
		gettimeofday(&time_now, NULL);
		srand (time_now.tv_usec);
		file_num = RANDOM_RANGE(0, 4);
	}
	else {
		// File number provided, use that one
		file_num = atoi(argv[1]);
	}
	return reader(file_num);
}
