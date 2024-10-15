--Copryght:		
--Date:		02/10/24
--Version:	1.0
--Owners:	Gabriel D. Maruschi
-- 			Vitor Alexandre Garcia Vaz

entity DE10_Lite_mux is
	port (
			SW		: in bit_vector(9 downto 0);
			KEY	: in bit_vector(1 downto 0);
			LEDR	: out bit_vector(9 downto 0)
			);
end DE10_Lite_mux;

architecture concurrent of DE10_Lite_mux is

--Declaração de sinais internos

begin

	LEDR(3 downto 0) <= 
		SW(3 downto 0) when KEY(0) = '0' else
		SW(7 downto 4); 


end concurrent;
			