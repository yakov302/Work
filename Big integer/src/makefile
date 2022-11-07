SRC_DIR = .
INC_DIR = ../inc

CXX = g++
CC = $(CXX)
WARNINGS = -pedantic
DEBUG = -g3
CXX_STD = c++17
LDLIBS   = 

CXXFLAGS = $(WARNINGS) $(DEBUG) -std=$(CXX_STD) $(LDLIBS)
CPPFLAGS = -I$(INC_DIR)

TARGET = main
OBJS = ./main.o ./big_integer.o 
$(TARGET):$(OBJS)

vala: $(TARGET)
	valgrind --log-file=V1.log ./$(TARGET)
	valgrind --log-file=V2.log --leak-check=full --track-origins=yes ./$(TARGET) 
   
check: $(TARGET)
	./$(TARGET) -v
	
clean:
	@$(RM) $(TARGET) $(OBJS)
	
.PHONY: check clean
