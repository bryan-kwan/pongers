	component top_level is
		port (
			clk_clk                         : in    std_logic                     := 'X';             -- clk
			ledr_external_connection_export : out   std_logic_vector(7 downto 0);                     -- export
			sw_external_connection_export   : in    std_logic_vector(7 downto 0)  := (others => 'X'); -- export
			memory_addr                     : out   std_logic_vector(12 downto 0);                    -- addr
			memory_ba                       : out   std_logic_vector(1 downto 0);                     -- ba
			memory_cas_n                    : out   std_logic;                                        -- cas_n
			memory_cke                      : out   std_logic;                                        -- cke
			memory_cs_n                     : out   std_logic;                                        -- cs_n
			memory_dq                       : inout std_logic_vector(15 downto 0) := (others => 'X'); -- dq
			memory_dqm                      : out   std_logic_vector(1 downto 0);                     -- dqm
			memory_ras_n                    : out   std_logic;                                        -- ras_n
			memory_we_n                     : out   std_logic;                                        -- we_n
			bridge_memory_address           : in    std_logic_vector(26 downto 0) := (others => 'X'); -- address
			bridge_memory_byte_enable       : in    std_logic_vector(1 downto 0)  := (others => 'X'); -- byte_enable
			bridge_memory_read              : in    std_logic                     := 'X';             -- read
			bridge_memory_write             : in    std_logic                     := 'X';             -- write
			bridge_memory_write_data        : in    std_logic_vector(15 downto 0) := (others => 'X'); -- write_data
			bridge_memory_acknowledge       : out   std_logic;                                        -- acknowledge
			bridge_memory_read_data         : out   std_logic_vector(15 downto 0);                    -- read_data
			vga_conduit_CLK                 : out   std_logic;                                        -- CLK
			vga_conduit_HS                  : out   std_logic;                                        -- HS
			vga_conduit_VS                  : out   std_logic;                                        -- VS
			vga_conduit_BLANK               : out   std_logic;                                        -- BLANK
			vga_conduit_SYNC                : out   std_logic;                                        -- SYNC
			vga_conduit_R                   : out   std_logic_vector(3 downto 0);                     -- R
			vga_conduit_G                   : out   std_logic_vector(3 downto 0);                     -- G
			vga_conduit_B                   : out   std_logic_vector(3 downto 0)                      -- B
		);
	end component top_level;

	u0 : component top_level
		port map (
			clk_clk                         => CONNECTED_TO_clk_clk,                         --                      clk.clk
			ledr_external_connection_export => CONNECTED_TO_ledr_external_connection_export, -- ledr_external_connection.export
			sw_external_connection_export   => CONNECTED_TO_sw_external_connection_export,   --   sw_external_connection.export
			memory_addr                     => CONNECTED_TO_memory_addr,                     --                   memory.addr
			memory_ba                       => CONNECTED_TO_memory_ba,                       --                         .ba
			memory_cas_n                    => CONNECTED_TO_memory_cas_n,                    --                         .cas_n
			memory_cke                      => CONNECTED_TO_memory_cke,                      --                         .cke
			memory_cs_n                     => CONNECTED_TO_memory_cs_n,                     --                         .cs_n
			memory_dq                       => CONNECTED_TO_memory_dq,                       --                         .dq
			memory_dqm                      => CONNECTED_TO_memory_dqm,                      --                         .dqm
			memory_ras_n                    => CONNECTED_TO_memory_ras_n,                    --                         .ras_n
			memory_we_n                     => CONNECTED_TO_memory_we_n,                     --                         .we_n
			bridge_memory_address           => CONNECTED_TO_bridge_memory_address,           --            bridge_memory.address
			bridge_memory_byte_enable       => CONNECTED_TO_bridge_memory_byte_enable,       --                         .byte_enable
			bridge_memory_read              => CONNECTED_TO_bridge_memory_read,              --                         .read
			bridge_memory_write             => CONNECTED_TO_bridge_memory_write,             --                         .write
			bridge_memory_write_data        => CONNECTED_TO_bridge_memory_write_data,        --                         .write_data
			bridge_memory_acknowledge       => CONNECTED_TO_bridge_memory_acknowledge,       --                         .acknowledge
			bridge_memory_read_data         => CONNECTED_TO_bridge_memory_read_data,         --                         .read_data
			vga_conduit_CLK                 => CONNECTED_TO_vga_conduit_CLK,                 --              vga_conduit.CLK
			vga_conduit_HS                  => CONNECTED_TO_vga_conduit_HS,                  --                         .HS
			vga_conduit_VS                  => CONNECTED_TO_vga_conduit_VS,                  --                         .VS
			vga_conduit_BLANK               => CONNECTED_TO_vga_conduit_BLANK,               --                         .BLANK
			vga_conduit_SYNC                => CONNECTED_TO_vga_conduit_SYNC,                --                         .SYNC
			vga_conduit_R                   => CONNECTED_TO_vga_conduit_R,                   --                         .R
			vga_conduit_G                   => CONNECTED_TO_vga_conduit_G,                   --                         .G
			vga_conduit_B                   => CONNECTED_TO_vga_conduit_B                    --                         .B
		);

