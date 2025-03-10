-- Copyright
-- Name: DE10_LITE_decod
-- Date: 23/10/2024
-- Version: 1.1
-- Owners:	Gabriel Dezejácomo Maruschi
--				Vitor Alexandre Garcia Vaz

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.std_logic_arith.ALL;
USE ieee.std_logic_unsigned.ALL;


entity hex27seg is
	port
	(
		hexa 		: in STD_LOGIC_VECTOR(3 downto 0);	--entrada de 4 bits
		segments	: out STD_LOGIC_VECTOR(7 downto 0)	--Display
	);
end hex27seg;

architecture logica of hex27seg is

begin
	-- Segmento 'a'
	segments(0) <= (NOT hexa(3) AND NOT hexa(2) AND NOT hexa(1) AND hexa(0)) OR (NOT hexa(3) AND hexa(2) AND NOT hexa(1) AND NOT hexa(0)) OR (hexa(3) AND hexa(2) AND NOT hexa(1) AND hexa(0)) OR (hexa(3) AND NOT hexa(2) AND hexa(1) 
	AND hexa(0));
	
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