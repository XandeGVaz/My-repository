-- Version: 1.1
-- Date: 07/11/2024
-- Owners: Gabriel D. Maruschi
--			  Vitor Garcia Vaz

ENTITY DE10_LITE_Reg IS
PORT(
		SW 	: IN BIT_VECTOR (9 DOWNTO 0);
		KEY	: IN BIT_VECTOR (1 DOWNTO 0);
		LEDR	: OUT BIT_VECTOR (7 DOWNTO 4)
	 );
END DE10_LITE_Reg;

ARCHITECTURE interface OF DE10_LITE_Reg IS
BEGIN
	REG: entity work.Reg
		GENERIC MAP(
		n => 4)
		PORT MAP(
		D => SW(7 DOWNTO 4), clk => KEY(0), cr => KEY(1), en => SW(9), Q => LEDR(7 DOWNTO 4));
END interface;

