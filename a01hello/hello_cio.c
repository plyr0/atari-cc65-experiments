#include <atari.h>
#include <conio.h>

#define CIOV 0xE456
#define CHANNEL 0

void ciov(void){
    asm("LDX #%b", CHANNEL * 16);
    asm("JSR %w", CIOV);
    asm("RTS");
}

void printl(void* c, int l)
{
  OS.iocb[CHANNEL].buffer=c;
  OS.iocb[CHANNEL].buflen=l;
  OS.iocb[CHANNEL].command=IOCB_PUTCHR;
  ciov();
}

int main (void)
{
    printl("Hello, world!", 13);
    while(!kbhit());
    return 0;
}