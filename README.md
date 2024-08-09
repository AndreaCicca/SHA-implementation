# Italian: Progetto corso Crittografia 

Implementazione di una funzione di hash Sha1 in C++

Il progetto sfrutta Conan per le dipendenze e Cmake come toolchain di compilazione del progetto.

## Compilazione del progetto.

```bash
git clone https://github.com/AndreaCicca/crittografia-progetto
```

Installazione di conan -> [pagina download ufficiale](https://conan.io/downloads).

## Installazione delle dipendenze e compilazione del progetto.

Installazione di conan:

```bash
pip install conan
```

Compilazione del progetto e installazione delle dipendenze:

```bash
cd src
mkdir build
conan profile detect
conan install . --output-folder=build --build=missing
cd build
cmake .. --preset conan-release
cmake --build .
```

> [!NOTE]
> Per non copia e incollare ogni comando si può usare lo script ./src/compile.sh 