CC = g++
DEL = @rm -f

ifeq ($(OS),Windows_NT)
	TARGET_EXTENSION = exe
else
	TARGET_EXTENSION = out
endif

LIBS = -lcppunit

OBJ = simple.unittest.o ../simple.o ../../../raat.o \
	../../../../unittest/raat-mock-board.o \
	../../../../unittest/raat-mock-device.o \
	../../../../unittest/raat-mock-parameter.o \
	../../../raat-callbacks.o
	
INC = -I../../../../unittest/ -I../ -I../../ -I../../../ -I../../../../devices -I../../../../parameters

TARGET = simple.unittest.$(TARGET_EXTENSION)

CFLAGS = -Wall -Wextra

%.o: %.cpp
	$(CC) $(INC) $(DEFINES) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	$(CC) -o $(TARGET) $^ $(CFLAGS) $(LIBS)
	./$(TARGET)
	
clean:
	$(DEL) $(TARGET)
