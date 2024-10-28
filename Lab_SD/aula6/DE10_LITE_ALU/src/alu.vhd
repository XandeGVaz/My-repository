--Copryght:		
--Date:		23/10/24
--Version:	1.3
--Owners:	Gabriel D. Maruschi
-- 			Vitor Alexandre Garcia Vaz

entity alu is
	port
	(
		A, B		: in  bit_vector(3 downto 0);	-- Signals A e B do MODO de entrada (in) e do TIPO bit_vector
		ALUControl	: in  bit_vector(2 downto 0);		-- Signal ALUControl do MODO de entrada (in) e do TIPO bit_vector

		-- Saida(s)
		Result		: out bit_vector(3 downto 0);	-- Signal Result do MODO de saida (out) e do TIPO bit_vector de tamanho 3
		Zero		: out bit 							-- Signal Zero de MODO de saída (out) e do tipo bit
						-- A ultima declaracao de porta nao tem ponto e virgula (;)
	);
end alu;


architecture estrutural of alu is	-- ARQUITETURA 'estrutural' associada aa ENTIDADE 'alu'
	
	signal fb 			: bit_vector(3 downto 0);	-- recebe b ou b negado (dependendo do ALUContrrol(0) )
	
	signal adderResult  	: bit_vector(3 downto 0);	-- recebe resultado do adder (pode ser uma subtração ou uma soma)
	signal andResult 		: bit_vector(3 downto 0);	-- recebe resultando da operação lógica and
	signal orResult  		: bit_vector(3 downto 0);	-- recebe resultado da operação lógica or
	signal sltResult		: bit_vector(3 downto 0);	-- recebe resultado da comparação slt
	signal tempResult		: bit_vector(3 downto 0);	-- buffer de resultado final da ULA
	
	-- Inicio da declaracao da ARQUITETURA
begin
	
	-- Operações aritméticas
	
	mux0: work.mux21 port map (I0 => B, I1 => (not B), S => ALUControl(0), z => fb);
	
	add:	work.adder port map(A => A, B => fB, Cin =>ALUControl(0), RESULT => adderResult); 
	
	-- Operação and
	andResult <= A and B;
	
	-- Operação orr
	orResult <= A or B;
	
	--	Operação slt
	sltResult <= "000" & adderResult(3);
	
	-- Mux 5 pra 1 para selecionamento da operração que definirá a saída
	with ALUControl select
	tempResult <= 	adderResult when "000", --soma
						adderResult when "001",	--subtraçao
						andResult when "010",	--adn
						orResult when "011",		--or
						sltResult when "101",	--A < B
						"0000" when others;
	
	-- Flag zero (iguaol a 1 para resultado nulo)
	Zero <= not ((tempResult(0) or tempResult(1)) or (tempResult(2) or tempResult(3)));
	
	Result <= tempResult;		-- Resultado final
	
end estrutural;