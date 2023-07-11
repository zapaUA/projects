#include <detpic32.h>

void  configADC(void);
void  send2displays(unsigned char value);
unsigned char toBcd(unsigned char value);

int main(void)
{
    //declare variables
	static int sample = 4;
    unsigned int i = 0;
    unsigned int p = 0;
    unsigned int volt = 0;
	
    //port config
    TRISB = (TRISB & 0x80FF);
	TRISD = TRISD & 0xFF9F;
	TRISE = TRISE & 0xFF00;
    configADC();

    //---------------------------------------------------------------------------
	while(1)
	{
		if(p == 0){
            AD1CON1bits.ASAM = 1;				// Start conversion
		    while(IFS1bits.AD1IF == 0);			// Wait while conversion not done
    
		    int *p = (int *)(&ADC1BUF0);		// Read ADC value
	    	for(i = 0; i < sample; i++){
			    printInt(p[i*4], 10|4 << 16);
			    putChar(' ');
			    volt += p[i*4];
            }
		    volt = ((volt/sample)*33+511)/1023;		// Read Volt
            putChar('\r');
		    IFS1bits.AD1IF = 0;						// Reset AD1IF bit
        }

		send2displays(toBcd(volt));
		LATE = (LATE & 0xFF00) | volt;
        // display freq: wait 10 ms (1/100Hz)
		resetCoreTimer();
		while(readCoreTimer() < 200000);
        // counter freq: 1/5Hz = 200 ms
        p = (p + 1) % 5;    //10ms * 5 = 50ms
	}
	return 0;
}

void  configADC(void){
	TRISBbits.TRISB4 = 1; 		// RBx digital output disconnected
	AD1PCFGbits.PCFG4= 0; 		// RBx configured as analog input
	AD1CON1bits.SSRC = 7; 		// Conversion trigger selection bits: in this
								// mode an internal counter ends sampling and
								// starts conversion
	AD1CON1bits.CLRASAM = 1; 	// Stop conversions when the 1st A/D converter
								// interrupt is generated. At the same time,
								// hardware clears the ASAM bit
	AD1CON3bits.SAMC = 16; 		// Sample time is 16 TAD (TAD = 100 ns)
	AD1CON2bits.SMPI = 4-1; 	// Interrupt is generated after N samples
								// (replace N by the desired number of
								// consecutive samples)
	AD1CHSbits.CH0SA = 4; 		// replace x by the desired input
								// analog channel (0 to 15)
	AD1CON1bits.ON = 1; 		// Enable A/D converter
								// This must the last command of the A/D
								// configuration sequence 
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
