# TCL File Generated by Component Editor 18.1
# Tue Sep 17 00:15:06 CEST 2019
# DO NOT MODIFY


# 
# ICEboardControl "ICEboardControl" v1.0
# Simon Trendel 2019.09.17.00:15:06
# 
# 

# 
# request TCL package from ACDS 16.1
# 
package require -exact qsys 16.1


# 
# module ICEboardControl
# 
set_module_property DESCRIPTION ""
set_module_property NAME ICEboardControl
set_module_property VERSION 1.0
set_module_property INTERNAL false
set_module_property OPAQUE_ADDRESS_MAP true
set_module_property AUTHOR "Simon Trendel"
set_module_property DISPLAY_NAME ICEboardControl
set_module_property INSTANTIATE_IN_SYSTEM_MODULE true
set_module_property EDITABLE true
set_module_property REPORT_TO_TALKBACK false
set_module_property ALLOW_GREYBOX_GENERATION false
set_module_property REPORT_HIERARCHY false


# 
# file sets
# 
add_fileset QUARTUS_SYNTH QUARTUS_SYNTH "" ""
set_fileset_property QUARTUS_SYNTH TOP_LEVEL ICEboardControl
set_fileset_property QUARTUS_SYNTH ENABLE_RELATIVE_INCLUDE_PATHS false
set_fileset_property QUARTUS_SYNTH ENABLE_FILE_OVERWRITE_MODE false
add_fileset_file iCEboardControl.sv SYSTEM_VERILOG PATH iCEboardControl.sv TOP_LEVEL_FILE
add_fileset_file coms.sv SYSTEM_VERILOG PATH coms.sv
add_fileset_file uart_rx.v VERILOG PATH uart_rx.v
add_fileset_file uart_tx.v VERILOG PATH uart_tx.v


# 
# parameters
# 
add_parameter NUMBER_OF_MOTORS INTEGER 6 "how many motors should be controlled"
set_parameter_property NUMBER_OF_MOTORS DEFAULT_VALUE 6
set_parameter_property NUMBER_OF_MOTORS DISPLAY_NAME NUMBER_OF_MOTORS
set_parameter_property NUMBER_OF_MOTORS TYPE INTEGER
set_parameter_property NUMBER_OF_MOTORS UNITS None
set_parameter_property NUMBER_OF_MOTORS ALLOWED_RANGES -2147483648:2147483647
set_parameter_property NUMBER_OF_MOTORS DESCRIPTION "how many motors should be controlled"
set_parameter_property NUMBER_OF_MOTORS HDL_PARAMETER true
add_parameter CLOCK_FREQ_HZ INTEGER 48000000 "of the clock fed to this module"
set_parameter_property CLOCK_FREQ_HZ DEFAULT_VALUE 48000000
set_parameter_property CLOCK_FREQ_HZ DISPLAY_NAME CLOCK_FREQ_HZ
set_parameter_property CLOCK_FREQ_HZ TYPE INTEGER
set_parameter_property CLOCK_FREQ_HZ UNITS None
set_parameter_property CLOCK_FREQ_HZ ALLOWED_RANGES -2147483648:2147483647
set_parameter_property CLOCK_FREQ_HZ DESCRIPTION "of the clock fed to this module"
set_parameter_property CLOCK_FREQ_HZ HDL_PARAMETER true
add_parameter BAUDRATE INTEGER 115200 "of the UART transmission"
set_parameter_property BAUDRATE DEFAULT_VALUE 115200
set_parameter_property BAUDRATE DISPLAY_NAME BAUDRATE
set_parameter_property BAUDRATE TYPE INTEGER
set_parameter_property BAUDRATE UNITS None
set_parameter_property BAUDRATE ALLOWED_RANGES -2147483648:2147483647
set_parameter_property BAUDRATE DESCRIPTION "of the UART transmission"
set_parameter_property BAUDRATE HDL_PARAMETER true


# 
# display items
# 


# 
# connection point reset
# 
add_interface reset reset end
set_interface_property reset associatedClock clock_sink
set_interface_property reset synchronousEdges DEASSERT
set_interface_property reset ENABLED true
set_interface_property reset EXPORT_OF ""
set_interface_property reset PORT_NAME_MAP ""
set_interface_property reset CMSIS_SVD_VARIABLES ""
set_interface_property reset SVD_ADDRESS_GROUP ""

add_interface_port reset reset reset Input 1


# 
# connection point avalon_slave_0
# 
add_interface avalon_slave_0 avalon end
set_interface_property avalon_slave_0 addressUnits WORDS
set_interface_property avalon_slave_0 associatedClock clock_sink
set_interface_property avalon_slave_0 associatedReset reset
set_interface_property avalon_slave_0 bitsPerSymbol 8
set_interface_property avalon_slave_0 burstOnBurstBoundariesOnly false
set_interface_property avalon_slave_0 burstcountUnits WORDS
set_interface_property avalon_slave_0 explicitAddressSpan 0
set_interface_property avalon_slave_0 holdTime 0
set_interface_property avalon_slave_0 linewrapBursts false
set_interface_property avalon_slave_0 maximumPendingReadTransactions 0
set_interface_property avalon_slave_0 maximumPendingWriteTransactions 0
set_interface_property avalon_slave_0 readLatency 0
set_interface_property avalon_slave_0 readWaitTime 1
set_interface_property avalon_slave_0 setupTime 0
set_interface_property avalon_slave_0 timingUnits Cycles
set_interface_property avalon_slave_0 writeWaitTime 0
set_interface_property avalon_slave_0 ENABLED true
set_interface_property avalon_slave_0 EXPORT_OF ""
set_interface_property avalon_slave_0 PORT_NAME_MAP ""
set_interface_property avalon_slave_0 CMSIS_SVD_VARIABLES ""
set_interface_property avalon_slave_0 SVD_ADDRESS_GROUP ""

add_interface_port avalon_slave_0 address address Input 16
add_interface_port avalon_slave_0 write write Input 1
add_interface_port avalon_slave_0 writedata writedata Input 32
add_interface_port avalon_slave_0 read read Input 1
add_interface_port avalon_slave_0 readdata readdata Output 32
add_interface_port avalon_slave_0 waitrequest waitrequest Output 1
set_interface_assignment avalon_slave_0 embeddedsw.configuration.isFlash 0
set_interface_assignment avalon_slave_0 embeddedsw.configuration.isMemoryDevice 0
set_interface_assignment avalon_slave_0 embeddedsw.configuration.isNonVolatileStorage 0
set_interface_assignment avalon_slave_0 embeddedsw.configuration.isPrintableDevice 0


# 
# connection point conduit_end
# 
add_interface conduit_end conduit end
set_interface_property conduit_end associatedClock clock_sink
set_interface_property conduit_end associatedReset reset
set_interface_property conduit_end ENABLED true
set_interface_property conduit_end EXPORT_OF ""
set_interface_property conduit_end PORT_NAME_MAP ""
set_interface_property conduit_end CMSIS_SVD_VARIABLES ""
set_interface_property conduit_end SVD_ADDRESS_GROUP ""

add_interface_port conduit_end rx rx Input 1
add_interface_port conduit_end tx tx Output 1
add_interface_port conduit_end rx_receive rx_receive Bidir 1
add_interface_port conduit_end clock24MHz clock24mhz Input 1


# 
# connection point clock_sink
# 
add_interface clock_sink clock end
set_interface_property clock_sink clockRate 0
set_interface_property clock_sink ENABLED true
set_interface_property clock_sink EXPORT_OF ""
set_interface_property clock_sink PORT_NAME_MAP ""
set_interface_property clock_sink CMSIS_SVD_VARIABLES ""
set_interface_property clock_sink SVD_ADDRESS_GROUP ""

add_interface_port clock_sink clock48MHz clk Input 1

