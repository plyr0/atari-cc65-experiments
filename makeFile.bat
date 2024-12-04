@echo off
IF [%1]==[] goto :ARGZ
cl65 -t atari -O -S %~n1.c
move %~n1.s %~n1.asm
cl65 --debug-info -Wl --dbgfile,%~n1.lab -m %~n1.map -Ln %~n1.lbl -t atari -Oi %~n1.c -o %~n1.xex -C atari.cfg
%~n1.xex
goto :END

:ARGZ
echo Usage: makeFile file.c
pause

:END