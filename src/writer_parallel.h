#ifndef __WRITER_PARALLEL_H__
	#define __WRITER_PARALLEL_H__
	
	/**
	 * @brief Runs writer threads and waits for them to finish.
	 * 
	 * @param thread_count number of child processes
	 * 
	 * @retval -1 on failure, 0 on success
	 */
	int run_and_wait_for_threads( int thread_count );

	void *writer_thread();
	
	void sigusr1_handler(int number);
	void sigusr2_handler(int sig_num);
	
#endif /* __WRITER_PARALLEL_H__ */
