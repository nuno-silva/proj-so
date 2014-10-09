#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "shared_constants.h"
#include "reader.h"

const int writer_f_flags = O_RDONLY;


int reader(int file_num){
    char file_name[32];
    int fd;
    sprintf(file_name, FILENAME, file_num); // build file name
    fd = open(file_name, writer_f_flags);
    
    // TEST PRINTFS BELOW
    if (file_contents_are_valid(fd, 10)) {
        printf("VALID!\n");
    }
    else
        printf("INVALID!\n");
    
    close(fd);
}


int file_contents_are_valid(int fd, int line_length){
    char *char_sequence;
    // number of bytes to read at a time from the file
    int num_bytes_to_read = line_length*sizeof(char);
    int i;
    // allocate memory for the buffer ( used in read() )
    char *first_line = (char*)malloc(num_bytes_to_read);
    
    if (read(fd, first_line, num_bytes_to_read) != num_bytes_to_read) {
        // the first line doesn't even have the correct number of characters
        free(first_line);
        return 0;
    }
    
    if (!valid_line(first_line, line_length)){
        free(first_line);
        return 0; // character sequence is not identical, so it can't be valid
    }
        
    char_sequence = (char*) malloc(sizeof(char) * line_length);
    // strncpy(char_sequence, first_line, num_bytes_to_read);
    
    
    for (i=1; read(fd, char_sequence, num_bytes_to_read); i++){
        if (strncmp(char_sequence, first_line, num_bytes_to_read)){
            free(first_line);
            free(char_sequence);
            return 0; // file contents are invalid
        }
            
    }
    
    free(first_line);
    free(char_sequence);
    
    if (i != 1024)
        return 0;   // nummber of lines is incorrect
    
    return 1; // file contents are valid
}

int valid_line(char *first_line, int num_bytes){
    if (!known_writer_string(first_line, num_bytes, WRITER_STRING_COUNT))
        // the first line is not a known string
        return 0;
}

int known_writer_string(char *first_line, int num_bytes, int num_strings){
    int i;
    
    for (i = 0; i < num_strings; i++){
        if (strncmp(first_line, writer_strings[i], num_bytes) == 0){
            return 1;
        }
    }
    
    return 0;
}
