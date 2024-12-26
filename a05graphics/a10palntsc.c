#include <atari.h>
#include <stdio.h>

int main() {
    unsigned char old_nmien = ANTIC.nmien;
	ANTIC.nmien = 0;
    while(ANTIC.vcount < 0x82){
        ANTIC.wsync = 1;
    }
    ANTIC.wsync = 1;
    ANTIC.wsync = 1;
    if(ANTIC.vcount == 0){
        puts("NTSC");
    } else {
        puts("PAL");
    }
    ANTIC.nmien = old_nmien;

    OS.ch = 255;
    while(OS.ch == 255)
      ;
    return 0;
}