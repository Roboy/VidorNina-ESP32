module rtc ( 
	input clock,
	input reset,
	input event_trigger,
	input event_trigger2,
	// this is for the avalon interface
	input [15:0] avalon_slave_address,
	input avalon_slave_write,
	input signed [31:0] avalon_slave_writedata,
	input avalon_slave_read,
	output signed [31:0] avalon_slave_readdata,
	output avalon_slave_waitrequest,
	// trigger out
	output wire piezo_enable
);

//TODO add two regs one for the amount of cycles to be bursted out and one enable a burst
	
	//definition
	parameter CLOCK_SPEED_HZ = 50_000_000; //-> 20ns per cloc  ->so the rsolution was choosen 100ns
	parameter RTC_RESOLUTION = 100;//-> 20ns per cloc  ->so the rsolution was choosen 100ns
	
   //reg def
	reg [31:0] time_cnt;
	reg [31:0] rtc_trigger_data;
	reg [31:0] rtc_trigger_data2;
	
	reg [31:0] US_output_time;
	reg US_out_trigger;
	
	reg [31:0] burst_cycles_def;
	reg [31:0] burst_cycles_cnt;
	reg burst_enable;
	
	reg waitflag_status;
	reg waitflag_trigger;
	
	wire piezo_output_enable;
	assign piezo_output_enable = US_out_trigger | burst_enable;
	
	//wires
	wire clock_div;
	wire [31:0] time_stamp_US_out;
	//wire piezo_enable;
	
	//assign wires
	//assign piezo_enable = enable_IO;
	
	
	
	//ext moduls
	//clock_divider cd1(clock, reset, clock_div);
	IO_time_ctl tim1(clock, reset, piezo_output_enable, time_cnt, time_stamp_US_out, piezo_enable);//detects trigger event starts output and matches it with the current time stamp 
	
	always @(posedge piezo_enable) begin : start_US
		US_output_time <= time_stamp_US_out[31:0]; 
	end
	
	  
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
					8'h00: returnvalue <= time_cnt[31:0];
					8'h01: returnvalue <= rtc_trigger_data[31:0];
					8'h02: returnvalue <= US_output_time[31:0];
					8'h03: returnvalue <= waitflag_status;
					8'h04: returnvalue <= burst_cycles_def;
					8'h05: returnvalue <= rtc_trigger_data2[31:0];
					//8'h04: returnvalue <= waitflag_status;
					default: returnvalue <= 32'hDEADBEEF;
				endcase
				if(avalon_slave_waitFlag==1) begin // next clock cycle the returnvalue should be ready
					avalon_slave_waitFlag <= 0;
				end
			end
		end
	end
	
	
	reg [1:0] write_delay_cnt;
	always @(posedge clock, posedge reset) begin: AVALON_WRITE_INTERFACE
		if (reset == 1) begin
			waitflag_trigger <= 0;
			time_cnt <= 0;
			burst_cycles_cnt <= 0;
			write_delay_cnt <= 0;

			burst_cycles_def <= 32'd5000;
		end else begin
			// if we are writing via avalon bus and waitrequest is deasserted, write the respective register
			time_cnt <= time_cnt + 32'd1; 
			burst_cycles_cnt <= 0;
			//write_delay_cnt <= write_delay_cnt + 2'd1;
			//if (time_cnt == 4294967295) begin
			//	time_cnt <= 32'd0;
			//end
			/*if (write_delay_cnt == 1) begin
				waitflag_trigger <= 0;
				write_delay_cnt <= 0;
			end*/
			if(waitflag_trigger_clear == 1) begin
				waitflag_trigger <= 0;
			end
			if (burst_enable == 1) begin
				burst_cycles_cnt <= burst_cycles_cnt + 32'd1;
				if(burst_cycles_cnt >= burst_cycles_def) begin
					burst_enable <= 0;
					burst_cycles_cnt <= 32'd0;
				end
			end
			if(avalon_slave_write && ~avalon_slave_waitrequest) begin
				case(avalon_slave_address>>8)
					8'h00: time_cnt <= avalon_slave_writedata[31:0];
					8'h02: waitflag_trigger <= (avalon_slave_writedata!=0);
					8'h03: US_out_trigger <= (avalon_slave_writedata!=0);
					8'h04: burst_cycles_def <= avalon_slave_writedata[31:0];
					8'h05: burst_enable <= (avalon_slave_writedata!=0);
				endcase
			end
		end 
	end
	

	
	// so wie das aktuell laueft hat man einen taktcyclus wo waitflag_status sich nicht aendert ... waitfalg_trigger muss  mit 2bit counter sein
	/*always @(posedge clock, posedge event_trigger, posedge reset) begin: IO_time_trigger_in
		if (reset == 1) begin
			rtc_trigger_data <= 32'd0;
			waitflag_status <= 1;
		end else if(event_trigger == 1) begin
			if(waitflag_status == 0) begin
				rtc_trigger_data <= time_cnt[31:0];
				waitflag_status <= 1;
				#3;
			end 
		end else begin
			if(waitflag_trigger == 1)begin
				waitflag_status = 0;
			end
		end
	end*/
	
	reg waitflag_trigger_recursive;
	reg waitflag_trigger_clear;
	reg start_input;
	reg [31:0] filter_cnt;
	reg [31:0] peak_cnt;
	
	reg first_trigger;
	
	always @(posedge clock, posedge reset) begin: IO_time_trigger_in
		if (reset == 1) begin
			rtc_trigger_data <= 32'd0;
			waitflag_status <= 0;
			waitflag_trigger_clear <= 0;
			filter_cnt <= 32'd0;
			peak_cnt <= 32'd0;
			waitflag_trigger_recursive <= 0;
			first_trigger <= 1;
		end else begin
			filter_cnt <= filter_cnt + 32'd1;
			waitflag_trigger_clear <= 0;
			if(waitflag_trigger == 1) begin
				waitflag_status <= 1;
				waitflag_trigger_clear <= 1;
				peak_cnt <= 0;
				filter_cnt <= 0;
			end else begin
				if(event_trigger == 1) begin
					peak_cnt <= 0;
					if(waitflag_status == 1) begin
						peak_cnt <= peak_cnt + 32'd1;
						if(first_trigger == 1) begin
							first_trigger <=0;
							rtc_trigger_data <= time_cnt[31:0];
							rtc_trigger_data2 <= 32'd32;
							filter_cnt <= 0;
							peak_cnt <= 0;
						end
					end
				end
				if(filter_cnt >= 32'd7000) begin
					first_trigger <=1;
					filter_cnt <= 0;
					if(peak_cnt >= 32'd4000)begin
						//rtc_trigger_data <= peak_cnt [31:0];
						rtc_trigger_data2 <= filter_cnt [31:0];
						waitflag_status <= 0;
					end 
				end
			end
		end
	end
	
	/*
	always @(posedge clock, posedge reset) begin: IO_time_trigger_in
		if (reset == 1) begin
			rtc_trigger_data <= 32'd0;
			waitflag_status <= 0;
			waitflag_trigger_clear <= 0;
			filter_cnt <= 32'd0;
			peak_cnt <= 32'd0;
			waitflag_trigger_recursive <= 0;
		end else begin
			filter_cnt <= 0;
			waitflag_trigger_clear <= 0;
			
			if(waitflag_status == 1) begin
				filter_cnt <= filter_cnt + 32'd1;
				if(filter_cnt >= 32'd7000) begin
					if(peak_cnt >= 32'd1250) begin
						waitflag_status <= 0;
						waitflag_trigger_recursive <= 0;
						rtc_trigger_data <= peak_cnt [31:0];
					end else begin
						rtc_trigger_data <= 32'd0;
						waitflag_status <= 1;
						filter_cnt <= 32'd0;
						peak_cnt <= 32'd0;
						waitflag_trigger_recursive <= 1;
					end
				end
			end
			
			if(event_trigger == 1) begin
				waitflag_trigger_recursive <= 0;
				waitflag_trigger_clear <=1;
				if(waitflag_trigger == 1) begin
					filter_cnt <= 32'd0;
					rtc_trigger_data <= time_cnt[31:0];
					waitflag_status <= 1;
					peak_cnt <= 32'd0;
				end
				if(waitflag_trigger_recursive == 1) begin
					filter_cnt <= 32'd0;
					rtc_trigger_data <= time_cnt[31:0];
					waitflag_status <= 1;
					peak_cnt <= 32'd0;
				end
				if(waitflag_status == 1) begin
					peak_cnt <= peak_cnt + 32'd1;
				end else begin
					peak_cnt <= 0;
				end
			end
			
			
		end
	end*/
	
endmodule


//detects trigger event starts output and matches it with the current time stamp 
module IO_time_ctl ( 
	input clock,
	input reset,
	input trigger,
	input [31:0] time_cnt,
	output [31:0] time_stamp_US_out,
	output enable_IO
); 
	//IO_time_ctl
	reg [31:0] ret_val;
	reg ret_val_IO;
	reg [31:0] dealy_cnt;
	
	always @(posedge clock) begin
		dealy_cnt <= 32'd0;
		if (reset) begin
			  ret_val <= 32'd0;
			  ret_val_IO <= 0;
		end else begin
			if(trigger == 1) begin
				if(dealy_cnt < 1)begin
					ret_val_IO <= 1;
					ret_val <= time_cnt;
					dealy_cnt <= dealy_cnt + 32'd1;
				end else begin
					dealy_cnt <= dealy_cnt + 32'd1;
				end
				if (dealy_cnt == 4294967295) begin
					dealy_cnt <= 32'd0;
				end
			end else begin
				ret_val_IO <= 0;
				dealy_cnt <= 32'd0;
			end
		end
	end
	
	assign enable_IO = ret_val_IO;
	assign time_stamp_US_out = ret_val;
endmodule
