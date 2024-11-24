-- Version: 1.1
-- Date: --/11/2024
-- Owners: Gabriel D. Maruschi
--              Vitor Alexandre Garcia Vaz

LIBRARY ieee;
USE ieee.std_logic_1164.ALL; -- tipos de dados lógicos std_logic e std_logic_vector
USE ieee.std_logic_arith.ALL; -- operações aritméticas com std_logic_vector
USE ieee.std_logic_unsigned.ALL; -- operações aritméticas com std_logic_vector como unsigned

ENTITY regbank IS
    GENERIC (
        M : INTEGER := 8; -- Número de registradores
        X : INTEGER := 4  -- Largura de cada registrador
    );
    PORT (
        CLK : IN std_logic; -- Clock
        EN : IN std_logic; -- Habilita o banco de registradores
        WE3 : IN std_logic; -- Habilita a escrita
        WD3 : IN std_logic_vector(X-1 DOWNTO 0); -- Dados a serem escritos
        A1 : IN std_logic_vector(2 DOWNTO 0); -- Seleção do registrador 1 para leitura
        A2 : IN std_logic_vector(2 DOWNTO 0); -- Seleção do registrador 2 para leitura
        A3 : IN std_logic_vector(2 DOWNTO 0); -- Seleção do registrador para escrita
        RD1 : OUT std_logic_vector(X-1 DOWNTO 0); -- Saída do registrador 1
        RD2 : OUT std_logic_vector(X-1 DOWNTO 0) -- Saída do registrador 2
    );
END regbank;

ARCHITECTURE estrutural OF regbank IS
    
    -- Declaração de tipos
    TYPE reg_array IS ARRAY (0 TO M-1) OF std_logic_vector(X-1 DOWNTO 0);
    
    -- Declaração de sinais internos
    signal outDecoder : std_logic_vector(M-1 DOWNTO 0); -- Saída do decodificador
    signal regEscrita : std_logic_vector(M-1 DOWNTO 0); -- Habilita a escrita em cada registrador
    signal outRegister : reg_array; -- Saída de cada registrador
    signal outMux1 : std_logic_vector(X-1 DOWNTO 0); -- Saída do multiplexador 1
    signal outMux2 : std_logic_vector(X-1 DOWNTO 0); -- Saída do multiplexador 2
BEGIN
	
	-- Decoder 1 : M
	decoder: entity work.decode38
        PORT MAP(
            ENT => A3,
            OUTPUT0 => outDecoder(0),
            OUTPUT1 => outDecoder(1),
            OUTPUT2 => outDecoder(2),
            OUTPUT3 => outDecoder(3),
            OUTPUT4 => outDecoder(4),
            OUTPUT5 => outDecoder(5),
            OUTPUT6 => outDecoder(6),
            OUTPUT7 => outDecoder(7)
        );

    -- Banco de M registradores
    registers: FOR i in 0 to M-1 generate
        regEscrita(i) <= outDecoder(i) AND WE3;
        reg : entity work.Reg
            PORT MAP(
                clk => CLK AND EN,
                en => regEscrita(i),
                cr => '0',
                D => WD3,
                Q => outRegister(i)
            );
    END generate registers;

    -- Multiplexadores M : 1
    mux1: entity work.mux81
        PORT MAP(
            INPUT0 => outRegister(0),
            INPUT1 => outRegister(1),
            INPUT2 => outRegister(2),
            INPUT3 => outRegister(3),
            INPUT4 => outRegister(4),
            INPUT5 => outRegister(5),
            INPUT6 => outRegister(6),
            INPUT7 => outRegister(7),
            S => A1,
            R => outMux1
        );

    mux2: entity work.mux81
        PORT MAP(
            INPUT0 => outRegister(0),
            INPUT1 => outRegister(1),
            INPUT2 => outRegister(2),
            INPUT3 => outRegister(3),
            INPUT4 => outRegister(4),
            INPUT5 => outRegister(5),
            INPUT6 => outRegister(6),
            INPUT7 => outRegister(7),
            S => A2,
            R => outMux2
        );

    -- Conectando as saídas dos multiplexadores às saídas do banco de registradores
    RD1 <= outMux1;
    RD2 <= outMux2;
END estrutural;