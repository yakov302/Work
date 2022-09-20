
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
OBJS = $(SRC_DIR)/main.o $(SRC_DIR)/protocol.o $(SRC_DIR)/args.o $(SRC_DIR)/socket.o $(SRC_DIR)/list.o $(SRC_DIR)/list_iterator.o
OBJS += $(SRC_DIR)/tcp.o $(SRC_DIR)/mutex.o $(SRC_DIR)/thread.o $(SRC_DIR)/router.o $(SRC_DIR)/action_in.o $(SRC_DIR)/user.o 
OBJS += $(SRC_DIR)/hash_map.o $(SRC_DIR)/users_manager.o $(SRC_DIR)/sha256.o $(SRC_DIR)/subscribs_manager.o

$(TARGET):$(OBJS)
	$(CC) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBRARIES)

check: $(TARGET)
	./$(TARGET)  

debug: $(TARGET)
	gdb ./$(TARGET)

clean:
	@$(RM) $(TARGET) $(OBJS)

.PHONY: check clean