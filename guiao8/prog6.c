#include <detpic32.h>

int main(void){
    // output config
    TRISD = TRISD | 0x0100;
    TRISE = TRISE & 0xFFFE;
    LATE = LATE & 0xFFFE;

    static int i = 0;
    while(1){
        if(PORTDbits.RD8 == 0){
        LATEbits.LATE0 = 1;
        while(PORTEbits.RE0 == 1){
            resetCoreTimer();
            while(readCoreTimer() < 20000000);
            if(i == 2){
                LATEbits.LATE0 = 0;
                putChar('.');   
                }
            i = (i + 1) % 3;            // smp que i == 3, i = 0;
            }
        }
    }
    return 0;
}
