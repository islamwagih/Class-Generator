# Compiler settings
CXX=g++
CXXFLAGS=-std=c++11 -Wall -Wextra

# Directories
SRC_DIR=sources
INC_DIR=headers
OBJ_DIR=obj

# Source files
SOURCES=$(wildcard $(SRC_DIR)/*.cpp)
OBJECTS=$(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# Include directories
INCLUDES=-I$(INC_DIR)

# Output file name
OUTPUT=temp

# Make targets
all: $(OUTPUT)

$(OUTPUT): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(OUTPUT)
