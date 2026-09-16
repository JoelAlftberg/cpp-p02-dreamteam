# Testsuite target.
TARGET := testsuite

# Source directory.
SOURCE_DIR := ../source

# Source files - update this list as new source files are added to the system.
SOURCE_FILES := \
                $(SOURCE_DIR)/driver/adc/esp32s3.cpp \
                $(SOURCE_DIR)/driver/gpio/esp32s3.cpp \
                $(SOURCE_DIR)/driver/serial/esp32s3.cpp \
                $(SOURCE_DIR)/driver/tempsensor/tmp36.cpp \
                $(SOURCE_DIR)/driver/timer/esp32s3.cpp \
                $(SOURCE_DIR)/logic/logic.cpp \
                $(SOURCE_DIR)/utils/utils.cpp \

# Test files - update this list as new test files are added to the system.
TEST_FILES := driver/adc/esp32s3_test.cpp \
              driver/eeprom/atmega328p_test.cpp \
              driver/gpio/esp32s3_test.cpp \
              driver/gpio/stub_test.cpp \
              driver/serial/esp32s3_test.cpp \
              driver/tempsensor/tmp36_test.cpp \
              driver/timer/esp32s3_test.cpp \
              driver/timer/stub_test.cpp \
              driver/watchdog/atmega328p_test.cpp \
              logic/logic_test.cpp \
              testsuite.cpp \

# All files.
ALL_FILES := $(SOURCE_FILES) $(TEST_FILES)

# Main include directory.
INC_DIR := ../include

# Directory containing the yrgo::test framework submodule.
YRGO_TEST_DIR := ../../test
YRGO_TEST_LIB := $(YRGO_TEST_DIR)/libyrgo_test.a

# C++ compiler.
CXX_COMPILER = g++

# Extra compiler flags, appended to CXX_FLAGS. Used to build the suite with coverage
# instrumentation (L11) or sanitizers (L12) without editing this file, e.g.:
#   make clean && make EXTRA_FLAGS="--coverage -O0 -g"
#   make clean && make EXTRA_FLAGS="-fsanitize=address,undefined -fno-sanitize-recover=all -g"
EXTRA_FLAGS =

# C++ compiler flags.
CXX_FLAGS = -std=c++17 -Werror -Wall -I$(INC_DIR) -I$(YRGO_TEST_DIR)/include -DTESTSUITE \
            $(EXTRA_FLAGS)

.PHONY: default build run clean

# Build and run the test suite as default:
default: build run

# Build the yrgo::test library.
$(YRGO_TEST_LIB):
	@$(MAKE) -C $(YRGO_TEST_DIR) lib

# Build the test suite.
build: $(YRGO_TEST_LIB)
	@$(CXX_COMPILER) $(ALL_FILES) -o $(TARGET) $(CXX_FLAGS) -L$(YRGO_TEST_DIR) -lyrgo_test

# Run the test suite.
run: build
	@./$(TARGET)

# Clean the test suite, the yrgo::test library and any coverage artifacts.
clean:
	@rm -f $(TARGET) *.gcda *.gcno
	@$(MAKE) -C $(YRGO_TEST_DIR) clean
