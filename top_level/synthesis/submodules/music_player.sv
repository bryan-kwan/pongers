module music_player (
	input logic clk,
	output logic tunes
);

//We will generate music by mimicing notes on a keyboard
//Let's use 6 bits to encode a note
//This will give us 64 possible notes to choose from (2^6 = 64)
//There are 12 notes per octave
//Therefore, we have a range of 5 octaves to play from!

//Let's use a 28-bit counter, and extract the 6 most significant bits
//This allows us to play a range of increasing notes
//logic [28:0] tone;
//always_ff @(posedge clk)
//	tone <= tone + 1;
//	
//logic [5:0] fullnote;
//assign fullnote = tone[27:22];

//With a 25 MHz clk, each note lasts 168 ms.
//The reason we are instantiating a 28-bit counter and extracting the 6 MSB
//Is to let each note last for a longer period of time.
//This is because the counter has to run for longer to reach the 6 MSB 
//Math: 2^22 = 4,194,304. 1 / (25E6 / 2^22) = 0.168s

//Oscilliscope Test: Make counter [40:0] to give us 687s to measure first note!
//logic [40:0] tone;
//always_ff @(posedge clk)
//	tone <= tone + 1;
//	
//logic [5:0] fullnote;
//assign fullnote = tone[39:34];

//ROM Player
logic [30:0] tone;
always_ff @(posedge clk)
	tone <= tone + 1;

logic [7:0] fullnote;
musicrom_v rom(.clk(clk), .address(tone[29:22]), .note(fullnote));
//With a 25 MHz clk, each note lasts 168 ms.
//The reason we are instantiating a 31-bit counter and extracting the 6 MSB
//Is to let each note last for a longer period of time.
//This is because the counter has to run for longer to reach the 6 MSB 
//Math: 2^22 = 4,194,304. 1 / (25E6 / 2^22) = 0.168s

//Now, let's divide the "fullnote" by 12
//This will give us information about:
// 1) The particular octave we're currently on (3, 4, 5, etc)
// 2) The particular note We're currently on (A, B, C#, etc)
// Let's use a 3-bit bus for octave (2^3 = 8), which is enough for us to use 5 octaves
// Let's use a 4-bit bus for note (2^4 = 16), which is enough for us to use 12 notes
logic [2:0] octave;
logic [3:0] note;
divide_by_12 div(.numerator(fullnote[5:0]), .quotient(octave), .remainder(note));
//	For example: 
// "fullnote" = 6'b101010 = 42
// 42 / 12 = 3.5
// Therefore, we are on octave 3 (quotient = 3) and note 6 (remainder = 6)

//Let's create a look-up table to define what the value of "note"
//From the divide_by_12 module pretains to
//The value for each note is defined by its frequency
//We wil divide the clock by this in order to produce the desired freuqnecy
//For example, note A - octave 4 produces 440 Hz
logic [8:0] clkdivider;
always_ff @*
case(note)
//	 0: clkdivider = 9'd444 - 1;//A
//	 1: clkdivider = 9'd419 - 1;// A#/Bb
//	 2: clkdivider = 9'd396 - 1;//B
//	 3: clkdivider = 9'd745 - 1;//C
//	 4: clkdivider = 9'd705 - 1;// C#/Db
//	 5: clkdivider = 9'd664 - 1;//D
//	 6: clkdivider = 9'd628 - 1;// D#/Eb
//	 7: clkdivider = 9'd592 - 1;//E
//	 8: clkdivider = 9'd560 - 1;//F
//	 9: clkdivider = 9'd528 - 1;// F#/Gb
//	10: clkdivider = 9'd498 - 1;//G
//	11: clkdivider = 9'd470 - 1;// G#/Ab
	
//	 0: clkdivider = 9'd888 - 1;//A
//	 1: clkdivider = 9'd838 - 1;// A#/Bb
//	 2: clkdivider = 9'd792 - 1;//B
//	 3: clkdivider = 9'd1490 - 1;//C
//	 4: clkdivider = 9'd1410 - 1;// C#/Db
//	 5: clkdivider = 9'd1328 - 1;//D
//	 6: clkdivider = 9'd1256 - 1;// D#/Eb
//	 7: clkdivider = 9'd1184 - 1;//E
//	 8: clkdivider = 9'd1120 - 1;//F
//	 9: clkdivider = 9'd1056 - 1;// F#/Gb
//	10: clkdivider = 9'd996 - 1;//G
//	11: clkdivider = 9'd942 - 1;// G#/Ab

//	 0: clkdivider = 9'd511;//A
//	 1: clkdivider = 9'd482;// A#/Bb
//	 2: clkdivider = 9'd455;//B
//	 3: clkdivider = 9'd430;//C
//	 4: clkdivider = 9'd405;// C#/Db
//	 5: clkdivider = 9'd383;//D
//	 6: clkdivider = 9'd361;// D#/Eb
//	 7: clkdivider = 9'd341;//E
//	 8: clkdivider = 9'd322;//F
//	 9: clkdivider = 9'd303;// F#/Gb
//	10: clkdivider = 9'd286;//G
//	11: clkdivider = 9'd270;// G#/Ab

	0: clkdivider = 9'd440;	//A
	1: clkdivider = 9'd466;	// A#/Bb
	2: clkdivider = 9'd493;	//B
	3: clkdivider = 9'd261;	//C
	4: clkdivider = 9'd277;	// C#/Db
	5: clkdivider = 9'd293;	//D
	6: clkdivider = 9'd311;	// D#/Eb
	7: clkdivider = 9'd329;	//E
	8: clkdivider = 9'd349;	//F
	9: clkdivider = 9'd369;	// F#/Gb
	10: clkdivider = 9'd392;	//G
	11: clkdivider = 9'd415;	// G#/Ab
	default: clkdivider = 9'd0;
endcase
//There are 12 possible cases of notes from the divide_by_12 module
//This is why there are 12 cases in this look-up table

//Here, we achieve clk_division based on the value of clkdivider
//For example, if clkvdivider = 511 = 9'b1_1111_1111 
//(25E6) / (511) = 48, 923. (25E6) / (48, 923) = 511 Hz produced
// This is because the value of note, along with the value of octave (we will see this module below)
// Determine the frequency outputted by the speaker by changing how long it takes for the counter to count down
logic [8:0] counter_note;
always_ff @(posedge clk)
	if (counter_note == 0)
		counter_note <= clkdivider;
	else
		counter_note <= counter_note - 1;
//Everytime "counter_note" equals 0, we get a tick for the octave divider
//Which is shown below

logic [7:0] counter_octave;
always_ff @(posedge clk)
if (counter_note == 0)
begin
	if (counter_octave == 0)
		counter_octave <= (octave == 0 ? (256-1) :
															octave == 1 ? (128-1) :
																						octave == 2 ? (64-1) :
																													octave == 2 ? (32-1) : 
																																				octave == 4 ? (16-1) : (8-1));
	else
		counter_octave <= counter_octave - 1;
end
//This checks what the value of octave is from the divide_by_12 module
//For example, if we're in octave 4, then counter_octave will be assigned 15
//If we're in octave 0, counter_octave will be assigned 255
//A higher counter_octave value will result in a longer lasting counter
//This feeds into our "clkdivider" which will ultimatelty produce the frequencies we want
//Continuing from the example provided from the "counter_note" module
//Note A, Octave 0 (First note)
//F = (25E6) / (111) / (256) / 2 = 440

//Let A2 = 440
always_ff @(posedge clk)
	if (counter_note == 0 && counter_octave == 0 && fullnote!=0 && tone[21:18] != 0)
		tunes <= ~tunes;
//always @(posedge clk) counter_note <= counter_note==0 ? clkdivider : counter_note-9'd1;
//always @(posedge clk) if(counter_note==0) counter_octave <= counter_octave==0 ? 8'd255 >> octave : counter_octave-8'd1;
//always @(posedge clk) if(counter_note==0 && counter_octave==0 && fullnote!=0 && tone[21:18]!=0) tunes <= ~tunes;

endmodule