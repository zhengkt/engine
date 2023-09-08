
cmake_minimum_required(VERSION 2.9)
project(engine)
if(WIN32)
	SET(BUILD_PROJECT_NAME "engine")
elseif(UNIX)
	SET(BUILD_PROJECT_NAME "engine")
endif()

message(STATUS "cmake ${BUILD_PROJECT_NAME} start")

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/tools/cmake)

include(UseLemon)

SET(INC_LIST
  ${CMAKE_CURRENT_SOURCE_DIR}/match-engine.h
)

SET(SRC_LIST
   ${CMAKE_CURRENT_SOURCE_DIR}/match-engine.c
)

ADD_DEFINITIONS(
  # -DHAVE_EPOLL
)

ADD_LIBRARY(${BUILD_PROJECT_NAME} SHARED ${SRC_LIST} ${INC_LIST})

TARGET_LINK_LIBRARIES(${BUILD_PROJECT_NAME}
  glib-2.0
)

# file(GLOB ruleunitEtcFiles "${CMAKE_CURRENT_SOURCE_DIR}/etc/*")
# ADD_CUSTOM_COMMAND(OUTPUT ruleunitcpfile #不会生成ruleunitcpfile文件，因为执行的commond 不是生成文件的命令哈
# #但是必须使用OUTPUT、或则TARGET，改成copy_ruleunit_etc_files 更容易理解
#   COMMAND mkdir -p ${OUTPUT_HOME}/etc/sdx/
#   COMMAND cp -f ${ruleunitEtcFiles} ${OUTPUT_HOME}/etc/sdx/
#   COMMAND echo "Build cpfileTarget success."
# )
# ADD_CUSTOM_TARGET(ruleunitcpfileTarget ALL DEPENDS ruleunitcpfile) #ALL 表示默认构建
# ADD_DEPENDENCIES(ruleunitcpfileTarget ${BUILD_PROJECT_NAME}) #先生成BUILD_PROJECT_NAME 在生成ruleunitcpfileTarget

add_subdirectory(tools/lemon)
