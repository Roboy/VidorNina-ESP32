`define MAX_WAIT_CYCLES 50000000 //50Mhz clk -> 50M cycles for one sec
`define  INIT_WAIT_DELAY 5000
`define  WAIT_DELAY 7000
`define  CONV_CYCLES 2
module ptp_sync(
		input 	clock,
		input 	reset,
		
		// this is for the avalon interface
		input [15:0] 				avalon_slave_address,
		input 						avalon_slave_write,
		input signed 	[31:0] 	avalon_slave_writedata,
		input 						avalon_slave_read,
		output signed  [31:0] 	avalon_slave_readdata,
		output 						avalon_slave_waitrequest,
		
		//piezo interface
		output  	piezo_interface_out,
		input 		piezo_interface_in,
		
		output [31:0]time_data_master,
		output [31:0]time_data_slave
	);
	
reg default_def;
reg start_delay;
reg [1:0]start_ptp;

//reg test_avalon;
//reg test_avalon2;
	
reg enable_time_sync_mode;
reg enable_master;
reg hps_reset;

wire ptp_slave_clk;
wire ptp_master_clk;

assign ptp_slave_clk 			= 	(~ enable_master) & clock & enable_time_sync_mode;
assign ptp_master_clk 		= 	enable_master  & clock  & enable_time_sync_mode;
//assign ptp_master_reset 	= 	~enable_master ;

wire [31:0] startsync_cnt;
wire [31:0] travel_time_cnt_master;
wire [31:0] travel_time_cnt_slave;

reg [31:0] travel_time_cnt_master_reg;
reg [31:0] travel_time_cnt_slave_reg;
assign time_data_master= travel_time_cnt_master_reg[31:0];
assign time_data_slave= travel_time_cnt_slave_reg[31:0];

wire output_interface0;
wire output_interface1;
wire output_interface_test;

wire wire_reset;

wire conv_finished_master;
wire conv_finished_slave;
reg conv_finished;

assign wire_reset = reset | hps_reset;
//assign output_interface_test = test_avalon2;
assign piezo_interface_out 	= 	output_interface0 | output_interface1;//output_interface_test;//output_interface0 | output_interface1| output_interface_test;

//assign travel_time_slave 	= 	travel_time_cnt_slave[31:0];
//assign travel_time_master = 	travel_time_cnt_master[31:0];


PTP_ctl ptpmaster0(
		ptp_master_clk,
		wire_reset,
		default_def, 
		piezo_interface_in, 
		output_interface0,
		travel_time_cnt_master,
		conv_finished_master
);
PTP_ctl ptpslave0(
		ptp_slave_clk,
		wire_reset,
		~default_def,
		piezo_interface_in, 
		output_interface1,
		travel_time_cnt_slave,
		conv_finished_slave
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
			default_def <= 0;
		end else begin
			avalon_slave_waitFlag <= 1;
			travel_time_cnt_master_reg<= travel_time_cnt_master[31:0];
			travel_time_cnt_slave_reg<= travel_time_cnt_slave[31:0];
			if(avalon_slave_read) begin
				case(avalon_slave_address>>8)
					8'h00: returnvalue 	<= travel_time_cnt_master[31:0];
					8'h01: returnvalue 	<= travel_time_cnt_slave[31:0];
					8'h02: returnvalue 	<= {31'd0,conv_finished}; 
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
			enable_master <= 0;
			enable_time_sync_mode <= 0;
			hps_reset <= 0;
			conv_finished 	<= 0;
			start_ptp <= 0;
			start_delay <= 0;
			//test_avalon <=0;
			//test_avalon2<=0;
		end else begin
			hps_reset <= 0;
			conv_finished<= conv_finished_master| conv_finished_slave;
			if(conv_finished == 1)begin
				enable_time_sync_mode<= 0;
			end
			if(start_ptp[0] == 1 )begin				
				enable_master <= start_ptp[1]; 
				start_ptp[0] <= 0;
				//test_avalon <= start_ptp[1]; 
				enable_time_sync_mode<= 0;
				hps_reset <= 1;
				start_delay <= 1;
			end
			if(start_delay == 1)begin
				start_delay<=0;
				enable_time_sync_mode<= 1;
			end
			// if we are writing via avalon bus and waitrequest is deasserted, write the respective register
			if(avalon_slave_write && ~avalon_slave_waitrequest) begin
				case(avalon_slave_address>>8)
					8'h00: enable_master 						<= (avalon_slave_writedata!=0);
					8'h01: enable_time_sync_mode <= (avalon_slave_writedata!=0);
					8'h02: hps_reset <= (avalon_slave_writedata!=0);
					8'h03: start_ptp <=  avalon_slave_writedata[1:0];
					//8'h04: test_avalon <=  avalon_slave_writedata[0];
				endcase
			end

		end 
	end
	
endmodule
	
	
//time when started sync will always be 0
module PTP_ctl(
	input clock,
	input reset,
	
	input mode_select, //0 is master
	
	input input_interface,
	output output_interface,

	output [31:0] travel_time_cnt,
	
	output conv_finished
);
	
	reg output_interface_reg;
	reg [31:0] travel_time_cnt_reg;
	assign output_interface = output_interface_reg;
	assign travel_time_cnt = travel_time_cnt_reg[31:0];
	reg conv_finished_reg;
	assign conv_finished = conv_finished_reg;
	
	reg [31:0] delay_cnt;
	
	reg FLAG_is_master;
	
	reg FLAG_first_impuls;
	
	reg [31:0] conv_cnt;
	
	
	always @(posedge clock, posedge reset) begin : start_sync //TODO add ptp_reset 
		if (reset == 1) begin
			delay_cnt 								<= 32'd0;
			conv_cnt 								<= {31'd0,~mode_select};
			travel_time_cnt_reg		<= 1;
			FLAG_is_master				<= mode_select;
			FLAG_first_impuls			<= 0;
			conv_finished_reg			<= 0;
			output_interface_reg 	<= 0;
		end else begin
			output_interface_reg 	<= 0;
			delay_cnt 								<= delay_cnt + 32'd1;
			if(FLAG_is_master == 0) begin
					FLAG_is_master <= 0;
					if(FLAG_first_impuls==0)begin	//start counting at first impuls
						FLAG_first_impuls		<=1;
						delay_cnt 							<= 32'd0;
					end
					if(delay_cnt <= `INIT_WAIT_DELAY) begin
						output_interface_reg 	<= 1;
					end
					if(delay_cnt >= `WAIT_DELAY) begin
						FLAG_is_master				<= 1;
					end
			end else begin
					if(input_interface == 1) begin
							conv_cnt									<= conv_cnt + 32'd1;		
							FLAG_is_master 				<= 0;
							if(FLAG_first_impuls == 1) begin
									if(conv_finished_reg == 0)begin
											travel_time_cnt_reg <= delay_cnt[31:0];
									end
									delay_cnt 							<= 32'd0;
									FLAG_first_impuls	<= 0;
							end else begin
									delay_cnt 								<= 32'd0;
							end
					end
					if(conv_cnt >= `CONV_CYCLES)begin
							conv_cnt 								<= `CONV_CYCLES;
							conv_finished_reg			<= 1;
							travel_time_cnt_reg 	<= travel_time_cnt_reg;
							output_interface_reg 	<= 0;
							FLAG_is_master 				<= 1;
					end
			end
			if (delay_cnt == `MAX_WAIT_CYCLES) begin
				output_interface_reg 	<= 0;
				delay_cnt 								<= 32'd0;
				output_interface_reg 	<= 0;
			end	
		end
	end
	
endmodule 
