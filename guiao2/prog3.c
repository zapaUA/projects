
#include <detpic32.h>

void delay(int);

int main() {

    int cnt1 = 0;
    int cnt5 = 0;
    int cnt10 = 0;

    while (1) {
        delay(100);

        cnt10++;

        cnt5 += cnt10 % 2 == 0;
        cnt1 += cnt10 % 10 == 0;

        putChar('\r');
        printInt(cnt10, 10 | 5 << 16);
        putChar('\t');
        printInt(cnt5, 10 | 5 << 16);
        putChar('\t');
        printInt(cnt1, 10 | 5 << 16);
    }

    return 0;
}


void delay(int ms) {
    for (; ms > 0; ms--) {
        resetCoreTimer();
        while (readCoreTimer() < 20000);
    }
}
