.data
.align 2
vetor: .word  7,2,0,9,3,6,1,8,5,4
tam: .word  10

.text
.align 2
.globl main

main:
    la a0, vetor                                # a0 recebe endereço de primeiro valor do vetor
    jal imprime_vetor                           # impressão de vetor desordenado
    la a0, vetor                                # a0 recebe endereço de primeiro valor do vetor
    jal bubble_sort                             # pula para rotina de ordenação
    la a0, vetor                                # a0 recebe endereço de primeiro valor do vetor
    jal imprime_vetor                           # impressão de vetor ordenado crescentemente
    #Fim de programa
    li a7, 10
    ecall

#Rotinha de impressão de vetor de inteiros  
#    Parâmetros:
#        a0: endereço do primeiro valor do vetor (&vetor[0])
#
imprime_vetor:
    mv a3, a0                                   # o registrador a3 recebe endereço do vetor
    la t1, tam                                  # t1 = tam 
    lw a1, 0(t1)                                # a1 recebe tamanho do vetor 
    li a2, 0                                    # int i = 0
loop_imprime:
    bge a2, a1, sai_loop_imprime                # se a2 >= tamanho a impressão acabou
    lw a0, 0(a3)                                # a0 recebe valor que será impresso
    li a7, 1                                    # chamada de impressão de valor inteiro
    ecall
    addi a2, a2, 1                              # incrementa-se o índice i
    addi a3, a3, 4                              # a3 recebe endereço inicial do próximo elemento a ser impresso
    j loop_imprime                              # continua o loop
sai_loop_imprime:
    ret

#Rotina de troca de dois valores
#    Parâmetros: 
#        a4 ea a5: endereços a terem seus valores trocados
#
troca:
    lw t1, 0(a4)
    lw t2, 0(a5)
    sw t1, 0(a5)
    sw t2, 0(a4)
    ret                                      

#Rotina de ordenação pelo método bubble_sort
#    Parâmetros:
#        a0: endereço do primeiro valor do vetor (&vetor[0])
#
bubble_sort:
    la t1, tam                                  # t1 = tam 
    lw a1, 0(t1)                                # a1 recebe tamanho do vetor 
    li a2, 0                                    # int i = 0
loopi:
    bge a2, a1, sai_loopi                       # permanece no loopi enquanto i<tam
    addi t1, a1, -1                             # t1 = tam - 1
    mv a3, t1                                   # int j = tam - 1
loopj:
    blt a3, a2, sai_loopj                       # permanece no loopj enquanto j>=i
    li t1, 4                                    # t1 recebe a quantidade de bytes de uma word (inteiro)
    mul t2, a3, t1                              # t2 recebe o deslocamento em bytes de &vetor[j] em relação a &vetor[0]
    add a4, a0, t2                              # a4 = &vetor[j]
    addi a5, a4, -4                             # a5 = &vetor[j-1] (endereço de 4 bytes atrás)
    lw t1, 0(a4)                                # t1 recebe valor de vetor vetor[j]
    lw t2, 0(a5)                                # t2 recebe valor de vetor vetor[j-1]
    ble t2, t1, cont_loopj                      # se vetor[j-1] > vetor[j] troca valores
valido:
    addi sp, sp, -4                             # aloca espaço na pilha
    sw ra, 0(sp)                                # guarda endereço de retorno à main
    jal troca                                   # chama função de trocar valores de dois endereços
    lw ra, 0(sp)                                # recupera endereço de retorno à main
    addi sp, sp, 4                              # desaloca espaço na pilha
cont_loopj:
    addi a3, a3, -1                             # decrementa j              
    j loopj                                     # continua loopj
sai_loopj:
    addi a2, a2, 1                              # incrementa i
    j loopi                                     # volta para loopi
sai_loopi:
    ret                                         # pula para a instrução subsequente a chamada da rotina bubble_sort

