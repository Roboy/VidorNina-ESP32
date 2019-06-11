# VidorNina-ESP32
Template to use Vidor 4000k with clean fpga and AVALON Bridge to Nina W-10* 

The aim of this project is to use the power of the nina (esp32) with an clean Cyclon10. 

## Required software
* Quartus 18.1 light (could also work with other Quartus versions >= 17.0 )
* [espressif toolchain](https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system-cmake.html
 "Link to setup tutorial")

## Quartus setup
the following enviroment vars have to be set (could be added to ~/.profile)
```bash
export QSYS_ROOTDIR=~/intelFPGA_lite/18.1/quartus/sopc_builder/bin
export QUARTUS_ROOTDIR=~/intelFPGA_lite/18.1/quartus/
```

## Espressif setup
the following enviroment vars have to be set (could be added to ~/.profile) 
```bash
export IDF_PATH=~/esp/esp-idf
export PATH="$IDF_PATH/tools:$PATH"
export PATH=$PATH:$HOME/esp/xtensa-esp32-elf/bin
```



The FPGA can be programmed on fly via the Atmel core over Wifi. 
