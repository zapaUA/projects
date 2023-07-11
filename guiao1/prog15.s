        .equ    UP,1
        .equ    DOWN,0
        .data
        .text
        .globl main

main:   addiu   $sp,$sp,-16
        sw      $ra,0($sp)
        sw      $s0,0($sp)
        sw      $s1,0($sp)
        sw      $s2,0($sp)

        li      $s0,1       # $s0: state
        li      $s1,0       # $s1: cnt
        
while:  li      $a0,'\r'
        li      $v0,3       # putChar()
        syscall
        li      $a1,0x0003000A
        move    $a0,$s1
        li      $v0,6       # printInt()
        syscall

        li      $a0,'\t'
        li      $v0,3       # putChar()
        syscall
        li      $a1,0x00080002
        move    $a0,$s1
        li      $v0,6       # printInt()
        syscall
        
        li      $a0,5
        jal     wait

        li      $v0,1
        syscall
        move    $s2,$v0     # $s2: c
if1:    bne     $s2,'+',if2
        li      $s0,UP
        j       endif
if2:    bne     $s2,'-',endif
        li      $s0,DOWN

endif:
if3:    bne     $s0,UP,if4
        addi    $s1,$s1,1
        andi    $s1,$s1,0xFF
        j       endw
if4:    addi    $s1,$s1,-1
        andi    $s1,$s1,0xFF

endw:   bne     $s2,'q',while
        
        lw      $ra,0($sp)
        lw      $s0,0($sp)
        lw      $s1,0($sp)
        lw      $s3,0($sp)
        addiu   $sp,$sp,16
        li      $v0,0
        jr      $ra


wait:   li      $t0,0
        li      $t1,515000
        mul     $t1,$t1,$a0
for:    bge     $t0,$t1,endfor
        addi    $t0,$t0,1
        j       for
endfor: jr      $ra
