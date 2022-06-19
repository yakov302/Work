SRC_DIR = ../src
TEST_DIR  = ../test/image
INC_DIR = ../inc

CXX = g++
CC = $(CXX)

WARNINGS = -pedantic
WARNINGS += -Wall -Werror

DEBUG = -g3
CXX_STD = c++17

CXXFLAGS = $(WARNINGS) $(DEBUG) -std=$(CXX_STD)


CPPFLAGS = -I$(INC_DIR)

TARGET = utest
OBJS = utest.o 

$(TARGET):$(OBJS)

utest.o : $(INC_DIR)/image.hpp 

check: $(TARGET)
	./$(TARGET) -v

prod: CXXFLAGS += -O2 -DNDEBUG
prod: $(TARGET)
	./$(TARGET) -v

clean:
	@$(RM) $(TARGET) $(OBJS) book*

.PHONY: check clean
