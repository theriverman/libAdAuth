#!/usr/bin/env bash

# sudo apt-get install libldap2-dev

# Export Runtime Variables
export PROJECT_ROOT=$(pwd)
export BASE_FILES_BIN="$PROJECT_ROOT/src/linux/linuxMain.cpp $PROJECT_ROOT/src/linux/adAdapterLinux.cpp $PROJECT_ROOT/src/linux/include/libAdLinux.h"
export BASE_FILES="$PROJECT_ROOT/src/linux/sharedObject.cpp $PROJECT_ROOT/src/linux/adAdapterLinux.cpp $PROJECT_ROOT/src/linux/include/libAdLinux.h"
export LIBLDAP="/usr/lib/x86_64-linux-gnu/libldap-2.4.so.2"
export OUT_BIN="test_libAdAuthBin"
export OUT_BIN_DEBUG="libAdAuthBinDebug"
export OUT_SO="$PROJECT_ROOT/out/libAdAuth.so"
export OUT_SO_DEBUG="$PROJECT_ROOT/out/libAdAuthDebug.so"

# Change Directory to ./src
mkdir -p build || exit 1
mkdir -p out   || exit 1
cd build || exit 1

# Build Test Binary [Debug]
# g++ -std=c++17 -I. -DDEBUG $BASE_FILES_BIN $LIBLDAP -o $OUT_BIN_DEBUG

# Build Test Binary [Release]
# g++ -std=c++17 -I. $BASE_FILES_BIN $LIBLDAP -o $OUT_BIN

# Build Shared Object Library [Debug]
# g++ -std=c++17 -fPIC -c -Wall -DDEBUG $BASE_FILES
# g++ -shared adAdapterLinux.o sharedObject.o $LIBLDAP -o $OUT_SO_DEBUG

# Build Shared Object Library [Release]
g++ -std=c++17 -fPIC -c -Wall $BASE_FILES
g++ -shared ../build/adAdapterLinux.o ../build/sharedObject.o $LIBLDAP -o $OUT_SO

# Change directory back to $PROJECT_ROOT
cd ../
