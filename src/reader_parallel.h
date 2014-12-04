#ifndef __READER_PARALLEL_H__
	#define __READER_PARALLEL_H__
	
	#define SEM_PSHARED_VAL 0 // share between threads
	#define SEM_INIT_VAL 0 // initial semaphore value 

	/**
	* @brief Creates a thread prepared with reader credentials. Said thread then brings
	* out the appropriate reader() return value
	*
	* @param arg Abstract argument, in this case corresponding to a file number
	*/
	void *reader_thread(void *arg);

	/**
	* @brief Runs reader threads, each one reading a different file, and waits for
	* them to finish.
	*
	* @param thread_count Number of threads to run
	*
	* @retval -1 on failure, 0 on success
	*/
	int run_and_wait_for_threads(int thread_count);

	typedef struct {
		int first_line, last_line;
		char *filename;
	} thread_info_t;

#endif /* __READER_PARALLEL_H__ */
