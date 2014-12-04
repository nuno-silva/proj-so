#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <pthread.h>

#include "writer_parallel.h"
#include "shared_stuff.h"
#include "writer_constants.h"
#include "writer.h"

#define BUFFER_CHAR_COUNT 32


void *writer_thread() {
    int file_num;
    char *rand_str;
    
	while(1) { /* TODO terminate loop on signal*/

        file_num = RANDOM_RANGE(0, 4);
        rand_str = get_writer_string( RANDOM_RANGE(0, WRITER_STRING_COUNT - 1) );
        writer(file_num, rand_str, WRITER_STRING_LEN);

	}
}

int run_and_wait_for_threads(int thread_count) {
	int error;
    int i;
	pthread_t *threads;
    
	threads = (pthread_t*) malloc( sizeof(pthread_t) * thread_count );
	if (threads == NULL) {
		printf("Could not allocate memory for 'threads'\n");
		return -1;
	}
	
	/* start threads */
	for (i = 0; i < thread_count; i++) {
		error = pthread_create( threads+i, NULL, writer_thread, NULL );
		if (error != 0) {
			printf("Error %d: Could not create thread %d\n", error, i);
			free(threads);
			return -1;
		}
	}
	
	
	/* wait for threads */
	for (i = 0; i < thread_count; i++) {
		error = pthread_join(threads[i], NULL);
		if (error != 0) {
			printf("Error %d: Thread %d could not be suspended\n", error, i);
			free(threads);
			return -1;
		}
	}
	free(threads);
    return 0;
}


int main() {
    int ret;
    struct timeval tvstart;     /* data de inicio */
    struct timeval tvend;       /* data de fim */
    struct timeval tvduration;  /* diferenca entre as duas datas */
    unsigned int duration_us;   /* diferenca entre as datas em microssegundos */

    time_t curtime;             /* tempo em formato time_t para conversao de formatos */
    char buffer[BUFFER_CHAR_COUNT]; /* para escrever a data em formato legivel */

    gettimeofday(&tvstart, NULL);   /* ler a data actual */
    /* converter e imprimir a data */
    curtime = tvstart.tv_sec;
    strftime(buffer, BUFFER_CHAR_COUNT, "%m-%d-%Y  %T.", localtime(&curtime));
    printf("inicio: %s%ld\n", buffer, (long int)tvstart.tv_usec);

    ret = run_and_wait_for_threads(THREAD_COUNT);
    if (ret < 0) /* error */
        return ret;

    gettimeofday(&tvend, NULL); /* ler a data actual */

    /* converter e imprimir a data */
    curtime = tvend.tv_sec;
    strftime(buffer, BUFFER_CHAR_COUNT, "%m-%d-%Y  %T.", localtime(&curtime));
    printf("fim: %s%ld\n", buffer, (long int)tvend.tv_usec);

    /* calcular e imprimir a diferenca de datas */
    tvduration.tv_sec = tvend.tv_sec - tvstart.tv_sec;
    tvduration.tv_usec = tvend.tv_usec - tvstart.tv_usec;
    duration_us = tvduration.tv_sec * 1000000 + tvduration.tv_usec;
    printf("duracao: %.4f segundos\n", ((float)duration_us)/1000000.0f);


    return ret;
}
