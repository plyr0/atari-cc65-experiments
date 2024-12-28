#include <atari.h>
#include <stdio.h>
#include <stdint.h>
#include "custom_cio/custom_cio.h"

int main() {
    char c[1000];
    int i = 0;
    uint8_t fptr;

    fptr = a_dir("D1:*.*");
    
    if(fptr == 0xFF){
        printf("error");
    } else {
        while(a_fread(fptr, c + i, 1)) {
            ++i;
        }
        printf("Data from the file:\n%s", c);
        a_fclose(fptr);
    }

    OS.ch = 255;
    while(OS.ch == 255)
      ;
    return 0;
}
