#include "custom_cio.h"

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

A_FILE a_dir( char *wildcard ) {
   uint8_t a_error;

    uint8_t iocbToUse = findFreeIOCB();
    if( iocbToUse == 0xff )
        return 0xff;

    a_error = callCIO( iocbToUse, IOCB_OPEN, ICAX_DISK_READ_DIR, 0, wildcard, 0);
    if( a_error == CIO_SUCCESS ) {
        iocbFree[ iocbToUse ] = false;
        atEOF[ iocbToUse ] = false;
        return iocbToUse;
    } else
        callCIO( iocbToUse, IOCB_CLOSE, 0, 0, NULL, 0 );

    return 0xff;
}
