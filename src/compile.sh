#!/bin/bash
set -e

BUILD_DIR="build"
PRESET="conan-release"

# mkdir "$BUILD_DIR"

conan install . --output-folder="$BUILD_DIR" --build=missing

cmake -B "$BUILD_DIR" --preset "$PRESET"

NUM_CORES=$(sysctl -n hw.ncpu)

cmake --build build -j$NUM_CORES