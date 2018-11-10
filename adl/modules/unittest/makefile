CC = g++
DEL = @rm -f

ifeq ($(OS),Windows_NT)
	TARGET_EXTENSION = exe
else
	TARGET_EXTENSION = out
endif

LIBS = -lcppunit

INC = -I../ \
	-I../../unittest -I../../adl_code \
	-I../../adl_code/utility \
	-I../../adl_code/messages \
	-I../../devices -I../../parameters \
	-I../task \
	-I../oneshot_timer \
	-I../oneshot_task \
	-I../grid_indexer

CFLAGS = -Wall -Wextra

GLOBAL_OBJS = adl-module.unittest.runner.o \
	../../unittest/adl-mock-board.o

ONESHOT_TIMER_OBJS = ../oneshot_timer/adl-oneshot-timer.o \
	adl-module-oneshot-timer.unittest.o \
	$(GLOBAL_OBJS)

ONESHOT_TASK_OBJS = ../oneshot_task/adl-oneshot-task.o \
	../oneshot_timer/adl-oneshot-timer.o \
	adl-module-oneshot-task.unittest.o \
	$(GLOBAL_OBJS)

TASK_OBJS = ../task/adl-task.o \
	../oneshot_task/adl-oneshot-task.o \
	../oneshot_timer/adl-oneshot-timer.o \
	adl-module-task.unittest.o \
	$(GLOBAL_OBJS)


GRID_INDEXER_OBJS = ../grid_indexer/grid-indexer.o \
	adl-module-grid-indexer.unittest.o \
	$(GLOBAL_OBJS)

%.o: %.cpp
	$(CC) $(INC) $(DEFINES) -c -o $@ $< $(CFLAGS)

adl-module-oneshot-timer.$(TARGET_EXTENSION): $(ONESHOT_TIMER_OBJS)
	$(CC) -o adl-module-oneshot-timer.$(TARGET_EXTENSION) $^ $(CFLAGS) $(LIBS)
	./adl-module-oneshot-timer.$(TARGET_EXTENSION)

adl-module-oneshot-task.$(TARGET_EXTENSION): $(ONESHOT_TASK_OBJS)
	$(CC) -o adl-module-oneshot-task.$(TARGET_EXTENSION) $^ $(CFLAGS) $(LIBS)
	./adl-module-oneshot-task.$(TARGET_EXTENSION)

adl-module-task.$(TARGET_EXTENSION): $(TASK_OBJS)
	$(CC) -o adl-module-task.$(TARGET_EXTENSION) $^ $(CFLAGS) $(LIBS)
	./adl-module-task.$(TARGET_EXTENSION)

adl-module-grid-indexer.$(TARGET_EXTENSION): $(GRID_INDEXER_OBJS)
	$(CC) -o adl-module-grid-indexer.$(TARGET_EXTENSION) $^ $(CFLAGS) $(LIBS)
	./adl-module-grid-indexer.$(TARGET_EXTENSION)

all: clean adl-module-oneshot-timer.$(TARGET_EXTENSION) adl-module-oneshot-task.$(TARGET_EXTENSION) adl-module-task.$(TARGET_EXTENSION) adl-module-grid-indexer.$(TARGET_EXTENSION)

clean:
	$(DEL) $(GLOBAL_OBJS)
	$(DEL) $(ONESHOT_TIMER_OBJS)
	$(DEL) $(ONESHOT_TASK_OBJS)
	$(DEL) $(GRID_INDEXER_OBJS)
