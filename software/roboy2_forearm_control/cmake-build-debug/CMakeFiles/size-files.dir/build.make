# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /opt/clion-2018.3.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion-2018.3.4/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/letrend/workspace/VidorNina-ESP32/software/roboy2_forearm_control

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/letrend/workspace/VidorNina-ESP32/software/roboy2_forearm_control/cmake-build-debug

# Utility rule file for size-files.

# Include the progress variables for this target.
include CMakeFiles/size-files.dir/progress.make

CMakeFiles/size-files:
	python /home/letrend/workspace/m3/esp/esp-idf/tools/idf_size.py --files m3_control.map

size-files: CMakeFiles/size-files
size-files: CMakeFiles/size-files.dir/build.make

.PHONY : size-files

# Rule to build all files generated by this target.
CMakeFiles/size-files.dir/build: size-files

.PHONY : CMakeFiles/size-files.dir/build

CMakeFiles/size-files.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/size-files.dir/cmake_clean.cmake
.PHONY : CMakeFiles/size-files.dir/clean

CMakeFiles/size-files.dir/depend:
	cd /home/letrend/workspace/VidorNina-ESP32/software/roboy2_forearm_control/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/letrend/workspace/VidorNina-ESP32/software/roboy2_forearm_control /home/letrend/workspace/VidorNina-ESP32/software/roboy2_forearm_control /home/letrend/workspace/VidorNina-ESP32/software/roboy2_forearm_control/cmake-build-debug /home/letrend/workspace/VidorNina-ESP32/software/roboy2_forearm_control/cmake-build-debug /home/letrend/workspace/VidorNina-ESP32/software/roboy2_forearm_control/cmake-build-debug/CMakeFiles/size-files.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/size-files.dir/depend

