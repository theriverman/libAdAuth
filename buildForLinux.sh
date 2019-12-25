#!/usr/bin/env bash

# sudo apt-get install libldap2-dev

export BASE_FILES_BIN="linuxMain.cpp adAdapterLinux.cpp libAdLinux.h"
export BASE_FILES="sharedObject.cpp adAdapterLinux.cpp libAdLinux.h"
export LIBLDAP="/usr/lib/x86_64-linux-gnu/libldap-2.4.so.2"
export OUT_BIN="test_libAdAuthBin"
export OUT_BIN_DEBUG="libAdAuthBinDebug"
export OUT_SO="libAdAuth.so"
export OUT_SO_DEBUG="libAdAuthDebug.so"

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


# Cleanup
rm -rf adAdapterLinux.o libAdLinux.h.gch sharedObject.o
