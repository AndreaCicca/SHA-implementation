# CMakeLists.txt per la libreria lib-hash

# Aggiungi i file sorgenti
file(GLOB LIB_SOURCES "src/*.cc")

# Crea la libreria hash-lib
add_library(hash-lib ${LIB_SOURCES})

# Includi la directory degli headers
target_include_directories(hash-lib PUBLIC headers)

# Linka eventuali librerie aggiuntive necessarie per hash-lib
target_link_libraries(hash-lib PRIVATE logging-lib)