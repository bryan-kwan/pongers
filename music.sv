module music
													//25 MHz clk, divided by 56818 = 440 Hz
(input clk,										//Divide 56818 by 2 to perserve 50% duty cycle output
output sound);
				 
logic [14:0] counter;
logic [27:0] tone;
logic [6:0] fast;
logic [6:0] slow;
logic [14:0] frequency;

assign fast = (tone[22] ? tone[21:15] : ~tone[21:15]); 
assign slow = (tone[25] ? tone[24:18] : ~tone[24:18]);
assign frequency = {2'b01, (tone[27] ? slow: fast), 6'b000000};


always_ff@(posedge clk)
	tone <= tone + 1;

always_ff@(posedge clk)
begin
	if(counter == 0) 						//Same as regular counter, but counting down instead!
		//counter <= frequency;		
		counter <= (tone[23] ? (frequency - 1) : ( (frequency/2) - 1) );		//Disco Police Siren
	else
		counter <= counter - 1;
end

always_ff@(posedge clk)
begin 
	if(counter == 0)				//Once counts all the way down, send pulsey
		sound <= ~sound;
end

endmodule

//First, use a 24 bit counter called "tone" to produce a slow square wave. The MSB [23] toggles with a frequency of 1.5 Hz
//We use tone[23] to switch another counter between two frequencies