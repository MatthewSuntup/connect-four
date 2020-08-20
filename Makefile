CXX = g++
CXXFLAGS = -g -Wall -Iinclude
TARGET=connect_four

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

_OBJS = connect_four.o debugging.o evaluation.o
OBJS = $(patsubst %,$(OBJ_DIR)/%,$(_OBJS))

DEPS = $(INC_DIR)/*.hpp

# Genereate object files from source
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(DEPS) | $(OBJ_DIR)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

# Link objects into executable
$(TARGET): $(OBJS)
	$(CXX) -o $@ $(OBJS)

# Make object directory if it doesn't exist yet
$(OBJ_DIR):
	mkdir $@