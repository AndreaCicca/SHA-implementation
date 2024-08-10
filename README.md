# Italian: Progetto corso Crittografia 

Implementazione di una funzione di hash Sha1 in C++

Il progetto sfrutta Conan per le dipendenze e Cmake come toolchain di compilazione del progetto.

Prima di clonare e compilare il progetto accertarsi di avere a disposizione un compilatore c++ e cmake.

## Clonazione locale del progetto ed installazione di Conan

```bash
git clone https://github.com/AndreaCicca/crittografia-progetto
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
