#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#include "reader_parent_main_3.h"
#include "reader_constants.h"
#include "reader.h"
#include "shared_stuff.h"


void *reader_thread(void *arg) {
	thread_info_t thread_info = *((thread_info_t*) arg);
	int *ret = (int*) malloc( sizeof(int) );
	
	if (ret == NULL || arg == NULL)
		exit(-1);
	
	DBG_PRINTF("thread will read from %d to %d\n",
				thread_info.first_line, thread_info.last_line);
	
	*ret = reader_ranged(thread_info.file_num, thread_info.first_line, thread_info.last_line);
	
	pthread_exit((void*) ret);
}


int run_and_wait_for_threads(int file_num, int thread_count) {
	int i;
	int error;
	int portion_size, remaining;
	int last_thread_i;
	int **thread_results;
	pthread_t *threads;
	thread_info_t *thread_info;
	
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
    
	thread_info = (thread_info_t*) malloc( sizeof(thread_info_t) * thread_count );
	if (thread_info == NULL) {
		free(thread_results);
		free(threads);
		printf("Could not allocate memory for 'thread_info'\n");
		return -1;
	}
	
	portion_size	= LINES_PER_FILE / thread_count;
	remaining		= LINES_PER_FILE % thread_count;
	
	last_thread_i = thread_count - 1;
	
	// start threads
	for (i = 0; i < thread_count; i++) {
		// populate thread_info
		thread_info[i].file_num		= file_num;
		thread_info[i].first_line	= i * portion_size;
		thread_info[i].last_line	= thread_info[i].first_line + portion_size -1;
		
		if (i == last_thread_i) {
			thread_info[i].last_line += remaining;
		}
		
		error = pthread_create( threads+i, NULL, reader_thread, thread_info + i );
		if (error != 0) {
			printf("Error %d: Could not create thread %d\n", error, i);
			free(thread_results);
			free(threads);
			free(thread_info);
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
			free(thread_info);
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
				free(thread_info);
				return -1;
			}
		}
	}
	
	free(thread_results);
	free(threads);
	free(thread_info);
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
	
	DBG_PRINTF("file_num = %d\n", file_num);
	
	return run_and_wait_for_threads(file_num, READER_3_THREAD_COUNT);
}
