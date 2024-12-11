-- Version: 1.1
-- Date: 07/11/2024
-- Owners: Gabriel D. Maruschi
--			  Vitor Garcia Vaz

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.std_logic_arith.ALL;
USE ieee.std_logic_unsigned.ALL;

ENTITY DE10_LITE_FSM IS 
    PORT(  
        SW : IN STD_LOGIC_VECTOR(9 DOWNTO 0);
        KEY : IN STD_LOGIC_VECTOR(1 DOWNTO 0);
        LEDR : OUT STD_LOGIC_VECTOR(9 DOWNTO 0);
		HEX0 : OUT STD_LOGIC_VECTOR(7 downto 0);
		HEX1 : OUT STD_LOGIC_VECTOR(7 downto 0);
		HEX2 : OUT STD_LOGIC_VECTOR(7 downto 0);
		HEX3 : OUT STD_LOGIC_VECTOR(7 downto 0);
		HEX4 : OUT STD_LOGIC_VECTOR(7 downto 0)
    );
END DE10_LITE_FSM;


ARCHITECTURE estrutural OF DE10_LITE_FSM IS

    -- Vetores de sinais de controle internos
    signal intResultSrc : std_logic_vector(1 downto 0);
    signal intALUControl : std_logic_vector(2 downto 0);
    signal intALUSrcB : std_logic_vector(1 downto 0);
    signal intALUSrcA : std_logic_vector(1 downto 0);
    signal intImmSrc : std_logic_vector(1 downto 0);

    -- Vetores de sinais de controle internos extendidos para 4 bits
    signal extResultSrc : std_logic_vector(3 downto 0);
    signal extALUControl : std_logic_vector(3 downto 0);
    signal extALUSrcB : std_logic_vector(3 downto 0);
    signal extALUSrcA : std_logic_vector(3 downto 0);
    signal extImmSrc : std_logic_vector(3 downto 0);
BEGIN

    -- Instanciação do módulo FSM
    FSM: entity work.FSM
        PORT MAP (
            clk => not KEY(0),
            clr => KEY(1),
            zero => SW(5),
            op => SW(1 downto 0),
            funct3 => SW(4 downto 2),
            PCWrite => LEDR(0),
            AdrSrc => LEDR(1),
            MemWrite => LEDR(2),
            IRWrite => LEDR(3),
            ResultSrc => intResultSrc(1 downto 0),
            ALUControl => intALUControl(2 downto 0),
            ALUSrcB => intALUSrcB(1 downto 0),
            ALUSrcA => intALUSrcA(1 downto 0),
            ImmSrc => intImmSrc(1 downto 0),
            RegWrite => LEDR(4)
        );
    
    -- Extensão dos sinais de controle para 4 bits
    extResultSrc <= "00" & intResultSrc;
    extALUControl <= '0' & intALUControl;
    extALUSrcB <= "00" & intALUSrcB;
    extALUSrcA <= "00" & intALUSrcA;
    extImmSrc <= "00" & intImmSrc;

    -- Displays de 7 segmentos
    display1: entity work.hex27seg
        PORT MAP (
            hexa => extResultSrc,
            segments => HEX0
        );

    display2: entity work.hex27seg
        PORT MAP (
            hexa => extALUControl,
            segments => HEX1
        );

    display3: entity work.hex27seg
        PORT MAP (
            hexa => extALUSrcB,
            segments => HEX2
        );

    display4: entity work.hex27seg
        PORT MAP (
            hexa => extALUSrcA,
            segments => HEX3
        );

    display5: entity work.hex27seg
        PORT MAP (
            hexa => extImmSrc,
            segments => HEX4
        );

END estrutural;