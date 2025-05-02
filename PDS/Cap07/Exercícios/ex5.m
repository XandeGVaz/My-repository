%{
    Exercício visa comparar a DTFTs de um sinal gaussinano calculadas computacionalmente
    para diferentes valores de TS.
    O sinal gaussiano é dado por g(t) = A * exp(-(t/Sigma)^2), onde A é a amplitude.
%}

% Janelas temporais
Npt_n1 = 2^10;
Npt_n2 = 2^8;
Npt_n3 = 2^6;
n1 = (-Npt_n1/2:1:Npt_n1/2-1);
n2 = (-Npt_n2/2:1:Npt_n2/2-1);
n3 = (-Npt_n3/2:1:Npt_n3/2-1);
to = -300;
tf = -to;
Ts1 = (tf - to)/Npt_n1;
Ts2 = (tf - to)/Npt_n2;
Ts3 = (tf - to)/Npt_n3;
t1 = n1 * Ts1;
t2 = n2 * Ts2;
t3 = n3 * Ts3;

% Sinal g(t) de função gaussiana (avaliados em diferentes janelas temporais)
A = 5;
Sigma = 10;
g1 = t1 * 0;
g1 = A * exp(-(t1./Sigma).^2);
g2 = t2 * 0;
g2 = A * exp(-(t2./Sigma).^2);
g3 = t3 * 0;
g3 = A * exp(-(t3./Sigma).^2);

% Janela de frequência
Npt_k = 2^11;
k = (-Npt_k/2:1:Npt_k/2-1);
vo = -2;
vf = -vo;
v_step = (vo-vf)/Npt_k;
v = k * v_step;

% DTFTs calculadas computacionalmente de g(t)
G_DTFT1 = v * 0;
G_DTFT2 = v * 0;
G_DTFT3 = v * 0;
for u = 1:length(v)
    G_DTFT1(u) = sum(g1.*exp(-1i*2*pi*v(u)*n1));
    G_DTFT2(u) = sum(g2.*exp(-1i*2*pi*v(u)*n2));
    G_DTFT3(u) = sum(g3.*exp(-1i*2*pi*v(u)*n3));
end

% Plotagem
figure(1)
plot(v, abs(G_DTFT1), 'r', 'LineWidth', 1.5);
hold on;
plot(v, abs(G_DTFT2), 'b--', 'LineWidth', 1.5);
plot(v, abs(G_DTFT3), 'g:', 'LineWidth', 1.5);
hold off;
xlabel('v');
ylabel('G_{DTFT}(v)');
title(sprintf('DTFT de g(t)'));
legend(sprintf('Ts1 = %.2f e fs1 = %.2f',Ts1,1/Ts1), sprintf('Ts2 = %.2f e fs2 = %.2f',Ts2,1/Ts2), sprintf('Ts3 = %.2f e fs3 = %.2f',Ts3,1/Ts3));