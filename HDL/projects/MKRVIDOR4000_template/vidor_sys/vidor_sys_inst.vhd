	component vidor_sys is
		port (
			clk_clk                                                    : in    std_logic                    := 'X';             -- clk
			id_switch_sw                                               : in    std_logic_vector(3 downto 0) := (others => 'X'); -- sw
			id_switch_debug_out1                                       : out   std_logic;                                       -- debug_out1
			reset_reset_n                                              : in    std_logic                    := 'X';             -- reset_n
			spi_bridge_mosi_to_the_spislave_inst_for_spichain          : in    std_logic                    := 'X';             -- mosi_to_the_spislave_inst_for_spichain
			spi_bridge_nss_to_the_spislave_inst_for_spichain           : in    std_logic                    := 'X';             -- nss_to_the_spislave_inst_for_spichain
			spi_bridge_miso_to_and_from_the_spislave_inst_for_spichain : inout std_logic                    := 'X';             -- miso_to_and_from_the_spislave_inst_for_spichain
			spi_bridge_sclk_to_the_spislave_inst_for_spichain          : in    std_logic                    := 'X';             -- sclk_to_the_spislave_inst_for_spichain
			id_switch1_sw                                              : in    std_logic_vector(3 downto 0) := (others => 'X'); -- sw
			id_switch1_debug_out1                                      : out   std_logic                                        -- debug_out1
		);
	end component vidor_sys;

	u0 : component vidor_sys
		port map (
			clk_clk                                                    => CONNECTED_TO_clk_clk,                                                    --        clk.clk
			id_switch_sw                                               => CONNECTED_TO_id_switch_sw,                                               --  id_switch.sw
			id_switch_debug_out1                                       => CONNECTED_TO_id_switch_debug_out1,                                       --           .debug_out1
			reset_reset_n                                              => CONNECTED_TO_reset_reset_n,                                              --      reset.reset_n
			spi_bridge_mosi_to_the_spislave_inst_for_spichain          => CONNECTED_TO_spi_bridge_mosi_to_the_spislave_inst_for_spichain,          -- spi_bridge.mosi_to_the_spislave_inst_for_spichain
			spi_bridge_nss_to_the_spislave_inst_for_spichain           => CONNECTED_TO_spi_bridge_nss_to_the_spislave_inst_for_spichain,           --           .nss_to_the_spislave_inst_for_spichain
			spi_bridge_miso_to_and_from_the_spislave_inst_for_spichain => CONNECTED_TO_spi_bridge_miso_to_and_from_the_spislave_inst_for_spichain, --           .miso_to_and_from_the_spislave_inst_for_spichain
			spi_bridge_sclk_to_the_spislave_inst_for_spichain          => CONNECTED_TO_spi_bridge_sclk_to_the_spislave_inst_for_spichain,          --           .sclk_to_the_spislave_inst_for_spichain
			id_switch1_sw                                              => CONNECTED_TO_id_switch1_sw,                                              -- id_switch1.sw
			id_switch1_debug_out1                                      => CONNECTED_TO_id_switch1_debug_out1                                       --           .debug_out1
		);

