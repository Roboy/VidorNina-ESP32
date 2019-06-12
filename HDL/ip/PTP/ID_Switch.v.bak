module id_switch ( 
		input 	clock,
		input 	reset,
		
		// this is for the avalon interface
		input [15:0] 							avalon_slave_address,
		input 											avalon_slave_write,
		input signed 	[31:0] 	avalon_slave_writedata,
		input 											avalon_slave_read,
		output signed  [31:0] 	avalon_slave_readdata,
		output 										avalon_slave_waitrequest,
		
		input	[3:0]	sw 
);
// the following iterface handles read requests via lightweight axi bridge
	// the upper 8 bit of the read address define which value we want to read
	// the lower 8 bit of the read address define for which motor	
	reg avalon_slave_waitFlag;
	reg [31:0] returnvalue;
	assign avalon_slave_readdata = returnvalue;
	assign avalon_slave_waitrequest = (avalon_slave_waitFlag && avalon_slave_read);
	always @(posedge clock, posedge reset) begin: AVALON_READ_INTERFACE
		if (reset == 1) begin
			avalon_slave_waitFlag <= 1;
		end else begin
			avalon_slave_waitFlag <= 1;
			if(avalon_slave_read) begin
				case(avalon_slave_address>>8)
					8'h00: returnvalue <= sw[3:0];
					8'h01: returnvalue <= 32'd2; //DELETE DEBUG STUFF
					default: returnvalue <= 32'hDEADBEEF;
				endcase
				if(avalon_slave_waitFlag==1) begin // next clock cycle the returnvalue should be ready
					avalon_slave_waitFlag <= 0;
				end
			end
		end
	end
	
	
	/*always @(posedge clock, posedge reset) begin: AVALON_WRITE_INTERFACE
		if (reset == 1) begin
		end else begin
			// if we are writing via avalon bus and waitrequest is deasserted, write the respective register
			if(avalon_slave_write && ~avalon_slave_waitrequest) begin
				case(avalon_slave_address>>8)
					//8'h00: time_cnt <= avalon_slave_writedata[31:0];
					//8'h02: waitflag_trigger <= (avalon_slave_writedata!=0);
				endcase
			end
		end 
	end*/
endmodule
