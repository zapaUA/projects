#include <detpic32.h>

int main(void){
    // Timer T3 config 1Hz
    // kpresc = 20MHz/(1Hz*65536) = 305 => excede 256
    T3CONbits.TCKPS = 7;    
    PR3 = 39062;            
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
        static int i = 0;
        if(i == 0){
            putChar('.');   
        }
        i = (i + 1) % 2;            // smp que i == 2, i = 0;
        IFS0bits.T3IF = 0;
}
