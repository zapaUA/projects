        .data
msg:    .asciiz "AC2 - Aulas praticas\n"
        .text

        .globl main
main:   la  $a0,msg
        li  $v0,8       #printStr()
        syscall
        li  $v0,0
        jr  $ra         #return 0
