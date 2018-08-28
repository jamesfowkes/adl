CC = g++
DEL = @rm -f

ifeq ($(OS),Windows_NT)
	TARGET_EXTENSION = exe
else
	TARGET_EXTENSION = out
endif

LIBS = -lcppunit

INC = -I../ -I../boolean -I../integer

CFLAGS = -Wall -Wextra

OBJS = ../boolean/boolean-param.o \
	../integer/integer-param.o \
	adl-parameter-boolean.unittest.o \
	adl-parameter-integer.unittest.o \
	adl-parameter.unittest.runner.o

%.o: %.cpp
	$(CC) $(INC) $(DEFINES) -c -o $@ $< $(CFLAGS)

.PHONY: adl-parameter
adl-parameter: $(OBJS)
	$(CC) -o adl-parameter.$(TARGET_EXTENSION) $^ $(CFLAGS) $(LIBS)
	./adl-parameter.$(TARGET_EXTENSION)
