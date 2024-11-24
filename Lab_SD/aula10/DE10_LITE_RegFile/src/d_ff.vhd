-- Version: 1.1
-- Date: 07/11/2024
-- Owners: Gabriel D. Maruschi
--			  Vitor Alexandre Garcia Vaz

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.std_logic_arith.ALL;
USE ieee.std_logic_unsigned.ALL;

entity d_ff is
	port(
		clk		: IN STD_LOGIC;
		cr			: IN STD_LOGIC;
		d			: IN STD_LOGIC;
		q			: OUT STD_LOGIC
	
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
