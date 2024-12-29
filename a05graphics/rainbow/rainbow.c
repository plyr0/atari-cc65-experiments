// Based on Yaron Nir's tutorial

#include <atari.h>
#include <string.h>

#define CHARSET_MEM  0x3000
#define DLIST_MEM    0x4000
#define SCREEN_MEM   0x5000
#define BLANK_VCOUNT (3 * 8 / 2)
#define MODE_VCOUNT  (24 * 8 / 2 + BLANK_VCOUNT)

#pragma bss-name (push,"ZEROPAGE")
#pragma data-name (push,"ZEROPAGE")
volatile unsigned char counter;
volatile unsigned char is_vblank_occured;
#pragma bss-name (pop)
#pragma data-name (pop)
#pragma zpsym ("counter");
#pragma zpsym ("is_vblank_occured");

#if defined(__clang__)
    void _waitvblank(void);
#define waitvblank _waitvblank
#elif defined(__CC65__)
    void waitvblank(void);
#else
#error Unkown compiler. Only cc65 and llvm-mos are supported.
#endif

unsigned char antic4_display_list[32] = {
    DL_DLI(DL_BLK8),
    DL_DLI(DL_BLK8),
    DL_DLI(DL_BLK8),
    DL_DLI(DL_LMS(DL_GRAPHICS12)),
    0x00,
    0x50,
    DL_DLI(DL_GRAPHICS12), DL_DLI(DL_GRAPHICS12), DL_DLI(DL_GRAPHICS12),
    DL_DLI(DL_GRAPHICS12), DL_DLI(DL_GRAPHICS12), DL_DLI(DL_GRAPHICS12), DL_DLI(DL_GRAPHICS12),
    DL_DLI(DL_GRAPHICS12), DL_DLI(DL_GRAPHICS12), DL_DLI(DL_GRAPHICS12), DL_DLI(DL_GRAPHICS12),
    DL_DLI(DL_GRAPHICS12), DL_DLI(DL_GRAPHICS12), DL_DLI(DL_GRAPHICS12), DL_DLI(DL_GRAPHICS12),
    DL_DLI(DL_GRAPHICS12), DL_DLI(DL_GRAPHICS12), DL_DLI(DL_GRAPHICS12), DL_DLI(DL_GRAPHICS12),
    DL_DLI(DL_GRAPHICS12), DL_DLI(DL_GRAPHICS12), DL_DLI(DL_GRAPHICS12), DL_DLI(DL_GRAPHICS12),
    DL_DLI(DL_JVB),
    0x00,
    0x40
};

void dli_routine(void)
{
    asm volatile("pha");
    asm volatile("txa");
    asm volatile("pha");
    asm volatile("tya");
    asm volatile("pha");

    ANTIC.wsync = 1;
    if(ANTIC.vcount > BLANK_VCOUNT && ANTIC.vcount < MODE_VCOUNT) {
        GTIA_WRITE.colbk = OS.color4 = ANTIC.vcount + counter;
    } else {
        ANTIC.wsync = 1;    
        GTIA_WRITE.colbk = OS.color4 = 0;
    }

	asm volatile("pla");
    asm volatile("tay");
    asm volatile("pla");
    asm volatile("tax");
    asm volatile("pla"); 
    asm volatile("rti");
}

void vbi_routine(void)
{
	is_vblank_occured = 1;
    asm volatile("pla");
    asm volatile("tay");
    asm volatile("pla");
    asm volatile("tax");
    asm volatile("pla"); 
    asm volatile("rti");
}

void init_vbi_dli(void)
{
    waitvblank();
	OS.vvblki = &vbi_routine;
	OS.vdslst = &dli_routine;
	ANTIC.nmien = NMIEN_DLI | NMIEN_VBI;
}

void wait_for_vblank(void)
{
	while (is_vblank_occured == 0)
        asm volatile(""); //llvm-mos aggresively removes empty loops

	is_vblank_occured = 0;
}

int main(void)
{
    memcpy((void *)DLIST_MEM, antic4_display_list, sizeof(antic4_display_list));
    OS.sdlst = (void *)DLIST_MEM;

    init_vbi_dli();
    counter=0;
	
    for(;;){
        wait_for_vblank();
        ++counter;
    }
    return 0;
}
