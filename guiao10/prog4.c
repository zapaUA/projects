#include <detpic32.h>

void putstr(char *str);
void putc(char byte);
char getc(void)

int main(void){
    // Configure UART2 (115200, N, 8, 1); fator divisao: x16
    // ((PBCLK+8*baudRate)/(divFactor*baudRate))-1
    U2BRG = (20E6 + 8 * 115200) / (16 * 115200) - 1;
    U2MODEbits.BRGH = 0;    // 0,1
    U2MODEbits.PDSEL = 0;   // 0,1,2,3
    U2MODEbits.STSEL = 0;   // 0,1
    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;
    U2MODEbits.ON = 1; 

    while(1){
        putc(getc());
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
    // Wait while UART2 UTXBF == 1
    // Copy "byte" to the U2TXREG register
    while(U2STAbits.UTXBF == 1);
    U2TXREG = byte;
}

char getc(void){
    // Wait while URXDA == 0
    // Return U2RXREG
    while(U2STAbits.URXDA == 0);
    return U2RXREG;
}
