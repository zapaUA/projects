#include <detpic32.h>

void putc1(char byte);

int main(void){
    // Configure UART1 (115200, N, 8, 1); fator divisao: x16
    U1BRG = (20E6 + 8 * 115200) / (16 * 115200) - 1;
    U1MODEbits.BRGH = 0;    // 0,1
    U1MODEbits.PDSEL = 0;   // 0,1,2,3
    U1MODEbits.STSEL = 0;   // 0,1
    U1STAbits.UTXEN = 1;
    U1STAbits.URXEN = 1;
    U1MODEbits.ON = 1;  

    while(1){
        putc1(0x0F);
        resetCoreTimer();
        while(readCoreTimer() < 200000);   
   
    }
    return 0;
}

void putc1(char byte){
    while(U1STAbits.UTXBF == 1);
    U1TXREG = byte;
}
