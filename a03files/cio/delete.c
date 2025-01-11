#include <atari.h>
#include <stdio.h>  // printf()
#include <stdbool.h>
#include "custom_cio/custom_cio.h"

int main() {
    bool result;

    result = a_fdelete("D1:hello.txt");
    if(!result){
        printf("error");
    } else {
        printf("File deleted");
    }

    OS.ch = 255;
    while(OS.ch == 255)
      ;
    return 0;
}
