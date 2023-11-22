cmake_minimum_required (VERSION 2.6)
#define the project
project (libht16k33)
#add lib subdirectory to build
add_subdirectory (lib)
#include directories to building path
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/lib)
# add the executable
add_executable (prueba_matriz test/prueba_matriz.c)
#link against required libraries
target_link_libraries(prueba_matriz ht16k33)
#install the binary
install (TARGETS prueba_matriz DESTINATION bin)
