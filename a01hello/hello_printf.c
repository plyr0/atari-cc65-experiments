#include <stdio.h>
#include <atari.h>

int main (void)
{
    printf("Hello, world!");
    OS.ch = 255;
    while(OS.ch == 255)
      ;
    return 0;
}