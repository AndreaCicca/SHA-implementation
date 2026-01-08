# Italian: Implementazione Secure Hash Algorithm (SHA)

[![Cmake compilation Conan](https://github.com/AndreaCicca/SHA-implementation/actions/workflows/compilation.yaml/badge.svg)](https://github.com/AndreaCicca/SHA-implementation/actions/workflows/compilation.yaml)
[![Run Tests](https://github.com/AndreaCicca/SHA-implementation/actions/workflows/test.yaml/badge.svg)](https://github.com/AndreaCicca/SHA-implementation/actions/workflows/test.yaml)

Corso di Crittografia presso Unipr.

In questo progetto è stata effettuata l'implementazione degli algoritmi SHA-0, SHA-1 e SHA-256 (SHA-2) tramite il linguaggio C++17.
La maggior parte delle dipendenze vengono gestite tramite il package manager Conan, per poter la compilazione hai bisogno soltanto 
di avere un ambiente python, un compilatore C++17 e Cmake.

## Clonazione locale del progetto ed installazione di Conan

```bash
https://github.com/AndreaCicca/SHA-implementation
```

Documentazione per Conan -> [Link](https://conan.io/downloads).

Installazione di conan:

```bash
pip install conan
```

Creazopme del profilo di conan necessario per la compilazione del progetto:

```bash
conan profile detect --force
```

## Installazione delle dipendenze e compilazione del progetto.

Compilazione del progetto e installazione delle dipendenze:

```bash
cd src &&
mkdir build &&
conan install . --output-folder=build --build=missing &&
cmake -B build --preset conan-release &&
cmake --build build
```

> [!NOTE]
> Per non copia e incollare i singoli comandi si può usare lo script src/compile.sh

## Esecuzione dei test

Dopo aver compilato il progetto, è possibile eseguire i test unitari:

### Eseguire tutti i test

```bash
cd src && ./run_all_ut.sh
```

### Eseguire i test manualmente

```bash
cd src && ./build/Release/ut_sha_functions
```

### Eseguire i test con output XML (per CI/CD)

```bash
cd src && ./build/Release/ut_sha_functions --gtest_output=xml:test-results.xml
```

I test verificano la correttezza dell'implementazione SHA-1 e SHA-256 confrontandola con la libreria OpenSSL, includendo:
- Test con stringhe vuote, corte, lunghe e molto lunghe
- Test con caratteri speciali e non-ASCII
- Test di determinismo
- Test dell'effetto valanga (avalanche effect)
- Test di performance
