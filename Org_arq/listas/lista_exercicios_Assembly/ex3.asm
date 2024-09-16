
.text
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
    mv s2, a0                       # s2 recebe endereço da string

    li a7, 4                        # print da string
    ecall
    
    mv a0, s2
    mv a1, s1
    jal invString

    li a7, 10             
    ecall                           # fim de programa


invString:
    li a2, 0                         # int i = 0
    addi a3, a1, -1                  # max = número de caracteres na string s/ \0
    sub sp, sp, a3                   # aloca espaço na pilha para guardar caracteres invertidos
loopGuarda:
    bge a2, a3 , cont                # continua loop se i < max
    add t1, a0, a2
    sub a4, a3, a2
    addi a4, a4, -1
    add t2, sp, a4
    lb t3, 0(t1)
    sb t3, 0(t2)
    addi a2, a2, 1
    j loopGuarda
cont:
    li a2, 0
loopRecupera:
    beq a2, a3, fim_invString
    add t1, a0, a2
    add t2, sp, a2
    lb t3, 0(t2)
    sb t3, 0(t1)
    addi a2, a2, 1
    j loopRecupera
fim_invString:
    add sp, sp, a3
    li a7, 4
    ecall
    ret
    
    






