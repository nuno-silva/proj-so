#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>


#include "writer.h"
#include "shared_stuff.h"


const static int writer_f_flags = O_WRONLY | O_CREAT | O_TRUNC;
const static int writer_f_mode  = S_IRUSR  | S_IWUSR | S_IROTH;

void writer(int file_num, char *txt, int txt_len){
	char file_name[64];
	int fd, i, txt_size;

	sprintf(file_name, FILENAME, file_num);	// place file_num in FILENAME
	fd = open(file_name, writer_f_flags, writer_f_mode);
	
	flock(fd, LOCK_EX);
	
	txt_size = txt_len * sizeof(char);
	for (i = 0; i < LINES_PER_FILE; i++){
		write(fd, txt, txt_size);
	}
	
	flock(fd, LOCK_UN);
	
	close(fd);
}


char *get_writer_string(int index){
	return (char*) writer_strings[index];
}
