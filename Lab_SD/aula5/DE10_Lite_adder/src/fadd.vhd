entity fadd is
		port(
			a, b , cin		: in bit;
			s, cout			: out bit
			);
end fadd;

architecture top_down of fadd is

	signal aux : bit_vector (2 downto 0);
	
begin
	
	-- concatena abcin
	aux <= a & b & cin;
	
	--whith select
	with aux select
		s <= '0' when "000",
				'1' when "001",
				'1' when "010",
				'0' when "011",
				'1' when "100",
				'0' when "101",
				'0' when "110",
				'1' when others;

	--when else
	cout <= '0' when aux = "000" else
				'0' when aux = "001" else 
				'0' when aux = "010" else
				'1' when aux = "011" else
				'0' when aux = "100" else
				'1' when aux = "101" else
				'1' when aux = "110" else
				'1';

end top_down;
