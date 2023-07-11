#include <detpic32.h>

// U2TXREG = '.';  prints char to help debug

void configADC(void);
void configDisplays(void);
void configInterrupts(void);
void send2Displays(unsigned char value);

volatile unsigned char voltage = 0; // Global variable
int main(void)
{
    unsigned int cnt = 0;
    // Configure all (digital I/O, analog input, A/D module, interrupts)
    configADC();
    configDisplays();
    configInterrupts();
    EnableInterrupts();     // Global Interrupt Enable

    while(1)
    {
        if(cnt == 0)
        // 0, 200 ms, 400 ms, ... (5 samples/second)
        {
            AD1CON1bits.ASAM = 1;   // Start A/D conversion
        }
        send2Displays(voltage);   	// Send "voltage" value to displays
        cnt = (cnt + 1) % 20;    	// 20*10ms = 200ms
                
        // Wait 10 ms -> 100Hz
        resetCoreTimer();
        while(readCoreTimer() < 200000);	//20MHz/100Hz -> 200000
    }
return 0;
}

void _int_(27) isr_adc(void)
{
    // Read 8 samples (ADC1BUF0, ..., ADC1BUF7) and calculate average
    // Calculate voltage amplitude
    // Convert voltage amplitude to decimal and store the result in the
    // global variable "voltage"
    // Reset AD1IF flag
		
    int *p = (int *)(&ADC1BUF0);
	int i, volt = 0;
	for(i = 0; i < 8; i++)
	{
		volt += p[i*4];
	}
	volt = ((volt/8)*33+511)/1023;		
	voltage = ((volt/10)<<4) + (volt % 10);	// convert to BCD	
	IFS1bits.AD1IF = 0;						// Reset AD1IF bit
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
	AD1CON2bits.SMPI = 1-1; 	// Interrupt is generated after N samples
								// (replace N by the desired number of
								// consecutive samples)
	AD1CHSbits.CH0SA = 4; 		// replace x by the desired input
								// analog channel (0 to 15)
	AD1CON1bits.ON = 1; 		// Enable A/D converter
								// This must the last command of the A/D
								// configuration sequence 
}

void  configDisplays(void){
    TRISB = TRISB & 0x80FF;
    LATB = LATB & 0x80FF;		// configure RB8-RB14 as outputs
    TRISD = TRISD & 0xFF9F;
    LATD = LATD & 0xFF9F;		// configure RD5-RD6 as outputs 
}

void  configInterrupts(void){
	IPC6bits.AD1IP = 2; 			// configure priority of A/D interrupts 
	IEC1bits.AD1IE = 1; 			// enable A/D interrupts
	IFS1bits.AD1IF = 0; 			// clear A/D interrupt flag 
}

void send2Displays(unsigned char value){
	static const char display7Scodes[] = {
		0x3F,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,  //0..9
		0x77,0x7c,0x39,0x5e,0x79,0x71};						//A..F
	// select display high
	// send digit_high (dh) to display: dh = value >> 4
	// select display low
	// send digit_low (dl) to display: dl = value & 0x0F

	static char displayFlag = 0;	// static variable: doesn't lose its
									// value between calls to function
	unsigned char dl = value & 0x0F;
	unsigned char dh = value >> 4; 
	if (displayFlag == 0)
		{
            LATD = (LATD & 0xFF9F) | 0x0020;
			LATB = (LATB & 0x80FF) | display7Scodes[dl] << 8;	
		}	else
		{
            LATD = (LATD & 0xFF9F) | 0x0040;
			LATB = (LATB & 0x80FF) | display7Scodes[dh] << 8;
        }
	displayFlag = !displayFlag;
}
