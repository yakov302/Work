
SRC_DIR = .
INC_DIR = ../inc

CXX = gcc
CC = $(CXX)
WARNINGS = -ansi -pedantic -Wall -Werror
DEBUG = -g3
LIBRARIES = -pthread
CXXFLAGS = $(WARNINGS) $(DEBUG)

CFLAGS = -I$(INC_DIR)

TARGET = router 
OBJS = $(SRC_DIR)/main.o $(SRC_DIR)/protocol.o $(SRC_DIR)/args.o $(SRC_DIR)/socket.o $(SRC_DIR)/action_out.o 
OBJS += $(SRC_DIR)/tcp.o $(SRC_DIR)/mutex.o $(SRC_DIR)/thread.o $(SRC_DIR)/router.o $(SRC_DIR)/action_in.o

$(TARGET):$(OBJS)
	$(CC) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBRARIES)

check: $(TARGET)
	./$(TARGET)  

debug: $(TARGET)
	gdb ./$(TARGET)

clean:
	@$(RM) $(TARGET) $(OBJS)

.PHONY: check clean