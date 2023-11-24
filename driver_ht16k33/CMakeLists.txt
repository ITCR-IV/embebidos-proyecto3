cmake_minimum_required (VERSION 3.5)
# define the project
project (libht16k33)

add_compile_options(-Wall -Wextra -Werror -pedantic)

add_subdirectory (lib)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/lib)
add_executable (prueba_matriz test/prueba_matriz.c)

target_link_libraries(prueba_matriz ht16k33)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "/usr" CACHE PATH "..." FORCE)
endif()

install (TARGETS prueba_matriz DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS ht16k33 LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES include/ht16k33.h TYPE INCLUDE)
