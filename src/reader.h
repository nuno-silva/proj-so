#ifndef __READER_H__
    #define __READER_H__
    
    
    #define FILE_IS_VALID    0
    #define FILE_IS_INVALID -1
    /*
     * @brief Check the specified file for consistency.
     * @param file_num The file number
     * @retval FILE_IS_VALID or FILE_IS_INVALID
     */
    int reader(int file_num);
    
    /**
     * @brief Checks wether the file is valid.
     * A file is considered valid if it repeats one of the known writer strings
     * line_count times.
     * 
     * @param fd The file descriptor of the file to check
     * @param line_length Expected length of each line, in characters
     * @param line_count Expected number of lines in the file
     * 
     * @retval TRUE if the file is valid; FALSE otherwise
     */
    int file_contents_are_valid(int fd, int line_length, int line_count);
    
    /**
     * @brief looks for str in writer_strings
     * @param str The string to look for
     * @param str_len Number of characters in str
     * @retval TRUE if str is in writer_strings; FALSE otherwise
     */
    int known_writer_string(char *str, int str_len);
    
    
#endif
