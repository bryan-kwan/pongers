
module top_level (
	clk_clk,
	ledr_external_connection_export,
	sw_external_connection_export,
	vga_conduit_CLK,
	vga_conduit_HS,
	vga_conduit_VS,
	vga_conduit_BLANK,
	vga_conduit_SYNC,
	vga_conduit_R,
	vga_conduit_G,
	vga_conduit_B);	

	input		clk_clk;
	output	[7:0]	ledr_external_connection_export;
	input	[7:0]	sw_external_connection_export;
	output		vga_conduit_CLK;
	output		vga_conduit_HS;
	output		vga_conduit_VS;
	output		vga_conduit_BLANK;
	output		vga_conduit_SYNC;
	output	[3:0]	vga_conduit_R;
	output	[3:0]	vga_conduit_G;
	output	[3:0]	vga_conduit_B;
endmodule
