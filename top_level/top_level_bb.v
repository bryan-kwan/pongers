
module top_level (
	clk_clk,
	ledr_external_connection_export,
	sw_external_connection_export);	

	input		clk_clk;
	output	[7:0]	ledr_external_connection_export;
	input	[7:0]	sw_external_connection_export;
endmodule
