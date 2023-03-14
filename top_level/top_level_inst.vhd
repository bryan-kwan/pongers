	component top_level is
		port (
			audio_out_writeresponsevalid_n : out   std_logic;                                        -- writeresponsevalid_n
			clk_clk                        : in    std_logic                     := 'X';             -- clk
			gpio_export                    : in    std_logic_vector(3 downto 0)  := (others => 'X'); -- export
			memory_addr                    : out   std_logic_vector(12 downto 0);                    -- addr
			memory_ba                      : out   std_logic_vector(1 downto 0);                     -- ba
			memory_cas_n                   : out   std_logic;                                        -- cas_n
			memory_cke                     : out   std_logic;                                        -- cke
			memory_cs_n                    : out   std_logic;                                        -- cs_n
			memory_dq                      : inout std_logic_vector(15 downto 0) := (others => 'X'); -- dq
			memory_dqm                     : out   std_logic_vector(1 downto 0);                     -- dqm
			memory_ras_n                   : out   std_logic;                                        -- ras_n
			memory_we_n                    : out   std_logic;                                        -- we_n
			sdram_clk_clk                  : out   std_logic;                                        -- clk
			spi_master_MISO                : in    std_logic                     := 'X';             -- MISO
			spi_master_MOSI                : out   std_logic;                                        -- MOSI
			spi_master_SCLK                : out   std_logic;                                        -- SCLK
			spi_master_SS_n                : out   std_logic;                                        -- SS_n
			spi_slave_MISO                 : out   std_logic;                                        -- MISO
			spi_slave_MOSI                 : in    std_logic                     := 'X';             -- MOSI
			spi_slave_SCLK                 : in    std_logic                     := 'X';             -- SCLK
			spi_slave_SS_n                 : in    std_logic                     := 'X';             -- SS_n
			sw_external_connection_export  : in    std_logic_vector(7 downto 0)  := (others => 'X'); -- export
			vga_conduit_CLK                : out   std_logic;                                        -- CLK
			vga_conduit_HS                 : out   std_logic;                                        -- HS
			vga_conduit_VS                 : out   std_logic;                                        -- VS
			vga_conduit_BLANK              : out   std_logic;                                        -- BLANK
			vga_conduit_SYNC               : out   std_logic;                                        -- SYNC
			vga_conduit_R                  : out   std_logic_vector(3 downto 0);                     -- R
			vga_conduit_G                  : out   std_logic_vector(3 downto 0);                     -- G
			vga_conduit_B                  : out   std_logic_vector(3 downto 0)                      -- B
		);
	end component top_level;

	u0 : component top_level
		port map (
			audio_out_writeresponsevalid_n => CONNECTED_TO_audio_out_writeresponsevalid_n, --              audio_out.writeresponsevalid_n
			clk_clk                        => CONNECTED_TO_clk_clk,                        --                    clk.clk
			gpio_export                    => CONNECTED_TO_gpio_export,                    --                   gpio.export
			memory_addr                    => CONNECTED_TO_memory_addr,                    --                 memory.addr
			memory_ba                      => CONNECTED_TO_memory_ba,                      --                       .ba
			memory_cas_n                   => CONNECTED_TO_memory_cas_n,                   --                       .cas_n
			memory_cke                     => CONNECTED_TO_memory_cke,                     --                       .cke
			memory_cs_n                    => CONNECTED_TO_memory_cs_n,                    --                       .cs_n
			memory_dq                      => CONNECTED_TO_memory_dq,                      --                       .dq
			memory_dqm                     => CONNECTED_TO_memory_dqm,                     --                       .dqm
			memory_ras_n                   => CONNECTED_TO_memory_ras_n,                   --                       .ras_n
			memory_we_n                    => CONNECTED_TO_memory_we_n,                    --                       .we_n
			sdram_clk_clk                  => CONNECTED_TO_sdram_clk_clk,                  --              sdram_clk.clk
			spi_master_MISO                => CONNECTED_TO_spi_master_MISO,                --             spi_master.MISO
			spi_master_MOSI                => CONNECTED_TO_spi_master_MOSI,                --                       .MOSI
			spi_master_SCLK                => CONNECTED_TO_spi_master_SCLK,                --                       .SCLK
			spi_master_SS_n                => CONNECTED_TO_spi_master_SS_n,                --                       .SS_n
			spi_slave_MISO                 => CONNECTED_TO_spi_slave_MISO,                 --              spi_slave.MISO
			spi_slave_MOSI                 => CONNECTED_TO_spi_slave_MOSI,                 --                       .MOSI
			spi_slave_SCLK                 => CONNECTED_TO_spi_slave_SCLK,                 --                       .SCLK
			spi_slave_SS_n                 => CONNECTED_TO_spi_slave_SS_n,                 --                       .SS_n
			sw_external_connection_export  => CONNECTED_TO_sw_external_connection_export,  -- sw_external_connection.export
			vga_conduit_CLK                => CONNECTED_TO_vga_conduit_CLK,                --            vga_conduit.CLK
			vga_conduit_HS                 => CONNECTED_TO_vga_conduit_HS,                 --                       .HS
			vga_conduit_VS                 => CONNECTED_TO_vga_conduit_VS,                 --                       .VS
			vga_conduit_BLANK              => CONNECTED_TO_vga_conduit_BLANK,              --                       .BLANK
			vga_conduit_SYNC               => CONNECTED_TO_vga_conduit_SYNC,               --                       .SYNC
			vga_conduit_R                  => CONNECTED_TO_vga_conduit_R,                  --                       .R
			vga_conduit_G                  => CONNECTED_TO_vga_conduit_G,                  --                       .G
			vga_conduit_B                  => CONNECTED_TO_vga_conduit_B                   --                       .B
		);

