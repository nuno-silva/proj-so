#ifndef __SHARED_STUFF_H__
    #define __SHARED_STUFF_H__
    
    
    #define WRITER_STRING_LEN   10
    #define WRITER_STRING_COUNT 10
    #define LINES_PER_FILE      1024
    
    #define FILENAME "SO2014-%d.txt"
    
    #define RANDOM_RANGE(MIN, MAX) (( rand() % ( MAX + 1 - MIN ) ) + MIN )
    
    extern char writer_strings [ WRITER_STRING_COUNT ][ WRITER_STRING_LEN + 1 ];
    
    #define TRUE    1
    #define FALSE   0
#endif
