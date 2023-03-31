module counter(input logic clk,
                       reset_n,
                                 
               output logic [3:0] enable);
							
logic [25:0] count;



always_ff @(posedge clk)
    begin
        if (!reset_n)
            count <= 0;
		  else if (reset_n) begin
				count<=count+1; 
				enable[0]<= count[25];
				enable[1]<= count[24];
				enable[2]<= count[23];
				enable[3]<= count[22];
					
    end

//assign enable = count[28:22];
end

endmodule