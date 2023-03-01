module audio_avalon_interface (input logic clock25, 
							input logic clock50, 
							input logic reset_n, 
							input logic read,
							output logic [31:0]readdata,
							input logic [31:0] writedata, 
							input logic write, 
							output logic speaker);

							
	// Data registers
	logic [31:0] data;
	always_ff @(posedge clock50) begin
		if (!reset_n)
			data<=0;
		else begin
			if(write)
				data<=writedata;
			if(read)
				readdata<=data;
		end
	end

	// Audio output
	logic audio_enable;
	logic audio_signal;
	assign audio_enable=data[0];
	always_comb begin
		if(audio_enable)
			speaker = audio_signal;
		else
			speaker = 0;
	end
	audio_top_level U1 ( .clk(clock25), .enable(audio_enable), .reset_n(reset_n), .speaker(audio_signal));
	
endmodule
