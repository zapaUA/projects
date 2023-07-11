#include <detpic32.h>

void setPWM(unsigned int dutyCycle);

int main(void){
    //port config
    TRISDbits.TRISD0 = 1;
    TRISCbits.TRISC14 = 0;
    LATCbits.LATC14 = 0;
    
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
    OC1CONbits.ON = 1;      // Enable OC1 module 

    setPWM(50);    

    while(1){
        LATCbits.LATC14 = PORTDbits.RD0;
    };
    return 0;
}

void _int_(12) isr_T3(void){
    IFS0bits.T3IF = 0;
}

void setPWM(unsigned int dutyCycle){
    // duty_cycle must be in the range [0, 100]
    if(dutyCycle >= 0 && dutyCycle <= 100){
        OC1RS = (PR3+1)*dutyCycle/100;          // Determine OC1RS as a function of "dutyCycle"
    }
}
