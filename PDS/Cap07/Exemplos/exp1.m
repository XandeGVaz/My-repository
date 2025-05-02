clear all
close all

%{
================= Cálculo de DTFT em de v=(-2,2) =======================
    Este programa visa calcular a DTFT de uma função gauassina,
considerando uma janela de frequência de -2 a 2.
    O sinal gaussiano é dado por g(t) = A * exp(-(t/Sigma)^2), onde A é a 
amplitude do sinal.
%}

% Número de pontos de amostragem
Npt_n = 2^10;
n = (-Npt_n/2:1:Npt_n/2-1);

% Janela temporal
to = -300;
tf = 300;
Ts = (tf - to)/Npt_n; %período
t = n * Ts;           %vetor de janela temporal

% Amostragem da função g(t)
A = 5;          %amplitude
Sigma = 10;    %sigma
g = t * 0;      %inicializa vetor g com o mesmo número de pontos que t
g = A * exp(-(t/Sigma).^2); %gaussiana discreta

% Plotagem da g(t)
figure(1)
plot(t,abs(g))
xlabel('v')
ylabel('g(t)')
title(sprintf('DTFT do sinal g(t) t = (-300 e 300)'));

% Janela de frequẽncia (v)
Npt_v = 2^11;               %número de pontos de v
k = (-Npt_v/2:1:Npt_v/2-1); %vetor auxiliar k
vo = -2;                        
vf = -vo;
v_step = (vf - vo)/Npt_v;   %passo de v
v = k * v_step;             %vetor de janela de frequência -> suficiente pois compreende mais q 3 períodos

% DTFT de G (G_DTFT)
G_DTFT = v * 0;
for u = 1 : length(v)
    G_DTFT(u) = sum(g.*exp(-1i*2*pi*v(u)*n));
end

% Plotagem da G_DTFT
figure(2)
plot(v,abs(G_DTFT))
xlabel('v')
ylabel('G_{DTFT}')
title(sprintf('DTFT do sinal g(t) (Ts = %.2f e fs= %.2f)', Ts, 1/Ts));