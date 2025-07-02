clear all
close all

% Obtenção do gráfico de nyquist para verificação do resultado
num = [1 10];
den = conv([1 0], conv([1 -1], [1 100]));
sys = tf(num, den);
nyquist(sys);
grid on;