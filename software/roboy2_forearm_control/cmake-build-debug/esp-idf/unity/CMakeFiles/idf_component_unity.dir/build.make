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

# Include any dependencies generated for this target.
include esp-idf/unity/CMakeFiles/idf_component_unity.dir/depend.make

# Include the progress variables for this target.
include esp-idf/unity/CMakeFiles/idf_component_unity.dir/progress.make

# Include the compile flags for this target's objects.
include esp-idf/unity/CMakeFiles/idf_component_unity.dir/flags.make

esp-idf/unity/CMakeFiles/idf_component_unity.dir/unity/src/unity.c.obj: esp-idf/unity/CMakeFiles/idf_component_unity.dir/flags.make
esp-idf/unity/CMakeFiles/idf_component_unity.dir/unity/src/unity.c.obj: /home/letrend/workspace/m3/esp/esp-idf/components/unity/unity/src/unity.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/letrend/workspace/VidorNina-ESP32/software/roboy2_forearm_control/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object esp-idf/unity/CMakeFiles/idf_component_unity.dir/unity/src/unity.c.obj"
	cd /home/letrend/workspace/VidorNina-ESP32/software/roboy2_forearm_control/cmake-build-debug/esp-idf/unity && /home/letrend/workspace/m3/esp/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/idf_component_unity.dir/unity/src/unity.c.obj   -c /home/letrend/workspace/m3/esp/esp-idf/components/unity/unity/src/unity.c

esp-idf/unity/CMakeFiles/idf_component_unity.dir/unity/src/unity.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/idf_component_unity.dir/unity/src/unity.c.i"
	cd /home/letrend/workspace/VidorNina-ESP32/software/roboy2_forearm_control/cmake-build-debug/esp-idf/unity && /home/letrend/workspace/m3/esp/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/letrend/workspace/m3/esp/esp-idf/components/unity/unity/src/unity.c > CMakeFiles/idf_component_unity.dir/unity/src/unity.c.i

esp-idf/unity/CMakeFiles/idf_component_unity.dir/unity/src/unity.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/idf_component_unity.dir/unity/src/unity.c.s"
	cd /home/letrend/workspace/VidorNina-ESP32/software/roboy2_forearm_control/cmake-build-debug/esp-idf/unity && /home/letrend/workspace/m3/esp/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/letrend/workspace/m3/esp/esp-idf/components/unity/unity/src/unity.c -o CMakeFiles/idf_component_unity.dir/unity/src/unity.c.s

esp-idf/unity/CMakeFiles/idf_component_unity.dir/unity_port_esp32.c.obj: esp-idf/unity/CMakeFiles/idf_component_unity.dir/flags.make
esp-idf/unity/CMakeFiles/idf_component_unity.dir/unity_port_esp32.c.obj: /home/letrend/workspace/m3/esp/esp-idf/components/unity/unity_port_esp32.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/letrend/workspace/VidorNina-ESP32/software/roboy2_forearm_control/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object esp-idf/unity/CMakeFiles/idf_component_unity.dir/unity_port_esp32.c.obj"
	cd /home/letrend/workspace/VidorNina-ESP32/software/roboy2_forearm_control/cmake-build-debug/esp-idf/unity && /home/letrend/workspace/m3/esp/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/idf_component_unity.dir/unity_port_esp32.c.obj   -c /home/letrend/workspace/m3/esp/esp-idf/components/unity/unity_port_esp32.c

esp-idf/unity/CMakeFiles/idf_component_unity.dir/unity_port_esp32.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/idf_component_unity.dir/unity_port_esp32.c.i"
	cd /home/letrend/workspace/VidorNina-ESP32/software/roboy2_forearm_control/cmake-build-debug/esp-idf/unity && /home/letrend/workspace/m3/esp/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/letrend/workspace/m3/esp/esp-idf/components/unity/unity_port_esp32.c > CMakeFiles/idf_component_unity.dir/unity_port_esp32.c.i

esp-idf/unity/CMakeFiles/idf_component_unity.dir/unity_port_esp32.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/idf_component_unity.dir/unity_port_esp32.c.s"
	cd /home/letrend/workspace/VidorNina-ESP32/software/roboy2_forearm_control/cmake-build-debug/esp-idf/unity && /home/letrend/workspace/m3/esp/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/letrend/workspace/m3/esp/esp-idf/components/unity/unity_port_esp32.c -o CMakeFiles/idf_component_unity.dir/unity_port_esp32.c.s

esp-idf/unity/CMakeFiles/idf_component_unity.dir/unity_runner.c.obj: esp-idf/unity/CMakeFiles/idf_component_unity.dir/flags.make
esp-idf/unity/CMakeFiles/idf_component_unity.dir/unity_runner.c.obj: /home/letrend/workspace/m3/esp/esp-idf/components/unity/unity_runner.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/letrend/workspace/VidorNina-ESP32/software/roboy2_forearm_control/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object esp-idf/unity/CMakeFiles/idf_component_unity.dir/unity_runner.c.obj"
	cd /home/letrend/workspace/VidorNina-ESP32/software/roboy2_forearm_control/cmake-build-debug/esp-idf/unity && /home/letrend/workspace/m3/esp/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/idf_component_unity.dir/unity_runner.c.obj   -c /home/letrend/workspace/m3/esp/esp-idf/components/unity/unity_runner.c

esp-idf/unity/CMakeFiles/idf_component_unity.dir/unity_runner.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/idf_component_unity.dir/unity_runner.c.i"
	cd /home/letrend/workspace/VidorNina-ESP32/software/roboy2_forearm_control/cmake-build-debug/esp-idf/unity && /home/letrend/workspace/m3/esp/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/letrend/workspace/m3/esp/esp-idf/components/unity/unity_runner.c > CMakeFiles/idf_component_unity.dir/unity_runner.c.i

esp-idf/unity/CMakeFiles/idf_component_unity.dir/unity_runner.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/idf_component_unity.dir/unity_runner.c.s"
	cd /home/letrend/workspace/VidorNina-ESP32/software/roboy2_forearm_control/cmake-build-debug/esp-idf/unity && /home/letrend/workspace/m3/esp/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/letrend/workspace/m3/esp/esp-idf/components/unity/unity_runner.c -o CMakeFiles/idf_component_unity.dir/unity_runner.c.s

# Object files for target idf_component_unity
idf_component_unity_OBJECTS = \
"CMakeFiles/idf_component_unity.dir/unity/src/unity.c.obj" \
"CMakeFiles/idf_component_unity.dir/unity_port_esp32.c.obj" \
"CMakeFiles/idf_component_unity.dir/unity_runner.c.obj"

# External object files for target idf_component_unity
idf_component_unity_EXTERNAL_OBJECTS =

esp-idf/unity/libunity.a: esp-idf/unity/CMakeFiles/idf_component_unity.dir/unity/src/unity.c.obj
esp-idf/unity/libunity.a: esp-idf/unity/CMakeFiles/idf_component_unity.dir/unity_port_esp32.c.obj
esp-idf/unity/libunity.a: esp-idf/unity/CMakeFiles/idf_component_unity.dir/unity_runner.c.obj
esp-idf/unity/libunity.a: esp-idf/unity/CMakeFiles/idf_component_unity.dir/build.make
esp-idf/unity/libunity.a: esp-idf/unity/CMakeFiles/idf_component_unity.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/letrend/workspace/VidorNina-ESP32/software/roboy2_forearm_control/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C static library libunity.a"
	cd /home/letrend/workspace/VidorNina-ESP32/software/roboy2_forearm_control/cmake-build-debug/esp-idf/unity && $(CMAKE_COMMAND) -P CMakeFiles/idf_component_unity.dir/cmake_clean_target.cmake
	cd /home/letrend/workspace/VidorNina-ESP32/software/roboy2_forearm_control/cmake-build-debug/esp-idf/unity && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/idf_component_unity.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
esp-idf/unity/CMakeFiles/idf_component_unity.dir/build: esp-idf/unity/libunity.a

.PHONY : esp-idf/unity/CMakeFiles/idf_component_unity.dir/build

esp-idf/unity/CMakeFiles/idf_component_unity.dir/clean:
	cd /home/letrend/workspace/VidorNina-ESP32/software/roboy2_forearm_control/cmake-build-debug/esp-idf/unity && $(CMAKE_COMMAND) -P CMakeFiles/idf_component_unity.dir/cmake_clean.cmake
.PHONY : esp-idf/unity/CMakeFiles/idf_component_unity.dir/clean

esp-idf/unity/CMakeFiles/idf_component_unity.dir/depend:
	cd /home/letrend/workspace/VidorNina-ESP32/software/roboy2_forearm_control/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/letrend/workspace/VidorNina-ESP32/software/roboy2_forearm_control /home/letrend/workspace/m3/esp/esp-idf/components/unity /home/letrend/workspace/VidorNina-ESP32/software/roboy2_forearm_control/cmake-build-debug /home/letrend/workspace/VidorNina-ESP32/software/roboy2_forearm_control/cmake-build-debug/esp-idf/unity /home/letrend/workspace/VidorNina-ESP32/software/roboy2_forearm_control/cmake-build-debug/esp-idf/unity/CMakeFiles/idf_component_unity.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : esp-idf/unity/CMakeFiles/idf_component_unity.dir/depend

