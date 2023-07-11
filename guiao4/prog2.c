#include <detpic32.h>

int main(void)
{
	TRISE = TRISE & 0xFF87;		// 0xFF 1000 0111
	LATE = LATE & 0xFF87;
	
	int cnt = 0;
	while(1)
	{
		
		LATE = (LATE & 0xFF87) | cnt << 3;
		printInt(cnt, 10 | 2 << 16);
		putChar('\r');
		resetCoreTimer();
		while(readCoreTimer() < 5000000);
		cnt++;
		
		if (cnt == 10)
			cnt = 0;			
	}
	return 0;
}
