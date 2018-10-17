CC = g++
DEL = @rm -f

ifeq ($(OS),Windows_NT)
	TARGET_EXTENSION = exe
else
	TARGET_EXTENSION = out
endif

LIBS = -lcppunit

INC = -I../ -I../boolean -I../integer -I../rgb -I../../adl_code

CFLAGS = -Wall -Wextra

GLOBAL_OBJS = adl-parameter.unittest.runner.o

INTEGER_OBJS = ../integer/integer-param.o \
	adl-parameter-integer.unittest.o \
	../../adl_code/adl-util-limited-range-int.o \
	$(GLOBAL_OBJS)

BOOLEAN_OBJS = ../boolean/boolean-param.o \
	adl-parameter-boolean.unittest.o \
	$(GLOBAL_OBJS)

RGB_OBJS = ../rgb/rgb-param.o \
	adl-parameter-rgb.unittest.o \
	../../adl_code/adl-util-limited-range-int.o \
	../../adl_code/adl-messages.o \
	../../adl_code/adl-util.o \
	$(GLOBAL_OBJS)

%.o: %.cpp
	$(CC) $(INC) $(DEFINES) -c -o $@ $< $(CFLAGS)

adl-integer-param.$(TARGET_EXTENSION): $(INTEGER_OBJS)
	$(CC) -o adl-integer-param.$(TARGET_EXTENSION) $^ $(CFLAGS) $(LIBS)
	./adl-integer-param.$(TARGET_EXTENSION)

adl-boolean-param.$(TARGET_EXTENSION): $(BOOLEAN_OBJS)
	$(CC) -o adl-boolean-param.$(TARGET_EXTENSION) $^ $(CFLAGS) $(LIBS)
	./adl-boolean-param.$(TARGET_EXTENSION)

adl-rgb-param.$(TARGET_EXTENSION): $(RGB_OBJS)
	$(CC) -o adl-rgb-param.$(TARGET_EXTENSION) $^ $(CFLAGS) $(LIBS)
	./adl-rgb-param.$(TARGET_EXTENSION)

all: adl-integer-param.$(TARGET_EXTENSION) adl-boolean-param.$(TARGET_EXTENSION)

clean:
	$(DEL) $(GLOBAL_OBJS)
	$(DEL) $(INTEGER_OBJS)
	$(DEL) $(BOOLEAN_OBJS)
	$(DEL) $(RGB_OBJS)
	