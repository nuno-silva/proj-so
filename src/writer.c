#include <stdio.h>
#include <stdlib.h>

#include "writer.h"


#define FILENAME "S02014-%d.txt"
#define CYCLE_COUNT 5120
#define WRITE_COUNT 1024

const int writer_f_flags = O_WRONLY | O_CREAT | O_TRUNC;

void writer(int file_num, char *txt, size_t txt_size )
{
	char file_name[32];
	int fd, i;

	sprintf(file_name, FILENAME, file_num);
	fd = open(file_name, writer_f_flags);
	
	txt_size *= sizeof(char); // calculate size in bytes of txt to write
	for (i=0; i < WRITE_COUNT; i++)
	{
		write( fd, txt, txt_size );
	}
}

