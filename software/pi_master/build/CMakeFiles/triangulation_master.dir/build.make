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
CMAKE_SOURCE_DIR = /home/sausy/Projects/VidorNina-ESP32/software/pi_master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sausy/Projects/VidorNina-ESP32/software/pi_master/build

# Include any dependencies generated for this target.
include CMakeFiles/triangulation_master.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/triangulation_master.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/triangulation_master.dir/flags.make

CMakeFiles/triangulation_master.dir/src/main.cpp.o: CMakeFiles/triangulation_master.dir/flags.make
CMakeFiles/triangulation_master.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sausy/Projects/VidorNina-ESP32/software/pi_master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/triangulation_master.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/triangulation_master.dir/src/main.cpp.o -c /home/sausy/Projects/VidorNina-ESP32/software/pi_master/src/main.cpp

CMakeFiles/triangulation_master.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/triangulation_master.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sausy/Projects/VidorNina-ESP32/software/pi_master/src/main.cpp > CMakeFiles/triangulation_master.dir/src/main.cpp.i

CMakeFiles/triangulation_master.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/triangulation_master.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sausy/Projects/VidorNina-ESP32/software/pi_master/src/main.cpp -o CMakeFiles/triangulation_master.dir/src/main.cpp.s

CMakeFiles/triangulation_master.dir/src/master_gen.cpp.o: CMakeFiles/triangulation_master.dir/flags.make
CMakeFiles/triangulation_master.dir/src/master_gen.cpp.o: ../src/master_gen.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sausy/Projects/VidorNina-ESP32/software/pi_master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/triangulation_master.dir/src/master_gen.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/triangulation_master.dir/src/master_gen.cpp.o -c /home/sausy/Projects/VidorNina-ESP32/software/pi_master/src/master_gen.cpp

CMakeFiles/triangulation_master.dir/src/master_gen.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/triangulation_master.dir/src/master_gen.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sausy/Projects/VidorNina-ESP32/software/pi_master/src/master_gen.cpp > CMakeFiles/triangulation_master.dir/src/master_gen.cpp.i

CMakeFiles/triangulation_master.dir/src/master_gen.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/triangulation_master.dir/src/master_gen.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sausy/Projects/VidorNina-ESP32/software/pi_master/src/master_gen.cpp -o CMakeFiles/triangulation_master.dir/src/master_gen.cpp.s

CMakeFiles/triangulation_master.dir/src/udp_data_rx.cpp.o: CMakeFiles/triangulation_master.dir/flags.make
CMakeFiles/triangulation_master.dir/src/udp_data_rx.cpp.o: ../src/udp_data_rx.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sausy/Projects/VidorNina-ESP32/software/pi_master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/triangulation_master.dir/src/udp_data_rx.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/triangulation_master.dir/src/udp_data_rx.cpp.o -c /home/sausy/Projects/VidorNina-ESP32/software/pi_master/src/udp_data_rx.cpp

CMakeFiles/triangulation_master.dir/src/udp_data_rx.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/triangulation_master.dir/src/udp_data_rx.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sausy/Projects/VidorNina-ESP32/software/pi_master/src/udp_data_rx.cpp > CMakeFiles/triangulation_master.dir/src/udp_data_rx.cpp.i

CMakeFiles/triangulation_master.dir/src/udp_data_rx.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/triangulation_master.dir/src/udp_data_rx.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sausy/Projects/VidorNina-ESP32/software/pi_master/src/udp_data_rx.cpp -o CMakeFiles/triangulation_master.dir/src/udp_data_rx.cpp.s

CMakeFiles/triangulation_master.dir/src/udp_data_tx.cpp.o: CMakeFiles/triangulation_master.dir/flags.make
CMakeFiles/triangulation_master.dir/src/udp_data_tx.cpp.o: ../src/udp_data_tx.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sausy/Projects/VidorNina-ESP32/software/pi_master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/triangulation_master.dir/src/udp_data_tx.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/triangulation_master.dir/src/udp_data_tx.cpp.o -c /home/sausy/Projects/VidorNina-ESP32/software/pi_master/src/udp_data_tx.cpp

CMakeFiles/triangulation_master.dir/src/udp_data_tx.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/triangulation_master.dir/src/udp_data_tx.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sausy/Projects/VidorNina-ESP32/software/pi_master/src/udp_data_tx.cpp > CMakeFiles/triangulation_master.dir/src/udp_data_tx.cpp.i

CMakeFiles/triangulation_master.dir/src/udp_data_tx.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/triangulation_master.dir/src/udp_data_tx.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sausy/Projects/VidorNina-ESP32/software/pi_master/src/udp_data_tx.cpp -o CMakeFiles/triangulation_master.dir/src/udp_data_tx.cpp.s

# Object files for target triangulation_master
triangulation_master_OBJECTS = \
"CMakeFiles/triangulation_master.dir/src/main.cpp.o" \
"CMakeFiles/triangulation_master.dir/src/master_gen.cpp.o" \
"CMakeFiles/triangulation_master.dir/src/udp_data_rx.cpp.o" \
"CMakeFiles/triangulation_master.dir/src/udp_data_tx.cpp.o"

# External object files for target triangulation_master
triangulation_master_EXTERNAL_OBJECTS =

triangulation_master: CMakeFiles/triangulation_master.dir/src/main.cpp.o
triangulation_master: CMakeFiles/triangulation_master.dir/src/master_gen.cpp.o
triangulation_master: CMakeFiles/triangulation_master.dir/src/udp_data_rx.cpp.o
triangulation_master: CMakeFiles/triangulation_master.dir/src/udp_data_tx.cpp.o
triangulation_master: CMakeFiles/triangulation_master.dir/build.make
triangulation_master: CMakeFiles/triangulation_master.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sausy/Projects/VidorNina-ESP32/software/pi_master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable triangulation_master"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/triangulation_master.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/triangulation_master.dir/build: triangulation_master

.PHONY : CMakeFiles/triangulation_master.dir/build

CMakeFiles/triangulation_master.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/triangulation_master.dir/cmake_clean.cmake
.PHONY : CMakeFiles/triangulation_master.dir/clean

CMakeFiles/triangulation_master.dir/depend:
	cd /home/sausy/Projects/VidorNina-ESP32/software/pi_master/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sausy/Projects/VidorNina-ESP32/software/pi_master /home/sausy/Projects/VidorNina-ESP32/software/pi_master /home/sausy/Projects/VidorNina-ESP32/software/pi_master/build /home/sausy/Projects/VidorNina-ESP32/software/pi_master/build /home/sausy/Projects/VidorNina-ESP32/software/pi_master/build/CMakeFiles/triangulation_master.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/triangulation_master.dir/depend

