#include <detpic32.h>

void configUart2(unsigned int baud, char parity, unsigned int stopbits);
void putc(char byte);

int main(void){
    TRISCbits.TRISC14 = 0;
    LATCbits.LATC14 = 0;

    configUart2(115200,'N',1);

    //enable U2RXIE, disable U2TXIE (register IEC1) 
    IEC1bits.U2RXIE = 1;
    IEC1bits.U2TXIE = 0;
    //set UART2 priority level (register IPC8) 
    IPC8bits.U2IP = 2;
    //clear Interrupt Flag bit U2RXIF (register IFS1)
    IFS1bits.U2RXIF = 0;
    //define RX interrupt mode (URXISEL bits)
    U2STAbits.UTXISEL = 0;
    U2STAbits.URXISEL = 0;

    EnableInterrupts();

    while(1);
    return 0;
}

volatile char c;
void _int_(32) isr_uart2(void){
    if(IFS1bits.U2RXIF == 1){
        // Read character from FIFO (U2RXREG)
        // Send the character using putc()
        c = U2RXREG;
        putc(c);
        
        if(c == 'T'){
            LATCbits.LATC14 = 1;
        } else if(c == 't'){
            LATCbits.LATC14 = 0;
        }
        // Clear UART2 Rx interrupt flag
        IFS1bits.U2RXIF = 0;
    }
}

void configUart2(unsigned int baud, char parity, unsigned int stopbits){
    // Default arguments: (115200, N, 1)
    
    // Configure BaudRate Generator
    U2MODEbits.BRGH = 0;
    if(baud < 600 || baud > 115200){
        U2BRG = (PBCLK + 8 * 115200)/(16 * 115200) - 1;
    }else{
        U2BRG = (PBCLK + 8 * baud)/(16 * baud) - 1;
    }    

    // Configure number of data bits (8), parity and number of stop bits
    switch(parity){
        case 'O':
            U2MODEbits.PDSEL = 2;
            break;        
        case 'E':
            U2MODEbits.PDSEL = 1;
            break;
        default:
            U2MODEbits.PDSEL = 0;
    }

    if(stopbits == 2){
        U2MODEbits.STSEL = 1;
    }else{
        U2MODEbits.STSEL = 0;
    }

    // Enable the trasmitter and receiver modules
    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;

    // Enable UART2 
    U2MODEbits.ON = 1;
}

void putc(char byte){
    // Wait while UART2 UTXBF == 1
    // Copy "byte" to the U2TXREG register
    while(U2STAbits.UTXBF == 1);
    U2TXREG = byte;
}
