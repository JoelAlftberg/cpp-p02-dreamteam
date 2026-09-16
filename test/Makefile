# Target application.
TARGET := app

# Static library.
LIB := libyrgo_test.a

# C++ compiler.
CXX_COMPILER := g++

# C++ compiler flags.
CXX_FLAGS := -Wall -Werror -std=c++17 -Iinclude

# Library source files.
LIB_SRC := source/yrgo/test/impl/case.cpp \
           source/yrgo/test/impl/registry.cpp \
           source/yrgo/test/test.cpp

# Library object files.
LIB_OBJ := $(LIB_SRC:.cpp=.o)

# Application source files.
APP_SRC := source/main.cpp

# Build and run the application by default.
default: build run

# Build the static library.
lib: $(LIB)

$(LIB): $(LIB_OBJ)
	@ar rcs $(LIB) $(LIB_OBJ)

%.o: %.cpp
	@$(CXX_COMPILER) $(CXX_FLAGS) -c $< -o $@

# Build the application.
build: $(LIB)
	@$(CXX_COMPILER) $(APP_SRC) -o $(TARGET) $(CXX_FLAGS) -L. -lyrgo_test

# Run the application.
run:
	@./$(TARGET)

# Clean the application.
clean:
	@rm -f $(TARGET) $(LIB) $(LIB_OBJ)
