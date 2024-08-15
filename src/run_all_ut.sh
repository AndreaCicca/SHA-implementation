#!/bin/bash

set -e

# Nella cartella ./build avviare tutti gli eseguibili che iniziano con ut_

BUILD_DIR="build"

if [ -d "$BUILD_DIR" ]; then
    for file in "$BUILD_DIR"/ut_*; do
        ./"$file"
    done
fi