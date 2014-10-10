#ifndef __READER_H__
    #define __READER_H__
    
    
    #define FILE_IS_VALID    0
    #define FILE_IS_INVALID -1
    
    int reader(int file_num);
    int file_contents_are_valid(int fd, int line_length, int line_count);
    int known_writer_string(char *str, int str_size);
    
    
#endif
