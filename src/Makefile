CC = gcc
CFLAGS = -g

all: writer reader


writer: writer_main.o writer.o

writer_main.o: writer_main.c writer.h
writer.o: writer.c writer.h



reader: reader_main.o reader.o

reader_main.o: reader_main.c reader.h
reader.o: reader.c reader.h


clean:
	rm -rf writer reader *.o
