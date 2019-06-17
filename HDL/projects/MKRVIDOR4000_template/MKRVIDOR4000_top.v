/*
* Copyright 2018 ARDUINO SA (http://www.arduino.cc/)
* This file is part of Vidor IP.
* Copyright (c) 2018
* Authors: Dario Pennisi
*
* This software is released under:
* The GNU General Public License, which covers the main part of 
* Vidor IP
* The terms of this license can be found at:
* https://www.gnu.org/licenses/gpl-3.0.en.html
*
* You can be released from the requirements of the above licenses by purchasing
* a commercial license. Buying such a license is mandatory if you want to modify or
* otherwise use the software for commercial activities involving the Arduino
* software without disclosing the source code of your own applications. To purchase
* a commercial license, send an email to license@arduino.cc.
*
*/

module MKRVIDOR4000_top
(
  // system signals
  input         iCLK,
  input         iRESETn,
  input         iSAM_INT,
  output        oSAM_INT,
  
  // SDRAM
  output        oSDRAM_CLK,
  output [11:0] oSDRAM_ADDR,
  output [1:0]  oSDRAM_BA,
  output        oSDRAM_CASn,
  output        oSDRAM_CKE,
  output        oSDRAM_CSn,
  inout  [15:0] bSDRAM_DQ,
  output [1:0]  oSDRAM_DQM,
  output        oSDRAM_RASn,
  output        oSDRAM_WEn,

  // SAM D21 PINS
  inout         bMKR_AREF,
  inout  [6:0]  bMKR_A,
  inout  [14:0] bMKR_D,
  
  // Mini PCIe
  inout         bPEX_RST,
  inout         bPEX_PIN6,
  inout         bPEX_PIN8,
  inout         bPEX_PIN10,
  input         iPEX_PIN11,
  inout         bPEX_PIN12,
  input         iPEX_PIN13,
  inout         bPEX_PIN14,
  inout         bPEX_PIN16,
  inout         bPEX_PIN20,
  input         iPEX_PIN23,
  input         iPEX_PIN25,
  inout         bPEX_PIN28,
  inout         bPEX_PIN30,
  input         iPEX_PIN31,
  inout         bPEX_PIN32,
  input         iPEX_PIN33,
  inout         bPEX_PIN42,
  inout         bPEX_PIN44,
  inout         bPEX_PIN45,
  inout         bPEX_PIN46,
  inout         bPEX_PIN47,
  inout         bPEX_PIN48,
  inout         bPEX_PIN49,
  inout         bPEX_PIN51,

  // NINA interface
  inout         bWM_PIO1,
  inout         bWM_PIO2,
  inout         bWM_PIO3,
  inout         bWM_PIO4,
  inout         bWM_PIO5,
  inout         bWM_PIO7,
  inout         bWM_PIO8,
  inout         bWM_PIO18,
  inout         bWM_PIO20,
  inout         bWM_PIO21,
  inout         bWM_PIO27,
  inout         bWM_PIO28,
  inout         bWM_PIO29,
  inout         bWM_PIO31,
  input         iWM_PIO32,
  inout         bWM_PIO34,
  inout         bWM_PIO35,
  inout         bWM_PIO36,
  input         iWM_TX,
  inout         oWM_RX,
  inout         oWM_RESET,

  // HDMI output
  output [2:0]  oHDMI_TX,
  output        oHDMI_CLK,

  inout         bHDMI_SDA,
  inout         bHDMI_SCL,
  
  input         iHDMI_HPD,
  
  // MIPI input
  input  [1:0]  iMIPI_D,
  input         iMIPI_CLK,
  inout         bMIPI_SDA,
  inout         bMIPI_SCL,
  inout  [1:0]  bMIPI_GP,

  // Q-SPI Flash interface
  output        oFLASH_SCK,
  output        oFLASH_CS,
  inout         oFLASH_MOSI,
  inout         iFLASH_MISO,
  inout         oFLASH_HOLD,
  inout         oFLASH_WP

);

// signal declaration

//=====nina esp32 programm interface===============
//DEF
wire iRx_header,iCts_header,iDtr_header;
wire oTx_header;
wire iTx_esp;
wire oRx_esp,oCts_esp,oDtr_esp;
wire iRESET_button,iBOOT_button;

//PIN - MAP
assign {iRESET_button,iBOOT_button} = {bMKR_AREF,bMKR_A[0]};
assign {iTx_esp,iRx_header,iCts_header,iDtr_header} = {iWM_TX,bMKR_D[13:11]};
assign {bMKR_D[14],oWM_RX,bWM_PIO27,oWM_RESET} = {oTx_header,oRx_esp,oCts_esp,oDtr_esp};

//LOGIC
assign oTx_header = iTx_esp;
assign oRx_esp   = iRx_header;
assign oCts_esp   = iBOOT_button;//(iBOOT_button == 1) ? iCts_header : 1'b0;
assign oDtr_esp   = iRESET_button;//(iRESET_button == 1) ? iDtr_header : 1'b0;
//=================================================
//assign bMKR_D[6] = 1'b1;
//=================================================



//=====nina esp32 spi avalon interface ============
//DEF
wire iSpiMOSI, iSpiClk, iSpiCS;
wire oSpiMISO;

//PIN - MAP
assign {iSpiMOSI,iSpiClk,iSpiCS} = {bWM_PIO1,bWM_PIO29,bWM_PIO28};
//assign {bMKR_D[8],bMKR_D[9],bMKR_D[7]} = {bWM_PIO1,bWM_PIO29,bWM_PIO28};

assign bWM_PIO21 = oSpiMISO;
//assign bMKR_D[10] = oSpiMISO;
/*
//=====arduino spi avalon interface ============
wire iSpiMOSI, iSpiClk, iSpiCS;
wire oSpiMISO;

assign {iSpiMOSI,iSpiClk,iSpiCS} = {bMKR_D[8],bMKR_D[9],bMKR_D[7]};

assign bMKR_D[10] = oSpiMISO;
*/
//=================================================

//=====ID SWITCH interface =======
//DEF
wire	[3:0]	sw; 
//PIN - MAP
assign sw = bMKR_A[5:2];
//=================================================

 vidor_sys u0 (
	  .clk_clk       	(iCLK),       //      clk.clk
	  .reset_reset_n 	(iRESETn), //    reset.reset_n
	  
	  .spi_bridge_mosi_to_the_spislave_inst_for_spichain 				(iSpiMOSI), // spislave.mosi
	  .spi_bridge_nss_to_the_spislave_inst_for_spichain  				(iSpiCS),  //         .nss
	  .spi_bridge_miso_to_and_from_the_spislave_inst_for_spichain 	(oSpiMISO), //         .miso
	  .spi_bridge_sclk_to_the_spislave_inst_for_spichain 	(iSpiClk),  //         .sclk
	  
	  
	  //.spi_MISO      (oSpiMISO),      //       spi.MISO
	  //.spi_MOSI      (iSpiMOSI),      //          .MOSI
	  //.spi_SCLK      (iSpiClk),      //          .SCLK
	  //.spi_SS_n      (iSpiCS)       //          .SS_n

	  .id_switch_debug_out1 (bMKR_D[6]),
	  .id_switch_sw	(sw[3:0]),
	  //.id_switch_debug_out1 (bMKR_D[6]),
	  .id_switch1_sw	(sw[3:0])
	  
 );
 
 //=====debug test ============DELETE WHEN DONE====
 
 //=================================================
 


wire        wOSC_CLK;

wire        wCLK8,wCLK24, wCLK64, wCLK120;

wire [31:0] wJTAG_ADDRESS, wJTAG_READ_DATA, wJTAG_WRITE_DATA, wDPRAM_READ_DATA;
wire        wJTAG_READ, wJTAG_WRITE, wJTAG_WAIT_REQUEST, wJTAG_READ_DATAVALID;
wire [4:0]  wJTAG_BURST_COUNT;
wire        wDPRAM_CS;

wire [7:0]  wDVI_RED,wDVI_GRN,wDVI_BLU;
wire        wDVI_HS, wDVI_VS, wDVI_DE;

wire        wVID_CLK, wVID_CLKx5;
wire        wMEM_CLK;

assign wVID_CLK   = wCLK24;
assign wVID_CLKx5 = wCLK120;
assign wCLK8      = iCLK;

// internal oscillator
cyclone10lp_oscillator   osc
  ( 
  .clkout(wOSC_CLK),
  .oscena(1'b1));

// system PLL
SYSTEM_PLL PLL_inst(
  .areset(1'b0),
  .inclk0(wCLK8),
  .c0(wCLK24),
  .c1(wCLK120),
  .c2(wMEM_CLK),
   .c3(oSDRAM_CLK),
  .c4(wFLASH_CLK),
   
  .locked());


reg [5:0] rRESETCNT;

always @(posedge wMEM_CLK)
begin
  if (!rRESETCNT[5])
  begin
  rRESETCNT<=rRESETCNT+1;
  end
end

endmodule
