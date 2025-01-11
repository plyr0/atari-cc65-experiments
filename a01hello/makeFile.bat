@echo off
IF [%1]==[] goto :ARGZ
rem cl65 -t atari -O -S %~n1.c
rem move %~n1.s %~n1.asm
cl65 --debug-info -Wl --dbgfile,%~n1.lab -m %~n1.map -Ln %~n1.lbl -t atari -Oi %~n1.c -o %~n1.xex
rem cl65 -t atari -Osir %~n1.c -o %~n1.xex
rem %~n1.xex
goto :END

:ARGZ
echo Usage: makeFile file.c
pause

:END