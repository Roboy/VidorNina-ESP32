module id_switch ( 
		input 	clock,
		input 	reset,
		
		// this is for the avalon interface
		input [15:0] 				avalon_slave_address,
		input 						avalon_slave_write,
		input signed 	[31:0] 	avalon_slave_writedata,
		input 						avalon_slave_read,
		output signed  [31:0] 	avalon_slave_readdata,
		output 						avalon_slave_waitrequest,
		
		output debug_out1,
		input	[3:0]	sw 
);
	//Debug stuff 
	
	
		//Debug stuff 
	reg [31:0] loopback [31:0];
	reg [31:0] foo_cnt;
	reg [31:0] foo_cnt2;
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
			foo_cnt <= 32'd15;
			foo_cnt2 <= 32'd20;
		end else begin
			avalon_slave_waitFlag <= 1;
			if(avalon_slave_read) begin
				case(avalon_slave_address>>8)
					8'h00: returnvalue <= foo_cnt2;//avalon_slave_address[15:0]; //foo_cnt; 
					8'h01: returnvalue <= foo_cnt;//avalon_slave_address[15:0]; 
					8'h02: returnvalue <= loopback[0];
					8'h03: returnvalue <= loopback[2];
					8'h04: returnvalue <= avalon_slave_address[15:0];  
					8'h05: returnvalue <= 32'd4294967295; 
					8'h06: returnvalue <= 32'd3; 
					8'h07: returnvalue <= 32'd3221225471; 
					8'h08: returnvalue <= 32'd3;  
					8'h09: returnvalue <= 32'd74; 
					8'h10: returnvalue <= 32'd3; 
					8'h11: returnvalue <= 32'd11; 
					8'h12: returnvalue <= 32'd3; 
					8'h13: returnvalue <= 32'd12;
					default: returnvalue <= 32'hFFFFFFFF;
				endcase
				//if (foo_cnt > 100) begin
				//	foo_cnt <= 32'd14;
				//end
				if(avalon_slave_waitFlag==1) begin // next clock cycle the returnvalue should be ready
					avalon_slave_waitFlag <= 0;
				end
			end
		end
	end
	
	
	always @(posedge clock, posedge reset) begin: AVALON_WRITE_INTERFACE
		if (reset == 1) begin
			loopback[0] <= 32'd1;
			debug_out1 <= 0;
		end else begin
			// if we are writing via avalon bus and waitrequest is deasserted, write the respective register
			if(avalon_slave_write && ~avalon_slave_waitrequest) begin
				case(avalon_slave_address>>8)
					8'h00: loopback[0] <= avalon_slave_writedata[31:0];
					8'h01: debug_out1 <= (avalon_slave_writedata!=0);
					8'h02: loopback[2] <= avalon_slave_writedata[31:0]; 
					8'h03: loopback[3] <= avalon_slave_writedata[31:0]; 
					8'h04: loopback[4] <= avalon_slave_writedata[31:0]; 
					8'h05: loopback[5] <= avalon_slave_writedata[31:0]; 
					8'h06: loopback[6] <= avalon_slave_writedata[31:0]; 
					8'h07: loopback[7] <= avalon_slave_writedata[31:0]; 
					8'h08: loopback[8] <= avalon_slave_writedata[31:0]; 
					8'h09: loopback[9] <= avalon_slave_writedata[31:0]; 
					8'h10: loopback[10] <= avalon_slave_writedata[31:0]; 
					8'h11: loopback[11] <= avalon_slave_writedata[31:0]; 
					8'h12: loopback[12] <= avalon_slave_writedata[31:0]; 
					8'h13: loopback[13] <= avalon_slave_writedata[31:0]; 
					//8'h02: waitflag_trigger <= (avalon_slave_writedata!=0);
				endcase
			end
		end 
	end
	/*
	reg [31:0] loopback;
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
					8'h01: returnvalue <= loopback; //DELETE DEBUG STUFF
					default: returnvalue <= 32'hDEADBEEF;
				endcase
				if(avalon_slave_waitFlag==1) begin // next clock cycle the returnvalue should be ready
					avalon_slave_waitFlag <= 0;
				end
			end
		end
	end
	
	
	always @(posedge clock, posedge reset) begin: AVALON_WRITE_INTERFACE
		if (reset == 1) begin
			loopback <= 32'd2;
		end else begin
			// if we are writing via avalon bus and waitrequest is deasserted, write the respective register
			if(avalon_slave_write && ~avalon_slave_waitrequest) begin
				case(avalon_slave_address>>8)
					8'h01: loopback <= avalon_slave_writedata[31:0];
					//8'h02: waitflag_trigger <= (avalon_slave_writedata!=0);
				endcase
			end
		end 
	end
	*/
endmodule
