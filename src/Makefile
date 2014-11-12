LD = gcc
CC = gcc
CFLAGS = -Wall 
EXECS = writer_parent writer reader
EXECS+= reader_parent_1
ZIPNAME = ex4-g46

all: $(EXECS)

debug: CFLAGS += -DDEBUG -g -Wextra -Wunreachable-code -Wbad-function-cast
debug: all


writer_parent: writer_parent_main.o
	$(LD) $^ -o $@
writer_parent_main.o: writer_parent_main.c writer_parent_main.h writer_constants.h shared_stuff.h

writer: writer_main.o writer.o shared_stuff.o

writer_main.o: writer_main.c writer.h shared_stuff.h writer_constants.h
writer.o: writer.c writer.h shared_stuff.h



reader_parent_1: reader_parent_main_1.o
	$(LD) $^ -o $@
reader_parent_main_1.o: reader_parent_main_1.c reader_parent_main_1.h reader_constants.h shared_stuff.h

reader: reader_main.o reader.o shared_stuff.o

reader_main.o: reader_main.c reader.h shared_stuff.h
reader.o: reader.c reader.h shared_stuff.h



shared_stuff.o: shared_stuff.c shared_stuff.h


clean:
	rm -rf $(EXECS) *.o *.txt $(ZIPNAME).zip

zip: $(EXECS)
	rm -f $(ZIPNAME).zip
	zip $(ZIPNAME).zip *.c *.h Makefile $(EXECS)

