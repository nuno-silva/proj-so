#ifndef __WRITER_H__
	#define __WRITER_H__
	
	
	#define CHILDREN_COUNT 10	/*	Constant useful only for writer function	*/
	
	/**
	 * @brief Opens the file specified by file_num and writes to it.
	 * 
	 * @param file_num the number of the file
	 * @param txt pointer to the string to write
	 * @param txt_len number of characters in txt to write
	 */
	void writer(int file_num, char *txt, int txt_len);
	
	
	/**
	 * @brief Get a writer string by its index
	 * 
	 * @param index string index 
	 * 
	 * @retval string placed in the index position of the global value writer_strings
	 */
	char *get_writer_string(int index);
	

#endif //__WRITER_H__
