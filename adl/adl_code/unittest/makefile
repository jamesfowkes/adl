CC = g++
DEL = @rm -f

ifeq ($(OS),Windows_NT)
	TARGET_EXTENSION = exe
else
	TARGET_EXTENSION = out
endif

LIBS = -lcppunit

INC = -I../

CFLAGS = -Wall -Wextra

ADL_UTIL_OBJS = adl-util-numeric-range.unittest.o \
	adl-util-single-numeric.unittest.o \
	adl-util-csv-numerics.unittest.o \
	adl-util.unittest.runner.o \
	../adl-util.o

ADL_UTIL_DELIMITED_STREAM_PARSER_OBJS = ../adl-util-delimited-stream-parser.o \
	adl-util-delimited-stream-parser.unittest.o \
	adl-util.unittest.runner.o

%.o: %.cpp
	$(CC) $(INC) $(DEFINES) -c -o $@ $< $(CFLAGS)

default:
	@echo "Available Tests: adl-util adl-util-delimited-stream-parser"

.PHONY: adl-util
adl-util: $(ADL_UTIL_OBJS)
	$(CC) -o adl-util.$(TARGET_EXTENSION) $^ $(CFLAGS) $(LIBS)
	./adl-util.$(TARGET_EXTENSION)

.PHONY: adl-util-delimited-stream-parser
adl-util-delimited-stream-parser: $(ADL_UTIL_DELIMITED_STREAM_PARSER_OBJS)
	$(CC) -o adl-util-delimited-stream-parser.$(TARGET_EXTENSION) $^ $(CFLAGS) $(LIBS)
	./adl-util-delimited-stream-parser.$(TARGET_EXTENSION)

clean:
	rm *.o
	rm ../*.o
