
SRC_DIR = .
SRC_DIR_2 = ../src
INC_DIR = ../inc

CXX = gcc
CC = $(CXX)
WARNINGS = -ansi -pedantic -Wall -Werror
DEBUG = -g3
LIBRARIES = 
CXXFLAGS = $(WARNINGS) $(DEBUG)

CFLAGS = -I$(INC_DIR)

TARGET = main 
OBJS =  $(SRC_DIR_2)/protocol.o $(SRC_DIR_2)/args.o $(SRC_DIR)/client.o

$(TARGET):$(OBJS)
	$(CC) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBRARIES)

check: $(TARGET)
	./$(TARGET)  

debug: $(TARGET)
	gdb ./$(TARGET)

clean:
	@$(RM) $(TARGET) $(OBJS)

.PHONY: check clean