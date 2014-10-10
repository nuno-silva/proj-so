#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "shared_stuff.h"
#include "reader.h"

const static int reader_f_flags = O_RDONLY;


int reader(int file_num){
    char file_name[64];
    int fd, file_value;
    sprintf(file_name, FILENAME, file_num); // place file_num in FILENAME
    fd = open(file_name, reader_f_flags);
    
    if (fd == -1){ // error opening the file (does not exist?)
        return FILE_IS_INVALID;
    }
    
    // TEST PRINTFS BELOW
    if ( file_contents_are_valid(fd, WRITER_STRING_LEN, LINES_PER_FILE) == TRUE ){
        printf("VALID!\n");
        file_value = FILE_IS_VALID;
    }else{
        printf("INVALID!\n");
        file_value =  FILE_IS_INVALID;
    }
    
    close(fd);
    return file_value;
}


int file_contents_are_valid(int fd, int line_length, int line_count)
{
    // number of bytes to read at a time from the file
    int line_size = line_length * sizeof(char);
    
    char *first_line = (char*) malloc(line_size);
    
    // try to read and validate the first line of the file
    if ( read(fd, first_line, line_size) != line_size ) {
        // the first line doesn't even have the correct number of characters
        free(first_line);
        return FALSE; // file is invalid
    }
    if ( !known_writer_string(first_line, line_size) ){
        free(first_line);
        return FALSE; // file is invalid
    }
    
    // the first line is valid, so we can compare it with all other lines
    char *line_buffer = (char*) malloc(line_size);
    
    // compare all lines with the first line
    int i;
    for ( i = 1 ; read(fd, line_buffer, line_size) == line_size; i++ )
    {
        if ( strncmp(line_buffer, first_line, line_size) != 0 || i >= line_count){
            free(first_line);
            free(line_buffer);
            return FALSE; // file is invalid
        }
    }
    
    free(first_line);
    free(line_buffer);
    
    if (i != line_count)
        return FALSE;
    
    return TRUE; // file is valid
}

int known_writer_string(char *str, int str_size){
    int i;
    
    for ( i = 0; i < WRITER_STRING_COUNT; i++ ){
        if ( strncmp(str, writer_strings[i], str_size) == 0 ){
            return TRUE;
        }
    }
    
    return FALSE;
}