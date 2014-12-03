#ifndef __SHARED_BUFFER_H__
	#define __SHARED_BUFFER_H__
	
	typedef char* item_t;
	
	typedef struct {
			Item *buffer;
			size_t size;
			size_t index;
			//TODO semaphores, lock
		} shared_buffer_t;
	
	
	void shared_buffer_insert( shared_buffer_t *s, item_t i );
	
	item_t shared_buffer_remove( shared_buffer_t *s );
	
	int shared_buffer_init( shared_buffer_t *s, size_t size );
	
	void shared_buffer_free( shared_buffer_t *s );

#endif /* __SHARED_BUFFER_H__ */