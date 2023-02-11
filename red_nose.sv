module red_nose
													//25 MHz clk, divided by 56818 = 440 Hz
(input clk,										//Divide 56818 by 2 to perserve 50% duty cycle output
output sound);
				 
logic [30:0] tone;
always_ff@(posedge clk)
	tone <= tone + 1;

logic [7:0] fullnote;					 //6 bits encodes a note, therefore we can get 64 notes
												//There are 12 notes per octave, so 64 notes gives us over 5 octaves
												//With a 25MHz clock, each note lasts 167ms
//music_ROM rom(.clk(clk), .address(tone[29:22]), .note(fullnote));
												

logic [2:0] octave;
logic [3:0] note;

								//tone acts as a 28 bit counter, 
										//we are extracting the 6 most significant bits to give us the 6 notes we want to play
divide_by12 divby12(.numerator(fullnote[5:0]), .quotient(octave), .remainder(note)); //Dividing the fullnote by 12 gives us 5 octaves
lpm_rom #(.LPM_WIDTH(8), .LPM_WIDTHAD(8), .LPM_FILE("mem.mif")) music_rom(.address(tone[29:22]), .inclock(clk), .outclock(clk), .q(fullnote));

logic [8:0] frequency;
always @(note)
	case(note)
	 0: frequency = 9'd511;//A
	 1: frequency = 9'd482;// A#/Bb
	 2: frequency = 9'd455;//B
	 3: frequency = 9'd430;//C
	 4: frequency = 9'd405;// C#/Db
	 5: frequency = 9'd383;//D
	 6: frequency = 9'd361;// D#/Eb
	 7: frequency = 9'd341;//E
	 8: frequency = 9'd322;//F
	 9: frequency = 9'd303;// F#/Gb
	10: frequency = 9'd286;//G
	11: frequency = 9'd270;// G#/Ab
	default: frequency = 9'd0;
endcase

logic [8:0] counter_note;
logic [7:0] counter_octave;

always @(posedge clk) 
	counter_note <= (counter_note == 0 ? frequency : counter_note - 9'd1);

always @(posedge clk) 
	if(counter_note==0) 
		counter_octave <= (counter_octave==0 ? 8'd255 >> octave : counter_octave-8'd1);
	
always @(posedge clk) 
	if(counter_note==0 && counter_octave==0 && fullnote!=0 && tone[21:18]!=0) 
		sound <= ~sound;
		
endmodule

//First, use a 24 bit counter called "tone" to produce a slow square wave. The MSB [23] toggles with a frequency of 1.5 Hz
//We use tone[23] to switch another counter between two frequencies