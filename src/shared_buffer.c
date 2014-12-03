#include "shared_buffer.h"

#include <stdlib.h>

void shared_buffer_insert( shared_buffer_t *s, item_t i ) {
	
	/* lock if there are no empty slots */
	if (sem_wait(&(s->empty)) != 0) {
		printf("Error waiting on semaphore\n");
		exit(-1);
	}
	
	if (pthread_mutex_lock(&(s->mutex)) !=0 ) {
		printf("Error locking the mutex\n");
		exit(-1);
	}
	
	s->buffer[s->index++] = i; /* insert the item */
	
	if (pthread_mutex_unlock(&(s->mutex)) !=0) {
		printf("Error unlocking the mutex\n");
		exit(-1);
	}
	
	if (sem_post(&(s->occupied)) != 0) {
		printf("Error posting on semaphore\n");
		exit(-1);
	}
	
}

item_t shared_buffer_consume( shared_buffer_t *s ) {
	
	item_t item = NULL;
	
	/* lock if there are no available items */
	if (sem_wait(&(s->occupied)) != 0) {
		printf("Error waiting on semaphore\n");
		exit(-1);
	}
	
	if (pthread_mutex_lock(&(s->mutex)) !=0 ) {
		printf("Error locking the mutex\n");
		exit(-1);
	}
	
	item = buffer[s->index--];
	
	
	if (pthread_mutex_unlock(&(s->mutex)) !=0 ) {
		printf("Error unlocking the mutex\n");
		exit(-1);
	}
	
	/* there is another free slot now */
	if (sem_post(&(s->empty)) != 0) {
		printf("Error posting on semaphore\n");
		exit(-1);
	}
	
	return item;
	
}

int shared_buffer_init( shared_buffer_t *s, int pshared_val, size_t size ) {
	
	/* initially all slots are empty */
	if (sem_init(&(s->empty), psharedval, size) == -1) {
		/* error occured */
		// TODO: treat error
		printf("Error initliazing the semaphore\n");
		exit(-1);
	}
	
	/* intially there are no occupied slots */
	if (sem_init(&(s->occupied), psharedval, 0) == -1) {
		/* error occured */
		// TODO: treat error
		printf("Error initliazing the semaphore\n");
		exit(-1);
	}
	
	pthread_mutex_init(&(s->mutex), NULL);
	
	s->index = -1; /* initially array has no elements */
	
	s->size = size;

	return 0;
}

int shared_buffer_close(shared_buffer_t *s ) {
	
	if (sem_close(&(s->occupied)) == -1) {
		printf("Error closing *occupied* semaphore\n");
		exit(-1);
	}
	
	if (sem_close(&(s->empty)) == -1) {
		printf("Error closing *empty* semaphore\n");
		exit(-1);
	}
	
	if (pthread_mutex_destroy(&(s->mutex)) != 0) {
		printf("Error destroying *mutex*\n");
		exit(-1);
	} 
	
	return 0;
}
	

