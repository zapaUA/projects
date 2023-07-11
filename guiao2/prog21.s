        .data
        .text
        .globl main

main:   li      $t0,0       # $t0: counter
while1: li      $v0,12      #resetCoreTimer()
        syscall
        
while:  li      $v0,11
        syscall             #readCoreTimer()
        blt     $v0,200000,while
        addi    $t0,$t0,1
        move    $a0,$t0
        li      $a1,0x0004000A
        li      $v0,6
        syscall             #printInt()
        
        li      $a0,'\r'
        li      $v0,3
        syscall             #putChar()
        j       while1


endw:   li      $v0,0
        jr      $ra
