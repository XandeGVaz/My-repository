-- Version: 1.1
-- Date: 07/11/2024
-- Owners: Gabriel D. Maruschi
--			  Vitor Garcia Vaz

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.std_logic_arith.ALL;
USE ieee.std_logic_unsigned.ALL;

ENTITY FSM is
    PORT(

        -- Entradas
        clk     : in std_logic;
        clr     : in std_logic;
        zero    : in std_logic;
        op      : in std_logic_vector(1 downto 0);
        funct3  : in std_logic_vector(2 downto 0);

        -- Saídas (Sinais de controle)
        PCWrite     : out std_logic;
        AdrSrc      : out std_logic;
        MemWrite    : out std_logic;
        IRWrite     : out std_logic;
        ResultSrc   : out std_logic_vector(1 downto 0);
        ALUControl  : out std_logic_vector(2 downto 0);
        ALUSrcB     : out std_logic_vector(1 downto 0);
        ALUSrcA     : out std_logic_vector(1 downto 0);
        ImmSrc      : out std_logic_vector(1 downto 0);
        RegWrite    : out std_logic
    );

END FSM;


ARCHITECTURE estrutural OF FSM IS

    -- Declaraçção dos estados s0 a s9
    type state_type is (s0, s1, s2, s3, s4, s5, s6, s7, s8, s9);

    -- Estado atual e próximo estado
    signal state, next_state : state_type; --  tem que ser do mesmo tipo que os estados definidos

BEGIN

    -- Lógica de controle do próximo estado (verifica reset e transição positiva de clock)
    PROCESS(clk, clr)
    BEGIN

        if clr = '1' then
            state <= s0;

        elsif clk'event and clk = '1' then
            state <= next_state;

        end if;

    END PROCESS;


    -- Lógica de controle do próximo estado
    PROCESS(state)
    BEGIN
        case state is
            when s0=>
                next_state <= s1;
            when s1=>
                if op = "00" then
                    next_state <= s6;
                
                elsif op = "01" then
                    next_state <= s8;
                
                elsif op = "10" then
                    next_state <= s2;
                
                elsif op = "11" then
                    next_state <= s9;

                end if;
            when s2=>
                if funct3(0) = '0' then
                    next_state <= s3;
                
                else
                    next_state <= s5;

                end if;
            when s3=>
                next_state <= s4;
            when s4=>
                next_state <= s0;
            when s5=>
                next_state <= s0;
            when s6=>
                next_state <= s7;
            when s7=>
                next_state <= s0;
            when s8=>
                next_state <= s7;
            when s9=>
                next_state <= s0;
        end case;

    END PROCESS;

    -- Lógica de controle das saídas
    PROCESS(state)
    BEGIN
        case state is
            when s0=>
                PCWrite     <= '1';
                AdrSrc      <= '0';
                MemWrite    <= '0';
                IRWrite     <= '1';
                ResultSrc   <= "10";
                ALUControl  <= "000";
                ALUSrcB     <= "10";
                ALUSrcA     <= "00";
                RegWrite    <= '0';
            when s1=>
                PCWrite     <= '0';
                MemWrite    <= '0';
                IRWrite     <= '0';
                RegWrite    <= '0';
            when s2=>
                PCWrite     <= '0';
                MemWrite    <= '0';
                IRWrite     <= '0';
                ALUControl  <= "000";
                ALUSrcB     <= "01";
                ALUSrcA     <= "01";
                ImmSrc      <= "01";
                RegWrite    <= '0';
            when s3=>
                PCWrite     <= '0';
                AdrSrc      <= '1';
                MemWrite    <= '0';
                IRWrite     <= '0';
                ResultSrc   <= "00";
                RegWrite    <= '0';
            when s4=>
                PCWrite     <= '0';
                MemWrite    <= '0';
                IRWrite     <= '0';
                ResultSrc   <= "01";
                RegWrite    <= '1';

            when s5=>
                PCWrite     <= '0';
                AdrSrc      <= '1';
                MemWrite    <= '1';
                IRWrite     <= '0';
                ResultSrc   <= "00";
                RegWrite    <= '0';
            when s6=>
                PCWrite     <= '0';
                MemWrite    <= '0';
                IRWrite     <= '0';
                ALUControl  <= funct3;
                ALUSrcB     <= "00";
                ALUSrcA     <= "10";
                RegWrite    <= '0';
            when s7=>
                PCWrite     <= '0';
                MemWrite    <= '0';
                IRWrite     <= '0';
                ResultSrc   <= "00";
                ALUControl  <= funct3;
                RegWrite    <= '1';
            when s8=>
                PCWrite     <= '0';
                MemWrite    <= '0';
                IRWrite     <= '0';
                ALUControl  <= funct3;
                ALUSrcB     <= "01";
                ALUSrcA     <= "10";
                ImmSrc      <= "00";
                RegWrite    <= '0';
            when s9=>
                PCWrite     <= not zero;
                MemWrite    <= '0';
                IRWrite     <= '0';
                ResultSrc   <= "10";
                ALUControl  <= "000";
                ALUSrcB     <= "01";
                ALUSrcA     <= "01";
                ImmSrc      <= "10";
                RegWrite    <= '0';
            end case;

    END PROCESS;


END estrutural;