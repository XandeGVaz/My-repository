-- Version: 1.1
-- Date: --/11/2024
-- Owners: Gabriel D. Maruschi
--			  Vitor Alexandre Garcia Vaz

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.std_logic_arith.ALL;
USE ieee.std_logic_unsigned.ALL;

ENTITY decode38 is

    PORt (
        ENT      : IN STD_LOGIC_VECTOR (2 downto 0);
        OUTPUT0  : OUT STD_LOGIC;
        OUTPUT1  : OUT STD_LOGIC;
        OUTPUT2  : OUT STD_LOGIC;
        OUTPUT3  : OUT STD_LOGIC;
        OUTPUT4  : OUT STD_LOGIC;
        OUTPUT5  : OUT STD_LOGIC;
        OUTPUT6  : OUT STD_LOGIC;
        OUTPUT7  : OUT STD_LOGIC
    );
end decode38;


ARCHITECTURE decode38_module OF decode38 IS

    signal aux  : STD_LOGIC_VECTOR (7 downto 0);

BEGIN

	with ENT select
	aux <= 	"10000000" when "000",
            "01000000" when "001",
            "00100000" when "010",
            "00010000" when "011",
            "00001000" when "100",
            "00000100" when "101",
            "00000010" when "110",
            "00000001" when "111";
    
    OUTPUT0 <= aux(0);
    OUTPUT1 <= aux(1);
    OUTPUT2 <= aux(2);
    OUTPUT3 <= aux(3);
    OUTPUT4 <= aux(4);
    OUTPUT5 <= aux(5);
    OUTPUT6 <= aux(6);
    OUTPUT7 <= aux(7);

END decode38_module;