#include <atari.h>
#include <string.h>
#include <stdlib.h>

#define DLIST_MEM    0x4000
#define SCREEN_MEM   0x5000

unsigned char antic4_display_list[21] = {
    DL_LMS(DL_GRAPHICS1),
    //DL_LMS(DL_GRAPHICS0),
    0x00,
    0x50,
    DL_GRAPHICS2, 
    DL_GRAPHICS2,
    DL_GRAPHICS2,
    DL_GRAPHICS2, 
    DL_GRAPHICS2,
    DL_GRAPHICS2,
    DL_GRAPHICS2, 
    DL_GRAPHICS2,
    DL_GRAPHICS2, 
    DL_GRAPHICS2, 
    DL_GRAPHICS2, 
    DL_GRAPHICS2,
    DL_GRAPHICS2, 
    DL_GRAPHICS2, 
    DL_GRAPHICS1, 
    DL_JVB,
    0x00,
    0x40
};

int main(void)
{
    unsigned i, j;

    memcpy((void*)DLIST_MEM, antic4_display_list, sizeof(antic4_display_list));
    OS.sdlst = (void*)DLIST_MEM;
    OS.sdmctl = 33; // narrow playfield
    srand(POKEY_READ.random);

    OS.ch = 255;
    while(OS.ch == 255)
    {
        OS.color0 = GTIA_COLOR_RED;
        OS.color1 = GTIA_COLOR_GREEN;
        OS.color2 = GTIA_COLOR_YELLOW;
        OS.color3 = GTIA_COLOR_CYAN;
        OS.color4 = GTIA_COLOR_BLACK;

        for(i = 0; i<16*16; i++ ){
            //((unsigned char*)SCREEN_MEM)[i] = (unsigned char)(rand());
            ((unsigned char*)SCREEN_MEM)[i] = i;
        }
        for(j=0; j<65535U; j++) asm volatile(""); //unistd.h sleep();
    }

    return 0;
}