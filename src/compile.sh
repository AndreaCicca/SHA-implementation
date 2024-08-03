#!/bin/bash

# Abilita l'interruzione dello script in caso di errori
set -e

# Definizione delle variabili
BUILD_DIR="build"
PRESET="conan-release"

# Rimozione della directory build se esiste
if [ -d "$BUILD_DIR" ]; then
    rm -rf "$BUILD_DIR"
fi

# Creazione della directory build
mkdir "$BUILD_DIR"

# Installazione delle dipendenze con Conan
conan install . --output-folder="$BUILD_DIR" --build=missing

# Spostamento nella directory build
cd "$BUILD_DIR"

# Configurazione del progetto con CMake
cmake .. --preset "$PRESET"

# Compilazione del progetto con CMake
cmake --build .



# cmake .. -G Xcode -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release