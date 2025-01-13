@echo off
IF [%1]==[] goto :ARGZ
mos-clang --config mos-atari8-dos.cfg -Tlink.ld -Os -flto %~n1.c -o %~n1_cl.xex
goto :END

:ARGZ
echo Usage: makeFileClang file.c
pause

:END
