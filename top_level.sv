// top level module
// Watch out for case sensitivity when translating from VHDL.
// Also note that the .QSF is case sensitive.

module top_level
 (input  logic       clk,
  input  logic       reset_n,
  output logic       speaker);
  
  
	//music box
	logic tunes;              	
	assign speaker = ~tunes;
	
	
	logic outclk; 
	pll clktest(.inclk0(clk), .c0(outclk));	//Need a 25MHz clk 
	
  //musicbox_v test(.clk(outclk), .speaker(tunes)); 
	music_player musiK(.clk(outclk), .tunes(tunes));
endmodule