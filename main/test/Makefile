TARGET := test_suite

INC_DIR := ../include

# Shortcut to the source directory.
SRC := ../source

SRC_FILES := main.cpp \
            # $(SRC)/driver/gpio/stub.cpp \ Om denna fanns.
                

CXX_COMPILER := g++

CXX_FLAGS := -Wall -Werror -std=c++17 -I$(INC_DIR)

default: build run

build:
	@$(CXX_COMPILER) $(SRC_FILES) -o $(TARGET) $(CXX_FLAGS)

run:
	@./$(TARGET)
	
clean:
	@rm -f $(TARGET)
