#include <detpic32.h>

int main(void){
    // port config
    TRISE = TRISE & 0xFFFE;     //RE0 output
    LATE = LATE & 0xFFFE;       //RE0 = 0
    TRISD = TRISD | 0x0100;     //RD8 input

    // timer T2 config
    T2CONbits.TCKPS = 7;        //k = 256
    PR2 = 23437;                //3.3Hz
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

void _int_(8) isr_T2(void){
    static int i = 0;
    if(i == 0){
        LATEbits.LATE0 = 0;   
    }
    i = (i + 1) % 10;           // smp que i == 10, i = 0; 0.33Hz
    IFS0bits.T2IF = 0;
}

void _int_(7) isr_INT1(void){
    if(PORTDbits.RD8 == 0){
        LATEbits.LATE0 = 1;
        TMR2 = 0;
    }
    IFS0bits.INT1IF = 0;
}
