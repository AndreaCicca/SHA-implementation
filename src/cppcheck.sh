#!/bin/bash

set -e

# Colori per output
if [[ "$OSTYPE" == "darwin"* ]] || [[ "$OSTYPE" == "linux-gnu"* ]]; then
    RED='\033[0;31m'
    GREEN='\033[0;32m'
    YELLOW='\033[1;33m'
    BLUE='\033[0;34m'
    NC='\033[0m' # No Color
else
    RED=''
    GREEN=''
    YELLOW=''
    BLUE=''
    NC=''
fi

# Directory da analizzare
SOURCE_DIRS=(
    "lib-hash/src"
    "lib-hash/headers"
    "lib-log/src"
    "lib-log/headers"
    "main.cc"
    "sha_cli.cc"
    "ut_sha_functions.cc"
)

# Opzioni cppcheck
CPPCHECK_OPTIONS=(
    "--enable=all"                    # Abilita tutti i controlli
    "--std=c++17"                     # Standard C++17
    "--suppress=missingIncludeSystem" # Ignora include di sistema mancanti
    "--suppress=unusedFunction"       # Ignora funzioni non usate (comuni in librerie)
    "--suppress=normalCheckLevelMaxBranches" # Ignora warning su limiti analisi branch
    "--suppress=checkersReport"       # Ignora report sui checker attivi
    "--suppress=unmatchedSuppression" # Ignora suppressioni non utilizzate
    "--inline-suppr"                  # Permette soppressione inline nel codice
    "--force"                         # Forza il controllo anche su file duplicati
    "--template=gcc"                  # Formato output simile a GCC
    "--error-exitcode=1"              # Esci con codice 1 se ci sono errori
    "-Ilib-hash/headers"              # Include directory per header hash
    "-Ilib-log/headers"               # Include directory per header log
)

# Esegui cppcheck
if cppcheck "${CPPCHECK_OPTIONS[@]}" "${SOURCE_DIRS[@]}" 2>&1; then
    echo ""
    echo -e "${GREEN}✓ Analisi completata: nessun problema trovato!${NC}"
    exit 0
fi
