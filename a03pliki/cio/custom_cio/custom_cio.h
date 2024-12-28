#ifndef __CUSTOM_CIO_H
#define __CUSTOM_CIO_H

// Original from damosan314 https://github.com/damosan314/roguelike

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <atari.h>

#define CIO_SUCCESS         ((uint8_t)0x01)
//#define CIO_NO_DEVICE       0x82
//#define CIO_NOT_OPEN        0x85
#define CIO_END_OF_FILE     ((uint8_t)0x88)
//#define CIO_TIMEOUT         0x8a
//#define CIO_DISK_FULL       0xa2
//#define CIO_FATAL_DISK      0xa3
//#define CIO_FILE_NOT_FOUND  0xaa

#define ICAX_DISK_OPEN_FILE ((uint8_t)0x04)    // read
#define ICAX_DISK_READ_DIR  ((uint8_t)0x06)    // read disk directory
#define ICAX_DISK_WRITE_NEW ((uint8_t)0x08)    // overwrite an existing file
//#define ICAX_DISK_WRITE_APP 0x09    // write-append mode
//#define ICAX_DISK_WRITE_OVR 0x12    // write-overwrite mode

#define EOL     ((uint8_t)0x9B)

typedef uint8_t A_FILE;

A_FILE a_fopen( char *filename, char *mode );
void a_fclose( A_FILE f );
uint16_t a_fwrite( A_FILE f, void *data, uint16_t size );
uint16_t a_fread( A_FILE f, void *data, uint16_t size );
bool a_feof( A_FILE f );
bool a_fdelete( char *filename );
A_FILE a_dir( char *wildcard );

static uint8_t callCIO( uint8_t iocb_channel, uint8_t command, uint8_t aux1, uint8_t aux2, void *data, uint16_t bytes );
static uint8_t findFreeIOCB( void );

#if defined(__clang__)
    uint8_t _cio( uint8_t A );
#define cio _cio
#elif defined(__CC65__)
    uint8_t cio( uint8_t A );
#else
#error Unkown compiler. Only cc65 and llvm-mos are supported.
#endif

#endif // __CUSTOM_CIO_H
