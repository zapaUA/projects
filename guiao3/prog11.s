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

main:   lui     $t0,SFR_BASE_HI
        lw      $t1,TRISE($t0)
        andi    $t1,$t1,0xFFFE
        sw      $t1,TRISE($t0)

        lw      $t1,TRISB($t0)
        ori     $t1,$t1,0x0001
        sw      $t1,TRISB($t0)

while:  lw      $t1,PORTB($t0)
        andi    $t1,$t1,0x0001

        lw      $t2,LATE($t0)
        andi    $t2,$t2,0xFFFE
        nor      $t2,$t2,$t1
        sw      $t2,LATE($t0)
        j       while
        jr      $ra
