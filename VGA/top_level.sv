module top_level(input logic CLK, reset_n,
output logic [2:0] VGA_B, VGA_R, VGA_G,
output logic VGA_VS, VGA_HS);

logic vga_clk;
logic locked;

pll pll_ins(.areset(0), .inclk0(CLK), .c0(vga_clk), .locked(locked));

VGADriver vgatimer_ins(.clk(vga_clk), .reset_n(reset_n), .hsync(VGA_HS), .vsync(VGA_VS));

endmodule