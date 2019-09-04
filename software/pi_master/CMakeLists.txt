cmake_minimum_required(VERSION 2.8.3)
project(triangulation_master)

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

SET(CMAKE_BUILD_TYPE Debug)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  visualization_msgs
)

catkin_package(
#  INCLUDE_DIRS include
  LIBRARIES using_markers
  CATKIN_DEPENDS roscpp visualization_msgs
#  DEPENDS system_lib
)



#==============================================================================
# Dependencies
#==============================================================================
include_directories(
        lib/
        include/
        ${catkin_INCLUDE_DIRS}
      )
#==============================================================================
# Application
#==============================================================================

FILE(GLOB SRC_FILES src/*.cpp)
FILE(GLOB INCLUDE_FILES lib/*.hpp)

add_executable( triangulation_master
        ${SRC_FILES}
        ${INCLUDE_FILES}
        )

target_link_libraries( triangulation_master -lpthread -lrt -lmosquitto -lncurses basic_shapes ${catkin_LIBRARIES})
