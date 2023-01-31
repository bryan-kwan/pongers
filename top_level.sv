// top level module
// Watch out for case sensitivity when translating from VHDL.
// Also note that the .QSF is case sensitive.

module top_level
 (input  logic       clk,
  input  logic       reset_n,
  output logic       arduino);
  
  
	//music box
	logic sound;                                         
	assign arduino = ~sound;
	
	music_box test(.clk(clk), .sound(sound));
   //red_nose test(.clk(clk), .sound(sound)); 
	//music test(.clk(clk), .sound(sound));
	  
endmodule