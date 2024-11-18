--oi 2

ENTITY DE10_LITE_counter IS 
	PORT (
		KEY : IN BIT_VECTOR(1 DOWNTO 0);
		LEDR: OUT BIT_VECTOR(9 DOWNTO 0);
		HEX0: OUT BIT_VECTOR(7 DOWNTO 0));
		
		
END DE10_LITE_counter;

ARCHITECTURE interface OF DE10_LITE_counter IS
SIGNAL aux : BIT_VECTOR(3 DOWNTO 0);
BEGIN
	count: entity work.counter
		GENERIC MAP(n => 4)
		PORT MAP(clk => KEY(0), clrn => KEY(1), Q => aux);
		
		LEDR(9 DOWNTO 6) <= aux;
		
	display: entity work.hex27seg
		PORT MAP(hexa => aux, segments => HEX0);
END interface;