#ifndef __WRITER_PARENT_MAIN_H__
	#define __WRITER_PARENT_MAIN_H__
	/**
	 * @brief Runs writer processes and waits for them to finish. The cycles
	 * will be distributed by each child.
	 * 
	 * @param cycle_count total number of cycles to run
	 * @param num_children number of child processes
	 * 
	 * @retval -1 on failure, 0 on success
	 */
	int run_and_wait_for_children(int cycle_count, int children_count);

#endif
