ENTITY max6816 IS 
	PORT
	(
		KEY_IN :  IN  bit;
		CLK :  IN  bit;
		KEY_out :  OUT  bit
	);
END max6816;

ARCHITECTURE bdf_type OF max6816 IS 

	signal q_xnor : bit;
	signal q_out : bit_vector(3 downto 0);
	signal clk_div : bit_vector(15 downto 0);

BEGIN 

	cnt0: work.counter generic map (16) port map(CLK, '0', clk_div);

	dff0: work.d_ff port map (not q_out(3), '0', not KEY_IN, q_xnor);
	cnt1: work.counter generic map (4) port map(clk_div(15), not KEY_IN xnor q_xnor, q_out);
	KEY_OUT <= not q_xnor;


END bdf_type;