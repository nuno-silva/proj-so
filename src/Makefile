CC = gcc
CFLAGS = -g

all: writer reader


writer: writer_main.o writer.o shared_constants.o

writer_main.o: writer_main.c writer.h
writer.o: writer.c writer.h shared_constants.h



reader: reader_main.o reader.o shared_constants.o

reader_main.o: reader_main.c reader.h
reader.o: reader.c reader.h shared_constants.h

shared_constants.o: shared_constants.c shared_constants.h

clean:
	rm -rf writer reader *.o *.txt
