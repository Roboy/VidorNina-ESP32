
module vidor_sys (
	clk_clk,
	myocontrol_0_conduit_end_angle_miso,
	myocontrol_0_conduit_end_angle_mosi,
	myocontrol_0_conduit_end_angle_sck,
	myocontrol_0_conduit_end_angle_ss_n_o,
	myocontrol_0_conduit_end_gpio_n,
	myocontrol_0_conduit_end_mirrored_muscle_unit,
	myocontrol_0_conduit_end_miso,
	myocontrol_0_conduit_end_mosi,
	myocontrol_0_conduit_end_power_sense_n,
	myocontrol_0_conduit_end_ss_n_o,
	myocontrol_0_conduit_end_sck,
	reset_reset_n,
	spi_bridge_mosi_to_the_spislave_inst_for_spichain,
	spi_bridge_nss_to_the_spislave_inst_for_spichain,
	spi_bridge_miso_to_and_from_the_spislave_inst_for_spichain,
	spi_bridge_sclk_to_the_spislave_inst_for_spichain);	

	input		clk_clk;
	input		myocontrol_0_conduit_end_angle_miso;
	output		myocontrol_0_conduit_end_angle_mosi;
	output		myocontrol_0_conduit_end_angle_sck;
	output	[3:0]	myocontrol_0_conduit_end_angle_ss_n_o;
	output		myocontrol_0_conduit_end_gpio_n;
	input		myocontrol_0_conduit_end_mirrored_muscle_unit;
	input		myocontrol_0_conduit_end_miso;
	output		myocontrol_0_conduit_end_mosi;
	input		myocontrol_0_conduit_end_power_sense_n;
	output	[3:0]	myocontrol_0_conduit_end_ss_n_o;
	output		myocontrol_0_conduit_end_sck;
	input		reset_reset_n;
	input		spi_bridge_mosi_to_the_spislave_inst_for_spichain;
	input		spi_bridge_nss_to_the_spislave_inst_for_spichain;
	inout		spi_bridge_miso_to_and_from_the_spislave_inst_for_spichain;
	input		spi_bridge_sclk_to_the_spislave_inst_for_spichain;
endmodule
