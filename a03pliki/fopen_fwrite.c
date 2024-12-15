#include <stdio.h>
#include <conio.h>  // kbhit()
#include <string.h> // strlen()

int main() {
    char c[1000];
    FILE *fptr;
    unsigned len, result;

    if ((fptr = fopen("hello.txt", "w")) == NULL) {
        printf("Error! File cannot be opened.");
    } else {
        printf("Enter string for to write:\n");
        scanf("%[^\n]", c);
        len = strlen(c);
        result = fwrite(c, 1, len, fptr);
        if (result != len)
            printf("Error writing:%d/%d\n", result, len);
        fclose(fptr);
    }
    while(!kbhit());
    return 0;
}