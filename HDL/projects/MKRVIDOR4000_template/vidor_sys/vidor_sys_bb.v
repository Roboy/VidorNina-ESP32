
module vidor_sys (
	clk_clk,
	id_switch_sw,
	id_switch_debug_out1,
	piezo_controller_piezo_enable_export,
	piezo_controller_piezo_enable_piezo_enable_in,
	piezo_controller_piezo_out_export,
	piezo_controller_piezo_status_export,
	ptp_piezo_interface0_piezo_interface_in,
	ptp_piezo_interface0_piezo_interface_out,
	ptp_piezo_interface0_time_data_master,
	ptp_piezo_interface0_time_data_slave,
	reset_reset_n,
	rtc_0_conduit_end_event_trigger,
	rtc_0_conduit_end_piezo_enable,
	rtc_0_conduit_end_event_trigger2,
	spi_bridge_mosi_to_the_spislave_inst_for_spichain,
	spi_bridge_nss_to_the_spislave_inst_for_spichain,
	spi_bridge_miso_to_and_from_the_spislave_inst_for_spichain,
	spi_bridge_sclk_to_the_spislave_inst_for_spichain,
	piezo_ctl_gpio_out,
	piezo_ctl_enable_in,
	piezo_ctl_enable_out);	

	input		clk_clk;
	input	[3:0]	id_switch_sw;
	output		id_switch_debug_out1;
	output		piezo_controller_piezo_enable_export;
	input		piezo_controller_piezo_enable_piezo_enable_in;
	output	[119:0]	piezo_controller_piezo_out_export;
	output	[2:0]	piezo_controller_piezo_status_export;
	input		ptp_piezo_interface0_piezo_interface_in;
	output		ptp_piezo_interface0_piezo_interface_out;
	output	[31:0]	ptp_piezo_interface0_time_data_master;
	output	[31:0]	ptp_piezo_interface0_time_data_slave;
	input		reset_reset_n;
	input		rtc_0_conduit_end_event_trigger;
	output		rtc_0_conduit_end_piezo_enable;
	input		rtc_0_conduit_end_event_trigger2;
	input		spi_bridge_mosi_to_the_spislave_inst_for_spichain;
	input		spi_bridge_nss_to_the_spislave_inst_for_spichain;
	inout		spi_bridge_miso_to_and_from_the_spislave_inst_for_spichain;
	input		spi_bridge_sclk_to_the_spislave_inst_for_spichain;
	output		piezo_ctl_gpio_out;
	input		piezo_ctl_enable_in;
	output		piezo_ctl_enable_out;
endmodule
