#include <detpic32.h>

int main(void)
{
	// configure RB8-RB14 as outputs
	TRISB = TRISB & 0x80FF;		// 1000 0000 1111 1111
	
	// configure RB0-RB3 as inputs
	TRISB = TRISB | 0x000F;
	
	// configure RD5-RD6 as outputs
	TRISD = TRISD & 0xFF9F;		// 1111 1111 1001 1111
	
	// enable display low (RD5) and disable display high (RD6)
	LATD = (LATD & 0xFF9F) | 0x0040;	//0000 0000 0010 0000
	
	
	static const char disp7Scodes[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,	//0..9
									   0x77,0x7C,0x39,0x5E,0x79,0x71};						//A..F
	while(1)
	{
		// read dip-switch
		int codes = PORTB & 0x000F;
		
		// convert to 7 segments code
		codes = disp7Scodes[codes];
		
		// send to display
		LATB = (LATB & 0x80FF) | codes << 8;
	}
	return 0;
}
