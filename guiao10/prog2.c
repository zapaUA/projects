#include <detpic32.h>

void putstr(char *str);
void putc(char byte);

int main(void){
    // Configure UART2 (115200, N, 8, 1); fator divisao: x16
    // 1 - Configure BaudRate Generator
    // 2 – Configure number of data bits, parity and number of stop bits
    // (see U2MODE register)
    // 3 – Enable the trasmitter and receiver modules (see register U2STA)
    // 4 – Enable UART2 (see register U2MODE)
    
    // ver manual UART
    U2BRG = 10;             // (20MHz/16*115200)-1
    // (bit3)
    U2MODEbits.BRGH = 0;    // x16 = 0

    // PDSEL = 00 (bit2-1); STSEL = 0 (bit0) 
    U2MODEbits.PDSEL = 0;   // 0,1,2,3
    U2MODEbits.STSEL = 0;
    
    // URXEN = 1 (bit10); UTXEN = 1 (bit12)
    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;
    
    // (bit15)
    U2MODEbits.ON = 1; 

    while(1){
        putstr("String de teste\n");
        
        // wait 1s
        resetCoreTimer();
        while(readCoreTimer() < 20E6);  // 20E6 == PBCLK == 20000000
    }
    return 0;
}

void putstr(char *str){
    // use putc() function to send each charater ('\0' should not be sent)
    int i;
    for(i = 0; *str != '\0'; i++){
        putc(*str);
        str++;
    }

}
void putc(char byte){
    // wait while UART2 UTXBF == 1
    // Copy "byte" to the U2TXREG register 
    
    while(U2STAbits.UTXBF == 1);
    U2TXREG = byte;
}
