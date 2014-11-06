#ifndef __SHARED_STUFF_H__
	#define __SHARED_STUFF_H__
	
	#include <stdio.h>
	
	// enables debug prints if defined; we define it in the makefile
	//#define DEBUG
	
	#define CYCLE_COUNT 5120
	#define WRITER_MAIN_PATH  "./writer"
	
	#define WRITER_STRING_LEN   10
	#define WRITER_STRING_COUNT 10
	#define LINES_PER_FILE      1024
	
	#define FILENAME "SO2014-%d.txt"
	
	#define RANDOM_RANGE(MIN, MAX) (( rand() % ( MAX + 1 - MIN ) ) + MIN )
	
	// used to print debug messages
	#ifdef DEBUG
	    #define DBG_PRINTF(format, ...) printf("%s:%d: "format, __FILE__, __LINE__, __VA_ARGS__)
	#else
	    #define DBG_PRINTF(format, ...) 
	#endif
	
	extern char writer_strings[ WRITER_STRING_COUNT ][ WRITER_STRING_LEN + 1 ];
	
	#define TRUE    1
	#define FALSE   0
#endif
