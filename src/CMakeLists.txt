cmake_minimum_required(VERSION 3.28)

# Nome del progetto
project(cripto_project)

# Impostazioni cmake
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic")

# Trova le librerie installate tramite conan
find_package(Boost REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(GTest REQUIRED)

# Aggiungi le sottodirectory
add_subdirectory(lib-hash)
add_subdirectory(lib-log)

# Aggiungi l'eseguibile principale
add_executable(${PROJECT_NAME} main.cc)
add_executable(sha_cli sha_cli.cc)
add_executable(ut_sha_functions ut_sha_functions.cc)

# Linka le librerie
target_link_libraries(${PROJECT_NAME} PRIVATE 
    hash-lib
    logging-lib
    openssl::openssl
    boost::boost
)

target_link_libraries(sha_cli PRIVATE 
    hash-lib
    logging-lib
    openssl::openssl
)

target_link_libraries(ut_sha_functions PRIVATE 
    hash-lib
    logging-lib
    openssl::openssl
    gtest::gtest
)

# Copia il file commedia.txt
configure_file(${CMAKE_SOURCE_DIR}/commedia.txt ${CMAKE_BINARY_DIR}/commedia.txt COPYONLY)