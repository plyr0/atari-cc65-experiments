#include <conio.h>
#include <atari.h>

int main (void)
{
    cputs("Hello, world!");
    OS.ch = 255;
    while(OS.ch == 255)
      ;
    return 0;
}