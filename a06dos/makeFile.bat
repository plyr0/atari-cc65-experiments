@echo off
IF [%1]==[] goto :ARGZ
cl65 --debug-info -Wl --dbgfile,%~n1.lab -m %~n1.map -Ln %~n1.lbl -t atari -C atari.cfg -Oi %~n1.c -o %~n1.xex
goto :END

:ARGZ
echo Usage: makeFile file.c
pause

:END
