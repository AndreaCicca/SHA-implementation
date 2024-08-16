#!/bin/bash

# Trova tutti i file .tex nelle sottocartelle
find . -type f -name "*.tex" | while read -r file
do
    echo "Processando $file"
    
    # Esegui latexindent sul file
    latexindent -w "$file"
    
    # Verifica se l'operazione è andata a buon fine
    if [ $? -eq 0 ]; then
        echo "File $file processato con successo"
    else
        echo "Errore nel processare $file"
    fi
    
    echo "------------------------"
done

echo "Operazione completata"

echo "rimozione del file *.bak[0-9]*"

find . -type f -name "*.bak[0-9]*" | while read -r file

do
    echo "Rimozione del file $file"
    rm "$file"
done