### Trabaho final de sinais e sistemas

## Alunos:
# Pedro Gasparelo Leme - 14602421
# Vitor Alexandre Garcia Vaz - 14611432


# Imports
import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import interp1d
import math


# Integral de uma função
def intg_s(a,b,N,f):
    h=(b-a)/N ##calcula tamanho das partições
    som=0 ##somatório da fórmula

    x=np.zeros(N+1)
    x[0]=a

    for k in range(1,N+1):
        x[k]=a+h*k ## valores de x a cada partição h
    
    for k in range (1,N+1):##cálculo do somatório
        xb=(x[k-1]+x[k])/2
        som=som+f(x[k-1])+4*f(xb)+f(x[k]) 

    return ((h/6)*som)

# Convolução de duas funções (f e g)
def conv(a,b,N,f,g,x):
    
    ## Calcula tamanho das partições
    h=(b-a)/N 
    
    ## Somatório da fórmula
    som=0 

    t=np.zeros(N+1)
    t[0]=a

    ## Valores de t a cada partição h
    for k in range(1,N+1):
        t[k]=a+h*k 
    
    ## Cálculo do somatório
    for k in range (1,N+1):
        tb=(t[k-1]+t[k])/2
        som += f(t[k-1])*g(x-t[k-1]) + 4*f(tb)*g(x-tb)+ f(t[k])*g(x-t[k]) 

    ## Retorno do resultado da convolução no ponto x
    return ((h/6)*som)


## Primeiro exemplo de convolução
# Definindo as funções f e g
def f1(t):
    if(abs(t) <= 5):
        return 1
    return 0

def g1(t):
    if(abs(t) <= 5):
        return 1
    return 0

# Parâmetros
a = -20         # limite inferior 
b = 20          # limite superior
N = 1000        # número de partições

# Definindo os valores de x
x_values = np.linspace(a, b, N)

# Calculando a convolução para cada valor de x
i = 0
conv_values = np.zeros(N)
for x in x_values:
    conv_values[i] = conv(a,b,N,f1,g1,x)
    i += 1

# Plotando os resultados
plt.figure(figsize=(10, 6))
plt.plot(x_values, [f1(x) for x in x_values], label='f(x) = $G_{10}(x)$', color='blue')
plt.plot(x_values, [g1(x) for x in x_values], label='g(x) = $G_{10}(x)$', color='orange')
plt.plot(x_values, conv_values, label='Convolução de f e g', color='#fa19ef')
plt.xlabel('x')
plt.ylabel('y(x)')
plt.title('$y(x) = f(x) * g(x)$')
plt.legend()
plt.grid(True)

# Salvamento do gráfico
plt.savefig('graficos_plotados/convolucao1.png')



## Segundo exemplo de convolução
# Definindo as funções f e g
def f2(t):
    if( t >= 0 and t <= 5 ):
        return 5 - t
    return 0

def g2(t):
    if(abs(t) <= 2.5):
        return 1
    return 0

# Parâmetros
a = -20         # limite inferior 
b = 20          # limite superior
N = 1000        # número de partições

# Definindo os valores de x
x_values = np.linspace(a, b, N)

# Calculando a convolução para cada valor de x
i = 0
conv_values = np.zeros(N)
for x in x_values:
    conv_values[i] = conv(a,b,N,f2,g2,x)
    i += 1

# Plotando os resultados
plt.figure(figsize=(10, 6))
plt.plot(x_values, [f2(x) for x in x_values], label='f(x) = $rampa(x)$', color='blue')
plt.plot(x_values, [g2(x) for x in x_values], label='g(x) = $G_5(x)$', color = 'orange')
plt.plot(x_values, conv_values, label='Convolução de f e g', color='#fa19ef')
plt.xlabel('x')
plt.ylabel('y(x)')
plt.title('$y(x) = f(x) * g(x)$')
plt.legend()
plt.grid(True)

# Salvamento do gráfico
plt.savefig('graficos_plotados/convolucao2.png')


## Terceiro exemplo de convolução
# Definindo as funções f e g
def f3(t):
    if(t <= 0):
        return math.exp(0.2*t) 
    return 0

def g3(t):
    if(t >= 0):
        return math.exp(-0.2*t) 
    return 0

# Parâmetros
a = -50         # limite inferior 
b = 50          # limite superior
N = 2000        # número de partições

# Definindo os valores de x
x_values = np.linspace(a, b, N)

# Calculando a convolução para cada valor de x
i = 0
conv_values = np.zeros(N)
for x in x_values:
    conv_values[i] = conv(a,b,N,f3,g3,x)
    i += 1

# Plotando os resultados
plt.figure(figsize=(10, 6))
plt.plot(x_values, [f3(x) for x in x_values], label='$f(x)=e^{0,2x}u(-x)$', color='blue')
plt.plot(x_values, [g3(x) for x in x_values], label='$f(x)=e^{-0,2x}u(x)$', color = 'orange')
plt.plot(x_values, conv_values, label='Convolução de f e g', color='#fa19ef')
plt.xlabel('x')
plt.ylabel('y(x)')
plt.title('$y(x) = f(x) * g(x)$')
plt.legend()
plt.grid(True)

# Salvamento do gráfico
plt.savefig('graficos_plotados/convolucao3.png')

# Exibição do gráfico
plt.show()