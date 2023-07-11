#include <detpic32.h>

void  configAll(void);
void  send2displays(unsigned char value);
unsigned char toBcd(unsigned char value);
volatile int voltage = 0;

int main(void)
{
    configAll();

    EnableInterrupts();
	while(1){
        if(PORTBbits.RB1 == 0 && PORTBbits.RB0 == 1)
            IEC0bits.T1IE = 0;
        else
            IEC0bits.T1IE = 1;
    };
	return 0;
}

void _int_(4) isr_T1(void){
    AD1CON1bits.ASAM = 1;				// Start A/D conversion
    IFS0bits.T1IF = 0;
}

void _int_(12) isr_T3(void){
    send2displays(toBcd(voltage));      // Send the value of the global variable "voltage" to the displays
                                        // using BCD (decimal) format
    IFS0bits.T3IF = 0;                  // Reset T3IF flag
}

void _int_(27) isr_AD1(void){
    // Calculate buffer average (8 samples)
    // Calculate voltage amplitude and copy it to "voltage"

    static int i;
    int *p = (int *)(&ADC1BUF0);
	    for(i = 0; i < 8; i++){
		    voltage += p[i*4];
        }
	voltage = ((voltage/8)*33+511)/1023;

    IFS1bits.AD1IF = 0;                 // Reset AD1IF flag 
}

void  configAll(void){
	//port config
    TRISB = (TRISB & 0x80FF) | 0x0002;
	TRISD = TRISD & 0xFF9F;

    //ADC
    TRISBbits.TRISB4 = 1; 		// RBx digital output disconnected
	AD1PCFGbits.PCFG4 = 0; 		// RBx configured as analog input
	AD1CON1bits.SSRC = 7; 		// Conversion trigger selection bits: in this
								// mode an internal counter ends sampling and
								// starts conversion
	AD1CON1bits.CLRASAM = 1; 	// Stop conversions when the 1st A/D converter
								// interrupt is generated. At the same time,
								// hardware clears the ASAM bit
	AD1CON3bits.SAMC = 16; 		// Sample time is 16 TAD (TAD = 100 ns)
	AD1CON2bits.SMPI = 8-1; 	// Interrupt is generated after N samples
								// (replace N by the desired number of
								// consecutive samples)
	AD1CHSbits.CH0SA = 4; 		// replace x by the desired input
								// analog channel (0 to 15)
	AD1CON1bits.ON = 1; 		// Enable A/D converter
								// This must the last command of the A/D
								// configuration sequence
    
    //Timers T1:5Hz T3:100Hz
    T1CONbits.TCKPS = 2;        // k = 20MHz/(5Hz*65536) = 61 => 64
    PR1 = 62499;
    TMR1 = 0;
    T1CONbits.TON = 1;

    T3CONbits.TCKPS = 2;            
    PR3 = 49999;               
    TMR3 = 0;
    T3CONbits.TON = 1;

    // Enable timer & ADC interrupts
    IPC1bits.T1IP = 2;
    IEC0bits.T1IE = 1;
    IFS0bits.T1IF = 0;
    
    IPC3bits.T3IP = 2;
    IEC0bits.T3IE = 1;
    IFS0bits.T3IF = 0;

    IPC6bits.AD1IP = 2;
    IEC1bits.AD1IE = 1;
    IFS1bits.AD1IF = 0;
}

void  send2displays(unsigned char value){
    static const char display7Scodes[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,	//0..9
										  0x77,0x7C,0x39,0x5E,0x79,0x71};                       //A..F

    static char displayFlag = 0;
    unsigned char dl = value & 0x0F;
    unsigned char dh = value >> 4;
    

    if(displayFlag == 0){
        LATD = (LATD & 0xFF9F) | 0x0020;
        LATB = (LATB & 0x80FF) | display7Scodes[dl] << 8;
    }else{
        LATD = (LATD & 0xFF9F) | 0x0040;
        LATB = (LATB & 0x80FF) | display7Scodes[dh] << 8;
    }
    displayFlag = !displayFlag;
}

unsigned char toBcd(unsigned char value){
    return ((value/10) << 4) + (value % 10);
}
