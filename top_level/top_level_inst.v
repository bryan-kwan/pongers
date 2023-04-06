	top_level u0 (
		.clk_clk                       (<connected-to-clk_clk>),                       //                    clk.clk
		.gpio_export                   (<connected-to-gpio_export>),                   //                   gpio.export
		.key_export                    (<connected-to-key_export>),                    //                    key.export
		.memory_addr                   (<connected-to-memory_addr>),                   //                 memory.addr
		.memory_ba                     (<connected-to-memory_ba>),                     //                       .ba
		.memory_cas_n                  (<connected-to-memory_cas_n>),                  //                       .cas_n
		.memory_cke                    (<connected-to-memory_cke>),                    //                       .cke
		.memory_cs_n                   (<connected-to-memory_cs_n>),                   //                       .cs_n
		.memory_dq                     (<connected-to-memory_dq>),                     //                       .dq
		.memory_dqm                    (<connected-to-memory_dqm>),                    //                       .dqm
		.memory_ras_n                  (<connected-to-memory_ras_n>),                  //                       .ras_n
		.memory_we_n                   (<connected-to-memory_we_n>),                   //                       .we_n
		.sdram_clk_clk                 (<connected-to-sdram_clk_clk>),                 //              sdram_clk.clk
		.sine_wave_output_readdata     (<connected-to-sine_wave_output_readdata>),     //       sine_wave_output.readdata
		.sw_external_connection_export (<connected-to-sw_external_connection_export>), // sw_external_connection.export
		.vga_conduit_CLK               (<connected-to-vga_conduit_CLK>),               //            vga_conduit.CLK
		.vga_conduit_HS                (<connected-to-vga_conduit_HS>),                //                       .HS
		.vga_conduit_VS                (<connected-to-vga_conduit_VS>),                //                       .VS
		.vga_conduit_BLANK             (<connected-to-vga_conduit_BLANK>),             //                       .BLANK
		.vga_conduit_SYNC              (<connected-to-vga_conduit_SYNC>),              //                       .SYNC
		.vga_conduit_R                 (<connected-to-vga_conduit_R>),                 //                       .R
		.vga_conduit_G                 (<connected-to-vga_conduit_G>),                 //                       .G
		.vga_conduit_B                 (<connected-to-vga_conduit_B>)                  //                       .B
	);

