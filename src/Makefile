LD = gcc
CC = gcc
CFLAGS = -Wall -ansi
LDFLAGS =
EXECS = writer reader
EXECS+= writer_parent reader_parent
ZIPNAME = ex5-g46

all: $(EXECS)

debug: CFLAGS += -DDEBUG -g -Wextra -Wunreachable-code -Wbad-function-cast
debug: all


shared_stuff.o: shared_stuff.c shared_stuff.h


writer_parent: writer_parent_main.o
	$(LD) $(LDFLAGS) $^ -o $@
writer_parent_main.o: writer_parent_main.c writer_parent_main.h writer_constants.h shared_stuff.h


writer: writer_main.o writer.o shared_stuff.o

writer_main.o: writer_main.c writer.h shared_stuff.h writer_constants.h
writer.o: writer.c writer.h shared_stuff.h



reader: reader_main.o reader.o shared_stuff.o

reader_main.o: reader_main.c reader.h shared_stuff.h
reader.o: reader.c reader.h shared_stuff.h


reader_parent: LDFLAGS+=-pthread
reader_parent: reader_parent_main.o reader.o shared_stuff.o
	$(LD) $(LDFLAGS) $^ -o $@

reader_parent_main.o: reader_parent_main.c reader_parent_main.h
reader_parent_main.o: reader.h reader_constants.h shared_stuff.h



clean:
	rm -rf $(EXECS) *.o *.txt $(ZIPNAME).zip

zip: $(EXECS)
	rm -f $(ZIPNAME).zip
	zip $(ZIPNAME).zip *.c *.h Makefile $(EXECS)
