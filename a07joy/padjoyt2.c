#include <atari.h>
#include <stdint.h>
#include <stdio.h>

int main (void)
{
    OS.ch = 255;
    while(OS.ch != KEY_ESC) {
        printf("(%d %d %d %d)", POKEY_READ.pot0, POKEY_READ.pot1, POKEY_READ.pot2, POKEY_READ.pot3);
    }
    return 0;
}
