#include <atari.h>
#include <string.h>

#include <atari_screen_charmap.h>
char* hello = "Hello, world!";
#include <atari_atascii_charmap.h>

int main (void)
{
    memcpy(OS.savmsc, hello, 13);
    OS.ch = 255;
    while(OS.ch == 255)
      ;
    return 0;
}