#include <detpic32.h>

int main(void){
    T3CONbits.TCKPS = 7;    //kpresc = 20MHz/(2Hz*65536) = 153 => 256
    PR3 = 39062;            //PRx = (20MHz/(256*2))-1 = 39061.5
    TMR3 = 0;
    T3CONbits.TON = 1;

    while(1){
        while(IFS0bits.T3IF == 0);
        IFS0bits.T3IF = 0;
        putChar('.');
    }
    return 0;
}