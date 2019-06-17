
module vidor_sys (
	clk_clk,
	id_switch_sw,
	id_switch_debug_out1,
	reset_reset_n,
	spi_bridge_mosi_to_the_spislave_inst_for_spichain,
	spi_bridge_nss_to_the_spislave_inst_for_spichain,
	spi_bridge_miso_to_and_from_the_spislave_inst_for_spichain,
	spi_bridge_sclk_to_the_spislave_inst_for_spichain,
	id_switch1_sw,
	id_switch1_debug_out1);	

	input		clk_clk;
	input	[3:0]	id_switch_sw;
	output		id_switch_debug_out1;
	input		reset_reset_n;
	input		spi_bridge_mosi_to_the_spislave_inst_for_spichain;
	input		spi_bridge_nss_to_the_spislave_inst_for_spichain;
	inout		spi_bridge_miso_to_and_from_the_spislave_inst_for_spichain;
	input		spi_bridge_sclk_to_the_spislave_inst_for_spichain;
	input	[3:0]	id_switch1_sw;
	output		id_switch1_debug_out1;
endmodule
