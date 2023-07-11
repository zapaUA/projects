#include <detpic32.h>

int main(void){
	TRISCbits.TRISC14 = 0;
	// TRISC = TRISC & 0xBFFF;		1011111111111111   
	
	LATCbits.LATC14 = 0;
	// LATC = LATC & 0xBFFF;		1011111111111111
	
	while(1){
		resetCoreTimer();
		while(readCoreTimer() < 10000000);
		
		LATCbits.LATC14 = !LATCbits.LATC14;
		// LATC = LATC ^ 0x4000;
	}
	return 0;
}
