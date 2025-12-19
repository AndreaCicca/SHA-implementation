#!/bin/bash
set -e

BUILD_DIR="build"
GENERATOR="Ninja"
BUILD_TYPE="${1:-Release}"  # Default a Release se non specificato

# install dependencies and generate toolchain in $BUILD_DIR with the correct build type
conan install . --output-folder="$BUILD_DIR" --build=missing -s build_type="$BUILD_TYPE"

TOOLCHAIN_FILE="$BUILD_DIR/Release/generators/conan_toolchain.cmake"

# Configure with explicit CMake invocation using Ninja and the Conan toolchain
cmake -S . -B "$BUILD_DIR" -G "$GENERATOR" -DCMAKE_TOOLCHAIN_FILE="$TOOLCHAIN_FILE" -DCMAKE_BUILD_TYPE="$BUILD_TYPE"

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    NUM_CORES=$(nproc)
elif [[ "$OSTYPE" == "darwin"* ]]; then
    NUM_CORES=$(sysctl -n hw.ncpu)
else
    NUM_CORES=1  # Fallback a 1 core in caso di sistema non supportato
fi

# Build
cmake --build "$BUILD_DIR" -- -j"$NUM_CORES"