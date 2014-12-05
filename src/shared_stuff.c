#include "shared_stuff.h"
#include <unistd.h>

char writer_strings [ WRITER_STRING_COUNT ][ WRITER_STRING_LEN + 1 ] = {
	"aaaaaaaaa\n",
	"bbbbbbbbb\n",
	"ccccccccc\n",
	"ddddddddd\n",
	"eeeeeeeee\n",
	"fffffffff\n",
	"ggggggggg\n",
	"hhhhhhhhh\n",
	"iiiiiiiii\n",
	"jjjjjjjjj\n"
};


int read_command_from_fd(int fd, char * buff, size_t buff_size) {
	size_t count = 0;
	int read_res;
	while( count < buff_size ) {
		/* read byte-by-byte */
		read_res = read(fd, buff+count, 1);

		if (read_res == -1) {
			DBG_PRINT("read() failed.\n");
			return -1;
		} else if( read_res == 0) { /* EOF */
			return -1;
		}

		if (buff[count] == '\n' || buff[count] == ' ') {
			buff[count] = '\0';
			return 0;
		}
		count ++;
	}
	return -1; /* buff was full */
}
