# Bring in the headers and sources
include_directories(../include)
file(GLOB SOURCES "*.c")

# Generate the shared library from the sources
add_library(utilc-file SHARED ${SOURCES})

# Install system-wide
install(TARGETS utilc-file DESTINATION /usr/lib)
