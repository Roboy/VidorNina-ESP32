module clock_divider ( 
	input clock,
	input reset,
	output out_clk 
);
parameter PULS_FREQ = 40000 ;

	reg out_clk_reg;
	reg [32:0] counter_up;

	always @(posedge clock)
		if (reset) begin
			  out_clk_reg <= 1'b0;
			  counter_up <= 32'd1;
		end else begin
			counter_up <= counter_up + 32'd1;
			out_clk_reg <=0;
			if(counter_up <= 50000000/PULS_FREQ/2) begin //625-1 tak cycle
				//counter_up <= 32'd1;
				//out_clk_reg <= ~out_clk_reg;
				out_clk_reg <= 1;
			end
			if(counter_up == 50000000/PULS_FREQ) begin //1250-1 tak cycle
				//counter_up <= 32'd1;
				//out_clk_reg <= ~out_clk_reg;
				counter_up<=0;
			end
		end
	assign out_clk = out_clk_reg;
endmodule
