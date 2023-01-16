module VGADriver (
	input logic 			  clk,  	// 83.46 MHz (PLL)
							 reset_n,	// Active Low
	output logic 			hsync,	// HSYNC to VGA connector
								vsync	// VSYNC to VGA connector
	//output logic [3:0] 	  o_red,	// RED to resistor DAC VGA connector
								//o_green,	// GREEN to resistor DAC VGA connector
								 //o_blue	// BLUE to resistor DAC VGA connector
);

logic LOW;
assign LOW = 1'b0;
logic HIGH;
assign HIGH = 1'b1;

logic [3:0] r_red;
logic [3:0] r_blue;
logic [3:0] r_green;

//1280 x 800, 60 Hz

//Horizontal Counter
logic h_count;
logic v_en;

always@(posedge clk)
begin
	if(h_count < 1679)
		h_count <= h_count + 1;
	else
		begin
			h_count <= 0;
			v_en = HIGH;
		end
end

//Vertical Counter
logic v_count;

always@(posedge clk)
begin
	if(v_en)
	begin
		if(v_count < 827)
			v_count <= v_count + 1;
		else
			v_count <= 0;
	end
end


//sync logic
assign hsync = (h_count >= 0 && h_count < 136) ? 1:0;
assign vsync = (v_count >= 0 && v_count < 3) ? 1:0;


//assign color = (h_count > (sync + back) && h_count <= (visible + sync + back - 1) && v_count > (sync + back) && v_count <= (sync + back - 1)
assign o_red = (h_count > 336 && h_count <= 1615 && v_count > 27 && v_count <= 826) ? r_red:0;
assign o_green = (h_count > 336 && h_count <= 1615 && v_count > 27 && v_count <= 826) ? r_green:0;
assign o_blue = (h_count > 336 && h_count <= 1615 && v_count > 27 && v_count <= 826) ? r_blue:0;

endmodule


//module VGADriver (
//	input logic 			  clk,  	// 25 MHz
//							 reset_n,	// Active Low
//	input logic  [7:0]   color,	//	Pixel Color Data (RRRGGGBB)
//	output logic [9:0] pixel_x, 	// x-coordinate of NEXT pixel that will be drawn
//					 [9:0] pixel_y,   // y-coordinate of NEXT pixel that will be drawn
//	output logic 			hsync,	// HSYNC to VGA connector
//								vsync,	// VSYNC to VGA connector
//	output logic [7:0] 	  red,	// RED to resistor DAC VGA connector
//								green,	// GREEN to resistor DAC VGA connector
//								 blue,	// BLUE to resistor DAC VGA connector
//	output logic 			 sync,	// SYNC to VGA connector
//								  clk,	// CLK to VGA connector
//								 blank	// BLANK to VGA connector
//);
//
///*
//Horizontal and Vertical Paramters are defined here for a 25MHz Pixel Clock, 640 x 480 resolution, 60 Hz Refresh Rate Configuration
//Other timing parameters are described in http://martin.hinner.info/vga/timing.html
//These values can be changed based on the design requirements, and have therefore been parameterized
//*/
//
//// Horizontal Paramters (Pixels)
//parameter [9:0] H_ACTIVE = 10'd_640;
//parameter [9:0] H_FRONT = 10'd_16;
//parameter [9:0] H_SYNC = 10'd_96;
//parameter [9:0] H_BACK = 10'd_48;
//
//// Horizontal States (Defined for Readability)
//logic [7:0] H_ACTIVE_S = 8'd_0;
//logic [7:0] H_FRONT_S = 8'd_1;
//logic [7:0] H_SYNC_S = 8'd_2;
//logic [7:0] H_BACK_S = 8'd_3;
//
//// Vertical Paramters (Lines)
//parameter [9:0] V_ACTIVE = 10'd_480;
//parameter [9:0] V_FRONT = 10'd_11;
//parameter [9:0] V_SYNC = 10'd_2;
//parameter [9:0] V_BACK = 10'd_31;
//
//// Vertical States (Defined for Readability)
//logic [7:0] V_ACTIVE_S = 8'd_0;
//logic [7:0] V_FRONT_S = 8'd_1;
//logic [7:0] V_SYNC_S = 8'd_2;
//logic [7:0] V_BACK_S = 8'd_3;
//
//// Low/High (Defined for Readability)
//logic LOW = 1'b0;
//logic HIGH = 1'b1;
//
//// Clocked Registers
//logic hsync_reg;
//logic vsync_reg;
//logic [7:0] red_reg;
//logic [7:0] green_reg;
//logic {7:0] blue_reg;
//logic line_done;
//
//// Control Registers
//logic [9:0] h_counter;
//logic [9:0] v_counter;
//logic [7:0] h_state;
//logic [7:0] v_state;
//
//always@(posedge clk) begin
//if (!reset_n) begin
//	//Zero the Counters
//	h_counter <= 10'd_0;
//	v_counter <= 10'd_0;
//	
//	//Set States to Active
//	h_state <= H_ACTIVE_STATE;
//	v_state <= V_ACTIVE_STATE;
//	
//	//Reset line done
//	line_done <= LOW;
//end
//
//else begin
//	//Horizontal Logic
//	
//
//end
//
//end
//
//endmodule







