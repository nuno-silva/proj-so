#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#include "reader_parent_main.h"
#include "shared_stuff.h"
#include "reader_constants.h"

int run_and_wait_for_children(int file_nums[], int children_count) {
    int fork_result;
    int i;
    char arg[32];
    int status, exit_value;
    
    for (i = 0; i < children_count; i++) {
    	fork_result = fork();
    	
    	if (fork_result == -1) {  // ERROR
            printf("fork() failed. errno=%d", errno);
    		return -1;
    	}
    	else if (fork_result == 0) {  // child
            DBG_PRINTF("child %d\n", i);
            sprintf(arg, "%d", file_nums[i]);
    		execl("reader", "reader", arg, NULL);
    	}
    	else {  // parent
            DBG_PRINTF("parent %d\n", i);
    	}
    }
    
    
    while (children_count--) { // wait for all children to terminate
        if (wait(&status) == -1) { // wait for one child
            printf("wait() failed. errno=%d", errno);
        }
        else {
            if (WIFEXITED(status)) {
                exit_value = (char) WEXITSTATUS(status);
                printf("Child exited with value %d\n", exit_value);
            }
            else {
                printf("Child exited abnormally\n");
            }
        }
    }
    return 0;
}

int main() {
	int file_nums[READER_CHILDREN_COUNT];
	int i;
    struct timeval time_now;
    
    // use the current micro seconds as a random seed
    gettimeofday(&time_now, NULL);
    srand (time_now.tv_usec);
	
	// generate random file numbers
	for (i = 0; i < READER_CHILDREN_COUNT; i++) {
		file_nums[i] = RANDOM_RANGE(0, 4);
	}

	return run_and_wait_for_children(file_nums, READER_CHILDREN_COUNT);
}
