#include <atari.h>
#include <conio.h>

unsigned char i=0;

int main() {
    while(1){    
        if(ANTIC.vcount == 0x82){
            ++i;
            if(i>10) {
                cputs("NTSC");
                goto END;
            }
        }

        if(ANTIC.vcount > 0x83){
            cputs("PAL");
            goto END;
        }
    }
END:
    while(!kbhit());
    return 0;
}