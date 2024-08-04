cmake_minimum_required(VERSION 3.30)

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
add_library(hash-lib ${LIB_SOURCES})
add_library(logging-lib ${LIB_LOG_SOURCES})

# Trova le librerie installate tramite conan
find_package(Boost)
find_package(OpenSSL REQUIRED)
find_package(GTest REQUIRED)

# Aggiungi l'eseguibile principale
add_executable(${PROJECT_NAME} main.cc)
add_executable(ut_sha_functions ut_sha_functions.cc)

# Linka la librerie

target_link_libraries(logging-lib PRIVATE 
    boost::boost
)

target_link_libraries(hash-lib PRIVATE 
    logging-lib
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    hash-lib
    logging-lib
    openssl::openssl
    boost::boost
)

target_link_libraries(ut_sha_functions PRIVATE 
    hash-lib
    logging-lib
    openssl::openssl
    gtest::gtest
)




configure_file(${CMAKE_SOURCE_DIR}/commedia.txt ${CMAKE_BINARY_DIR}/commedia.txt COPYONLY)