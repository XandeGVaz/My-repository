-- Projeto multiplexador 2 para 1
-- Aula 06 - SEL0384/SEL0606
-- Professor: Maximiliam Luppe
-- Data: 04/10/2023

entity mux21 is
	port
	(
		I0, I1	: in bit_vector(3 downto 0);
		S			: in bit;
		Z			: out bit_vector(3 downto 0)
	);
end mux21;

architecture concorrente of mux21 is
begin

	with S select
		Z <= I0 when '0',
		     I1 when '1';

end;
