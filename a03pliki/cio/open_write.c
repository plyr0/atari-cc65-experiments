#include <atari.h>
#include <stdio.h>  // printf()
#include <string.h> // strlen()
#include <stdint.h>
#include "custom_cio/custom_cio.h"

int main() {

#if defined(__clang__)
    char c[] = "This is hello from llvm-mos!!";
#elif defined(__CC65__)
    char c[] = "This is hello from cc65!!";
#else
#error Unknown compiler. Only cc65 and llvm-mos are supported.
#endif

    uint8_t fptr;
    uint16_t len, result;

    fptr = a_fopen("D1:hello.txt", "W");
    if(fptr == 0xFF){
        printf("error");
    } else {
        len = strlen(c);
        result = a_fwrite(fptr, c, len);
        if(result != len)
            printf("Error writing:%d/%d\n", result, len);
        a_fclose(fptr);
    }

    OS.ch = 255;
    while(OS.ch == 255)
      ;
    return 0;
}
