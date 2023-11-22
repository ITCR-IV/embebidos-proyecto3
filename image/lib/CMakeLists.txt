include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

set(LIBRARY_NAME ompfilters)
set(SRC_FILES ompfilters.cpp)
set(INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../include/ompfilters.hpp)

add_library(${LIBRARY_NAME} SHARED ${SRC_FILES} ${INCLUDE_FILES})

find_package(OpenCV REQUIRED)
target_link_libraries(${LIBRARY_NAME} ${OpenCV_LIBS})
