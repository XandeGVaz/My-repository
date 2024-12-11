-- Version: 1.1
-- Date: --/11/2024
-- Owners: Gabriel D. Maruschi
--			  Vitor Alexandre Garcia Vaz

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.std_logic_arith.ALL;
USE ieee.std_logic_unsigned.ALL;

ENTITY DE10_LITE_RegFile IS
    PORT (
        SW : IN STD_LOGIC_VECTOR(9 DOWNTO 0);
        KEY : IN STD_LOGIC_VECTOR(1 DOWNTO 0);
        LEDR : OUT STD_LOGIC_VECTOR(9 DOWNTO 0);
		  HEX0 : OUT STD_LOGIC_VECTOR(7 downto 0);
		  HEX1 : OUT STD_LOGIC_VECTOR(7 downto 0)
    );
END DE10_LITE_RegFile;


ARCHITECTURE estrutural OF DE10_LITE_RegFile IS

	signal aux1 : STD_LOGIC_VECTOR (3 downto 0);
	signal aux2 : STD_LOGIC_VECTOR (3 downto 0);

BEGIN
    RegBank: entity work.regbank

        GENERIC MAP (
            M => 4,
            X => 4
        )

        PORT MAP (
            CLK => not KEY(0),
            EN => '1',
            WE3 => not KEY(1),
            WD3 => SW(9 DOWNTO 6),
            A1 => SW(1 DOWNTO 0),
            A2 => SW(3 DOWNTO 2),
            A3 => SW(5 DOWNTO 4),
            RD1 => aux1,
            RD2 => aux2
        );
		  
	display1: entity work.hex27seg
		PORT MAP (
			hexa => aux1,
			segments => HEX0
		);
		
	display2: entity work.hex27seg
		PORT MAP (
			hexa => aux2,
			segments => HEX1
		);
		  
	LEDR(3 downto 0) <= aux1;
	LEDR(7 downto 4) <= aux2;

END estrutural;