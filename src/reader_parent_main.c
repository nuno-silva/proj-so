#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#include "reader_parent_main.h"
#include "reader.h"
#include "shared_stuff.h"

int run_and_wait_for_children(int file_nums[], int children_count) {
    int fork_result;
    int i;
    
    for (i = 0; i < children_count; i++) {
    	fork_result = fork();
    	
    	if (fork_result == -1) {  // ERROR
            printf("fork() failed. errno=%d", errno);
    		return -1;
    	}
    	else if (fork_result == 0) {  // child
            DBG_PRINTF("child %d\n", i);
    		execl("reader", "reader", file_nums[i], NULL);
    	}
    	else {  // parent
            DBG_PRINTF("parent %d\n", i);
    	}
    }
    
    
    while (children_count--) { // wait for all children to terminate
        wait(NULL); // wait for one child
    }
    return 0;
}

int main(int argc, char* argv[]) {
	int file_nums[CHILDREN_COUNT];
	int i, j, temp;
    struct timeval time_now;
    
    // use the current micro seconds as a random seed
    gettimeofday(&time_now, NULL);
    srand (time_now.tv_usec);
	
	// generate random file numbers
	for (i = 0; i < CHILDREN_COUNT; i++) {
		temp = RANDOM_RANGE(0,4);
		for (j = 0; j < i; j++) {
			if (file_nums[i] == temp) {
				i--;
			}
			else{
				file_nums[i] = temp;
			}
		}
	}

	return run_and_wait_for_children(file_nums, CHILDREN_COUNT);
}
