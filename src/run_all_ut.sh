#!/bin/bash

set -e

# Nella cartella ./build avviare tutti gli eseguibili che iniziano con ut_

BUILD_DIR="build"
BUILD_TYPE="${1:-Release}"  # Default a Release se non specificato

# Cerca gli eseguibili di test nelle diverse possibili locazioni
TEST_LOCATIONS=(
    "$BUILD_DIR/$BUILD_TYPE"
    "$BUILD_DIR"
)

echo "Searching for test executables (build type: $BUILD_TYPE)..."

TESTS_FOUND=0
for location in "${TEST_LOCATIONS[@]}"; do
    if [ -d "$location" ]; then
        for file in "$location"/ut_*; do
            if [ -x "$file" ]; then
                echo "Running test: $file"
                "$file"
                TESTS_FOUND=$((TESTS_FOUND + 1))
            fi
        done
    fi
done

if [ $TESTS_FOUND -eq 0 ]; then
    echo "No test executables found. Please build the project first."
    exit 1
fi

echo "All tests completed successfully! ($TESTS_FOUND test suite(s) executed)"