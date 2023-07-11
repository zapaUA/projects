#include <detpic32.h>

int main(void)
{	
	// configurar RE6-RE1 como saídas
	TRISE = TRISE & 0xFF81;
	LATE = LATE & 0xFF81;   	//1111 1111 1100 0000
	
	// inicializar a variavel de contagem
	int cnt = 0;
	while(1)
	{
		LATE = (LATE & 0xFF81) | cnt << 1;
		resetCoreTimer();
		while(readCoreTimer() < PBCLK/4);
		cnt++;
		
		if(cnt == 64)
			cnt = 0;
	}
	return 0;
}
