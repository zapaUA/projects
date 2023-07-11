        .equ SFR_BASE_HI, 0xBF88    # 16 MSbits of SFR area
        .equ TRISB, 0x6040
        .equ PORTB, 0x6050
        .equ LATB, 0x6060
        .equ TRISE, 0x6100          # TRISE address is 0xBF886100
        .equ PORTE, 0x6110          # PORTE address is 0xBF886110
        .equ LATE, 0x6120           # LATE address is 0xBF886120

        .data
        .text
        .globl main

main:
        lui     $t0,SFR_BASE_HI
        lw      $t1,TRISE($t0)
        andi    $t1,$t1,0xFFE1        #0xFF 1110 0001
        sw      $t1,TRISE($t0)

        lw      $t1,TRISB($t0)
        ori     $t1,$t1,0x000E         #0x000 1110
        sw      $t1,TRISB($t0)

        li      $t2,0        
while:
        lw      $t1,LATE($t0)
        andi    $t1,$t1,0xFFE1
        sll     $t3,$t2,1
        or      $t1,$t1,$t3
        sw      $t1,LATE($t0)
        

        li      $v0,12
        syscall
delay:  
        li      $v0,11
        syscall
        blt     $v0,2000000,delay
        addi    $t2,$t2,1           #cnt++
        blt     $t2,16,while
        
        li      $t2,0
        j       while
        li      $v0,0
        jr      $ra
