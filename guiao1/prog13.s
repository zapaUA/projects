        .data
        .text
        .globl main

main:   
while:  li      $v0,1       #inKey()
        syscall
        move    $a0,$v0

if:     beq     $a0,0,else
        li      $v0,3       #putChar()
        syscall
        j       endw

else:   li      $a0,'.'
        li      $v0,3       #putChar()
        syscall

endw:   bne     $a0,'\n',while

        li      $v0,0
        jr      $ra         #return 0
