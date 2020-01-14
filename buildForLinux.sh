#!/usr/bin/env bash

# sudo apt-get install libldap2-dev

# Runtime Variables
PROJECT_ROOT=$(pwd)
BASE_FILES_BIN="$PROJECT_ROOT/src/linux/linuxMain.cpp $PROJECT_ROOT/src/linux/adAdapterLinux.cpp $PROJECT_ROOT/src/linux/include/libAdLinux.h"
BASE_FILES="$PROJECT_ROOT/src/linux/sharedObject.cpp $PROJECT_ROOT/src/linux/adAdapterLinux.cpp $PROJECT_ROOT/src/linux/include/libAdLinux.h"
LIBLDAP="/usr/lib/x86_64-linux-gnu/libldap-2.4.so.2"
OUT_BIN="test_libAdAuthBin"
OUT_BIN_DEBUG="libAdAuthBinDebug"
OUT_SO="$PROJECT_ROOT/out/libAdAuth.so"
OUT_SO_DEBUG="$PROJECT_ROOT/out/libAdAuthDebug.so"

# Clear previous build files
rm -rf ./build/* || mkdir -p build || exit 1
rm -rf ./out/*   || mkdir -p out   || exit 1

# Change Directory to ./src
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
g++ -shared adAdapterLinux.o sharedObject.o $LIBLDAP -o $OUT_SO

# Change directory back to $PROJECT_ROOT
cd ../
