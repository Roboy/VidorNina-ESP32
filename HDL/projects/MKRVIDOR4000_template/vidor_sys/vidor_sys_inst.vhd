	component vidor_sys is
		port (
			clk_clk                                                    : in    std_logic                      := 'X';             -- clk
			id_switch_sw                                               : in    std_logic_vector(3 downto 0)   := (others => 'X'); -- sw
			id_switch_debug_out1                                       : out   std_logic;                                         -- debug_out1
			piezo_controller_piezo_enable_export                       : out   std_logic;                                         -- export
			piezo_controller_piezo_enable_piezo_enable_in              : in    std_logic                      := 'X';             -- piezo_enable_in
			piezo_controller_piezo_out_export                          : out   std_logic_vector(119 downto 0);                    -- export
			piezo_controller_piezo_status_export                       : out   std_logic_vector(2 downto 0);                      -- export
			piezo_ctl_gpio_out                                         : out   std_logic;                                         -- gpio_out
			piezo_ctl_enable_in                                        : in    std_logic                      := 'X';             -- enable_in
			piezo_ctl_enable_out                                       : out   std_logic;                                         -- enable_out
			pll_areset_export                                          : in    std_logic                      := 'X';             -- export
			pll_c0_clk                                                 : out   std_logic;                                         -- clk
			pll_locked_export                                          : out   std_logic;                                         -- export
			ptp_piezo_interface0_piezo_interface_in                    : in    std_logic                      := 'X';             -- piezo_interface_in
			ptp_piezo_interface0_piezo_interface_out                   : out   std_logic;                                         -- piezo_interface_out
			ptp_piezo_interface0_time_data_master                      : out   std_logic_vector(31 downto 0);                     -- time_data_master
			ptp_piezo_interface0_time_data_slave                       : out   std_logic_vector(31 downto 0);                     -- time_data_slave
			reset_reset_n                                              : in    std_logic                      := 'X';             -- reset_n
			spi_bridge_mosi_to_the_spislave_inst_for_spichain          : in    std_logic                      := 'X';             -- mosi_to_the_spislave_inst_for_spichain
			spi_bridge_nss_to_the_spislave_inst_for_spichain           : in    std_logic                      := 'X';             -- nss_to_the_spislave_inst_for_spichain
			spi_bridge_miso_to_and_from_the_spislave_inst_for_spichain : inout std_logic                      := 'X';             -- miso_to_and_from_the_spislave_inst_for_spichain
			spi_bridge_sclk_to_the_spislave_inst_for_spichain          : in    std_logic                      := 'X';             -- sclk_to_the_spislave_inst_for_spichain
			rtc_0_conduit_end_event_trigger                            : in    std_logic                      := 'X';             -- event_trigger
			rtc_0_conduit_end_piezo_enable                             : out   std_logic;                                         -- piezo_enable
			rtc_0_conduit_end_event_trigger2                           : in    std_logic                      := 'X';             -- event_trigger2
			rtc_0_conduit_end_flag_allow_read                          : out   std_logic                                          -- flag_allow_read
		);
	end component vidor_sys;

	u0 : component vidor_sys
		port map (
			clk_clk                                                    => CONNECTED_TO_clk_clk,                                                    --                           clk.clk
			id_switch_sw                                               => CONNECTED_TO_id_switch_sw,                                               --                     id_switch.sw
			id_switch_debug_out1                                       => CONNECTED_TO_id_switch_debug_out1,                                       --                              .debug_out1
			piezo_controller_piezo_enable_export                       => CONNECTED_TO_piezo_controller_piezo_enable_export,                       -- piezo_controller_piezo_enable.export
			piezo_controller_piezo_enable_piezo_enable_in              => CONNECTED_TO_piezo_controller_piezo_enable_piezo_enable_in,              --                              .piezo_enable_in
			piezo_controller_piezo_out_export                          => CONNECTED_TO_piezo_controller_piezo_out_export,                          --    piezo_controller_piezo_out.export
			piezo_controller_piezo_status_export                       => CONNECTED_TO_piezo_controller_piezo_status_export,                       -- piezo_controller_piezo_status.export
			piezo_ctl_gpio_out                                         => CONNECTED_TO_piezo_ctl_gpio_out,                                         --                     piezo_ctl.gpio_out
			piezo_ctl_enable_in                                        => CONNECTED_TO_piezo_ctl_enable_in,                                        --                              .enable_in
			piezo_ctl_enable_out                                       => CONNECTED_TO_piezo_ctl_enable_out,                                       --                              .enable_out
			pll_areset_export                                          => CONNECTED_TO_pll_areset_export,                                          --                    pll_areset.export
			pll_c0_clk                                                 => CONNECTED_TO_pll_c0_clk,                                                 --                        pll_c0.clk
			pll_locked_export                                          => CONNECTED_TO_pll_locked_export,                                          --                    pll_locked.export
			ptp_piezo_interface0_piezo_interface_in                    => CONNECTED_TO_ptp_piezo_interface0_piezo_interface_in,                    --          ptp_piezo_interface0.piezo_interface_in
			ptp_piezo_interface0_piezo_interface_out                   => CONNECTED_TO_ptp_piezo_interface0_piezo_interface_out,                   --                              .piezo_interface_out
			ptp_piezo_interface0_time_data_master                      => CONNECTED_TO_ptp_piezo_interface0_time_data_master,                      --                              .time_data_master
			ptp_piezo_interface0_time_data_slave                       => CONNECTED_TO_ptp_piezo_interface0_time_data_slave,                       --                              .time_data_slave
			reset_reset_n                                              => CONNECTED_TO_reset_reset_n,                                              --                         reset.reset_n
			spi_bridge_mosi_to_the_spislave_inst_for_spichain          => CONNECTED_TO_spi_bridge_mosi_to_the_spislave_inst_for_spichain,          --                    spi_bridge.mosi_to_the_spislave_inst_for_spichain
			spi_bridge_nss_to_the_spislave_inst_for_spichain           => CONNECTED_TO_spi_bridge_nss_to_the_spislave_inst_for_spichain,           --                              .nss_to_the_spislave_inst_for_spichain
			spi_bridge_miso_to_and_from_the_spislave_inst_for_spichain => CONNECTED_TO_spi_bridge_miso_to_and_from_the_spislave_inst_for_spichain, --                              .miso_to_and_from_the_spislave_inst_for_spichain
			spi_bridge_sclk_to_the_spislave_inst_for_spichain          => CONNECTED_TO_spi_bridge_sclk_to_the_spislave_inst_for_spichain,          --                              .sclk_to_the_spislave_inst_for_spichain
			rtc_0_conduit_end_event_trigger                            => CONNECTED_TO_rtc_0_conduit_end_event_trigger,                            --             rtc_0_conduit_end.event_trigger
			rtc_0_conduit_end_piezo_enable                             => CONNECTED_TO_rtc_0_conduit_end_piezo_enable,                             --                              .piezo_enable
			rtc_0_conduit_end_event_trigger2                           => CONNECTED_TO_rtc_0_conduit_end_event_trigger2,                           --                              .event_trigger2
			rtc_0_conduit_end_flag_allow_read                          => CONNECTED_TO_rtc_0_conduit_end_flag_allow_read                           --                              .flag_allow_read
		);

