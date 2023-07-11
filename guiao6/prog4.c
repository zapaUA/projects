#include <detpic32.h>

void  configADC(void);

int main(void)
{
	static int sample = 4;
	configADC();
	while(1)
	{
		AD1CON1bits.ASAM = 1;				// Start conversion
		while(IFS1bits.AD1IF == 0);			// Wait while conversion not done
		
		int i, volt = 0;
		int *p = (int *)(&ADC1BUF0);		// Read ADC value
		for(i = 0; i < sample; i++)
		{
			printInt(p[i*4], 10|4 << 16);
			putChar(' ');
			volt += p[i*4];
		}
		volt = ((volt/sample)*33+511)/1023;		// Read Volt
		
		printInt(volt, 10|2 << 16);
		putChar('\r');
		
		IFS1bits.AD1IF = 0;						// Reset AD1IF bit
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
