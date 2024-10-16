-- Copyright
-- Name: DE10_LITE_decod
-- Date: 25/09/2024
-- Version:
-- Owners:	Gabriel Dezejácomo Maruschi
--			Vitor Alexandre Garcia Vaz

entity hex27seg is
	port
	(
		hexa 		: in bit_vector(3 downto 0);	--entrada de 4 bits
		segments	: out bit_vector(7 downto 0)	--Display
	);
end hex27seg;

architecture logica of hex27seg is

begin
	-- Segmento 'a'
	segments(0) <= (NOT hexa(3) AND NOT hexa(2) AND NOT hexa(1) AND hexa(0)) OR (NOT hexa(3) AND hexa(2) AND NOT hexa(1) AND NOT hexa(0)) OR (hexa(3) AND hexa(2) AND NOT hexa(1) AND hexa(0)) OR (hexa(3) AND NOT hexa(2) AND hexa(1) AND hexa(0));
	
	-- Segmento 'b'
	segments(1) <= (NOT hexa(3) AND hexa(2) AND NOT hexa(1) AND hexa(0)) OR (hexa(3) AND hexa(2) AND NOT hexa(0)) OR (hexa(2) AND hexa(1) AND NOT hexa(0)) OR (hexa(3) AND hexa(1) AND hexa(0));
	
	-- Segmento 'c'
	segments(2) <= (NOT hexa(3) AND NOT hexa(2) AND hexa(1) AND NOT hexa(0)) OR (hexa(3) AND hexa(2) AND NOT hexa(0)) OR (hexa(3) AND hexa(2) AND hexa(1));
	
	-- Segmento 'd'
	segments(3) <= (NOT hexa(3) AND NOT hexa(2) AND NOT hexa(1) AND hexa(0)) OR (NOT hexa(3) AND hexa(2) AND NOT hexa(1) AND NOT hexa(0)) OR (hexa(2) AND hexa(1) AND hexa(0)) OR (hexa(3) AND NOT hexa(2) AND hexa(1) AND NOT hexa(0));
	
	-- Segmento 'e'
	segments(4) <= (NOT hexa(3) AND hexa(0)) OR (NOT hexa(2) AND NOT hexa(1) AND hexa(0)) OR (NOT hexa(3) AND hexa(2) AND NOT hexa(1));
	
	-- Segmento 'f'
	segments(5) <= (NOT hexa(3) AND NOT hexa(2) AND hexa(0)) OR (NOT hexa(3) AND NOT hexa(2) AND hexa(1)) OR (NOT hexa(3) AND hexa(1) AND hexa(0)) OR (hexa(3) AND hexa(2) AND NOT hexa(1) AND hexa(0));
	
	-- Segmento 'g'
	segments(6) <= (NOT hexa(3) AND NOT hexa(2) AND NOT hexa(1)) OR (NOT hexa(3) AND hexa(2) AND hexa(1) AND hexa(0)) OR (hexa(3) AND hexa(2) AND NOT hexa(1) AND NOT hexa(0));
	
	-- Ponto decimal
	segments(7) <= '1';		--Apagado
end;