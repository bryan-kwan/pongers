module audio_avalon_interface (clock25, clock50, resetn, writedata, readdata, write, read,
	byteenable, chipselect, speaker);
	
	// signals for connecting to the Avalon fabric
	input clock25, clock50, resetn, read, write, chipselect;
	input [3:0] byteenable;
	input [31:0] writedata;
	output [31:0] readdata;
	
	// signal for exporting register contents outside of the embedded system
	output speaker;
	
	audio_top_level U1 ( .clk(clock25), .writedata(writedata), .reset_n(resetn), .speaker(speaker));
	
endmodule
