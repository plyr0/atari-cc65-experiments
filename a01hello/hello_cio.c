#include <atari.h>

#define CIOV ((unsigned int)0xE456)
#define CHANNEL ((unsigned int)0)


#ifdef __clang__
void ciov(void){
    asm volatile ("LDX #%0" : : "i"(CHANNEL * 16));
    asm volatile ("JSR %0" : : "i"(CIOV));
    asm volatile ("RTS" : : );
}
#else
void ciov(void){
    asm("LDX #%b", CHANNEL * 16);
    asm("JSR %w", CIOV);
    asm("RTS");
}
#endif

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
    OS.ch = 255;
    while(OS.ch == 255)
      ;
    return 0;
}