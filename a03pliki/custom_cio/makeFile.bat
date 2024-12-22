cl65 -t atari -c open_read.c
cl65 -t atari -c cio.s
cl65 -t atari -o cio_cc65.xex cio.o open_read.o

cl65 -t atari -c open_write.c
rem cl65 -t atari -c cio.s
cl65 -t atari -o cio_wr_cc65.xex cio.o open_write.o

cl65 -t atari -c delete.c
rem cl65 -t atari -c cio.s
cl65 -t atari -o delete65.xex cio.o open_write.o