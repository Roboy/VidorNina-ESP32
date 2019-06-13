
module vidor_sys (
	clk_clk,
	id_switch_sw,
	id_switch_debug_out1,
	reset_reset_n,
	spi_bridge_mosi_to_the_spislave_inst_for_spichain,
	spi_bridge_nss_to_the_spislave_inst_for_spichain,
	spi_bridge_miso_to_and_from_the_spislave_inst_for_spichain,
	spi_bridge_sclk_to_the_spislave_inst_for_spichain,
	ptp_piezo_interface0_piezo_interface_in,
	ptp_piezo_interface0_piezo_interface_out,
	ptp_piezo_interface0_time_data_master,
	ptp_piezo_interface0_time_data_slave,
	rtc_0_conduit_end_event_trigger,
	rtc_0_conduit_end_piezo_enable,
	rtc_0_conduit_end_event_trigger2,
	piezo_controller_piezo_out_export,
	piezo_controller_piezo_enable_export,
	piezo_controller_piezo_enable_piezo_enable_in,
	piezo_controller_piezo_status_export);	

	input		clk_clk;
	input	[3:0]	id_switch_sw;
	output		id_switch_debug_out1;
	input		reset_reset_n;
	input		spi_bridge_mosi_to_the_spislave_inst_for_spichain;
	input		spi_bridge_nss_to_the_spislave_inst_for_spichain;
	inout		spi_bridge_miso_to_and_from_the_spislave_inst_for_spichain;
	input		spi_bridge_sclk_to_the_spislave_inst_for_spichain;
	input		ptp_piezo_interface0_piezo_interface_in;
	output		ptp_piezo_interface0_piezo_interface_out;
	output	[31:0]	ptp_piezo_interface0_time_data_master;
	output	[31:0]	ptp_piezo_interface0_time_data_slave;
	input		rtc_0_conduit_end_event_trigger;
	output		rtc_0_conduit_end_piezo_enable;
	input		rtc_0_conduit_end_event_trigger2;
	output	[119:0]	piezo_controller_piezo_out_export;
	output		piezo_controller_piezo_enable_export;
	input		piezo_controller_piezo_enable_piezo_enable_in;
	output	[2:0]	piezo_controller_piezo_status_export;
endmodule
