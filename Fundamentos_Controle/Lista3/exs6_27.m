
clear all
close all

% -------------------------------------------------------------------
%   SELECIONE AQUI A LETRA DO EXERCÍCIO (de 'a' a 'g')
% -------------------------------------------------------------------
letter = 'a';
% -------------------------------------------------------------------

% Definição do ganho K, conforme solicitado no exercício.
K = 1;

% Geração e exibição das figuras para cada análise.
% Figura 1: Lugar das Raízes
figure(1)
RLOCUS(letter, K);
title(['Lugar das Raízes - Sistema (' upper(letter) ')']);

% Figura 2: Diagrama de Nyquist
figure(2)
NYQUIST(letter, K);
title(['Diagrama de Nyquist - Sistema (' upper(letter) ')']);

% Figura 3: Diagrama de Bode
figure(3)
BODE(letter, K);
title(['Diagrama de Bode - Sistema (' upper(letter) ')']);


% Função para gerar o Diagrama de Bode
function BODE(letter, K)
    [num, den] = getSystemDynamics(letter, K);
    sys = tf(num, den);
    bode(sys);
    grid on;
end

% Função para gerar o Diagrama de Nyquist
function NYQUIST(letter, K)
    [num, den] = getSystemDynamics(letter, K);
    sys = tf(num, den);
    nyquist(sys);
    grid on;
    % Melhora a visualização do gráfico de Nyquist
    axis equal;
end

% Função para gerar o Lugar das Raízes
function RLOCUS(letter, K)
    % Para o Lugar das Raízes, o ganho K é a variável do gráfico, então definimos a planta com K=1.
    [num, den] = getSystemDynamics(letter, 1);
    sys = tf(num, den);
    rlocus(sys);
    grid on;
end


% Retorna o numerador e o denominador da função de transferência com base na letra selecionada.
function [num, den] = getSystemDynamics(letter, K)
    switch letter
        case 'a'
            % KG(s) = K / (s+1)^3
            num = K;
            den = conv([1 1], conv([1 1], [1 1]));
        case 'b'
            % KG(s) = K / (s*(s+1)^2)
            num = K;
            den_temp = conv([1 1], [1 1]); 
            den = conv([1 0], den_temp);   
        case 'c'
            % KG(s) = K / ((s-1)*(s+1)^2)
            num = K;
            den_temp = conv([1 1], [1 1]); 
            den = conv([1 -1], den_temp);  
        case 'd'
            % KG(s) = K / ((s-1)*(s+2))
            num = K;
            den = conv([1 -1], [1 2]);
        case 'e'
            % KG(s) = K * 2(s+1)(s^2-4s+1) / (s-1)^3
            num = K * 2 * conv([1 1], [1 -4 1]);
            den = conv([1 -1], conv([1 -1], [1 -1]));
        case 'f'
            % KG(s) = K * (s+1)(s^2+3) / (4*(s-1)^3)
            num = (K/4) * conv([1 1], [1 0 3]);
            den = conv([1 -1], conv([1 -1], [1 -1]));
        case 'g'
            % KG(s) = K * (s^2+1) / (s-1)^3
            num = K * [1 0 1];
            den = conv([1 -1], conv([1 -1], [1 -1]));
        otherwise
            error("Letra inválida. Por favor, escolha uma letra entre 'a' e 'g'.");
    end
end