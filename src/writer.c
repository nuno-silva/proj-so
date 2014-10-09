#include <stdio.h>
#include <fcntl.h>


#include "writer.h"
#include "shared_constants.h"


const int writer_f_flags = O_WRONLY | O_CREAT | O_TRUNC;
const int writer_f_mode  = S_IRUSR  | S_IWUSR | S_IROTH;

void writer(int file_num, char *txt, int txt_len){
	char file_name[32];
	int fd, i, txt_size;

	sprintf(file_name, FILENAME, file_num);	// place file_num in FILENAME
	fd = open(file_name, writer_f_flags, writer_f_mode);
	
	txt_len *= sizeof(char);
	for (i = 0; i < WRITE_COUNT; i++){
		write(fd, txt, txt_len);
	}
	
	close(fd);
}

void run_writer_cycle(){
	int i, file_num;
    char *rand_str;
    
    for ( i = 0; i < CYCLE_COUNT; i++ ){
    	file_num = random_range(0, 4);
    	rand_str = get_writer_string( random_range(0, WRITER_STRING_COUNT - 1) );
		writer(file_num, rand_str, WRITER_STRING_LEN);
    }
}


char *get_writer_string(int index){
	return (char*) writer_strings[index];
}
