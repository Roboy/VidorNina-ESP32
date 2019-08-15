// new_component.v

// This file was auto-generated as a prototype implementation of a module
// created in component editor.  It ties off all outputs to ground and
// ignores all inputs.  It needs to be edited to make it do something
// useful.
// 
// This file will not be automatically regenerated.  You should check it in
// to your version control system if you want to keep it.
`timescale 1 ps / 1 ps
module piezo_ctl2 #(
		parameter PULS_FREQ = 40000
	) (
		input  wire  clk,       // clock_sink.clk
		input  wire  reset,     //      reset.reset
		output wire  gpio_out,  //    conduit.gpio_out
		input  wire  enable_in,  //           .enable_in
		output wire  enable_out
	);

	reg out_clk_reg;
	reg [32:0] counter_up;
	
	assign enable_out = enable_in;

	always @(posedge clk)
		if (reset) begin
			  out_clk_reg <= 1'b0;
			  counter_up <= 32'd1;
		end else begin
			out_clk_reg <=0;
			if(enable_in == 1) begin
				counter_up <= counter_up + 32'd1;
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
			end else begin
				out_clk_reg <= 1'bz;
			end
		end
	assign gpio_out = out_clk_reg;

endmodule
