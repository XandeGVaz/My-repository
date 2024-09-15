.data
.align 2
vetor: .word  7,2,0,9,3,6,1,8,5,4
tam: .word  10

.text
.align 2
.globl main

main:
    la a0, vetor                    # endereço do vetor é passado por parâmetro em a0
    jal somatorio                   # chamada da rotina de somatorio
    li a7, 1                        # impressão do somatório de valores armazenado em a0
    ecall
    li a7, 10                       # fim do programa
    ecall

#Função de somatório de elementos em um vetor de inteiros
#   Parâmetros:
#       a0: endereço do vetor (&vetor[0])
#   Retorna:
#       a0: valor do somatorio dos elementos do vetor de inteiros
somatorio:
    li a1, 0                        # int i=0
    li a2, 0                        # int som=0
    la t1, tam                      # t1 recebe endereço do tamanho do vetor
    lw a3, 0(t1)                    # a3 recebe tamanho do vetor
loopSom:
    bge a1, a3, sai_lopSOM          # permanece no loop se i < tamnho do vetor
    li t1, 4                        # número de bytes do word (inteiro)
    mul t2, a1, t1                  # deslocamento em bytes do valor a ser somado em relação ao início do vetor
    add t2, t2, a0                  # t2 = &vetor[i]
    lw t3, 0(t2)                    # t3 = vetor[i]
    add a2, a2, t3                  # som = som + vetor[i]
    addi a1, a1 , 1                 # incremento do índice i
    j loopSom                       # continua o loop
sai_lopSOM:
    mv a0, a2                       # soma total é retornada em a0
    ret                             # retorna a instrução subsequente à chamada feita na main
