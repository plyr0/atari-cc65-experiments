#include <atari.h>
#include <stdio.h>
#include <string.h> // strlen()

int main() {
    char c[] = "This is hello from fopen_fwrite";
    FILE *fptr;
    unsigned len, result;

    if ((fptr = fopen("hello.txt", "w")) == NULL) {
        printf("Error! File cannot be opened.");
    } else {
        len = strlen(c);
        result = fwrite(c, 1, len, fptr);
        if (result != len)
            printf("Error writing:%d/%d\n", result, len);
        fclose(fptr);
    }
    OS.ch = 255;
    while(OS.ch == 255)
      ;
    return 0;
}