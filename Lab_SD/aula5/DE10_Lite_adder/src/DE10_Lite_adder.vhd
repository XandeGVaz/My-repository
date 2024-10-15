entity DE10_Lite_adder is
port(
	SW		: in bit_vector(9 downto 0);
	LEDR 	: out bit_vector(9 downto 0)
	);
end DE10_Lite_adder;

architecture top_down of DE10_Lite_adder is
	-- declaração dos componentes adder
	component adder
		port(
			A, B 		: in bit_vector(3 downto 0);
			RESULT	: out bit_vector(3 downto 0)
			);
	end component;

begin
	-- solicitação do componente adder
	somador: adder port map (SW(3 downto 0), SW(7 downto 4), LEDR(3 downto 0));
	
end top_down;
