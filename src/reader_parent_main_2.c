#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#include "reader_parent_main_2.h"
#include "reader_constants.h"
#include "reader.h"
#include "shared_stuff.h"

void *reader_thread(void *arg) {
    int file_num = *((int*) arg);
    int *ret = (int*) malloc( sizeof(int) );
    
    if (ret == NULL || arg == NULL)
        exit(-1);
    
    *ret = reader(file_num);
    
    pthread_exit((void*) ret);
}


int run_and_wait_for_threads(int *file_nums, int thread_count) {
    int i;
    int error;
    int **thread_results;
    pthread_t *threads;
    
    thread_results = (int**) malloc( sizeof(int*) * thread_count );
    if (thread_results == NULL) {
        printf("Could not allocate memory for 'thread_results'\n");
        return -1;
    }
    
    threads = (pthread_t*) malloc( sizeof(pthread_t) * thread_count );
    if (threads == NULL) {
        free(thread_results);
        printf("Could not allocate memory for 'threads'\n");
        return -1;
    }
    
    // start threads
    for (i = 0; i < thread_count; i++) {
        error = pthread_create( threads+i, NULL, reader_thread, file_nums+i );
        if (error != 0) {
            printf("Error %d: Could not create thread %d\n", error, i);
            free(thread_results);
            free(threads);
            return -1;
        }
    }
    
    // wait for threads
    for (i = 0; i < thread_count; i++) {
        error = pthread_join(threads[i], (void**) &(thread_results[i]));
        if (error != 0) {
            printf("Error %d: Thread %d could not be suspended\n", error, i);
            free(thread_results);
			free(threads);
            return -1;
        }
        else {
            if (thread_results[i] != NULL) {
                printf("Thread %d returned %d\n", i, *thread_results[i]);
                free(thread_results[i]);
            }
            else {
                printf("Thread %d returned nothing\n", i);
                free(thread_results);
				free(threads);
                return -1;
            }
        }
    }
    
    free(thread_results);
    free(threads);
    return 0;
}

int main(void) {
    int file_nums[READER_2_THREAD_COUNT];
	int i;
    struct timeval time_now;
    
    // use the current micro seconds as a random seed
    gettimeofday(&time_now, NULL);
    srand(time_now.tv_usec);
	
	// generate random file numbers
	for (i = 0; i < READER_2_THREAD_COUNT; i++) {
		file_nums[i] = RANDOM_RANGE(0, 4);
	}

	return run_and_wait_for_threads(file_nums, READER_2_THREAD_COUNT);
}