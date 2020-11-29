#!/usr/bin/env bash

# sudo apt-get install libldap2-dev

# Runtime Variables
PROJECT_ROOT=$(pwd)
# shellcheck disable=SC2034
BASE_FILES_BIN="$PROJECT_ROOT/src/linux/linuxMain.cpp $PROJECT_ROOT/src/linux/adAdapterLinux.cpp $PROJECT_ROOT/src/linux/include/libAdLinux.hpp"
BASE_FILES="$PROJECT_ROOT/src/linux/sharedObject.cpp $PROJECT_ROOT/src/linux/adAdapterLinux.cpp $PROJECT_ROOT/src/linux/include/libAdLinux.hpp"
# shellcheck disable=SC2034
OUT_BIN="$PROJECT_ROOT/out/libAdAuthBin"
# shellcheck disable=SC2034
OUT_BIN_DEBUG="$PROJECT_ROOT/out/libAdAuthBinDebug"
OUT_SO="$PROJECT_ROOT/out/libAdAuth.so"
# shellcheck disable=SC2034
OUT_SO_DEBUG="$PROJECT_ROOT/out/libAdAuthDebug.so"

# Clear previous build files
rm -rf ./build && mkdir -p ./build
rm -rf ./out   && mkdir -p ./out

# Change Directory to ./src
cd build || exit 1

# Build Test Binary [Debug]
g++ -std=c++17 -DDEBUG -I/usr/include -I"$PROJECT_ROOT"/src/linux/include $BASE_FILES_BIN -lldap -o "$OUT_BIN_DEBUG"

# Build Test Binary [Release]
g++ -std=c++17 -I/usr/include -I"$PROJECT_ROOT"/src/linux/include $BASE_FILES_BIN -lldap -o "$OUT_BIN"

# Build Shared Object Library [Debug]
g++ -std=c++17 -fPIC -c -Wall -DDEBUG -I/usr/include -I"$PROJECT_ROOT"/src/linux/include $BASE_FILES
g++ -shared adAdapterLinux.o sharedObject.o -lldap -o "$OUT_SO_DEBUG"

# Build Shared Object Library [Release]
g++ -std=c++17 -fPIC -c -Wall -I/usr/include -I"$PROJECT_ROOT"/src/linux/include $BASE_FILES
g++ -shared adAdapterLinux.o sharedObject.o -lldap -o "$OUT_SO"

# Change directory back to $PROJECT_ROOT
cd ../
