
.text
.align 2
.globl main

main:
    li a7, 5                        # lê número de caracteres da strig
    ecall
    
    addi a0, a0, 1                  # adiciona-se 1 ao tamanho da string para adição de indicador nulo
    mv s1, a0                       # s1 recebe o número de caracteres da string que será lida
    li a7, 9                        # aloca espaço na memória para string
    ecall

    li a7, 8                        # lê string que é colocada no espaço já alocado
    mv a1, s1                       # o tamanho da string deve contar o NULL
    ecall

    li a7, 4                        # print da string
    ecall

    li a7, 10             
    ecall                           # fim de programa       


