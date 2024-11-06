--Copryght:		
--Date:		23/10/24
--Version:	1.0
--Owners:	Gabriel D. Maruschi
-- 			Vitor Alexandre Garcia Vaz

entity d_ff is
	port(
		clk		: IN bit;
		cr			: IN bit;
		d			: IN bit;
		q			: OUT bit
	
	);
end d_ff;


architecture dff_module of d_ff is

----
BEGIN
	PROCESS (clk, cr)
		BEGIN

			IF cr = '1' then q <= '0';
			
			ELSIF (clk'EVENT and clk = '1') then q <= d;
			
			END IF;
			
	END PROCESS;

end dff_module;
