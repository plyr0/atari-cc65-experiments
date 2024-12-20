#include <atari.h>

void printinternal(unsigned char* mem, char* str);

unsigned char ch, i;

int main (void)
{
    printinternal(OS.savmsc, "Hello, world!");
    OS.ch = 255;
    while(OS.ch == 255)
      ;
    return 0;
}

void printinternal(unsigned char* mem, char* str){
    ch = str[0];
    i = 0;
    while(ch){
        if(ch>0 && ch<=0x1F || ch>=0x80 && ch<=0x9F){ 
            ch += 0x40; //Ruszczyc asembler book
        } else if(ch>=0x20 && ch<=0x5F || ch>=0xA0 && ch<=0xDF){
            ch -= 0x20;
        } //else atascii=internal
        mem[i] = ch;
        ++i;
        ch=str[i];
    }
}