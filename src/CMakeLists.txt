cmake_minimum_required(VERSION 3.28)

if(NOT WIN32)
  string(ASCII 27 Esc)
  set(ColourReset "${Esc}[m")
  set(ColourBold  "${Esc}[1m")
  set(Red         "${Esc}[31m")
  set(Green       "${Esc}[32m")
  set(Yellow      "${Esc}[33m")
  set(Blue        "${Esc}[34m")
  set(Magenta     "${Esc}[35m")
  set(Cyan        "${Esc}[36m")
  set(White       "${Esc}[37m")
  set(BoldRed     "${Esc}[1;31m")
  set(BoldGreen   "${Esc}[1;32m")
  set(BoldYellow  "${Esc}[1;33m")
  set(BoldBlue    "${Esc}[1;34m")
  set(BoldMagenta "${Esc}[1;35m")
  set(BoldCyan    "${Esc}[1;36m")
  set(BoldWhite   "${Esc}[1;37m")
endif()

# Nome del progetto
project(cripto_project)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
elseif(CMAKE_BUILD_TYPE STREQUAL "release")
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

# Definisci variabili per i nomi degli eseguibili
set(MAIN_EXECUTABLE ${PROJECT_NAME})
set(CLI_EXECUTABLE sha_cli)
set(TEST_EXECUTABLE ut_sha_functions)

# Usa le variabili per gli eseguibili
add_executable(${MAIN_EXECUTABLE} main.cc)
add_executable(${CLI_EXECUTABLE} sha_cli.cc)
add_executable(${TEST_EXECUTABLE} ut_sha_functions.cc)

# Aggiungi questa riga dopo la definizione degli eseguibili
target_compile_features(${MAIN_EXECUTABLE} PRIVATE cxx_std_17)
target_compile_features(${CLI_EXECUTABLE} PRIVATE cxx_std_17)
target_compile_features(${TEST_EXECUTABLE} PRIVATE cxx_std_17)

# Definisci una variabile per le dipendenze comuni
set(COMMON_DEPENDENCIES
    hash-lib
    logging-lib
    openssl::openssl
)

# Usa la variabile nelle sezioni target_link_libraries
target_link_libraries(${MAIN_EXECUTABLE} PRIVATE 
    ${COMMON_DEPENDENCIES}
    boost::boost
)

target_link_libraries(${CLI_EXECUTABLE} PRIVATE 
    ${COMMON_DEPENDENCIES}
)

target_link_libraries(${TEST_EXECUTABLE} PRIVATE 
    ${COMMON_DEPENDENCIES}
    gtest::gtest
)

# Copia il file commedia.txt
message("${Blue} Copia della divina Commedia.txt ${ColourReset}")
configure_file(${CMAKE_SOURCE_DIR}/commedia.txt ${CMAKE_BINARY_DIR}/commedia.txt COPYONLY)