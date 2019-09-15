module coms #(parameter NUMBER_OF_MOTORS = 6, parameter CLK_FREQ_HZ = 50_000_000, parameter BAUDRATE = 115200)(
	input CLK,
	input reset,
	output tx_o,
	output tx_enable,
	input rx_i,
	output signed [31:0] position[NUMBER_OF_MOTORS-1:0],
	output signed [31:0] velocity[NUMBER_OF_MOTORS-1:0],
	output signed [31:0] displacement[NUMBER_OF_MOTORS-1:0],
	output [15:0] current[NUMBER_OF_MOTORS-1:0],
	input reg signed [31:0] setpoint[NUMBER_OF_MOTORS-1:0],
	input reg [7:0] control_mode[NUMBER_OF_MOTORS-1:0]
);

	localparam  MAX_FRAME_LENGTH = 21;

	reg[7:0] byte_transmit_counter ;
	reg [15:0] data ;
	reg[7:0] data_out[MAX_FRAME_LENGTH-1:0];
	wire [7:0] tx_data ;
	wire tx_active ;
	wire tx_done ;
	reg tx_transmit ;


////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1999-2008 Easics NV.
// This source file may be used and distributed without restriction
// provided that this copyright statement is not removed from the file
// and that any derivative work contains the original copyright notice
// and the associated disclaimer.
//
// THIS SOURCE FILE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS
// OR IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
// WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// Purpose : synthesizable CRC function
//   * polynomial: x^16 + x^15 + x^2 + 1
//   * data width: 8
//
// Info : tools@easics.be
//        http://www.easics.com
////////////////////////////////////////////////////////////////////////////////

// polynomial: x^16 + x^15 + x^2 + 1
// data width: 8
// convention: the first serial bit is D[7]
function [15:0] nextCRC16_D8;

	input [7:0] Data;
	input [15:0] crc;
	reg [7:0] d;
	reg [15:0] c;
	reg [15:0] newcrc;
	begin
		d = Data;
		c = crc;

		newcrc[0] = d[7] ^ d[6] ^ d[5] ^ d[4] ^ d[3] ^ d[2] ^ d[1] ^ d[0] ^ c[8] ^ c[9] ^ c[10] ^ c[11] ^ c[12] ^ c[13] ^ c[14] ^ c[15];
		newcrc[1] = d[7] ^ d[6] ^ d[5] ^ d[4] ^ d[3] ^ d[2] ^ d[1] ^ c[9] ^ c[10] ^ c[11] ^ c[12] ^ c[13] ^ c[14] ^ c[15];
		newcrc[2] = d[1] ^ d[0] ^ c[8] ^ c[9];
		newcrc[3] = d[2] ^ d[1] ^ c[9] ^ c[10];
		newcrc[4] = d[3] ^ d[2] ^ c[10] ^ c[11];
		newcrc[5] = d[4] ^ d[3] ^ c[11] ^ c[12];
		newcrc[6] = d[5] ^ d[4] ^ c[12] ^ c[13];
		newcrc[7] = d[6] ^ d[5] ^ c[13] ^ c[14];
		newcrc[8] = d[7] ^ d[6] ^ c[0] ^ c[14] ^ c[15];
		newcrc[9] = d[7] ^ c[1] ^ c[15];
		newcrc[10] = c[2];
		newcrc[11] = c[3];
		newcrc[12] = c[4];
		newcrc[13] = c[5];
		newcrc[14] = c[6];
		newcrc[15] = d[7] ^ d[6] ^ d[5] ^ d[4] ^ d[3] ^ d[2] ^ d[1] ^ d[0] ^ c[7] ^ c[8] ^ c[9] ^ c[10] ^ c[11] ^ c[12] ^ c[13] ^ c[14] ^ c[15];
		nextCRC16_D8 = newcrc;
	end
endfunction

	localparam  MAGIC_NUMBER_LENGTH = 4;
	localparam  STATUS_REQUEST_FRAME_MAGICNUMBER = 32'h1CE1CEBB;
	localparam	STATUS_REQUEST_FRAME_LENGTH = 7;
	localparam 	STATUS_FRAME_MAGICNUMBER = 32'h1CEB00DA;
	localparam  STATUS_FRAME_LENGTH = 21;
	localparam 	SETPOINT_FRAME_MAGICNUMBER = 32'hD0D0D0D0;
	localparam  SETPOINT_FRAME_LENGTH = 11;
	localparam 	CONTROL_MODE_FRAME_MAGICNUMBER = 32'hBAADA555;
	localparam  CONTROL_MODE_FRAME_LENGTH = 8;

	assign tx_data = data_out[byte_transmit_counter];

	uart_tx #(CLK_FREQ_HZ,BAUDRATE) tx(CLK,tx_transmit,tx_data,tx_active,tx_o,tx_enable,tx_done);

	reg [15:0] tx_crc ;

	wire [(MAX_FRAME_LENGTH-2)*8-1:0] data_out_field ;
	genvar j;
	generate
	for(j=MAGIC_NUMBER_LENGTH;j<MAX_FRAME_LENGTH;j=j+1) begin: DATA_OUT_FIELD// without MAGICNUMBER
	  assign data_out_field[(8*((j-MAGIC_NUMBER_LENGTH)+1))-1:(8*(j-MAGIC_NUMBER_LENGTH))] = data_out[j];
	end
	endgenerate


	reg [13:0]delay_counter;
	reg tx_active_prev;
	always @(posedge CLK, posedge reset) begin: UART_TRANSMITTER
		localparam IDLE=8'h0, PREPARE_CONTROL_MODE = 8'h1, SEND_CONTROL_MODE = 8'h2, PREPARE_SETPOINT  = 8'h3, SEND_SETPOINT = 8'h4,
				PREPARE_STATUS_REQUEST = 8'h5, SEND_STATUS_REQUEST = 8'h6;
		reg [7:0] state;
		reg [7:0] motor;
		integer i;
		if(reset) begin
			state = IDLE;
		end else begin
			tx_active_prev <= tx_active;
			tx_transmit <= 0;
			case(state)
				IDLE: begin
					if(motor<NUMBER_OF_MOTORS-1) begin
						motor <= motor +1;
					end else begin
						motor <= 0;
					end
					state = PREPARE_CONTROL_MODE;
				end
				PREPARE_CONTROL_MODE: begin
					data_out[0] = CONTROL_MODE_FRAME_MAGICNUMBER[31:24];
					data_out[1] = CONTROL_MODE_FRAME_MAGICNUMBER[23:16];
					data_out[2] = CONTROL_MODE_FRAME_MAGICNUMBER[15:8];
					data_out[3] = CONTROL_MODE_FRAME_MAGICNUMBER[7:0];
					data_out[4] = motor; // motor id
					data_out[5] = control_mode[motor]; // control_mode
					tx_crc = 16'hFFFF;
					for(i=0;i<CONTROL_MODE_FRAME_LENGTH-2;i++) begin
						tx_crc = nextCRC16_D8(data_out[i],tx_crc);
					end
					data_out[CONTROL_MODE_FRAME_LENGTH-2] = tx_crc[15:8];
					data_out[CONTROL_MODE_FRAME_LENGTH-1] = tx_crc[7:0];
					byte_transmit_counter = 0;
					state = SEND_CONTROL_MODE;
				end
				SEND_CONTROL_MODE: begin
					if(!tx_active && tx_active_prev)begin
						byte_transmit_counter = byte_transmit_counter+1;
					end
					if(!tx_active && !tx_transmit)begin
						if(byte_transmit_counter<CONTROL_MODE_FRAME_LENGTH)begin
							tx_transmit <= 1;
						end else begin
							state = PREPARE_SETPOINT;
						end
					end
				end
				PREPARE_SETPOINT: begin
					data_out[0] = SETPOINT_FRAME_MAGICNUMBER[31:24];
					data_out[1] = SETPOINT_FRAME_MAGICNUMBER[23:16];
					data_out[2] = SETPOINT_FRAME_MAGICNUMBER[15:8];
					data_out[3] = SETPOINT_FRAME_MAGICNUMBER[7:0];
					data_out[4] = motor; // motor id
					data_out[5] = setpoint[0][31:24];
					data_out[6] = setpoint[0][23:16];
					data_out[7] = setpoint[0][15:8];
					data_out[8] = setpoint[0][7:0];
					tx_crc = 16'hFFFF;
					for(i=0;i<SETPOINT_FRAME_LENGTH-2;i++) begin
						tx_crc = nextCRC16_D8(data_out[i],tx_crc);
					end
					data_out[SETPOINT_FRAME_LENGTH-2] = tx_crc[15:8];
					data_out[SETPOINT_FRAME_LENGTH-1] = tx_crc[7:0];
					byte_transmit_counter = 0;
					state = SEND_SETPOINT;
				end
				SEND_SETPOINT: begin
					if(!tx_active && tx_active_prev)begin
						byte_transmit_counter = byte_transmit_counter+1;
					end
					if(!tx_active && !tx_transmit)begin
						if(byte_transmit_counter<SETPOINT_FRAME_LENGTH)begin
							tx_transmit <= 1;
						end else begin
							state = PREPARE_STATUS_REQUEST;
						end
					end
				end
				PREPARE_STATUS_REQUEST: begin
					data_out[0] = STATUS_REQUEST_FRAME_MAGICNUMBER[31:24];
					data_out[1] = STATUS_REQUEST_FRAME_MAGICNUMBER[23:16];
					data_out[2] = STATUS_REQUEST_FRAME_MAGICNUMBER[15:8];
					data_out[3] = STATUS_REQUEST_FRAME_MAGICNUMBER[7:0];
					data_out[4] = motor; // motor id
					tx_crc = 16'hFFFF;
					for(i=0;i<STATUS_REQUEST_FRAME_LENGTH-2;i++) begin
						tx_crc = nextCRC16_D8(data_out[i],tx_crc);
					end
					data_out[STATUS_REQUEST_FRAME_LENGTH-2] = tx_crc[15:8];
					data_out[STATUS_REQUEST_FRAME_LENGTH-1] = tx_crc[7:0];
					byte_transmit_counter = 0;
					delay_counter = CLK_FREQ_HZ/BAUDRATE*MAX_FRAME_LENGTH*8*8;
					state = SEND_STATUS_REQUEST;
				end
				SEND_STATUS_REQUEST: begin
					if(!tx_active && tx_active_prev)begin
						byte_transmit_counter = byte_transmit_counter+1;
					end
					if(!tx_active && !tx_transmit)begin
						if(byte_transmit_counter<STATUS_REQUEST_FRAME_LENGTH)begin
							tx_transmit <= 1;
						end else begin
							if(delay_counter==0) begin // we have to wait until the bus is free
								byte_transmit_counter = 0;
								state = IDLE;
							end else begin
							  delay_counter = delay_counter - 1;
							end
						end
					end
				end
			endcase
		end
	end

	wire rx_data_ready;
	wire [7:0] rx_data ;

	uart_rx #(CLK_FREQ_HZ,BAUDRATE) rx(CLK,rx_i,rx_data_ready,rx_data);

	reg [7:0] data_in[MAX_FRAME_LENGTH-1:0];
	reg [7:0] data_in_frame[MAX_FRAME_LENGTH-1:0];

	reg [15:0] rx_crc ;

	wire [MAX_FRAME_LENGTH*8-1:0] data_in_field ;
	generate
		for(j=1;j<MAX_FRAME_LENGTH;j=j+1) begin: DATA_IN_FIELD
		  assign data_in_field[(8*j)-1:(8*(j-1))] = data_in_frame[j];
		end
	endgenerate

	always @(posedge CLK, posedge reset) begin: FRAME_MATCHER
		localparam IDLE = 8'h0, RECEIVE_STATUS = 8'h1, CHECK_CRC_STATUS = 8'h2;
		integer state;
		integer next_state;
		integer i, j;
		if(reset) begin
			state <= IDLE;
			i <= 0;
		end else begin
			if(rx_data_ready)begin
			  data_in[MAGIC_NUMBER_LENGTH-1] <= rx_data;
			  for(j=MAGIC_NUMBER_LENGTH-2;j>=0;j=j-1)begin
					data_in[j] <= data_in[j+1];
			  end
			end
			if({data_in[0],data_in[1],data_in[2],data_in[3]}==STATUS_FRAME_MAGICNUMBER)begin
			 	state <= RECEIVE_STATUS;
			end
			case(state)
				IDLE: begin
					i <= 0;
				end
				RECEIVE_STATUS: begin
					if(rx_data_ready)begin
						data_in_frame[i] = rx_data;
						i <= i+1;
					end
					if(i>STATUS_FRAME_LENGTH-MAGIC_NUMBER_LENGTH-1) begin
						state <= CHECK_CRC_STATUS;
					end
				end
				CHECK_CRC_STATUS: begin
					rx_crc = nextCRC16_D8(data_in_field,16'hFFFF);
					if(rx_crc[15:8]==data_in_frame[SETPOINT_FRAME_LENGTH-MAGIC_NUMBER_LENGTH-2]
						  && rx_crc[7:0]==data_in_frame[SETPOINT_FRAME_LENGTH-MAGIC_NUMBER_LENGTH-1]) begin // MATCH!
						position[data_in_field[0]][31:24] <= data_in_field[1];
						position[data_in_field[0]][23:16] <= data_in_field[2];
						position[data_in_field[0]][15:8] <= data_in_field[3];
						position[data_in_field[0]][7:0] <= data_in_field[4];
						velocity[data_in_field[0]][31:24] <= data_in_field[5];
						velocity[data_in_field[0]][23:16] <= data_in_field[6];
						velocity[data_in_field[0]][15:8] <= data_in_field[7];
						velocity[data_in_field[0]][7:0] <= data_in_field[8];
						displacement[data_in_field[0]][31:24] <= data_in_field[9];
						displacement[data_in_field[0]][23:16] <= data_in_field[10];
						displacement[data_in_field[0]][15:8] <= data_in_field[11];
						displacement[data_in_field[0]][7:0] <= data_in_field[12];
						current[data_in_field[0]][15:8] <= data_in_field[13];
						current[data_in_field[0]][7:0] <= data_in_field[14];
					end else begin
						state <= IDLE;
					end
				end
			endcase
		end
	end

endmodule
