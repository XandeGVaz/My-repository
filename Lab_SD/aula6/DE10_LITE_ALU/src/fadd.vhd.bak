-- Projeto somador completo
-- Aula 06 - SEL0384/sel0606
-- Professor: Maximiliam Luppe
-- Data: 04/10/2023

entity fadd is
	port
		(
			a, b, ci	: in bit;
			s, co		: out bit
		);
end fadd;

architecture concorrente of fadd is
begin

	-- implementacao da saida s
	s <= a xor b xor ci;
	
	-- implementacao da saida co
	co <= (a and (b or ci)) or (b and ci);

end;

		