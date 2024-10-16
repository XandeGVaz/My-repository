entity DE10_LITE_ALU is
	port
	(
		HEX0		: out bit_vector(7 downto 0);

		SW			: in bit_vector(9 downto 0);
		KEY		: in bit_vector(1 downto 0);

		LEDR 		: out bit_vector(9 downto 0)
	);

end DE10_LITE_ALU;


architecture top of DE10_LITE_ALU is

	signal ALUResult: bit_vector(3 downto 0);

begin

	-- Component Instantiation Statement
	
	ALU0: work.alu
		port map (
				A => SW(3 downto 0), B => SW(7 downto 4), ALUControl => SW(9 downto 8) & KEY(0), 
				Result => ALUResult, Zero => LEDR(0)
				);

	display0: work.hex27seg
		port map (
				hexa => ALUResult, 
				segments => HEX0(6 downto 0)
				);

end top;