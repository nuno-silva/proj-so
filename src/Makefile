CC = gcc
CFLAGS = -Wall 
EXECS = writer_parent writer reader_parent reader
ZIPNAME = ex3-g46

all: $(EXECS)

debug: CFLAGS += -DDEBUG -g -Wextra -Wunreachable-code
debug: all


writer_parent: writer_parent_main.o
writer_parent_main.o: writer_parent_main.c writer.h shared_stuff.h

writer: writer_main.o writer.o shared_stuff.o

writer_main.o: writer_main.c writer.h shared_stuff.h
writer.o: writer.c writer.h shared_stuff.h



reader_parent: reader_parent_main.o
reader_parent_main.o: reader_parent_main.c reader.h shared_stuff.h

reader: reader_main.o reader.o shared_stuff.o

reader_main.o: reader_main.c reader.h shared_stuff.h
reader.o: reader.c reader.h shared_stuff.h



shared_stuff.o: shared_stuff.c shared_stuff.h


clean:
	rm -rf $(EXECS) *.o *.txt $(ZIPNAME).zip

zip: $(EXECS)
	rm -f $(ZIPNAME).zip
	zip $(ZIPNAME).zip *.c *.h Makefile $(EXECS)

