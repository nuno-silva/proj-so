#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <errno.h>
#include <sys/types.h> // for lseek()
#include <unistd.h>    // for lseek()


#include "reader.h"
#include "shared_stuff.h"
#include "reader_constants.h"

static const int reader_f_flags = O_RDONLY;

int reader(int file_num) {
	return reader_ranged(file_num, 0, LINES_PER_FILE - 1);
}

int reader_ranged(int file_num, int first_line, int last_line) {
	char file_name[64];
	int fd, file_value;
	sprintf(file_name, FILENAME, file_num); // place file_num in FILENAME
	
	fd = open(file_name, reader_f_flags);
	if (fd == -1) { // error opening the file (does not exist?)
		printf("open(%s) failed. errno=%d\n", file_name, errno);
		return FILE_IS_INVALID;
	}  
	
	flock(fd, LOCK_SH);
	
	if ( file_contents_are_valid(fd, WRITER_STRING_LEN,
								 first_line, last_line) == TRUE ) {
		file_value = FILE_IS_VALID;
	} else {
	    file_value =  FILE_IS_INVALID;
	}
	
	flock(fd, LOCK_UN);
	
	close(fd);
	return file_value;
}


int file_contents_are_valid(int fd, int line_length, int first_line, int last_line){
	int line_count = last_line - first_line + 1;
	
	// number of bytes to read at a time from the file
	int line_size = line_length * sizeof(char);
	DBG_PRINTF("fd=%d, line_size = %d\n", fd, line_size);
	
	char *first_line_buf = (char*) malloc(line_size);
	
	// try to read and validate the first line of the file
	if ( read(fd, first_line_buf, line_size) != line_size ) {
		// the first line doesn't even have the correct number of characters
		free(first_line_buf);
		DBG_PRINT("invalid file detected here (file is too small)\n");
		return FALSE; // file is invalid
	}

	DBG_PRINTF("fd=%d, first_line_buf='%s'\n",fd,first_line_buf);
	if ( !known_writer_string(first_line_buf, line_length) ){
		free(first_line_buf);
		DBG_PRINT("invalid file detected here (unknown line)\n");
		return FALSE; // file is invalid
	}
	
	// the first line is valid, so we can compare it with all other lines
	char *line_buffer = (char*) malloc(line_size);
	
	lseek( fd, first_line * line_size, SEEK_SET );
	
	// compare all lines with the first line of the file
	int i;
	for ( i = 0 ; i < line_count && read(fd, line_buffer, line_size) == line_size; i++ )
	{
		if ( strncmp(line_buffer, first_line_buf, line_length) != 0 ) {
			DBG_PRINTF( "invalid file detected here (unconsistent line); fd=%d, first_line=%d, i=%d\n",
			            fd, first_line, i );
			free(first_line_buf);
			free(line_buffer);
			return FALSE; // file is invalid
		}
	}
	
	// did we read all expected lines?
	if( i < line_count  ) {
		DBG_PRINT("invalid file detected here (shorter than expected)\n");
		return FALSE;
	}
	
	// is the file longer than expected?
	if ( (first_line + i) >= LINES_PER_FILE ) { // we are in the last line of the file
		if( read(fd, line_buffer, 1) > 0 ) { // file is longer than expected
			DBG_PRINT("invalid file detected here (longer than expected)\n");
			return FALSE;
		}
	}
	
	free(first_line_buf);
	free(line_buffer);
	
	return TRUE; // file is valid
}

int known_writer_string(char *str, int str_len){
	int i;
	
	for ( i = 0; i < WRITER_STRING_COUNT; i++ ){
		if ( strncmp(str, writer_strings[i], str_len) == 0 ){
			return TRUE;
		}
	}
	
	return FALSE;
}
