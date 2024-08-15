#!/bin/bash
set -e

if [ -d "$BUILD_DIR" ]; then
    rm -rf "$BUILD_DIR"
fi