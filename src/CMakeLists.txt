cmake_minimum_required(VERSION 3.28)

# Nome del progetto
project(cripto_project)

# Impostazione della versione dello standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Includi la cartella headers per cercare i file di intestazione
include_directories(lib-hash/headers)
include_directories(lib-log/headers)

file(GLOB LIB_SOURCES "lib-hash/*.cc")
file(GLOB LIB_LOG_SOURCES "lib-log/*.cc")

# Aggiungi librerie
add_library(hashlib ${LIB_SOURCES})
add_library(logging-lib ${LIB_LOG_SOURCES})

# Trova le librerie installate tramite conan
find_package(Boost)
find_package(OpenSSL REQUIRED)

# Aggiungi l'eseguibile principale
add_executable(${PROJECT_NAME} main.cc)

# Linka la librerie

target_link_libraries(logging-lib PRIVATE 
    boost::boost
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    hashlib
    logging-lib
    openssl::openssl
)