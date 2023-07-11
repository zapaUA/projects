#include <detpic32.h>

int main(void){
    // Timer T3 config 2Hz
    T3CONbits.TCKPS = 7;    //kpresc = 20MHz/(2Hz*65536) = 153 => 256
    PR3 = 39062;            //PRx = (20MHz/(256*2))-1 = 39061.5
    TMR3 = 0;
    T3CONbits.TON = 1;

    // Enable timer T2 interrupts
    IPC3bits.T3IP = 2;
    IEC0bits.T3IE = 1;
    IFS0bits.T3IF = 0;     
    EnableInterrupts();

    while(1);
    return 0;
}

    // VECTOR datasheet pg 74
void _int_(12) isr_T3(void){
        putChar('.');
        IFS0bits.T3IF = 0;
}