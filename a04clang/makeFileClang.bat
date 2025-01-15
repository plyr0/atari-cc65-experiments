@echo off
IF [%1]==[] goto :ARGZ
mos-clang --config mos-atari8-dos.cfg -g -gline-tables-only -O0 -flto %~n1.c -o %~n1_cl.xex
rem -flto link time optimization
rem -O0 disable
rem -O1 debuggable, doesn't work with altirra
rem -O2 speed, keep size
rem -O3 speed aggresive
rem -Os size 
rem -Oz size aggresive

llvm-readelf --all %~n1_cl.xex.elf > %~n1_cl.xex.elf.lab
llvm-objdump -d %~n1_cl.xex.elf > %~n1_cl.xex.elf.s

goto :END

:ARGZ
echo Usage: makeFileClang file.c
pause

:END