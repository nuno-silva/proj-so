#ifndef __SHARED_BUFFER_H__
	#define __SHARED_BUFFER_H__
	
	#include <semaphore.h>
	#include <pthread.h>
	
	typedef char* item_t;

	// NOTE: THE CODE BELOW ASSUMES THAT AN ARRAY OF POINTES IS USED
	
	typedef struct {
			item_t *buffer;
			size_t size;
			size_t index;
			sem_t empty; // counts the number of empty buffer slots
			sem_t occupied; // counts the number of occupied buffer slots
			pthread_mutex_t mutex;
		} shared_buffer_t;


	void shared_buffer_insert( shared_buffer_t *s, item_t i );

	item_t shared_buffer_remove( shared_buffer_t *s );

	int shared_buffer_init( shared_buffer_t *s, int pshared_val, size_t size );

	int shared_buffer_close( shared_buffer_t *s );

#endif /* __SHARED_BUFFER_H__ */
