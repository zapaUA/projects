    .data
    .text
    .globl main

main:
    li  $t0, 0  #counter = 0

while:
    li  $v0, 12
    syscall

read:
    li      $v0, 11
    syscall
    blt     $v0, 200000, read

    move    $a0, $t0
    li      $a1, 0x0004000A
    li      $v0, 6
    syscall
    addi    $t0, $t0, 1  #counter++

    li      $a0, '\r'
    li      $v0, 3
    syscall             #putChar('\r')
    j       while
    
    li      $v0, 0
    jr      $ra
