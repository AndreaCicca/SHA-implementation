rm -rf build
mkdir build
./pre-compilation.sh
cd build
cmake .. --preset conan-release
cmake --build .


# cmake .. -G Xcode -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release