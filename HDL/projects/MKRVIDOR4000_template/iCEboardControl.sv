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
	reg signed [31:0] position[NUMBER_OF_MOTORS-1:0];
	// velocitys of the motors
	reg signed [31:0] velocity[NUMBER_OF_MOTORS-1:0];
	// currents of the motors
	reg signed [15:0] current[NUMBER_OF_MOTORS-1:0];
	// displacements of the springs
	reg signed [31:0] displacement[NUMBER_OF_MOTORS-1:0];

	assign readdata = returnvalue;
	assign waitrequest = (waitFlag && read);
	reg [31:0] returnvalue;
	reg waitFlag;
	
	reg [7:0] motor;

	always @(posedge clock, posedge reset) begin: AVALON_READ_INTERFACE
		if (reset == 1) begin
			waitFlag <= 1;
		end else begin
			waitFlag <= 1;
			if(read) begin
				case(address)
					8'h00: returnvalue <= motor;
					8'h01: returnvalue <= Kp[motor];
					8'h02: returnvalue <= Ki[motor];
					8'h03: returnvalue <= Kd[motor];
					8'h04: returnvalue <= position[motor];
					8'h05: returnvalue <= velocity[motor];
					8'h06: returnvalue <= displacement[motor];
					8'h07: returnvalue <= current[motor];
					8'h08: returnvalue <= PWMLimit[motor];
					8'h09: returnvalue <= IntegralLimit[motor];
					8'h0A: returnvalue <= deadBand[motor];
					8'h0B: returnvalue <= control_mode[motor];
					8'h0C: returnvalue <= sp[motor];
					default: returnvalue <= 32'hDEADBEEF;
				endcase
				if(waitFlag==1) begin // next clock cycle the returnvalue should be ready
					waitFlag <= 0;
				end
			end
		end
	end
		
	always @(posedge clock, posedge reset) begin: MYO_CONTROL_LOGIC
		integer i;
		if (reset == 1) begin
			for(i=0;i<NUMBER_OF_MOTORS;i=i+1) begin
				Kp[i] <= 8'hA+i;
				Ki[i] <= 8'hB+i;
				Kd[i] <= 8'hC+i;
				sp[i] <= 8'hD+i;
				PWMLimit[i] <= 8'hE+i;
				IntegralLimit[i] <= 8'hF+i;
			end
		end else begin
			// if we are writing via avalon bus and waitrequest is deasserted, write the respective register
			if(write && ~waitrequest) begin
				case(address)
					8'h00: motor <= writedata[31:0];
					8'h01: Kp[motor][31:0] <= writedata[31:0];
					8'h02: Ki[motor][31:0] <= writedata[31:0];
					8'h03: Kd[motor][31:0] <= writedata[31:0];
					8'h08: PWMLimit[motor][31:0] <= writedata[31:0];
					8'h09: IntegralLimit[motor][31:0] <= writedata[31:0];
					8'h0A: deadBand[motor][31:0] <= writedata[31:0];
					8'h0B: control_mode[motor][2:0] <= writedata[2:0];
					8'h0C: sp[motor][31:0] <= writedata[31:0];
				endcase
			end
		end 
	end
	
endmodule