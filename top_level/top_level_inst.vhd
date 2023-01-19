	component top_level is
		port (
			clk_clk                         : in  std_logic                    := 'X';             -- clk
			ledr_external_connection_export : out std_logic_vector(7 downto 0);                    -- export
			sw_external_connection_export   : in  std_logic_vector(7 downto 0) := (others => 'X'); -- export
			vga_conduit_CLK                 : out std_logic;                                       -- CLK
			vga_conduit_HS                  : out std_logic;                                       -- HS
			vga_conduit_VS                  : out std_logic;                                       -- VS
			vga_conduit_BLANK               : out std_logic;                                       -- BLANK
			vga_conduit_SYNC                : out std_logic;                                       -- SYNC
			vga_conduit_R                   : out std_logic_vector(3 downto 0);                    -- R
			vga_conduit_G                   : out std_logic_vector(3 downto 0);                    -- G
			vga_conduit_B                   : out std_logic_vector(3 downto 0)                     -- B
		);
	end component top_level;

	u0 : component top_level
		port map (
			clk_clk                         => CONNECTED_TO_clk_clk,                         --                      clk.clk
			ledr_external_connection_export => CONNECTED_TO_ledr_external_connection_export, -- ledr_external_connection.export
			sw_external_connection_export   => CONNECTED_TO_sw_external_connection_export,   --   sw_external_connection.export
			vga_conduit_CLK                 => CONNECTED_TO_vga_conduit_CLK,                 --              vga_conduit.CLK
			vga_conduit_HS                  => CONNECTED_TO_vga_conduit_HS,                  --                         .HS
			vga_conduit_VS                  => CONNECTED_TO_vga_conduit_VS,                  --                         .VS
			vga_conduit_BLANK               => CONNECTED_TO_vga_conduit_BLANK,               --                         .BLANK
			vga_conduit_SYNC                => CONNECTED_TO_vga_conduit_SYNC,                --                         .SYNC
			vga_conduit_R                   => CONNECTED_TO_vga_conduit_R,                   --                         .R
			vga_conduit_G                   => CONNECTED_TO_vga_conduit_G,                   --                         .G
			vga_conduit_B                   => CONNECTED_TO_vga_conduit_B                    --                         .B
		);

