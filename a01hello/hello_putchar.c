#include <stdio.h>
#include <atari.h>

char* hello = "Hello, world!";
char c, i;

int main (void)
{
    i = 0;
    c = hello [0];
    while(c) {
      putchar(c);
      ++i;
      c = hello[i];
    }

    OS.ch = 255;
    while(OS.ch == 255)
      ;
    return 0;
}