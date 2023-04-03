module top_level
 (input  logic        clk,
						reset_n,
							en_n,
  //input  logic [9:0] note,
  output logic [6:0] r2r);
  
  logic [8:0] count;
  logic [3:0] en;
  
  
  //logic [9:0] note;
  
  
   sine_wave sine_1(.reset_n(reset_n), .clk(clk), .en(en), .sine_faze(r2r));
  
	counter count_1(.clk(clk), .reset_n(reset_n), .enable(en));
	

	
	//song song_1(.clk(clk), .reset_n(reset_n), .milisec(milisec), .note(note));
 endmodule 