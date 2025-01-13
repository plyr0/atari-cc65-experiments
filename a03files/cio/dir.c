#include <atari.h>
#include <stdio.h>
#include <stdint.h>
#include "custom_cio/custom_cio.h"

uint8_t fptr;
int i;
char buffer[1000];

void print_file(void);
void a_getch(void);

int main() {

    printf("List D:*.*\n");
    fptr = a_dir("D:*.*");
    print_file();
    a_fclose(fptr);
    a_getch();
    
    printf("List D1:*.*\n");
    fptr = a_dir("D1:*.*");
    print_file();
    a_fclose(fptr);
    a_getch();
    
    return 0;
}

void print_file()
{
    if (fptr == 0xFF) {
        printf("error");
    }
    else {
        i = 0;
        while (a_fread(fptr, buffer + i, 1) > 0) {
            ++i;
        }
        printf("Data from the file:\n%s", buffer);
    }
}

void a_getch()
{
    OS.ch = 255;
    while (OS.ch == 255)
        asm volatile("");
}
