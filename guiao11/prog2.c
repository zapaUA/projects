#include <detpic32.h>

void putstrInt(char *s);
void configUart2(unsigned int baud, char parity, unsigned int stopbits);
typedef struct{
    char mem[100];  //size
    int nchar;      //number of chars
    int posrd;      //position
} t_buf;
volatile t_buf txbuf;

int main(){
    configUart2(115200,'N',1);

    //disable U2RXIE, disable U2TXIE (register IEC1) 
    IEC1bits.U2RXIE = 0;
    IEC1bits.U2TXIE = 0;
    //set UART2 priority level (register IPC8) 
    IPC8bits.U2IP = 2;
    //clear Interrupt Flags bit U2RXIF U2TXIF (register IFS1)
    IFS1bits.U2RXIF = 0;
    IFS1bits.U2TXIF = 0;
    //define RX TX interrupt mode (URXISEL bits)
    U2STAbits.UTXISEL = 0;
    U2STAbits.URXISEL = 0;

    EnableInterrupts();

    txbuf.nchar = 0;

    while(1){
        putstrInt("Bifinhos\n");
    }
    return 0;
}

void _int_(32) isr_uart2(void){
    if(IFS1bits.U2TXIF == 1){
        if(txbuf.nchar > 0){
            U2TXREG = txbuf.mem[txbuf.posrd];
            txbuf.posrd++;
            txbuf.nchar--;
        }else {
            IEC1bits.U2TXIE = 0;
        }
        IFS1bits.U2TXIF = 0;
    }
}

void putstrInt(char *s){
    // Wait while the buffer is not empty
    while(txbuf.nchar > 0);

    // Copy all characters of the string "s" to the buffer
    while(*s != '\0'){
        txbuf.mem[txbuf.nchar] = *s;
        txbuf.nchar++;
        s++;
    }
    
    // Initialize "posrd" variable with 0
    // Enable UART2 Tx interrupts
    txbuf.posrd = 0;
    IEC1bits.U2TXIE = 1;
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
