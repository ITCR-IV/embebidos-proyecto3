cmake_minimum_required (VERSION 3.5)
# define the project
project (ompfilters)

add_compile_options(-fopenmp -Wall -Wextra -Werror)


add_subdirectory (lib)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/lib)

add_executable (prueba_filtros src/main.cpp)

find_package(OpenCV REQUIRED)
target_link_libraries(prueba_filtros ompfilters ${OpenCV_LIBS})

include(GNUInstallDirs)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "/usr" CACHE PATH "..." FORCE)
endif()

install (TARGETS prueba_filtros DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS ompfilters LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES include/ompfilters.hpp TYPE INCLUDE)
