module posedge_det(input logic clk,
										signal,
							output logic pos);


logic delay;

always_ff @(posedge clk)
begin
		delay <= signal;
end							

assign pos = signal & ~delay;

endmodule