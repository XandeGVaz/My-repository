--Copryght:		
--Date:		23/10/24
--Version:	1.0
--Owners:	Gabriel D. Maruschi
-- 			Vitor Alexandre Garcia Vaz

ENTITY  t_ff IS
	PORT
	(
		cr		: IN BIT;
		t		: IN BIT;
		clk	: IN BIT;
		q		: OUT BIT
	);
END t_ff;

ARCHITECTURE tff_module OF t_ff IS

BEGIN
	PROCESS(clk, cr)
	VARIABLE qs	: BIT;
	BEGIN
		IF(cr = '1') THEN qs := '0';
		
		ELSIF(clk'EVENT and clk = '1') THEN
			qs := (t AND NOT qs) OR (NOT t AND qs);
		
		END IF;
		q <= qs;
	END PROCESS;
END tff_module;