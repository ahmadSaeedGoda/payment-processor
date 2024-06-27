CXX = g++
CXXFLAGS = -std=c++23 -pthread -Iinclude
LDFLAGS = -pthread

SRC_DIR = src
OBJ_DIR = build
TARGET = payment_processor

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS)) # pattern substitution

# Compilation for src code files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Linking all object files into the final executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(TARGET)

run:
	./$(TARGET)

test:
	make clean && mkdir build && cd build && cmake .. && cmake --build . && ctest --output-on-failure

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

all: $(TARGET)

.PHONY: clean all test
