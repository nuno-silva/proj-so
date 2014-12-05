#ifndef __READER_PARALLEL_H__
	#define __READER_PARALLEL_H__

	/**
	* @brief Creates a thread prepared with reader credentials. Said thread then brings
	* out the appropriate reader() return value
	*
	* @param arg Abstract argument, in this case corresponding to a file number
	*/
	void *reader_thread(void *arg);

	/**
	* @brief Runs reader threads, each one reading a different file brought to
	* it via a shared buffer.
	* 
	* @param threads Thread array to pass that contain information about the 
	* files.
	* @param thread_count Number of threads to run
	* 
	* @retval -1 on failure, 0 on success
	*/
	int run_threads(pthread_t **threads, int thread_count);
	
	/**
	* @brief Waits for running threads to finish.
	* 
	* @param threads Thread array to pass that contain information about the 
	* files.
	* @param thread_count Number of threads that we should wait for (must be the
	* as the number of threads started)
	*
	* @retval -1 on failure, 0 on success
	*/
	int wait_for_threads(pthread_t **threads, int thread_count);
	
	/**
	 * @brief Processes input and sends every filename candidate to buffer.
	 * 
	 * @param input Text to process.
	 * @param input_length Maximum length to consider when reading the input text.
	 * 
	 */
	void process_input_for_buffer(char *input, size_t input_length);

	typedef struct {
		int first_line, last_line;
		char *filename;
	} thread_info_t;

#endif /* __READER_PARALLEL_H__ */
