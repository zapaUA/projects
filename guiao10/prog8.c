#include <detpic32.h>

void putstr(char *str);
void putc(char byte);
char getc(void);
void configUart1(unsigned int baud, char parity, unsigned int stopbits);


int main(void){
    configUart1(115200, 'E', 2);

    while(1){
        putstr("Bifinhos\n");
        resetCoreTimer();
        while(readCoreTimer() < 30000);    //1.5ms
        
        putc(0x41);
        resetCoreTimer();
        while(readCoreTimer() < 10000);    //0.5ms

    }
    return 0;
}

void configUart1(unsigned int baud, char parity, unsigned int stopbits){
    // Default arguments: (115200, N, 1)
    
    // Configure BaudRate Generator
    U1MODEbits.BRGH = 0;
    if(baud < 600 || baud > 115200){
        U1BRG = (PBCLK + 8 * 115200)/(16 * 115200) - 1;
    }else{
        U1BRG = (PBCLK + 8 * baud)/(16 * baud) - 1;
    }    

    // Configure number of data bits (8), parity and number of stop bits
    switch(parity){
        case 'O':
            U1MODEbits.PDSEL = 2;
            break;        
        case 'E':
            U1MODEbits.PDSEL = 1;
            break;
        default:
            U1MODEbits.PDSEL = 0;
    }

    if(stopbits == 2){
        U1MODEbits.STSEL = 1;
    }else{
        U1MODEbits.STSEL = 0;
    }
    
    // Enable the trasmitter and receiver modules
    U1STAbits.UTXEN = 1;
    U1STAbits.URXEN = 1;

    // Enable UART1 
    U1MODEbits.ON = 1;
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
    // Wait while UART1 UTXBF == 1
    // Copy "byte" to the U1TXREG register
    while(U1STAbits.UTXBF == 1);
    U1TXREG = byte;
}

char getc(void){
    // Wait while URXDA == 0
    // Return U1RXREG
    while(U1STAbits.URXDA == 0);
    return U1RXREG;
}
