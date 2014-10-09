#ifndef __READER_H__
#define __READER_H__

int reader(int file_num);
int file_contents_are_valid(int fd, int line_length);
int valid_line(char *first_line, int num_bytes);
int known_writer_string(char *first_line, int num_bytes, int num_strings);

#endif