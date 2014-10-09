#ifndef __WRITER_H__
#define __WRITER_H__

#define random_range(min, max) (( rand() % ( max + 1 - min ) ) + min )

#define CYCLE_COUNT 5120
#define WRITE_COUNT 1024



/**
 * @brief Opens the file specified by file_num and writes to it.
 * @param file_nume the number of the file
 * @param txt pointer to the string to write
 * @param txt_size number of characters in txt to write
 */
void writer(int file_num, char *txt, int txt_len);

/**
 * @brief TODO
 */
void run_writer_cycle();

/**
 * @brief Get a writer string by its index
 */
char * get_writer_string( int index );

#endif //__WRITER_H__
