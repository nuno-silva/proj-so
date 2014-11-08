#ifndef __READER_PARENT_MAIN_H__
	#define __READER_PARENT_MAIN_H__
	
	/**
	 * @brief Runs reader processes, each one reading a different file, and
	 * waits for them to finish.
	 * 
	 * @param file_nums[] array of file mumbers to read
	 * @param num_children number of reader child processes
	 * 
	 * @retval -1 on failure, 0 on success
	 */
	int run_and_wait_for_children(int file_nums[], int children_count);



#endif