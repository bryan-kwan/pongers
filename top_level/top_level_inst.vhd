	component top_level is
		port (
			clk_clk                         : in  std_logic                    := 'X';             -- clk
			ledr_external_connection_export : out std_logic_vector(7 downto 0);                    -- export
			sw_external_connection_export   : in  std_logic_vector(7 downto 0) := (others => 'X')  -- export
		);
	end component top_level;

	u0 : component top_level
		port map (
			clk_clk                         => CONNECTED_TO_clk_clk,                         --                      clk.clk
			ledr_external_connection_export => CONNECTED_TO_ledr_external_connection_export, -- ledr_external_connection.export
			sw_external_connection_export   => CONNECTED_TO_sw_external_connection_export    --   sw_external_connection.export
		);

