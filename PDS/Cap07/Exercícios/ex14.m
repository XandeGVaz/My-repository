%{
    Exercício visa calcular uma integral computacionalmente
%}

n = (0:0.1:200);

% Função que será integrada
W1 = @(x,no) sin(pi*x*(1+2*no))/sin(pi*x);

% Função de integração
function resultado = calcIntegral1(f, a, b, no)

    resultado = 0;

    % Janela de frequência
    Npt_v = 2^12;
    k = (-Npt_v/2:1:Npt_v/2);
    vf = b;
    vo = a;
    v_step = (vf-vo)/Npt_v;
    v = k * v_step;
    
    %Cálculo
    for u = 2:length(v)
        resultado = resultado + f((v(u)+v(u-1))/2,no).*v_step;
    end
end

% Plotagem
figure(1)
plot(n, calcIntegral1(W,-0.5,0.5,n), 'b', 'LineWidth', 1.5);
xlabel('no');
ylabel('Integral');
title('Valores da integral de W(v) ( DFT de rect(t) ) para diferentes valores de no');
grid("on");