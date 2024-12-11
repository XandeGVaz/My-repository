-- Version: 1.1
-- Date: --/11/2024
-- Owners: Gabriel D. Maruschi
--			  Vitor Alexandre Garcia Vaz

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.std_logic_arith.ALL;
USE ieee.std_logic_unsigned.ALL;

ENTITY decode24 is

    PORt (
        ENT      : IN STD_LOGIC_VECTOR (1 downto 0);
        OUTPUT0  : OUT STD_LOGIC;
        OUTPUT1  : OUT STD_LOGIC;
        OUTPUT2  : OUT STD_LOGIC;
        OUTPUT3  : OUT STD_LOGIC
    );
end decode24;


ARCHITECTURE decode24_module OF decode24 IS
    signal aux  : STD_LOGIC_VECTOR (0 to 3);

BEGIN

	with ENT select
	aux <= 	"1000" when "00",
            "0100" when "01",
            "0010" when "10",
            "0001" when "11";
    
    OUTPUT0 <= aux(0);
    OUTPUT1 <= aux(1);
    OUTPUT2 <= aux(2);
    OUTPUT3 <= aux(3);

END decode24_module;