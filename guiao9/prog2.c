#include <detpic32.h>

int main(void){
    //T3 config
    T3CONbits.TCKPS = 2;    // k = 20MHz/(100Hz*65536) => 4
    PR3 = 49999;            // PR3 = 20MHz/(100Hz*4)-1 = 49999
    TMR3 = 0;
    T3CONbits.TON = 1;

    IPC3bits.T3IP = 2;
    IEC0bits.T3IE = 1;
    IFS0bits.T3IF = 0;

    OC1CONbits.OCM = 6;     // PWM mode on OCx; fault pin disabled
    OC1CONbits.OCTSEL = 1;  // Use timer T3 as the time base for PWM generation
    OC1RS = 12500;          // Ton = PRx*duty_cicle = 50000*0.25 = 12500
    OC1CONbits.ON = 1;      // Enable OC1 module 
    
    while(1);
    return 0;
}

void _int_(12) isr_T3(void){
    IFS0bits.T3IF = 0;
}
