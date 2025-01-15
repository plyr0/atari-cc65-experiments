/*
(C) kklis
https://weblambdazero.blogspot.com/2022/03/llvm-mos-compiler-for-8-bit-6502.html
*/

#include <atari.h>

#define SDMCTL (*((unsigned char*)0x22F))

int main() {
    unsigned char line, counter = 0;

    SDMCTL = 0; // disable display in BASIC screen area
    while (1) {
        line = ANTIC.vcount;  // read current screen line
        if (!line) counter++; // increase colour shift on new frame
        ANTIC.wsync = line;   // block CPU until vertical sync
        GTIA_WRITE.colbk = line + counter; // change background colour
    }
    return 0;
}