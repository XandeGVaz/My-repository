--Copryght:		
--Date:		23/10/24
--Version:	1.0
--Owners:	Gabriel D. Maruschi
-- 			Vitor Alexandre Garcia Vaz

ENTITY  jk_ff IS
	PORT
	(
		cr		: IN BIT;
		j, k	: IN BIT;
		clk	: IN BIT;
		q		: OUT BIT
	);
END jk_ff;

ARCHITECTURE jkff_module OF jk_ff IS

BEGIN
	PROCESS(clk, cr)
	VARIABLE qs	: BIT;
	BEGIN
		IF(cr = '1') THEN qs := '0';
		
		ELSIF(clk'EVENT and clk = '1') THEN
			qs := (j AND NOT qs) OR (NOT k AND qs);
		
		END IF;
		q <= qs;
	END PROCESS;
END jkff_module;
		
	