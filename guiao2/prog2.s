    .data
    .text
    .globl main

main:
    addiu   $sp, $sp, -8
    sw      $ra, 0($sp)
    sw      $s0, 4($sp)

    li  	$s0, 0  #counter = 0

while:
	li		$a0, 1000
	jal		delay
    
    
    move    $a0, $s0    
    li      $a1, 0x0004000A
    li      $v0, 6
    syscall
    addi    $s0, $s0, 1  #counter++

    li      $a0, '\r'
    li      $v0, 3
    syscall             #putChar('\r')
    j       while
    
    li      $v0, 0
    
    lw      $ra, 0($sp)
    lw      $s0, 4($sp)
    addiu   $sp, $sp, 8
    jr      $ra


delay:
    mul     $a0, $a0, 20000
    li      $v0, 12
    syscall

read:
    li      $v0, 11
    syscall
    blt     $v0, $a0, read
    jr      $ra
