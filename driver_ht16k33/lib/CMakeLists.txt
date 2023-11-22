include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

set(SRC_FILES ht16k33.c)
set(INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../include/ht16k33.h)

add_library(ht16k33 SHARED ${SRC_FILES} ${INCLUDE_FILES})
