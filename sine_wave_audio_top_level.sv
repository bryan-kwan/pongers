module sine_wave_audio_top_level
 (input  logic        clk,
						reset_n,
							en_n,
  input  logic [1:0] song_select,
  output logic [6:0] r2r);
  
  logic [8:0] count;
  logic [3:0] en;
  
  logic [6:0] sine_value_0, sine_value_1, sine_value_2, sine_value_3;
  //logic [9:0] note;
  

   sine_wave sine_0(.reset_n(reset_n), .clk(clk), .en(en), .sine_faze(sine_value_0));

   sine_wave_1 sine_1(.reset_n(reset_n), .clk(clk), .en(en), .sine_faze(sine_value_1));

   always_comb begin 
      case(song_select)
         0: r2r = sine_value_0;
         1: r2r = sine_value_1;
         2: r2r = sine_value_2;
         3: r2r = sine_value_3;
         default: r2r = sine_value_0;
      endcase
      
      
   end
  
	counter count_1(.clk(clk), .reset_n(reset_n), .enable(en));
	

	
	//sine_wave_song song song_1(.clk(clk), .reset_n(reset_n), .milisec(milisec), .note(note));
 endmodule 