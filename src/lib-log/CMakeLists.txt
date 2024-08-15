# CMakeLists.txt per la libreria lib-log

# Aggiungi i file sorgenti
file(GLOB LIB_LOG_SOURCES "src/*.cc")

# Crea la libreria logging-lib
add_library(logging-lib ${LIB_LOG_SOURCES})

# Includi la directory degli headers
target_include_directories(logging-lib PUBLIC headers)

# Linka eventuali librerie necessarie (in questo caso, Boost)
target_link_libraries(logging-lib PRIVATE boost::boost)
