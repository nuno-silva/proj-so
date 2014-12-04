#ifndef __WRITER_H__
	#define __WRITER_H__

	/**
	 * @brief Opens the file specified by file_num and writes to it.
	 *
	 * @param file_num the number of the file
	 * @param txt pointer to the string to write
	 * @param txt_len number of characters in txt to write
	 * @param use_locks  use exclusive locks while writing to the file
	 */
	void writer(int file_num, char *txt, int txt_len, int use_locks, 
	int enable_writing_errors);


	/**
	 * @brief Get a writer string by its index
	 *
	 * @param index string index
	 *
	 * @retval string placed in the index position of the global value writer_strings
	 */
	char *get_writer_string(int index);


#endif
