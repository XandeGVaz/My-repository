clear all
close all

%{
================= Cálculo da DTFT em de v=(-1/2,1/2) e da FT =========================
    Este programa visa:
    1) Calcular a DTFT do sinal de uma função gauassina,considerando uma janela de 
    frequência de -1/2 a 1/2, ou seja, na janela temporal de (no máximo) um período de 
    amostragem.
    2) Calcular a FT do sinal de uma função gaussiana, tendo como base a DTFT calculada
    desse mesmo sinal.
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

% Janela de frequẽncia (v)
Npt_v = 2^11;               %número de pontos de v
k = (-Npt_v/2:1:Npt_v/2-1); %vetor auxiliar k
vo = -1/2;                        
vf = -vo;
v_step = (vf - vo)/Npt_v;   %passo de v
v = k * v_step;             %vetor de janela de frequência -> suficiente pois compreende mais q 3 períodos

% DTFT de G (G_DTFT)
G_DTFT = v * 0;
for u = 1 : length(v)
    G_DTFT(u) = sum(g.*exp(-1i*2*pi*v(u)*n));
end

% Plotagem da G_DTFT
figure(1)
plot(v,abs(G_DTFT))
xlabel('v')
ylabel('G_{DTFT}(v)')
title(sprintf('DTFT do sinal g(t) (Ts = %.2f e fs= %.2f)', Ts, 1/Ts));

%{
Janela de frequência f[Hz]:
    Sendo de G_DTFT ser apenas uma versão em outra escala(1/fs) de G_D e, consequentemente, uma versão
em outra escala(1/fs) e outra amplitude (A*fs) de G_FT. Para obtermos G_FT é necessário apenas:
1) Dividir a amplitude de G_DTFT
2) Considerar uma janela de frequência em outra escala (v*fs)  
%}

%1) Ft de G
fs = 1/Ts;
G_FT = G_DTFT/fs;

%2) Escala do domínio
f = v*fs;

% Plotagem de G_FT
figure(2)
plot(f,abs(G_FT))
xlabel('f[Hz]')
ylabel('G_{FT}(f)')
title(sprintf('FT do sinal g(t) (Ts = %.2f e fs = %.2f)', Ts, fs));