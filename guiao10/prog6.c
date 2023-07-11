#include <detpic32.h>

int main(void){
    // Configure UART2 (115200, N, 8, 1)
    U2BRG = (PBCLK + 8 * 19200)/(16 * 19200) - 1;
    U2MODEbits.BRGH = 0;
    U2MODEbits.PDSEL = 0;
    U2MODEbits.STSEL = 0;
    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;
    U2MODEbits.ON = 1;

    // config RD11 as output 
    TRISDbits.TRISD11 = 0;

    while(1){
        // Wait while TRMT == 0
        while(U2STAbits.TRMT == 0);
        // Set RD11
        LATDbits.LATD11 = 1;
        puts("12345");
        // Reset RD11 
        LATDbits.LATD11 = 0;
    }
    return 0;
}
