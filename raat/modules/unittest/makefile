CC = g++
DEL = @rm -f

ifeq ($(OS),Windows_NT)
	TARGET_EXTENSION = exe
else
	TARGET_EXTENSION = out
endif

LIBS = -lcppunit

INC = -I../ \
	-I../../unittest -I../../raat_code \
	-I../../raat_code/utility \
	-I../../raat_code/messages \
	-I../../devices -I../../parameters \
	-I../task \
	-I../oneshot_timer \
	-I../oneshot_task \
	-I../grid_indexer

CFLAGS = -Wall -Wextra

GLOBAL_OBJS = raat-module.unittest.runner.o \
	../../unittest/raat-mock-board.o

ONESHOT_TIMER_OBJS = ../oneshot_timer/raat-oneshot-timer.o \
	raat-module-oneshot-timer.unittest.o \
	$(GLOBAL_OBJS)

ONESHOT_TASK_OBJS = ../oneshot_task/raat-oneshot-task.o \
	../oneshot_timer/raat-oneshot-timer.o \
	raat-module-oneshot-task.unittest.o \
	$(GLOBAL_OBJS)

TASK_OBJS = ../task/raat-task.o \
	../oneshot_task/raat-oneshot-task.o \
	../oneshot_timer/raat-oneshot-timer.o \
	raat-module-task.unittest.o \
	$(GLOBAL_OBJS)


GRID_INDEXER_OBJS = ../grid_indexer/grid-indexer.o \
	raat-module-grid-indexer.unittest.o \
	$(GLOBAL_OBJS)

%.o: %.cpp
	$(CC) $(INC) $(DEFINES) -c -o $@ $< $(CFLAGS)

raat-module-oneshot-timer.$(TARGET_EXTENSION): $(ONESHOT_TIMER_OBJS)
	$(CC) -o raat-module-oneshot-timer.$(TARGET_EXTENSION) $^ $(CFLAGS) $(LIBS)
	./raat-module-oneshot-timer.$(TARGET_EXTENSION)

raat-module-oneshot-task.$(TARGET_EXTENSION): $(ONESHOT_TASK_OBJS)
	$(CC) -o raat-module-oneshot-task.$(TARGET_EXTENSION) $^ $(CFLAGS) $(LIBS)
	./raat-module-oneshot-task.$(TARGET_EXTENSION)

raat-module-task.$(TARGET_EXTENSION): $(TASK_OBJS)
	$(CC) -o raat-module-task.$(TARGET_EXTENSION) $^ $(CFLAGS) $(LIBS)
	./raat-module-task.$(TARGET_EXTENSION)

raat-module-grid-indexer.$(TARGET_EXTENSION): $(GRID_INDEXER_OBJS)
	$(CC) -o raat-module-grid-indexer.$(TARGET_EXTENSION) $^ $(CFLAGS) $(LIBS)
	./raat-module-grid-indexer.$(TARGET_EXTENSION)

all: clean raat-module-oneshot-timer.$(TARGET_EXTENSION) raat-module-oneshot-task.$(TARGET_EXTENSION) raat-module-task.$(TARGET_EXTENSION) raat-module-grid-indexer.$(TARGET_EXTENSION)

clean:
	$(DEL) $(GLOBAL_OBJS)
	$(DEL) $(ONESHOT_TIMER_OBJS)
	$(DEL) $(ONESHOT_TASK_OBJS)
	$(DEL) $(GRID_INDEXER_OBJS)