#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#include "reader_parent_main_3.h"
#include "reader_constants.h"
#include "reader.h"
#include "shared_stuff.h"


void* reader_thread(int file_num) {
    int *ret = (int*) malloc( sizeof(int) );
    
    if (ret == NULL)
        exit(-1);
    
    *ret = reader(file_num);
    
    pthread_exit((void*) ret);
}


int run_and_wait_for_threads(int file_num, int thread_count) {
    int i;
    int error;
    int portion_size, remaining;
    int **thread_results;
    pthread_t *threads;
    
    thread_results = (int**) malloc( sizeof(int*) * thread_count );
    if (thread_results == NULL) {
        DBG_PRINTF("Could not allocate memory for 'thread_results'\n");
        return -1;
    }
    
    threads = (pthread_t*) malloc( sizeof(pthread_t) * thread_count );
    if (threads == NULL) {
        free(thread_results);
        DBG_PRINTF("Could not allocate memory for 'threads'\n");
        return -1;
    }
    
    portion_size = LINES_PER_FILE / thread_count;
    remaining = LINES_PER_FILE % thread_count;
    
    // TODO: make each thread read a portion of ONE file
    // start threads
    for (i = 0; i < thread_count; i++) {
        error = pthread_create( threads+i, NULL, reader_thread(i), file_nums+i );
        if (error != 0) {
            printf("Could not create thread %d\n", i);
            return -1;
        }
    }
    
    // wait for threads
    for (i = 0; i < thread_count; i++) {
        error = pthread_join(threads[i], (void**) &(thread_results[i]));
        if (error != 0) {
            printf("Thread %d could not be suspended\n", i);
            return -1;
        }
        else {
            if (thread_results[i] != NULL) {
                printf("Thread %d returned %d\n", i, *thread_results[i]);
                free(thread_results[i]);
            }
            else {
                printf("Thread %d returned nothing\n", i);
                return -1;
            }
        }
    }
    
    free(thread_results);
    free(threads);
    return 0;
}

int main(void) {
    int file_num;
    struct timeval time_now;
    
    // use the current micro seconds as a random seed
    gettimeofday(&time_now, NULL);
    srand(time_now.tv_usec);
	
	// generate random file number
	file_num = RANDOM_RANGE(0, 4);

	return run_and_wait_for_threads(file_num, READER_3_THREAD_COUNT);
}
