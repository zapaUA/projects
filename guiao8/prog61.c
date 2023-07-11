#include <detpic32.h>

int main(void){
    // output config
    TRISD = TRISD | 0x0100;
    TRISE = TRISE & 0xFFFE;
    LATE = LATE & 0xFFFE;

    while(1){
        if(PORTDbits.RD8 == 0){
        LATEbits.LATE0 = 1;
        while(PORTEbits.RE0 == 1){
            resetCoreTimer();
            while(readCoreTimer() < 60000000);  //delay 3s
            LATEbits.LATE0 = 0;
            }
        }
    }
    return 0;
}
