module ICEboardControl (
		input clock,
		input reset,
		// this is for the avalon interface
		input [15:0] address,
		input write,
		input signed [31:0] writedata,
		input read,
		output signed [31:0] readdata,
		output waitrequest,
		input rx,
		output tx
);
	
	parameter NUMBER_OF_MOTORS = 6;
	parameter CLOCK_SPEED_HZ = 50_000_000;
	
	// gains and shit
	// p gains
	reg signed [31:0] Kp[NUMBER_OF_MOTORS-1:0];
	// i gains
	reg signed [31:0] Ki[NUMBER_OF_MOTORS-1:0];
	// d gains
	reg signed [31:0] Kd[NUMBER_OF_MOTORS-1:0];
	// setpoints
	reg signed [31:0] sp[NUMBER_OF_MOTORS-1:0];
	// pwm limit
	reg signed [31:0] PWMLimit[NUMBER_OF_MOTORS-1:0];
	// integral negative limits
	reg signed [31:0] IntegralLimit[NUMBER_OF_MOTORS-1:0];
	// deadband
	reg signed [31:0] deadBand[NUMBER_OF_MOTORS-1:0];
	// control mode
	reg [2:0] control_mode[NUMBER_OF_MOTORS-1:0];

	// the following is stuff we receive from the motors via uart
	// positions of the motors
	reg signed [31:0] positions[NUMBER_OF_MOTORS-1:0];
	// velocitys of the motors
	reg signed [31:0] velocitys[NUMBER_OF_MOTORS-1:0];
	// currents of the motors
	reg signed [15:0] currents[NUMBER_OF_MOTORS-1:0];
	// displacements of the springs
	reg signed [31:0] displacements[NUMBER_OF_MOTORS-1:0];

	assign readdata = returnvalue;
	assign waitrequest = (waitFlag && read);
	reg [31:0] returnvalue;
	reg waitFlag;
	
	// the following iterface handles read requests via lightweight axi bridge
	// the upper 8 bit of the read address define which value we want to read
	// the lower 8 bit of the read address define for which motor
	always @(posedge clock, posedge reset) begin: AVALON_READ_INTERFACE
		if (reset == 1) begin
			waitFlag <= 1;
		end else begin
			waitFlag <= 1;
			if(read) begin
				case(address>>8)
					8'h00: returnvalue <= Kp[address[7:0]][31:0];
					8'h01: returnvalue <= Ki[address[7:0]][31:0];
					8'h02: returnvalue <= Kd[address[7:0]][31:0];
					8'h03: returnvalue <= sp[address[7:0]][31:0];
					8'h05: returnvalue <= PWMLimit[address[7:0]][31:0];
					8'h07: returnvalue <= IntegralLimit[address[7:0]][31:0];
					8'h09: returnvalue <= deadBand[address[7:0]][31:0];
					8'h0A: returnvalue <= control_mode[address[7:0]][2:0];
					8'h0B: returnvalue <= positions[address[7:0]][31:0];
					8'h0C: returnvalue <= velocitys[address[7:0]][15:0];
					8'h0D: returnvalue <= currents[address[7:0]][15:0];
					8'h0E: returnvalue <= displacements[address[7:0]][31:0];
					default: returnvalue <= 32'hDEADBEEF;
				endcase
				if(waitFlag==1) begin // next clock cycle the returnvalue should be ready
					waitFlag <= 0;
				end
			end
		end
	end
		
	reg [7:0] motor;
	reg [7:0] pid_update;
	reg [31:0] spi_enable_counter;
		
	always @(posedge clock, posedge reset) begin: MYO_CONTROL_LOGIC
		if (reset == 1) begin

		end else begin
			// if we are writing via avalon bus and waitrequest is deasserted, write the respective register
			if(write && ~waitrequest) begin
				if((address>>8)<=8'h13 && address[7:0]<NUMBER_OF_MOTORS) begin
					case(address>>8)
						8'h00: Kp[address[7:0]][31:0] <= writedata[31:0];
						8'h01: Ki[address[7:0]][31:0] <= writedata[31:0];
						8'h02: Kd[address[7:0]][31:0] <= writedata[31:0];
						8'h03: sp[address[7:0]][31:0] <= writedata[31:0];
						8'h05: PWMLimit[address[7:0]][31:0] <= writedata[31:0];
						8'h07: IntegralLimit[address[7:0]][31:0] <= writedata[31:0];
						8'h09: deadBand[address[7:0]][31:0] <= writedata[31:0];
						8'h0A: control_mode[address[7:0]][2:0] <= writedata[2:0];
					endcase
				end
			end
		end 
	end
	
endmodule