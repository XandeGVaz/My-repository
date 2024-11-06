
--Copryght:		
--Date:		23/10/24
--Version:	1.0
--Owners:	Gabriel D. Maruschi
-- 			Vitor Alexandre Garcia Vaz

ENTITY DE10_LITE_FF IS
	PORT
	(
		SW		:	IN 	BIT_VECTOR(9 DOWNTO 0);
		KEY	: 	IN 	BIT_VECTOR(1 DOWNTO 0);
		LEDR	: 	OUT	BIT_VECTOR(9 DOWNTO 0)
	);
END DE10_LITE_FF;

ARCHITECTURE top OF DE10_LITE_FF IS

BEGIN

	JKFF: work.jk_ff
		PORT MAP
		(
			j => SW(3), k => SW(2), clk => KEY(0), cr => KEY(1), q => LEDR(2)
		);


	DFF: work.d_ff
		PORT MAP
		(
			d => SW(1), clk => KEY(0), cr => KEY(1), q => LEDR(1)
		);
		
		
	TFF: work.t_ff
		PORT MAP
		(
			t => SW(0), clk => KEY(0), cr => KEY(1), q => LEDR(0)
		);
		
END top;