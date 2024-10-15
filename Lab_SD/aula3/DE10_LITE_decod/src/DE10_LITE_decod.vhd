-- Copyright
-- Name: DE10_LITE_decod
-- Date: 25/09/2024
-- Version:
-- Owners

entity DE10_LITE_decod is
	port
	(
		SW 	: in bit_vector(9 downto 0);		--Chaves
		HEX0	: out bit_vector(7 downto 0)		--Display
	);
end DE10_LITE_decod;

architecture netlist of DE10_LITE_decod is

begin
	-- Segmento 'a'
	HEX0(0) <= (NOT SW(3) AND NOT SW(2) AND NOT SW(1) AND SW(0)) OR (NOT SW(3) AND SW(2) AND NOT SW(1) AND NOT SW(0)) OR (SW(3) AND SW(2) AND NOT SW(1) AND SW(0)) OR (SW(3) AND NOT SW(2) AND SW(1) AND SW(0));
	
	-- Segmento 'b'
	HEX0(1) <= (NOT SW(3) AND SW(2) AND NOT SW(1) AND SW(0)) OR (SW(3) AND SW(2) AND NOT SW(0)) OR (SW(2) AND SW(1) AND NOT SW(0)) OR (SW(3) AND SW(1) AND SW(0));
	
	-- Segmento 'c'
	HEX0(2) <= (NOT SW(3) AND NOT SW(2) AND SW(1) AND NOT SW(0)) OR (SW(3) AND SW(2) AND NOT SW(0)) OR (SW(3) AND SW(2) AND SW(1));
	
	-- Segmento 'd'
	HEX0(3) <= (NOT SW(3) AND NOT SW(2) AND NOT SW(1) AND SW(0)) OR (NOT SW(3) AND SW(2) AND NOT SW(1) AND NOT SW(0)) OR (SW(2) AND SW(1) AND SW(0)) OR (SW(3) AND NOT SW(2) AND SW(1) AND NOT SW(0));
	
	-- Segmento 'e'
	HEX0(4) <= (NOT SW(3) AND SW(0)) OR (NOT SW(2) AND NOT SW(1) AND SW(0)) OR (NOT SW(3) AND SW(2) AND NOT SW(1));
	
	-- Segmento 'f'
	HEX0(5) <= (NOT SW(3) AND NOT SW(2) AND SW(0)) OR (NOT SW(3) AND NOT SW(2) AND SW(1)) OR (NOT SW(3) AND SW(1) AND SW(0)) OR (SW(3) AND SW(2) AND NOT SW(1) AND SW(0));
	
	-- Segmento 'g'
	HEX0(6) <= (NOT SW(3) AND NOT SW(2) AND NOT SW(1)) OR (NOT SW(3) AND SW(2) AND SW(1) AND SW(0)) OR (SW(3) AND SW(2) AND NOT SW(1) AND NOT SW(0));
	
	-- Ponto decimal
	HEX0(7) <= '1';		--Apagado
end;