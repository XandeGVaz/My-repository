-- Version: 1.1
-- Date: 07/11/2024
-- Owners: Gabriel D. Maruschi
--			  Vitor Garcia Vaz

ENTITY Reg IS
	GENERIC (n		:	INTEGER	:=	4);
	PORT (clk	:	IN	BIT;
			en		:	IN BIT;
			cr		:	IN BIT;
			D		: 	IN BIT_VECTOR (n-1 DOWNTO 0);
			Q		:	OUT BIT_VECTOR (n-1 DOWNTO 0));
END Reg;

ARCHITECTURE estrutural OF Reg IS

	SIGNAL aux	: BIT;
	
BEGIN
	
	aux <= clk AND en;
		
	regis_gen: FOR i IN 0 TO n-1 GENERATE
		
			FF: entity work.d_ff
				PORT MAP(
					clk => aux, cr => cr, d => D(i), q => Q(i)
					);
					
		END GENERATE regis_gen;

END estrutural;
		
		