rm -rf build
mkdir build
conan install . --output-folder=build --build=missing
cd build
cmake .. --preset conan-release
cmake --build .


# cmake .. -G Xcode -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release