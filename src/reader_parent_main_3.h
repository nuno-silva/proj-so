#ifndef __READER_PARENT_MAIN_3_H__
    #define __READER_PARENT_MAIN_3_H__
    
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
	 * @param file_num File number
     * @param thread_count Number of threads to run
     *
     * @retval -1 on failure, 0 on success
     */
    int run_and_wait_for_threads(int file_num, int thread_count);
    
	typedef struct {
		int file_num, first_line, last_line;
	} thread_info_t;
    
#endif