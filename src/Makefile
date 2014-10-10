CC = gcc
CFLAGS = -g

all: writer reader


writer: writer_main.o writer.o shared_stuff.o

writer_main.o: writer_main.c writer.h
writer.o: writer.c writer.h shared_stuff.h



reader: reader_main.o reader.o shared_stuff.o

reader_main.o: reader_main.c reader.h
reader.o: reader.c reader.h shared_stuff.h

shared_stuff.o: shared_stuff.c shared_stuff.h

clean:
	rm -rf writer reader *.o *.txt
