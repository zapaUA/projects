#include <detpic32.h>

int main(void)
{
	// Configure port RC14 as output
	TRISCbits.TRISC14 = 0;
	LATCbits.LATC14 = 1;
	while(1)
	{
		// Wait 0.5s
		resetCoreTimer();
		while(readCoreTimer() < PBCLK/2);	
		// Toggle RC14 port value
		LATCbits.LATC14 = !LATCbits.LATC14;
	}
	return 0;
}
