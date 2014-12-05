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


#define ITEM_BUFFER_SIZE	30
#define INPUT_BUFFER_SIZE	( sizeof(char) * 255 )

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

int main(void) {
	int i;
	char *input_buffer;
	struct timeval time_now;
	pthread_t *threads;
	
	/* use the current micro seconds as a random seed */
	gettimeofday(&time_now, NULL);
	srand(time_now.tv_usec);

	/* Initialize shared buffer */
 	if ( shared_buffer_init(&Item_Buffer, 0, ITEM_BUFFER_SIZE) != 0 ) {
		printf("Could not allocate shared buffer.\n");
		exit(-1);
	}

	/*	Launching threads BEFORE capturing any input	*/
	if( run_threads( &threads, READER_THREAD_COUNT ) != 0 ) {
		printf("Could run threads.\n");
		exit(-1);
	}

	/* allocate input_buffer */
	input_buffer = (char*) malloc( INPUT_BUFFER_SIZE );
	if( input_buffer == NULL) {
		printf("Could not allocate input buffer.\n");
		exit(-1);
	}

	while (TRUE) {
		read_command_from_fd(STDIN_FILENO, input_buffer, INPUT_BUFFER_SIZE);
		
		DBG_PRINTF("input to be processed = %s\n", input_buffer);
		
		process_file(input_buffer);
	}
	
	free(input_buffer);
	
	
	/* make threads quit (produce_n_NULLs()) */
	for ( i = 0; i < READER_THREAD_COUNT; i++ ) {
		shared_buffer_insert( &Item_Buffer, (item_t) NULL );
	}
	
	wait_for_threads( &threads, READER_THREAD_COUNT );
	
	shared_buffer_close(&Item_Buffer);
	
	return EXIT_SUCCESS;
}


void process_file( char* filename ) {
	char* item = (char*) malloc( (strlen(filename) + 1) * sizeof(char) );
	if(item == NULL) {
		printf("Could not allocate memory.\n");
		return;
	}
	strcpy(item, filename);
	shared_buffer_insert( &Item_Buffer, (item_t) item );
}