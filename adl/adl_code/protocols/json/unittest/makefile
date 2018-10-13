CC = g++
DEL = @rm -f

ifeq ($(OS),Windows_NT)
	TARGET_EXTENSION = exe
else
	TARGET_EXTENSION = out
endif

LIBS = -lcppunit

OBJ = json.unittest.o ../json.o ../../../adl.o \
	../../../../unittest/adl-mock-board.o \
	../../../../unittest/adl-mock-device.o \
	../../../../unittest/adl-mock-parameter.o \
	../../../adl-callbacks.o
	
INC = -I../../../../unittest/ -I../ -I../../ -I../../../ -I../../../../devices -I../../../../parameters

TARGET = json.unittest.$(TARGET_EXTENSION)

CFLAGS = -Wall -Wextra

%.o: %.cpp
	$(CC) $(INC) $(DEFINES) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	$(CC) -o $(TARGET) $^ $(CFLAGS) $(LIBS)
	./$(TARGET)
	
clean:
	$(DEL) $(TARGET)
