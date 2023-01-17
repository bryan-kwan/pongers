module top_level(input logic CLK, reset_n,
output logic [3:0] VGA_B, VGA_R, VGA_G,
output logic VGA_VS, VGA_HS,out_test);

logic vga_clk;
logic locked;
assign out_test = CLK;
pll pll_ins(.areset(0), .inclk0(CLK), .c0(vga_clk), .locked(locked));

VGADriver vgatimer_ins(.clk(vga_clk), .reset_n(reset_n), .hsync(VGA_HS), .vsync(VGA_VS),
.o_red(VGA_R), .o_blue(VGA_B), .o_green(VGA_G));

endmodule