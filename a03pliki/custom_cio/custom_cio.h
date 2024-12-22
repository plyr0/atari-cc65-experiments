#ifndef __CUSTOM_CIO_H
#define __CUSTOM_CIO_H

// Stolen from damosan314 https://github.com/damosan314/roguelike

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
//#define ICAX_DISK_READ_DIR  0x06    // read disk directory
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

static uint8_t callCIO( uint8_t iocb_channel, uint8_t command, uint8_t aux1, uint8_t aux2, void *data, uint16_t bytes );
static uint8_t findFreeIOCB( void );
static uint8_t ciov();

#if defined(__clang__)
    uint8_t _cio( uint8_t A );
#define cio _cio
#elif defined(__CC65__)
    uint8_t cio( uint8_t A );
#else
#error Unkown compiler. Only cc65 and llvm-mos are supported.
#endif

// iocb0 = screen, (BASIC: iocb6 = graphics, iocb7 = printer)
bool iocbFree[ 8 ] = { false, true, true, true, true, true, false, false };
bool atEOF[ 8 ]    = { false, false, false, false, false, false, false, false };

static uint8_t callCIO( uint8_t iocb_channel, uint8_t command, uint8_t aux1, uint8_t aux2, void *data, uint16_t bytes ) {
    uint8_t a_error, cio_channel;

    OS.iocb[iocb_channel].command = command;
    if( command == IOCB_OPEN ) 
    {
        OS.iocb[iocb_channel].aux1 = aux1;
        OS.iocb[iocb_channel].aux2 = aux2;
    }
    OS.iocb[iocb_channel].buffer=data;
    OS.iocb[iocb_channel].buflen=bytes;

    cio_channel = iocb_channel << 4; // channel in four high bits
    a_error = cio( cio_channel );
    return a_error;
}

static uint8_t findFreeIOCB( void ) {
    uint8_t i;

    for( i = 0; i < 8; i++ )
        if( iocbFree[ i ] == true ) {
            return i;
        }
    return 0xff;
}

uint16_t a_fwrite( A_FILE f, void *data, uint16_t size ) {
    uint8_t a_error;

    a_error = callCIO( f, IOCB_PUTCHR, 0, 0, data, size );
    if( a_error == CIO_SUCCESS )
        return OS.iocb[ f ].buflen;
    return 0;
}

uint16_t a_fread( A_FILE f, void *data, uint16_t size ) {
    uint8_t a_error;

    a_error = callCIO( f, IOCB_GETCHR, 0, 0, data, size );
    if( a_error == CIO_END_OF_FILE ) {
        atEOF[ f ] = true;
        return 0;
    }

    if( a_error == CIO_SUCCESS )
        return OS.iocb[ f ].buflen;

    return 0;
}

bool a_feof( A_FILE f ) { return atEOF[ f ]; }

void a_fclose( A_FILE f ) {
    uint8_t a_error;

    a_error = callCIO( f, IOCB_CLOSE, 0, 0, NULL, 0 );
    if( a_error == CIO_SUCCESS ) {
        iocbFree[ f ] = true;
        atEOF[ f ] = false;
    }
}

A_FILE a_fopen( char *filename, char *mode ) {
    uint8_t openMode, a_error;

    uint8_t iocbToUse = findFreeIOCB();
    if( iocbToUse == 0xff )
        return 0xff;

    switch( *mode ) {
        case 'W':
        case 'w':
            openMode = ICAX_DISK_WRITE_NEW;
            break;
        case 'R':
        case 'r':
            openMode = ICAX_DISK_OPEN_FILE;
            break;
    }

    a_error = callCIO( iocbToUse, IOCB_OPEN, openMode, 0, filename, 0);
    if( a_error == CIO_SUCCESS ) {
        iocbFree[ iocbToUse ] = false;
        atEOF[ iocbToUse ] = false;
        return iocbToUse;
    } else
        callCIO( iocbToUse, IOCB_CLOSE, 0, 0, NULL, 0 );

    return 0xff;
}

bool a_fdelete( char *filename ) {
    uint8_t a_error, iocbToUse;
    char localFilename[ 20 ];
    bool rv = false;

    strcpy( localFilename, filename );
    localFilename[ strlen( filename ) + 1 ] = EOL;

    iocbToUse = findFreeIOCB();
    if( iocbToUse == 0xff )
        return false;

    a_error = callCIO( iocbToUse, IOCB_DELETE, 0, 0, &localFilename, 0 );
    if( a_error == CIO_SUCCESS )
        rv = true;
    callCIO( iocbToUse, IOCB_CLOSE, 0, 0, NULL, 0 );

    return rv;
}

#endif // __CUSTOM_CIO_H
