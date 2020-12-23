# Basic Compiler Settings
CC = g++
CFLAGS = -std=c++17

# Runtime Variables
PRODNAME = libAdAuth
PROJECT_ROOT = .

# Detect The Operating System
ifeq ($(OS),Windows_NT)
	exit
else
	OS_NAME := $(shell uname -s | tr A-Z a-z)
	ifeq ($(OS_NAME),linux)
		INCLUDE_FLAGS = -I/usr/include
	endif
	ifeq ($(OS_NAME),darwin)
		INCLUDE_FLAGS = -I$(PROJECT_ROOT)/src/$(OS_NAME)/include
		INCLUDE_FLAGS += -I$(shell brew --prefix openldap)/include
	endif
endif

# Base Files
BASE_FILES_BIN = $(PROJECT_ROOT)/src/$(OS_NAME)/main.cpp $(PROJECT_ROOT)/src/$(OS_NAME)/adapter.cpp

# Build Dir.
BUILD_DIR = ./build
OBJECT_FILE_ADAPTER = $(PRODNAME).adapter.o
OBJECT_FILE_ADAPTER_DEBUG = $(PRODNAME).adapter.debug.o
OBJECT_FILE_INTERFACE = $(PRODNAME).interface.o
OBJECT_FILE_INTERFACE_DEBUG = $(PRODNAME).interface.debug.o

# Out Dir.
OUT_DIR = ./out
OUT_BIN = $(PRODNAME).release.bin
OUT_BIN_DEBUG = $(PRODNAME).debug.bin
OUT_LIB = $(PRODNAME).release.dylib
OUT_LIB_DEBUG = $(PRODNAME).debug.dylib

#
# BUILD TARGETS 
#

all: bin lib

all-debug: bin-debug lib-debug

bin:
	$(CC) $(CFLAGS) $(INCLUDE_FLAGS) $(PROJECT_ROOT)/src/$(OS_NAME)/main.cpp $(PROJECT_ROOT)/src/$(OS_NAME)/adapter.cpp -lldap -o ./out/$(OUT_BIN)

lib:
	$(CC) $(CFLAGS) -fPIC -Wall -c $(PROJECT_ROOT)/src/$(OS_NAME)/interface.cpp -o $(BUILD_DIR)/$(OBJECT_FILE_INTERFACE)
	$(CC) $(CFLAGS) -fPIC -Wall -c $(INCLUDE_FLAGS) $(PROJECT_ROOT)/src/$(OS_NAME)/adapter.cpp -o $(BUILD_DIR)/$(OBJECT_FILE_ADAPTER)
	$(CC) -dynamiclib -lldap $(BUILD_DIR)/$(OBJECT_FILE_INTERFACE) $(BUILD_DIR)/$(OBJECT_FILE_ADAPTER) -o $(OUT_DIR)/$(OUT_LIB)

bin-debug:
	$(CC) $(CFLAGS) -DDEBUG $(INCLUDE_FLAGS) $(PROJECT_ROOT)/src/$(OS_NAME)/main.cpp $(PROJECT_ROOT)/src/$(OS_NAME)/adapter.cpp -lldap -o ./out/$(OUT_BIN_DEBUG)

lib-debug:
	$(CC) $(CFLAGS) -fPIC -Wall -c -DDEBUG $(PROJECT_ROOT)/src/$(OS_NAME)/interface.cpp -o $(BUILD_DIR)/$(OBJECT_FILE_INTERFACE_DEBUG)
	$(CC) $(CFLAGS) -fPIC -Wall -c -DDEBUG $(INCLUDE_FLAGS) $(PROJECT_ROOT)/src/$(OS_NAME)/adapter.cpp -o $(BUILD_DIR)/$(OBJECT_FILE_ADAPTER_DEBUG)
	$(CC) -dynamiclib -lldap -DDEBUG $(BUILD_DIR)/$(OBJECT_FILE_INTERFACE_DEBUG) $(BUILD_DIR)/$(OBJECT_FILE_ADAPTER_DEBUG) -o $(OUT_DIR)/$(OUT_LIB_DEBUG)

clean-build:
	rm -rf ./build/* || mkdir -p build || exit 1

clean-out:
	rm -rf ./out/*   || mkdir -p out   || exit 1

exit:
	echo "This operating system is not supported yet"

clean-all: clean-build clean-out
