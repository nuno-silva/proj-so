#include "shared_stuff.h"

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

void removeNewLine(char *input, int size){
	int i;
	
	for (i = 0; i < size; i++){
		if (input[i] == '\n'){
			input[i] = '\0';
			break;
		}
	}
}
