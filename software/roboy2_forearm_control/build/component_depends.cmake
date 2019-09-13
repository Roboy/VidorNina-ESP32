# Component requirements generated by expand_requirements.cmake

set(BUILD_COMPONENTS soc;xtensa;esp_common;esp_rom;log;heap;freertos;vfs;newlib;esp_ringbuf;driver;mbedtls;wpa_supplicant;efuse;bootloader_support;partition_table;app_update;spi_flash;nvs_flash;esp_wifi;ethernet;lwip;tcpip_adapter;esp_event;pthread;smartconfig_ack;espcoredump;esp32;cxx;app_trace;asio;bootloader;bt;coap;console;nghttp;esp-tls;esp_adc_cal;tcp_transport;esp_http_client;esp_http_server;esp_https_ota;openssl;esp_https_server;esptool_py;expat;wear_levelling;sdmmc;fatfs;freemodbus;idf_test;jsmn;json;libsodium;mdns;mqtt;protobuf-c;protocomm;spiffs;ulp;unity;wifi_provisioning)
set(BUILD_COMPONENT_PATHS /home/letrend/workspace/m3/esp/esp-idf/components/soc;/home/letrend/workspace/m3/esp/esp-idf/components/xtensa;/home/letrend/workspace/m3/esp/esp-idf/components/esp_common;/home/letrend/workspace/m3/esp/esp-idf/components/esp_rom;/home/letrend/workspace/m3/esp/esp-idf/components/log;/home/letrend/workspace/m3/esp/esp-idf/components/heap;/home/letrend/workspace/m3/esp/esp-idf/components/freertos;/home/letrend/workspace/m3/esp/esp-idf/components/vfs;/home/letrend/workspace/m3/esp/esp-idf/components/newlib;/home/letrend/workspace/m3/esp/esp-idf/components/esp_ringbuf;/home/letrend/workspace/m3/esp/esp-idf/components/driver;/home/letrend/workspace/m3/esp/esp-idf/components/mbedtls;/home/letrend/workspace/m3/esp/esp-idf/components/wpa_supplicant;/home/letrend/workspace/m3/esp/esp-idf/components/efuse;/home/letrend/workspace/m3/esp/esp-idf/components/bootloader_support;/home/letrend/workspace/m3/esp/esp-idf/components/partition_table;/home/letrend/workspace/m3/esp/esp-idf/components/app_update;/home/letrend/workspace/m3/esp/esp-idf/components/spi_flash;/home/letrend/workspace/m3/esp/esp-idf/components/nvs_flash;/home/letrend/workspace/m3/esp/esp-idf/components/esp_wifi;/home/letrend/workspace/m3/esp/esp-idf/components/ethernet;/home/letrend/workspace/m3/esp/esp-idf/components/lwip;/home/letrend/workspace/m3/esp/esp-idf/components/tcpip_adapter;/home/letrend/workspace/m3/esp/esp-idf/components/esp_event;/home/letrend/workspace/m3/esp/esp-idf/components/pthread;/home/letrend/workspace/m3/esp/esp-idf/components/smartconfig_ack;/home/letrend/workspace/m3/esp/esp-idf/components/espcoredump;/home/letrend/workspace/m3/esp/esp-idf/components/esp32;/home/letrend/workspace/m3/esp/esp-idf/components/cxx;/home/letrend/workspace/m3/esp/esp-idf/components/app_trace;/home/letrend/workspace/m3/esp/esp-idf/components/asio;/home/letrend/workspace/m3/esp/esp-idf/components/bootloader;/home/letrend/workspace/m3/esp/esp-idf/components/bt;/home/letrend/workspace/m3/esp/esp-idf/components/coap;/home/letrend/workspace/m3/esp/esp-idf/components/console;/home/letrend/workspace/m3/esp/esp-idf/components/nghttp;/home/letrend/workspace/m3/esp/esp-idf/components/esp-tls;/home/letrend/workspace/m3/esp/esp-idf/components/esp_adc_cal;/home/letrend/workspace/m3/esp/esp-idf/components/tcp_transport;/home/letrend/workspace/m3/esp/esp-idf/components/esp_http_client;/home/letrend/workspace/m3/esp/esp-idf/components/esp_http_server;/home/letrend/workspace/m3/esp/esp-idf/components/esp_https_ota;/home/letrend/workspace/m3/esp/esp-idf/components/openssl;/home/letrend/workspace/m3/esp/esp-idf/components/esp_https_server;/home/letrend/workspace/m3/esp/esp-idf/components/esptool_py;/home/letrend/workspace/m3/esp/esp-idf/components/expat;/home/letrend/workspace/m3/esp/esp-idf/components/wear_levelling;/home/letrend/workspace/m3/esp/esp-idf/components/sdmmc;/home/letrend/workspace/m3/esp/esp-idf/components/fatfs;/home/letrend/workspace/m3/esp/esp-idf/components/freemodbus;/home/letrend/workspace/m3/esp/esp-idf/components/idf_test;/home/letrend/workspace/m3/esp/esp-idf/components/jsmn;/home/letrend/workspace/m3/esp/esp-idf/components/json;/home/letrend/workspace/m3/esp/esp-idf/components/libsodium;/home/letrend/workspace/m3/esp/esp-idf/components/mdns;/home/letrend/workspace/m3/esp/esp-idf/components/mqtt;/home/letrend/workspace/m3/esp/esp-idf/components/protobuf-c;/home/letrend/workspace/m3/esp/esp-idf/components/protocomm;/home/letrend/workspace/m3/esp/esp-idf/components/spiffs;/home/letrend/workspace/m3/esp/esp-idf/components/ulp;/home/letrend/workspace/m3/esp/esp-idf/components/unity;/home/letrend/workspace/m3/esp/esp-idf/components/wifi_provisioning)
set(BUILD_TEST_COMPONENTS )
set(BUILD_TEST_COMPONENT_PATHS )

# get_component_requirements: Generated function to read the dependencies of a given component.
#
# Parameters:
# - component: Name of component
# - var_requires: output variable name. Set to recursively expanded COMPONENT_REQUIRES 
#   for this component.
# - var_private_requires: output variable name. Set to recursively expanded COMPONENT_PRIV_REQUIRES 
#   for this component.
#
# Throws a fatal error if 'componeont' is not found (indicates a build system problem).
#
function(get_component_requirements component var_requires var_private_requires)
  if("${component}" STREQUAL "soc")
    set(${var_requires} "" PARENT_SCOPE)
    set(${var_private_requires} "" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "xtensa")
    set(${var_requires} "" PARENT_SCOPE)
    set(${var_private_requires} "soc" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "esp_common")
    set(${var_requires} "" PARENT_SCOPE)
    set(${var_private_requires} "soc" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "esp_rom")
    set(${var_requires} "" PARENT_SCOPE)
    set(${var_private_requires} "" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "log")
    set(${var_requires} "" PARENT_SCOPE)
    set(${var_private_requires} "soc" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "heap")
    set(${var_requires} "" PARENT_SCOPE)
    set(${var_private_requires} "soc" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "freertos")
    set(${var_requires} "app_trace" PARENT_SCOPE)
    set(${var_private_requires} "esp_common;soc" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "vfs")
    set(${var_requires} "" PARENT_SCOPE)
    set(${var_private_requires} "" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "newlib")
    set(${var_requires} "vfs" PARENT_SCOPE)
    set(${var_private_requires} "soc" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "esp_ringbuf")
    set(${var_requires} "" PARENT_SCOPE)
    set(${var_private_requires} "" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "driver")
    set(${var_requires} "esp_ringbuf;soc" PARENT_SCOPE)
    set(${var_private_requires} "" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "mbedtls")
    set(${var_requires} "lwip" PARENT_SCOPE)
    set(${var_private_requires} "" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "wpa_supplicant")
    set(${var_requires} "" PARENT_SCOPE)
    set(${var_private_requires} "mbedtls" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "efuse")
    set(${var_requires} "" PARENT_SCOPE)
    set(${var_private_requires} "bootloader_support;soc" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "bootloader_support")
    set(${var_requires} "soc" PARENT_SCOPE)
    set(${var_private_requires} "spi_flash;mbedtls;efuse" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "partition_table")
    set(${var_requires} "" PARENT_SCOPE)
    set(${var_private_requires} "" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "app_update")
    set(${var_requires} "spi_flash;partition_table;bootloader_support" PARENT_SCOPE)
    set(${var_private_requires} "" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "spi_flash")
    set(${var_requires} "" PARENT_SCOPE)
    set(${var_private_requires} "bootloader_support;app_update;soc" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "nvs_flash")
    set(${var_requires} "spi_flash;mbedtls" PARENT_SCOPE)
    set(${var_private_requires} "" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "esp_wifi")
    set(${var_requires} "" PARENT_SCOPE)
    set(${var_private_requires} "wpa_supplicant;nvs_flash" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "ethernet")
    set(${var_requires} "" PARENT_SCOPE)
    set(${var_private_requires} "tcpip_adapter;esp_event;soc" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "lwip")
    set(${var_requires} "vfs;esp_wifi" PARENT_SCOPE)
    set(${var_private_requires} "ethernet;tcpip_adapter;nvs_flash" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "tcpip_adapter")
    set(${var_requires} "lwip" PARENT_SCOPE)
    set(${var_private_requires} "" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "esp_event")
    set(${var_requires} "log;tcpip_adapter;ethernet" PARENT_SCOPE)
    set(${var_private_requires} "ethernet" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "pthread")
    set(${var_requires} "" PARENT_SCOPE)
    set(${var_private_requires} "" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "smartconfig_ack")
    set(${var_requires} "" PARENT_SCOPE)
    set(${var_private_requires} "lwip;tcpip_adapter" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "espcoredump")
    set(${var_requires} "" PARENT_SCOPE)
    set(${var_private_requires} "spi_flash;soc" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "esp32")
    set(${var_requires} "driver;esp_event;efuse;soc" PARENT_SCOPE)
    set(${var_private_requires} "app_trace;app_update;bootloader_support;log;mbedtls;nvs_flash;pthread;smartconfig_ack;spi_flash;vfs;wpa_supplicant;espcoredump;esp_common;esp_wifi" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "cxx")
    set(${var_requires} "" PARENT_SCOPE)
    set(${var_private_requires} "" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "app_trace")
    set(${var_requires} "" PARENT_SCOPE)
    set(${var_private_requires} "heap;soc" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "asio")
    set(${var_requires} "lwip" PARENT_SCOPE)
    set(${var_private_requires} "" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "bootloader")
    set(${var_requires} "" PARENT_SCOPE)
    set(${var_private_requires} "" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "bt")
    set(${var_requires} "" PARENT_SCOPE)
    set(${var_private_requires} "nvs_flash;soc" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "coap")
    set(${var_requires} "lwip" PARENT_SCOPE)
    set(${var_private_requires} "" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "console")
    set(${var_requires} "" PARENT_SCOPE)
    set(${var_private_requires} "" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "nghttp")
    set(${var_requires} "" PARENT_SCOPE)
    set(${var_private_requires} "" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "esp-tls")
    set(${var_requires} "mbedtls" PARENT_SCOPE)
    set(${var_private_requires} "lwip;nghttp" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "esp_adc_cal")
    set(${var_requires} "" PARENT_SCOPE)
    set(${var_private_requires} "" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "tcp_transport")
    set(${var_requires} "lwip;esp-tls" PARENT_SCOPE)
    set(${var_private_requires} "" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "esp_http_client")
    set(${var_requires} "nghttp" PARENT_SCOPE)
    set(${var_private_requires} "mbedtls;lwip;esp-tls;tcp_transport" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "esp_http_server")
    set(${var_requires} "nghttp" PARENT_SCOPE)
    set(${var_private_requires} "lwip" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "esp_https_ota")
    set(${var_requires} "esp_http_client" PARENT_SCOPE)
    set(${var_private_requires} "log;app_update" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "openssl")
    set(${var_requires} "mbedtls" PARENT_SCOPE)
    set(${var_private_requires} "" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "esp_https_server")
    set(${var_requires} "esp_http_server;openssl" PARENT_SCOPE)
    set(${var_private_requires} "lwip" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "esptool_py")
    set(${var_requires} "" PARENT_SCOPE)
    set(${var_private_requires} "" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "expat")
    set(${var_requires} "" PARENT_SCOPE)
    set(${var_private_requires} "" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "wear_levelling")
    set(${var_requires} "spi_flash" PARENT_SCOPE)
    set(${var_private_requires} "" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "sdmmc")
    set(${var_requires} "driver" PARENT_SCOPE)
    set(${var_private_requires} "soc" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "fatfs")
    set(${var_requires} "wear_levelling;sdmmc" PARENT_SCOPE)
    set(${var_private_requires} "" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "freemodbus")
    set(${var_requires} "driver" PARENT_SCOPE)
    set(${var_private_requires} "" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "idf_test")
    set(${var_requires} "" PARENT_SCOPE)
    set(${var_private_requires} "" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "jsmn")
    set(${var_requires} "" PARENT_SCOPE)
    set(${var_private_requires} "" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "json")
    set(${var_requires} "" PARENT_SCOPE)
    set(${var_private_requires} "" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "libsodium")
    set(${var_requires} "mbedtls" PARENT_SCOPE)
    set(${var_private_requires} "" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "mdns")
    set(${var_requires} "lwip;mbedtls;console;tcpip_adapter" PARENT_SCOPE)
    set(${var_private_requires} "" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "mqtt")
    set(${var_requires} "lwip;nghttp;mbedtls;tcp_transport" PARENT_SCOPE)
    set(${var_private_requires} "" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "protobuf-c")
    set(${var_requires} "" PARENT_SCOPE)
    set(${var_private_requires} "" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "protocomm")
    set(${var_requires} "" PARENT_SCOPE)
    set(${var_private_requires} "protobuf-c;mbedtls;console;esp_http_server;bt" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "spiffs")
    set(${var_requires} "spi_flash" PARENT_SCOPE)
    set(${var_private_requires} "bootloader_support" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "ulp")
    set(${var_requires} "" PARENT_SCOPE)
    set(${var_private_requires} "" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "unity")
    set(${var_requires} "" PARENT_SCOPE)
    set(${var_private_requires} "" PARENT_SCOPE)
    return()
  endif()
  if("${component}" STREQUAL "wifi_provisioning")
    set(${var_requires} "lwip" PARENT_SCOPE)
    set(${var_private_requires} "protobuf-c;protocomm" PARENT_SCOPE)
    return()
  endif()
  message(FATAL_ERROR "Component not found: ${component}")
endfunction()