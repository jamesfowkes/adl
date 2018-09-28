CC = g++
DEL = @rm -f

ifeq ($(OS),Windows_NT)
	TARGET_EXTENSION = exe
else
	TARGET_EXTENSION = out
endif

LIBS = -lcppunit

INC = -I../ -I../oneshot-timer -I../../unittest -I../../adl_code -I../../devices -I../../parameters

CFLAGS = -Wall -Wextra

GLOBAL_OBJS = adl-module.unittest.runner.o \
	../../unittest/adl-mock-board.o

ONESHOT_OBJS = ../oneshot-timer/adl-oneshot-timer.o \
	adl-module-oneshot-timer.unittest.o \
	$(GLOBAL_OBJS)

%.o: %.cpp
	$(CC) $(INC) $(DEFINES) -c -o $@ $< $(CFLAGS)

adl-module-oneshot-timer.$(TARGET_EXTENSION): $(ONESHOT_OBJS)
	$(CC) -o adl-module-oneshot-timer.$(TARGET_EXTENSION) $^ $(CFLAGS) $(LIBS)
	./adl-module-oneshot-timer.$(TARGET_EXTENSION)

all: adl-module-oneshot-timer.$(TARGET_EXTENSION)

clean:
	$(DEL) $(GLOBAL_OBJS)
	$(DEL) $(ONESHOT_OBJS)