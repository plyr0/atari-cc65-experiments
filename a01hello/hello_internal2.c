#include <atari.h>
#include <conio.h>
#include <string.h>

#include <atari_screen_charmap.h>
char* hello = "Hello, world!";
#include <atari_atascii_charmap.h>

int main (void)
{
    memcpy(OS.savmsc, hello, 13);
    while(!kbhit());
    return 0;
}