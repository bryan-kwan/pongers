(* multstyle = "dsp" *)

module sine_wave_1
 #(int                      width = 7,
	int							 length = 8192,
	int 							 song_length = 128)
  (input  logic             reset_n,
                            clk,
									
	input  logic [3:0]		  en,
	//input  logic [9:0]		 note,
	output logic [width-1:0] sine_faze
	);
	
	
	logic [1:0] s;
	logic [11:0] increment;
	logic [8:0] limit;
	logic [8:0]	count;
	assign increment = 8;
	
	
	logic [2:0] duration_list[song_length-1:0];
	logic [9:0] note_list[song_length-1:0];
	
	
	
	logic [9:0] note;
	
	logic [2:0] duration;
	
	logic [10:0] index;
	
								
  //logic [width-1:0] count_value_2;							
  								
  logic [width-1:0] my_lut[length-1:0]; // width of array should be size of counter
  logic [$clog2(length)+1:0] counter_value_2;
  initial begin // normally we don't use initial in RTL code, this is an exception
    $readmemh("sine_lut_2.txt",my_lut); // reads hexadecimal data from v2d_rom and places into my_rom
	 
	//Song 2
	$readmemh("duration_1.txt",duration_list);
	$readmemh("note_1.txt",note_list);
	 

  end
  
  //int counter;
 	assign s = counter_value_2[$clog2(length)+1:$clog2(length)];

  
  //int counter_value_2;
  always_ff @(posedge clk) begin
    if (!reset_n) begin
	   counter_value_2 <= 0;
		sine_faze<=0;
		count<=0;
		
		end
	 else if (en[duration]!=0) begin
		count <= count + 1;
		if (count>=limit) begin
			count<=0;
			counter_value_2 <= counter_value_2 + increment;
		if(limit==0) begin
			sine_faze <= 0;
		end
		else begin
			case(s)
			2'b00: sine_faze <= my_lut[counter_value_2[$clog2(length)-1:0]];
			2'b01: sine_faze <= -my_lut[~counter_value_2[$clog2(length)-1:0]];
			2'b10: sine_faze <= -my_lut[counter_value_2[$clog2(length)-1:0]];
			2'b11: sine_faze <= my_lut[~counter_value_2[$clog2(length)-1:0]];
			endcase
		end
		end
		
	end
//		else begin
//			count <= count + 1;
//		end
 end
 always_ff @ (negedge en[duration]) begin
	
	if(!reset_n) begin
	 index<=0;
	 
	 end
	
		index<=index+1;
		
//		
//		if (index>song_length-1) begin
//		index<=0;
//		end
	
	end
	
	

	always_comb begin
		
		case(note)
			11: limit = 0;
			10: limit = 53;//A
			9: limit = 51;//A#
			8: limit = 48;//B
			7: limit = 45;//C
			6: limit = 42;//C#
			5: limit = 40;//D
			4: limit = 38;//D#
			3: limit = 36;//E
			2: limit = 34;//F
			1: limit = 32;//F#
			0: limit = 30;//G
			
			default: limit = 50;
		endcase	
		
	end
	
	assign duration=duration_list[index];
   assign note = note_list[index];
endmodule