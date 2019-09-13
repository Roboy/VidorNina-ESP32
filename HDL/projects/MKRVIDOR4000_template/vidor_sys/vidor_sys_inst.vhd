	component vidor_sys is
		port (
			clk_clk                                                    : in    std_logic := 'X'; -- clk
			iceboardcontrol_0_conduit_end_rx                           : in    std_logic := 'X'; -- rx
			iceboardcontrol_0_conduit_end_tx                           : out   std_logic;        -- tx
			reset_reset_n                                              : in    std_logic := 'X'; -- reset_n
			spi_bridge_mosi_to_the_spislave_inst_for_spichain          : in    std_logic := 'X'; -- mosi_to_the_spislave_inst_for_spichain
			spi_bridge_nss_to_the_spislave_inst_for_spichain           : in    std_logic := 'X'; -- nss_to_the_spislave_inst_for_spichain
			spi_bridge_miso_to_and_from_the_spislave_inst_for_spichain : inout std_logic := 'X'; -- miso_to_and_from_the_spislave_inst_for_spichain
			spi_bridge_sclk_to_the_spislave_inst_for_spichain          : in    std_logic := 'X'  -- sclk_to_the_spislave_inst_for_spichain
		);
	end component vidor_sys;

	u0 : component vidor_sys
		port map (
			clk_clk                                                    => CONNECTED_TO_clk_clk,                                                    --                           clk.clk
			iceboardcontrol_0_conduit_end_rx                           => CONNECTED_TO_iceboardcontrol_0_conduit_end_rx,                           -- iceboardcontrol_0_conduit_end.rx
			iceboardcontrol_0_conduit_end_tx                           => CONNECTED_TO_iceboardcontrol_0_conduit_end_tx,                           --                              .tx
			reset_reset_n                                              => CONNECTED_TO_reset_reset_n,                                              --                         reset.reset_n
			spi_bridge_mosi_to_the_spislave_inst_for_spichain          => CONNECTED_TO_spi_bridge_mosi_to_the_spislave_inst_for_spichain,          --                    spi_bridge.mosi_to_the_spislave_inst_for_spichain
			spi_bridge_nss_to_the_spislave_inst_for_spichain           => CONNECTED_TO_spi_bridge_nss_to_the_spislave_inst_for_spichain,           --                              .nss_to_the_spislave_inst_for_spichain
			spi_bridge_miso_to_and_from_the_spislave_inst_for_spichain => CONNECTED_TO_spi_bridge_miso_to_and_from_the_spislave_inst_for_spichain, --                              .miso_to_and_from_the_spislave_inst_for_spichain
			spi_bridge_sclk_to_the_spislave_inst_for_spichain          => CONNECTED_TO_spi_bridge_sclk_to_the_spislave_inst_for_spichain           --                              .sclk_to_the_spislave_inst_for_spichain
		);

