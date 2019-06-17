	vidor_sys u0 (
		.clk_clk                                                    (<connected-to-clk_clk>),                                                    //        clk.clk
		.id_switch_sw                                               (<connected-to-id_switch_sw>),                                               //  id_switch.sw
		.id_switch_debug_out1                                       (<connected-to-id_switch_debug_out1>),                                       //           .debug_out1
		.reset_reset_n                                              (<connected-to-reset_reset_n>),                                              //      reset.reset_n
		.spi_bridge_mosi_to_the_spislave_inst_for_spichain          (<connected-to-spi_bridge_mosi_to_the_spislave_inst_for_spichain>),          // spi_bridge.mosi_to_the_spislave_inst_for_spichain
		.spi_bridge_nss_to_the_spislave_inst_for_spichain           (<connected-to-spi_bridge_nss_to_the_spislave_inst_for_spichain>),           //           .nss_to_the_spislave_inst_for_spichain
		.spi_bridge_miso_to_and_from_the_spislave_inst_for_spichain (<connected-to-spi_bridge_miso_to_and_from_the_spislave_inst_for_spichain>), //           .miso_to_and_from_the_spislave_inst_for_spichain
		.spi_bridge_sclk_to_the_spislave_inst_for_spichain          (<connected-to-spi_bridge_sclk_to_the_spislave_inst_for_spichain>),          //           .sclk_to_the_spislave_inst_for_spichain
		.id_switch1_sw                                              (<connected-to-id_switch1_sw>),                                              // id_switch1.sw
		.id_switch1_debug_out1                                      (<connected-to-id_switch1_debug_out1>)                                       //           .debug_out1
	);

