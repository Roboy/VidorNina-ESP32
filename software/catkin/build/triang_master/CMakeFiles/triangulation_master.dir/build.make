# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sausy/Projects/VidorNina-ESP32/software/catkin/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sausy/Projects/VidorNina-ESP32/software/catkin/build

# Include any dependencies generated for this target.
include triang_master/CMakeFiles/triangulation_master.dir/depend.make

# Include the progress variables for this target.
include triang_master/CMakeFiles/triangulation_master.dir/progress.make

# Include the compile flags for this target's objects.
include triang_master/CMakeFiles/triangulation_master.dir/flags.make

triang_master/CMakeFiles/triangulation_master.dir/src/main.cpp.o: triang_master/CMakeFiles/triangulation_master.dir/flags.make
triang_master/CMakeFiles/triangulation_master.dir/src/main.cpp.o: /home/sausy/Projects/VidorNina-ESP32/software/catkin/src/triang_master/src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sausy/Projects/VidorNina-ESP32/software/catkin/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object triang_master/CMakeFiles/triangulation_master.dir/src/main.cpp.o"
	cd /home/sausy/Projects/VidorNina-ESP32/software/catkin/build/triang_master && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/triangulation_master.dir/src/main.cpp.o -c /home/sausy/Projects/VidorNina-ESP32/software/catkin/src/triang_master/src/main.cpp

triang_master/CMakeFiles/triangulation_master.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/triangulation_master.dir/src/main.cpp.i"
	cd /home/sausy/Projects/VidorNina-ESP32/software/catkin/build/triang_master && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sausy/Projects/VidorNina-ESP32/software/catkin/src/triang_master/src/main.cpp > CMakeFiles/triangulation_master.dir/src/main.cpp.i

triang_master/CMakeFiles/triangulation_master.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/triangulation_master.dir/src/main.cpp.s"
	cd /home/sausy/Projects/VidorNina-ESP32/software/catkin/build/triang_master && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sausy/Projects/VidorNina-ESP32/software/catkin/src/triang_master/src/main.cpp -o CMakeFiles/triangulation_master.dir/src/main.cpp.s

triang_master/CMakeFiles/triangulation_master.dir/src/master_gen.cpp.o: triang_master/CMakeFiles/triangulation_master.dir/flags.make
triang_master/CMakeFiles/triangulation_master.dir/src/master_gen.cpp.o: /home/sausy/Projects/VidorNina-ESP32/software/catkin/src/triang_master/src/master_gen.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sausy/Projects/VidorNina-ESP32/software/catkin/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object triang_master/CMakeFiles/triangulation_master.dir/src/master_gen.cpp.o"
	cd /home/sausy/Projects/VidorNina-ESP32/software/catkin/build/triang_master && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/triangulation_master.dir/src/master_gen.cpp.o -c /home/sausy/Projects/VidorNina-ESP32/software/catkin/src/triang_master/src/master_gen.cpp

triang_master/CMakeFiles/triangulation_master.dir/src/master_gen.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/triangulation_master.dir/src/master_gen.cpp.i"
	cd /home/sausy/Projects/VidorNina-ESP32/software/catkin/build/triang_master && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sausy/Projects/VidorNina-ESP32/software/catkin/src/triang_master/src/master_gen.cpp > CMakeFiles/triangulation_master.dir/src/master_gen.cpp.i

triang_master/CMakeFiles/triangulation_master.dir/src/master_gen.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/triangulation_master.dir/src/master_gen.cpp.s"
	cd /home/sausy/Projects/VidorNina-ESP32/software/catkin/build/triang_master && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sausy/Projects/VidorNina-ESP32/software/catkin/src/triang_master/src/master_gen.cpp -o CMakeFiles/triangulation_master.dir/src/master_gen.cpp.s

triang_master/CMakeFiles/triangulation_master.dir/src/rviz_interface.cpp.o: triang_master/CMakeFiles/triangulation_master.dir/flags.make
triang_master/CMakeFiles/triangulation_master.dir/src/rviz_interface.cpp.o: /home/sausy/Projects/VidorNina-ESP32/software/catkin/src/triang_master/src/rviz_interface.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sausy/Projects/VidorNina-ESP32/software/catkin/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object triang_master/CMakeFiles/triangulation_master.dir/src/rviz_interface.cpp.o"
	cd /home/sausy/Projects/VidorNina-ESP32/software/catkin/build/triang_master && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/triangulation_master.dir/src/rviz_interface.cpp.o -c /home/sausy/Projects/VidorNina-ESP32/software/catkin/src/triang_master/src/rviz_interface.cpp

triang_master/CMakeFiles/triangulation_master.dir/src/rviz_interface.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/triangulation_master.dir/src/rviz_interface.cpp.i"
	cd /home/sausy/Projects/VidorNina-ESP32/software/catkin/build/triang_master && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sausy/Projects/VidorNina-ESP32/software/catkin/src/triang_master/src/rviz_interface.cpp > CMakeFiles/triangulation_master.dir/src/rviz_interface.cpp.i

triang_master/CMakeFiles/triangulation_master.dir/src/rviz_interface.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/triangulation_master.dir/src/rviz_interface.cpp.s"
	cd /home/sausy/Projects/VidorNina-ESP32/software/catkin/build/triang_master && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sausy/Projects/VidorNina-ESP32/software/catkin/src/triang_master/src/rviz_interface.cpp -o CMakeFiles/triangulation_master.dir/src/rviz_interface.cpp.s

triang_master/CMakeFiles/triangulation_master.dir/src/udp_data_rx.cpp.o: triang_master/CMakeFiles/triangulation_master.dir/flags.make
triang_master/CMakeFiles/triangulation_master.dir/src/udp_data_rx.cpp.o: /home/sausy/Projects/VidorNina-ESP32/software/catkin/src/triang_master/src/udp_data_rx.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sausy/Projects/VidorNina-ESP32/software/catkin/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object triang_master/CMakeFiles/triangulation_master.dir/src/udp_data_rx.cpp.o"
	cd /home/sausy/Projects/VidorNina-ESP32/software/catkin/build/triang_master && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/triangulation_master.dir/src/udp_data_rx.cpp.o -c /home/sausy/Projects/VidorNina-ESP32/software/catkin/src/triang_master/src/udp_data_rx.cpp

triang_master/CMakeFiles/triangulation_master.dir/src/udp_data_rx.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/triangulation_master.dir/src/udp_data_rx.cpp.i"
	cd /home/sausy/Projects/VidorNina-ESP32/software/catkin/build/triang_master && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sausy/Projects/VidorNina-ESP32/software/catkin/src/triang_master/src/udp_data_rx.cpp > CMakeFiles/triangulation_master.dir/src/udp_data_rx.cpp.i

triang_master/CMakeFiles/triangulation_master.dir/src/udp_data_rx.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/triangulation_master.dir/src/udp_data_rx.cpp.s"
	cd /home/sausy/Projects/VidorNina-ESP32/software/catkin/build/triang_master && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sausy/Projects/VidorNina-ESP32/software/catkin/src/triang_master/src/udp_data_rx.cpp -o CMakeFiles/triangulation_master.dir/src/udp_data_rx.cpp.s

triang_master/CMakeFiles/triangulation_master.dir/src/udp_data_tx.cpp.o: triang_master/CMakeFiles/triangulation_master.dir/flags.make
triang_master/CMakeFiles/triangulation_master.dir/src/udp_data_tx.cpp.o: /home/sausy/Projects/VidorNina-ESP32/software/catkin/src/triang_master/src/udp_data_tx.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sausy/Projects/VidorNina-ESP32/software/catkin/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object triang_master/CMakeFiles/triangulation_master.dir/src/udp_data_tx.cpp.o"
	cd /home/sausy/Projects/VidorNina-ESP32/software/catkin/build/triang_master && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/triangulation_master.dir/src/udp_data_tx.cpp.o -c /home/sausy/Projects/VidorNina-ESP32/software/catkin/src/triang_master/src/udp_data_tx.cpp

triang_master/CMakeFiles/triangulation_master.dir/src/udp_data_tx.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/triangulation_master.dir/src/udp_data_tx.cpp.i"
	cd /home/sausy/Projects/VidorNina-ESP32/software/catkin/build/triang_master && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sausy/Projects/VidorNina-ESP32/software/catkin/src/triang_master/src/udp_data_tx.cpp > CMakeFiles/triangulation_master.dir/src/udp_data_tx.cpp.i

triang_master/CMakeFiles/triangulation_master.dir/src/udp_data_tx.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/triangulation_master.dir/src/udp_data_tx.cpp.s"
	cd /home/sausy/Projects/VidorNina-ESP32/software/catkin/build/triang_master && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sausy/Projects/VidorNina-ESP32/software/catkin/src/triang_master/src/udp_data_tx.cpp -o CMakeFiles/triangulation_master.dir/src/udp_data_tx.cpp.s

# Object files for target triangulation_master
triangulation_master_OBJECTS = \
"CMakeFiles/triangulation_master.dir/src/main.cpp.o" \
"CMakeFiles/triangulation_master.dir/src/master_gen.cpp.o" \
"CMakeFiles/triangulation_master.dir/src/rviz_interface.cpp.o" \
"CMakeFiles/triangulation_master.dir/src/udp_data_rx.cpp.o" \
"CMakeFiles/triangulation_master.dir/src/udp_data_tx.cpp.o"

# External object files for target triangulation_master
triangulation_master_EXTERNAL_OBJECTS =

/home/sausy/Projects/VidorNina-ESP32/software/catkin/devel/lib/triangulation_master/triangulation_master: triang_master/CMakeFiles/triangulation_master.dir/src/main.cpp.o
/home/sausy/Projects/VidorNina-ESP32/software/catkin/devel/lib/triangulation_master/triangulation_master: triang_master/CMakeFiles/triangulation_master.dir/src/master_gen.cpp.o
/home/sausy/Projects/VidorNina-ESP32/software/catkin/devel/lib/triangulation_master/triangulation_master: triang_master/CMakeFiles/triangulation_master.dir/src/rviz_interface.cpp.o
/home/sausy/Projects/VidorNina-ESP32/software/catkin/devel/lib/triangulation_master/triangulation_master: triang_master/CMakeFiles/triangulation_master.dir/src/udp_data_rx.cpp.o
/home/sausy/Projects/VidorNina-ESP32/software/catkin/devel/lib/triangulation_master/triangulation_master: triang_master/CMakeFiles/triangulation_master.dir/src/udp_data_tx.cpp.o
/home/sausy/Projects/VidorNina-ESP32/software/catkin/devel/lib/triangulation_master/triangulation_master: triang_master/CMakeFiles/triangulation_master.dir/build.make
/home/sausy/Projects/VidorNina-ESP32/software/catkin/devel/lib/triangulation_master/triangulation_master: /opt/ros/melodic/lib/libroscpp.so
/home/sausy/Projects/VidorNina-ESP32/software/catkin/devel/lib/triangulation_master/triangulation_master: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
/home/sausy/Projects/VidorNina-ESP32/software/catkin/devel/lib/triangulation_master/triangulation_master: /usr/lib/x86_64-linux-gnu/libboost_signals.so
/home/sausy/Projects/VidorNina-ESP32/software/catkin/devel/lib/triangulation_master/triangulation_master: /opt/ros/melodic/lib/librosconsole.so
/home/sausy/Projects/VidorNina-ESP32/software/catkin/devel/lib/triangulation_master/triangulation_master: /opt/ros/melodic/lib/librosconsole_log4cxx.so
/home/sausy/Projects/VidorNina-ESP32/software/catkin/devel/lib/triangulation_master/triangulation_master: /opt/ros/melodic/lib/librosconsole_backend_interface.so
/home/sausy/Projects/VidorNina-ESP32/software/catkin/devel/lib/triangulation_master/triangulation_master: /usr/lib/x86_64-linux-gnu/liblog4cxx.so
/home/sausy/Projects/VidorNina-ESP32/software/catkin/devel/lib/triangulation_master/triangulation_master: /usr/lib/x86_64-linux-gnu/libboost_regex.so
/home/sausy/Projects/VidorNina-ESP32/software/catkin/devel/lib/triangulation_master/triangulation_master: /opt/ros/melodic/lib/libxmlrpcpp.so
/home/sausy/Projects/VidorNina-ESP32/software/catkin/devel/lib/triangulation_master/triangulation_master: /opt/ros/melodic/lib/libroscpp_serialization.so
/home/sausy/Projects/VidorNina-ESP32/software/catkin/devel/lib/triangulation_master/triangulation_master: /opt/ros/melodic/lib/librostime.so
/home/sausy/Projects/VidorNina-ESP32/software/catkin/devel/lib/triangulation_master/triangulation_master: /opt/ros/melodic/lib/libcpp_common.so
/home/sausy/Projects/VidorNina-ESP32/software/catkin/devel/lib/triangulation_master/triangulation_master: /usr/lib/x86_64-linux-gnu/libboost_system.so
/home/sausy/Projects/VidorNina-ESP32/software/catkin/devel/lib/triangulation_master/triangulation_master: /usr/lib/x86_64-linux-gnu/libboost_thread.so
/home/sausy/Projects/VidorNina-ESP32/software/catkin/devel/lib/triangulation_master/triangulation_master: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
/home/sausy/Projects/VidorNina-ESP32/software/catkin/devel/lib/triangulation_master/triangulation_master: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
/home/sausy/Projects/VidorNina-ESP32/software/catkin/devel/lib/triangulation_master/triangulation_master: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
/home/sausy/Projects/VidorNina-ESP32/software/catkin/devel/lib/triangulation_master/triangulation_master: /usr/lib/x86_64-linux-gnu/libpthread.so
/home/sausy/Projects/VidorNina-ESP32/software/catkin/devel/lib/triangulation_master/triangulation_master: /usr/lib/x86_64-linux-gnu/libconsole_bridge.so.0.4
/home/sausy/Projects/VidorNina-ESP32/software/catkin/devel/lib/triangulation_master/triangulation_master: triang_master/CMakeFiles/triangulation_master.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sausy/Projects/VidorNina-ESP32/software/catkin/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable /home/sausy/Projects/VidorNina-ESP32/software/catkin/devel/lib/triangulation_master/triangulation_master"
	cd /home/sausy/Projects/VidorNina-ESP32/software/catkin/build/triang_master && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/triangulation_master.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
triang_master/CMakeFiles/triangulation_master.dir/build: /home/sausy/Projects/VidorNina-ESP32/software/catkin/devel/lib/triangulation_master/triangulation_master

.PHONY : triang_master/CMakeFiles/triangulation_master.dir/build

triang_master/CMakeFiles/triangulation_master.dir/clean:
	cd /home/sausy/Projects/VidorNina-ESP32/software/catkin/build/triang_master && $(CMAKE_COMMAND) -P CMakeFiles/triangulation_master.dir/cmake_clean.cmake
.PHONY : triang_master/CMakeFiles/triangulation_master.dir/clean

triang_master/CMakeFiles/triangulation_master.dir/depend:
	cd /home/sausy/Projects/VidorNina-ESP32/software/catkin/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sausy/Projects/VidorNina-ESP32/software/catkin/src /home/sausy/Projects/VidorNina-ESP32/software/catkin/src/triang_master /home/sausy/Projects/VidorNina-ESP32/software/catkin/build /home/sausy/Projects/VidorNina-ESP32/software/catkin/build/triang_master /home/sausy/Projects/VidorNina-ESP32/software/catkin/build/triang_master/CMakeFiles/triangulation_master.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : triang_master/CMakeFiles/triangulation_master.dir/depend
