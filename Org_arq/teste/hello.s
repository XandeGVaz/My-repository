# Risc-V Assembler program to print "Hello World!"
# to stdout.

# a0-a2 - parameters to Linux function services
# a7 - Linux function number

# Setup the parameters to print hello world
# and then call Linux to do it.
.text
_start: 
        addi  a0, x0, 1      # 1 = StdOut
        la    a1, helloworld # load address of helloworld
        addi  a2, x0, 13     # length of our string
        addi  a7, x0, 64     # Linux write system call
        ecall                # Call Linux to output the string

# Setup the parameters to exit the program
# and then call Linux to do it.
        addi    a0, x0, 0   # Use 0 return code
        addi    a7, x0, 93  # Service command code 93 terminates
        ecall               # Call Linux to terminate the program

.data
helloworld: .string "Hello World!\n"
