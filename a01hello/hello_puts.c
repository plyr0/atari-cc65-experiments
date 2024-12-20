#include <stdio.h>
#include <conio.h>
#include <atari.h>

int main (void)
{
    puts("Hello, world!");
    OS.ch = 255;
    while(OS.ch == 255)
      ;
    return 0;
}