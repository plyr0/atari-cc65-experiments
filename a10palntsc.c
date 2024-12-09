#include <atari.h>
#include <conio.h>

int main() {
    unsigned char i=0;

    while(1){
        if(ANTIC.vcount == 0x82){
            ++i;
            if(i>10) {
                cputs("NTSC\n");
                return 0;
            }
        }

        if(ANTIC.vcount > 0x83){
            cputs("PAL");
            return 0;
        }
    }
    
}