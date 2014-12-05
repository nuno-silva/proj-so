UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
	LD = gcc-4.9
	CC = gcc-4.9
else
	LD = gcc
	CC = gcc
endif
CFLAGS = -Wall -ansi
CFLAGS+= -D_POSIX_C_SOURCE
LDFLAGS =
EXECS  = reader_parallel
EXECS += writer_parallel
EXECS += monitor
ZIPNAME = ex5-g46

all: $(EXECS)

debug: CFLAGS += -DDEBUG -g -Wextra -Wunreachable-code -Wbad-function-cast
debug: all


shared_stuff.o: shared_stuff.c shared_stuff.h


writer_parallel: LDFLAGS+=-pthread
writer_parallel: writer_parallel.o writer.o shared_stuff.o
	$(LD) $(LDFLAGS) $^ -o $@

writer_parallel.o: writer_parallel.c writer_parallel.h
writer_parallel.o: writer.h shared_stuff.h


writer.o: writer.c writer.h shared_stuff.h


reader.o: reader.c reader.h shared_stuff.h


reader_parallel: LDFLAGS+=-pthread
reader_parallel: reader_parallel.o reader.o shared_stuff.o
reader_parallel: shared_buffer.o
	$(LD) $(LDFLAGS) $^ -o $@

reader_parallel.o: reader_parallel.c reader_parallel.h
reader_parallel.o: reader.h shared_stuff.h shared_buffer.h

monitor: monitor.o shared_stuff.o
	$(LD) $(LDFLAGS) $^ -o $@
monitor.o: monitor.c monitor.h shared_stuff.h


shared_buffer.o: shared_buffer.c shared_buffer.h

clean:
	rm -rf $(EXECS) *.o *.txt $(ZIPNAME).zip

zip: $(EXECS)
	rm -f $(ZIPNAME).zip
	zip $(ZIPNAME).zip *.c *.h Makefile $(EXECS)
