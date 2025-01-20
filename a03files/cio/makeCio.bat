cl65 -t atari -Osir -c custom_cio/cio.s
cl65 -t atari -Osir -c custom_cio/custom_cio.c

cl65 -t atari -Osir -c open_read.c
cl65 -t atari -o cio_cc65.xex custom_cio/custom_cio.o custom_cio/cio.o open_read.o

cl65 -t atari -Osir -c open_write.c
cl65 -t atari -o cio_wr_cc65.xex custom_cio/custom_cio.o custom_cio/cio.o open_write.o

cl65 -t atari -Osir -c delete.c
cl65 -t atari -o delete_cc65.xex custom_cio/custom_cio.o custom_cio/cio.o open_write.o

cl65 -t atari -Osir -c dir.c
cl65 -t atari -o dir_cc65.xex custom_cio/custom_cio.o custom_cio/cio.o dir.o
