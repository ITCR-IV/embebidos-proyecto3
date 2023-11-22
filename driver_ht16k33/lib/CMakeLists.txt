#add include to directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)
#set the proper macros
set(LIBRARY_NAME ht16k33)
set(SRC_FILES ht16k33.c)
set(INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../include/ht16k33.h)
#add the library
add_library(${LIBRARY_NAME} SHARED ${SRC_FILES} ${INCLUDE_FILES})
#installing the library
install (TARGETS ${LIBRARY_NAME} DESTINATION lib)
install (FILES ${INCLUDE_FILES} DESTINATION include)
