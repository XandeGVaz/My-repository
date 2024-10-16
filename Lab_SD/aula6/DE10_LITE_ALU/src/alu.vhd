-- Declaracao da ENTIDADE (entity)
-- 	Ela estabelece a interface do sistema digital com o mundo, ou seja, os pinos (sinais) de entrada e saida.
-- 	O nome da ENTIDADE deve ter tamanho maximo de 32 caracteres, sem pontuacao ou caracteres especiais.
-- 	Deve comecar por letra e pode incluir algarismos numericos e 'underline' (_).
-- 	O VHDL nao distingue entre maiuscula e minuscula ('case insensitive')
-- 
entity alu is
	port
	(
		-- Portas
		-- A sintaxe eh: NOME_DA_PORTA : MODO (in, out, inout) TIPO (bit, boolean, character, integer, real, time, bit_vector, string);
		-- Entrada(s)
		A, B		: in  bit_vector(3 downto 0);	-- Signals A e B do MODO de entrada (in) e do TIPO bit_vector
		ALUControl	: in  bit_vector(2 downto 0);		-- Signal ALUControl do MODO de entrada (in) e do TIPO bit_vector

		-- Saida(s)
		Result		: out bit_vector(3 downto 0);	-- Signal Result do MODO de saida (out) e do TIPO bit_vector de tamanho 3
		Zero		: out bit 							-- Signal Zero de MODO de saída (out) e do tipo bit
						-- A ultima declaracao de porta nao tem ponto e virgula (;)
	);
end alu;

-- Declaracao da ARQUITETURA (architecture)
-- 	Ela estabelece a relacao entre os pinos de entrada e de saida, ou seja, o circuito a ser implementado.
-- 	O nome da ARQUITETURA deve ter tamanho maximo de 32 caracteres, sem pontuacao ou caracteres especiais.
-- 	Deve comecar por letra e pode incluir algarismos numericos e 'underline' (_).
-- 	Cada ENTIDADE pode ter mais de uma ARQUITETURA, assim e necessario distingui-las por meio de um nome.

architecture estrutural of alu is	-- ARQUITETURA 'estrutural' associada aa ENTIDADE 'alu'
	
	signal fb 			: bit_vector(3 downto 0);	-- recebe b ou b negado (dependendo do ALUContrrol(0) )
	
	signal adderResult  	: bit_vector(3 downto 0);	-- recebe resultado do adder (pode ser uma subtração ou uma soma)
	signal andResult 		: bit_vector(3 downto 0);	-- recebe resultando da operação lógica and
	signal orResult  		: bit_vector(3 downto 0);	-- recebe resultado da operação lógica or
	signal sltResult		: bit_vector(3 downto 0);	-- recebe resultado da comparação slt
	signal tempResult		: bit_vector(3 downto 0);	-- buffer de resultado final da ULA
	
	-- Inicio da declaracao da ARQUITETURA
begin

	-- Para a implementacao da arquitetura da ALU, recomenda-se o uso da construção concorrente "Selected Signal Assignment":
	--<optional_label>: with <expression> select
	--<target> <= <value> when <choices>
	--			  <value> when <choices>
	--			  <value> when <choices>
	-- 		      ...
	--			  <value> when others;
	--tendo como <target> Result (ou Result_tmp), e como <expression> ALUControl
	
	-- Dicas:
	-- Como o resultado da operacao SLT e a saida ZERO depende de Result, recomenda-se criar um sinal intermediario (Result_tmp)
	--que armazena o valor das operacoes aritmetica e lógicas, ou zero para as operacoes nao definidas. Lembre-se de que para a
	--operacao SLT eh necessario calcular A-B para verificar se A eh menor do que B.
	-- Depois, utiliza-se Result_tmp para definir o valor final de Result e de Zero.
	-- O valor de ZeroExt pode ser obtido por "000" & Sum(3)
	
	-- Operações aritméticas
	
	mux0: work.mux21 port map (I0 => B, I1 => (not B), S => ALUControl(0), z => fb);
	
	add:	work.adder port map(A => A, B => fB, Cin =>'0', RESULT => adderResult); 
	
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
	Zero <= ((tempResult(0) nand tempResult(1)) nand (tempResult(2) nand tempResult(3)));
	
	Result <= tempResult;		-- Resultado final
	
end estrutural;