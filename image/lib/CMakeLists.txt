include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

set(SRC_FILES ompfilters.cpp)
set(INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../include/ompfilters.hpp)

add_library(ompfilters SHARED ${SRC_FILES} ${INCLUDE_FILES})

find_package(OpenCV REQUIRED)
target_link_libraries(ompfilters ${OpenCV_LIBS})
