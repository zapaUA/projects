#include <detpic32.h>

int main(void)
{
	// RB14..8 outputs, RD6..5 outputs
	TRISB = TRISB & 0x80FF ;		// 1000 0000 1111 1111
	TRISD = TRISD & 0xFF9F; 		// 0xFF 1001 1111 
		
	LATB = (LATB & 0x80FF) | 0x0000;
	LATD = (LATD & 0xFF9F) | 0x0020;

	char c;
	while(1)
		{
		c =	getChar();
		putChar(c);
		
		if(c == 'a' || c == 'A')
			LATB = (LATB & 0x80FF) | 0x0100;
		else if(c == 'b' || c == 'B')
			LATB = (LATB & 0x80FF) | 0x0200;
		else if(c == 'c' || c == 'C')
			LATB = (LATB & 0x80FF) | 0x0400;
		else if(c == 'd' || c == 'D')
			LATB = (LATB & 0x80FF) | 0x0800;
		else if(c == 'e' || c == 'E')
			LATB = (LATB & 0x80FF) | 0x1000;
		else if(c == 'f' || c == 'F')
			LATB = (LATB & 0x80FF) | 0x2000;
		else if(c == 'g' || c == 'G')
			LATB = (LATB & 0x80FF) | 0x4000;
		else if(c == '5')
			LATD = (LATD & 0xFF9F) | 0x0020;
		else if(c == '6')
			LATD = (LATD & 0xFF9F) | 0x0040;
		}
	return 0;
}
