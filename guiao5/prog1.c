#include <detpic32.h>

void send2displays(unsigned char);
void delay(int);
 
int main(void)
	{
	// configure RB8-RB14 as outputs
	// configure RD5-RD6 as outputs
    TRISB = TRISB & 0x80FF;
    LATB = LATB & 0x80FF;
    TRISD = TRISD & 0xFF9F;
    LATD = LATD & 0xFF9F;

    unsigned char cnt = 0;
    while (1) {
        send2displays(cnt++);
        delay(100);
    }
    return 0;
}

void send2displays(unsigned char value)
	{
	static const char display7Scodes[] = {0x3F,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,
										0x77,0x7c,0x39,0x5e,0x79,0x71};
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

void delay(int ms)			//delay permite t maiores que 1seg
	{
		for (; ms > 0; ms--) {
        resetCoreTimer();
        while (readCoreTimer() < 20000);
    }
}
