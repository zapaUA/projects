#int main(void)
#{
#  char c;
#  do
#  {
#      c = getChar();
#      putChar( c );
#  } while( c != '\n' );
#  return 0;
#} 

        .data
        .text
        .globl main

main:   
while:  li      $v0,2       #getChar()
        syscall
        addi    $v0,$v0,1   #c+1
        move    $a0,$v0
        li      $v0,3       #putChar()
        syscall
        bne     $a0,'\n',while

endw:   li      $v0,0
        jr      $ra         #return 0
