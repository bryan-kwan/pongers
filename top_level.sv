// top level module
// Watch out for case sensitivity when translating from VHDL.
// Also note that the .QSF is case sensitive.

module top_level
 (input  logic       clk,
  input  logic       reset_n,
  output logic       arduino);
  
  
	//music box
	logic sound;              	
	assign arduino = sound;
	
	
	logic outclk; 
	pll clktest(.inclk0(clk), .c0(outclk));
	
   red_nose test(.clk(outclk), .sound(sound)); 
	  
endmodule