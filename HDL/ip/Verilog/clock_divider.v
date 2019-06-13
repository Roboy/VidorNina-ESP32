module clock_divider ( 
	input clock,
	input reset,
	output out_clk 
);
	reg out_clk_reg;
	reg [32:0] counter_up;

	always @(posedge clock)
		if (reset) begin
			  out_clk_reg <= 1'b0;
			  counter_up <= 32'd1;
		end else begin
			counter_up <= counter_up + 32'd1;
			if(counter_up == 5) begin
				counter_up <= 32'd1;
				out_clk_reg <= ~out_clk_reg;
			end
		end
	assign out_clk = out_clk_reg;
endmodule
