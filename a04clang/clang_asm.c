#ifndef __clang__
#error Clang only
#endif

#include <atari.h>
#include <stdio.h>
#include <stdlib.h>

#define CONST_BYTE ((unsigned char)0xF)
#define CONST_UINT 1025U

int main (void)
{
    srand(POKEY_READ.random);
    char ch = (unsigned char)rand();
    int i = rand();

    unsigned char result_const;
    char result_dyn;
    unsigned int result_const_uint;
    int result_dyn_uint;

    asm volatile ("LDA #%1\n"
                  "ADC #2\n" 
                  : "=a"(result_const) : "i"(CONST_BYTE));

    asm volatile ("LDA %1\n"
                  "ADC #2\n" 
                  : "=a"(result_dyn) : "r"(ch));

    printf("%d %d\n", CONST_BYTE, result_const);
    printf("%d %d\n", ch, result_dyn);
    // printf("%d %d\n", CONST_UINT, result_const_uint);
    // printf("%d %d\n", i, result_dyn_uint);

    OS.ch = 255;
    while(OS.ch == 255)
      ;
    return 0;
}