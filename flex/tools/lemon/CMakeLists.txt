cmake_minimum_required(VERSION 2.9)

if(WIN32)
	SET(BUILD_PROJECT_NAME "lemon")
elseif(UNIX)
	SET(BUILD_PROJECT_NAME "lemon")
endif()

SET(SRC_LIST
  ${CMAKE_CURRENT_SOURCE_DIR}/lemon.c
)

ADD_DEFINITIONS(
  -D_GNU_SOURCE
)

ADD_EXECUTABLE(${BUILD_PROJECT_NAME} ${SRC_LIST})
