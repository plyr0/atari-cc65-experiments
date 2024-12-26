#include <atari.h>
#include <stdlib.h>
#include <unistd.h>

unsigned char i;

int main (void)
{
    _graphics(2 + 16);
    OS.sdmctl = 33;
    srand(POKEY_READ.random);

    OS.ch = 255;
    while(OS.ch == 255)
    {
      for(i = 0; i<12*16; i++ ){
          OS.savmsc[i] = (unsigned char)(rand());
      }
      sleep(1);
    }
    return 0;
}
