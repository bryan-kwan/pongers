// top level module
// Watch out for case sensitivity when translating from VHDL.
// Also note that the .QSF is case sensitive.

module audio_top_level
 (input  logic       	clk,
  input  logic	[31:0]		writedata,
  input  logic       	reset_n,
  output logic       	speaker);
  
  logic tunes; 
  always_comb
	begin
		//selecting bit 0 of the 32 bit avalon writedata signal as the enable for the audio module
		if(writedata[0] == 1)        	
			speaker = ~tunes;
		else
			speaker = 1;	
	end
	
	music_player musiK(.clk(clk), .tunes(tunes));
	
endmodule