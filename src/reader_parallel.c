#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>

#include "reader.h"
#include "reader_constants.h"
#include "reader_parallel.h"
#include "shared_stuff.h"
#include "shared_buffer.h"


#define ITEM_BUFFER_SIZE 10

shared_buffer_t Item_Buffer;

void *reader_thread(void *arg) {
	(void) arg; /* suppress unused variable warning */

	DBG_PRINT("Reader thread running\n");
	
	/* TODO: consume */
	/* TODO: process */
	/* TODO: free */
	return NULL;
}

int run_threads(pthread_t **threads, int thread_count) {
	int i,
		error;
	if (threads == NULL) {
		return 0;
	}
	
	*threads = (pthread_t*) malloc( sizeof(pthread_t) * thread_count );
	if (*threads == NULL) {
		free(*threads);
		printf("Could not allocate memory for 'threads'\n");
		return -1;
	}
	
	/* start threads */
	for (i = 0; i < thread_count; i++) {
		DBG_PRINTF("Firing up thread %d.\n", i);
		
		error = pthread_create( (*threads)+i, NULL, reader_thread, NULL );
		if (error != 0) {
			printf("Error %d: Could not create thread %d\n", error, i);
			free(*threads);
			return -1;
		}
	}
	
	return 0;
}

int wait_for_threads(pthread_t **threads, int thread_count) {
	int i,
		error;
	
	/* wait for threads */
	for (i = 0; i < thread_count; i++) {
		error = pthread_join( (*threads)[i], NULL );
		if (error != 0) {
			printf("Error %d: Thread %d could not be suspended\n", error, i);
			free(*threads);
			return -1;
		}
	}
	
	free(*threads);
	return 0;
}

void process_input_for_buffer(char *input, size_t input_length) {
	size_t concurrent = 0;
	int temp_len;
	char *temp = NULL,
		 *toSend = NULL;
	char *end = input + input_length;
	
	/* Begin extracting information from input */
	temp = strtok(input, " ");
	do {
		temp_len = strlen(temp);
		removeNewLine(temp, temp_len);
		DBG_PRINTF("Processing \"%s\"\n", temp);
		
		toSend = (char*) malloc(sizeof(char) * (temp_len + 1));
		strcpy(toSend, temp);
		shared_buffer_insert( &Item_Buffer, (item_t) toSend );
		
		concurrent += temp_len;
		temp = strtok(NULL, " ");
	} while (temp != NULL && temp < end);
}

int main(void) {
	int i,
		ret_result = 0;
	char *input = NULL;
	struct timeval time_now;
	pthread_t *threads;
	
	/* use the current micro seconds as a random seed */
	gettimeofday(&time_now, NULL);
	srand(time_now.tv_usec);

	/* Initialize shared buffer */
	ret_result = shared_buffer_init(&Item_Buffer, 0, ITEM_BUFFER_SIZE);
 	if ( ret_result ) {
		DBG_PRINTF("shared_buffer_init failed with %d\n", ret_result);
		return EXIT_FAILURE;
	}

	/*	Launching threads BEFORE capturing any input	*/
	run_threads( &threads, READER_THREAD_COUNT );

	while (TRUE) {
		input = (char*) malloc(sizeof(char) * INPUT_LEN);
		read(0, input, INPUT_LEN);
		
		DBG_PRINTF("input to be processed = %s\n", input);
		
		process_input_for_buffer(input, INPUT_LEN);
	}
	
	/* make threads quit (produce_n_NULLs()) */
	for (i = 0; i < READER_THREAD_COUNT; i++)
		process_input_for_buffer(NULL, INPUT_LEN);
	
	wait_for_threads( &threads, READER_THREAD_COUNT );
	
	shared_buffer_close(&Item_Buffer);
	
	return EXIT_SUCCESS;
}

