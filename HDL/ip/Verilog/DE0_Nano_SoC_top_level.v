// Copyright (C) 2018  Intel Corporation. All rights reserved.
// Your use of Intel Corporation's design tools, logic functions 
// and other software and tools, and its AMPP partner logic 
// functions, and any output files from any of the foregoing 
// (including device programming or simulation files), and any 
// associated documentation or information are expressly subject 
// to the terms and conditions of the Intel Program License 
// Subscription Agreement, the Intel Quartus Prime License Agreement,
// the Intel FPGA IP License Agreement, or other applicable license
// agreement, including, without limitation, that your use is for
// the sole purpose of programming logic devices manufactured by
// Intel and sold by Intel or its authorized distributors.  Please
// refer to the applicable agreement for further details.

module DE0_Nano_SoC_top_level
(
// {ALTERA_ARGS_BEGIN} DO NOT REMOVE THIS LINE!

	ENABLE,
	FPGA_CLK1_50,
	HPS_CONV_USB_N,
	HPS_DDR3_ADDR,
	HPS_DDR3_BA,
	HPS_DDR3_CAS_N,
	HPS_DDR3_CK_N,
	HPS_DDR3_CK_P,
	HPS_DDR3_CKE,
	HPS_DDR3_CS_N,
	HPS_DDR3_DM,
	HPS_DDR3_DQ,
	HPS_DDR3_DQS_N,
	HPS_DDR3_DQS_P,
	HPS_DDR3_ODT,
	HPS_DDR3_RAS_N,
	HPS_DDR3_RESET_N,
	HPS_DDR3_RZQ,
	HPS_DDR3_WE_N,
	HPS_ENET_GTX_CLK,
	HPS_ENET_INT_N,
	HPS_ENET_MDC,
	HPS_ENET_MDIO,
	HPS_ENET_RX_CLK,
	HPS_ENET_RX_DATA,
	HPS_ENET_RX_DV,
	HPS_ENET_TX_DATA,
	HPS_ENET_TX_EN,
	HPS_GSENSOR_INT,
	HPS_I2C0_SCLK,
	HPS_I2C0_SDAT,
	HPS_KEY_N,
	HPS_LED,
	HPS_LTC_GPIO,
	HPS_LTC_GPIO_ENABLE_N,
	HPS_SD_CLK,
	HPS_SD_CMD,
	HPS_SD_DATA,
	HPS_UART_RX,
	HPS_UART_TX,
	HPS_USB_CLKOUT,
	HPS_USB_DATA,
	HPS_USB_DIR,
	HPS_USB_NXT,
	HPS_USB_STP,
	KEY_N,
	LED,
	PIEZO,
	ADC_CONVST,
	ADC_SCK,
	ADC_SDI,
	ADC_SDO,
	ARDUINO_IO_0,
	ARDUINO_IO_1,
	ARDUINO_IO_2,
	ARDUINO_IO_3,
	ARDUINO_IO_4,
	ARDUINO_IO_5,
	ARDUINO_IO_6,
	ARDUINO_IO_7,
	ARDUINO_IO_8,
	ARDUINO_IO_9,
	ARDUINO_IO_10,
	ARDUINO_IO_11,
	ARDUINO_IO_12,
	ARDUINO_IO_13,
	ARDUINO_IO_14,
	ARDUINO_IO_15,
	ARDUINO_RESET_N,
	FPGA_CLK2_50,
	FPGA_CLK3_50,
	HPS_DDR3_ADDR_0,
	HPS_DDR3_ADDR_1,
	HPS_DDR3_ADDR_2,
	HPS_DDR3_ADDR_3,
	HPS_DDR3_ADDR_4,
	HPS_DDR3_ADDR_5,
	HPS_DDR3_ADDR_6,
	HPS_DDR3_ADDR_7,
	HPS_DDR3_ADDR_8,
	HPS_DDR3_ADDR_9,
	HPS_DDR3_ADDR_10,
	HPS_DDR3_ADDR_11,
	HPS_DDR3_ADDR_12,
	HPS_DDR3_ADDR_13,
	HPS_DDR3_ADDR_14,
	HPS_DDR3_BA_0,
	HPS_DDR3_BA_1,
	HPS_DDR3_BA_2,
	HPS_DDR3_DM_0,
	HPS_DDR3_DM_1,
	HPS_DDR3_DM_2,
	HPS_DDR3_DM_3,
	HPS_DDR3_DQ_0,
	HPS_DDR3_DQ_1,
	HPS_DDR3_DQ_2,
	HPS_DDR3_DQ_3,
	HPS_DDR3_DQ_4,
	HPS_DDR3_DQ_5,
	HPS_DDR3_DQ_6,
	HPS_DDR3_DQ_7,
	HPS_DDR3_DQ_8,
	HPS_DDR3_DQ_9,
	HPS_DDR3_DQ_10,
	HPS_DDR3_DQ_11,
	HPS_DDR3_DQ_12,
	HPS_DDR3_DQ_13,
	HPS_DDR3_DQ_14,
	HPS_DDR3_DQ_15,
	HPS_DDR3_DQ_16,
	HPS_DDR3_DQ_17,
	HPS_DDR3_DQ_18,
	HPS_DDR3_DQ_19,
	HPS_DDR3_DQ_20,
	HPS_DDR3_DQ_21,
	HPS_DDR3_DQ_22,
	HPS_DDR3_DQ_23,
	HPS_DDR3_DQ_24,
	HPS_DDR3_DQ_25,
	HPS_DDR3_DQ_26,
	HPS_DDR3_DQ_27,
	HPS_DDR3_DQ_28,
	HPS_DDR3_DQ_29,
	HPS_DDR3_DQ_30,
	HPS_DDR3_DQ_31,
	HPS_DDR3_DQS_N_0,
	HPS_DDR3_DQS_N_1,
	HPS_DDR3_DQS_N_2,
	HPS_DDR3_DQS_N_3,
	HPS_DDR3_DQS_P_0,
	HPS_DDR3_DQS_P_1,
	HPS_DDR3_DQS_P_2,
	HPS_DDR3_DQS_P_3,
	HPS_ENET_RX_DATA_0,
	HPS_ENET_RX_DATA_1,
	HPS_ENET_RX_DATA_2,
	HPS_ENET_RX_DATA_3,
	HPS_ENET_TX_DATA_0,
	HPS_ENET_TX_DATA_1,
	HPS_ENET_TX_DATA_2,
	HPS_ENET_TX_DATA_3,
	HPS_I2C1_SCLK,
	HPS_I2C1_SDAT,
	HPS_SD_DATA_0,
	HPS_SD_DATA_1,
	HPS_SD_DATA_2,
	HPS_SD_DATA_3,
	HPS_SPIM_CLK,
	HPS_SPIM_MISO,
	HPS_SPIM_MOSI,
	HPS_SPIM_SS,
	HPS_USB_DATA_0,
	HPS_USB_DATA_1,
	HPS_USB_DATA_2,
	HPS_USB_DATA_3,
	HPS_USB_DATA_4,
	HPS_USB_DATA_5,
	HPS_USB_DATA_6,
	HPS_USB_DATA_7,
	KEY_N_0,
	KEY_N_1,
	LED_0,
	LED_1,
	LED_2,
	LED_3,
	LED_4,
	LED_5,
	LED_6,
	LED_7,
	SW_0,
	SW_1,
	SW_2,
	SW_3,
	GPIO_0_0,
	GPIO_0_1,
	GPIO_0_2,
	GPIO_0_3,
	GPIO_0_4,
	GPIO_0_5,
	GPIO_0_6,
	GPIO_0_7,
	GPIO_0_8,
	GPIO_0_9,
	GPIO_0_10,
	GPIO_0_11,
	GPIO_0_12,
	GPIO_0_13,
	GPIO_0_14,
	GPIO_0_15,
	GPIO_0_16,
	GPIO_0_17,
	GPIO_0_18,
	GPIO_0_19,
	GPIO_0_20,
	GPIO_0_21,
	GPIO_0_22,
	GPIO_0_23,
	GPIO_0_24,
	GPIO_0_25,
	GPIO_0_26,
	GPIO_0_27,
	GPIO_0_28,
	GPIO_0_29,
	GPIO_0_30,
	GPIO_0_31,
	GPIO_0_32,
	GPIO_0_33,
	GPIO_0_34,
	GPIO_0_35,
	GPIO_1_0,
	GPIO_1_1,
	GPIO_1_2,
	GPIO_1_3,
	GPIO_1_4,
	GPIO_1_5,
	GPIO_1_6,
	GPIO_1_7,
	GPIO_1_8,
	GPIO_1_9,
	GPIO_1_10,
	GPIO_1_11,
	GPIO_1_12,
	GPIO_1_13,
	GPIO_1_14,
	GPIO_1_15,
	GPIO_1_16,
	GPIO_1_17,
	GPIO_1_18,
	GPIO_1_19,
	GPIO_1_20,
	GPIO_1_21,
	GPIO_1_22,
	GPIO_1_23,
	GPIO_1_24,
	GPIO_1_25,
	GPIO_1_26,
	GPIO_1_27,
	GPIO_1_28,
	GPIO_1_29,
	GPIO_1_30,
	GPIO_1_31,
	GPIO_1_32,
	GPIO_1_33,
	GPIO_1_34,
	GPIO_1_35,
	PIEZO_1,
	PIEZO_2,
	PIEZO_3,
	PIEZO_4,
	PIEZO_5,
	PIEZO_6,
	PIEZO_7,
	PIEZO_8,
	PIEZO_9,
	PIEZO_10,
	PIEZO_11,
	PIEZO_12,
	PIEZO_13,
	PIEZO_14,
	PIEZO_15,
	PIEZO_16,
	PIEZO_17,
	PIEZO_18,
	PIEZO_19,
	PIEZO_20,
	PIEZO_21,
	PIEZO_22,
	PIEZO_23,
	PIEZO_24,
	PIEZO_25,
	PIEZO_26,
	PIEZO_27,
	PIEZO_28,
	PIEZO_29,
	PIEZO_30,
	PIEZO_31,
	PIEZO_32,
	PIEZO_33,
	PIEZO_34,
	PIEZO_35,
	PIEZO_36,
	PIEZO_37,
	PIEZO_38,
	PIEZO_39,
	PIEZO_40,
	PIEZO_41,
	PIEZO_42,
	PIEZO_43,
	PIEZO_44,
	PIEZO_45,
	PIEZO_46,
	PIEZO_47,
	PIEZO_48,
	PIEZO_49,
	PIEZO_50,
	PIEZO_51,
	PIEZO_52,
	PIEZO_53,
	PIEZO_54,
	PIEZO_55,
	PIEZO_56,
	PIEZO_57,
	PIEZO_58,
	PIEZO_59,
	PIEZO_60,
	PIEZO_61,
	PIEZO_62,
	PIEZO_63,
	PIEZO_64,
	PIEZO_65,
	PIEZO_66,
	PIEZO_67,
	PIEZO_68,
	PIEZO_69,
	PIEZO_70,
	PIEZO_71,
	PIEZO_72,
	PIEZO_73,
	PIEZO_74,
	PIEZO_75,
	PIEZO_76,
	PIEZO_77,
	PIEZO_78,
	PIEZO_79,
	PIEZO_80,
	PIEZO_81,
	PIEZO_82,
	PIEZO_83,
	PIEZO_84,
	PIEZO_85,
	PIEZO_86,
	PIEZO_87,
	PIEZO_88,
	HPS_LTC_GPIO_0,
	HPS_LTC_GPIO_1,
	HPS_LTC_GPIO_2,
	HPS_LTC_GPIO_3,
	RTC_TRIGGER,
	ARDUINO_IO,
	SW,
	GPIO_0,
	GPIO_1
// {ALTERA_ARGS_END} DO NOT REMOVE THIS LINE!

);

// {ALTERA_IO_BEGIN} DO NOT REMOVE THIS LINE!
output			ENABLE;
input			FPGA_CLK1_50;
inout			HPS_CONV_USB_N;
output	[14:0]	HPS_DDR3_ADDR;
output	[2:0]	HPS_DDR3_BA;
output			HPS_DDR3_CAS_N;
output			HPS_DDR3_CK_N;
output			HPS_DDR3_CK_P;
output			HPS_DDR3_CKE;
output			HPS_DDR3_CS_N;
output	[3:0]	HPS_DDR3_DM;
inout	[31:0]	HPS_DDR3_DQ;
inout	[3:0]	HPS_DDR3_DQS_N;
inout	[3:0]	HPS_DDR3_DQS_P;
output			HPS_DDR3_ODT;
output			HPS_DDR3_RAS_N;
output			HPS_DDR3_RESET_N;
input			HPS_DDR3_RZQ;
output			HPS_DDR3_WE_N;
output			HPS_ENET_GTX_CLK;
inout			HPS_ENET_INT_N;
output			HPS_ENET_MDC;
inout			HPS_ENET_MDIO;
input			HPS_ENET_RX_CLK;
input	[3:0]	HPS_ENET_RX_DATA;
input			HPS_ENET_RX_DV;
output	[3:0]	HPS_ENET_TX_DATA;
output			HPS_ENET_TX_EN;
inout			HPS_GSENSOR_INT;
inout			HPS_I2C0_SCLK;
inout			HPS_I2C0_SDAT;
inout			HPS_KEY_N;
inout			HPS_LED;
inout	[3:0]	HPS_LTC_GPIO;
inout			HPS_LTC_GPIO_ENABLE_N;
output			HPS_SD_CLK;
inout			HPS_SD_CMD;
inout	[3:0]	HPS_SD_DATA;
input			HPS_UART_RX;
output			HPS_UART_TX;
input			HPS_USB_CLKOUT;
inout	[7:0]	HPS_USB_DATA;
input			HPS_USB_DIR;
input			HPS_USB_NXT;
output			HPS_USB_STP;
input	[1:0]	KEY_N;
output	[7:0]	LED;
output	[88:1]	PIEZO;
input			ADC_CONVST;
input			ADC_SCK;
input			ADC_SDI;
input			ADC_SDO;
input			ARDUINO_IO_0;
input			ARDUINO_IO_1;
input			ARDUINO_IO_2;
input			ARDUINO_IO_3;
input			ARDUINO_IO_4;
input			ARDUINO_IO_5;
input			ARDUINO_IO_6;
input			ARDUINO_IO_7;
input			ARDUINO_IO_8;
input			ARDUINO_IO_9;
input			ARDUINO_IO_10;
input			ARDUINO_IO_11;
input			ARDUINO_IO_12;
input			ARDUINO_IO_13;
input			ARDUINO_IO_14;
input			ARDUINO_IO_15;
input			ARDUINO_RESET_N;
input			FPGA_CLK2_50;
input			FPGA_CLK3_50;
input			HPS_DDR3_ADDR_0;
input			HPS_DDR3_ADDR_1;
input			HPS_DDR3_ADDR_2;
input			HPS_DDR3_ADDR_3;
input			HPS_DDR3_ADDR_4;
input			HPS_DDR3_ADDR_5;
input			HPS_DDR3_ADDR_6;
input			HPS_DDR3_ADDR_7;
input			HPS_DDR3_ADDR_8;
input			HPS_DDR3_ADDR_9;
input			HPS_DDR3_ADDR_10;
input			HPS_DDR3_ADDR_11;
input			HPS_DDR3_ADDR_12;
input			HPS_DDR3_ADDR_13;
input			HPS_DDR3_ADDR_14;
input			HPS_DDR3_BA_0;
input			HPS_DDR3_BA_1;
input			HPS_DDR3_BA_2;
input			HPS_DDR3_DM_0;
input			HPS_DDR3_DM_1;
input			HPS_DDR3_DM_2;
input			HPS_DDR3_DM_3;
input			HPS_DDR3_DQ_0;
input			HPS_DDR3_DQ_1;
input			HPS_DDR3_DQ_2;
input			HPS_DDR3_DQ_3;
input			HPS_DDR3_DQ_4;
input			HPS_DDR3_DQ_5;
input			HPS_DDR3_DQ_6;
input			HPS_DDR3_DQ_7;
input			HPS_DDR3_DQ_8;
input			HPS_DDR3_DQ_9;
input			HPS_DDR3_DQ_10;
input			HPS_DDR3_DQ_11;
input			HPS_DDR3_DQ_12;
input			HPS_DDR3_DQ_13;
input			HPS_DDR3_DQ_14;
input			HPS_DDR3_DQ_15;
input			HPS_DDR3_DQ_16;
input			HPS_DDR3_DQ_17;
input			HPS_DDR3_DQ_18;
input			HPS_DDR3_DQ_19;
input			HPS_DDR3_DQ_20;
input			HPS_DDR3_DQ_21;
input			HPS_DDR3_DQ_22;
input			HPS_DDR3_DQ_23;
input			HPS_DDR3_DQ_24;
input			HPS_DDR3_DQ_25;
input			HPS_DDR3_DQ_26;
input			HPS_DDR3_DQ_27;
input			HPS_DDR3_DQ_28;
input			HPS_DDR3_DQ_29;
input			HPS_DDR3_DQ_30;
input			HPS_DDR3_DQ_31;
input			HPS_DDR3_DQS_N_0;
input			HPS_DDR3_DQS_N_1;
input			HPS_DDR3_DQS_N_2;
input			HPS_DDR3_DQS_N_3;
input			HPS_DDR3_DQS_P_0;
input			HPS_DDR3_DQS_P_1;
input			HPS_DDR3_DQS_P_2;
input			HPS_DDR3_DQS_P_3;
input			HPS_ENET_RX_DATA_0;
input			HPS_ENET_RX_DATA_1;
input			HPS_ENET_RX_DATA_2;
input			HPS_ENET_RX_DATA_3;
input			HPS_ENET_TX_DATA_0;
input			HPS_ENET_TX_DATA_1;
input			HPS_ENET_TX_DATA_2;
input			HPS_ENET_TX_DATA_3;
input			HPS_I2C1_SCLK;
input			HPS_I2C1_SDAT;
input			HPS_SD_DATA_0;
input			HPS_SD_DATA_1;
input			HPS_SD_DATA_2;
input			HPS_SD_DATA_3;
input			HPS_SPIM_CLK;
input			HPS_SPIM_MISO;
input			HPS_SPIM_MOSI;
input			HPS_SPIM_SS;
input			HPS_USB_DATA_0;
input			HPS_USB_DATA_1;
input			HPS_USB_DATA_2;
input			HPS_USB_DATA_3;
input			HPS_USB_DATA_4;
input			HPS_USB_DATA_5;
input			HPS_USB_DATA_6;
input			HPS_USB_DATA_7;
input			KEY_N_0;
input			KEY_N_1;
input			LED_0;
input			LED_1;
input			LED_2;
input			LED_3;
input			LED_4;
input			LED_5;
input			LED_6;
input			LED_7;
input			SW_0;
input			SW_1;
input			SW_2;
input			SW_3;
input			GPIO_0_0;
input			GPIO_0_1;
input			GPIO_0_2;
input			GPIO_0_3;
input			GPIO_0_4;
input			GPIO_0_5;
input			GPIO_0_6;
input			GPIO_0_7;
input			GPIO_0_8;
input			GPIO_0_9;
input			GPIO_0_10;
input			GPIO_0_11;
input			GPIO_0_12;
input			GPIO_0_13;
input			GPIO_0_14;
input			GPIO_0_15;
input			GPIO_0_16;
input			GPIO_0_17;
input			GPIO_0_18;
input			GPIO_0_19;
input			GPIO_0_20;
input			GPIO_0_21;
input			GPIO_0_22;
input			GPIO_0_23;
input			GPIO_0_24;
input			GPIO_0_25;
input			GPIO_0_26;
input			GPIO_0_27;
input			GPIO_0_28;
input			GPIO_0_29;
input			GPIO_0_30;
input			GPIO_0_31;
input			GPIO_0_32;
input			GPIO_0_33;
input			GPIO_0_34;
input			GPIO_0_35;
input			GPIO_1_0;
input			GPIO_1_1;
input			GPIO_1_2;
input			GPIO_1_3;
input			GPIO_1_4;
input			GPIO_1_5;
input			GPIO_1_6;
input			GPIO_1_7;
input			GPIO_1_8;
input			GPIO_1_9;
input			GPIO_1_10;
input			GPIO_1_11;
input			GPIO_1_12;
input			GPIO_1_13;
input			GPIO_1_14;
input			GPIO_1_15;
input			GPIO_1_16;
input			GPIO_1_17;
input			GPIO_1_18;
input			GPIO_1_19;
input			GPIO_1_20;
input			GPIO_1_21;
input			GPIO_1_22;
input			GPIO_1_23;
input			GPIO_1_24;
input			GPIO_1_25;
input			GPIO_1_26;
input			GPIO_1_27;
input			GPIO_1_28;
input			GPIO_1_29;
input			GPIO_1_30;
input			GPIO_1_31;
input			GPIO_1_32;
input			GPIO_1_33;
input			GPIO_1_34;
input			GPIO_1_35;
input			PIEZO_1;
input			PIEZO_2;
input			PIEZO_3;
input			PIEZO_4;
input			PIEZO_5;
input			PIEZO_6;
input			PIEZO_7;
input			PIEZO_8;
input			PIEZO_9;
input			PIEZO_10;
input			PIEZO_11;
input			PIEZO_12;
input			PIEZO_13;
input			PIEZO_14;
input			PIEZO_15;
input			PIEZO_16;
input			PIEZO_17;
input			PIEZO_18;
input			PIEZO_19;
input			PIEZO_20;
input			PIEZO_21;
input			PIEZO_22;
input			PIEZO_23;
input			PIEZO_24;
input			PIEZO_25;
input			PIEZO_26;
input			PIEZO_27;
input			PIEZO_28;
input			PIEZO_29;
input			PIEZO_30;
input			PIEZO_31;
input			PIEZO_32;
input			PIEZO_33;
input			PIEZO_34;
input			PIEZO_35;
input			PIEZO_36;
input			PIEZO_37;
input			PIEZO_38;
input			PIEZO_39;
input			PIEZO_40;
input			PIEZO_41;
input			PIEZO_42;
input			PIEZO_43;
input			PIEZO_44;
input			PIEZO_45;
input			PIEZO_46;
input			PIEZO_47;
input			PIEZO_48;
input			PIEZO_49;
input			PIEZO_50;
input			PIEZO_51;
input			PIEZO_52;
input			PIEZO_53;
input			PIEZO_54;
input			PIEZO_55;
input			PIEZO_56;
input			PIEZO_57;
input			PIEZO_58;
input			PIEZO_59;
input			PIEZO_60;
input			PIEZO_61;
input			PIEZO_62;
input			PIEZO_63;
input			PIEZO_64;
input			PIEZO_65;
input			PIEZO_66;
input			PIEZO_67;
input			PIEZO_68;
input			PIEZO_69;
input			PIEZO_70;
input			PIEZO_71;
input			PIEZO_72;
input			PIEZO_73;
input			PIEZO_74;
input			PIEZO_75;
input			PIEZO_76;
input			PIEZO_77;
input			PIEZO_78;
input			PIEZO_79;
input			PIEZO_80;
input			PIEZO_81;
input			PIEZO_82;
input			PIEZO_83;
input			PIEZO_84;
input			PIEZO_85;
input			PIEZO_86;
input			PIEZO_87;
input			PIEZO_88;
input			HPS_LTC_GPIO_0;
input			HPS_LTC_GPIO_1;
input			HPS_LTC_GPIO_2;
input			HPS_LTC_GPIO_3;
input			RTC_TRIGGER;
input	[0:15]	ARDUINO_IO;
input	[0:3]	SW;
input	[0:35]	GPIO_0;
input	[0:35]	GPIO_1;

// {ALTERA_IO_END} DO NOT REMOVE THIS LINE!
// {ALTERA_MODULE_BEGIN} DO NOT REMOVE THIS LINE!
// {ALTERA_MODULE_END} DO NOT REMOVE THIS LINE!
endmodule
