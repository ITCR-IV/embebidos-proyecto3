# CMakeLists.txt

cmake_minimum_required(VERSION 3.5)
project(ImageServer)

set(SOURCES
		src/main.c
		src/parse.c
		src/connection_handler.cpp
)

set(HEADERS
		include/connection_handler.h
		include/process_image.h
		include/util.h
		include/parse.h
)

add_executable(ImageServer ${SOURCES} ${HEADERS})

find_package(OpenCV REQUIRED)
target_link_libraries(ImageServer microhttpd ${OpenCV_LIBS})
target_include_directories(ImageServer PRIVATE include)

include(GNUInstallDirs)

install(TARGETS ImageServer DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES default_config.conf DESTINATION ${CMAKE_INSTALL_SYSCONFDIR}/ImageServer/config.conf)
install(FILES ImageServer.service DESTINATION ${CMAKE_INSTALL_SYSCONFDIR}/systemd/system)
