//Credit to Tan Kian Yiak for creating this module
//It has been commented for further clarity by Ahmed Elmenshawi
//In order to implement it into ENEL 400 "Pongers" project

module divide_by_12 (
	input logic [5:0] numerator,	//Dividing the 6-bit bus "fullnote" by 12
	output logic [2:0] quotient,	//The quotient will be the 3-bit bus for octave
	output logic [3:0] remainder	//The remainder will be the 4-bit bus for note
);

logic [1:0] remainder3to2;	
//Remainder is trickier to deal with than quotient
//We'll need to split it into two busses, and combine at the end

always_ff @(numerator[5:2])
case(numerator[5:2])
	 0: begin quotient=0; remainder3to2=0; end
	 1: begin quotient=0; remainder3to2=1; end
	 2: begin quotient=0; remainder3to2=2; end
	 3: begin quotient=1; remainder3to2=0; end
	 4: begin quotient=1; remainder3to2=1; end
	 5: begin quotient=1; remainder3to2=2; end
	 6: begin quotient=2; remainder3to2=0; end
	 7: begin quotient=2; remainder3to2=1; end
	 8: begin quotient=2; remainder3to2=2; end
	 9: begin quotient=3; remainder3to2=0; end
	10: begin quotient=3; remainder3to2=1; end
	11: begin quotient=3; remainder3to2=2; end
	12: begin quotient=4; remainder3to2=0; end
	13: begin quotient=4; remainder3to2=1; end
	14: begin quotient=4; remainder3to2=2; end
	15: begin quotient=5; remainder3to2=0; end
endcase
//For example, if numerator = 6'b101010 = 42
//Then, numerator[5:2] = 4'b1010 = 10
//So, quotient (octave) = 3. remainder3to2 = 1

assign remainder[1:0] = numerator[1:0];
assign remainder[3:2] = remainder3to2;
//The remainder is composed of the numerator, as well as the remainder3to2
//Continuing from the previous example, 
//remainder[3:0] = remainder3to2 + numerator[1:0]
//remainder[3:0] = 4'b01_10 = 6

endmodule