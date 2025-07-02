clear all
close all

% Exercício 6.19 livro Sistemas de Controle para Engenharia

letter = 'c';

% Verificação do diagrama de BODE
function BODE(letter)
    switch letter
        case 'a'
            num = [1 2];
            den = [1 10];
            sys = tf(num, den);
            bode(sys);
            grid on;
        case 'b'
            num = 1;
            den = conv([1 10], conv([1 2], [1 2]));
            sys = tf(num, den);
            bode(sys);
            grid on;
        case 'c'
            num = conv([1 10], [1 1]);
            den = conv([1 100], conv([1 2], conv([1 2], [1 2])));
            sys = tf(num, den);
            bode(sys);
            grid on;
    end
end

% Diagrama de Nyquist
function NYQUIST(letter)
    switch letter
        case 'a'
            num = [1 2];
            den = [1 10];
            sys = tf(num, den);
            nyquist(sys);
            grid on;
        case 'b'
            num = 1;
            den = conv([1 10], conv([1 2], [1 2]));
            sys = tf(num, den);
            nyquist(sys);
            grid on;
        case 'c'
            num = conv([1 10], [1 1]);
            den = conv([1 100], conv([1 2], conv([1 2], [1 2])));
            sys = tf(num, den);
            nyquist(sys);
            grid on;
    end
end

% Lugar das raízes
function RLOCUS(letter)
    switch letter
        case 'a'
            num = [1 2];
            den = [1 10];
            sys = tf(num, den);
            rlocus(sys);
            grid on;
        case 'b'
            num = 1;
            den = conv([1 10], conv([1 2], [1 2]));
            sys = tf(num, den);
            rlocus(sys);
            grid on;
        case 'c'
            num = conv([1 10], [1 1]);
            den = conv([1 100], conv([1 2], conv([1 2], [1 2])));
            sys = tf(num, den);
            rlocus(sys);
            grid on;
    end
end



figure(1)
RLOCUS(letter);

figure(2)
NYQUIST(letter);

figure(3)
BODE(letter);