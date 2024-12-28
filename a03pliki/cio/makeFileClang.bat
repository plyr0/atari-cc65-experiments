mos-clang --config mos-atari8-dos.cfg -Os -flto -o cio_clang.xex open_read.c custom_cio/cio.s custom_cio/custom_cio.c
mos-clang --config mos-atari8-dos.cfg -Os -flto -o cio_wr_clang.xex open_write.c custom_cio/cio.s custom_cio/custom_cio.c
mos-clang --config mos-atari8-dos.cfg -Os -flto -o delete_clang.xex delete.c custom_cio/cio.s custom_cio/custom_cio.c
mos-clang --config mos-atari8-dos.cfg -Os -flto -o dir_clang.xex dir.c custom_cio/cio.s custom_cio/custom_cio.c
