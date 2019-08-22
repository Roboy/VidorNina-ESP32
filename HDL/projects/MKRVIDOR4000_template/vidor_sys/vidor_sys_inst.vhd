	component vidor_sys is
		port (
			clk_clk                                                    : in    std_logic                    := 'X'; -- clk
			myocontrol_0_conduit_end_angle_miso                        : in    std_logic                    := 'X'; -- angle_miso
			myocontrol_0_conduit_end_angle_mosi                        : out   std_logic;                           -- angle_mosi
			myocontrol_0_conduit_end_angle_sck                         : out   std_logic;                           -- angle_sck
			myocontrol_0_conduit_end_angle_ss_n_o                      : out   std_logic_vector(3 downto 0);        -- angle_ss_n_o
			myocontrol_0_conduit_end_gpio_n                            : out   std_logic;                           -- gpio_n
			myocontrol_0_conduit_end_mirrored_muscle_unit              : in    std_logic                    := 'X'; -- mirrored_muscle_unit
			myocontrol_0_conduit_end_miso                              : in    std_logic                    := 'X'; -- miso
			myocontrol_0_conduit_end_mosi                              : out   std_logic;                           -- mosi
			myocontrol_0_conduit_end_power_sense_n                     : in    std_logic                    := 'X'; -- power_sense_n
			myocontrol_0_conduit_end_ss_n_o                            : out   std_logic_vector(3 downto 0);        -- ss_n_o
			myocontrol_0_conduit_end_sck                               : out   std_logic;                           -- sck
			reset_reset_n                                              : in    std_logic                    := 'X'; -- reset_n
			spi_bridge_mosi_to_the_spislave_inst_for_spichain          : in    std_logic                    := 'X'; -- mosi_to_the_spislave_inst_for_spichain
			spi_bridge_nss_to_the_spislave_inst_for_spichain           : in    std_logic                    := 'X'; -- nss_to_the_spislave_inst_for_spichain
			spi_bridge_miso_to_and_from_the_spislave_inst_for_spichain : inout std_logic                    := 'X'; -- miso_to_and_from_the_spislave_inst_for_spichain
			spi_bridge_sclk_to_the_spislave_inst_for_spichain          : in    std_logic                    := 'X'  -- sclk_to_the_spislave_inst_for_spichain
		);
	end component vidor_sys;

	u0 : component vidor_sys
		port map (
			clk_clk                                                    => CONNECTED_TO_clk_clk,                                                    --                      clk.clk
			myocontrol_0_conduit_end_angle_miso                        => CONNECTED_TO_myocontrol_0_conduit_end_angle_miso,                        -- myocontrol_0_conduit_end.angle_miso
			myocontrol_0_conduit_end_angle_mosi                        => CONNECTED_TO_myocontrol_0_conduit_end_angle_mosi,                        --                         .angle_mosi
			myocontrol_0_conduit_end_angle_sck                         => CONNECTED_TO_myocontrol_0_conduit_end_angle_sck,                         --                         .angle_sck
			myocontrol_0_conduit_end_angle_ss_n_o                      => CONNECTED_TO_myocontrol_0_conduit_end_angle_ss_n_o,                      --                         .angle_ss_n_o
			myocontrol_0_conduit_end_gpio_n                            => CONNECTED_TO_myocontrol_0_conduit_end_gpio_n,                            --                         .gpio_n
			myocontrol_0_conduit_end_mirrored_muscle_unit              => CONNECTED_TO_myocontrol_0_conduit_end_mirrored_muscle_unit,              --                         .mirrored_muscle_unit
			myocontrol_0_conduit_end_miso                              => CONNECTED_TO_myocontrol_0_conduit_end_miso,                              --                         .miso
			myocontrol_0_conduit_end_mosi                              => CONNECTED_TO_myocontrol_0_conduit_end_mosi,                              --                         .mosi
			myocontrol_0_conduit_end_power_sense_n                     => CONNECTED_TO_myocontrol_0_conduit_end_power_sense_n,                     --                         .power_sense_n
			myocontrol_0_conduit_end_ss_n_o                            => CONNECTED_TO_myocontrol_0_conduit_end_ss_n_o,                            --                         .ss_n_o
			myocontrol_0_conduit_end_sck                               => CONNECTED_TO_myocontrol_0_conduit_end_sck,                               --                         .sck
			reset_reset_n                                              => CONNECTED_TO_reset_reset_n,                                              --                    reset.reset_n
			spi_bridge_mosi_to_the_spislave_inst_for_spichain          => CONNECTED_TO_spi_bridge_mosi_to_the_spislave_inst_for_spichain,          --               spi_bridge.mosi_to_the_spislave_inst_for_spichain
			spi_bridge_nss_to_the_spislave_inst_for_spichain           => CONNECTED_TO_spi_bridge_nss_to_the_spislave_inst_for_spichain,           --                         .nss_to_the_spislave_inst_for_spichain
			spi_bridge_miso_to_and_from_the_spislave_inst_for_spichain => CONNECTED_TO_spi_bridge_miso_to_and_from_the_spislave_inst_for_spichain, --                         .miso_to_and_from_the_spislave_inst_for_spichain
			spi_bridge_sclk_to_the_spislave_inst_for_spichain          => CONNECTED_TO_spi_bridge_sclk_to_the_spislave_inst_for_spichain           --                         .sclk_to_the_spislave_inst_for_spichain
		);

