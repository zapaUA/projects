#include <detpic32.h>


int main(void)
{
	TRISB = TRISB & 0x80FF;		// 1000 0000 1111 1111
	LATB = LATB & 0x80FF;
	
	TRISD = TRISD & 0xFF9F;		// 1111 1111 1001 1111
	LATDbits.LATD5 = 1;
	LATDbits.LATD6 = 0;
	
	char c;
	while(1)
	{
		c = getChar();
		putChar(c);
		putChar('\r');
		
		if (c == 'a')
		LATBbits.LATB8 = 1;
	}
	return 0;
}
