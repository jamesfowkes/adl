CC = g++
DEL = rm -f

ifeq ($(OS),Windows_NT)
	TARGET_EXTENSION = exe
else
	TARGET_EXTENSION = out
endif

LIBS = -lcppunit

INC = -I../ -I../boolean -I../integer -I../rgb -I../string \
	-I../../raat_code -I../../raat_code/utility \
	-I../../unittest -I../../devices \
	-I../../raat_code/messages

CFLAGS = -Wall -Wextra

GLOBAL_OBJS = raat-parameter.unittest.runner.o \
	../../unittest/raat-mock-board.o

INTEGER_OBJS = ../integer/integer-param.o \
	raat-parameter-integer.unittest.o \
	../../raat_code/utility/raat-util-limited-range-int.o \
	$(GLOBAL_OBJS)

BOOLEAN_OBJS = ../boolean/boolean-param.o \
	raat-parameter-boolean.unittest.o \
	$(GLOBAL_OBJS)

RGB_OBJS = ../rgb/rgb-param.o \
	raat-parameter-rgb.unittest.o \
	../../raat_code/utility/raat-util-limited-range-int.o \
	../../raat_code/messages/raat-messages.o \
	../../raat_code/utility/raat-util.o \
	$(GLOBAL_OBJS)

STRING_OBJS = ../string/string-param.o \
	raat-parameter-string.unittest.o \
	$(GLOBAL_OBJS)

ALL_TESTS = raat-integer-param raat-boolean-param raat-rgb-param raat-string-param
ALL_TEST_EXECTUABLES = $(addsuffix .$(TARGET_EXTENSION), $(ALL_TESTS))

%.o: %.cpp
	$(CC) $(INC) $(DEFINES) -c -o $@ $< $(CFLAGS)

raat-integer-param.$(TARGET_EXTENSION): $(INTEGER_OBJS)
	$(CC) -o raat-integer-param.$(TARGET_EXTENSION) $^ $(CFLAGS) $(LIBS)
	./raat-integer-param.$(TARGET_EXTENSION)

raat-boolean-param.$(TARGET_EXTENSION): $(BOOLEAN_OBJS)
	$(CC) -o raat-boolean-param.$(TARGET_EXTENSION) $^ $(CFLAGS) $(LIBS)
	./raat-boolean-param.$(TARGET_EXTENSION)

raat-rgb-param.$(TARGET_EXTENSION): $(RGB_OBJS)
	$(CC) -o raat-rgb-param.$(TARGET_EXTENSION) $^ $(CFLAGS) $(LIBS)
	./raat-rgb-param.$(TARGET_EXTENSION)

raat-string-param.$(TARGET_EXTENSION): $(STRING_OBJS)
	$(CC) -o raat-string-param.$(TARGET_EXTENSION) $^ $(CFLAGS) $(LIBS)
	./raat-string-param.$(TARGET_EXTENSION)

all: $(ALL_TEST_EXECTUABLES)

clean:
	$(DEL) $(ALL_TEST_EXECTUABLES)
	$(DEL) $(GLOBAL_OBJS)
	$(DEL) $(INTEGER_OBJS)
	$(DEL) $(BOOLEAN_OBJS)
	$(DEL) $(RGB_OBJS)
	$(DEL) $(STRING_OBJS)
