// top level module
// Watch out for case sensitivity when translating from VHDL.
// Also note that the .QSF is case sensitive.

module audio_top_level
 (input  logic       	clk,
  input  logic			enable,
  input  logic       	reset_n,
  output logic       	speaker);
  
  logic tunes; 
      	
	assign speaker = tunes;

	
	music_player musiK(.clk(clk), .tunes(tunes));
	
endmodule