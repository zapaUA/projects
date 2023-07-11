#include <detpic32.h>

void send2displays(unsigned char value);

int main(void)
{
	// declare variables
	unsigned int i = 0;
	unsigned int counter = 0;
	
	// intialize ports
	TRISB = TRISB & 0x80FF;
	TRISD = TRISD & 0xFF9F;
	
	while(1)
	{
		send2displays(counter);
		
		// display freq: wait 20 ms (1/50Hz)
		resetCoreTimer();
		while(readCoreTimer() < 400000);
		
		// counter freq: 1/5Hz = 200 ms
		i = (i + 1) % 10; //(20ms * 10)
		if(i == 0)
			// increment counter (mod 256)
			counter++;
	}
	return 0;
}

void send2displays(unsigned char value)
{
	static const char display7Scodes[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,	//0..9
										  0x77,0x7C,0x39,0x5E,0x79,0x71};						//A..F
	
	static char displayFlag = 0; 	// static variable: doesn't lose its
									// value between calls to function
	
	if(displayFlag == 0)
	{
		// select display low
		LATD = (LATD & 0xFF9F) | 0x0020;
		// send digit_low (dl) to display: dl = value & 0x0F
		unsigned char dl = value & 0x0F;
		LATB = (LATB & 0x80FF) | display7Scodes[dl] << 8;
	}
	else 
	{
		// select display high
		LATD = (LATD & 0xFF9F) | 0x0040;
		// send digit_high (dh) to display: dh = value >> 4
		unsigned char dh = value >> 4;
		LATB = (LATB & 0x80FF) | display7Scodes[dh] << 8;
	}
	displayFlag = !displayFlag;
} 
