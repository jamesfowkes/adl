CC = g++
DEL = rm -f

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
	-I../grid_indexer \
	-I../led_effect \
	-I../http \
	-I../buffer

CFLAGS = -Wall -Wextra

DEFINES = -DHTTP_SERVER_RESPONSE_SIZE=1024

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

LED_EFFECT_OBJS = ../led_effect/larson-scanner.o \
	raat-module-led-effect.unittest.o \
	$(GLOBAL_OBJS)

HTTP_GET_SERVER_OBJS = ../http/http-get-server.o \
	../buffer/raat-buffer.o \
	../../unittest/raat-mock-logging.o \
	raat-module-http-get-server.unittest.o \
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

raat-module-led-effect.$(TARGET_EXTENSION): $(LED_EFFECT_OBJS)
	$(CC) -o raat-module-led-effect.$(TARGET_EXTENSION) $^ $(CFLAGS) $(LIBS)
	./raat-module-led-effect.$(TARGET_EXTENSION)

raat-module-http-get-server.$(TARGET_EXTENSION): $(HTTP_GET_SERVER_OBJS)
	$(CC) -o raat-module-http-get-server.$(TARGET_EXTENSION) $^ $(CFLAGS) $(LIBS)
	./raat-module-http-get-server.$(TARGET_EXTENSION)

ALL_TARGETS = raat-module-oneshot-timer.$(TARGET_EXTENSION) \
	raat-module-oneshot-task.$(TARGET_EXTENSION) \
	raat-module-task.$(TARGET_EXTENSION) \
	raat-module-grid-indexer.$(TARGET_EXTENSION) \
	raat-module-led-effect.$(TARGET_EXTENSION) \
	raat-module-http-get-server.$(TARGET_EXTENSION)

all: clean $(ALL_TARGETS)

clean:
	$(DEL) $(GLOBAL_OBJS)
	$(DEL) $(ONESHOT_TIMER_OBJS)
	$(DEL) $(ONESHOT_TASK_OBJS)
	$(DEL) $(GRID_INDEXER_OBJS)
	$(DEL) $(LED_EFFECT_OBJS)
