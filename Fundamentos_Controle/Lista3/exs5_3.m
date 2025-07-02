clear all
close all

% Função para gerar o Lugar das Raízes
function RLOCUS(num, den)
    sys = tf(num, den);
    rlocus(sys);
    grid on;
end

figure(1)
RLOCUS([1 2 12], conv([1 0], [1 2 10]));