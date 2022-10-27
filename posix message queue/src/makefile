
SRC_DIR = .
INC_DIR = ../inc/

CXX = gcc
CC = $(CXX)
WARNINGS = -pedantic
DEBUG = -g3
LIBRARIES = -pthread -lrt
CXXFLAGS = $(WARNINGS) $(DEBUG)

CFLAGS = -I$(INC_DIR)

TARGET = main 

OBJS = common.o data.o main.o receiver.o sender.o thread.o 

$(TARGET):$(OBJS)
	$(CC) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBRARIES)

common.o: common.c $(INC_DIR)common.h
	$(CC) $(CXXFLAGS) -c common.c

data.o: data.c $(INC_DIR)data.h
	$(CC) $(CXXFLAGS) -c data.c

main.o: main.c $(INC_DIR)sender.h $(INC_DIR)receiver.h $(INC_DIR)thread.h $(INC_DIR)common.h
	$(CC) $(CXXFLAGS) -c main.c

receiver.o: receiver.c $(INC_DIR)receiver.h
	$(CC) $(CXXFLAGS) -c receiver.c

sender.o: sender.c $(INC_DIR)sender.h 
	$(CC) $(CXXFLAGS) -c sender.c

thread.o: thread.c $(INC_DIR)thread.h
	$(CC) $(CXXFLAGS) -c thread.c

check: $(TARGET)
	./$(TARGET) 

debug: $(TARGET)
	gdb ./$(TARGET)

clean:
	@$(RM) $(TARGET) $(OBJS) 

.PHONY: check clean
