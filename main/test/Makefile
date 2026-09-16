# Target test suite.
TARGET := testsuite

# C++ compiler.
CXX_COMPILER := g++

# C++ compiler flags, we define TESTSUITE.
CXX_FLAGS := -Wall -Werror -std=c++17 -Iinclude -DTESTSUITE

# Test files.
TST_FILES := testsuite.cpp \

# Build and run the test suite by default:
default: build run

# Build the test suite.
build:
	@$(CXX_COMPILER) $(TST_FILES) -o $(TARGET) $(CXX_FLAGS)

# Run the test suite.
run:
	@./$(TARGET)

# Clean the test suite.
clean:
	@rm -f $(TARGET)
