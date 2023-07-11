#include <detpic32.h>

int main(void){
    // port config
    TRISE = TRISE & 0xFFFE;     //RE0 output
    LATE = LATE & 0xFFFE;       //RE0 = 0
    TRISD = TRISD | 0x0100;     //RD8 input

    // timer T2 config
    T2CONbits.TCKPS = 4;        //k = 16
    PR2 = 37499;                //33.3Hz
    TMR2 = 0;
    T2CONbits.TON = 1;

    // Enable timer T2 interrupts
    IPC2bits.T2IP = 2;
    IEC0bits.T2IE = 1;
    IFS0bits.T2IF = 0; 
    
    // Enable INT1 interrupts
    IPC1bits.INT1IP = 2;
    IEC0bits.INT1IE = 1;
    IFS0bits.INT1IF = 0;
    INTCONbits.INT1EP = 0;
    EnableInterrupts();
    
    while(1);
    return 0;
}

volatile int i = 0;
    
void _int_(8) isr_T2(void){
    //static int i = 0;
    i = i + 1;
    if(i == 100){
        LATEbits.LATE0 = 0;        // apaga após 3s
        T2CONbits.TON = 0;
    }
    IFS0bits.T2IF = 0;
}

void _int_(7) isr_INT1(void){
    T2CONbits.TON = 1;
    TMR2 = 0;
    LATEbits.LATE0 = 1;
    i = 0;
    IFS0bits.INT1IF = 0;
}
