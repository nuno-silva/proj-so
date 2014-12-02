#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>

#include "reader.h"
#include "reader_constants.h"
#include "reader_parent_main.h"
#include "shared_stuff.h"

char *Buffer_filename;

void *reader_thread(void *arg) {
	thread_info_t thread_info = *((thread_info_t*) arg);
	int *ret = (int*) malloc( sizeof(int) );
	int file_num;

	if (ret == NULL || arg == NULL)
		exit(-1);

	DBG_PRINTF("thread will read from %d to %d\n",
	thread_info.first_line, thread_info.last_line);

	file_num = atoi(&thread_info.filename[7]);

	*ret = reader_ranged(file_num, thread_info.first_line, thread_info.last_line);

	pthread_exit((void*) ret);
}

int run_and_wait_for_threads(int thread_count) {
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

	/* start threads */
	for (i = 0; i < thread_count; i++) {
		DBG_PRINT("Populating thread_info.\n");
		thread_info[i].filename = malloc(sizeof(char)*strlen(Buffer_filename));

		/* populate thread_info */
		strcpy(thread_info[i].filename, Buffer_filename);
		thread_info[i].first_line	= i * portion_size;
		thread_info[i].last_line	= thread_info[i].first_line + portion_size - 1;
		DBG_PRINTF("index = %d", i);

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

	/* wait for threads */
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
	int filename_size = sizeof(char)*FILENAME_LEN;
	struct timeval time_now;

	/* use the current micro seconds as a random seed */
	gettimeofday(&time_now, NULL);
	srand(time_now.tv_usec);

	/* Initializing buffer */
	Buffer_filename = (char*) malloc(filename_size);

	while (TRUE){
		read(0, Buffer_filename, filename_size);

		/* Removing trailing '\n' */
		Buffer_filename[strlen(Buffer_filename) - 1] = '\0';

		DBG_PRINTF("filename = %s\n", Buffer_filename);

		run_and_wait_for_threads(READER_THREAD_COUNT);
	}

	return 0;
}
