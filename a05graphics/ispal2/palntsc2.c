#include <atari.h>
#include <stdio.h>
#include <stdint.h>

#if defined(__clang__)
    extern uint8_t _ispal(void);
#define ispal _ispal
#elif defined(__CC65__)
    extern uint8_t ispal(void);
#else
#error Unknown compiler. Only cc65 and llvm-mos are supported.
#endif

int main() {
	uint8_t pal = ispal();
	if(GTIA_READ.pal & 0b00001110 == 0b00001110){
		printf("GTIA: NTSC\n");
	} else {
		printf("GTIA: PAL\n");
	}
	
    if(pal == 155 || pal == 156){
        printf("ANTIC: PAL50Hz");
    } else {
        printf("ANTIC: NTSC60Hz");
    }

    OS.ch = 255;
    while(OS.ch == 255)
      asm volatile("");
    return 0;
}