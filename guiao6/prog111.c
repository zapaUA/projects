#include <detpic32.h>

void  delay(int ms);
void  send2displays(unsigned char value);

int main(void){
    TRISB = TRISB & 0x80FF;  // TRISB[8] A TRISB[14] SAO SAIDAS
    TRISD = TRISD & 0xFF9F;  // displays high e low sao saidas
    LATDbits.LATD5 = 0;      // display high desligado
    LATDbits.LATD6 = 0;      // display low desligado

    int i = 0;
    char c;
    unsigned char display = 0;
    while(1){
        c = inkey();
        switch (c) {
            case 0:
                if(display==0xFF) display = 5;
                break;
            case '0':
                display = 0x00;
                break;
            case '1':
                display = 0x01;
                break;
            case '2':
                display = 0x02;
                break;
            case '3':
                display = 0x03;
                break;
            default:
                display = 0xFF;
                break;
        }


        if (display == 0xFF) {
            putChar('.');
            for (i = 0; i < 100; i++) {
                delay(10);
                send2displays(0xFF);
            }
            LATDbits.LATD5 = 0;  // display high desligado
            LATDbits.LATD6 = 0;  // display low desligado
        } else if (display < 0x04){
            i = 0;
            do{
                send2displays(display);
                delay(10);
            } while(++i < 2);
          
        }
    }
    return 0;
}

void  send2displays(unsigned char value){
    static const char display7Scodes[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,	//0..9
										  0x77,0x7C,0x39,0x5E,0x79,0x71};                       //A..F

    static char displayFlag = 0;
    unsigned char dl = value & 0x0F;
    unsigned char dh = value >> 4;
    

    if(displayFlag == 0){
        LATD = (LATD & 0xFF9F) | 0x0020;
        LATB = (LATB & 0x80FF) | display7Scodes[dl] << 8;
    }else{
        LATD = (LATD & 0xFF9F) | 0x0040;
        LATB = (LATB & 0x80FF) | display7Scodes[dh] << 8;
    }
    displayFlag = !displayFlag;
}

void delay(int ms) {
    resetCoreTimer();
    while (readCoreTimer() < ms * 20000);
}