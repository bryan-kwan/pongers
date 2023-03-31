module audio_avalon_interface (input logic clock25, 
							input logic clock50, 
							input logic reset_n, 
							input logic read,
							output logic [31:0]readdata,
							input logic [31:0] writedata, 
							input logic write, 
							output logic [6:0] speaker);

							
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
	logic [6:0] audio_signal;
	assign audio_enable=data[0];
	always_comb begin
		if(audio_enable)
			speaker = audio_signal;
		else
			speaker = 0;
	end
	sine_wave_audio_top_level U1 ( .clk(clock25), .en_n(audio_enable), .reset_n(reset_n), .r2r(audio_signal));
	
endmodule
