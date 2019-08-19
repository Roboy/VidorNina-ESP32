cmake_minimum_required(VERSION 2.8.3)
project(visualitation)

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

SET(CMAKE_BUILD_TYPE Debug)

#==============================================================================
# Dependencies
#==============================================================================
include_directories(
        lib/
        include/
      )
#==============================================================================
# Application
#==============================================================================

FILE(GLOB SRC_FILES src/*.cpp)
FILE(GLOB INCLUDE_FILES lib/*.hpp)

add_executable( visualitation
        ${SRC_FILES}
        ${INCLUDE_FILES}
        )

target_link_libraries( visualitation -lpthread -lrt -lmosquitto -lconio)
