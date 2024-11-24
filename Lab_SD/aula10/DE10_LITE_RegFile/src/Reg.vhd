-- Version: 1.1
-- Date: 07/11/2024
-- Owners: Gabriel D. Maruschi
--			  Vitor Garcia Vaz

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.std_logic_arith.ALL;
USE ieee.std_logic_unsigned.ALL;

ENTITY Reg IS
	GENERIC (n		:	INTEGER	:=	4);
	PORT (clk	:	IN	STD_LOGIC;
			en		:	IN STD_LOGIC;
			cr		:	IN STD_LOGIC;
			D		: 	IN STD_LOGIC_VECTOR (n-1 DOWNTO 0);
			Q		:	OUT STD_LOGIC_VECTOR (n-1 DOWNTO 0));
END Reg;

ARCHITECTURE estrutural OF Reg IS

	SIGNAL aux	: STD_LOGIC;
	
BEGIN
	
	aux <= clk AND en;
		
	regis_gen: FOR i IN 0 TO n-1 GENERATE
		
			FF: entity work.d_ff
				PORT MAP(
					clk => aux, cr => cr, d => D(i), q => Q(i)
					);
					
		END GENERATE regis_gen;

END estrutural;
		
		