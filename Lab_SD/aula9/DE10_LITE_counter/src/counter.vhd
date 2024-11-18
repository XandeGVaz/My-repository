--oi

entity counter is
	generic (
		n		: integer :=	4
	);
	
	port(
		clk	: IN BIT;
		clrn	: IN BIT;
		Q		: OUT BIT_VECTOR (n-1 downto 0)
	);
END counter;


ARCHITECTURE estrutural of counter is

	signal qaux	: bit_vector (n-1 downto 0);
	signal qand	: bit_vector (n-1 downto 0);

BEGIN
	

	FF0:	entity work.jk_ff PORT MAP (clk => clk, cr => clrn, j => '1', k => '1', q => qaux(0));
	
	
	qand(0) <= qaux (0);
	
	
	abc: FOR i IN 1 TO n-1 GENERATE
	
	
		FF: entity work.jk_ff PORT MAP ( clk => clk, cr => clrn , j => qand(i-1), k => qand(i-1), q => qaux(i));
		
		qand(i) <= qaux(i) AND qand(i-1);
		
		
	END GENERATE abc;
	
	
	Q <= qaux;
	
	
end estrutural;