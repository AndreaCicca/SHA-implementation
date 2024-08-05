#!/bin/bash
set -e

BUILD_DIR="build"
PRESET="conan-release"

# if [ -d "$BUILD_DIR" ]; then
#     rm -rf "$BUILD_DIR"
# fi

# mkdir "$BUILD_DIR"

conan install . --output-folder="$BUILD_DIR" --build=missing

cd "$BUILD_DIR"

cmake .. --preset "$PRESET"

NUM_CORES=$(sysctl -n hw.ncpu)

cmake --build . -j$NUM_CORES

# cmake .. -G Xcode -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release