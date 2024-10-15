entity adder is 
	port(
		A, B		: in bit_vector(3 downto 0);
		Result	: out bit_vector(3 downto 0)
		);
end adder;

architecture top_down of adder is
	--declaracao do componente fadd
	component fadd
		port(
			a, b , cin		: in bit;
			s, cout			: out bit
			);
	end component; 
	
	-- declaracao do carry interno (ripple carry)
	
	signal carry : bit_vector( 4 downto 1 );
	
begin
	
	fa0: fadd port map (A(0), B(0), '0'		, Result(0), carry(1));
	fa1: fadd port map (A(1), B(1), carry(1), Result(1), carry(2));
	fa2: fadd port map (A(2), B(2), carry(2), Result(2), carry(3));
	fa3: fadd port map (A(3), B(3), carry(3), Result(3), carry(4));
	
end top_down;
	