#include <atari.h>
#include <stdio.h>
#include <stdint.h>

void a_getch()
{
    OS.ch = KEY_NONE;
    while (OS.ch == KEY_NONE)
        asm volatile("");
}

int main()
{
	uint8_t i;
	
    for(i=0; i<10; i++){
		putchar(i+'0');
		putchar(CH_EOL);
	}
	a_getch();
		
	for(i=0; i<10; ++i){
		putchar(i+'0');
		putchar(CH_EOL);
	}
	a_getch();
	
	i=0;
	while(i<10){
		putchar(i+'0');
		putchar(CH_EOL);
		++i;
	}
	a_getch();

    return 0;
}