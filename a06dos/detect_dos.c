/*
https://forums.atariage.com/topic/186973-current-disk-device-number/
https://forums.atariage.com/topic/252474-how-to-detect-sparta-dos/#comment-3507849
http://atariki.krap.pl/index.php/Programowanie:_Jak_stwierdzi%C4%87_obecno%C5%9B%C4%87_SpartaDOS_X_oraz_jego_konfiguracj%C4%99_pami%C4%99ci
C:\cc65\libsrc\atari\dosdetect.s
*/

#include <stdio.h>
#include <atari.h>
#include <peekpoke.h>
#include <stdint.h>

#define DDEVIC          0x0300
#define DUNIT           0x0301
#define DOS 			0x0700
#define SDX_VERSION	    0x0701
#define SDX_SUBVERSION	0x0702
#define BEWEDOS_MAGIC   0x0703
#define SPARTA_FILE_ID  0x0760
#define SDX_DEVICE   	0x0761
#define SPARTA_FILENAME 0x0762
#define SPARTA_NAMELEN  ((uint8_t)11)

uint8_t c, i;

void sparta(void);

int main(void)
{
	printf("\n");
	c = PEEK(DOS);
	if (c == 'S')
		sparta();
	else if (c == '\x0B' || c == '\xE8')
		printf("Very old SpartaDOS 0x0700=%#x\n", c);
	else if (c == 'M')
		printf("MyDOS 0x0700=%#x\n", c);
	else if (c == 'X')
		printf("XDOS 0x0700=%#x\n", c);
	else if (c == 'R')
		printf("RealDOS 0x0700=%#x\n", c);
	else
		printf("Unknown DOS 0x0700=%c\n", c);

	printf("\n");
	c = PEEK(DDEVIC);
	printf("DDEVIC 0x0300=%d", c); /* doesn't work on sparta at all */
	printf(" => D%d\n", c - 48);
	printf("DUNIT 0x0301=%d\n", PEEK(DUNIT)); /* might not work on sparta properly */

	OS.ch = 255;
	while (OS.ch == 255)
		asm volatile("");
	return 0;
}

void sparta(void)
{
	c = PEEK(BEWEDOS_MAGIC);
	if (c == 'B' && PEEK(BEWEDOS_MAGIC+1) == 'W') {
		printf("BeweDOS 0x0703=%c\n", c);
		return;
	}

	printf("SpartaDOS 0x0700=%c\n", c);
	c = PEEK(SDX_VERSION);
	printf("Version 0x0701=%#x", c);

	if (c < 0x41)
		return;

	printf(" => SpartaDOS X\n");
	printf("FILE_ID 0x0760=%d\n", PEEK(SPARTA_FILE_ID));
	printf("File name 0x0762=");
	for (i = 0; i < SPARTA_NAMELEN; ++i) {
		if (i == 8)
			printf(".");
		printf("%c", PEEK(SPARTA_FILENAME + i));
	}
	printf("\n");

	c = PEEK(SDX_DEVICE);
	printf("DEVICE 0x0761=%#x => ", c);
	switch (c & 0b11110000) {
	case 0: printf("DSK "); break;
	case 0x10: printf("CLK "); break;
	case 0x20: printf("CAR "); break;
	case 0x30: printf("CON "); break;
	case 0x40: printf("PRN "); break;
	default:   printf("?(%#x) ", c & 0b11110000);
	}
	printf("%d", c & 0b00001111);

	printf("\n");

	/* TODO getenv address of sparta procedure */
}
