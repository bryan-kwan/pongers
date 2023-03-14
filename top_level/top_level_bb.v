
module top_level (
	audio_out_writeresponsevalid_n,
	clk_clk,
	gpio_export,
	memory_addr,
	memory_ba,
	memory_cas_n,
	memory_cke,
	memory_cs_n,
	memory_dq,
	memory_dqm,
	memory_ras_n,
	memory_we_n,
	sdram_clk_clk,
	spi_master_MISO,
	spi_master_MOSI,
	spi_master_SCLK,
	spi_master_SS_n,
	spi_slave_MISO,
	spi_slave_MOSI,
	spi_slave_SCLK,
	spi_slave_SS_n,
	sw_external_connection_export,
	vga_conduit_CLK,
	vga_conduit_HS,
	vga_conduit_VS,
	vga_conduit_BLANK,
	vga_conduit_SYNC,
	vga_conduit_R,
	vga_conduit_G,
	vga_conduit_B);	

	output		audio_out_writeresponsevalid_n;
	input		clk_clk;
	input	[3:0]	gpio_export;
	output	[12:0]	memory_addr;
	output	[1:0]	memory_ba;
	output		memory_cas_n;
	output		memory_cke;
	output		memory_cs_n;
	inout	[15:0]	memory_dq;
	output	[1:0]	memory_dqm;
	output		memory_ras_n;
	output		memory_we_n;
	output		sdram_clk_clk;
	input		spi_master_MISO;
	output		spi_master_MOSI;
	output		spi_master_SCLK;
	output		spi_master_SS_n;
	output		spi_slave_MISO;
	input		spi_slave_MOSI;
	input		spi_slave_SCLK;
	input		spi_slave_SS_n;
	input	[7:0]	sw_external_connection_export;
	output		vga_conduit_CLK;
	output		vga_conduit_HS;
	output		vga_conduit_VS;
	output		vga_conduit_BLANK;
	output		vga_conduit_SYNC;
	output	[3:0]	vga_conduit_R;
	output	[3:0]	vga_conduit_G;
	output	[3:0]	vga_conduit_B;
endmodule
