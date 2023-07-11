       .data
str1:  .asciiz "\nIntroduza um inteiro (sinal e módulo): "
str2:  .asciiz "\nValor em base 10 (signed): "
str3:  .asciiz "\nValor em base 2: "
str4:  .asciiz "\nValor em base 16: "
str5:  .asciiz "\nValor em base 10 (unsigned): "
str6:  .asciiz "\nValor em base 10 (unsigned), formatado: "

       .text
       .globl  main

main:   la      $a0,str1
        li      $v0,8
        syscall             #printStr()
        li      $v0,5
        syscall             #readInt10()
        move    $t0,$v0      #value: $t0

###
        la      $a0,str2
        li      $v0,8
        syscall             #printStr()
        move    $a0,$t0
        li      $v0,7
        syscall             #printInt10()

###
        la      $a0,str3
        li      $v0,8
        syscall             #printStr()
        move    $a0,$t0
        li      $a1,2
        li      $v0,6
        syscall             #printInt()

###
        la      $a0,str4
        li      $v0,8
        syscall             #printStr()
        move    $a0,$t0
        li      $a1,16
        li      $v0,6
        syscall             #printInt()

###
        la      $a0,str5
        li      $v0,8
        syscall             #printStr()
        move    $a0,$t0
        li      $a1,10
        li      $v0,6
        syscall             #printInt()

###
        la      $a0,str6
        li      $v0,8
        syscall             #printStr()
        
        li      $t1,4
        sll     $t1,$t1,16
        ori     $t1,$t1,2
        move    $a0,$t0
        move    $a1,$t1
        li      $v0,6
        syscall             #printInt()

        li      $v0,0
        jr      $ra
