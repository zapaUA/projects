#include <detpic32.h>

int main(void){
    // Timer T3 config 50Hz
    // kpresc = 20MHz/(50Hz*65536) = 6 => 8
    T3CONbits.TCKPS = 3;    //tipo B: 1 = 000; 2 = 001; 4 = 010 ... 256 = 111 
    PR3 = 49999;            
    TMR3 = 0;
    T3CONbits.TON = 1;

    // Timer T1(tipo A) config 5Hz
    // kpresc = 20MHz/(5Hz*65536) = 61 => 64
    T1CONbits.TCKPS = 2;    //tipo A: 1 = 00; 8 = 01; 64 = 10; 256 = 11 
    PR1 = 62499;            
    TMR1 = 0;
    T1CONbits.TON = 1;


    // Enable timer T3 & T1 interrupts
    IPC3bits.T3IP = 2;
    IEC0bits.T3IE = 1;
    IFS0bits.T3IF = 0;
    
    IPC1bits.T1IP = 2;
    IEC0bits.T1IE = 1;
    IFS0bits.T1IF = 0;      
    EnableInterrupts();

    while(1);
    return 0;
}

    // VECTOR datasheet pg 74
void _int_(12) isr_T3(void){
        putChar('3');   
        IFS0bits.T3IF = 0;
}

void _int_(4) isr_T1(void){
        putChar('1');   
        IFS0bits.T1IF = 0;
}
