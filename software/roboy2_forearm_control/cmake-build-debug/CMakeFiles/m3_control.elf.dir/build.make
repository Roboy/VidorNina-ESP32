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
include CMakeFiles/m3_control.elf.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/m3_control.elf.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/m3_control.elf.dir/flags.make

CMakeFiles/m3_control.elf.dir/src/main.c.obj: CMakeFiles/m3_control.elf.dir/flags.make
CMakeFiles/m3_control.elf.dir/src/main.c.obj: ../src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/letrend/workspace/VidorNina-ESP32/software/roboy2_forearm_control/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/m3_control.elf.dir/src/main.c.obj"
	/home/letrend/workspace/m3/esp/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/m3_control.elf.dir/src/main.c.obj   -c /home/letrend/workspace/VidorNina-ESP32/software/roboy2_forearm_control/src/main.c

CMakeFiles/m3_control.elf.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/m3_control.elf.dir/src/main.c.i"
	/home/letrend/workspace/m3/esp/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/letrend/workspace/VidorNina-ESP32/software/roboy2_forearm_control/src/main.c > CMakeFiles/m3_control.elf.dir/src/main.c.i

CMakeFiles/m3_control.elf.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/m3_control.elf.dir/src/main.c.s"
	/home/letrend/workspace/m3/esp/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/letrend/workspace/VidorNina-ESP32/software/roboy2_forearm_control/src/main.c -o CMakeFiles/m3_control.elf.dir/src/main.c.s

# Object files for target m3_control.elf
m3_control_elf_OBJECTS = \
"CMakeFiles/m3_control.elf.dir/src/main.c.obj"

# External object files for target m3_control.elf
m3_control_elf_EXTERNAL_OBJECTS =

m3_control.elf: CMakeFiles/m3_control.elf.dir/src/main.c.obj
m3_control.elf: CMakeFiles/m3_control.elf.dir/build.make
m3_control.elf: esp-idf/soc/libsoc.a
m3_control.elf: esp-idf/xtensa/libxtensa.a
m3_control.elf: esp-idf/esp_common/libesp_common.a
m3_control.elf: esp-idf/esp_rom/libesp_rom.a
m3_control.elf: esp-idf/log/liblog.a
m3_control.elf: esp-idf/heap/libheap.a
m3_control.elf: esp-idf/freertos/libfreertos.a
m3_control.elf: esp-idf/vfs/libvfs.a
m3_control.elf: esp-idf/newlib/libnewlib.a
m3_control.elf: esp-idf/esp_ringbuf/libesp_ringbuf.a
m3_control.elf: esp-idf/driver/libdriver.a
m3_control.elf: esp-idf/mbedtls/libmbedtls.a
m3_control.elf: esp-idf/wpa_supplicant/libwpa_supplicant.a
m3_control.elf: esp-idf/efuse/libefuse.a
m3_control.elf: esp-idf/bootloader_support/libbootloader_support.a
m3_control.elf: esp-idf/app_update/libapp_update.a
m3_control.elf: esp-idf/spi_flash/libspi_flash.a
m3_control.elf: esp-idf/nvs_flash/libnvs_flash.a
m3_control.elf: esp-idf/esp_wifi/libesp_wifi.a
m3_control.elf: esp-idf/ethernet/libethernet.a
m3_control.elf: esp-idf/lwip/liblwip.a
m3_control.elf: esp-idf/tcpip_adapter/libtcpip_adapter.a
m3_control.elf: esp-idf/esp_event/libesp_event.a
m3_control.elf: esp-idf/pthread/libpthread.a
m3_control.elf: esp-idf/smartconfig_ack/libsmartconfig_ack.a
m3_control.elf: esp-idf/espcoredump/libespcoredump.a
m3_control.elf: esp-idf/esp32/libesp32.a
m3_control.elf: esp-idf/cxx/libcxx.a
m3_control.elf: esp-idf/app_trace/libapp_trace.a
m3_control.elf: esp-idf/asio/libasio.a
m3_control.elf: esp-idf/coap/libcoap.a
m3_control.elf: esp-idf/console/libconsole.a
m3_control.elf: esp-idf/nghttp/libnghttp.a
m3_control.elf: esp-idf/esp-tls/libesp-tls.a
m3_control.elf: esp-idf/esp_adc_cal/libesp_adc_cal.a
m3_control.elf: esp-idf/tcp_transport/libtcp_transport.a
m3_control.elf: esp-idf/esp_http_client/libesp_http_client.a
m3_control.elf: esp-idf/esp_http_server/libesp_http_server.a
m3_control.elf: esp-idf/esp_https_ota/libesp_https_ota.a
m3_control.elf: esp-idf/openssl/libopenssl.a
m3_control.elf: esp-idf/esp_https_server/libesp_https_server.a
m3_control.elf: esp-idf/expat/libexpat.a
m3_control.elf: esp-idf/wear_levelling/libwear_levelling.a
m3_control.elf: esp-idf/sdmmc/libsdmmc.a
m3_control.elf: esp-idf/fatfs/libfatfs.a
m3_control.elf: esp-idf/freemodbus/libfreemodbus.a
m3_control.elf: esp-idf/jsmn/libjsmn.a
m3_control.elf: esp-idf/json/libjson.a
m3_control.elf: esp-idf/libsodium/liblibsodium.a
m3_control.elf: esp-idf/mdns/libmdns.a
m3_control.elf: esp-idf/mqtt/libmqtt.a
m3_control.elf: esp-idf/protobuf-c/libprotobuf-c.a
m3_control.elf: esp-idf/protocomm/libprotocomm.a
m3_control.elf: esp-idf/spiffs/libspiffs.a
m3_control.elf: esp-idf/ulp/libulp.a
m3_control.elf: esp-idf/unity/libunity.a
m3_control.elf: esp-idf/wifi_provisioning/libwifi_provisioning.a
m3_control.elf: esp-idf/mbedtls/mbedtls/library/libmbedtls.a
m3_control.elf: esp-idf/mbedtls/mbedtls/library/libmbedx509.a
m3_control.elf: esp-idf/mbedtls/mbedtls/library/libmbedcrypto.a
m3_control.elf: esp-idf/soc/libsoc.a
m3_control.elf: esp-idf/xtensa/libxtensa.a
m3_control.elf: /home/letrend/workspace/m3/esp/esp-idf/components/xtensa/esp32/libhal.a
m3_control.elf: esp-idf/esp_common/libesp_common.a
m3_control.elf: esp-idf/esp_rom/libesp_rom.a
m3_control.elf: esp-idf/log/liblog.a
m3_control.elf: esp-idf/heap/libheap.a
m3_control.elf: esp-idf/freertos/libfreertos.a
m3_control.elf: esp-idf/newlib/libnewlib.a
m3_control.elf: esp-idf/esp32/libesp32.a
m3_control.elf: esp-idf/cxx/libcxx.a
m3_control.elf: esp-idf/esp32/esp32.project.ld
m3_control.elf: /home/letrend/workspace/m3/esp/esp-idf/components/esp_rom/esp32/ld/esp32.rom.ld
m3_control.elf: /home/letrend/workspace/m3/esp/esp-idf/components/esp_rom/esp32/ld/esp32.rom.libgcc.ld
m3_control.elf: /home/letrend/workspace/m3/esp/esp-idf/components/esp_rom/esp32/ld/esp32.rom.syscalls.ld
m3_control.elf: /home/letrend/workspace/m3/esp/esp-idf/components/esp_rom/esp32/ld/esp32.rom.newlib-data.ld
m3_control.elf: /home/letrend/workspace/m3/esp/esp-idf/components/esp_rom/esp32/ld/esp32.rom.newlib-funcs.ld
m3_control.elf: /home/letrend/workspace/m3/esp/esp-idf/components/esp_rom/esp32/ld/esp32.rom.newlib-locale.ld
m3_control.elf: esp-idf/esp32/esp32_out.ld
m3_control.elf: /home/letrend/workspace/m3/esp/esp-idf/components/esp32/ld/esp32.peripherals.ld
m3_control.elf: CMakeFiles/m3_control.elf.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/letrend/workspace/VidorNina-ESP32/software/roboy2_forearm_control/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable m3_control.elf"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/m3_control.elf.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/m3_control.elf.dir/build: m3_control.elf

.PHONY : CMakeFiles/m3_control.elf.dir/build

CMakeFiles/m3_control.elf.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/m3_control.elf.dir/cmake_clean.cmake
.PHONY : CMakeFiles/m3_control.elf.dir/clean

CMakeFiles/m3_control.elf.dir/depend:
	cd /home/letrend/workspace/VidorNina-ESP32/software/roboy2_forearm_control/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/letrend/workspace/VidorNina-ESP32/software/roboy2_forearm_control /home/letrend/workspace/VidorNina-ESP32/software/roboy2_forearm_control /home/letrend/workspace/VidorNina-ESP32/software/roboy2_forearm_control/cmake-build-debug /home/letrend/workspace/VidorNina-ESP32/software/roboy2_forearm_control/cmake-build-debug /home/letrend/workspace/VidorNina-ESP32/software/roboy2_forearm_control/cmake-build-debug/CMakeFiles/m3_control.elf.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/m3_control.elf.dir/depend

