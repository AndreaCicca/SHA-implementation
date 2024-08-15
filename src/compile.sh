#!/bin/bash
set -e

BUILD_DIR="build"
PRESET="conan-release"

# mkdir "$BUILD_DIR"

conan install . --output-folder="$BUILD_DIR" --build=missing

cmake -B "$BUILD_DIR" --preset "$PRESET"

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    NUM_CORES=$(nproc)
elif [[ "$OSTYPE" == "darwin"* ]]; then
    NUM_CORES=$(sysctl -n hw.ncpu)
else
    NUM_CORES=1  # Fallback a 1 core in caso di sistema non supportato
fi

cmake --build build -j$NUM_CORES