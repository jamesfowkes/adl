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

OBJS = adl-util-numeric-range.unittest.o \
	adl-util-single-numeric.unittest.o \
	adl-util-csv-numerics.unittest.o \
	adl-util.unittest.runner.o \
	../adl-util.o

%.o: %.cpp
	$(CC) $(INC) $(DEFINES) -c -o $@ $< $(CFLAGS)

.PHONY: adl-util
adl-util: $(OBJS)
	$(CC) -o adl-util.$(TARGET_EXTENSION) $^ $(CFLAGS) $(LIBS)
	./adl-util.$(TARGET_EXTENSION)
