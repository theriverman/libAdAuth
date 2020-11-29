#!/usr/bin/env bash

# brew install openldap

# Runtime Variables
PROJECT_ROOT=$(pwd)
# shellcheck disable=SC2034
BASE_FILES_BIN="$PROJECT_ROOT/src/darwin/darwinMain.cpp $PROJECT_ROOT/src/darwin/adAdapterDarwin.cpp $PROJECT_ROOT/src/darwin/include/libAdDarwin.hpp"
BASE_FILES="$PROJECT_ROOT/src/darwin/sharedObject.cpp $PROJECT_ROOT/src/darwin/adAdapterDarwin.cpp $PROJECT_ROOT/src/darwin/include/libAdDarwin.hpp"

# shellcheck disable=SC2034
OUT_BIN="test_libAdAuthBin"
# shellcheck disable=SC2034
OUT_BIN_DEBUG="libAdAuthBinDebug"
OUT_SO="$PROJECT_ROOT/out/libAdAuth.dylib"
# shellcheck disable=SC2034
OUT_SO_DEBUG="$PROJECT_ROOT/out/libAdAuthDebug.dylib"

# Clear previous build files
rm -rf ./build/* || mkdir -p build || exit 1
rm -rf ./out/*   || mkdir -p out   || exit 1

# Change Directory to ./src
cd build || exit 1

# Build Test Binary [Debug]
# g++ -std=c++17 -DDEBUG -I$(brew --prefix openldap)/include -I"$PROJECT_ROOT"/src/darwin/include $BASE_FILES_BIN -lldap

# Build Test Binary [Release]
# g++ -std=c++17 -I$(brew --prefix openldap)/include -I"$PROJECT_ROOT"/src/darwin/include $BASE_FILES_BIN -lldap

# Build Shared Object Library [Debug]
# g++ -std=c++17 -fPIC -c -Wall -DDEBUG -I$(brew --prefix openldap)/include -I"$PROJECT_ROOT"/src/darwin/include $BASE_FILES
# g++ -dynamiclib adAdapterDarwin.o sharedObject.o -lldap -o $OUT_SO_DEBUG

# Build Shared Object Library [Release]
g++ -std=c++17 -fPIC -c -Wall -I$(brew --prefix openldap)/include -I"$PROJECT_ROOT"/src/darwin/include $BASE_FILES
g++ -shared adAdapterDarwin.o sharedObject.o -lldap -o $OUT_SO

# Change directory back to $PROJECT_ROOT
cd ../
