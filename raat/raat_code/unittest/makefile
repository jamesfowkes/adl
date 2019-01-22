CC = g++
DEL = @rm -f

ifeq ($(OS),Windows_NT)
	TARGET_EXTENSION = exe
else
	TARGET_EXTENSION = out
endif

LIBS = -lcppunit

INC = -I../ -I../utility/ -I../messages/ -I../../unittest -I../../devices -I../../parameters

CFLAGS = -Wall -Wextra

RAAT_UTIL_OBJS = raat-util-numeric-range.unittest.o \
	raat-util-single-numeric.unittest.o \
	raat-util-csv-numerics.unittest.o \
	raat-util-nibbleandbyte.unittest.o \
	raat-util.unittest.runner.o \
	../utility/raat-util.o

RAAT_UTIL_DELIMITED_STREAM_PARSER_OBJS = ../utility/raat-util-delimited-stream-parser.o \
	raat-util-delimited-stream-parser.unittest.o \
	raat-util.unittest.runner.o

RAAT_UTIL_LIMITED_RANGE_INT_OBJS = ../utility/raat-util-limited-range-int.o \
	raat-util-limited-range-int.clipped-behaviour.unittest.o \
	raat-util-limited-range-int.unclipped-behaviour.unittest.o \
	raat-util.unittest.runner.o

ALL_TARGETS = \
	raat-util.$(TARGET_EXTENSION) \
	raat-util-delimited-stream-parser.$(TARGET_EXTENSION) \
	raat-util-limited-range-int.$(TARGET_EXTENSION) \
	raat-util-grid-indexing.$(TARGET_EXTENSION)

%.o: %.cpp
	$(CC) $(INC) $(DEFINES) -c -o $@ $< $(CFLAGS)

default:
	@echo "Available Tests: raat-util raat-util-delimited-stream-parser raat-util-limited-range-int"

raat-util.$(TARGET_EXTENSION): $(RAAT_UTIL_OBJS)
	$(CC) -o raat-util.$(TARGET_EXTENSION) $^ $(CFLAGS) $(LIBS)
	./raat-util.$(TARGET_EXTENSION)

raat-util-delimited-stream-parser.$(TARGET_EXTENSION): $(RAAT_UTIL_DELIMITED_STREAM_PARSER_OBJS)
	$(CC) -o raat-util-delimited-stream-parser.$(TARGET_EXTENSION) $^ $(CFLAGS) $(LIBS)
	./raat-util-delimited-stream-parser.$(TARGET_EXTENSION)

raat-util-limited-range-int.$(TARGET_EXTENSION): $(RAAT_UTIL_LIMITED_RANGE_INT_OBJS)
	$(CC) -o raat-util-limited-range-int.$(TARGET_EXTENSION) $^ $(CFLAGS) $(LIBS)
	./raat-util-limited-range-int.$(TARGET_EXTENSION)

raat-util-grid-indexing.$(TARGET_EXTENSION): $(RAAT_GRID_INDEXING_OBJS)
	$(CC) -o raat-util-grid-indexing.$(TARGET_EXTENSION) $^ $(CFLAGS) $(LIBS)
	./raat-util-grid-indexing.$(TARGET_EXTENSION)

all: 
clean:
	rm -f *.o
	rm -f ../*.o
