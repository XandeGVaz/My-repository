%{
    Exercício visa comparar a DTFTs (computacional, obtida por propriedade, aproximação 
    e por comparação com FT) do sinal retangular para diferentes valores de no.
    OBS: 2no é o comprimento do sinal retangular.
%}

% Valor de no
no = [0.5, 1, 5, 20, 100];

% Janela Temporal
Npt_n = 2^10;
n = (-Npt_n/2:1:Npt_n/2-1);
tf = 512;
to = -tf;
Ts = (tf - to)/Npt_n;
t = n * Ts;

% Função rect(t)=1 p/ -no<n<no
g = zeros(length(no), length(t));
for u = 1:length(no)
    for j = 1:length(t)
        if abs(t(j)) <= abs(no(u))
            g(u,j) = 1;
        end
    end 
end

% Janela de frequência
Npt_v = 2^11;
k = (-Npt_v/2:1:Npt_v/2+1);
vf = 0.5;
vo = -vf;
v_step = (vf-vo)/Npt_v;
v = k * v_step;

% DTFT computacional  de rect(t)=1 p/ -no<n<no para diferentes no
G_DTFT_CO = zeros(length(no), length(v));
G_DTFT_PR = zeros(length(no), length(v));
G_DTFT_AP = zeros(length(no), length(v));
G_DTFT_CF = zeros(length(no), length(v));
for u = 1 : length(no)
    for j = 1 : length(v)
        G_DTFT_CO(u,j) = sum(g(u, :).*exp(-1i*2*pi*v(j)*n));
        G_DTFT_PR(u,j) = sin(pi*v(j)*(2*no(u)+1))/sin(pi*v(j));
        G_DTFT_AP(u,j) = 2*no(u)*sin(2*pi*v(j)*no(u))/(2*pi*v(j)*no(u));
        G_DTFT_CF(u,j) = (2*no(u)+1)*sin(pi*v(j)*(2*no(u)+1))/(pi*v(j)*(2*no(u)+1));
    end
end

% Plotagem para no=0.5
figure(1)
plot(v, abs(G_DTFT_CO(1,:)), 'r', 'LineWidth', 2.0);
hold on
plot(v, abs(G_DTFT_PR(1,:)), 'b', 'LineWidth', 1.5);
plot(v, abs(G_DTFT_AP(1,:)), 'g', 'LineWidth', 1.5);
plot(v, abs(G_DTFT_CF(1,:)), 'm', 'LineWidth', 1.5);
hold off
grid on
title('DTFT Computacional, Propriedade, Aproximação e Comparação com FT para no=0.5');
xlabel('v');
ylabel('G_{DTFT}(v)');
legend('DTFT Computacional', 'DTFT Propriedade', 'DTFT Aproximação', 'DTFT Comparação com FT');

% Plotagem para no=1
figure(2)
plot(v, abs(G_DTFT_CO(2,:)), 'r', 'LineWidth', 2.0);
hold on
plot(v, abs(G_DTFT_PR(2,:)), 'b', 'LineWidth', 1.5);
plot(v, abs(G_DTFT_AP(2,:)), 'g', 'LineWidth', 1.5);
plot(v, abs(G_DTFT_CF(2,:)), 'm', 'LineWidth', 1.5);
hold off
grid on
title('DTFT Computacional, Propriedade, Aproximação e Comparação com FT para no=1');
xlabel('v');
ylabel('G_{DTFT}(v)');
legend('DTFT Computacional', 'DTFT Propriedade', 'DTFT Aproximação', 'DTFT Comparação com FT');

% Plotagem para no=5
figure(3)
plot(v, abs(G_DTFT_CO(3,:)), 'r', 'LineWidth', 2.0);
hold on
plot(v, abs(G_DTFT_PR(3,:)), 'b', 'LineWidth', 1.5);
plot(v, abs(G_DTFT_AP(3,:)), 'g', 'LineWidth', 1.5);
plot(v, abs(G_DTFT_CF(3,:)), 'm', 'LineWidth', 1.5);
hold off
grid on
title('DTFT Computacional, Propriedade, Aproximação e Comparação com FT para no=5');
xlabel('v');
ylabel('G_{DTFT}(v)');
legend('DTFT Computacional', 'DTFT Propriedade', 'DTFT Aproximação', 'DTFT Comparação com FT');

% Plotagem para no=20
figure(4)
plot(v, abs(G_DTFT_CO(4,:)), 'r', 'LineWidth', 2.0);
hold on
plot(v, abs(G_DTFT_PR(4,:)), 'b', 'LineWidth', 1.5);
plot(v, abs(G_DTFT_AP(4,:)), 'g', 'LineWidth', 1.5);
plot(v, abs(G_DTFT_CF(4,:)), 'm', 'LineWidth', 1.5);
hold off
grid on
title('DTFT Computacional, Propriedade, Aproximação e Comparação com FT para no=20');
xlabel('v');
ylabel('G_{DTFT}(v)');
legend('DTFT Computacional', 'DTFT Propriedade', 'DTFT Aproximação', 'DTFT Comparação com FT');

% Plotagem para no=100
figure(5)
plot(v, abs(G_DTFT_CO(5,:)), 'r', 'LineWidth', 2.0);
hold on
plot(v, abs(G_DTFT_PR(5,:)), 'b', 'LineWidth', 1.5);
plot(v, abs(G_DTFT_AP(5,:)), 'g', 'LineWidth', 1.5);
plot(v, abs(G_DTFT_CF(5,:)), 'm', 'LineWidth', 1.5);
hold off
grid on
title('DTFT Computacional, Propriedade, Aproximação e Comparação com FT para no=100');
xlabel('v');
ylabel('G_{DTFT}(v)');
legend('DTFT Computacional', 'DTFT Propriedade', 'DTFT Aproximação', 'DTFT Comparação com FT');


