%{
    Exercício visa comparar a DTFT de um sinal gaussinano calculada computacionalmente
    com a DTFT explícita do mesmo sinal.
    O sinal gaussiano é dado por g(t) = A * exp(-(t/Sigma)^2), onde A é a amplitude.
%}

% Janela temporal
Npt_n = 2^10;
n = (-Npt_n/2:1:Npt_n/2-1);
to = -300;
tf = -to;
Ts = (tf - to)/Npt_n;
t = n * Ts;

% Sinal g(t) de função gaussiana
A = 10;
Sigma = 10;
g = t * 0;
g = A * exp(-(t./Sigma).^2);

% Janela de frequência
Npt_k = 2^11;
k = (-Npt_k/2:1:Npt_k/2-1);
vo = -2;
vf = -vo;
v_step = (vo-vf)/Npt_k;
v = k * v_step;

% DTFT calculada computacionalmente de g(t)
G_DTFT_C = v * 0;
for u = 1:length(v)
    G_DTFT_C(u) = sum(g.*exp(-1i*2*pi*v(u)*n));
end

% DTFT explícita de g(t)
fs = 1/Ts;
G_DTFT_E = A*fs*Sigma*((pi)^(1/2))*exp(-(fs*pi*Sigma*v).^2);

figure(1)
plot(v, abs(G_DTFT_C), 'r', 'LineWidth', 1.5);
hold on;
plot(v, abs(G_DTFT_E), 'b--', 'LineWidth', 1.5);
hold off;
xlabel('v');
ylabel('G_{DTFT}(v)');
title(sprintf('DTFT de g(t) (fs = %.2f, Ts = %.2f)',fs,Ts));
legend('DTFT computacional', 'DTFT explícita');