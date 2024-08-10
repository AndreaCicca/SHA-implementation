# Italian: Progetto corso Crittografia (Unipr)

In questo progetto è stata effettuata la reimplementazione dell'algoritmo SHA1 tramite il linguaggio C++17.
La maggior parte delle dipendenze vengono gestite tramite il package manager Conan, per poter la compilazione c'è bisogno soltanto 
di avere un ambiente python, un compilatore C++17 e Cmake.

## Clonazione locale del progetto ed installazione di Conan

```bash
git clone https://github.com/AndreaCicca/crittografia-SHA
```

Documentazione per Conan -> [Link](https://conan.io/downloads).

Installazione di conan:

```bash
pip install conan
```

Creazopme del profilo di conan necessario per la compilazione del progetto:

```bash
conan profile detect
```

## Installazione delle dipendenze e compilazione del progetto.

Compilazione del progetto e installazione delle dipendenze:

```bash
cd src &&
mkdir build &&
conan install . --output-folder=build --build=missing &&
cd build &&
cmake .. --preset conan-release &&
cmake --build .
```

> [!NOTE]
> Per non copia e incollare ogni comando si può usare lo script ./src/compile.sh 
